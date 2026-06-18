// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gfx/camera.hpp>
#include <kern/core/engine.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace kern::gfx
{
    Camera::Camera(const Engine& engine, const glm::vec3& position,
                   const glm::vec3& forward, float fov, float z_near, float z_far)
        : engine_(engine),
          fov_(fov),
          z_near_(z_near),
          z_far_(z_far),
          position_(position),
          forward_(glm::normalize(forward)),
          projection_mat_(glm::identity<glm::mat4>()),
          projection_mat_dirty(true),
          view_mat_(glm::identity<glm::mat4>()),
          view_mat_dirty_(true)
    {
        recompute_direction_vectors();
    }

    Camera::Camera(const Engine& engine, const glm::vec3& position, const glm::vec3& forward,
                   float fov, float z_near)
        : Camera(engine, position, forward, fov, z_near, 1000.0f)
    {
    }

    Camera::Camera(const Engine& engine, const glm::vec3& position, const glm::vec3& forward,
                   float fov)
        : Camera(engine, position, forward, fov, 0.1f, 1000.0f)
    {
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

    void Camera::recompute_projection_matrix()
    {
        const auto& input_handler = engine_.get_window().input_handler();
        const auto vp_width = input_handler.get_window_width();
        const auto vp_height = input_handler.get_window_height();

        projection_mat_ = glm::perspective(
            fov_,
            static_cast<float>(vp_width) / static_cast<float>(vp_height),
            z_near_,
            z_far_
        );
    }

    void Camera::recompute_view_matrix()
    {
        view_mat_ = glm::lookAt(position_, position_ + forward_, up_);
    }

    void Camera::move(const glm::vec3& direction, const float t)
    {
        position_ += direction * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_forward(const float t)
    {
        position_ += forward_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_backward(const float t)
    {
        position_ += backward_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_right(const float t)
    {
        position_ += right_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_left(const float t)
    {
        position_ += left_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_up(const float t)
    {
        position_ += up_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::move_down(const float t)
    {
        position_ += down_ * t;
        view_mat_dirty_ = true;
    }

    void Camera::set_position(const glm::vec3& position)
    {
        position_ = position;
        view_mat_dirty_ = true;
    }

    void Camera::set_direction(const glm::vec3& direction)
    {
        forward_ = glm::normalize(direction);
        recompute_direction_vectors();
        view_mat_dirty_ = true;
    }

    void Camera::set_direction_look_at(const glm::vec3& center)
    {
        forward_ = glm::normalize(center - position_);
        view_mat_dirty_ = true;
    }

    void Camera::set_fov(const float fov)
    {
        fov_ = fov;
        projection_mat_dirty = true;
    }

    const glm::mat4& Camera::get_projection_matrix()
    {
        if (projection_mat_dirty)
        {
            recompute_projection_matrix();
        }

        return projection_mat_;
    }

    bool Camera::is_projection_matrix_dirty() const
    {
        return projection_mat_dirty;
    }

    const glm::mat4& Camera::get_view_matrix()
    {
        if (view_mat_dirty_)
        {
            recompute_view_matrix();
        }

        return view_mat_;
    }

    bool Camera::is_view_matrix_dirty() const
    {
        return view_mat_dirty_;
    }

    const glm::vec3& Camera::get_position() const
    {
        return position_;
    }

    const glm::vec3& Camera::get_forward() const
    {
        return forward_;
    }

    const glm::vec3& Camera::get_right() const
    {
        return right_;
    }

    const glm::vec3& Camera::get_left() const
    {
        return left_;
    }

    const glm::vec3& Camera::get_up() const
    {
        return up_;
    }
}
