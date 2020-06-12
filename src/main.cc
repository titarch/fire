#include "engine/program.hh"
#include "engine/models/Scene.hh"
#include "utils/colors.hh"

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

    auto cpy = shape->clone(false);
    cpy->translate({2, 0, 0});
    cpy->rescale({0.2, 0.2, 0.2});
    scene.add_shape(cpy);

    Event e(wr);
    int hue = 0;
    while (wr.is_open()) {

        while (wr.poll_event(e)) {
            const static float step = 0.07;
            const static float angle = 0.02;
            if (e.action == GLFW_PRESS || e.action == GLFW_REPEAT) {
                if (e.key == GLFW_KEY_W)
                    scene.move(step, Dir::FORWARD);
                else if (e.key == GLFW_KEY_A)
                    scene.move(step, Dir::LEFT);
                else if (e.key == GLFW_KEY_S)
                    scene.move(step, Dir::BACK);
                else if (e.key == GLFW_KEY_D)
                    scene.move(step, Dir::RIGHT);
                else if (e.key == GLFW_KEY_Z)
                    scene.move(step, Dir::UP);
                else if (e.key == GLFW_KEY_X)
                    scene.move(step, Dir::DOWN);
                else if (e.key == GLFW_KEY_I)
                    scene.turn(-angle, Norm::RIGHT);
                else if (e.key == GLFW_KEY_J)
                    scene.turn(angle, Norm::UP);
                else if (e.key == GLFW_KEY_K)
                    scene.turn(angle, Norm::RIGHT);
                else if (e.key == GLFW_KEY_L)
                    scene.turn(-angle, Norm::UP);
            }
        }

        shape->rotate(0.02f, {1, 0.5, 0});
        shape->materials()[0]->ka = hsv(hue, 1.0, 0.05);
        shape->materials()[0]->kd = hsv(hue, 1.0, 0.5);
        hue = (hue + 1) % 360;
        wr.clear();
        wr.draw(scene);
        wr.display();
    }
}
