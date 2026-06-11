// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/context.hpp>
#include <kern/platform/window.hpp>

kern::Context::Context(const platform::Window& window)
    : window_(window),
      timing_(std::make_unique<Timing>()),
      should_close_(false)
{
}

kern::Timing& kern::Context::get_timing() const
{
    return *timing_;
}

const kern::controls::InputHandler& kern::Context::get_input_handler() const
{
    return window_.input_handler();
}

bool kern::Context::should_close() const
{
    return window_.should_close() || should_close_;
}

void kern::Context::request_shutdown()
{
    should_close_ = true;
}
