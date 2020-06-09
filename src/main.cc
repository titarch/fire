#include "engine/program.hh"
#include "engine/models/Scene.hh"

auto main() -> int {
    auto wr = WinRender(1920, 1080);

    Scene scene{};
    scene.set_light_position({-3, 3, 15})
            .set_perspective(45.f, 16.f / 9.f, 0.01f, 50.f)
            .set_camera({0, 0, 3}, Vec::zero(), Vec::up())
            .use();

    auto shape = scene.add_object("../res/assets/sphere.obj");
    shape->translate({0, 0, -0.5});
    shape->recenter({0, -0.25, 0});
    shape->rescale({0.5, 0.5, 0.5});

    while (wr.is_open()) {
        shape->rotate(0.02f, {1, 0.5, 0});
        wr.clear();
        wr.draw(scene);
        wr.display();
    }
}
