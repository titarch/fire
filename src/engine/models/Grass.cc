//
// Created by bparsy on 1/28/21.
//

#include "Grass.hh"

Program::ptr Grass::program_;

Grass::Grass(const std::vector<float>& vertices) : va_() {
    va_ = VertexArray::create();
    va_->add_vertex_data(vertices, VertexBufferLayout::Common::F3D());
    init_program();
}

Grass::ptr Grass::make(const std::vector<float>& vertices) {
    return std::make_shared<Grass>(vertices);
}

void Grass::init_program() {
    if (!Grass::program_)
        Grass::program_ = Program::make_program("grass", "grass", "grass");
}
