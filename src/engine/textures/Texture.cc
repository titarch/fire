#include "Texture.hh"

Texture::Texture() {
    glGenTextures(1, &render_id_);
}

Texture::~Texture() {
    glDeleteTextures(1, &render_id_);
}

void Texture::bind(GLenum type, uint8_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type, render_id_);
}

void Texture::unbind(GLenum type) {
    glBindTexture(type, 0);
}

