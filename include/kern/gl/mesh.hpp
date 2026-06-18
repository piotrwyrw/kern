// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>
#include <kern/gfx/mesh.hpp>

namespace kern::gl
{
    class GpuMesh
    {
        GLuint vao_;
        GLuint vbo_;
        GLuint ebo_;

        int index_count_;

        void destroy_resources() const;

    public:
        explicit GpuMesh(const mesh::Mesh& mesh);

        GpuMesh(const GpuMesh&) = delete;
        GpuMesh& operator=(const GpuMesh&) = delete;

        GpuMesh(GpuMesh&& src) noexcept;
        GpuMesh& operator=(GpuMesh&& src) noexcept;

        ~GpuMesh();

        [[nodiscard]] GLuint get_vao_handle() const;
        [[nodiscard]] GLuint get_vbo_handle() const;
        [[nodiscard]] GLuint get_ebo_handle() const;

        [[nodiscard]] int get_index_count() const;
    };
}
