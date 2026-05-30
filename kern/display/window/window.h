// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_WINDOW_H
#define KERN_WINDOW_H

#include <GLFW/glfw3.h>
#include <core/error/error.h>
#include <display/monitor/monitor.h>
#include <stdbool.h>

enum KernWindowPropsCursor {
  WINDOW_CURSOR_DISABLED,
  WINDOW_CURSOR_HIDDEN,
  WINDOW_CURSOR_CAPTURED,
  WINDOW_CURSOR_NORMAL
};

struct KernWindowProps {
  unsigned int window_width;
  unsigned int window_height;
  unsigned int sample_count;
  const char *window_title;
  enum KernWindowPropsCursor cursor;
  struct KernMonitor *monitor;
};

struct KernWindow {
  GLFWwindow *handle;
  struct KernMonitor *monitor;
  struct KernWindowProps *props;
};

enum KernResult kern_window_create(struct KernWindow *window,
                                   struct KernWindowProps *props);

enum KernResult kern_window_destroy(struct KernWindow *window);

bool kern_window_should_close(struct KernWindow *window);

#endif
