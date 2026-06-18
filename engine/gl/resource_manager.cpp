// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl/resource_manager.hpp>
#include <kern/util/container_utils.hpp>
#include <kern/exception/exception.hpp>

namespace kern::gl
{
    ResourceManager::ResourceManager()
        : meshes_(std::vector<GpuMesh>())
    {
    }

    GpuMeshHandle ResourceManager::add_mesh(GpuMesh&& mesh)
    {
        const GpuMeshHandle handle{static_cast<uint32_t>(meshes_.size())};
        meshes_.push_back(std::move(mesh));
        return handle;
    }

    const GpuMesh& ResourceManager::get_mesh(const GpuMeshHandle& handle) const
    {
        if (handle.index >= meshes_.size())
        {
            throw exception::Exception(std::format(
                "ResourceManager Error: Attempted to retrieve "
                "mesh with invalid handle: {}", handle.index));
        }

        return meshes_[handle.index];
    }

    ShaderProgramHandle ResourceManager::add_shader(Shader&& shader)
    {
        const ShaderProgramHandle handle{static_cast<uint32_t>(shaders_.size())};
        shaders_.push_back(std::move(shader));
        return handle;
    }

    const Shader& ResourceManager::get_shader(const ShaderProgramHandle& handle) const
    {
        return util::get_or_throw(
            shaders_,
            handle,
            std::format(
                "ResourceManager Error: Attempted to retrieve shader with invalid handle: {}",
                handle.index
            )
        );
    }

    MaterialHandle ResourceManager::add_material(const gfx::Material& material)
    {
        const MaterialHandle handle{static_cast<uint32_t>(materials_.size())};
        materials_.push_back(material);
        return handle;
    }

    const gfx::Material& ResourceManager::get_material(const MaterialHandle& handle) const
    {
        return util::get_or_throw(
            materials_,
            handle,
            std::format(
                "ResourceManager Error: Attempted to retrieve material with invalid handle: {}",
                handle.index
            )
        );
    }
}
