#ifndef FIRE_TEXTURE_HH
#define FIRE_TEXTURE_HH

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <memory>

class Texture {
public:
    using ptr = std::shared_ptr<Texture>;
public:
    Texture();
    Texture(Texture const&) = delete;
    Texture(Texture&&) = default;
    ~Texture();
    virtual void bind(uint8_t slot) = 0;
    virtual void unbind() = 0;
protected:
    void bind(GLenum type, uint8_t slot);
    void unbind(GLenum type);

    GLuint render_id_;
};

#endif // FIRE_TEXTURE_HH
