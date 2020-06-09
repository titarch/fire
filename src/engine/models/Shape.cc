//
// Created by bparsy on 6/9/20.
//

#include <utility>
#include "Shape.hh"
#include "Mesh.hh"

Shape::Shape() : meshes_() {}

Shape::Shape(std::vector<Mesh> meshes) : meshes_(std::move(meshes)) {}

Shape& Shape::add_mesh(Mesh mesh) {
    meshes_.push_back(std::move(mesh));
    return *this;
}

std::vector<Mesh> const& Shape::meshes() const {
    return meshes_;
}

Shape& Shape::reset() {
    translation({});
    rotation({});
    scale({});
    center({});
    return *this;
}

Shape& Shape::translate(const Vec& v) {
    for (auto& mesh : meshes_)
        mesh.trans.translate(v);
    return *this;
}

Shape& Shape::translation(const Mat& m) {
    for (auto& mesh : meshes_)
        mesh.trans = m;
    return *this;
}

Shape& Shape::rotate(float angle, const Vec& dir) {
    for (auto& mesh : meshes_)
        mesh.rot.rotate(angle, dir);
    return *this;
}

Shape& Shape::rotation(const Mat& m) {
    for (auto& mesh : meshes_)
        mesh.rot = m;
    return *this;
}

Shape& Shape::rescale(const Vec& v) {
    for (auto& mesh : meshes_)
        mesh.scale.rescale(v);
    return *this;
}

Shape& Shape::scale(const Mat& m) {
    for (auto& mesh : meshes_)
        mesh.scale = m;
    return *this;
}

Shape& Shape::recenter(const Vec& v) {
    for (auto& mesh : meshes_)
        mesh.center.translate(v);
    return *this;
}

Shape& Shape::center(const Mat& m) {
    for (auto& mesh : meshes_)
        mesh.center = m;
    return *this;
}
