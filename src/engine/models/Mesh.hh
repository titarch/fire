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
    static std::vector<Mesh> load_obj(std::string const& path);
    void update_vao();

    Mat& model() { return model_; };
protected:
    explicit Mesh(std::string name) : name_(std::move(name)), vertices_(), indices_(), material_(), va_(), model_() {}

    static void init_program();

    std::string name_;
    std::vector<float> vertices_;
    std::vector<unsigned> indices_;
    Material material_;
    VertexArray::ptr va_;
    Mat model_;

    static Program::ptr program_;

    friend class WinRender;

    friend class Material;
};


#endif //FIRE_MESH_HH
