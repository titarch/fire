//
// Created by bparsy on 5/16/20.
//

#ifndef FIRE_WINHANDLER_HH
#define FIRE_WINHANDLER_HH

#include <GLFW/glfw3.h>
#include <cstddef>
#include "buffers/VertexArray.hh"
#include "Program.hh"

class WinHandler {
public:
    WinHandler(int width, int height);
    void draw(GLenum type, std::size_t object_size, bool indexed) const;
    void draw(VertexArray const& va, Program const& p);
    ~WinHandler();

protected:
    int width_, height_;
    GLFWwindow* win_;
};


#endif //FIRE_WINHANDLER_HH
