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

Scene& Scene::add_spawner(Spawner::ptr& spawner) {
    spawners_.push_back(spawner);
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

void Scene::update_spawners() {
    for (auto& spawner : spawners_)
        spawner->step();
}

const std::vector<Shape::ptr>& Scene::shapes() const {
    return shapes_;
}

const std::vector<Spawner::ptr> & Scene::spawners() const {
    return spawners_;
}

const Vec& Scene::position() const {
    return position_;
}

const Vec& Scene::direction() const {
    return direction_;
}

Scene& Scene::move(float amount, const Vec& direction) {
    position_ += direction * amount;
    refresh_view();
    return *this;
}

Scene& Scene::move(float amount, Dir direction) {
    switch (direction) {
        case Dir::FORWARD:
            return move(amount, direction_);
        case Dir::LEFT:
            return move(amount, Vec::up() ^ direction_);
        case Dir::BACK:
            return move(-amount, direction_);
        case Dir::RIGHT:
            return move(-amount, Vec::up() ^ direction_);
        case Dir::UP:
            return move(amount, Vec::up());
        case Dir::DOWN:
            return move(-amount, Vec::up());
    }
    return *this;
}

Scene& Scene::turn(float angle, const Vec& normal) {
    direction_.rotate(angle, normal);
    refresh_view();
    return *this;
}

Scene& Scene::turn(float angle, Norm normal) {
    switch (normal) {
        case Norm::UP:
            return turn(angle, Vec::up());
        case Norm::RIGHT:
            return turn(angle, Vec::up() ^ direction_);
    }
    return *this;
}

Mat Scene::view() const {
    return Mat::camera(position_, position_ + direction_, Vec::up());
}
