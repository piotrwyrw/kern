// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/common.h>

void kern_error_print(const Error *error)
{
	fprintf(stderr, "Error: %s (%s, %s : %d)\n", error->message,
	        error->function,
	        error->file, error->line);
}
