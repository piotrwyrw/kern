// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>
#include <kern/gl/texture.hpp>

namespace kern::gl
{
    class FrameBuffer
    {
        GLuint fbo_;
        Texture texture_;

    public:
        FrameBuffer(int width, int height);

        ~FrameBuffer();

        void bind() const;

        static void unbind();
    };
}
