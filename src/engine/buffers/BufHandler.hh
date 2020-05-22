//
// Created by bparsy on 5/17/20.
//

#ifndef FIRE_BUFHANDLER_HH
#define FIRE_BUFHANDLER_HH

#include <GL/glew.h>
#include <vector>
#include <array>
#include "VertexBuffer.hh"
#include "IndexBuffer.hh"
#include "VertexArray.hh"

class BufHandler {
public:
    BufHandler() = delete;

    static VertexArray make_vao() {
        return VertexArray::create();
    }

    static VertexBufferLayout make_layout() {
        return VertexBufferLayout();
    }

    template<typename T, std::size_t D>
    static VertexBuffer::ptr make_vbo(std::array<T, D> const& data) {
        return VertexBuffer::create(data);
    }

    template<std::size_t D>
    static IndexBuffer make_ibo(std::array<unsigned, D> const& data) {
        return IndexBuffer::create(data);
    }
};


#endif //FIRE_BUFHANDLER_HH
