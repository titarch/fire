//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_SCENE_HH
#define FIRE_SCENE_HH

#include <vector>
#include "../../utils/transform.hh"
#include "Shape.hh"
#include "../particles/Spawner.hh"

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
    Scene() : shapes_(), light_position_(), projection_(), position_(), direction_() {}

    Shape::ptr add_object(std::string const& path);
    Scene& add_shape(Shape::ptr& shape);
    Scene& add_spawner(Spawner::ptr& spawner);
    Scene& set_light_position(Vec const& position);
    Scene& set_perspective(float fov, float ratio, float near, float far);
    Scene& set_camera(Vec const& position, Vec const& direction);
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
    [[nodiscard]] Mat view() const;
private:
    std::vector<Shape::ptr> shapes_;
    std::vector<Spawner::ptr> spawners_;
    Vec light_position_;
    Mat projection_;
    Vec position_, direction_;
};


#endif //FIRE_SCENE_HH
