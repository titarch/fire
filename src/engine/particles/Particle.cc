//
// Created by bparsy on 6/17/20.
//

#include "Particle.hh"

Program::ptr Particle::program_;
VertexArray::ptr Particle::va_;

Particle::Particle() : pos_(), vel_(), color_(), alpha_(1.f), energy_((float) rand() / (float) RAND_MAX) {
    init_program();
    if (!va_) {
        static constexpr std::array square = {
                -0.5f, -0.5f, 0.f, 0.f,
                0.5f, -0.5f, 1.f, 0.f,
                0.5f, 0.5f, 1.f, 1.f,
                -0.5f, 0.5f, 0.f, 1.f
        };
        static constexpr std::array indices = {
                0u, 1u, 2u,
                2u, 3u, 0u
        };

        va_ = VertexArray::create();
        va_->add_data(
                square,
                VertexBufferLayout::Common::F2D()
                        .add_element<GL_FLOAT>(2)
        );
        va_->add_indices(indices);
    }
}

void Particle::init_program() {
    if (Particle::program_) return;
    program_ = Program::make_program("particle", "particle");
    program_->use();
}

void Particle::update_physics(float dt) {
    energy_ -= dt;
    if (energy_ <= 0.f) return;
    pos_ += vel_ * dt;
    alpha_ -= dt;
}

void Particle::respawn(Vec const& position) {
    if (energy_ > 0.f) return;
    float random_x = (float) ((rand() % 100) - 50) / 100.0f;
    float random_z = (float) ((rand() % 100) - 50) / 100.0f;
    float rColor = 0.5f + ((float) (rand() % 100) / 200.0f);
    pos_ = {position[0] + random_x, position[1], position[2] + random_z};
    color_ = {rColor, rColor / 3.f, 0};
    energy_ = 1.0f * (0.5f + ((float)rand() / (float)RAND_MAX) / 2.f);
    vel_ = {0, 2, 0};
    vel_ += pos_;
    alpha_ = 1.f;
}

void Particle::use() const {
    program_->set_uniform<GL_FLOAT_VEC4>("u_offset", pos_[0], pos_[1], pos_[2], 1.f);
    program_->set_uniform<GL_FLOAT_VEC4>("u_scale", 0.1f, 0.1f, 0.1f, 1.0f);
    program_->set_uniform<GL_FLOAT_VEC4>("u_color", color_[0], color_[1], color_[2], alpha_);
}

Program const& Particle::program() {
    return *program_;
}
