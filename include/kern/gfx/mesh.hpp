// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>

namespace kern::mesh
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
}
