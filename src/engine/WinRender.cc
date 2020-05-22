//
// Created by bparsy on 5/16/20.
//

#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include "WinRender.hh"

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

WinRender::WinRender(int width, int height) : width_(width), height_(height) {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win_ = glfwCreateWindow(width, height, "float-opengl", nullptr, nullptr);

    if (!win_) {
        glfwTerminate();
        throw std::runtime_error("Could not create glfw window");
    }
    glfwMakeContextCurrent(win_);
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Could not init glew");
    std::cout << "Using OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    // Baptiste's machine has maximum "4.6.0 NVIDIA 440.82"
    // Salome's machine has maximum "4.2.0 MESA 20.0.6"

#ifdef DEBUG_OPENGL
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);
#endif
}

WinRender::~WinRender() {
    glfwTerminate();
}

void WinRender::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

bool WinRender::is_open() const {
    return !glfwWindowShouldClose(win_);
}

void WinRender::display() const {
    glfwSwapBuffers(win_);
    glfwPollEvents();
}

void WinRender::draw(const VertexArray& va, const Program& p) const {
    p.use();
    va.bind();
    auto const* ibo = va.ibo();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, ibo->count(), GL_UNSIGNED_INT, nullptr);
}

