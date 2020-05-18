//
// Created by bparsy on 5/18/20.
//

#ifndef FIRE_PROGRAM_HH
#define FIRE_PROGRAM_HH

#include <string>
#include <GL/glew.h>
#include <memory>

class Program {
public:
    Program();
    ~Program();
    static GLuint compile_shader(GLuint type, std::string const& src);
    static std::unique_ptr<Program>
    make_program(std::string const& vertex_shader_fp, std::string const& fragment_shader_fp);
    bool is_ready();
    void use();
protected:
    GLuint program_id_;
    bool ready_;
};

using program_ptr = std::unique_ptr<Program>;

#endif //FIRE_PROGRAM_HH
