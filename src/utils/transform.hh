//
// Created by bparsy on 6/5/20.
//

#ifndef FIRE_TRANSFORM_HH
#define FIRE_TRANSFORM_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mat {
public:
    Mat() : mat_(1.f) {}

    Mat(glm::mat4 const& mat) : mat_(mat) {}

    static inline Mat id() { return {}; }

    static inline Mat perspective(float fov, float ratio, float near, float far) {
        return glm::perspective(fov, ratio, near, far);
    }

    float* data() { return &mat_[0][0]; }

    inline Mat& translate(float x, float y, float z) {
        mat_ = glm::translate(mat_, glm::vec3(x, y, z));
        return *this;
    }

    inline Mat& rotate(float angle, float x, float y, float z) {
        mat_ = glm::rotate(mat_, angle, glm::vec3(x, y, z));
        return *this;
    }

protected:
    glm::mat4 mat_;
};


class Vec {
public:
    Vec(float x, float y, float z) : vec_(x, y, z) {}

    static Vec left() { return {-1, 0, 0}; }

    static Vec right() { return {1, 0, 0}; }

    static Vec down() { return {0, -1, 0}; }

    static Vec up() { return {0, 1, 0}; }

    static Vec back() { return {0, 0, -1}; }

    static Vec forward() { return {0, 0, 1}; }


protected:
    glm::vec3 vec_;
};

#endif //FIRE_TRANSFORM_HH
