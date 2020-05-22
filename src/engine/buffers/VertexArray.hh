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
    VertexArray() : BaseBuffer() {}

public:
    VertexArray(VertexArray&&) = default;
    VertexArray& operator=(VertexArray&&) = default;
    virtual ~VertexArray();
    static VertexArray create();
    void bind() const override;
    void unbind() const override;

    template<typename T, std::size_t D>
    void add_data(std::array<T, D> data, VertexBufferLayout const& layout);

    template<std::size_t D>
    void add_indices(std::array<unsigned, D> indices);
protected:
    VertexBuffer::vec vbs_;
    IndexBuffer::vec ibs_;
};

template<typename T, std::size_t D>
void VertexArray::add_data(std::array<T, D> data, VertexBufferLayout const& layout) {
    auto vb = VertexBuffer::create(data);
    bind();
    vb->bind();
    std::size_t offset = 0u;
    auto const& els = layout.elements();
    for (auto i = 0u; i < els.size(); ++i) {
        auto const& el = els[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.stride(), reinterpret_cast<void*>(offset));
        offset += el.count * gl_sizeof(el.type);
    }
    vb->unbind();
    vbs_.push_back(std::move(vb));
}


template<std::size_t D>
void VertexArray::add_indices(std::array<unsigned, D> indices) {
    ibs_.push_back(IndexBuffer::create(indices));
}


#endif //FIRE_VERTEXARRAY_HH
