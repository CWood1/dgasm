#ifndef __OPCODE_H__
#define __OPCODE_H__

#include "ast.h"
#include "symbol_tbl.h"
#include <stdint.h>

typedef enum {
  ENCODING_IO,
  ENCODING_IONOXFER,
  ENCODING_FLOW,
  ENCODING_CONSTANT,
  ENCODING_ALU,
  ENCODING_LOAD,
  ENCODING_EXTENDEDLOAD,
  ENCODING_SAVE,
  ENCODING_TWOACC,
} instruction_encoding_t;

typedef struct {
  char* opcode;
  int size;

  uint16_t base_encoding;
  instruction_encoding_t encoding_type;
} instruction_t;

instruction_t find_instruction(char* opcode);
int encode_instruction(uint16_t** buffer, int offset, opcode_t* opcode, symboltbl_t* symbols);

#endif
