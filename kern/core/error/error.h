// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_ERROR_H
#define KERN_ERROR_H

#include <stdbool.h>

/**
 * Invoke a GLFW function and detect potential errors
 */
#define GLFW_TRY(call)                                                         \
  do {                                                                         \
    call;                                                                      \
    if (kern_poll_glfw_error() != RESULT_OK) {                            \
      return RESULT_ERROR;                                                     \
    }                                                                          \
  } while (0)

/**
 * Invoke call() and propagate potential errors
 */
#define TRY(call)                                                              \
  do {                                                                         \
    enunm KernResult _result = call;                                           \
    if (_result != RESULT_OK) {                                                \
      return _result;                                                          \
    }                                                                          \
  } while (0)

/**
 * Used as the return type of functions that may report an error
 */
enum KernResult { RESULT_OK = 0, RESULT_ERROR = 1 };

struct KernError {
  bool is_present;
  const char *message;
  const char *filename;
  unsigned int line;
};

extern struct KernError kern_last_error;

void kern_error_set(const char *message, const char *filename, unsigned int line);

enum KernResult kern_poll_glfw_error();

void kern_clear_error();

void kern_print_error();

#endif
