//
// Created by bparsy on 1/27/21.
//

#ifndef FIRE_HEIGHTMAP_HH
#define FIRE_HEIGHTMAP_HH

#include "../../utils/transform.hh"
#include "../../utils/3rdparty/PerlinNoise.hpp"

class HeightMap {
public:
    HeightMap(unsigned int width, unsigned int height, unsigned long seed = 0);

    [[nodiscard]] auto width() const -> unsigned ;
    [[nodiscard]] auto height() const -> unsigned ;
    [[nodiscard]] auto map() const -> std::vector<float> const&;
    [[nodiscard]] auto at(unsigned x, unsigned z) const -> float;
    [[nodiscard]] auto normal(unsigned x, unsigned z) const -> Vec;
private:
    void generate(float scale, float amplitude);

    unsigned w_, h_;
    siv::PerlinNoise perlin_;
    std::vector<float> hm_;
};


#endif //FIRE_HEIGHTMAP_HH
