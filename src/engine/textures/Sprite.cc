//
// Created by bparsy on 6/18/20.
//
#define STB_IMAGE_IMPLEMENTATION

#include "Sprite.hh"
#include "../../utils/3rdparty/stb_image.h"

Sprite::Sprite(const std::string& file_path) : Texture(), width_(0), height_(0), local_buffer_(nullptr), bytes_per_pixels_(0) {
    // open file , get width & height
    stbi_set_flip_vertically_on_load(1);
    local_buffer_ = stbi_load(file_path.c_str(), &width_, &height_, &bytes_per_pixels_, 4);
    if (!local_buffer_) throw std::runtime_error(file_path + ": could not load texture image");

    glBindTexture(GL_TEXTURE_2D, render_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_);
    if (local_buffer_) stbi_image_free(local_buffer_);
}

Texture::ptr Sprite::make(const std::string& file_path) {
    return std::make_shared<Sprite>(file_path);
}

void Sprite::bind(uint8_t slot) const {
    Texture::bind(GL_TEXTURE_2D, slot);
}

void Sprite::unbind() const {
    Texture::unbind(GL_TEXTURE_2D);
}
