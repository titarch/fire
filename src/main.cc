#include <map>
#include "engine/program.hh"
#include "engine/models/ClassicScene.hh"
#include "utils/colors.hh"

auto main() -> int {
    std::srand(0);
    auto wr = WinRender(1920, 1080);

    auto spawner = Spawner::make("../res/assets/fire.png", Vec(), 3000);
    auto tree = Shape::load_obj("../res/assets/pine.obj");
    auto log = Shape::load_obj("../res/assets/log.obj");

    ClassicScene scene{wr};
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
    std::map<int, bool> active_keys{};
    double last_xpos{0}, last_ypos{0};
    while (wr.is_open()) {
        while (wr.poll_event(e)) {
            if (e.action == GLFW_PRESS) {
                if (e.key == GLFW_KEY_ESCAPE)
                    wr.close();
                active_keys[e.key] = true;
            }
            else if (e.action == GLFW_RELEASE)
                active_keys[e.key] = false;
            else if (e.action == GLFW_CURSOR) {
                constexpr static float rotation_speed = 0.5f;
                scene.turn(float(last_xpos - e.xpos) * rotation_speed, Norm::UP);
                scene.turn(float(e.ypos - last_ypos) * rotation_speed, Norm::RIGHT);
                last_xpos = e.xpos;
                last_ypos = e.ypos;
            }
        }

        constexpr static float step = 3.f;
        constexpr static float angle = 0.5f;
        if (active_keys[GLFW_KEY_W]) scene.move(step, Dir::FORWARD);
        if (active_keys[GLFW_KEY_A]) scene.move(step, Dir::LEFT);
        if (active_keys[GLFW_KEY_S]) scene.move(step, Dir::BACK);
        if (active_keys[GLFW_KEY_D]) scene.move(step, Dir::RIGHT);
        if (active_keys[GLFW_KEY_Z]) scene.move(step, Dir::UP);
        if (active_keys[GLFW_KEY_X]) scene.move(step, Dir::DOWN);
        if (active_keys[GLFW_KEY_I]) scene.turn(-angle, Norm::RIGHT);
        if (active_keys[GLFW_KEY_J]) scene.turn(angle, Norm::UP);
        if (active_keys[GLFW_KEY_K]) scene.turn(angle, Norm::RIGHT);
        if (active_keys[GLFW_KEY_L]) scene.turn(-angle, Norm::UP);

        scene.update();
        wr.clear();
        wr.update_time();
        scene.render();
        wr.display();
    }
}
