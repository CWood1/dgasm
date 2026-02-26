#ifndef __AST_H__
#define __AST_H__

#include <stdint.h>

#define MAX_OPERANDS 3

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
} variable_t;

typedef struct {

} section_t;

typedef struct device_t {
  char* name;
  long value;

  struct device_t* next;
} device_t;

typedef enum {
  OPERAND_EXPR,        // normal expression (integer or identifier)
  OPERAND_INDIRECT,    // @expression
  OPERAND_SKIP         // skip condition keyword
} operand_kind_t;

typedef enum {
  SKIP_DONT,
  SKIP_SKP,
  SKIP_SZC,
  SKIP_SNC,
  SKIP_SZR,
  SKIP_SNR,
  SKIP_SEZ,  // Either carry or result are zero
  SKIP_SBN,  // Neither carry nor result are zero
} skip_condition_t;

typedef struct operand {
  operand_kind_t kind;
  union {
    expression_t *expr;      // for normal or indirect
    skip_condition_t skip;   // for skip keywords
  } u;
} operand_t;

typedef struct {
  int count;
  operand_t *items[MAX_OPERANDS];
} operand_list_t;

typedef struct opcode {
  char* mnemonic;
  operand_list_t* operands;
} opcode_t;

typedef enum {
  DIRECTIVE_ORG
} directive_type_t;

typedef struct directive {
  directive_type_t type;

  union {
    uint16_t org;
  };
} directive_t;

typedef enum {
  STMT_OPCODE,
  STMT_LABEL,
  STMT_VARIABLE,
  STMT_DIRECTIVE
} statement_type_t;

typedef struct statement {
  statement_type_t type;

  union {
    opcode_t*     opcode;
    char*         label;
    variable_t*   variable;
    directive_t*   directive;
  };

  struct statement* next;
} statement_t;

typedef struct {
  constant_t* constanttbl;
  device_t* devicetbl;
  
  statement_t* head;
  statement_t* tail;
} program_t;

#endif // __AST_H__
