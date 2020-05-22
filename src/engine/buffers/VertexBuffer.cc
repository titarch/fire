//
// Created by bparsy on 5/22/20.
//

#include "VertexBuffer.hh"

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id_);
}

VertexBuffer& VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

VertexBuffer& VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}