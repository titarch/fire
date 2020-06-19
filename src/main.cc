#include "engine/program.hh"
#include "engine/models/Scene.hh"
#include "utils/colors.hh"

auto main() -> int {
    auto wr = WinRender(1920, 1080);

    auto spawner = Spawner::make("../res/assets/fire.png", Vec(), 5000);
    auto shape = Shape::load_obj("../res/assets/sphere.obj");

    Scene scene{};
    scene.set_light_position({-3, 3, 15})
            .set_perspective(45.f, 16.f / 9.f, 0.01f, 1000.f)
            .set_camera({0, 0, 3}, Vec::back())
            .set_cubemap("../res/assets/cubemap/")
            .add_spawner(spawner)
            .add_shape(shape)
            .use();

    shape->rescale({0.05, 0.05, 0.05})
            .translate({1, 0, 0});

    Event e(wr);
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

        scene.update_spawners();
        wr.clear();
        wr.draw(scene);
        wr.display();
    }
}
