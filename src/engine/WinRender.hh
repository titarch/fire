//
// Created by bparsy on 5/16/20.
//

#ifndef FIRE_WINRENDER_HH
#define FIRE_WINRENDER_HH

#include <GLFW/glfw3.h>
#include <cstddef>
#include "buffers/VertexArray.hh"
#include "Program.hh"
#include "models/Scene.hh"

class WinRender {
public:
    WinRender(int width, int height);
    ~WinRender();

    void clear() const;
    [[nodiscard]] bool is_open() const;
    void display() const;
    void draw(VertexArray const& va, Program const& p) const;
    void draw(Mesh const& mesh) const;
    void draw(Shape const& shape) const;
    void draw(Scene const& scene) const;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] float ratio() const;
protected:
    int width_, height_;
    GLFWwindow* win_;
};


#endif //FIRE_WINRENDER_HH
