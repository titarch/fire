//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXBUFFER_HH
#define FIRE_VERTEXBUFFER_HH


#include <array>
#include "BaseBuffer.hh"

class VertexBuffer : public BaseBuffer {
protected:
    VertexBuffer() : BaseBuffer() {}
    // Create a buffer with VertexBuffer::create

public:
    virtual ~VertexBuffer();
    VertexBuffer& bind() const override;
    VertexBuffer& unbind() const override;

    template<typename T, std::size_t D>
    static VertexBuffer create(std::array<T, D> const& data);
};

template<typename T, std::size_t D>
VertexBuffer VertexBuffer::create(const std::array<T, D>& data) {
    VertexBuffer vb{};
    glGenBuffers(1, &vb.id_);
    glBindBuffer(GL_ARRAY_BUFFER, vb.id_);
    glBufferData(GL_ARRAY_BUFFER, D * sizeof(T), data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vb;
}


#endif //FIRE_VERTEXBUFFER_HH
