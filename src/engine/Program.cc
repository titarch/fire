//
// Created by bparsy on 5/18/20.
//

#include <fstream>
#include <vector>
#include <iostream>
#include "Program.hh"
#include "WinHandler.hh"
#include "buffers/BufHandler.hh"

Program::Program() : program_id_(0), ready_(false) {}

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

Program::ptr Program::make_program(const std::string& vertex_shader_fp, const std::string& fragment_shader_fp) {
    auto p = std::make_unique<Program>();
    p->program_id_ = glCreateProgram();

    auto v_src = load_file(vertex_shader_fp);
    auto f_src = load_file(fragment_shader_fp);

    GLuint v_shd, f_shd;
    try { v_shd = Program::compile_shader(GL_VERTEX_SHADER, v_src); } catch (std::runtime_error const& e) {
        std::cerr << "Failed to compile vertex shader (" << vertex_shader_fp << "): " << e.what() << std::endl;
        p->program_id_ = 0;
        return p;
    }
    try { f_shd = Program::compile_shader(GL_FRAGMENT_SHADER, f_src); } catch (std::runtime_error const& e) {
        std::cerr << "Failed to compile fragment shader (" << fragment_shader_fp << "): " << e.what() << std::endl;
        p->program_id_ = 0;
        return p;
    }

    glAttachShader(p->program_id_, v_shd);
    glAttachShader(p->program_id_, f_shd);

    glLinkProgram(p->program_id_);
    GLint link_status;
    glGetProgramiv(p->program_id_, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        GLint log_size;
        glGetProgramiv(p->program_id_, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<char> program_log(log_size);
        glGetProgramInfoLog(p->program_id_, log_size, &log_size, program_log.data());
        std::string log(program_log.cbegin(), program_log.cend());
        std::cerr << "Failed to link program: " << log << std::endl;
        glDeleteProgram(p->program_id_);
        glDeleteShader(v_shd);
        glDeleteShader(f_shd);
        p->program_id_ = 0;
        return p;
    }

    glValidateProgram(p->program_id_);

    glDeleteShader(v_shd);
    glDeleteShader(f_shd);

    p->ready_ = true;
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

void Program::Example::triangle(const WinHandler& wh) {
    static constexpr std::array triangle = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    auto vao = BufHandler::make_vao();
    vao.add_buffer(
            BufHandler::make_vbo(triangle),
            BufHandler::make_layout().add_element<GL_FLOAT>(2)
    );
    Program::make_program("../res/shaders/vertex/basic.shd",
                          "../res/shaders/fragment/magenta.shd")->use();

    vao.bind();
    wh.draw(GL_TRIANGLES, 3, false);
    vao.unbind();
}

void Program::Example::square(const WinHandler& wh) {
    static constexpr std::array square = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
    };
    static constexpr std::array indices = {
            0u, 1u, 2u,
            2u, 3u, 0u
    };

    BufHandler::make_vao()
            .add_buffer(
                    BufHandler::make_vbo(square),
                    BufHandler::make_layout().add_element<GL_FLOAT>(2)
            );

    BufHandler::make_ibo(indices);
    auto p = Program::make_program("../res/shaders/vertex/basic.shd",
                                   "../res/shaders/fragment/uniform.shd");
    p->use();

    auto loc = glGetUniformLocation(p->id(), "u_Color");
    glUniform4f(loc, 0.0f, 1.0f, 1.0f, 1.0f);

    wh.draw(GL_TRIANGLES, indices.size(), true);
}
