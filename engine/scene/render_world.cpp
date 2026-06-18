// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/scene/scene.hpp>
#include <kern/scene/mesh_instance.hpp>
#include <kern/exception/exception.hpp>

namespace kern::scene
{
    Scene::Scene()
        : objects_(std::vector<MeshInstance>())
    {
    }

    const std::vector<MeshInstance>& Scene::get_objects() const
    {
        return objects_;
    }

    MeshInstanceHandle Scene::add_object(const MeshInstance& object)
    {
        MeshInstanceHandle handle{static_cast<uint32_t>(objects_.size())};
        objects_.push_back(object);
        return handle;
    }

    const MeshInstance& Scene::get_object(const MeshInstanceHandle& handle) const
    {
        if (handle.index >= objects_.size())
        {
            throw exception::Exception(std::format("Scene Error: Attempted to retrieve "
                                                   "object with invalid handle: {}", handle.index));
        }

        return objects_[handle.index];
    }
}
