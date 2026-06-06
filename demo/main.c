// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/kern.h>

int main(void)
{
	// Error err = kern_start_windowed("Hello, Kern!", 1000, 700, false);
	Error err = kern_start_fullscreen("Hello, Kern!");

	if (err.code != KERN_NO_ERROR) {
		kern_print_error(&err);
		return 1;
	}

	kern_dispose();

	return 0;
}