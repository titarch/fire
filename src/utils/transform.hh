//
// Created by bparsy on 6/5/20.
//

#ifndef FIRE_TRANSFORM_HH
#define FIRE_TRANSFORM_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Vec {
public:
    Vec(float x, float y, float z) : vec_(x, y, z) {}

    Vec(const float v[3]) : vec_(v[0], v[1], v[2]) {}

    Vec() : vec_(0, 0, 0) {}

    operator glm::vec3() const { return vec_; };

    glm::vec3 vec() const { return vec_; }

    float* data() { return &vec_[0]; }

    float operator[](std::size_t idx) const { return vec_[idx]; }

    static Vec zero() { return {0, 0, 0}; }

    static Vec left() { return {-1, 0, 0}; }

    static Vec right() { return {1, 0, 0}; }

    static Vec down() { return {0, -1, 0}; }

    static Vec up() { return {0, 1, 0}; }

    static Vec back() { return {0, 0, -1}; }

    static Vec forward() { return {0, 0, 1}; }

protected:
    glm::vec3 vec_;
};

class Mat {
public:
    Mat() : mat_(1.f) {}

    Mat(glm::mat4 const& mat) : mat_(mat) {}

    static inline Mat id() { return {}; }

    static inline Mat perspective(float fov, float ratio, float near, float far) {
        return glm::perspective(fov, ratio, near, far);
    }

    static inline Mat camera(Vec const& eye, Vec const& center, Vec const& up) {
        return glm::lookAt(eye.vec(), center.vec(), up.vec());
    }

    const float* data() const { return &mat_[0][0]; }

    inline Mat& translate(Vec const& v) {
        mat_ = glm::translate(mat_, v.vec());
        return *this;
    }

    inline Mat& rotate(float angle, Vec const& v) {
        mat_ = glm::rotate(mat_, angle, v.vec());
        return *this;
    }

protected:
    glm::mat4 mat_;
};


#endif //FIRE_TRANSFORM_HH
