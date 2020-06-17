//
// Created by bparsy on 6/17/20.
//

#include "Particle.hh"

Program::ptr Particle::program_;
VertexArray::ptr Particle::va_;

Particle::Particle() : pos_(), vel_(), color_(), energy_() {
    if (!program_) {
        program_ = Program::make_program("particle", "particle");
        program_->use();
        auto proj = Mat::perspective(45.f, 16.f/9.f, 0.01f, 50.f);
        auto view = Mat::camera({0, 0, 10}, Vec::zero(), Vec::up());
        auto model = proj * view;
        program_->set_uniform<GL_FLOAT_MAT4>("u_projection", model.data());
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
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

void Particle::update_physics(float dt) {
    energy_ -= dt * ((float)rand() / (float)RAND_MAX);
    if (energy_ <= 0.f) return;
    pos_ += vel_ * dt;
}

void Particle::respawn(Vec const& position) {
    if (energy_ > 0.f) return;
    float random = (float) ((rand() % 100) - 50) / 100.0f;
    float rColor = 0.5f + ((float) (rand() % 100) / 200.0f);
    pos_ = position + random;
    color_ = {rColor, rColor / 3.f, 0};
    energy_ = 1.0f;
    vel_ = {0, 1, 0};
}

void Particle::use() const {
    program_->set_uniform<GL_FLOAT_VEC4>("u_offset", pos_[0], pos_[1], pos_[2], 1.f);
    program_->set_uniform<GL_FLOAT_VEC4>("u_scale", 0.1f, 0.1f, 0.1f, 1.0f);
    program_->set_uniform<GL_FLOAT_VEC4>("u_color", color_[0], color_[1], color_[2], 1.f);
}
