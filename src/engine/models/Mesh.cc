//
// Created by bparsy on 6/8/20.
//

#include <iostream>
#include "Mesh.hh"
#include "../../utils/3rdparty/tiny_obj_loader.h"

Program::ptr Mesh::program_;

void Mesh::init_program() {
    if (!Mesh::program_) Mesh::program_ = Program::make_program("mesh", "mesh");
}

Mesh::Mesh(std::string name, std::vector<float> vertices, std::vector<unsigned int> indices, const Material& material) :
        name_(std::move(name)), vertices_(std::move(vertices)), indices_(std::move(indices)), material_(material),
        va_() {
    update_vao();
    init_program();
}

void Mesh::update_vao() {
    if (!va_) va_ = VertexArray::create();
    va_->add_data(vertices_, VertexBufferLayout::Common::F3DN());
    va_->add_indices(indices_);
}

std::vector<Mesh> Mesh::load_obj(const std::string& path) {
    init_program();

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


    std::vector<Mesh> meshes{};
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
        mesh.material_ = Material::from_mtl(materials[shape.mesh.material_ids[0]]);
        mesh.update_vao();
        meshes.push_back(std::move(mesh));
    }
    return meshes;
}