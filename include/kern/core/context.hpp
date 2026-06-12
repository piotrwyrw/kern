// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <memory>

#include <kern/core/timing.hpp>
#include <kern/_internal.hpp>

KERN_FORWARD_DECLARE_WINDOW_;

KERN_FORWARD_DECLARE_CONFIGURATION_;

KERN_FORWARD_DECLARE_INPUT_HANDLER_;

KERN_FORWARD_DECLARE_SPDLOG_LOGGER_;

namespace kern
{
    class Context
    {
        std::unique_ptr<Timing> timing_;
        spdlog::logger& logger_;
        const platform::Window& window_;

        bool shutdown_request_;

        const Configuration& config_;

    public:
        Context(const platform::Window& window,
                const Configuration& config,
                spdlog::logger& logger);

        [[nodiscard]] spdlog::logger& logger() const;

        [[nodiscard]] Timing& get_timing() const;
        [[nodiscard]] const controls::InputHandler& get_input_handler() const;

        [[nodiscard]] const Configuration& get_config() const;

        [[nodiscard]] bool is_shutdown_requested() const;

        void request_shutdown();
    };
}
