//
// Created by bparsy on 6/17/20.
//

#ifndef FIRE_PARTICLE_HH
#define FIRE_PARTICLE_HH


#include "../../utils/transform.hh"
#include "../models/Material.hh"
#include "../Program.hh"
#include "../textures/texture.hh"
#include "../buffers/VertexArray.hh"

class Particle {
public:
    Particle();
    static void init_program();
    void update_physics(float dt);
    void respawn(Vec const& position);
    void use() const;
    static Program const& program();
private:
    Vec pos_, vel_, rand_vel;
    Vec color_;
    float alpha_;
    float energy_;
    static Program::ptr program_;
    static VertexArray::ptr va_;

    friend class Spawner;

    friend class WinRender;
};


#endif //FIRE_PARTICLE_HH
