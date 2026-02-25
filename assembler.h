#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include "ast.h"
#include <stdint.h>

typedef struct offset {
  char* name;
  uint16_t address;

  struct offset* next;
} offset_t;

typedef struct {
    uint16_t *data;        // trimmed output buffer
    uint16_t size;         // number of 16-bit words
    uint16_t start_addr;   // first used address
} output_t;

#include "symbol_tbl.h"

offset_t* pass1(program_t* prog);
output_t pass2(program_t* prog, symboltbl_t* symbols);

#endif
