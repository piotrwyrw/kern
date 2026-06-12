// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/context.hpp>
#include <kern/platform/window.hpp>

#include "spdlog/logger.h"

namespace kern
{
    Context::Context(const platform::Window& window, spdlog::logger& logger)
        : timing_(std::make_unique<Timing>()),
          logger_(logger),
          window_(window),
          should_close_(false)
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

    bool Context::should_close() const
    {
        return window_.should_close() || should_close_;
    }

    void Context::request_shutdown()
    {
        should_close_ = true;
    }
}
