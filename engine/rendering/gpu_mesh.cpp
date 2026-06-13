// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/rendering/gpu_mesh.hpp>

namespace kern::rendering
{
    GpuMesh::GpuMesh(const Mesh& mesh)
        : vao_(0), vbo_(0), ebo_(0), index_count_(0)
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        std::vector<float> vbo_data{};
        vbo_data.reserve(mesh.vertices.size() * 8);
        for (auto& vertex : mesh.vertices)
        {
            vbo_data.insert(
                vbo_data.end(), {
                    vertex.position.x, vertex.position.y, vertex.position.z,
                    vertex.normal.x, vertex.normal.y, vertex.normal.z,
                    vertex.tex_coords.x, vertex.tex_coords.y
                });
        }

        std::vector<uint32_t> ebo_data{};
        ebo_data.reserve(mesh.tri_faces.size() * 3);
        for (auto& face : mesh.tri_faces)
        {
            ebo_data.insert(ebo_data.end(), {face.v[0], face.v[1], face.v[2]});
        }

        index_count_ = static_cast<int>(ebo_data.size());

        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, (sizeof(float)) * vbo_data.size(), vbo_data.data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * ebo_data.size(), ebo_data.data(),
                     GL_STATIC_DRAW);

        // Vertex coordinates
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
        glEnableVertexAttribArray(0);

        // Vertex normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              reinterpret_cast<void*>(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        // UV coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              reinterpret_cast<void*>(sizeof(float) * 5));
        glEnableVertexAttribArray(2);


        glBindVertexArray(0);
    }

    GpuMesh::~GpuMesh()
    {
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ebo_);
        glDeleteVertexArrays(1, &vao_);
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
