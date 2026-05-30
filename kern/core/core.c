// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <core/core.h>

#include <GLFW/glfw3.h>

void kern_init() { glfwInit(); }

enum KernResult kern_quit() {
  GLFW_TRY(glfwTerminate());
  return RESULT_OK;
}
