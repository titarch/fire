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
