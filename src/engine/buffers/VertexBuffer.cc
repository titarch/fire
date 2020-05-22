//
// Created by bparsy on 5/22/20.
//

#include "VertexBuffer.hh"

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id_);
}

VertexBuffer& VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    return *this;
}

VertexBuffer& VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return *this;
}