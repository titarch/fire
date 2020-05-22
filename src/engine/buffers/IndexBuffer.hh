//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_INDEXBUFFER_HH
#define FIRE_INDEXBUFFER_HH


#include <array>
#include "BaseBuffer.hh"

class IndexBuffer : public BaseBuffer {
protected:
    IndexBuffer(std::size_t count) : BaseBuffer(), count_(count) {}
    // Create a buffer with IndexBuffer::create

public:
    virtual ~IndexBuffer();
    void bind() const override;
    void unbind() const override;

    template<std::size_t D>
    static IndexBuffer create(std::array<unsigned, D> const& indices);
protected:
    std::size_t count_;
};

template<std::size_t D>
IndexBuffer IndexBuffer::create(const std::array<unsigned, D>& indices) {
    IndexBuffer ib(D);
    glGenBuffers(1, &ib.id_);
    ib.bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, D * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
    ib.unbind();
    return ib;
}

#endif //FIRE_INDEXBUFFER_HH
