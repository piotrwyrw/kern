// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gfx/handles.hpp>
#include <kern/scene/mesh_instance.hpp>

#include <vector>

namespace kern::scene
{
    class Scene
    {
        std::vector<MeshInstance> objects_;

    public:
        Scene();

        [[nodiscard]] const std::vector<MeshInstance>& get_objects() const;
        [[nodiscard]] MeshInstanceHandle add_object(const MeshInstance& object);
        [[nodiscard]] const MeshInstance& get_object(const MeshInstanceHandle& handle) const;
    };
}
