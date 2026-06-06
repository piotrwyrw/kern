// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_TYPES_WINDOW_H
#define KERN_TYPES_WINDOW_H

#include <kern/kern.h>

typedef struct {
	GLFWwindow *window;
	GLFWmonitor *monitor;
	const char *title;
	int width;
	int height;
} KernWindow;

#endif //KERN_TYPES_WINDOW_H