#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"

static char **lines = NULL;
static int line_count = 0;
static int line_capacity = 0;
static int err_count = 0;

void source_add_line(const char *line) {
  if (line_count >= line_capacity) {
    line_capacity = line_capacity ? line_capacity * 2 : 128;
    lines = realloc(lines, sizeof(char*) * line_capacity);
  }

  lines[line_count++] = strdup(line);
}

const char *source_get_line(int lineno) {
  if (lineno <= 0 || lineno > line_count)
    return NULL;

  return lines[lineno - 1];
}

void report_error(statement_t* stmt, const char *fmt, ...) {
  va_list args;

  if (stmt) {
    fprintf(stderr, "Error on line %d: ", stmt->lineno);
  } else {
    fprintf(stderr, "Error: ");
  }

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");

  if (stmt) {
    const char* line = source_get_line(stmt->lineno);
    if (line)
      fprintf(stderr, "  %s\n", line);
  }

  err_count += 1;
}

int get_err_count() {
  return err_count;
}
