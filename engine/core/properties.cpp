// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/core/properties.hpp>
#include <kern/exception/exception.hpp>

void kern::validate_properties(const Properties &properties)
{
	if (!properties.window_width || !properties.window_height)
		throw exception::Exception(std::format(
			"Game window is too small: {}x{}",
			properties.window_width,
			properties.window_height));

	if (properties.title.empty())
		throw exception::Exception("Game window title is empty");
}
