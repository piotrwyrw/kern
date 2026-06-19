// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl/frame_buffer.hpp>
#include <kern/exception/exception.hpp>

namespace kern::gl
{
    FrameBuffer::FrameBuffer(const TextureHandle texture)
        : fbo_(0), texture_(texture)
    {
        glGenFramebuffers(1, &fbo_);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

        // TODO
        // texture_.bind();

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw exception::Exception("FrameBuffer Error: The frame buffer is not complete.");
        }
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &fbo_);
        fbo_ = 0;
    }

    void FrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    }

    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
