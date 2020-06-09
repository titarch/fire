//
// Created by bparsy on 6/9/20.
//

#include "Scene.hh"

Shape::ptr Scene::add_object(const std::string& path) {
    auto shape = Shape::load_obj(path);
    add_shape(shape);
    return shape;
}

Scene& Scene::add_shape(Shape::ptr& shape) {
    shapes_.push_back(shape);
    return *this;
}

Scene& Scene::set_light_position(Vec const& position) {
    light_position_ = position;
    return *this;
}

Scene& Scene::set_perspective(float fov, float ratio, float near, float far) {
    projection_ = Mat::perspective(fov, ratio, near, far);
    return *this;
}

Scene& Scene::set_camera(const Vec& posision, const Vec& direction) {
    position_ = posision;
    direction_ = direction;
    return *this;
}

void Scene::use() {
    Mesh::program().use();
    Mesh::program().set_uniform<GL_FLOAT_VEC4>("u_light_position", light_position_[0], light_position_[1],
                                               light_position_[2], 1.f);
    Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_proj", projection_.data());
    Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_view", view().data());
}

void Scene::refresh_view() const {
    Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_view", view().data());
}

const std::vector<Shape::ptr>& Scene::shapes() const {
    return shapes_;
}

Vec& Scene::position() {
    return position_;
}

Vec & Scene::direction() {
    return direction_;
}

Mat Scene::view() const {
    return Mat::camera(position_, position_ + direction_, Vec::up());
}
