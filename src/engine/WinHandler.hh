//
// Created by bparsy on 5/16/20.
//

#ifndef FIRE_WINHANDLER_HH
#define FIRE_WINHANDLER_HH

#include <GLFW/glfw3.h>
#include <stdexcept>

class WinHandler {
public:
    WinHandler(int width, int height);
    void loop();
    ~WinHandler();

protected:
    int width_, height_;
    GLFWwindow* win_;
};


#endif //FIRE_WINHANDLER_HH
