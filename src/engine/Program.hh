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
    static ptr make_program(std::string const& vertex_shader_fp, std::string const& fragment_shader_fp);
    [[nodiscard]] GLuint id() const;
    [[nodiscard]] bool is_ready() const;
    void use() const;
    [[nodiscard]] GLint uniform_location(std::string const& name);

    template<typename ...Args>
    constexpr void set_uniform(GLenum type, std::string const& name, Args ...args);

    class Example {
    public:
        static void triangle(WinRender const& wh);
        static void square(WinRender const& wr);
    };

protected:
    GLuint program_id_;
    bool ready_;
    std::unordered_map<std::string, GLint> location_cache_;
};


template<typename... Args>
constexpr void Program::set_uniform(GLenum type, const std::string& name, Args... args) {
    switch (type) {
        case GL_FLOAT_VEC4:
            return glUniform4f(uniform_location(name), args...);
        default:
            break;
    }
    throw std::runtime_error(name + ": unrecognized/unimplemented uniform type");
}


#endif //FIRE_PROGRAM_HH
