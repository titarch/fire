//
// Created by bparsy on 5/16/20.
//

#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include "WinHandler.hh"

[[maybe_unused]] static void GLAPIENTRY
MessageCallback([[maybe_unused]]GLenum source,
                GLenum type,
                [[maybe_unused]]GLuint id,
                GLenum severity,
                [[maybe_unused]]GLsizei length,
                const GLchar* message,
                [[maybe_unused]]const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

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

#ifdef DEBUG_OPENGL
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, reinterpret_cast<void*>(0));
#endif
}

WinHandler::~WinHandler() {
    glfwTerminate();
}

void WinHandler::display(std::size_t object_size) {
    while (!glfwWindowShouldClose(win_)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, object_size);
        glfwSwapBuffers(win_);
        glfwPollEvents();
    }
}
