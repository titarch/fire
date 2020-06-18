//
// Created by bparsy on 6/17/20.
//

#ifndef FIRE_SPAWNER_HH
#define FIRE_SPAWNER_HH


#include <vector>
#include "Particle.hh"
#include "../textures/Sprite.hh"

class Spawner {
public:
    using ptr = std::shared_ptr<Spawner>;
public:
    explicit Spawner(std::string const& texture_path, Vec const& pos, unsigned count);
    static Spawner::ptr make(std::string const& texture_path, Vec const& pos, unsigned count);
    Spawner(Spawner const&) = delete;
    Spawner(Spawner&&) = default;
    void step();
private:
    Texture::ptr texture_;
    Vec pos_;
    unsigned count_;
    std::vector<Particle> particles_;

    friend class WinRender;
};


#endif //FIRE_SPAWNER_HH
