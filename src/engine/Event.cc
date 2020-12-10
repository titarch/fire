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

void mouse_callback([[maybe_unused]] GLFWwindow* window, double xpos, double ypos) {
    Event::events_.emplace(xpos, ypos);
}

Event::Event(const WinRender& w) {
    attach(w);
}

Event::Event(int key, int action, int mods) : key(key), action(action), mods(mods) {}

Event::Event(double xpos, double ypos) : action(GLFW_CURSOR), xpos(xpos), ypos(ypos) {}

void Event::attach(WinRender const& w) {
    glfwSetKeyCallback(w.win_, key_callback);
    glfwSetCursorPosCallback(w.win_, mouse_callback);
}

