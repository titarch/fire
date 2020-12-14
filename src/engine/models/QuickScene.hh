//
// Created by bparsy on 11/30/20.
//

#ifndef FIRE_QUICKSCENE_HH
#define FIRE_QUICKSCENE_HH


#include <functional>
#include "BaseScene.hh"

class QuickScene : public BaseScene<QuickScene> {
public:
    using scene_callback = std::function<void(QuickScene const&)>;
public:
    QuickScene(WinRender& wr, scene_callback use, scene_callback update, scene_callback render);
    void use() override;
    void update() override;
    void render() override;

protected:
    scene_callback use_, update_, render_;
};


#endif //FIRE_QUICKSCENE_HH
