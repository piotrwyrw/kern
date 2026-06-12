// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gl/glew.h>
#include <kern/rendering/renderer.hpp>

kern::rendering::Renderer::Renderer(platform::Window& window)
    : window_(window)
{
}

void kern::rendering::Renderer::clear() // NOLINT(*-convert-member-functions-to-static)
{
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void kern::rendering::Renderer::render_current()
{
    clear();
}
