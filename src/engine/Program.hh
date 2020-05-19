//
// Created by bparsy on 5/18/20.
//

#ifndef FIRE_PROGRAM_HH
#define FIRE_PROGRAM_HH

#include <string>
#include <GL/glew.h>
#include <memory>

class WinHandler;

class Program {
public:
    using ptr = std::unique_ptr<Program>;

    Program();
    ~Program();
    static GLuint compile_shader(GLuint type, std::string const& src);
    static ptr make_program(std::string const& vertex_shader_fp, std::string const& fragment_shader_fp);
    [[nodiscard]] bool is_ready() const;
    void use() const;

    class Example {
    public:
        static void triangle(WinHandler const& wh);
        static void square(WinHandler const& wh);
    };

protected:
    GLuint program_id_;
    bool ready_;
};

#endif //FIRE_PROGRAM_HH
