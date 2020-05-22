//
// Created by bparsy on 5/22/20.
//

#include "IndexBuffer.hh"

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id_);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
