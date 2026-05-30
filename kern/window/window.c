#include <window/window.h>

enum KernResult kern_window_create(struct KernWindow *window,
                                   struct KernWindowProps *props) {
  int sample_count = (int)props->sample_count;
  int width = (int)props->window_width;
  int height = (int)props->window_height;
  const char *title = props->window_title;

  int cursor_mode;
  switch (props->cursor) {
  case WINDOW_CURSOR_DISABLED:
    cursor_mode = GLFW_CURSOR_DISABLED;
    break;

  case WINDOW_CURSOR_HIDDEN:
    cursor_mode = GLFW_CURSOR_HIDDEN;
    break;

  case WINDOW_CURSOR_CAPTURED:
    cursor_mode = GLFW_CURSOR_CAPTURED;
    break;

  default:
  case WINDOW_CURSOR_NORMAL:
    cursor_mode = GLFW_CURSOR_NORMAL;
    break;
  }

  GLFW_TRY(glfwDefaultWindowHints());

  GLFW_TRY(glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE));
  GLFW_TRY(glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE));
  GLFW_TRY(glfwWindowHint(GLFW_SAMPLES, sample_count));
  GLFW_TRY(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
  GLFW_TRY(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
  GLFW_TRY(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
  GLFW_TRY(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE));

  GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!handle) {
    GLFW_ERR_PROPAGATE;
  }

  GLFW_TRY(glfwSetInputMode(handle, GLFW_CURSOR, cursor_mode));

  GLFW_TRY(glfwSetCursor(handle, NULL));

  GLFW_TRY(glfwMakeContextCurrent(handle));
  GLFW_TRY(glfwSwapInterval(0));
  GLFW_TRY(glfwShowWindow(handle));

  window->props = props;
  window->handle = handle;

  return RESULT_OK;
}

enum KernResult kern_window_destroy(struct KernWindow *window) {
  GLFW_TRY(glfwDestroyWindow(window->handle));
  return RESULT_OK;
}

bool kern_window_should_close(struct KernWindow *window) {
  return glfwWindowShouldClose(window->handle) ? true : false;
}