//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXARRAY_HH
#define FIRE_VERTEXARRAY_HH


#include "VertexBuffer.hh"
#include "VertexBufferLayout.hh"
#include "IndexBuffer.hh"

class VertexArray : public BaseBuffer {
protected:
    VertexArray() : BaseBuffer(), vb_{}, ib_{} {}

public:
    VertexArray(VertexArray&&) = default;
    VertexArray& operator=(VertexArray&&) = default;
    virtual ~VertexArray();
    static VertexArray create();
    void bind() const override;
    void unbind() const override;

    [[nodiscard]] VertexBuffer const& vbo() const { return *vb_; }

    [[nodiscard]] IndexBuffer const& ibo() const { return *ib_; };

    template<typename T, std::size_t D>
    void add_data(std::array<T, D> data, VertexBufferLayout const& layout);

    template<std::size_t D>
    void add_indices(std::array<unsigned, D> indices);
protected:
    VertexBuffer::ptr vb_;
    IndexBuffer::ptr ib_;
};

template<typename T, std::size_t D>
void VertexArray::add_data(std::array<T, D> data, VertexBufferLayout const& layout) {
    vb_ = VertexBuffer::create(data);
    bind();
    vb_->bind();
    std::size_t offset = 0u;
    auto const& els = layout.elements();
    for (auto i = 0u; i < els.size(); ++i) {
        auto const& el = els[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.stride(), reinterpret_cast<void*>(offset));
        offset += el.count * gl_sizeof(el.type);
    }
    vb_->unbind();
}


template<std::size_t D>
void VertexArray::add_indices(std::array<unsigned, D> indices) {
    ib_ = IndexBuffer::create(indices);
}


#endif //FIRE_VERTEXARRAY_HH
