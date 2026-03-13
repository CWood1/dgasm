#ifndef __OPCODE_H__
#define __OPCODE_H__

#include "ast.h"
#include "symbol_tbl.h"
#include <stdint.h>

typedef enum {
  ENCODING_IO,
  ENCODING_IONOXFER,
  ENCODING_FLOW,
  ENCODING_EXTENDEDFLOW,
  ENCODING_CONSTANT,
  ENCODING_ALU,
  ENCODING_LOAD,
  ENCODING_EXTENDEDLOAD,
  ENCODING_SAVE,
  ENCODING_TWOACC,
  ENCODING_ONEACC,
  ENCODING_IMMEDIATE,
  ENCODING_EXTENDEDIMMEDIATE,
  ENCODING_FLOATEXLOAD,
  ENCODING_FLOATEXLOADNOACC,
  ENCODING_PSHJ,
  ENCODING_XOP,
  ENCODING_XOP1,
} instruction_encoding_t;

typedef struct {
  char* opcode;
  int size;

  uint16_t base_encoding;
  instruction_encoding_t encoding_type;
} instruction_t;

instruction_t find_instruction(statement_t* stmt);
int encode_instruction(uint16_t** buffer, int offset, statement_t* opcode_stmt, symboltbl_t* symbols);

#endif
