//
// Created by bparsy on 5/22/20.
//

#include "VertexBuffer.hh"

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id_);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::layout(const VertexBufferLayout& layout) {
    VertexBuffer::bind();
    std::size_t offset = 0u;
    auto const& els = layout.elements();
    for (auto i = 0u; i < els.size(); ++i) {
        auto const& el = els[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.stride(), reinterpret_cast<void*>(offset));
        offset += el.count * gl_sizeof(el.type);
    }
    stride_ = layout.stride();
    VertexBuffer::unbind();
}

std::size_t VertexBuffer::count() const {
    return size_ / stride_;
}