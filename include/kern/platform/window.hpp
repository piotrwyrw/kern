// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/configuration.hpp>
#include <kern/controls/input_handler.hpp>

namespace kern
{
    class Engine;

    namespace platform
    {
        class Window
        {
            int initial_width_;
            int initial_height_;

            GLFWwindow* window_;

            std::unique_ptr<controls::InputHandler> input_handler_;

            void handle_events() const;
            void swap_buffers() const;

            friend class kern::Engine;

        public:
            const Configuration& config_;

            explicit Window(const Configuration& config);
            ~Window();

            [[nodiscard]] int get_initial_width() const;
            [[nodiscard]] int get_initial_height() const;

            [[nodiscard]] GLFWwindow* glfw_handle() const;
            [[nodiscard]] bool should_close() const;
            [[nodiscard]] const controls::InputHandler& input_handler() const;
        };
    }
}
