#include "engine/program.hh"



auto main() -> int {
    auto wh = WinRender(1366, 768);
    Program::Example::square(wh);
}