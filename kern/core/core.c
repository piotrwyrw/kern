#include <core/core.h>

#include <GLFW/glfw3.h>

void kern_init() {
  glfwInit();
}

void kern_quit() {
  glfwTerminate();
}
