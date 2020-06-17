#define STB_IMAGE_IMPLEMENTATION
#include "../../utils/stb_image.h"
#include "../buffers/VertexBuffer.hh"
#include "texture.hh"


Texture::Texture(const std::string& file_path)
: file_path_(file_path), width_(0), height_(0), local_buffer_(nullptr), bytes_per_pixels_(0), render_id_(0)
{
    // open file , get width & height
    stbi_set_flip_vertically_on_load(1);
    local_buffer_ = stbi_load(file_path.c_str(), &width_, &height_, &bytes_per_pixels_, 4);
    
    glGenTextures(1, &render_id_);
    glBindTexture(GL_TEXTURE_2D, render_id_);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render_id_);

}

Texture::~Texture()
{
    glDeleteTextures(1, &render_id_);
}
