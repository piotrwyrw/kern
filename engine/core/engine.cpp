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
#include <utility>

kern::Engine::Engine(std::unique_ptr<Game> game, const Properties& properties)
    : properties_(properties),
      context_(std::make_unique<Context>()),
      game_(std::move(game)),
      window_(std::make_unique<platform::Window>(properties)),
      renderer_(std::make_unique<rendering::Renderer>(*window_))
{
    run();
}

[[nodiscard]] bool kern::Engine::should_close() const
{
    return context_->should_close() || window_->should_close();
}

void kern::Engine::run()
{
    game_->on_start(*context_);

    auto& timing = context_->get_timing();

    while (!should_close())
    {
        timing.start_frame();

        window_->tick();

        game_->on_update(*context_, timing.get_delta_time());
        renderer_->render_current();

        window_->swap_buffers();

        timing.end_frame();
    }

    game_->on_quit(*context_);
}