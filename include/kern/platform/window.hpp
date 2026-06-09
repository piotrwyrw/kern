// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/core/properties.hpp>

struct GLFWwindow;

namespace kern::platform {
	class Window {
		const Properties &properties_;
		GLFWwindow *window_;

	public:
		explicit Window(const Properties &properties);
		~Window();

		[[nodiscard]] bool should_close() const;
		void swap_buffers() const;
	};
}