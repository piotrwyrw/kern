// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/rendering/camera.hpp>

namespace kern::rendering
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const float fov)
        : position_(position),
          forward_(glm::normalize(forward)),
          fov_(fov)
    {
        recompute_direction_vectors();
    }

    void Camera::recompute_direction_vectors()
    {
        // Right = Forward x Up
        const glm::dvec3 cross = glm::cross(forward_, up_);
        const glm::dvec3 right = glm::normalize(cross);
        const glm::dvec3 left = -right;

        right_ = right;
        left_ = left;
        backward_ = -forward_;
    }

    void Camera::move(const glm::vec3& direction, const float amount)
    {
        position_ += direction * amount;
    }

    void Camera::move_forward(const float amount)
    {
        position_ += forward_ * amount;
    }

    void Camera::move_backward(const float amount)
    {
        position_ += backward_ * amount;
    }

    void Camera::move_right(const float amount)
    {
        position_ += right_ * amount;
    }

    void Camera::move_left(const float amount)
    {
        position_ += left_ * amount;
    }

    void Camera::move_up(const float amount)
    {
        position_ += up_ * amount;
    }

    void Camera::move_down(const float amount)
    {
        position_ += down_ * amount;
    }

    void Camera::set_position(const glm::vec3& position)
    {
        position_ = position;
    }

    void Camera::set_direction(const glm::vec3& direction)
    {
        forward_ = glm::normalize(direction);
        recompute_direction_vectors();
    }

    glm::vec3 Camera::get_position() const
    {
        return position_;
    }

    glm::vec3 Camera::get_forward() const
    {
        return forward_;
    }

    glm::vec3 Camera::get_right() const
    {
        return right_;
    }

    glm::vec3 Camera::get_left() const
    {
        return left_;
    }

    glm::vec3 Camera::get_up() const
    {
        return up_;
    }
}
