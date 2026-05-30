// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <core/error/error.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

struct KernError kern_last_error = {0};

void kern_error_set(const char *message, const char *filename,
                    unsigned int line) {
  kern_last_error.is_present = true;
  kern_last_error.message = message;
  kern_last_error.filename = filename;
  kern_last_error.line = line;
}

enum KernResult kern_poll_glfw_error() {
  const char *error_msg;
  int error = glfwGetError(&error_msg);
  if (error != GLFW_NO_ERROR) {
    kern_error_set(error_msg, NULL, 0);
    return RESULT_ERROR;
  }
  return RESULT_OK;
}

void kern_clear_error() {
  kern_last_error.is_present = false;
  kern_last_error.message = NULL;
  kern_last_error.filename = NULL;
  kern_last_error.line = 0;
}

void kern_print_error() {
  struct KernError *e = &kern_last_error;
  if (e->message && e->filename && e->line > 0) {
    fprintf(stderr, "[Error in %s:%d] %s\n", e->filename, e->line, e->message);
  } else if (e->message && e->filename) {
    fprintf(stderr, "[Error in %s] %s", e->filename, e->message);
  } else if (e->message) {
    fprintf(stderr, "[Error] %s", e->message);
  }
  kern_clear_error();
}