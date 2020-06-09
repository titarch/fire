//
// Created by bparsy on 6/9/20.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Event.hh"
#include "WinRender.hh"

std::queue<Event> Event::events_{};

void key_callback([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, int mods) {
    Event::events_.emplace(key, action, mods);
}

Event::Event(const WinRender& w) : key(-1), action(-1), mods(-1) {
    attach(w);
}

Event::Event(int key, int action, int mods) : key(key), action(action), mods(mods) {}

void Event::attach(WinRender const& w) {
    glfwSetKeyCallback(w.win_, key_callback);
}

