// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/exception/exception.hpp>

#include <vector>

namespace kern::util
{
    template <typename Handle, typename T>
    T& get_or_throw(std::vector<T>& vec,
                    const Handle& handle,
                    const std::string& error)
    {
        auto index = handle.index;
        auto gen = handle.generation;

        if (index >= vec.size())
        {
            throw exception::Exception(error);
        }

        const auto& slot = vec[index];

        if (slot.generation != gen)
        {
            throw exception::Exception(error);
        }

        return slot;
    }
}
