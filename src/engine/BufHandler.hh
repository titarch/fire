//
// Created by bparsy on 5/17/20.
//

#ifndef FIRE_BUFHANDLER_HH
#define FIRE_BUFHANDLER_HH

#include <GL/glew.h>
#include <vector>
#include <array>

class BufHandler {
public:
    BufHandler() = delete;

    template<std::size_t D>
    static GLuint create_vbo(std::array<float, D> const& data, GLint dim);
    template<std::size_t D>
    static GLuint create_ibo(std::array<unsigned, D> const& data);

protected:
    inline static std::vector<GLuint> buffers_{};
};

template<std::size_t D>
GLuint BufHandler::create_vbo(const std::array<float, D>& data, GLint dim) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, D * sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    BufHandler::buffers_.push_back(buffer);
    return buffer;
}

template<std::size_t D>
GLuint BufHandler::create_ibo(const std::array<unsigned int, D>& data) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, D * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
    return buffer;
}


#endif //FIRE_BUFHANDLER_HH
