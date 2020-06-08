//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_INDEXBUFFER_HH
#define FIRE_INDEXBUFFER_HH


#include <array>
#include <memory>
#include <vector>
#include "BaseBuffer.hh"

class IndexBuffer : public BaseBuffer {
public:
    using ptr = std::unique_ptr<IndexBuffer>;
    using vec = std::vector<ptr>;
public:
    explicit IndexBuffer(std::size_t count) : BaseBuffer(), count_(count) {}

    IndexBuffer(IndexBuffer&&) = default;
    virtual ~IndexBuffer();
    void bind() const override;
    void unbind() const override;
    [[nodiscard]] std::size_t count() const;
    
    static ptr create(const unsigned* indices, std::size_t size);
    template<std::size_t D>
    static ptr create(std::array<unsigned, D> const& indices);
    static ptr create(std::vector<unsigned> const& indices);
protected:
    std::size_t count_;
};

template<std::size_t D>
IndexBuffer::ptr IndexBuffer::create(const std::array<unsigned, D>& indices) {
    return create(indices.data(), D);
}

#endif //FIRE_INDEXBUFFER_HH
