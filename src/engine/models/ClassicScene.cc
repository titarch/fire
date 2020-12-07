//
// Created by bparsy on 6/9/20.
//

#include "ClassicScene.hh"

ClassicScene::ClassicScene()
        : BaseScene(), shapes_(), spawners_(), cubemap_(), tilemap_() {
    Particle::init_program();
    Mesh::init_program();
}

Shape::ptr ClassicScene::add_object(const std::string& path) {
    auto shape = Shape::load_obj(path);
    add_shape(shape);
    return shape;
}

ClassicScene& ClassicScene::add_shape(Shape::ptr& shape) {
    shapes_.push_back(shape);
    return *this;
}

ClassicScene& ClassicScene::add_spawner(Spawner::ptr& spawner) {
    spawners_.push_back(spawner);
    return *this;
}

ClassicScene& ClassicScene::set_cubemap(const std::string& path) {
    cubemap_ = CubeMap::make(path);
    return *this;
}

ClassicScene& ClassicScene::set_tilemap(const std::string& path) {
    tilemap_ = TileMap::make(path);
    return *this;
}

void ClassicScene::use() {
    if (!shapes_.empty()) {
        Mesh::program().use();
        Mesh::program().set_uniform<GL_FLOAT_VEC4>("u_light_position", light_position_[0], light_position_[1],
                                                   light_position_[2], 1.f);
        Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_proj", projection_.data());
    }
    if (!shapes_.empty()) {
        Particle::program().use();
        Particle::program().set_uniform<GL_FLOAT_MAT4>("u_proj", projection_.data());
    }
    if (cubemap_) {
        CubeMap::program_->use();
        CubeMap::program_->set_uniform<GL_FLOAT_MAT4>("u_proj", projection_.data());
    }
    if (tilemap_) {
        TileMap::program_->use();
        TileMap::program_->set_uniform<GL_FLOAT_VEC4>("u_light_position", light_position_[0], light_position_[1],
                                                      light_position_[2], 1.f);
        TileMap::program_->set_uniform<GL_FLOAT_MAT4>("u_proj", projection_.data());
    }
    update();
}

void ClassicScene::update() const {
    auto const& cur_view = view();
    if (!shapes_.empty()) {
        Mesh::program().use();
        Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_view", cur_view.data());
        Mesh::program().set_uniform<GL_FLOAT_VEC4>("u_camera_pos", position_[0], position_[1], position_[2], 1.0f);
    }
    if (!spawners_.empty()) {
        Particle::program().use();
        Particle::program().set_uniform<GL_FLOAT_MAT4>("u_view", cur_view.data());
    }
    if (cubemap_) {
        CubeMap::program_->use();
        CubeMap::program_->set_uniform<GL_FLOAT_MAT4>("u_view", cur_view.without_translation().data());
    }
    if (tilemap_) {
        TileMap::program_->use();
        TileMap::program_->set_uniform<GL_FLOAT_MAT4>("u_view", cur_view.data());
        TileMap::program_->set_uniform<GL_FLOAT_VEC4>("u_camera_pos", position_[0], position_[1], position_[2], 1.0f);
    }
}

void ClassicScene::render(WinRender const& wr) {
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    if (cubemap_)
        wr.draw(dynamic_cast<const CubeMap&>(*cubemap_));
    if (tilemap_)
        wr.draw(dynamic_cast<const TileMap&>(*tilemap_));
    for (auto const& shape : shapes_)
        wr.draw(*shape);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (auto const& spawner : spawners_)
        wr.draw(*spawner);
}

void ClassicScene::update_spawners() {
    for (auto& spawner : spawners_)
        spawner->step();
}