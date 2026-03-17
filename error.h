#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>
#include "ast.h"

void source_add_line(const char *line);
const char *source_get_line(int lineno);
void report_error(statement_t* stmt, const char *fmt, ...);
int get_err_count();
void free_lines();

#endif
