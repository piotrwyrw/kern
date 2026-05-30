// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <display/monitor/monitor.h>

void kern_monitor_load_primary(struct KernMonitor *monitor) {
  GLFWmonitor *primary = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(primary);

  monitor->width = mode->width;
  monitor->height = mode->height;
  monitor->handle = (const GLFWmonitor *)primary;
}