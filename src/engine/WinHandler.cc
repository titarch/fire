//
// Created by bparsy on 5/16/20.
//

#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include "WinHandler.hh"
#include "BufHandler.hh"
#include "Program.hh"

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
    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    // Baptiste's machine has "4.6.0 NVIDIA 440.82"
    // Salome's machine has "?"
}

WinHandler::~WinHandler() {
    glfwTerminate();
}

void WinHandler::loop() {
    static constexpr std::array triangle = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    BufHandler::create_2D_buffer(triangle);
    auto prgm = Program::make_program("../res/shaders/vertex/basic.shd", "../res/shaders/fragment/uniform_magenta.shd");
    if (!prgm->is_ready()) throw std::runtime_error("Program was not ready");
    prgm->use();

    while (!glfwWindowShouldClose(win_)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win_);
        glfwPollEvents();
    }
}
