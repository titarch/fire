//
// Created by bparsy on 6/8/20.
//

#include "Mesh.hh"

Program::ptr Mesh::program_;

void Mesh::init_program() {
    if (!Mesh::program_) {
        Mesh::program_ = Program::make_program("mesh", "mesh");
        glEnable(GL_DEPTH_TEST);
    }
}

const Program& Mesh::program() {
    init_program();
    return *program_;
}

Mesh::Mesh(std::string name) : name_(std::move(name)), vertices_(), indices_(), material_(), va_(), trans(), rot(),
                               center(), scale() {}

Mesh::Mesh(std::string name, std::vector<float> vertices, std::vector<unsigned int> indices, const Material& material) :
        name_(std::move(name)), vertices_(std::move(vertices)), indices_(std::move(indices)), material_(material),
        va_(), trans(), rot(), center(), scale() {
    update_vao();
    init_program();
}

void Mesh::update_vao() {
    if (!va_) va_ = VertexArray::create();
    va_->add_data(vertices_, VertexBufferLayout::Common::F3DN());
    va_->add_indices(indices_);
}

void Mesh::preload() const {
    program_->use();
    material_.use();

    program_->set_uniform<GL_FLOAT_MAT4>("u_trans", trans.data());
    program_->set_uniform<GL_FLOAT_MAT4>("u_rot", rot.data());
    program_->set_uniform<GL_FLOAT_MAT4>("u_center", center.data());
    program_->set_uniform<GL_FLOAT_MAT4>("u_scale", scale.data());

    va_->bind();
}

