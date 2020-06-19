//
// Created by bparsy on 6/19/20.
//

#include "TileMap.hh"
#include "../../utils/3rdparty/stb_image.h"

Program::ptr TileMap::program_;
VertexArray::ptr TileMap::va_;

static constexpr float square_size = 500.f;

static constexpr std::array square = {
        -square_size, -square_size,
        square_size, -square_size,
        square_size, square_size,
        -square_size, square_size
};

static constexpr std::array indices = {
        0u, 1u, 2u,
        2u, 3u, 0u
};

TileMap::TileMap(const std::string& file_path) : Texture(), width_(0), height_(0) {
    stbi_set_flip_vertically_on_load(1);
    int bpp;
    unsigned char* buffer = stbi_load(file_path.c_str(), &width_, &height_, &bpp, 4);
    if (!buffer) throw std::runtime_error(file_path + ": could not load texture image");

    glBindTexture(GL_TEXTURE_2D, render_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    stbi_image_free(buffer);
    init_graphics();
}

void TileMap::init_graphics() {
    if (!TileMap::program_)
        program_ = Program::make_program("tilemap", "tilemap");
    if (!va_) {
        va_ = VertexArray::create();
        va_->add_data(square, VertexBufferLayout::Common::F2D());
        va_->add_indices(indices);
    }
}

Texture::ptr TileMap::make(const std::string& file_path) {
    return std::make_shared<TileMap>(file_path);
}

void TileMap::bind(uint8_t slot) const {
    Texture::bind(GL_TEXTURE_2D, slot);
}

void TileMap::unbind() const {
    Texture::unbind(GL_TEXTURE_2D);
}
