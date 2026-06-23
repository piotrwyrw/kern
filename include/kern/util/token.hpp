// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

namespace kern::util
{
    /**
     * This is meant to be used as a dummy parameter to only allow the specified
     * class to call a given function.
     * @tparam Creator The *only* class that should be able to instantiate this token
     *
     * <b>Example</b><br/>
     * <code>kern::Token<kern::gl::ResourceManager></code><br/>
     * can only be instantiated by<br/>
     * <code>kern::gl::ResourceManager</code>.
     */
    template <typename Creator>
    class Token
    {
        Token() = default;
        friend Creator;

    public:
        Token(Token&) = delete;
        Token(Token&&) = delete;
        Token& operator=(Token&) = delete;
        Token& operator=(Token&&) = delete;
    };
}
