//
// Created by bparsy on 5/22/20.
//

#include "VertexArray.hh"

VertexArray VertexArray::create() {
    VertexArray va{};
    glGenVertexArrays(1, &va.id_);
    return va;
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind() const {
    glBindVertexArray(id_);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

VertexArray& VertexArray::add_buffer(VertexBuffer const& vb, VertexBufferLayout const& layout) {
    bind();
    vb.bind();
    std::size_t offset = 0u;
    auto const& els = layout.elements();
    for (auto i = 0u; i < els.size(); ++i) {
        auto const& el = els[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.stride(), reinterpret_cast<void*>(offset));
        offset += el.count * gl_sizeof(el.type);
    }
    return *this;
}
