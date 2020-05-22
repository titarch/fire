//
// Created by bparsy on 5/22/20.
//

#include "IndexBuffer.hh"

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id_);
}

IndexBuffer& IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    return *this;
}

IndexBuffer& IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return *this;
}
