// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_STATE_H
#define KERN_STATE_H

#include <kern/common.h>
#include <kern/types/error.h>
#include <kern/types/state.h>

extern KernState g_state;

bool kern__is_running();

bool kern__is_uninitialized();

bool kern__is_terminated();

const KernState *kern__state_get();

bool kern_is_running();

const KernWindow *kern_get_window();

Error kern__start(const char *title, int width, int height, bool resizable,
                  GLFWmonitor *monitor);

Error kern_start_fullscreen(const char *title);

Error kern_start_windowed(const char *title, int width, int height,
                          bool resizable);

Error kern_dispose();

#endif // KERN_STATE_H