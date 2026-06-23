// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/gl/mesh.hpp>

namespace kern::gl
{
    GpuMesh::GpuMesh(const GLuint vao, const GLuint vbo, const GLuint ebo, const int index_count)
        : vao_(vao), vbo_(vbo), ebo_(ebo), index_count_(index_count)
    {
    }

    GpuMesh GpuMesh::create(const mesh::Mesh& mesh)
    {
        GLuint vao, vbo, ebo;
        int index_count;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<float> vbo_data{};
        vbo_data.reserve(mesh.vertices.size() * 8);
        for (const auto& [position, normal, tex_coords] : mesh.vertices)
        {
            vbo_data.insert(
                vbo_data.end(), {
                    position.x, position.y, position.z,
                    normal.x, normal.y, normal.z,
                    tex_coords.x, tex_coords.y
                });
        }

        std::vector<uint32_t> ebo_data{};
        ebo_data.reserve(mesh.tri_faces.size() * 3);
        for (auto& [v] : mesh.tri_faces)
        {
            ebo_data.insert(ebo_data.end(), {v[0], v[1], v[2]});
        }

        index_count = static_cast<int>(ebo_data.size());

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * vbo_data.size(), // NOLINT
                     vbo_data.data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(uint32_t) * ebo_data.size(), // NOLINT
                     ebo_data.data(),
                     GL_STATIC_DRAW);

        // Vertex coordinates
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
        glEnableVertexAttribArray(0);


        // Vertex normals
        // TODO offsetof
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              reinterpret_cast<void*>(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        // UV coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              reinterpret_cast<void*>(sizeof(float) * 5));
        glEnableVertexAttribArray(2);


        glBindVertexArray(0);

        return GpuMesh(vao, vbo, ebo, index_count);
    }

    void GpuMesh::delete_resources(const GpuMesh& mesh)
    {
        glDeleteBuffers(1, &mesh.vbo_);
        glDeleteBuffers(1, &mesh.ebo_);
        glDeleteVertexArrays(1, &mesh.vao_);
    }

    int GpuMesh::get_index_count() const
    {
        return index_count_;
    }

    GLuint GpuMesh::get_vao_handle() const
    {
        return vao_;
    }

    GLuint GpuMesh::get_vbo_handle() const
    {
        return vbo_;
    }

    GLuint GpuMesh::get_ebo_handle() const
    {
        return ebo_;
    }
}
