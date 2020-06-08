//
// Created by bparsy on 6/8/20.
//

#ifndef FIRE_MATERIAL_HH
#define FIRE_MATERIAL_HH

#include "../../utils/transform.hh"

namespace tinyobj {
    class material_t;
}

class Material {
public:
    static Material from_mtl(tinyobj::material_t const& mtl);
    void use() const;
public:
    Vec ka, kd, ks;
    float ns;
};


#endif //FIRE_MATERIAL_HH
