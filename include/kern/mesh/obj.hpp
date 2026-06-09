// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/mesh/geometry.hpp>

namespace kern::mesh {
	Mesh load_obj_mesh(const std::string &filename);
	Mesh load_obj_source_mesh(const std::string &source);
}