// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gfx/handles.hpp>
#include <kern/gfx/uniform.hpp>

#include <unordered_map>

namespace kern::gfx
{
    class Material
    {
        ShaderProgramHandle shader_handle_{};
        std::unordered_map<std::string, AnyUniform> uniforms_;

    public:
        explicit Material(const ShaderProgramHandle shader_handle,
                          const std::unordered_map<std::string, AnyUniform>& uniforms)
            : shader_handle_(shader_handle),
              uniforms_(uniforms)
        {
        }

        template <typename... Ts>
        static Material create(const ShaderProgramHandle shader_handle,
                               const std::pair<std::string, to_uniform_t<Ts>>&... uniforms)
        {
            return Material(shader_handle, {{uniforms.first, uniforms.second}...});
        }
    };
}
