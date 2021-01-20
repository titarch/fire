#include "engine/program.hh"
#include "engine/models/QuickScene.hh"
#include "utils/colors.hh"
#include "bunny.hh"
#include "engine/buffers/StorageBuffer.hh"

constexpr auto width = 2560;
constexpr auto height = 1440;
constexpr auto ratio = float(width) / float(height);
constexpr auto fov = 80.f * M_PI / 180.f;

auto main() -> int {
    std::srand(0);
    auto wr = WinRender(width, height);

    std::vector<float> buffer_data{};
    buffer_data.reserve(vertex_buffer_data.size() * 2);
    for (auto i = 0u; i < vertex_buffer_data.size() / 3; ++i) {
        for (auto j = 0u; j < 3; ++j)
            buffer_data.push_back(vertex_buffer_data[3 * i + j]);
        for (auto j = 0u; j < 3; ++j)
            buffer_data.push_back(normal_smooth_buffer_data[3 * i + j]);
    }

    auto vao = BufHandler::make_vao();
    vao->bind();
    vao->add_storage_data(
            buffer_data,
            VertexBufferLayout::Common::F3DN()
    );
    vao->ssbo_base_index(1);

    auto puff = Program::make_compute("puff");
    puff->use();
    int size = buffer_data.size() / 6;
    float anim = 0;
    puff->set_uniform<GL_INT>("size", size);
    puff->set_uniform<GL_FLOAT>("anim", anim);
    puff->dispatch(1, size / 1024 + 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    Mesh mesh("bunny", buffer_data, {}, &Material::gray);
    auto bunny = std::make_shared<Shape>();
    bunny->add_mesh(std::move(mesh));

    QuickScene scene(wr,
            [](QuickScene const& scene) {
                auto const& lp = scene.light_position();
                Mesh::program().use();
                Mesh::program().set_uniform<GL_FLOAT_VEC4>("u_light_position", lp[0], lp[1], lp[2], 1.f);
                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_proj", scene.projection().data());
            },
            [](QuickScene const& scene) {
                auto const& cur_view = scene.view();
                auto const& pos = scene.position();
                Mesh::program().use();
                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_view", cur_view.data());
                Mesh::program().set_uniform<GL_FLOAT_VEC4>("u_camera_pos", pos[0], pos[1], pos[2], 1.0f);
            },
            [&vao, &puff, &anim, size](QuickScene const& scene) {
                glEnable(GL_DEPTH_TEST);
                Mesh::program().use();
                Material::gray.use();

                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_trans", Mat::id().data());
                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_rot", Mat::id().data());
                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_center", Mat::id().data());
                Mesh::program().set_uniform<GL_FLOAT_MAT4>("u_scale", Mat::id().data());


                puff->use();
                anim += 0.01;
                puff->set_uniform<GL_FLOAT>("anim", anim);
                puff->dispatch(1, size / 1024 + 1, 1);
                glMemoryBarrier(GL_ALL_BARRIER_BITS);

                scene.win().draw(*vao, Mesh::program());
            }
    );
    scene.set_light_position({1, 10, 5})
            .set_perspective(fov, ratio, 0.01f, 1000.f)
            .set_camera({0, 0.5, 3}, Vec::back())
            .use();

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

        scene.step();
    }
}
