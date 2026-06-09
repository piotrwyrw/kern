// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/core/timing.hpp>

void kern::Timing::start_frame()
{
	frame_start_time_ = get_time_now();
}

void kern::Timing::end_frame()
{
	frame_delta_time_ = get_time_now() - frame_start_time_;
}

[[nodiscard]] double kern::Timing::get_time_now() const
{
	return glfwGetTime();
}

[[nodiscard]] double kern::Timing::get_delta_time() const
{
	return frame_delta_time_;
}