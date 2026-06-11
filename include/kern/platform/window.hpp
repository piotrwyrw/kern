// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/properties.hpp>

#include "kern/controls/controls.hpp"

struct GLFWwindow;

namespace kern::platform
{
    class Window
    {
    private:
        const Properties& properties_;
        GLFWwindow* window_;

        std::unique_ptr<controls::InputHandler> input_handler_;

    public:
        explicit Window(const Properties& properties);
        ~Window();

        void handle_events() const;
        void swap_buffers() const;

        [[nodiscard]] GLFWwindow* glfw_handle() const;
        [[nodiscard]] bool should_close() const;
        [[nodiscard]] const controls::InputHandler& input_handler() const;
    };
}
