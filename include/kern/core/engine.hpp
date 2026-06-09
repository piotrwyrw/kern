// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/rendering/renderer.hpp>
#include <kern/platform/window.hpp>
#include <kern/core/game.hpp>

namespace kern {
	class Engine {
		Context context_;

		const std::shared_ptr<Game> game_;
		const Properties &properties_;
		const platform::Window window_;

		rendering::Renderer renderer_;

		void run();

	public:
		explicit Engine(std::shared_ptr<Game> game, const Properties &properties);

		[[nodiscard]] bool should_close() const;

		template <std::derived_from<Game> T> static std::unique_ptr<Engine> start(
			const Properties &properties)
		{
			auto game = std::make_shared<T>();
			return std::make_unique<Engine>(game, properties);
		}
	};
}