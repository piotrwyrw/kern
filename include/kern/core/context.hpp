// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/timing.hpp>

#include <memory>

namespace spdlog
{
    class logger;
}

namespace kern
{
    struct Configuration;

    namespace platform
    {
        class Window;
    }

    namespace controls
    {
        class InputHandler;
    }

    class Context
    {
        const Engine& engine_;

        std::unique_ptr<Timing> timing_;
        spdlog::logger& logger_;
        const platform::Window& window_;

        bool shutdown_request_;

        const Configuration& config_;

    public:
        Context(const Engine& engine,
                const platform::Window& window,
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
