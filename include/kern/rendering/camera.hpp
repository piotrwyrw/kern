// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>

namespace kern::rendering
{
    class Camera
    {
        glm::dvec3 position_;
        glm::dvec3 forward_;
        glm::dvec3 backward_{};
        double fov_;

        // Computed values
        glm::dvec3 right_{};
        glm::dvec3 left_{};

        const glm::dvec3 up_ = glm::dvec3(0.0, 1.0, 0.0);
        const glm::dvec3 down_ = -up_;

    public:
        explicit Camera(const glm::dvec3& position, const glm::dvec3& forward, double fov);

        void recompute_direction_vectors();

        void move(const glm::dvec3& direction, double amount);
        void move_forward(double amount);
        void move_backward(double amount);
        void move_right(double amount);
        void move_left(double amount);
        void move_up(double amount);
        void move_down(double amount);

        void set_position(const glm::dvec3& position);
        void set_direction(const glm::dvec3& direction);

        [[nodiscard]] glm::dvec3 get_position() const;
        [[nodiscard]] glm::dvec3 get_forward() const;
        [[nodiscard]] glm::dvec3 get_right() const;
        [[nodiscard]] glm::dvec3 get_left() const;
        [[nodiscard]] glm::dvec3 get_up() const;
    };
}
