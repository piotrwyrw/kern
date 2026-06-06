// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_STATE_H
#define KERN_STATE_H

#include <kern/types/error.h>
#include <stdbool.h>

Error kern_start_fullscreen(const char *title);

Error kern_start_windowed(const char *title, int width, int height,
                          bool resizable);

Error kern_dispose();

#endif // KERN_STATE_H