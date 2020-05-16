//
// Created by bparsy on 5/16/20.
//

#include <stdexcept>
#include <GL/glew.h>
#include "WinHandler.hh"

WinHandler::WinHandler(int width, int height) : width_(width), height_(height) {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    win_ = glfwCreateWindow(width, height, "float-opengl", nullptr, nullptr);

    if (!win_) {
        glfwTerminate();
        throw std::runtime_error("Could not create glfw window");
    }
    glfwMakeContextCurrent(win_);
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Could not init glew");
}

WinHandler::~WinHandler() {
    glfwTerminate();
}

void WinHandler::loop() {
    while (!glfwWindowShouldClose(win_)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glfwSwapBuffers(win_);
        glfwPollEvents();
    }
}
