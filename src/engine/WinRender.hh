//
// Created by bparsy on 5/16/20.
//

#ifndef FIRE_WINRENDER_HH
#define FIRE_WINRENDER_HH

#include <GLFW/glfw3.h>
#include <cstddef>
#include "buffers/VertexArray.hh"
#include "Program.hh"
#include "Event.hh"
#include "particles/Spawner.hh"
#include "textures/CubeMap.hh"
#include "textures/TileMap.hh"
#include "models/Mesh.hh"
#include "models/Shape.hh"
#include "models/Terrain.hh"
#include "models/Grass.hh"


class WinRender {
public:
    WinRender(int width, int height);
    ~WinRender();

    void close() const;
    void clear() const;
    [[nodiscard]] bool is_open() const;
    bool poll_event(Event& e);
    void update_time();
    [[nodiscard]] double dt() const;
    [[nodiscard]] double time() const;
    void display() const;
    void draw(VertexArray const& va, Program const& p, GLenum type = GL_TRIANGLES) const;
    void draw(Mesh const& mesh) const;
    void draw(Shape const& shape) const;
    void draw(Spawner const& spawner) const;
    void draw(Particle const& particle) const;
    void draw(CubeMap const& cubemap) const;
    void draw(TileMap const& tilemap) const;
    void draw(Terrain const& terrain) const;
    void draw(Grass const& grass) const;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] float ratio() const;
protected:
    int width_, height_;
    GLFWwindow* win_{};
    double current_frame_{}, last_frame_{}, delta_time_{};

    friend class Event;
};


#endif //FIRE_WINRENDER_HH
