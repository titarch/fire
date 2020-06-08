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

std::size_t IndexBuffer::count() const {
    return count_;
}

IndexBuffer::ptr IndexBuffer::create(const unsigned* indices, std::size_t size) {
    auto ib = std::make_unique<IndexBuffer>(size);
    glGenBuffers(1, &ib->id_);
    ib->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned), indices, GL_STATIC_DRAW);
    return ib;
}

IndexBuffer::ptr IndexBuffer::create(const std::vector<unsigned>& indices) {
    return create(indices.data(), indices.size());
}
