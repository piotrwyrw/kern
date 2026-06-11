// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/mesh/obj.hpp>
#include <kern/util/fs.hpp>

kern::mesh::Mesh load_obj_mesh(const std::string& filename)
{
    return kern::mesh::load_obj_source_mesh(kern::fs::read_text_file(filename));
}


kern::mesh::Mesh kern::mesh::load_obj_source_mesh(const std::string& source)
{
    return {};
}