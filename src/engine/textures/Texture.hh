#ifndef FIRE_TEXTURE_HH
#define FIRE_TEXTURE_HH

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>

class Texture {
public:
    using ptr = std::shared_ptr<Texture>;
public :
    explicit Texture(const std::string&);
    static ptr make(std::string const& path);
    Texture(Texture const&) = delete;
    Texture(Texture&&) = default;
    ~Texture();
    // can add slot as param
    void bind();
    void unbind();
private :
    std::string file_path_;
    int width_;
    int height_;
    unsigned char* local_buffer_;
    int bytes_per_pixels_;
    GLuint render_id_;
};

#endif // FIRE_TEXTURE_HH
