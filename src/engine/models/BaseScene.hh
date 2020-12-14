//
// Created by bparsy on 11/30/20.
//

#ifndef FIRE_BASESCENE_HH
#define FIRE_BASESCENE_HH

#include <GL/glew.h>
#include "../WinRender.hh"
#include "../../utils/transform.hh"

enum class Dir {
    FORWARD,
    LEFT,
    BACK,
    RIGHT,
    UP,
    DOWN,
};

enum class Norm {
    UP,
    RIGHT,
};

template<typename SceneType>
class BaseScene {
public:
    explicit BaseScene(WinRender& wr);

    SceneType& cthis();
    SceneType& cthis() const;

    virtual void use() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    void step();

    SceneType& set_light_position(Vec const& position);
    SceneType& set_perspective(float fov, float ratio, float near, float far);
    SceneType& set_camera(Vec const& position, Vec const& direction);

    [[nodiscard]] const WinRender& win() const;
    [[nodiscard]] const Vec& position() const;
    [[nodiscard]] const Mat& projection() const;
    [[nodiscard]] const Vec& light_position() const;
    [[nodiscard]] const Vec& direction() const;
    SceneType& move(float amount, Vec const& direction);
    SceneType& move(float amount, Dir direction);
    SceneType& turn(float angle, Vec const& normal);
    SceneType& turn(float angle, Norm normal);
    [[nodiscard]] Mat view() const;

protected:
    WinRender& wr_;
    Vec light_position_;
    Mat projection_;
    Vec position_, direction_;
};

template<typename SceneType>
BaseScene<SceneType>::BaseScene(WinRender& wr) :
        wr_(wr), light_position_(), projection_(), position_(), direction_() {}

template<typename SceneType>
void BaseScene<SceneType>::step() {
    update();
    wr_.update_time();
    wr_.clear();
    render();
    wr_.display();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::cthis() {
    return static_cast<SceneType&>(*this);
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::cthis() const {
    return static_cast<SceneType const&>(*this);
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::set_light_position(Vec const& position) {
    light_position_ = position;
    return cthis();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::set_perspective(float fov, float ratio, float near, float far) {
    projection_ = Mat::perspective(fov, ratio, near, far);
    return cthis();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::set_camera(const Vec& position, const Vec& direction) {
    position_ = position;
    direction_ = direction;
    return cthis();
}

template<typename SceneType>
const WinRender& BaseScene<SceneType>::win() const {
    return wr_;
}

template<typename SceneType>
const Mat& BaseScene<SceneType>::projection() const {
    return projection_;
}

template<typename SceneType>
const Vec& BaseScene<SceneType>::light_position() const {
    return light_position_;
}

template<typename SceneType>
const Vec& BaseScene<SceneType>::position() const {
    return position_;
}

template<typename SceneType>
const Vec& BaseScene<SceneType>::direction() const {
    return direction_;
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::move(float amount, const Vec& direction) {
    position_ += direction * amount * wr_.dt();
    return cthis();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::move(float amount, Dir direction) {
    switch (direction) {
        case Dir::FORWARD:
            return move(amount, direction_);
        case Dir::LEFT:
            return move(amount, Vec::up() ^ direction_);
        case Dir::BACK:
            return move(-amount, direction_);
        case Dir::RIGHT:
            return move(-amount, Vec::up() ^ direction_);
        case Dir::UP:
            return move(amount, Vec::up());
        case Dir::DOWN:
            return move(-amount, Vec::up());
    }
    return cthis();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::turn(float angle, const Vec& normal) {
    direction_.rotate(angle * wr_.dt(), normal);
    return cthis();
}

template<typename SceneType>
SceneType& BaseScene<SceneType>::turn(float angle, Norm normal) {
    switch (normal) {
        case Norm::UP:
            return turn(angle, Vec::up());
        case Norm::RIGHT:
            // This is to avoid gimbal lock issues, namely 180 jumps when looking up or down
            if ((angle < 0 && direction_[1] > 0.99) || (angle > 0 && direction_[1] < -0.99)) break;
            return turn(angle, Vec::up() ^ direction_);
    }
    return cthis();
}

template<typename SceneType>
Mat BaseScene<SceneType>::view() const {
    return Mat::camera(position_, position_ + direction_, Vec::up());
}

#endif //FIRE_BASESCENE_HH
