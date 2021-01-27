//
// Created by bparsy on 1/27/21.
//

#ifndef FIRE_TERRAIN_HH
#define FIRE_TERRAIN_HH


#include "../textures/HeightMap.hh"
#include "../Program.hh"
#include "../buffers/VertexArray.hh"

class Terrain {
public:
    using ptr = std::shared_ptr<Terrain>;
public:
    explicit Terrain(HeightMap const& hm);
    static Terrain::ptr make(unsigned int w, unsigned int h, unsigned long seed = 0);

    void update_vao();

    static void init_program();
protected:
    std::vector<float> vertices_;
    std::vector<unsigned> indices_;
    VertexArray::ptr va_;

    static Program::ptr program_;
public:
    friend class ClassicScene;

    friend class WinRender;
};


#endif //FIRE_TERRAIN_HH
