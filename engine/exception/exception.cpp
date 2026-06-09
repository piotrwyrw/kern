// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/exception/exception.hpp>
#include <tinyfiledialogs.h>

kern::exception::Exception::Exception(std::string message)
	: message_(std::move(message))
{
}

const char *kern::exception::Exception::what() const noexcept
{
	return message_.c_str();
}

void kern::exception::show_message_box(const Exception &e)
{
	tinyfd_messageBox("Error", e.what(), "ok", "error", 0);
}

void kern::exception::handle_all(const std::function<void()> &fn)
{
	try {
		fn();
	} catch (Exception &e) {
		show_message_box(e);
	}
}