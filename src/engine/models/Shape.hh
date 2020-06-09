//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_SHAPE_HH
#define FIRE_SHAPE_HH

#include <vector>
#include <utility>
#include <memory>
#include "../../utils/transform.hh"
#include "Mesh.hh"

class Shape {
public:
    using ptr = std::shared_ptr<Shape>;
public:
    explicit Shape();
    explicit Shape(std::vector<Mesh> meshes);

    static Shape::ptr load_obj(std::string const& path);
    Shape& add_mesh(Mesh mesh);
    [[nodiscard]] std::vector<Mesh> const& meshes() const;

    Shape& reset();
    Shape& translate(Vec const& v);
    Shape& translation(Mat const& m);
    Shape& rotate(float angle, const Vec& dir);
    Shape& rotation(Mat const& m);
    Shape& rescale(Vec const& v);
    Shape& scale(Mat const& m);
    Shape& recenter(Vec const& v);
    Shape& center(Mat const& m);
private:
    std::vector<Mesh> meshes_;
};


#endif //FIRE_SHAPE_HH
