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
    using win_callback = std::function<void(WinRender const&)>;
public:
    QuickScene(scene_callback use, scene_callback update, win_callback render);
    void use() override;
    void update() const override;
    void render(const WinRender& wr) override;

protected:
    scene_callback use_, update_;
    win_callback render_;
};


#endif //FIRE_QUICKSCENE_HH
