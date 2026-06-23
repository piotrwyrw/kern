// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <cstdint>
#include <string_view>

using namespace std::literals::string_view_literals;

#define MAKE_HANDLE_(type_, ns, name, display_name)                                        \
    namespace ns { type_ name; }                                                           \
    namespace kern {                                                                       \
        struct name##Handle {                                                              \
            std::uint32_t   index = UINT32_MAX,                                            \
                            generation = UINT32_MAX;                                       \
                                                                                           \
            [[nodiscard]] bool valid() const { return   index != UINT32_MAX &&             \
                                                        generation != UINT32_MAX; }        \
            void invalidate() { index = UINT32_MAX;                                        \
                                generation = UINT32_MAX; }                                 \
        };                                                                                 \
        template<> struct unwrap_hdl<name##Handle>  { using type = ns::name; };            \
        template<> struct wrap_hdl  <ns::name>      { using type = kern::name##Handle; };  \
        template<> struct rsrc_name <ns::name>  {                                      \
            static constexpr auto value = display_name##sv;                                \
        };                                                                                 \
    }

namespace kern
{
    template <typename>
    struct unwrap_hdl
    {
        using type = void;
    };

    template <typename>
    struct wrap_hdl
    {
        using type = void;
    };

    template <typename>
    struct rsrc_name
    {
        static constexpr std::string_view value = "Unknown Resource";
    };

    /**
     * Converts a handle type to a resource type.<br/><br/>
     * <b>Example:</b> <code>ShaderProgramHandle</code> becomes <code>ShaderProgram</code>
     */
    template <typename Handle>
    using unwrap_hdl_t = unwrap_hdl<Handle>::type;

    /**
     * Converts a resource type to a handle type.<br/><br/>
     * <b>Example:</b> <code>ShaderProgram</code> becomes <code>ShaderProgramHandle</code>
     */
    template <typename Resource>
    using wrap_hdl_t = wrap_hdl<Resource>::type;

    /**
     * Provides the name of a resource.<br/><br/>
     * <b>Example:</b> Given <code>GpuMesh</code> returns <code>"GpuMesh"</code>
     */
    template <typename Resource>
    constexpr auto rsrc_name_v = rsrc_name<Resource>::value;
}


MAKE_HANDLE_(class, kern::gl, GpuMesh, "GPU Mesh");

MAKE_HANDLE_(class, kern::gl, ShaderProgram, "Shader program");

MAKE_HANDLE_(class, kern::gl, Texture, "Texture");

MAKE_HANDLE_(class, kern::gl, FrameBuffer, "Frame buffer");

MAKE_HANDLE_(class, kern::gfx, Material, "Material");

MAKE_HANDLE_(struct, kern::scene, MeshInstance, "Mesh instance");


#undef MAKE_HANDLE_
