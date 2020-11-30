//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXARRAY_HH
#define FIRE_VERTEXARRAY_HH


#include "VertexBuffer.hh"
#include "IndexBuffer.hh"

class VertexArray : public BaseBuffer {
public:
    using ptr = std::shared_ptr<VertexArray>;
public:
    VertexArray();
    VertexArray(VertexArray&&) = default;
    VertexArray& operator=(VertexArray&&) = default;
    virtual ~VertexArray();
    static VertexArray::ptr create();
    void bind() const override;
    void unbind() const override;

    [[nodiscard]] VertexBuffer const* vbo() const { return vb_.get(); }

    [[nodiscard]] IndexBuffer const* ibo() const { return ib_.get(); };

    template<typename Cnt>
    void add_data(Cnt const& data, VertexBufferLayout const& layout);

    template<typename Cnt>
    void add_indices(Cnt const& indices);
protected:
    VertexBuffer::ptr vb_;
    IndexBuffer::ptr ib_;
};

template<typename Cnt>
void VertexArray::add_data(Cnt const& data, VertexBufferLayout const& layout) {
    vb_ = VertexBuffer::create(data);
    bind();
    vb_->layout(layout);
}


template<typename Cnt>
void VertexArray::add_indices(Cnt const& indices) {
    ib_ = IndexBuffer::create(indices);
}


#endif //FIRE_VERTEXARRAY_HH
