// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace kern::mesh {
	struct Vertex {
		glm::vec3 position, normal;
		glm::vec2 tex_coords;
	};

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

	namespace builtin {
		Mesh cube();
	}
}