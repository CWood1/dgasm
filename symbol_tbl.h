#ifndef __SYMBOL_TBL_H__
#define __SYMBOL_TBL_H__\

#include "ast.h"

#include <stdint.h>

typedef struct symboltbl {
  char* name;
  uint16_t value;

  struct symboltbl* next;
} symboltbl_t;

#include "assembler.h"

symboltbl_t* resolve_symbols(program_t* prog, offset_t* offsets);
uint32_t find_symbol(symboltbl_t* symbols, const char* symbol);

#endif
