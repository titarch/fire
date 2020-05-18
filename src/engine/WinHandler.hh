//
// Created by bparsy on 5/16/20.
//

#ifndef FIRE_WINHANDLER_HH
#define FIRE_WINHANDLER_HH

#include <GLFW/glfw3.h>
#include <cstddef>

class WinHandler {
public:
    WinHandler(int width, int height);
    void display(std::size_t object_size);
    ~WinHandler();

protected:
    int width_, height_;
    GLFWwindow* win_;
};


#endif //FIRE_WINHANDLER_HH
