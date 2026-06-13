// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <vector>
#include <kern/rendering/gpu_mesh.hpp>
#include <kern/rendering/handles.hpp>

namespace kern::rendering
{
    class ResourceManager
    {
        std::vector<std::unique_ptr<GpuMesh>> meshes_;

    public:
        ResourceManager();

        [[nodiscard]] GpuMeshHandle add_mesh(std::unique_ptr<GpuMesh> mesh);
        [[nodiscard]] const GpuMesh& get_mesh(const GpuMeshHandle& handle) const;
    };
}
