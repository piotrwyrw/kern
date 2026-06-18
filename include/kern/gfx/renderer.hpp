// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

namespace kern
{
    namespace gl
    {
        class ResourceManager;
        class GpuMesh;
    }

    namespace platform
    {
        class Window;
    }

    namespace scene
    {
        class Scene;
    }

    namespace gfx
    {
        class Camera;

        class Renderer
        {
            platform::Window& window_;

            static void clear();

            static void render_mesh(const gl::GpuMesh& mesh);

        public:
            explicit Renderer(platform::Window& window);

            void render(const scene::Scene& world, const gl::ResourceManager& resources,
                        const Camera& camera) const;
        };
    }
}
