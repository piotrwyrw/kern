// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <ctime>
#include <kern/core/context.hpp>

kern::Context::Context()
	: timing_({}),
	  should_close_(false)
{
}

kern::Timing &kern::Context::get_timing()
{
	return timing_;
}

bool kern::Context::should_close() const
{
	return should_close_;
}

void kern::Context::request_shutdown()
{
	should_close_ = true;
}