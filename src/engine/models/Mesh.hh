//
// Created by bparsy on 6/8/20.
//

#ifndef FIRE_MESH_HH
#define FIRE_MESH_HH

#include <string>
#include <utility>
#include <vector>
#include "../buffers/VertexArray.hh"
#include "../Program.hh"
#include "Material.hh"

class Mesh {
public:
    Mesh(std::string name, std::vector<float> vertices, std::vector<unsigned> indices, Material* material);
    Mesh(Mesh&&) = default;
    [[nodiscard]] Mesh clone(bool keep_vao) const;
    static const Program& program();
    void update_vao();
    void preload() const;

protected:
    explicit Mesh(std::string name);
    explicit Mesh(Mesh const&) = default;

    static void init_program();

    std::string name_;
    std::vector<float> vertices_;
    std::vector<unsigned> indices_;
    const Material* material_;
    int material_id_;
    VertexArray::ptr va_;
    static Program::ptr program_;
public:
    Mat trans, rot, center, scale;

    friend class WinRender;

    friend class Material;

    friend class Shape;
};


#endif //FIRE_MESH_HH
