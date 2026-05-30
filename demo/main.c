// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern.h>

int main(void) {
  kern_init();

  struct KernWindowProps props = {.window_width = 1500,
                                  .window_height = 900,
                                  .sample_count = 10,
                                  .window_title = "Kern Engine Demo",
                                  .cursor = WINDOW_CURSOR_DISABLED};
  struct KernWindow window;

  if (kern_window_create(&window, &props) != RESULT_OK) {
    kern_print_error();
    return 1;
  }

  while (!kern_window_should_close(&window)) {
    glfwPollEvents();
  }

  if (kern_window_destroy(&window) != RESULT_OK) {
    kern_print_error();
    return 1;
  }

  if (kern_quit() != RESULT_OK) {
    kern_print_error();
    return 1;
  };

  return 0;
}
