// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <string>

namespace kern
{
    enum CursorMode
    {
        Enabled,
        Hidden,
        Disabled
    };

    struct Configuration
    {
        std::string title;
        int window_width;
        int window_height;
        bool fullscreen;
        int antialiasing_samples;
        CursorMode cursor_mode;
    };
}
