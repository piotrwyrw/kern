// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>

#include "kern/mesh/geometry.hpp"

namespace kern::rendering {
	class GpuMesh {
		GLuint vbo_;
		GLuint vao_;
		GLuint ebo_;

	public:
		GpuMesh(const mesh::Mesh &mesh);
		~GpuMesh();
	};
}