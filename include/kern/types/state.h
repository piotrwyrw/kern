// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_TYPES_STATE_H
#define KERN_TYPES_STATE_H

#include <kern/window/window.h>

typedef enum {
	// The default state when nothing has been done
	KERN_STATUS_NOT_INITIALIZED = 0,

	// Kern has been initialized and is running
	KERN_STATUS_RUNNING = 1,

	// Kern was terminated. Recovery from this state is impossible.
	KERN_STATUS_TERMINATED = 2
} KernStatus;

typedef struct GLFWwindow GLFWwindow;

typedef struct {
	KernStatus status;
	KernWindow window;
	GLFWmonitor *monitor;
} KernState;

#endif //KERN_TYPES_STATE_H
