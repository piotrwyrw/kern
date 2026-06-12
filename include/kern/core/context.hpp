// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <memory>

#include "timing.hpp"
#include "spdlog/spdlog.h"

namespace kern::platform
{
    class Window;
}

namespace kern::controls
{
    class InputHandler;
}

namespace spdlog
{
    class logger;
}

namespace kern
{
    class Context
    {
        std::unique_ptr<Timing> timing_;
        spdlog::logger& logger_;
        const platform::Window& window_;
        bool should_close_;

    public:
        Context(const platform::Window& window, spdlog::logger& logger);

        [[nodiscard]] spdlog::logger& logger() const;

        [[nodiscard]] Timing& get_timing() const;
        [[nodiscard]] const controls::InputHandler& get_input_handler() const;

        [[nodiscard]] bool should_close() const;
        void request_shutdown();
    };
}
