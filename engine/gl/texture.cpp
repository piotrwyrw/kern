// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl/texture.hpp>
#include <kern/gl/resource_manager.hpp>

namespace kern::gl
{
    Texture::Texture(const int width, const int height,
                     const bool follow_window_dims)
        : txt_(0), follow_window_dims_(follow_window_dims), alloc_txt_([&](const int w, const int h)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT,
                         w, h, 0, FORMAT, TYPE, nullptr);
        })
    {
        glGenTextures(1, &txt_);
        glBindTexture(GL_TEXTURE_2D, txt_);

        alloc_txt_(width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &txt_);

        txt_ = 0;
        follow_window_dims_ = false;
        alloc_txt_ = [&](int, int)
        {
        };
    }

    void Texture::resize(const int width, const int height) const
    {
        glBindTexture(GL_TEXTURE_2D, txt_);
        alloc_txt_(width, height);
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, txt_);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint Texture::get_txt_handle() const
    {
        return txt_;
    }
}
