// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/exception/exception.hpp>
#include <kern/gfx/handles.hpp>
#include <kern/gl/mesh.hpp>
#include <kern/gl/shader.hpp>
#include <kern/gl/texture.hpp>
#include <kern/gl/frame_buffer.hpp>
#include <kern/gfx/material.hpp>
#include <kern/util/container_utils.hpp>

#include <vector>

namespace kern::gl
{
    namespace resource_type_name
    {
        inline constexpr auto UNKNOWN = "Unknown Resource";
        inline constexpr auto MESH = "Mesh";
        inline constexpr auto SHADER = "Shader";
        inline constexpr auto TEXTURE = "Texture";
        inline constexpr auto FRAME_BUFFER = "Frame Buffer";
        inline constexpr auto MATERIAL = "Material";

        template <typename T>
        struct resource_name_t
        {
            static constexpr const char* const name = UNKNOWN;
        };

        template <>
        struct resource_name_t<mesh::Mesh>
        {
            static constexpr const char* const name = MESH;
        };

        template <>
        struct resource_name_t<ShaderProgram>
        {
            static constexpr const char* const name = SHADER;
        };

        template <>
        struct resource_name_t<Texture>
        {
            static constexpr const char* const name = TEXTURE;
        };

        template <>
        struct resource_name_t<FrameBuffer>
        {
            static constexpr const char* const name = FRAME_BUFFER;
        };

        template <>
        struct resource_name_t<gfx::Material>
        {
            static constexpr const char* const name = MATERIAL;
        };

        template <typename T>
        constexpr auto resource_name_v = resource_name_t<T>::name;
    }

    template <typename T>
    struct ResourceSlot
    {
        T content;
        bool exists;
        std::uint32_t generation;
    };

    class ResourceManager
    {
        std::vector<ResourceSlot<GpuMesh>> meshes_{};
        std::vector<ResourceSlot<ShaderProgram>> shaders_{};
        std::vector<ResourceSlot<Texture>> textures_{};
        std::vector<ResourceSlot<FrameBuffer>> frame_buffers_{};
        std::vector<ResourceSlot<gfx::Material>> materials_{};

        template <typename Handle>
        using slot_t = ResourceSlot<handle_to_target_t<Handle>>;

        template <typename Handle>
        using slot_vec_t = std::vector<slot_t<Handle>>;

        template <typename Handle>
        slot_vec_t<Handle>& get_resource_vec();

        template <typename Handle>
        const slot_vec_t<Handle>& get_resource_vec() const
        {
            return const_cast<ResourceManager*>(this)->get_resource_vec<Handle>();
        }

        template <typename Handle>
        handle_to_target_t<Handle>& get_resource(Handle handle)
        {
            return util::get_or_throw<slot_t<Handle>>(
                get_resource_vec<Handle>(),
                handle,
                std::format(
                    "ResourceManager Error: Attempted to retrieve "
                    "a {} resource with invalid handle (Index {}, Generation {})",
                    resource_type_name::resource_name_v<handle_to_target_t<Handle>>,
                    handle.index, handle.generation
                )
            ).content;
        }

        template <typename Handle>
        const handle_to_target_t<Handle>& get_resource(Handle handle) const
        {
            return get_resource(handle);
        }

    public:
        ResourceManager() = default;
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
    };

    template <typename Handle>
    ResourceManager::slot_vec_t<Handle>& ResourceManager::get_resource_vec()
    {
        throw exception::Exception("ResourceManager Error: Attempted to retrieve resource vector "
            "with unknown handle type.");
    }

    template <>
    inline ResourceManager::slot_vec_t<GpuMeshHandle>&
    ResourceManager::get_resource_vec<GpuMeshHandle>()
    {
        return meshes_;
    }

    template <>
    inline ResourceManager::slot_vec_t<ShaderProgramHandle>&
    ResourceManager::get_resource_vec<ShaderProgramHandle>()
    {
        return shaders_;
    }

    template <>
    inline ResourceManager::slot_vec_t<TextureHandle>&
    ResourceManager::get_resource_vec<TextureHandle>()
    {
        return textures_;
    }

    template <>
    inline ResourceManager::slot_vec_t<FrameBufferHandle>&
    ResourceManager::get_resource_vec<FrameBufferHandle>()
    {
        return frame_buffers_;
    }

    template <>
    inline ResourceManager::slot_vec_t<MaterialHandle>&
    ResourceManager::get_resource_vec<MaterialHandle>()
    {
        return materials_;
    }
}
