//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_SCENE_HH
#define FIRE_SCENE_HH

#include "BaseScene.hh"
#include "Shape.hh"
#include "../particles/Spawner.hh"
#include "../textures/CubeMap.hh"
#include "../textures/TileMap.hh"

class Scene : public BaseScene<Scene> {
public:
    Scene();

    void use() override;
    void update() const override;
    void render(WinRender const& wr) override;

    Shape::ptr add_object(std::string const& path);
    Scene& add_shape(Shape::ptr& shape);
    Scene& add_spawner(Spawner::ptr& spawner);
    Scene& set_cubemap(std::string const& path);
    Scene& set_tilemap(std::string const& path);
    void update_spawners();
private:
    std::vector<Shape::ptr> shapes_;
    std::vector<Spawner::ptr> spawners_;
    CubeMap::ptr cubemap_;
    TileMap::ptr tilemap_;
};


#endif //FIRE_SCENE_HH
