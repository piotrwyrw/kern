// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/rendering/mesh.hpp>

#include "kern/rendering/renderer.hpp"

kern::rendering::GpuMesh::GpuMesh(const mesh::Mesh &mesh)
	: vbo_(0), vao_(0), ebo_(0)
{
	glCreateBuffers(1, &vbo_);
	glCreateVertexArrays(1, &vao_);
	glGenBuffers(1, &ebo_);
}

kern::rendering::GpuMesh::~GpuMesh()
{
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
	glDeleteVertexArrays(1, &vao_);
}