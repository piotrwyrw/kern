// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <type_traits>

namespace kern::util
{
    template <typename T, typename... Allowed>
    struct is_one_of : std::false_type
    {
    };

    template <typename T, typename First, typename... Rest>
    struct is_one_of<T, First, Rest...>
        : std::conditional_t<std::is_same_v<T, First>, std::true_type, is_one_of<T, Rest...>>
    {
    };
}
