// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <vector>
#include <kern/rendering/handles.hpp>
#include <kern/rendering/render_object.hpp>

namespace kern::rendering
{
    class RenderWorld
    {
        std::vector<RenderObject> objects_;

    public:
        RenderWorld();

        [[nodiscard]] RenderObjectHandle add_object(const RenderObject& object);
        [[nodiscard]] const RenderObject& get_object(const RenderObjectHandle& handle) const;
    };
}
