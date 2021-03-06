//
// Created by bparsy on 5/18/20.
//

#ifndef FIRE_PROGRAM_HH
#define FIRE_PROGRAM_HH

#include <string>
#include <GL/glew.h>
#include <memory>
#include <unordered_map>

class WinRender;

class Program {
public:
    using ptr = std::unique_ptr<Program>;

    Program();
    ~Program();
    static GLuint compile_shader(GLuint type, std::string const& src);
    static std::string shader_src_path(std::string const& name, GLuint type);
    GLuint attach_shader(std::string const& name, GLuint type);
    GLint link();
    void validate();
    static ptr make_program(std::string const& vtx, std::string const& fgt, std::string const& geo = "");
    static ptr make_compute(std::string const& cpt);
    [[nodiscard]] GLuint id() const;
    [[nodiscard]] bool is_ready() const;
    void use() const;
    void dispatch(GLuint x, GLuint y, GLuint z);
    [[nodiscard]] GLint uniform_location(std::string const& name) const;

    template<GLenum TYPE, typename ...Args>
    void set_uniform(std::string const& name, Args ...args) const;

    class Example {
    public:
        static void triangle(WinRender const& wh);
        static void square(WinRender const& wr);
        static void cube(WinRender const& wr);
    };

protected:
    GLuint program_id_;
    bool ready_;
    mutable std::unordered_map<std::string, GLint> location_cache_;
};

template<GLenum TYPE, typename... Args>
inline void Program::set_uniform(const std::string& name, Args... args) const {
    void(args...);
    throw std::runtime_error(name + ": unrecognized/unimplemented uniform type");
}

template<>
inline void Program::set_uniform<GL_FLOAT_VEC4>(const std::string& name, float v0, float v1, float v2, float v3) const {
    glUniform4f(uniform_location(name), v0, v1, v2, v3);
}

template<>
inline void Program::set_uniform<GL_FLOAT_MAT4>(const std::string& name, const float* mat_ptr) const {
    glUniformMatrix4fv(uniform_location(name), 1, GL_FALSE, mat_ptr);
}

template<>
inline void Program::set_uniform<GL_FLOAT>(const std::string& name, float arg) const {
    glUniform1f(uniform_location(name), arg);
}

template<>
inline void Program::set_uniform<GL_INT>(const std::string& name, int arg) const {
    glUniform1i(uniform_location(name), arg);
}

#endif //FIRE_PROGRAM_HH
