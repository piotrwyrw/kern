#include <error/error.h>

#include <stdio.h>
#include <stddef.h>

struct KernError kern_last_error = {0};

void kern_set_msg_error(const char *message) {
  kern_last_error.type = KERN_ERR_MSG;
  kern_last_error.message = message;
  kern_last_error.filename = NULL;
  kern_last_error.line = 0;
}

void kern_set_msg_file_error(const char *message, const char *filename) {
  kern_last_error.type = KERN_ERR_MSG_FILE;
  kern_last_error.message = message;
  kern_last_error.filename = filename;
  kern_last_error.line = 0;
}

void kern_set_msg_file_line_error(const char *message, const char *filename,
                                  unsigned int line) {
  kern_last_error.type = KERN_ERR_MSG_FILE_LINE;
  kern_last_error.message = message;
  kern_last_error.filename = filename;
  kern_last_error.line = line;
}

void kern_clear_error() {
  kern_last_error.type = KERN_ERR_NONE;
  kern_last_error.message = NULL;
  kern_last_error.filename = NULL;
  kern_last_error.line = 0;
}

void kern_print_error() {
  switch (kern_last_error.type) {
  case KERN_ERR_NONE:
    break;
  case KERN_ERR_MSG:
    fprintf(stderr, "[Error] %s", kern_last_error.message);
    break;
  case KERN_ERR_MSG_FILE:
    fprintf(stderr, "[Error] %s: %s", kern_last_error.filename,
            kern_last_error.message);
    break;
  case KERN_ERR_MSG_FILE_LINE:
    fprintf(stderr, "[Error] %s Line %d: %s", kern_last_error.filename,
            kern_last_error.line, kern_last_error.message);
    break;
  }
}
