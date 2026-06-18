// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>

#include <glm/vec2.hpp>

namespace kern
{
    namespace platform
    {
        class Window;
    }

    namespace controls
    {
        enum class Key : int;

        class InputHandler
        {
            const platform::Window& window_;
            GLFWwindow* window_handle_;

            bool keys_curr_[GLFW_KEY_LAST + 1] = {};
            bool keys_prev_[GLFW_KEY_LAST + 1] = {};

            bool is_first_cursor_event_;
            glm::vec2 cursor_curr_;
            glm::vec2 cursor_prev_;

            bool window_just_resized_;
            int window_width_;
            int window_height_;

            static void key_callback(GLFWwindow* window,
                                     int key,
                                     int scancode,
                                     int action,
                                     int mods);

            static void cursor_callback(GLFWwindow* window,
                                        double xpos,
                                        double ypos);

            static void size_callback(GLFWwindow* window,
                                      int width,
                                      int height);

            void swap_states();

            friend class kern::platform::Window;

        public:
            explicit InputHandler(platform::Window& window);
            ~InputHandler();

            InputHandler(const InputHandler&) = delete;
            InputHandler& operator=(const InputHandler&) = delete;

            /* True if the key was just pressed. False if it was released or held */
            [[nodiscard]] bool is_key_pressed(Key key) const;

            /* True if the key was held for at least 2 frames. False if it was just pressed or
             * released */
            [[nodiscard]] bool is_key_held(Key key) const;

            /* True if the key is currently pressed */
            [[nodiscard]] bool is_key_down(Key key) const;


            /* True if the key was just released. False if it was pressed or held */
            [[nodiscard]] bool is_key_released(Key key) const;

            /* True if the key was not pressed (up) for at least 2 frames. False if it was just
             * released or pressed */
            [[nodiscard]] bool is_key_held_up(Key key) const;

            /* True if the key is not currently pressed */
            [[nodiscard]] bool is_key_up(Key key) const;


            [[nodiscard]] glm::vec2 cursor_position() const;

            [[nodiscard]] glm::vec2 cursor_direction() const;

            [[nodiscard]] glm::vec2 cursor_delta() const;

            [[nodiscard]] float cursor_speed() const;

            /**
             * @return True if the cursor moved during this frame
             */
            [[nodiscard]] bool cursor_moved() const;


            [[nodiscard]] bool just_resized() const;

            [[nodiscard]] int get_window_width() const;

            [[nodiscard]] int get_window_height() const;
        };
    }
}
