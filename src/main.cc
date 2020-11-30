#include "engine/program.hh"
#include "engine/models/ClassicScene.hh"
#include "utils/colors.hh"

auto main() -> int {
    std::srand(0);
    auto wr = WinRender(1920, 1080);

    auto spawner = Spawner::make("../res/assets/fire.png", Vec(), 3000);
    auto tree = Shape::load_obj("../res/assets/pine.obj");
    auto log = Shape::load_obj("../res/assets/log.obj");

    ClassicScene scene{};
    scene.set_light_position({0, 0.5, 0})
            .set_perspective(45.f, 16.f / 9.f, 0.01f, 1000.f)
            .set_camera({0, 0.5, 3}, Vec::back())
            .set_cubemap("../res/assets/cubemap/")
            .set_tilemap("../res/assets/ground.jpg")
            .add_spawner(spawner)
            .add_shape(log)
            .use();

    tree->translate({0, 1.7, 0});
    for (auto i = 0u; i < 150; ++i) {
        auto tree_clone = tree->clone(true, true);
        float random_x = rand() % 50 - 25;
        float random_z = rand() % 50 - 25;
        float random_scale = ((float) rand() / (float) RAND_MAX - 0.5f) / 2.f + 1.f;
        tree_clone->translate({random_x, random_scale - 1.f, random_z})
                .rescale({random_scale, random_scale, random_scale})
                .rotate(random_scale + random_x, Vec::up());
        scene.add_shape(tree_clone);
    }

    log->translate({0.01, 0.0, 0.01})
            .rescale({0.15, 0.15, 0.15});

    auto log_copy = log->clone(false, true);
    log_copy->materials()[0]->ka = log_copy->materials()[0]->ka * 0.5;
    log_copy->materials()[0]->kd = log_copy->materials()[0]->kd * 0.5;
    log_copy->translate({-3, 0.1, -3.5})
            .rescale({0.7, 0.7, 0.7})
            .rotate(-M_PI / 2.f, Vec::up());
    scene.add_shape(log_copy);
    for (auto i = 0u; i < 3; ++i) {
        log_copy = log_copy->clone(true, false);
        log_copy->translate({0.4, 0, 0});
        scene.add_shape(log_copy);
    }


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
        scene.render(wr);
        wr.display();
    }
}
