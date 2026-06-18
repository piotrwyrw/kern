// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>

#include <functional>

namespace kern::gl
{
    class Texture
    {
        GLuint txt_;
        bool follow_window_dims_;
        std::function<void(int width, int height)> alloc_txt_;

    public:
        static constexpr auto INTERNAL_FORMAT = GL_RGBA8;
        static constexpr auto FORMAT = GL_RGBA;
        static constexpr auto TYPE = GL_UNSIGNED_BYTE;

        /**
         * @param width Initial width of the texture
         * @param height Initial height of the texture
         * @param follow_window_dims Whether to resize the texture to fit the window dimensions
         * when it is resized
         */
        Texture(int width, int height, bool follow_window_dims);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(const Texture&& src);
        Texture& operator=(const Texture&& src);

        ~Texture();

        void resize(int width, int height) const;

        void bind() const;

        static void unbind();

        [[nodiscard]] GLuint get_txt_handle() const;
    };
}
