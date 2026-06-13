// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/rendering/render_world.hpp>
#include <kern/exception/exception.hpp>

namespace kern::rendering
{
    RenderWorld::RenderWorld()
        : objects_(std::vector<RenderObject>())
    {
    }

    RenderObjectHandle RenderWorld::add_object(const RenderObject& object)
    {
        RenderObjectHandle handle{static_cast<uint32_t>(objects_.size())};
        objects_.push_back(object);
        return handle;
    }

    const RenderObject& RenderWorld::get_object(const RenderObjectHandle& handle) const
    {
        if (handle.index >= objects_.size())
        {
            throw exception::Exception(std::format("RenderWorld Error: Attempted to retrieve "
                                                   "object with invalid handle: {}", handle.index));
        }

        return objects_[handle.index];
    }
}
