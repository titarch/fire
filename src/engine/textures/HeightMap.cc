//
// Created by bparsy on 1/27/21.
//

#include "HeightMap.hh"

HeightMap::HeightMap(unsigned int width, unsigned int height, unsigned long seed)
        : w_(width), h_(height), perlin_(seed), hm_(width * height) {
    generate(200.f, 5.f);
    generate(100.f, 2.f);
    generate(50.f, 1.f);
}

void HeightMap::generate(float scale, float amplitude) {
    for (auto y = 0u; y < h_; ++y) {
        for (auto x = 0u; x < w_; ++x) {
            const float sampleX = float(x) / scale;
            const float sampleY = float(y) / scale;
            hm_[y * w_ + x] += perlin_.noise2D(sampleX, sampleY) * amplitude - amplitude / 2.f;
        }
    }
}

auto HeightMap::width() const -> unsigned {
    return w_;
}

auto HeightMap::height() const -> unsigned {
    return h_;
}

auto HeightMap::map() const -> std::vector<float> const& {
    return hm_;
}

auto HeightMap::at(unsigned int x, unsigned int z) const -> float {
    if (x >= h_ || z >= w_)
        throw std::invalid_argument("HeightMap: Out of range!");
    return hm_[x * w_ + z];
}

auto HeightMap::normal(unsigned int x, unsigned int z) const -> Vec {
    if (x == 0) x = 1;
    if (z == 0) z = 1;
    if (x == h_ - 1) x = h_ - 2;
    if (z == w_ - 1) z = w_ - 2;
    const auto hl = at(x-1, z);
    const auto hr = at(x+1, z);
    const auto hd = at(x, z-1);
    const auto hu = at(x, z+1);
    Vec n(hl - hr, 2.f, hd - hu);
    return glm::normalize(n.vec());
}