//
// Created by bparsy on 6/5/20.
//

#ifndef FIRE_TRANSFORM_HH
#define FIRE_TRANSFORM_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Vec {
public:
    Vec(float x, float y, float z) : vec_(x, y, z) {}

    Vec(const float v[3]) : vec_(v[0], v[1], v[2]) {}

    Vec() : vec_(0, 0, 0) {}

    Vec(glm::vec3 const& vec) : vec_(vec) {}

    operator glm::vec3() const { return vec_; };

    glm::vec3 vec() const { return vec_; }

    float* data() { return &vec_[0]; }

    float operator[](std::size_t idx) const { return vec_[idx]; }

    static Vec one() { return {1, 1, 1}; }

    static Vec zero() { return {0, 0, 0}; }

    static Vec left() { return {-1, 0, 0}; }

    static Vec right() { return {1, 0, 0}; }

    static Vec down() { return {0, -1, 0}; }

    static Vec up() { return {0, 1, 0}; }

    static Vec back() { return {0, 0, -1}; }

    static Vec forward() { return {0, 0, 1}; }

    Vec& rotate(float angle, Vec const& dir) {
        vec_ = glm::rotate(vec_, angle, dir.vec_);
        return *this;
    }

    Vec& operator+=(float rhs) {
        vec_ += rhs;
        return *this;
    }

    inline friend Vec operator+(Vec lhs, float rhs) {
        lhs += rhs;
        return lhs;
    }
    
    Vec& operator*=(float rhs) {
        vec_ *= rhs;
        return *this;
    }

    inline friend Vec operator*(Vec lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    Vec& operator+=(Vec const& rhs) {
        vec_ += rhs.vec_;
        return *this;
    }
    
    Vec& operator-=(Vec const& rhs) {
        vec_ -= rhs.vec_;
        return *this;
    }

    inline friend Vec operator+(Vec lhs, Vec const& rhs) {
        lhs += rhs;
        return lhs;
    }

    Vec& operator^=(Vec const& rhs) {
        vec_ = glm::cross(vec_, rhs.vec_);
        return *this;
    }

    inline friend Vec operator^(Vec lhs, Vec const& rhs) {
        lhs ^= rhs;
        return lhs;
    }

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

    const glm::mat4& mat() const { return mat_; };

    inline Mat& translate(Vec const& v) {
        mat_ = glm::translate(mat_, v.vec());
        return *this;
    }

    inline Mat& rotate(float angle, Vec const& v) {
        mat_ = glm::rotate(mat_, angle, v.vec());
        return *this;
    }

    inline Mat& rescale(Vec const& v) {
        mat_ = glm::scale(mat_, v.vec());
        return *this;
    }

    inline Mat without_translation() const {
        Mat copy = Mat(*this);
        for (auto i = 0u; i < 3; ++i)
            copy.mat_[3][i] = 0;
        return copy;
    }

    Mat& operator*=(Mat const& rhs) {
        mat_ *= rhs.mat_;
        return *this;
    }

    inline friend Mat operator*(Mat lhs, Mat const& rhs) {
        lhs *= rhs;
        return lhs;
    }

protected:
    glm::mat4 mat_;
};


#endif //FIRE_TRANSFORM_HH
