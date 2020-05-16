#include "engine/WinHandler.hh"

auto main() -> int {
    auto wh = WinHandler(1366, 768);
    wh.loop();
}