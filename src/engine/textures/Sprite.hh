//
// Created by bparsy on 6/18/20.
//

#ifndef FIRE_SPRITE_HH
#define FIRE_SPRITE_HH


#include "Texture.hh"

class Sprite : public Texture {
public:
    explicit Sprite(std::string const& file_path);
    static ptr make(std::string const& file_path);
    void bind(uint8_t slot) override;
    void unbind() override;
protected:
    int width_, height_;
    unsigned char* local_buffer_;
    int bytes_per_pixels_;
};


#endif //FIRE_SPRITE_HH
