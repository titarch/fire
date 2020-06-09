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
    Mesh(std::string name, std::vector<float> vertices, std::vector<unsigned> indices, Material const& material);
    static const Program& program();
    void update_vao();
    void preload() const;

    Mat model() const {
        return trans * rot * center * scale;
    }

protected:
    explicit Mesh(std::string name);

    static void init_program();

    std::string name_;
    std::vector<float> vertices_;
    std::vector<unsigned> indices_;
    Material material_;
    VertexArray::ptr va_;
    static Program::ptr program_;
public:
    Mat trans, rot, center, scale;

    friend class WinRender;

    friend class Material;

    friend class Shape;
};


#endif //FIRE_MESH_HH
