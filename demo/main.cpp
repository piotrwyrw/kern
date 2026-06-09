// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/engine.hpp>
#include <thread>
#include <chrono>

class DemoGame : public kern::Game {
public:
	void on_start(kern::Context &ctx) override
	{
	}

	void on_update(kern::Context &ctx, double delta_time) override
	{
	}

	void on_quit(kern::Context &ctx) override
	{
	}
};

int main()
{
	kern::Engine::start<DemoGame>({
		.title = "Kern Demo Game",
		.window_width = 1500,
		.window_height = 900,
		.fullscreen = true,
		.antialiasing = true
	});
	return 0;
}