// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <type_traits>

namespace kern::math
{
    /**
     * Check if the point <code>(px, py)</code> is contained within the rectangle at <code>(rect_x,
     * rect_y)</code> with the dimensions <code>(rect_w, rect_h)</code>
     */
    template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
    [[nodiscard]] bool is_inside_rect(T px, T py, T rect_x, T rect_y, T rect_w, T rect_h)
    {
        return px >= rect_x && px <= rect_x + rect_w
            && py >= rect_y && py <= rect_y + rect_h;
    }
}
