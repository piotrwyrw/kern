// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl/resource_manager.hpp>
#include <kern/platform/window.hpp>
#include <kern/gfx/renderer.hpp>
#include <kern/gfx/camera.hpp>
#include <kern/scene/scene.hpp>
#include <kern/core/game.hpp>

#include <spdlog/logger.h>

namespace kern
{
    class Engine
    {
        spdlog::logger logger_;

        std::unique_ptr<Game> game_;
        const Configuration& config_;

        platform::Window window_;
        gfx::Renderer renderer_;
        Context context_;
        gl::ResourceManager resources_;
        scene::Scene world_;
        gfx::Camera camera_;

    public:
        explicit Engine(std::unique_ptr<Game> game,
                        const Configuration& config);
        ~Engine();

        [[nodiscard]] const platform::Window& get_window() const;

        [[nodiscard]] bool should_close() const;

        void run();

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
