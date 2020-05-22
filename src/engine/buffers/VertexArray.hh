//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXARRAY_HH
#define FIRE_VERTEXARRAY_HH


#include "VertexBuffer.hh"
#include "VertexBufferLayout.hh"

class VertexArray : public BaseBuffer {
protected:
    VertexArray() : BaseBuffer() {}

public:
    static VertexArray create();
    virtual ~VertexArray();
    void bind() const override;
    void unbind() const override;
    VertexArray& add_buffer(VertexBuffer const& vb, VertexBufferLayout const& layout);
};


#endif //FIRE_VERTEXARRAY_HH
