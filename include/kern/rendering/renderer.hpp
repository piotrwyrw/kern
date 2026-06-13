// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/platform/window.hpp>

#include <kern/rendering/camera.hpp>
#include <kern/rendering/render_world.hpp>
#include <kern/rendering/resource_manager.hpp>

namespace kern::rendering
{
    class Renderer
    {
        platform::Window& window_;

        void clear() const;

    public:
        explicit Renderer(platform::Window& window);

        void render(const RenderWorld& world, const ResourceManager& resources,
                    const Camera& camera) const;
    };
}
