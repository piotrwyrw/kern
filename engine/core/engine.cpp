// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <format>

#include <kern/gl.hpp>
#include <kern/core/engine.hpp>
#include <kern/exception/exception.hpp>
#include <utility>

kern::Engine::Engine(std::shared_ptr<Game> game, const Properties &properties)
	: context_({}),
	  game_(std::move(game)),
	  properties_(properties),
	  window_({ properties_ }),
	  renderer_(window_)
{
	run();
}

[[nodiscard]] bool kern::Engine::should_close() const
{
	return context_.should_close() || window_.should_close();
}

void kern::Engine::run()
{
	game_->on_start(context_);

	auto &timing = context_.get_timing();

	while (!should_close()) {
		timing.start_frame();

		glfwPollEvents();

		game_->on_update(context_, timing.get_delta_time());

		renderer_.render_current();
		window_.swap_buffers();

		timing.end_frame();
	}

	game_->on_quit(context_);
}