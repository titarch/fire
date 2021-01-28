//
// Created by bparsy on 1/28/21.
//

#ifndef FIRE_GRASS_HH
#define FIRE_GRASS_HH


#include <memory>
#include "../buffers/VertexArray.hh"
#include "../Program.hh"

class Grass {
public:
    using ptr = std::shared_ptr<Grass>;
public:
    explicit Grass(std::vector<float> const& vertices);
    static ptr make(std::vector<float> const& vertices);
protected:
    VertexArray::ptr va_;
    static Program::ptr program_;

    static void init_program();

    friend class ClassicScene;
    friend class WinRender;
};


#endif //FIRE_GRASS_HH
