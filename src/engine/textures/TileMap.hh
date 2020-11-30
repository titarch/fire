//
// Created by bparsy on 6/19/20.
//

#ifndef FIRE_TILEMAP_HH
#define FIRE_TILEMAP_HH


#include "Texture.hh"
#include "../Program.hh"
#include "../buffers/VertexArray.hh"

class TileMap : public Texture {
public:
    explicit TileMap(std::string const& file_path);
    static ptr make(std::string const& file_path);
    void bind(uint8_t slot) const override;
    void unbind() const override;
private:
    int width_, height_;

    static Program::ptr program_;
    static VertexArray::ptr va_;

    static void init_graphics();

    friend class ClassicScene;

    friend class WinRender;
};


#endif //FIRE_TILEMAP_HH
