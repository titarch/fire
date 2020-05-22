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
    VertexArray(VertexArray&&) = default;
    VertexArray& operator=(VertexArray&&) = default;
    virtual ~VertexArray();
    static VertexArray create();
    void bind() const override;
    void unbind() const override;
    void add_buffer(VertexBuffer::ptr vb, VertexBufferLayout const& layout);
protected:
    VertexBuffer::vec vbs_;
};


#endif //FIRE_VERTEXARRAY_HH
