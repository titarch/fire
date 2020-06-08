//
// Created by bparsy on 5/22/20.
//

#ifndef FIRE_VERTEXBUFFERLAYOUT_HH
#define FIRE_VERTEXBUFFERLAYOUT_HH

#include <GL/glew.h>
#include <vector>
#include <stdexcept>

struct VertexBufferElement {
    GLenum type;
    GLuint count;
    GLboolean normalized;

    VertexBufferElement(GLenum type, GLuint count, GLbyte normalized) : type(type), count(count),
                                                                        normalized(normalized) {}
};

constexpr std::size_t gl_sizeof(GLenum type) {
    switch (type) {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
        default:
            break;
    }
    throw std::invalid_argument("gl_sizeof: unknown type");
}

class VertexBufferLayout {
public:
    VertexBufferLayout() : elements_{}, stride_(0) {}

    [[nodiscard]] std::vector<VertexBufferElement> elements() const { return elements_; }

    [[nodiscard]] std::size_t stride() const { return stride_; }

    template<GLenum TYPE>
    VertexBufferLayout& add_element(unsigned count);

    struct Common {
        static VertexBufferLayout empty() {
            return {};
        }

        static VertexBufferLayout F2D() {
            return empty().add_element<GL_FLOAT>(2);
        }

        static VertexBufferLayout F3D() {
            return empty().add_element<GL_FLOAT>(3);
        }

        static VertexBufferLayout F3DN() {
            return F3D().add_element<GL_FLOAT>(3);
        }
    };
protected:
    std::vector<VertexBufferElement> elements_;
    std::size_t stride_;
};

template<GLenum TYPE>
VertexBufferLayout& VertexBufferLayout::add_element(unsigned count) {
    elements_.emplace_back(TYPE, count, TYPE == GL_UNSIGNED_BYTE ? GL_TRUE : GL_FALSE);
    stride_ += count * gl_sizeof(TYPE);
    return *this;
}


#endif //FIRE_VERTEXBUFFERLAYOUT_HH
