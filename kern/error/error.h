#ifndef KERN_ERROR_H
#define KERN_ERROR_H

/**
 * Propagate any present GLFW error
 */
#define GLFW_ERR_PROPAGATE                                                     \
  do {                                                                         \
    const char *_glfw_err_desc;                                                \
    int _glfw_err = glfwGetError(&_glfw_err_desc);                             \
    if (_glfw_err != GLFW_NO_ERROR) {                                          \
      kern_set_msg_error(_glfw_err_desc);                                      \
      return RESULT_ERROR;                                                     \
    }                                                                          \
  } while (0)

/**
 * Invoke a GLFW function and detect potential errors
 */
#define GLFW_TRY(call)                                                         \
  do {                                                                         \
    call;                                                                      \
    GLFW_ERR_PROPAGATE;                                                        \
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

enum KernResult { RESULT_OK = 0, RESULT_ERROR = 1 };

enum KernErrorType {
  /**
   * No errors
   */
  KERN_ERR_NONE = 0,

  /**
   * The error message is set
   */
  KERN_ERR_MSG = 1,

  /**
   * The error message and file name are set
   */
  KERN_ERR_MSG_FILE = 2,

  /**
   * The error message, file name, and line number are set
   */
  KERN_ERR_MSG_FILE_LINE = 3
};

struct KernError {
  enum KernErrorType type;
  const char *message;
  const char *filename;
  unsigned int line;
};

extern struct KernError kern_last_error;

void kern_set_msg_error(const char *message);

void kern_set_msg_file_error(const char *message, const char *filename);

void kern_set_msg_file_line_error(const char *message, const char *filename,
                                  unsigned int line);

void kern_clear_error();

void kern_print_error();

#endif
