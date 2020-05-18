#include "engine/program.hh"

static constexpr std::array triangle = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
};

auto main() -> int {
    auto wh = WinHandler(1366, 768);

    BufHandler::create_2D_buffer(triangle);
    auto prgm = Program::make_program("../res/shaders/vertex/basic.shd", "../res/shaders/fragment/uniform_magenta.shd");
    if (!prgm->is_ready()) throw std::runtime_error("Program was not ready");
    prgm->use();

    wh.display(3);
}