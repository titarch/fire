#define TINYOBJLOADER_IMPLEMENTATION

#include "Material.hh"
#include "../../utils/3rdparty/tiny_obj_loader.h"
#include "Mesh.hh"

Material Material::from_mtl(tinyobj::material_t const& mtl) {
    return {mtl.ambient, mtl.diffuse, mtl.specular, mtl.shininess};
}

void Material::use() const {
    Mesh::program_->set_uniform<GL_FLOAT_VEC4>("u_ka", ka[0], ka[1], ka[2], 1.f);
    Mesh::program_->set_uniform<GL_FLOAT_VEC4>("u_kd", kd[0], kd[1], kd[2], 1.f);
    Mesh::program_->set_uniform<GL_FLOAT_VEC4>("u_ks", ks[0], ks[1], ks[2], 1.f);
    Mesh::program_->set_uniform<GL_FLOAT>("u_ns", ns);
}
