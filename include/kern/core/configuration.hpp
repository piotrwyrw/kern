// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <string>

namespace kern
{
    enum class CursorMode
    {
        Enabled,
        Hidden,
        Disabled
    };

    struct Configuration
    {
        std::string title = "Kern Game";
        int window_width = 1000;
        int window_height = 700;
        bool window_resizable = false;
        bool fullscreen = false;
        int antialiasing_samples = 0;
        CursorMode cursor_mode = CursorMode::Enabled;
    };

    constexpr int DefaultAntialiasingSamples = 4;

    [[nodiscard]] Configuration default_config(std::string title);
}
