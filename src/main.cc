#include "engine/program.hh"



auto main() -> int {
    auto wh = WinHandler(1366, 768);
    Program::Example::square(wh);
}