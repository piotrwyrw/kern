// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <format>

#include <kern/gl.hpp>
#include <kern/rendering/renderer.hpp>
#include <kern/core/game.hpp>
#include <kern/core/engine.hpp>
#include <kern/core/context.hpp>
#include <kern/exception/exception.hpp>
#include <kern/version.hpp>
#include <kern/logging/logging.hpp>

namespace kern
{
    Engine::Engine(std::unique_ptr<Game> game, const Configuration& config)
        : logger_(std::move(log::create_logger(spdlog::level::debug))),
          config_(config),
          game_(std::move(game)),
          window_(std::make_unique<platform::Window>(config)),
          renderer_(std::make_unique<rendering::Renderer>(*window_)),
          context_(std::make_unique<Context>(*window_, *logger_))
    {
        exception::handle_all(*logger_, [&]() -> void
        {
            run();
        });
    }

    Engine::~Engine()
    {
        logger_->info("Kern shutting down. Goodbye!");
    }

    bool Engine::should_close() const
    {
        return context_->should_close() || window_->should_close();
    }

    void Engine::run() const
    {
        logger_->info("Starting Kern " KERN_VERSION);

        game_->on_start(*context_);

        auto& timing = context_->get_timing();

        while (!should_close())
        {
            timing.start_frame();

            window_->handle_events();

            game_->on_update(*context_, timing.get_delta_time());
            renderer_->render_current();

            window_->swap_buffers();

            timing.end_frame();
        }

        game_->on_quit(*context_);
    }
}
