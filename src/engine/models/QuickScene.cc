//
// Created by bparsy on 11/30/20.
//

#include <utility>

#include "QuickScene.hh"

QuickScene::QuickScene(WinRender& wr, scene_callback use, scene_callback update, scene_callback render) :
        BaseScene(wr),
        use_(std::move(use)), update_(std::move(update)), render_(std::move(render)) {}

void QuickScene::use() {
    use_(*this);
    update();
}

void QuickScene::update() const {
    update_(*this);
}

void QuickScene::render() {
    render_(*this);
}
