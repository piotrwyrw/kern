// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl/frame_buffer.hpp>
#include <kern/gl/shader.hpp>
#include <kern/gl/mesh.hpp>
#include <kern/gfx/material.hpp>
#include <kern/gfx/handles.hpp>

#include <vector>

namespace kern::gl
{
    class ResourceManager
    {
        std::vector<GpuMesh> meshes_;
        std::vector<Shader> shaders_;
        std::vector<gfx::Material> materials_;
        std::vector<Texture> textures_;
        std::vector<FrameBuffer> frame_buffers_;

    public:
        ResourceManager();

        [[nodiscard]] GpuMeshHandle add_mesh(GpuMesh&& mesh);
        [[nodiscard]] const GpuMesh& get_mesh(const GpuMeshHandle& handle) const;

        [[nodiscard]] ShaderProgramHandle add_shader(Shader&& shader);
        [[nodiscard]] const Shader& get_shader(const ShaderProgramHandle& handle) const;

        [[nodiscard]] MaterialHandle add_material(const gfx::Material& material);
        [[nodiscard]] const gfx::Material& get_material(const MaterialHandle& handle) const;

        [[nodiscard]] TextureHandle add_texture(const Texture&& texture);
        [[nodiscard]] const Texture& get_texture(const TextureHandle& handle) const;

        [[nodiscard]] FrameBufferHandle add_frame_buffer(const FrameBuffer&& frame_buffer);
        [[nodiscard]] const FrameBuffer& get_frame_buffer(const FrameBufferHandle& handle) const;
    };
}
