// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl/resource_manager.hpp>

namespace kern::gl
{
    const GpuMesh& ResourceManager::get_mesh(const GpuMeshHandle& handle) const
    {
        return get_resource(handle);
    }

    const ShaderProgram& ResourceManager::get_shader(const ShaderProgramHandle& handle) const
    {
        return get_resource(handle);
    }

    const Texture& ResourceManager::get_texture(const TextureHandle& handle) const
    {
        return get_resource(handle);
    }

    const FrameBuffer& ResourceManager::get_frame_buffer(const FrameBufferHandle& handle) const
    {
        return get_resource(handle);
    }

    const gfx::Material& ResourceManager::get_material(const MaterialHandle& handle) const
    {
        return get_resource(handle);
    }
}
