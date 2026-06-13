// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>

namespace kern::rendering
{
    class Camera
    {
        glm::vec3 position_;
        glm::vec3 forward_;
        glm::vec3 backward_{};
        float fov_;

        // Computed values
        glm::vec3 right_{};
        glm::vec3 left_{};

        const glm::vec3 up_ = glm::vec3(0, 1, 0);
        const glm::vec3 down_ = -up_;

    public:
        explicit Camera(const glm::vec3& position, const glm::vec3& forward, float fov);

        void recompute_direction_vectors();

        void move(const glm::vec3& direction, float amount);
        void move_forward(float amount);
        void move_backward(float amount);
        void move_right(float amount);
        void move_left(float amount);
        void move_up(float amount);
        void move_down(float amount);

        void set_position(const glm::vec3& position);
        void set_direction(const glm::vec3& direction);

        [[nodiscard]] glm::vec3 get_position() const;
        [[nodiscard]] glm::vec3 get_forward() const;
        [[nodiscard]] glm::vec3 get_right() const;
        [[nodiscard]] glm::vec3 get_left() const;
        [[nodiscard]] glm::vec3 get_up() const;
    };
}
