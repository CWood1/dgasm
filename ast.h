#ifndef __AST_H__
#define __AST_H__

typedef enum {
    EXPR_INTEGER,
    EXPR_IDENTIFIER,
    EXPR_BINARY,
    EXPR_UNARY
} expr_kind_t;

typedef enum {
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_NOT
} expr_op_t;

typedef struct expression {
    expr_kind_t kind;
    union {
        long number;                 // for EXPR_INTEGER
        char *identifier;            // for EXPR_IDENTIFIER
        struct {                      // for EXPR_BINARY
            expr_op_t op;
            struct expression *left;
            struct expression *right;
        } binary;
        struct {                      // for EXPR_UNARY
            expr_op_t op;
            struct expression *child;
        } unary;
    } u;
} expression_t;

typedef struct constant_t {
  char* name;
  expression_t* value;

  struct constant_t* next;
} constant_t;

typedef enum {
  VARIABLE_STRING,
  VARIABLE_NUMBER,
} variable_type_t;

typedef union {
  char* str;
  expression_t* number;
} variable_value_t;

typedef struct variable_t {
  variable_type_t type;
  char* name;
  variable_value_t value;

  struct variable_t* next;
} variable_t;

typedef struct {

} section_t;

typedef struct device_t {
  char* name;
  long value;

  struct device_t* next;
} device_t;

typedef struct {
  constant_t* constanttbl;
  variable_t* variabletbl;
  device_t* devicetbl;
} program_t;

#endif // __AST_H__
