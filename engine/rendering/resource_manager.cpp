// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/rendering/resource_manager.hpp>
#include <kern/exception/exception.hpp>

namespace kern::rendering
{
    ResourceManager::ResourceManager()
        : meshes_(std::vector<std::unique_ptr<GpuMesh>>())
    {
    }

    GpuMeshHandle ResourceManager::add_mesh(std::unique_ptr<GpuMesh> mesh)
    {
        GpuMeshHandle handle{static_cast<uint32_t>(meshes_.size())};
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

        return *meshes_[handle.index];
    }
}
