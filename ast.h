#ifndef __AST_H__
#define __AST_H__

typedef struct {
  char* name;
  long value;
} constant_t;

typedef enum {
  VARIABLE_STRING,
  VARIABLE_NUMBER,
} variable_type_t;

typedef union {
  char* str;
  long number;
} variable_value_t;

typedef struct {
  variable_type_t type;
  char* name;
  variable_value_t value;
} variable_t;

typedef struct {

} section_t;

typedef struct {
  char* name;
  long value;
} device_t;

typedef enum {
  constant,
  variable,
  section,
  device,
} type_t;

typedef union {
  constant_t constant;
  variable_t variable;
  section_t section;
  device_t device;
} node_t;

typedef struct {
  type_t type;
  node_t node;
} program;

#endif // __AST_H__
