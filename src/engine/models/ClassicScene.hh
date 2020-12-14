//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_CLASSICSCENE_HH
#define FIRE_CLASSICSCENE_HH

#include "BaseScene.hh"
#include "Shape.hh"
#include "../particles/Spawner.hh"
#include "../textures/CubeMap.hh"
#include "../textures/TileMap.hh"

class ClassicScene : public BaseScene<ClassicScene> {
public:
    explicit ClassicScene(WinRender& wr);

    void use() override;
    void update() override;
    void render() override;

    Shape::ptr add_object(std::string const& path);
    ClassicScene& add_shape(Shape::ptr& shape);
    ClassicScene& add_spawner(Spawner::ptr& spawner);
    ClassicScene& set_cubemap(std::string const& path);
    ClassicScene& set_tilemap(std::string const& path);
    void update_spawners();
private:
    std::vector<Shape::ptr> shapes_;
    std::vector<Spawner::ptr> spawners_;
    CubeMap::ptr cubemap_;
    TileMap::ptr tilemap_;
};


#endif //FIRE_CLASSICSCENE_HH
