//
// Created by bparsy on 1/27/21.
//

#include "Terrain.hh"
#include "../../utils/3rdparty/stb_image.h"

Program::ptr Terrain::program_;

Terrain::Terrain(const HeightMap& hm, float step) :
        Texture(),
        step_(step), hm_(hm), vertices_(), indices_(), va_() {


    int img_w, img_h;
    const std::string& file_path("../res/assets/ground.jpg");
    stbi_set_flip_vertically_on_load(1);
    int bpp;
    unsigned char* buffer = stbi_load(file_path.c_str(), &img_w, &img_h, &bpp, 4);
    if (!buffer) throw std::runtime_error(file_path + ": could not load texture image");

    glBindTexture(GL_TEXTURE_2D, render_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    stbi_image_free(buffer);

    const long w = hm.width();
    const long h = hm.height();
    const long half_w = w / 2;
    const long half_h = h / 2;
    vertices_.reserve(w * h * 6);

    for (auto x = 0u; x < h; ++x) {
        for (auto z = 0u; z < w; ++z) {
            const auto y = hm.at(x, z);
            vertices_.push_back(float(x - half_h) * step);
            vertices_.push_back(y);
            vertices_.push_back(float(z - half_w) * step);

            const auto n = hm.normal(x, z);
            vertices_.push_back(n[0]);
            vertices_.push_back(n[1]);
            vertices_.push_back(n[2]);
        }
    }

    for (auto row = 0u; row < h - 1; row++) {
        if ((row & 1) == 0) { // even rows
            for (auto col = 0u; col < w; col++) {
                indices_.push_back(col + row * w);
                indices_.push_back(col + (row + 1) * w);
            }
        } else { // odd rows
            for (long col = long(w) - 1; col > 0; col--) {
                indices_.push_back(col + (row + 1) * w);
                indices_.push_back(col - 1 + row * w);
            }
        }
    }

    update_vao();
    init_program();
}

Terrain::ptr Terrain::make(float step, unsigned int w, unsigned int h, unsigned long seed) {
    HeightMap hm(w, h, seed);
    return std::make_shared<Terrain>(hm, step);
}

void Terrain::init_program() {
    if (Terrain::program_)return;
    Terrain::program_ = Program::make_program("terrain", "terrain");
}

void Terrain::update_vao() {
    if (!va_) va_ = VertexArray::create();
    va_->add_vertex_data(vertices_, VertexBufferLayout::Common::F3DN());
    va_->add_indices(indices_);
}

void Terrain::bind(uint8_t slot) const {
    Texture::bind(GL_TEXTURE_2D, slot);
}

void Terrain::unbind() const {
    Texture::unbind(GL_TEXTURE_2D);
}

auto Terrain::height_at(float x, float z) const -> float {
    const auto w = hm_.width();
    const auto h = hm_.height();
    auto mx = long(x / step_) + h / 2;
    auto mz = long(z / step_) + w / 2;
    return hm_.at(mx, mz);
}