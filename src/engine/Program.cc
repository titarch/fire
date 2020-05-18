//
// Created by bparsy on 5/18/20.
//

#include <fstream>
#include <vector>
#include "Program.hh"

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

program_ptr Program::make_program(const std::string& vertex_shader_fp, const std::string& fragment_shader_fp) {
    auto p = std::make_unique<Program>();
    p->program_id_ = glCreateProgram();

    auto v_src = load_file(vertex_shader_fp);
    auto f_src = load_file(fragment_shader_fp);
    auto v_shd = Program::compile_shader(GL_VERTEX_SHADER, v_src);
    auto f_shd = Program::compile_shader(GL_FRAGMENT_SHADER, f_src);

    glAttachShader(p->program_id_, v_shd);
    glAttachShader(p->program_id_, f_shd);
    glLinkProgram(p->program_id_);
    glValidateProgram(p->program_id_);

    glDeleteShader(v_shd);
    glDeleteShader(f_shd);

    p->ready_ = true;
    return p;
}

bool Program::is_ready() {
    return ready_;
}

void Program::use() {
    glUseProgram(program_id_);
}



