#include "engine/program.hh"



auto main() -> int {
    auto wr = WinRender(1366, 768);
    Program::Example::cube(wr);
}