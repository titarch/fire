//
// Created by bparsy on 6/9/20.
//

#ifndef FIRE_EVENT_HH
#define FIRE_EVENT_HH

#include <queue>

class WinRender;

class Event {
public:
    explicit Event(WinRender const& w);
    Event(int key, int action, int mods);
    Event(double xpos, double ypos);
    void attach(WinRender const& w);

    int key{-1}, action{-1}, mods{-1};
    double xpos{0}, ypos{0};
protected:
    static std::queue<Event> events_;
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    friend class WinRender;
};


#endif //FIRE_EVENT_HH
