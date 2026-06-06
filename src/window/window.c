#include <kern/kern.h>
#include <internal/state/state.h>

Error kern_window_create_ex(GLFWwindow **dst,
                          const int width, const int height,
                          const char *title, const bool resizable,
                          GLFWmonitor *monitor)
{
	TRY_GLFW(glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE));
	TRY_GLFW(glfwWindowHint(GLFW_RESIZABLE, resizable));
	TRY_GLFW(glfwWindowHint(GLFW_SAMPLES, 4));
	TRY_GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
	TRY_GLFW(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
	TRY_GLFW(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
	TRY_GLFW(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE));

	GLFWwindow *window = glfwCreateWindow(width, height,
	                                      title, monitor, NULL);

	PROPAGATE_GLFW_ERROR();

	TRY_GLFW(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
	TRY_GLFW(glfwMakeContextCurrent(window));
	TRY_GLFW(glfwSwapInterval(0));
	TRY_GLFW(glfwShowWindow(window));

	*dst = window;

	return OK();
}

Error kern_window_create(KernWindow *window, const char *title, int width,
                         int height, bool resizable, GLFWmonitor *monitor)
{
	if (KERN_STATE.status != KERN_STATUS_UNINITIALIZED) {
		return ERROR(KERN_BAD_STATUS, "Kern is not uninitialized.");
	}

	GLFWwindow *glfw_window;
	Error e = kern_window_create_ex(&glfw_window, width, height, title,
	                              resizable, monitor);

	if (e.code != KERN_NO_ERROR) {
		return e;
	}

	window->window = glfw_window;
	window->monitor = monitor;
	window->title = title;
	window->width = width;
	window->height = height;

	return OK();
}