//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_BASEBUFFER_HH
#define FIRE_BASEBUFFER_HH

#include <GL/glew.h>

class BaseBuffer {
public:
    BaseBuffer() : id_(0) {}
    virtual ~BaseBuffer() = default;

    virtual BaseBuffer& bind() = 0;
    virtual BaseBuffer& unbind() = 0;
protected:
    GLuint id_;
};


#endif //FIRE_BASEBUFFER_HH
