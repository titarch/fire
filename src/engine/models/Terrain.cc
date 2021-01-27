//
// Created by bparsy on 1/27/21.
//

#include "Terrain.hh"

Program::ptr Terrain::program_;

Terrain::Terrain(const HeightMap& hm) : vertices_() {
    const auto w = hm.width();
    const auto h = hm.height();
    vertices_.reserve(w * h * 6);

    for (auto x = 0u; x < h; ++x) {
        for (auto z = 0u; z < w; ++z) {
            const auto y = hm.at(x, z);
            vertices_.push_back(x);
            vertices_.push_back(y);
            vertices_.push_back(z);

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

//    for (auto e : indices_) {
//        printf("(%u %u) ", e / w, e % w);
//    }
//    printf("\n");

    update_vao();
    init_program();
}

Terrain::ptr Terrain::make(unsigned int w, unsigned int h, unsigned long seed) {
    HeightMap hm(w, h, seed);
    return std::make_shared<Terrain>(hm);
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
