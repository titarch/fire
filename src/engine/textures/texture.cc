#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"
#include "buffers/VertexBuffer.hh"
#include "texture.hh"


Texture::Texture(std::string file_path)
: file_path(file_path), width(0), height(0), local_buffer(nullptr), bytes_per_pixels(0), render_id(0)
{
    // open file , get width & height
    //stbi_set_flip_vertically_on_load(1);
    //local_buffer = stbi_load(file_path.c_str(), &width, &height, &bytes_per_pixels, 4);
    
    glGenTextures(1, &render_id);
    glBindTexture(GL_TEXTURE_2D, render_id);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, render_id);

}

Texture::~Texture()
{
    glDeleteTextures(1, &render_id);
}
