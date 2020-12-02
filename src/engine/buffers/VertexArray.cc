//
// Created by bparsy on 5/22/20.
//

#include "VertexArray.hh"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

VertexArray::ptr VertexArray::create() {
    return std::make_unique<VertexArray>();
}

void VertexArray::bind() const {
    glBindVertexArray(id_);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::ssbo_base_index(GLuint index) const {
    if (!sb_)
        throw std::runtime_error("SSBO was not initialized in VertexArray");

    sb_->bind();
    sb_->base_index(index);
    sb_->unbind();
}
