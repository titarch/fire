//
// Created by bparsy on 11/30/20.
//

#ifndef FIRE_STORAGEBUFFER_HH
#define FIRE_STORAGEBUFFER_HH


#include <memory>
#include <vector>
#include "VertexBuffer.hh"

class StorageBuffer : public VertexBuffer {
public:
    using ptr = std::unique_ptr<StorageBuffer>;
    using vec = std::vector<ptr>;
public:
    explicit StorageBuffer(std::size_t size) : VertexBuffer(size) {}

    StorageBuffer(StorageBuffer&&) = default;
    ~StorageBuffer() override;
    void bind() const override;
    void unbind() const override;
    void base_index(GLuint index) const;
    void vb_bind() const;
    void vb_unbind() const;

    template<typename T>
    static StorageBuffer::ptr create(const T* data, std::size_t size);

    template<typename T, std::size_t D>
    static ptr create(std::array<T, D> const& data);

    template<typename T>
    static ptr create(std::vector<T> const& data);
};


template<typename T>
StorageBuffer::ptr StorageBuffer::create(const T* data, std::size_t size) {
    auto sb = std::make_unique<StorageBuffer>(size * sizeof(T));
    glGenBuffers(1, &sb->id_);
    sb->bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, size * sizeof(T), data, GL_DYNAMIC_COPY);
    return sb;
}

template<typename T, std::size_t D>
StorageBuffer::ptr StorageBuffer::create(const std::array<T, D>& data) {
    return create(data.data(), D);
}

template<typename T>
StorageBuffer::ptr StorageBuffer::create(const std::vector<T>& data) {
    return create(data.data(), data.size());
}


#endif //FIRE_STORAGEBUFFER_HH
