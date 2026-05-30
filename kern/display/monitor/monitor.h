// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_MONITOR_H
#define KERN_MONITOR_H

#include <GLFW/glfw3.h>

struct KernMonitor {
  const GLFWmonitor *handle;
  unsigned int width;
  unsigned int height;
};

void kern_monitor_load_primary(struct KernMonitor *monitor);

#endif
