//
// Created by bparsy on 6/9/20.
//

#include <utility>
#include <iostream>
#include "Shape.hh"
#include "../../utils/3rdparty/tiny_obj_loader.h"

Shape::Shape() : meshes_() {}

Shape::Shape(std::vector<Mesh> meshes) : meshes_(std::move(meshes)) {}

Shape::ptr Shape::clone(bool keep_materials) const {
    auto copy = std::make_shared<Shape>();
    std::transform(meshes_.cbegin(), meshes_.cend(), std::back_inserter(copy->meshes_),
                   [](Mesh const& mesh) { return mesh.clone(); });

    if (keep_materials) {
        copy->materials_ = materials_;
        return copy;
    }

    std::transform(materials_.cbegin(), materials_.cend(), std::back_inserter(copy->materials_),
                   [](Material::ptr const& m) { return m->clone(); });
    std::for_each(copy->meshes_.begin(), copy->meshes_.end(),
                  [&copy](Mesh& m) { if (m.material_id_ != -1) m.material_ = copy->materials_[m.material_id_].get(); });
    return copy;
}

Shape::ptr Shape::load_obj(const std::string& path) {
    Mesh::init_program();

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
    if (!warn.empty())
        std::cerr << warn << std::endl;
    if (!err.empty())
        std::cerr << err << std::endl;
    if (!ret)
        throw std::runtime_error(path + ": failed to parse .obj");

    auto s = std::make_unique<Shape>();

    for (auto const& material : materials)
        s->materials_.push_back(Material::from_mtl(material));

    for (auto const& shape : shapes) {
        Mesh mesh(shape.name);
        size_t index_offset = 0;// indent offset
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            unsigned num_vertices = shape.mesh.num_face_vertices[f];
            for (size_t v = 0; v < num_vertices; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                for (auto i = 0u; i < 3; ++i)
                    mesh.vertices_.push_back(attrib.vertices[3 * idx.vertex_index + i]);
                for (auto i = 0u; i < 3; ++i)
                    mesh.vertices_.push_back(attrib.normals[3 * idx.normal_index + i]);
            }
            index_offset += num_vertices;
        }
        auto mat_id = shape.mesh.material_ids[0];
        mesh.material_ = mat_id == -1 ? &Material::gray : s->materials_[mat_id].get();
        mesh.material_id_ = mat_id;
        mesh.update_vao();
        s->add_mesh(std::move(mesh));
    }
    return s;
}

Shape& Shape::add_mesh(Mesh mesh) {
    meshes_.push_back(std::move(mesh));
    return *this;
}

std::vector<Mesh> const& Shape::meshes() const {
    return meshes_;
}

std::vector<Material::ptr>& Shape::materials() {
    return materials_;
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
