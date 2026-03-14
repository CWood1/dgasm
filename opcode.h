#ifndef __OPCODE_H__
#define __OPCODE_H__

#include "ast.h"
#include "symbol_tbl.h"
#include <stdint.h>

#define CPU_NOVA1        0x01
#define CPU_NOVA3        0x02
#define CPU_NOVA4        0x03
#define CPU_ECLIPSE_S140 0x04

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
  ENCODING_TRAP,
  ENCODING_NOVA4BYTE,
} instruction_encoding_t;

typedef struct {
  char* opcode;
  int size;

  uint16_t base_encoding;
  instruction_encoding_t encoding_type;

  int cpu_types;
} instruction_t;

instruction_t find_instruction(statement_t* stmt, int cpu);
int encode_instruction(uint16_t** buffer, int offset, statement_t* opcode_stmt, symboltbl_t* symbols, int cpu);

#endif
