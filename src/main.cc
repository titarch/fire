#include <map>
#include "engine/program.hh"
#include "engine/models/ClassicScene.hh"
#include "utils/colors.hh"

constexpr auto width = 2560;
constexpr auto height = 1440;
constexpr auto ratio = float(width) / float(height);
constexpr auto fov = 80.f * M_PI / 180.f;

auto main() -> int {
    std::srand(50);
    auto wr = WinRender(width, height);

    auto tree = Shape::load_obj("../res/assets/pine.obj");
    auto log = Shape::load_obj("../res/assets/log.obj");

    ClassicScene scene{wr};
    scene
            .set_terrain(0.1, 1000, 1000, 0)
            .set_light_position({0.0, 2.0, 0.0})
            .set_grass()
            .set_perspective(fov, ratio, 0.01f, 1000.f)
            .set_camera({0.0, scene.height_at(0.0, 2.0) + 0.5f, 2.0}, Vec::back())
            .set_cubemap("../res/assets/cubemap/")
            .add_shape(log)
            .use();

    auto spawner = Spawner::make("../res/assets/fire.png", Vec{}, 3000);
    scene.add_spawner(spawner)
            .use();

    tree->translate({0, 1.7, 0});
    for (auto i = 0u; i < 150; ++i) {
        auto tree_clone = tree->clone(true, true);
        float random_x = rand() % 50 - 25;
        float random_z = rand() % 50 - 25;
        float random_scale = ((float) rand() / (float) RAND_MAX - 0.5f) / 2.f + 1.f;
        tree_clone->translate({random_x, random_scale - 1.f + scene.height_at(random_x, random_z), random_z})
                .rescale({random_scale, random_scale, random_scale})
                .rotate(random_scale + random_x, Vec::up());
        scene.add_shape(tree_clone);
    }

    log->translate({0.0, 0.1, 0.0})
            .rescale({0.15, 0.15, 0.15});

    Event e(wr);
    std::map<int, bool> active_keys{};
    double last_xpos{0}, last_ypos{0};
    while (wr.is_open()) {
        while (wr.poll_event(e)) {
            if (e.action == GLFW_PRESS) {
                if (e.key == GLFW_KEY_ESCAPE)
                    wr.close();
                active_keys[e.key] = true;
            } else if (e.action == GLFW_RELEASE)
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

        scene.step();
    }
}
