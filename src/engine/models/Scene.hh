//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_SCENE_HH
#define FIRE_SCENE_HH

#include <vector>
#include "../../utils/transform.hh"
#include "Shape.hh"
#include "../particles/Spawner.hh"
#include "../textures/CubeMap.hh"
#include "../textures/TileMap.hh"

enum class Dir {
    FORWARD,
    LEFT,
    BACK,
    RIGHT,
    UP,
    DOWN,
};

enum class Norm {
    UP,
    RIGHT,
};

class Scene {
public:
    Scene();

    Shape::ptr add_object(std::string const& path);
    Scene& add_shape(Shape::ptr& shape);
    Scene& add_spawner(Spawner::ptr& spawner);
    Scene& set_light_position(Vec const& position);
    Scene& set_perspective(float fov, float ratio, float near, float far);
    Scene& set_camera(Vec const& position, Vec const& direction);
    Scene& set_cubemap(std::string const& path);
    Scene& set_tilemap(std::string const& path);
    void use();
    void refresh_view() const;
    void update_spawners();

    [[nodiscard]] const Vec& position() const;
    [[nodiscard]] const Vec& direction() const;
    Scene& move(float amount, Vec const& direction);
    Scene& move(float amount, Dir direction);
    Scene& turn(float angle, Vec const& normal);
    Scene& turn(float angle, Norm normal);
    [[nodiscard]] const std::vector<Shape::ptr>& shapes() const;
    [[nodiscard]] const std::vector<Spawner::ptr>& spawners() const;
    [[nodiscard]] const CubeMap::ptr& cubemap() const;
    [[nodiscard]] const TileMap::ptr& tilemap() const;
    [[nodiscard]] Mat view() const;
private:
    std::vector<Shape::ptr> shapes_;
    std::vector<Spawner::ptr> spawners_;
    CubeMap::ptr cubemap_;
    TileMap::ptr tilemap_;
    Vec light_position_;
    Mat projection_;
    Vec position_, direction_;
    bool use_shapes{false}, use_spawner{false}, use_cubemap{false}, use_tilemap{false};
};


#endif //FIRE_SCENE_HH
