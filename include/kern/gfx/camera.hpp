// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>

namespace kern
{
    class Engine;

    namespace gfx
    {
        class Camera
        {
            const Engine& engine_;

            float fov_;
            float z_near_ = 0.1;
            float z_far_ = 1000.0f;
            glm::vec3 position_;
            glm::vec3 forward_;

            glm::mat4 projection_mat_;
            bool projection_mat_dirty;

            glm::mat4 view_mat_;
            bool view_mat_dirty_;

            glm::vec3 backward_{};

            // Computed values
            glm::vec3 right_{};
            glm::vec3 left_{};

            const glm::vec3 up_ = glm::vec3(0, 1, 0);
            const glm::vec3 down_ = -up_;

        public:
            explicit Camera(const Engine& engine,
                            const glm::vec3& position,
                            const glm::vec3& forward,
                            float fov,
                            float z_near,
                            float z_far);

            explicit Camera(const Engine& engine,
                            const glm::vec3& position,
                            const glm::vec3& forward,
                            float fov,
                            float z_near);

            explicit Camera(const Engine& engine,
                            const glm::vec3& position,
                            const glm::vec3& forward,
                            float fov);

            void recompute_direction_vectors();

            void recompute_projection_matrix();
            void recompute_view_matrix();

            void move(const glm::vec3& direction, float t);
            void move_forward(float t);
            void move_backward(float t);
            void move_right(float t);
            void move_left(float t);
            void move_up(float t);
            void move_down(float t);

            void set_position(const glm::vec3& position);
            void set_direction(const glm::vec3& direction);
            void set_direction_look_at(const glm::vec3& center);

            void set_fov(float fov);

            [[nodiscard]] const glm::mat4& get_projection_matrix();
            [[nodiscard]] bool is_projection_matrix_dirty() const;

            [[nodiscard]] const glm::mat4& get_view_matrix();
            [[nodiscard]] bool is_view_matrix_dirty() const;

            [[nodiscard]] const glm::vec3& get_position() const;
            [[nodiscard]] const glm::vec3& get_forward() const;
            [[nodiscard]] const glm::vec3& get_right() const;
            [[nodiscard]] const glm::vec3& get_left() const;
            [[nodiscard]] const glm::vec3& get_up() const;
        };
    }
}
