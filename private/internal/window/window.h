// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_INTERNAL_WINDOW_H
#define KERN_INTERNAL_WINDOW_H

#include <kern/kern.h>

Error kern_window_create_ex(GLFWwindow **dst, int width, int height,
			   const char *title, bool resizable,
			   GLFWmonitor *monitor);

#endif //KERN_INTERNAL_WINDOW_H
