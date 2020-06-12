//
// Created by bparsy on 6/8/20.
//

#ifndef FIRE_MATERIAL_HH
#define FIRE_MATERIAL_HH

#include "../../utils/transform.hh"
#include <memory>

namespace tinyobj {
    class material_t;
}

class Material {
public:
    using ptr = std::shared_ptr<Material>;
public:
    Material(const Vec& ka, const Vec& kd, const Vec& ks, float ns) : ka(ka), kd(kd), ks(ks), ns(ns) {}

    [[nodiscard]] Material::ptr clone() const;
    static Material::ptr from_mtl(tinyobj::material_t const& mtl);
    void use() const;
public:
    Vec ka, kd, ks;
    float ns;

    static const Material gray;
};


#endif //FIRE_MATERIAL_HH
