// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <cstdint>
#include <string>

#define KERN_MAKE_HANDLE_FOR_(type_, ns, name)                                             \
    namespace kern {                                                                \
        struct name##Handle {                                                       \
            std::uint32_t index = UINT32_MAX;                                       \
            std::uint32_t generation = UINT32_MAX;                                  \
                                                                                    \
            [[nodiscard]] bool valid() const                                        \
            {                                                                       \
                return index != UINT32_MAX && generation != UINT32_MAX;             \
            }                                                                       \
                                                                                    \
            void invalidate()                                                       \
            {                                                                       \
                index = UINT32_MAX;                                                 \
                generation = UINT32_MAX;                                            \
            }                                                                       \
        };                                                                          \
    };                                                                              \
    namespace ns { type_ name; }                                                    \
    namespace kern {                                                                \
        template<> struct handle_to_target<name##Handle> { using type = ns::name; };\
    }

namespace kern
{
    template <typename>
    struct handle_to_target
    {
        using type = void;
    };

    template <typename T>
    using handle_to_target_t = handle_to_target<T>::type;
}

KERN_MAKE_HANDLE_FOR_(class, kern::gl, GpuMesh);

KERN_MAKE_HANDLE_FOR_(class, kern::gl, ShaderProgram);

KERN_MAKE_HANDLE_FOR_(class, kern::gl, Texture);

KERN_MAKE_HANDLE_FOR_(class, kern::gl, FrameBuffer);

KERN_MAKE_HANDLE_FOR_(class, kern::gfx, Material);


KERN_MAKE_HANDLE_FOR_(struct, kern::scene, MeshInstance);
