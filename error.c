#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"

typedef struct {
    char *filename;
    char **lines;
    int line_count;
    int line_capacity;
} file_source_t;

static file_source_t *files = NULL;
static int file_count = 0;
static int file_capacity = 0;

static int err_count = 0;

static file_source_t* get_file(const char *filename) {
  for (int i = 0; i < file_count; i++) {
    if (strcmp(files[i].filename, filename) == 0)
      return &files[i];
  }

  if (file_count >= file_capacity) {
    file_capacity = file_capacity ? file_capacity * 2 : 8;
    files = realloc(files, sizeof(file_source_t) * file_capacity);
  }

  file_source_t *f = &files[file_count++];
  f->filename = strdup(filename);
  f->lines = NULL;
  f->line_count = 0;
  f->line_capacity = 0;

  return f;
}

static file_source_t* find_file(const char *filename) {
  for (int i = 0; i < file_count; i++) {
    if (strcmp(files[i].filename, filename) == 0)
      return &files[i];
  }
  return NULL;
}

void source_add_line(char* filename, const char *line) {
  file_source_t *f = get_file(filename);

  if (f->line_count >= f->line_capacity) {
    f->line_capacity = f->line_capacity ? f->line_capacity * 2 : 128;
    f->lines = realloc(f->lines, sizeof(char*) * f->line_capacity);
  }

  f->lines[f->line_count++] = strdup(line);
}

const char *source_get_line(const char *filename, int lineno) {
  file_source_t *f = find_file(filename);

  if (f == NULL) {
    fprintf(stderr, "Attempted to print source from a nonexistent file %s\n", filename);
    exit(1);
  }

  if (lineno <= 0 || lineno > f->line_count)
    return NULL;

  return f->lines[lineno - 1];
}

void report_error(statement_t* stmt, const char *fmt, ...) {
  va_list args;

  if (stmt) {
    fprintf(stderr, "%s:%d - ", stmt->fn, stmt->lineno);
  } else {
    fprintf(stderr, "Error: ");
  }

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");

  if (stmt) {
    const char* line = source_get_line(stmt->fn, stmt->lineno);
    if (line)
      fprintf(stderr, "  %s\n", line);
  }

  err_count += 1;
}

void report_syntax_error(char* fn, int lineno, const char* fmt, ...) {
  va_list args;

  fprintf(stderr, "%s:%d - ", fn, lineno);

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fprintf(stderr, "\n");

  const char* line = source_get_line(fn, lineno);
  if (line)
    fprintf(stderr, "  %s\n", line);

  err_count += 1;
}

int get_err_count() {
  return err_count;
}

void free_lines(void){
  for (int i = 0; i < file_count; i++) {
    file_source_t *f = &files[i];

    // Free each line
    for (int j = 0; j < f->line_count; j++) {
      free(f->lines[j]);
    }

    // Free line array
    free(f->lines);
    f->lines = NULL;

    // Free filename
    free(f->filename);
    f->filename = NULL;

    f->line_count = 0;
    f->line_capacity = 0;
  }

  // Free file table
  free(files);
  files = NULL;

  file_count = 0;
  file_capacity = 0;
}
