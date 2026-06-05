// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_TYPES_ERROR_H
#define KERN_TYPES_ERROR_H

typedef enum {
	KERN_NO_ERROR = 0,

	KERN_BAD_STATUS = 1,
	KERN_OUT_OF_MEMORY_ERROR = 2,

	KERN_GLFW_ERROR = 3,
	KERN_GLEW_ERROR = 4,
} ErrorCode;

typedef struct {
	ErrorCode code;
	const char *message;
	const char *function;
	const char *file;
	int line;
} Error;

#endif //KERN_TYPES_ERROR_H
