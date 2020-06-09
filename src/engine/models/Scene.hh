//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_SCENE_HH
#define FIRE_SCENE_HH

#include <vector>
#include "../../utils/transform.hh"
#include "Shape.hh"

class Scene {
public:
    Scene() : shapes_(), light_position_(), projection_(), position_(), direction_() {}

    Shape::ptr add_object(std::string const& path);
    Scene& add_shape(Shape::ptr& shape);
    Scene& set_light_position(Vec const& position);
    Scene& set_perspective(float fov, float ratio, float near, float far);
    Scene& set_camera(Vec const& position, Vec const& direction);
    void use();
    void refresh_view() const;

    Vec& position();
    Vec& direction();
    [[nodiscard]] const std::vector<Shape::ptr>& shapes() const;
    [[nodiscard]] Mat view() const;
private:
    std::vector<Shape::ptr> shapes_;
    Vec light_position_;
    Mat projection_;
    Vec position_, direction_;
};


#endif //FIRE_SCENE_HH
