#ifndef KERN_WINDOW_H
#define KERN_WINDOW_H

#include <GLFW/glfw3.h>

struct KernWindow {
  GLFWwindow *handle;
};

void kern_window_create(struct KernWindow *ptr, const char *title);

#endif
