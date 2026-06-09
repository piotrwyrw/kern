// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "timing.hpp"

namespace kern {
	class Context {
		Timing timing_;
		bool should_close_;

	public:
		Context();

		[[nodiscard]] Timing &get_timing();

		[[nodiscard]] bool should_close() const;
		void request_shutdown();
	};
}