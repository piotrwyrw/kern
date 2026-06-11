// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/rendering/renderer.hpp>
#include <kern/platform/window.hpp>
#include <kern/core/game.hpp>

namespace kern
{
    class Engine
    {
        const Properties& properties_;

        std::unique_ptr<Context> context_;
        std::unique_ptr<Game> game_;
        std::unique_ptr<platform::Window> window_;
        std::unique_ptr<rendering::Renderer> renderer_;

    public:
        explicit Engine(std::unique_ptr<Game> game, const Properties& properties);

        [[nodiscard]] bool should_close() const;

        void run();

        template <typename T, typename = std::is_base_of<Game, T>>
        static std::unique_ptr<Engine> start(
            const Properties& properties)
        {
            return std::make_unique<Engine>(std::make_unique<T>(), properties);
        }
    };
}
