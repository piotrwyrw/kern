// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/gl/mesh.hpp>
#include <kern/gl/resource_manager.hpp>
#include <kern/gfx/renderer.hpp>
#include <kern/scene/mesh_instance.hpp>
#include <kern/scene/scene.hpp>

namespace kern::gfx
{
    Renderer::Renderer(platform::Window& window)
        : window_(window)
    {
    }

    void Renderer::clear()
    {
        glClearColor(0.15, 0, 0.6, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::render_mesh(const gl::GpuMesh& mesh)
    {
        glBindVertexArray(mesh.get_vao_handle());
        glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::render(const scene::Scene& world, const gl::ResourceManager& resources,
                          const Camera& camera) const
    {
        clear();

        auto& objects = world.get_objects();
        for (auto& object : objects)
        {
            auto& mesh = resources.get_mesh(object.mesh_handle);
            render_mesh(mesh);
        }
    }
}
