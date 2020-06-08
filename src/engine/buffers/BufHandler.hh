//
// Created by bparsy on 5/17/20.
//

#ifndef FIRE_BUFHANDLER_HH
#define FIRE_BUFHANDLER_HH

#include <GL/glew.h>
#include <vector>
#include <array>
#include "VertexBuffer.hh"
#include "IndexBuffer.hh"
#include "VertexArray.hh"

class BufHandler {
public:
    BufHandler() = delete;

    static VertexArray::ptr make_vao() {
        return VertexArray::create();
    }

    static VertexBufferLayout make_layout() {
        return VertexBufferLayout();
    }
};


#endif //FIRE_BUFHANDLER_HH
