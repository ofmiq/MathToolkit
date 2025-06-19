#include "input.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

bool read_line(char *buf, int bufsize) {
  if (!fgets(buf, bufsize, stdin)) {
    return false;
  }
  size_t len = strlen(buf);
  if (len && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }
  return true;
}

bool read_int(const char *prompt, int *out) {
  char line[MAX_LINE_LEN];
  char *endptr;
  long val;

  printf("%s", prompt);
  if (!read_line(line, sizeof(line))) {
    return false;
  }

  errno = 0;
  val = strtol(line, &endptr, 10);
  if (errno != 0 || endptr == line || *endptr != '\0') {
    return false;
  }
  *out = (int)val;
  return true;
}

bool read_double(const char *prompt, double *out) {
  char line[MAX_LINE_LEN];
  char *endptr;
  double val;

  printf("%s", prompt);
  if (!read_line(line, sizeof(line))) {
    return false;
  }

  errno = 0;
  val = strtod(line, &endptr);
  if (errno != 0 || endptr == line || *endptr != '\0') {
    return false;
  }
  *out = val;
  return true;
}
