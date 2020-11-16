//
// Created by bparsy on 5/18/20.
//

#include <fstream>
#include <vector>
#include <iostream>
#include "../utils/transform.hh"
#include "Program.hh"
#include "WinRender.hh"
#include "buffers/BufHandler.hh"
#include "../utils/colors.hh"
#include "shaders.hh"

Program::Program() : program_id_(0), ready_(false), location_cache_{} {}

Program::~Program() {
    glDeleteProgram(program_id_);
}

static std::string load_file(std::string const& filepath) {
    std::ifstream input(filepath);
    if (!input) throw std::runtime_error(filepath + ": could not open file");
    return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

GLuint Program::compile_shader(GLuint type, const std::string& src) {
    auto shd_id = glCreateShader(type);
    auto src_cstr = src.c_str();
    glShaderSource(shd_id, 1, &src_cstr, nullptr);
    glCompileShader(shd_id);

    GLint compile_status = GL_TRUE;
    glGetShaderiv(shd_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        GLint log_size;
        glGetShaderiv(shd_id, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<char> shd_log(log_size);
        glGetShaderInfoLog(shd_id, log_size, &log_size, shd_log.data());
        std::string shd_log_str(shd_log.cbegin(), shd_log.cend());
        glDeleteShader(shd_id);
        throw std::runtime_error(shd_log_str);
    }

    return shd_id;
}

std::string Program::shader_src_path(const std::string& name, GLuint type) {
    switch (type) {
        case GL_VERTEX_SHADER:
            return shd::vtx(name);
        case GL_FRAGMENT_SHADER:
            return shd::fgt(name);
        case GL_GEOMETRY_SHADER:
            return shd::gmt(name);
        default:
            throw std::runtime_error("Unrecognized shader type");
    }
}

GLuint Program::attach_shader(const std::string& name, GLuint type) {
    auto shd_path = shader_src_path(name, type);
    auto shd_src = load_file(shd_path);
    GLuint shd_id;
    try { shd_id = Program::compile_shader(type, shd_src); } catch (std::runtime_error const& e) {
        std::cerr << "Failed to compile shader (" << shd_path << "): " << e.what() << std::endl;
        program_id_ = 0;
        return 0;
    }
    glAttachShader(program_id_, shd_id);
    glDeleteShader(shd_id);
    return shd_id;
}

GLint Program::link() {
    glLinkProgram(program_id_);
    GLint link_status;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        GLint log_size;
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<char> program_log(log_size);
        glGetProgramInfoLog(program_id_, log_size, &log_size, program_log.data());
        std::string log(program_log.cbegin(), program_log.cend());
        std::cerr << "Failed to link program: " << log << std::endl;
        glDeleteProgram(program_id_);
        program_id_ = 0;
    }
    return link_status;
}

void Program::validate() {
    glValidateProgram(program_id_);
    ready_ = true;
}

Program::ptr Program::make_program(const std::string& vtx, const std::string& fgt) {
    auto p = std::make_unique<Program>();
    p->program_id_ = glCreateProgram();

    if (p->attach_shader(vtx, GL_VERTEX_SHADER) == 0) return p;
    if (p->attach_shader(fgt, GL_FRAGMENT_SHADER) == 0) return p;

    if (p->link() != GL_TRUE) return p;
    p->validate();

    return p;
}

GLuint Program::id() const {
    return program_id_;
}

bool Program::is_ready() const {
    return ready_;
}

void Program::use() const {
    if (!is_ready()) throw std::runtime_error("Cannot use program (not ready)");
    glUseProgram(program_id_);
}

GLint Program::uniform_location(const std::string& name) const {
    if (location_cache_.contains(name)) return location_cache_.at(name);
    GLint location = glGetUniformLocation(program_id_, name.c_str());
    if (location == -1) throw std::runtime_error(name + " could not be located in shader");
    location_cache_.emplace(name, location);
    return location;
}

void Program::Example::triangle(const WinRender& wh) {
    static constexpr std::array triangle = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    auto vao = BufHandler::make_vao();
    vao->add_data(
            triangle,
            VertexBufferLayout::Common::F2D()
    );
    vao->add_indices(std::array{0u, 1u, 2u});
    auto p = Program::make_program("basic", "magenta");
    p->use();
    while (wh.is_open()) {
        wh.clear();
        wh.draw(*vao, *p);
        wh.display();
    }
}

void Program::Example::square(const WinRender& wr) {
    static constexpr std::array square = {
            -0.5f, -0.5f, 0.f, 0.f,
            0.5f, -0.5f, 1.f, 0.f,
            0.5f, 0.5f, 1.f, 1.f,
            -0.5f, 0.5f, 0.f, 1.f
    };
    static constexpr std::array indices = {
            0u, 1u, 2u,
            2u, 3u, 0u
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    auto vao = BufHandler::make_vao();
    vao->add_data(
            square,
            VertexBufferLayout::Common::F2D()
                    .add_element<GL_FLOAT>(2)
    );
    vao->add_indices(indices);

    auto p = Program::make_program("tex2d", "tex2d");
    p->use();

    Sprite texture("../res/assets/atmo.png");
    texture.bind(0);
    p->set_uniform<GL_INT>("u_texture_sampler", 0);

    auto ratio = wr.ratio();
    const glm::mat4 ortho_proj = glm::ortho(-ratio, ratio, -1.f, 1.f, -1.f, 1.f);
    p->set_uniform<GL_FLOAT_MAT4>("u_MVP", &ortho_proj[0][0]);

    while (wr.is_open()) {
        wr.clear();
        wr.draw(*vao, *p);
        wr.display();
    }
}

void Program::Example::cube(const WinRender& wr) {
    struct Vertex {
        float position[3];
        float normal[3];
    }__attribute__((packed));


    static constexpr std::array<Vertex, 24> cube = {
            // back
            Vertex{{0.f, 0.f, 0.f},
                   {0.f, 0.f, 1.f}},
            {{1.f, 0.f, 0.f}, {0.f, 0.f, 1.f}},
            {{0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}},
            {{1.f, 1.f, 0.f}, {0.f, 0.f, 1.f}},

            // front
            {{0.f, 0.f, 1.f}, {0.f, 0.f, -1.f}},
            {{1.f, 0.f, 1.f}, {0.f, 0.f, -1.f}},
            {{0.f, 1.f, 1.f}, {0.f, 0.f, -1.f}},
            {{1.f, 1.f, 1.f}, {0.f, 0.f, -1.f}},

            // down
            {{0.f, 0.f, 0.f}, {0.f, -1.f, 0.f}},
            {{1.f, 0.f, 0.f}, {0.f, -1.f, 0.f}},
            {{0.f, 0.f, 1.f}, {0.f, -1.f, 0.f}},
            {{1.f, 0.f, 1.f}, {0.f, -1.f, 0.f}},

            // up
            {{0.f, 1.f, 0.f}, {0.f, 1.f, 0.f}},
            {{1.f, 1.f, 0.f}, {0.f, 1.f, 0.f}},
            {{0.f, 1.f, 1.f}, {0.f, 1.f, 0.f}},
            {{1.f, 1.f, 1.f}, {0.f, 1.f, 0.f}},

            // left
            {{0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}},
            {{0.f, 1.f, 0.f}, {-1.f, 0.f, 0.f}},
            {{0.f, 0.f, 1.f}, {-1.f, 0.f, 0.f}},
            {{0.f, 1.f, 1.f}, {-1.f, 0.f, 0.f}},

            // right
            {{1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}},
            {{1.f, 1.f, 0.f}, {1.f, 0.f, 0.f}},
            {{1.f, 0.f, 1.f}, {1.f, 0.f, 0.f}},
            {{1.f, 1.f, 1.f}, {1.f, 0.f, 0.f}},
    };
    static constexpr std::array indices = {
            0u, 1u, 2u,
            1u, 2u, 3u,

            4u, 5u, 6u,
            5u, 6u, 7u,

            8u, 9u, 10u,
            9u, 10u, 11u,

            12u, 13u, 14u,
            13u, 14u, 15u,

            16u, 17u, 18u,
            17u, 18u, 19u,

            20u, 21u, 22u,
            21u, 22u, 23u,
    };

    auto vao = BufHandler::make_vao();
    vao->add_data(
            cube,
            VertexBufferLayout::Common::F3D()
                    .add_element<GL_FLOAT>(3)
    );
    vao->add_indices(indices);

    auto p = Program::make_program("classic3d", "color");
    p->use();

    auto ratio = wr.ratio();
    auto proj = Mat::perspective(45.f, ratio, 0.01f, 5.f);
    auto view = Mat::camera({0, 0, 3}, Vec::zero(), Vec::up());
    auto trans = Mat::id().translate({0, 0, 0});
    auto rot = Mat::id();
    p->set_uniform<GL_FLOAT_MAT4>("u_proj", proj.data());
    p->set_uniform<GL_FLOAT_MAT4>("u_view", view.data());
    p->set_uniform<GL_FLOAT_MAT4>("u_trans", trans.data());
    p->set_uniform<GL_FLOAT_MAT4>("u_pivot", Mat::id().translate({-0.5, -0.5, -0.5}).data());
    p->set_uniform<GL_FLOAT_VEC4>("u_light_position", -3.f, 3.f, -15.f, 1.f);
    glEnable(GL_DEPTH_TEST);

    auto hue = 0;
    while (wr.is_open()) {
        wr.clear();
        auto color = hsv(hue++, 1.f, 1.f);
        p->set_uniform<GL_FLOAT_VEC4>("u_light_color", color[0], color[1], color[2], 1.f);
        rot = rot.rotate(0.01f, {0.5, 1.f, 0.f});
        p->set_uniform<GL_FLOAT_MAT4>("u_rot", rot.data());
        wr.draw(*vao, *p);
        wr.display();
    }
}
