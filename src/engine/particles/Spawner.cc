//
// Created by bparsy on 6/17/20.
//

#include <ctime>
#include "Spawner.hh"

Spawner::Spawner(std::string const& texture_path, Vec const& pos, unsigned count)
        : texture_(Sprite::make(texture_path)), pos_(pos), count_(count), particles_(count) {}

Spawner::ptr Spawner::make(const std::string& texture_path, const Vec& pos, unsigned int count) {
    return std::make_shared<Spawner>(texture_path, pos, count);
}

void Spawner::step() {
    for (auto& particle : particles_) {
        particle.respawn(pos_);
        particle.update_physics(0.03f);
    }
}
