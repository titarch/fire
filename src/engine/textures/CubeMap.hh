//
// Created by bparsy on 6/18/20.
//

#ifndef FIRE_CUBEMAP_HH
#define FIRE_CUBEMAP_HH


#include "Texture.hh"
#include "../Program.hh"
#include "../buffers/VertexArray.hh"

class CubeMap : public Texture {
public:
    explicit CubeMap(std::string const& path);
    CubeMap(CubeMap const&) = delete;
    CubeMap(CubeMap&&) = default;
    static Texture::ptr make(std::string const& path);
    void bind(uint8_t slot) const override;
    void unbind() const override;
private:
    static Program::ptr program_;
    static VertexArray::ptr va_;

    static void init_graphics();

    friend class ClassicScene;

    friend class WinRender;
};


#endif //FIRE_CUBEMAP_HH
