//
// Created by bparsy on 11/30/20.
//

#include "StorageBuffer.hh"

StorageBuffer::~StorageBuffer() {
    glDeleteBuffers(1, &id_);
}

void StorageBuffer::bind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id_);
}

void StorageBuffer::unbind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void StorageBuffer::vb_bind() const {
    VertexBuffer::bind();
}

void StorageBuffer::vb_unbind() const {
    VertexBuffer::unbind();
}
