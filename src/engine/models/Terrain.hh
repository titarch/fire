//
// Created by bparsy on 1/27/21.
//

#ifndef FIRE_TERRAIN_HH
#define FIRE_TERRAIN_HH


#include "../textures/Texture.hh"
#include "../textures/HeightMap.hh"
#include "../Program.hh"
#include "../buffers/VertexArray.hh"

class Terrain : public Texture {
public:
    using ptr = std::shared_ptr<Terrain>;
public:
    explicit Terrain(const HeightMap& hm, float step);
    static ptr make(float step, unsigned int w, unsigned int h, unsigned long seed = 0);

    void update_vao();
    void bind(uint8_t slot) const override;
    void unbind() const override;
    [[nodiscard]] auto height_at(float x, float z) const -> float;

    static void init_program();
protected:
    float step_;
    HeightMap hm_;
    std::vector<float> vertices_;
    std::vector<unsigned> indices_;
    VertexArray::ptr va_;

    static Program::ptr program_;
public:
    friend class ClassicScene;

    friend class WinRender;
};


#endif //FIRE_TERRAIN_HH
