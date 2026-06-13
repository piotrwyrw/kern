// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <cstdint>

#define KERN_MAKE_HANDLE_(name) \
    struct name { \
        uint32_t index = UINT32_MAX; \
        [[nodiscard]] bool valid() const \
        { \
            return index != UINT32_MAX; \
        }\
    }


KERN_MAKE_HANDLE_(GpuMeshHandle);
KERN_MAKE_HANDLE_(RenderObjectHandle);