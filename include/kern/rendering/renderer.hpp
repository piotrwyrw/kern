// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/platform/window.hpp>

namespace kern::rendering
{
    class Renderer
    {
        platform::Window& window_;

        void clear();

    public:
        explicit Renderer(platform::Window& window);

        void render_current();
    };
}
