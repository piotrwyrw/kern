// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/configuration.hpp>

namespace kern
{
    Configuration default_config(std::string title)
    {
        return Configuration{
            .title = std::move(title),
            .window_resizable = false,
            .window_decorated = true,
            .window_transparency = false,
            .fullscreen = true,
            .antialiasing_samples = DefaultAntialiasingSamples,
            .cursor_mode = CursorMode::Disabled
        };
    }
}
