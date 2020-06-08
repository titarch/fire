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
