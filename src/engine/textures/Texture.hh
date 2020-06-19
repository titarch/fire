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
    virtual void bind(uint8_t slot) const = 0;
    virtual void unbind() const = 0;
protected:
    void bind(GLenum type, uint8_t slot) const;
    void unbind(GLenum type) const;

    GLuint render_id_;
};

#endif // FIRE_TEXTURE_HH
