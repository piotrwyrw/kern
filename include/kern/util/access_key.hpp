// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

namespace kern::util
{
    template <typename T>
    class AccessKey
    {
        AccessKey() = default;
        friend T;
    };
}
