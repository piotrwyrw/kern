// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>
#include <kern/gl.hpp>

namespace kern::rendering
{
    struct Vertex
    {
        glm::vec3 position, normal;
        glm::vec2 tex_coords;
    };

    struct Triangle
    {
        uint32_t v[3];
    };

    struct Mesh
    {
        std::vector<Vertex> vertices;
        std::vector<Triangle> tri_faces;
    };

    class GpuMesh
    {
        GLuint vao_;
        GLuint vbo_;
        GLuint ebo_;

        int index_count_;

    public:
        explicit GpuMesh(const Mesh& mesh);

        GpuMesh(const GpuMesh&) = delete;
        GpuMesh& operator=(const GpuMesh&) = delete;
        GpuMesh& operator=(GpuMesh&&) = delete;

        [[nodiscard]] int get_index_count() const;

        [[nodiscard]] GLuint get_vao_handle() const;
        [[nodiscard]] GLuint get_vbo_handle() const;
        [[nodiscard]] GLuint get_ebo_handle() const;

        ~GpuMesh();
    };
}
