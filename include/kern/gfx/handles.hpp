// This File is Part of the Vanadium Kern Game Engine.
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
        void invalidate() \
        { \
            index = UINT32_MAX; \
        } \
    }

namespace kern
{
    KERN_MAKE_HANDLE_(GpuMeshHandle);

    KERN_MAKE_HANDLE_(MeshInstanceHandle);

    KERN_MAKE_HANDLE_(ShaderProgramHandle);

    KERN_MAKE_HANDLE_(MaterialHandle);

    KERN_MAKE_HANDLE_(TextureHandle);

    KERN_MAKE_HANDLE_(FrameBufferHandle);
}
