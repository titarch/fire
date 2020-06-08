//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXBUFFER_HH
#define FIRE_VERTEXBUFFER_HH


#include <array>
#include <memory>
#include <vector>
#include "BaseBuffer.hh"

class VertexBuffer : public BaseBuffer {
public:
    using ptr = std::unique_ptr<VertexBuffer>;
    using vec = std::vector<ptr>;
public:
    VertexBuffer() : BaseBuffer() {}

    VertexBuffer(VertexBuffer&&) = default;
    virtual ~VertexBuffer();
    void bind() const override;
    void unbind() const override;

    template<typename T>
    static VertexBuffer::ptr create(const T* data, std::size_t size);

    template<typename T, std::size_t D>
    static ptr create(std::array<T, D> const& data);

    template<typename T>
    static ptr create(std::vector<T> const& data);
};

template<typename T>
VertexBuffer::ptr VertexBuffer::create(const T* data, std::size_t size) {
    auto vb = std::make_unique<VertexBuffer>();
    glGenBuffers(1, &vb->id_);
    vb->bind();
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), data, GL_STATIC_DRAW);
    return vb;
}

template<typename T, std::size_t D>
VertexBuffer::ptr VertexBuffer::create(const std::array<T, D>& data) {
    return create(data.data(), D);
}

template<typename T>
VertexBuffer::ptr VertexBuffer::create(const std::vector<T>& data) {
    return create(data.data(), data.size());
}

#endif //FIRE_VERTEXBUFFER_HH
