// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>
#include <kern/gfx/mesh.hpp>
#include <kern/util/token.hpp>

namespace kern::gl
{
    class ResourceManager;

    class GpuMesh
    {
        GLuint vao_;
        GLuint vbo_;
        GLuint ebo_;

        int index_count_;

    public:
        explicit GpuMesh(GLuint vao, GLuint vbo, GLuint ebo, int index_count);

        static GpuMesh create(const mesh::Mesh& mesh);
        static void delete_resources(const GpuMesh& mesh);

        [[nodiscard]] GLuint get_vao_handle() const;
        [[nodiscard]] GLuint get_vbo_handle() const;
        [[nodiscard]] GLuint get_ebo_handle() const;
        [[nodiscard]] int get_index_count() const;
    };
}
