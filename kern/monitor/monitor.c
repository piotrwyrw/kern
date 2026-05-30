#include <monitor/monitor.h>

void kern_monitor_load_primary(struct KernMonitor *monitor) {
  GLFWmonitor *primary = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(primary);

  monitor->width = mode->width;
  monitor->height = mode->height;
  monitor->handle = (const GLFWmonitor *)primary;
}