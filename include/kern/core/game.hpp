// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/configuration.hpp>
#include <kern/core/context.hpp>

namespace kern
{
    class Game
    {
    public:
        virtual ~Game() = default;

        virtual Configuration startup_config() = 0;

        virtual void on_start(Context& ctx) = 0;
        virtual void on_update(Context& ctx, float delta_time) = 0;
        virtual void on_quit(Context& ctx) = 0;
    };
}
