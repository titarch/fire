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
    static GLuint create_2D_buffer(std::array<float, D> const& data);

protected:
    inline static std::vector<GLuint> buffers_{};
};

template<std::size_t D>
GLuint BufHandler::create_2D_buffer(const std::array<float, D>& data) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    BufHandler::buffers_.push_back(buffer);
    return buffer;
}


#endif //FIRE_BUFHANDLER_HH
