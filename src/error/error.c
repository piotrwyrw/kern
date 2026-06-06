// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <stdio.h>
#include <kern/error/error.h>

void kern_print_error(const Error *error)
{
	fprintf(stderr, "Error in function %s() in file %s on line %d)"
			":\n   ->  %s\n", error->function, error->file,
			error->line, error->message);
}