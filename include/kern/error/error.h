// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_ERROR_H
#define KERN_ERROR_H

#include <kern/kern.h>

#define ERROR(_code, _message)                                                 \
  (Error) {                                                                    \
    .code = _code, .message = _message, .function = __FUNCTION__,              \
    .file = __FILE__, .line = __LINE__                                         \
  }

#define OK() ERROR(KERN_NO_ERROR, "No error")

#define PROPAGATE_GLFW_ERROR()                                                         \
  do {                                                                         \
    const char *_glfw_err_desc;                                                \
    if (glfwGetError(&_glfw_err_desc) != GLFW_NO_ERROR) {                      \
      return ERROR(KERN_GLFW_ERROR, _glfw_err_desc);                           \
    }                                                                          \
  } while (0)

#define TRY_GLFW(call)                                                         \
  do {                                                                         \
    call;                                                                      \
    PROPAGATE_GLFW_ERROR();                                                    \
  } while (0)

void kern_print_error(const Error *error);

#endif // KERN_ERROR_H