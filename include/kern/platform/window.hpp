// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/configuration.hpp>
#include <kern/controls/controls.hpp>

KERN_FORWARD_DECLARE_ENGINE_;

KERN_FORWARD_DECLARE_GLFW_WINDOW_;

namespace kern::platform
{
    class Window
    {
        const Configuration& config_;
        GLFWwindow* window_;

        std::unique_ptr<controls::InputHandler> input_handler_;

        void handle_events() const;
        void swap_buffers() const;

        friend class kern::Engine;

    public:
        explicit Window(const Configuration& config);
        ~Window();

        [[nodiscard]] GLFWwindow* glfw_handle() const;
        [[nodiscard]] bool should_close() const;
        [[nodiscard]] const controls::InputHandler& input_handler() const;
    };
}
