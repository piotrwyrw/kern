// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/context.hpp>
#include <kern/platform/window.hpp>

#include <spdlog/logger.h>

namespace kern
{
    Context::Context(const Engine& engine,
                     const platform::Window& window,
                     const Configuration& config,
                     spdlog::logger& logger)
        : engine_(engine),
          timing_(std::make_unique<Timing>()),
          logger_(logger),
          window_(window),
          shutdown_request_(false),
          config_(config)
    {
    }

    spdlog::logger& Context::logger() const
    {
        return logger_;
    }

    Timing& Context::get_timing() const
    {
        return *timing_;
    }

    const controls::InputHandler& Context::get_input_handler() const
    {
        return window_.input_handler();
    }

    const Configuration& Context::get_config() const
    {
        return config_;
    }

    bool Context::is_shutdown_requested() const
    {
        return shutdown_request_;
    }

    void Context::request_shutdown()
    {
        shutdown_request_ = true;
    }
}
