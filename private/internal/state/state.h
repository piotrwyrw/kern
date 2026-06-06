// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_INTERNAL_STATE_H
#define KERN_INTERNAL_STATE_H

#include <kern/kern.h>

extern KernState KERN_STATE;

Error kern_start_ex(const char *title, int width, int height, bool resizable,
                GLFWmonitor *monitor);

#endif //KERN_INTERNAL_STATE_H