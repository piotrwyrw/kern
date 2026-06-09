// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/properties.hpp>
#include <kern/core/context.hpp>

namespace kern {
	class Game {
	public:
		virtual ~Game() = default;

		virtual void on_start(Context &ctx) = 0;
		virtual void on_update(Context &ctx, double delta_time) = 0;
		virtual void on_quit(Context &ctx) = 0;
	};
}