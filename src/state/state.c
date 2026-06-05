// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/state/state.h>
#include <kern/window/window.h>

KernState g_state = { .status = KERN_STATUS_NOT_INITIALIZED };

bool kern__is_running()
{
	return g_state.status == KERN_STATUS_RUNNING;
}

bool kern__is_uninitialized()
{
	return g_state.status == KERN_STATUS_NOT_INITIALIZED;
}

bool kern__is_terminated()
{
	return g_state.status == KERN_STATUS_TERMINATED;
}

const KernState *kern__state_get()
{
	return &g_state;
}

bool kern_is_running()
{
	return g_state.status == KERN_STATUS_RUNNING
	       && !glfwWindowShouldClose(g_state.window.window);
}

const KernWindow *kern_get_window()
{
	return &g_state.window;
}

Error kern__start(const char *title, int width, int height, bool resizable,
                  GLFWmonitor *monitor)
{
	Error e = kern_window_create(&g_state.window, title, width, height,
	                             resizable, monitor);

	if (e.code != KERN_NO_ERROR) {
		return e;
	}

	g_state.status = KERN_STATUS_RUNNING;
	g_state.monitor = monitor;

	glewInit();

	return OK();
}

Error kern_start_fullscreen(const char *title)
{
	if (!kern__is_uninitialized()) {
		return ERROR(KERN_BAD_STATUS, "Kern is not uninitialized");
	}

	TRY_GLFW(glfwInit());

	GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
	PROPAGATE_GLFW;

	if (!primary_monitor) {
		return ERROR(KERN_GLFW_ERROR, "Primary monitor not found");
	}

	const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
	PROPAGATE_GLFW;

	if (!video_mode) {
		return ERROR(KERN_GLFW_ERROR,
		             "Could not retrieve video mode of primary monitor");
	}

	return kern__start(title, video_mode->width, video_mode->height, false,
	                   primary_monitor);
}

Error kern_start_windowed(const char *title, int width, int height,
                          bool resizable)
{
	if (!kern__is_uninitialized()) {
		return ERROR(KERN_BAD_STATUS, "Kern is not uninitialized");
	}

	TRY_GLFW(glfwInit());

	return kern__start(title, width, height, resizable, NULL);
}

Error kern_dispose()
{
	if (!kern__is_running()) {
		return ERROR(KERN_BAD_STATUS, "Kern is not initialized");
	}

	TRY_GLFW(glfwHideWindow(g_state.window.window));
	TRY_GLFW(glfwDestroyWindow(g_state.window.window));
	TRY_GLFW(glfwTerminate());

	g_state.status = KERN_STATUS_TERMINATED;

	return OK();
}