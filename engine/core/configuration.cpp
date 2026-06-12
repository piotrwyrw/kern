// This file is part of Kern, an open-source game development library.
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
            .fullscreen = true,
            .antialiasing_samples = DefaultAntialiasingSamples,
            .cursor_mode = CursorMode::Disabled
        };
    }
}
