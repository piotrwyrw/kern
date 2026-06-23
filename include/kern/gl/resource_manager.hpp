// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gfx/handles.hpp>
#include <kern/gl/mesh.hpp>
#include <kern/gl/shader.hpp>
#include <kern/gl/texture.hpp>
#include <kern/gl/frame_buffer.hpp>
#include <kern/gfx/material.hpp>
#include <kern/gl/resource_container.hpp>

#include <vector>

namespace spdlog
{
    class logger;
}

namespace kern::gl
{
    class ResourceManager
    {
        spdlog::logger& logger_;

        ResourceContainer<GpuMesh> meshes_;
        ResourceContainer<ShaderProgram> shaders_;
        ResourceContainer<Texture> textures_;
        ResourceContainer<FrameBuffer> frame_buffers_;
        ResourceContainer<gfx::Material> materials_;

        template <typename Resource>
        ResourceContainer<Resource>& get_rsrc_container();

        template <typename Resource>
        const ResourceContainer<Resource>& get_rsrc_container() const;

        template <typename Handle>
        unwrap_hdl_t<Handle>& get_rsrc(Handle handle);

        template <typename Handle>
        const unwrap_hdl_t<Handle>& get_rsrc(Handle handle) const;

    public:
        explicit ResourceManager(spdlog::logger& logger);
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager(const ResourceManager&&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&&) = delete;

        [[nodiscard]] const GpuMesh& get_mesh(const GpuMeshHandle& handle) const;
        [[nodiscard]] const ShaderProgram& get_shader(const ShaderProgramHandle& handle) const;
        [[nodiscard]] const Texture& get_texture(const TextureHandle& handle) const;
        [[nodiscard]] const FrameBuffer& get_frame_buffer(const FrameBufferHandle& handle) const;
        [[nodiscard]] const gfx::Material& get_material(const MaterialHandle& handle) const;

        template <typename... Args>
        [[nodiscard]] GpuMeshHandle create_mesh(Args&&... args);

        template <typename... Args>
        [[nodiscard]] ShaderProgramHandle create_shader(Args&&... args);

        template <typename... Args>
        [[nodiscard]] TextureHandle create_texture(Args&&... args);

        template <typename... Args>
        [[nodiscard]] FrameBufferHandle create_frame_buffer(Args&&... args);

        template <typename... Args>
        [[nodiscard]] MaterialHandle create_material(Args&&... args);
    };

    inline ResourceManager::ResourceManager(spdlog::logger& logger)
        : logger_(logger),
          meshes_{logger_},
          shaders_{logger_},
          textures_{logger_},
          frame_buffers_(logger_),
          materials_(logger_)
    {
    }

    template <typename Resource>
    ResourceContainer<Resource>& ResourceManager::get_rsrc_container()
    {
        throw exception::Exception(
            "ResourceManager Error: Attempted to retrieve resource vector with unknown handle type."
        );
    }

    template <typename Resource>
    const ResourceContainer<Resource>& ResourceManager::get_rsrc_container() const
    {
        return const_cast<ResourceManager*>(this)->get_rsrc_container<Resource>();
    }

    template <>
    inline ResourceContainer<GpuMesh>& ResourceManager::get_rsrc_container<GpuMesh>() { return meshes_; }

    template <>
    inline ResourceContainer<ShaderProgram>& ResourceManager::get_rsrc_container<ShaderProgram>() { return shaders_; }

    template <>
    inline ResourceContainer<Texture>& ResourceManager::get_rsrc_container<Texture>() { return textures_; }

    template <>
    inline ResourceContainer<FrameBuffer>& ResourceManager::get_rsrc_container<FrameBuffer>() { return frame_buffers_; }

    template <>
    inline ResourceContainer<gfx::Material>& ResourceManager::get_rsrc_container<gfx::Material>() { return materials_; }

    template <typename Handle>
    unwrap_hdl_t<Handle>& ResourceManager::get_rsrc(Handle handle)
    {
        auto& cont = get_rsrc_container<unwrap_hdl_t<Handle>>();
        return cont.get_resource(handle);
    }

    template <typename Handle>
    const unwrap_hdl_t<Handle>& ResourceManager::get_rsrc(Handle handle) const
    {
        return const_cast<ResourceManager*>(this)->get_rsrc(handle);
    }

    inline const GpuMesh& ResourceManager::get_mesh(const GpuMeshHandle& handle) const
    {
        return get_rsrc(handle);
    }

    inline const ShaderProgram& ResourceManager::get_shader(const ShaderProgramHandle& handle) const
    {
        return get_rsrc(handle);
    }

    inline const Texture& ResourceManager::get_texture(const TextureHandle& handle) const
    {
        return get_rsrc(handle);
    }

    inline const FrameBuffer& ResourceManager::get_frame_buffer(const FrameBufferHandle& handle) const
    {
        return get_rsrc(handle);
    }

    inline const gfx::Material& ResourceManager::get_material(const MaterialHandle& handle) const
    {
        return get_rsrc(handle);
    }
}
