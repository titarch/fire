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

void glfw_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

WinRender::WinRender(int width, int height) : width_(width), height_(height) {
    glfwSetErrorCallback(glfw_callback);
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

void WinRender::close() const {
    glfwSetWindowShouldClose(win_, GL_TRUE);
}

void WinRender::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool WinRender::is_open() const {
    return !glfwWindowShouldClose(win_);
}

bool WinRender::poll_event(Event& e) {
    glfwPollEvents();
    if (Event::events_.empty()) return false;
    e = Event::events_.front();
    Event::events_.pop();
    return true;
}

void WinRender::display() const {
    glfwSwapBuffers(win_);
}

void WinRender::draw(const VertexArray& va, const Program& p) const {
    p.use();
    va.bind();

    if (va.ibo() != nullptr) {
        auto const* ibo = va.ibo();
        ibo->bind();
        glDrawElements(GL_TRIANGLES, ibo->count(), GL_UNSIGNED_INT, nullptr);
    } else if (va.vbo() != nullptr) {
        auto const* vbo = va.vbo();
        vbo->bind();
//        glDrawArrays(GL_PATCHES, 0, 4);
//        glPatchParameteri(GL_PATCH_VERTICES, 4);
        glDrawArrays(GL_TRIANGLES, 0, vbo->count());
    } else if (va.ssbo() != nullptr) {
        auto const* ssbo = va.ssbo();
        ssbo->vb_bind();
        glDrawArrays(GL_TRIANGLES, 0, ssbo->count());
    } else
        throw std::runtime_error("VAO: no data to draw");
}

void WinRender::draw(const Mesh& mesh) const {
    mesh.preload();
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices_.size() / 6);
}

void WinRender::draw(const Shape& shape) const {
    for (auto const& mesh : shape.meshes())
        draw(mesh);
}

void WinRender::draw(const Spawner& spawner) const {
    Particle::program_->use();
    Particle::va_->bind();
    Particle::va_->ibo()->bind();
    spawner.texture_->bind(0);
    for (auto const& particle : spawner.particles_)
        draw(particle);
}

void WinRender::draw(const Particle& particle) const {
    particle.use();
    glDrawElements(GL_TRIANGLES, Particle::va_->ibo()->count(), GL_UNSIGNED_INT, nullptr);
}

void WinRender::draw(const CubeMap& cubemap) const {
    CubeMap::program_->use();
    CubeMap::va_->bind();
    cubemap.bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void WinRender::draw(const TileMap& tilemap) const {
    tilemap.bind(0);
    draw(*TileMap::va_, *TileMap::program_);
}

int WinRender::width() const {
    return width_;
}

int WinRender::height() const {
    return height_;
}

float WinRender::ratio() const {
    return (float) width_ / (float) height_;
}
