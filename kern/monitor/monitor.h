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
