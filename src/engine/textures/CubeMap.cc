//
// Created by bparsy on 6/18/20.
//

#include "CubeMap.hh"
#include "../../utils/3rdparty/stb_image.h"

static constexpr float cube_size = 500.f;

static constexpr std::array cube = {
        -cube_size, cube_size, -cube_size,
        -cube_size, -cube_size, -cube_size,
        cube_size, -cube_size, -cube_size,
        cube_size, -cube_size, -cube_size,
        cube_size, cube_size, -cube_size,
        -cube_size, cube_size, -cube_size,

        -cube_size, -cube_size, cube_size,
        -cube_size, -cube_size, -cube_size,
        -cube_size, cube_size, -cube_size,
        -cube_size, cube_size, -cube_size,
        -cube_size, cube_size, cube_size,
        -cube_size, -cube_size, cube_size,

        cube_size, -cube_size, -cube_size,
        cube_size, -cube_size, cube_size,
        cube_size, cube_size, cube_size,
        cube_size, cube_size, cube_size,
        cube_size, cube_size, -cube_size,
        cube_size, -cube_size, -cube_size,

        -cube_size, -cube_size, cube_size,
        -cube_size, cube_size, cube_size,
        cube_size, cube_size, cube_size,
        cube_size, cube_size, cube_size,
        cube_size, -cube_size, cube_size,
        -cube_size, -cube_size, cube_size,

        -cube_size, cube_size, -cube_size,
        cube_size, cube_size, -cube_size,
        cube_size, cube_size, cube_size,
        cube_size, cube_size, cube_size,
        -cube_size, cube_size, cube_size,
        -cube_size, cube_size, -cube_size,

        -cube_size, -cube_size, -cube_size,
        -cube_size, -cube_size, cube_size,
        cube_size, -cube_size, -cube_size,
        cube_size, -cube_size, -cube_size,
        -cube_size, -cube_size, cube_size,
        cube_size, -cube_size, cube_size
};


Program::ptr CubeMap::program_;
VertexArray::ptr CubeMap::va_;

CubeMap::CubeMap(const std::string& path) : Texture() {
    stbi_set_flip_vertically_on_load(1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, render_id_);
    constexpr static std::array faces_str = {"right", "left", "bottom", "top", "front", "back"};

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (auto i = 0u; i < faces_str.size(); ++i) {
        int w, h, bpp;
        auto file_path = path + faces_str[i] + ".png";
        unsigned char* buffer = stbi_load(file_path.c_str(), &w, &h, &bpp, 4);
        if (!buffer) throw std::runtime_error(file_path + ": could not load texture image");
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        stbi_image_free(buffer);
    }
    init_graphics();
}

void CubeMap::init_graphics() {
    if (!CubeMap::program_)
        program_ = Program::make_program("cubemap", "cubemap");
    if (!va_) {
        va_ = VertexArray::create();
        va_->add_vertex_data(cube, VertexBufferLayout::Common::F3D());
    }
}

Texture::ptr CubeMap::make(const std::string& path) {
    return std::make_shared<CubeMap>(path);
}

void CubeMap::bind(uint8_t slot) const {
    Texture::bind(GL_TEXTURE_CUBE_MAP, slot);
}

void CubeMap::unbind() const {
    Texture::unbind(GL_TEXTURE_CUBE_MAP);
}
