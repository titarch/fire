#include "engine/program.hh"
#include "engine/models/Scene.hh"

auto main() -> int {
    auto wr = WinRender(1920, 1080);

    Scene scene{};
    scene.set_light_position({-3, 3, 15})
            .set_perspective(45.f, 16.f / 9.f, 0.01f, 50.f)
            .set_camera({0, 0, 3}, Vec::back())
            .use();

    auto shape = scene.add_object("../res/assets/sphere.obj");
    shape->translate({0, 0, -0.5});
    shape->recenter({0, -0.25, 0});
    shape->rescale({0.5, 0.5, 0.5});

    Event e(wr);
    while (wr.is_open()) {

        while (wr.poll_event(e)) {
            const static float step = 0.07;
            const static float angle = 0.02;
            if (e.action == GLFW_PRESS || e.action == GLFW_REPEAT) {
                if (e.key == GLFW_KEY_W)
                    scene.position() += scene.direction() * step;
                else if (e.key == GLFW_KEY_A)
                    scene.position() += Vec::up() ^ scene.direction() * step;
                else if (e.key == GLFW_KEY_S)
                    scene.position() += scene.direction() * -step;
                else if (e.key == GLFW_KEY_D)
                    scene.position() += scene.direction() ^ Vec::up() * step;
                else if (e.key == GLFW_KEY_I)
                    scene.direction().rotate(angle, Vec::right());
                else if (e.key == GLFW_KEY_J)
                    scene.direction().rotate(angle, Vec::up());
                else if (e.key == GLFW_KEY_K)
                    scene.direction().rotate(-angle, Vec::right());
                else if (e.key == GLFW_KEY_L)
                    scene.direction().rotate(-angle, Vec::up());
                scene.refresh_view();
            }
        }

        shape->rotate(0.02f, {1, 0.5, 0});
        wr.clear();
        wr.draw(scene);
        wr.display();
    }
}
