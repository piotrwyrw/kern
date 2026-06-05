// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_WINDOW_H
#define KERN_WINDOW_H

#include <kern/common.h>
#include <GLFW/glfw3.h>

typedef struct {
	GLFWwindow *window;
	GLFWmonitor *monitor;
	const char *title;
	int width;
	int height;
} KernWindow;

Error kern__window_create(GLFWwindow **dst, int width, int height,
			   const char *title, bool resizable,
			   GLFWmonitor *monitor);

Error kern_window_create(KernWindow *window, const char *title, int width,
			 int height, bool resizable, GLFWmonitor *monitor);

Error kern_window_dispose(KernWindow *window);

#endif //KERN_WINDOW_H
