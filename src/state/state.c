// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/kern.h>
#include <internal/state/state.h>

KernState KERN_STATE = { .status = KERN_STATUS_UNINITIALIZED };

Error kern_start_ex(const char *title, int width, int height, bool resizable,
                GLFWmonitor *monitor)
{
	Error e = kern_window_create(&KERN_STATE.window, title, width, height,
	                             resizable, monitor);

	if (e.code != KERN_NO_ERROR) {
		return e;
	}

	KERN_STATE.status = KERN_STATUS_INITIALIZED;
	KERN_STATE.monitor = monitor;

	glewInit();

	return OK();
}

Error kern_start_fullscreen(const char *title)
{
	if (KERN_STATE.status != KERN_STATUS_UNINITIALIZED) {
		return ERROR(KERN_BAD_STATUS, "Kern is not uninitialized");
	}

	TRY_GLFW(glfwInit());

	GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
	PROPAGATE_GLFW_ERROR();

	if (!primary_monitor) {
		return ERROR(KERN_GLFW_ERROR, "Primary monitor not found");
	}

	const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
	PROPAGATE_GLFW_ERROR();

	if (!video_mode) {
		return ERROR(KERN_GLFW_ERROR,
		             "Could not retrieve video mode of primary monitor");
	}

	return kern_start_ex(title, video_mode->width, video_mode->height, false,
	                 primary_monitor);
}

Error kern_start_windowed(const char *title, int width, int height,
                        bool resizable)
{
	if (KERN_STATE.status != KERN_STATUS_UNINITIALIZED) {
		return ERROR(KERN_BAD_STATUS, "Kern is not uninitialized");
	}

	TRY_GLFW(glfwInit());

	return kern_start_ex(title, width, height, resizable, NULL);
}

Error kern_dispose()
{
	if (KERN_STATE.status != KERN_STATUS_INITIALIZED) {
		return ERROR(KERN_BAD_STATUS, "Kern is not initialized");
	}

	TRY_GLFW(glfwHideWindow(KERN_STATE.window.window));
	TRY_GLFW(glfwDestroyWindow(KERN_STATE.window.window));
	TRY_GLFW(glfwTerminate());

	KERN_STATE.status = KERN_STATUS_TERMINATED;

	return OK();
}