// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/rendering/renderer.hpp>
#include <kern/platform/window.hpp>
#include <kern/core/game.hpp>

#include <spdlog/logger.h>

namespace kern
{
    class Engine
    {
        std::unique_ptr<spdlog::logger> logger_;

        const Configuration& config_;

        std::unique_ptr<Game> game_;
        std::unique_ptr<platform::Window> window_;
        std::unique_ptr<rendering::Renderer> renderer_;
        std::unique_ptr<Context> context_;

    public:
        explicit Engine(std::unique_ptr<Game> game, const Configuration& config);

        [[nodiscard]] bool should_close() const;

        void run() const;

        /**
         * Initialize and Start a Kern Game
         * @tparam T The game class. Must be an implementation of the <code>kern::Game</code> class
         * @return A <code>std::unique_ptr<Engine></code> created for this game
         */
        template <typename T, typename = std::is_base_of<Game, T>>
        static std::unique_ptr<Engine> start()
        {
            std::unique_ptr<Game> instance = std::make_unique<T>();
            auto cfg = instance->startup_config();
            return std::make_unique<Engine>(std::move(instance), std::move(cfg));
        }
    };
}
