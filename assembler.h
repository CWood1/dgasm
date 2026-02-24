#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include "ast.h"
#include <stdint.h>

typedef struct offset {
  char* name;
  uint16_t address;

  struct offset* next;
} offset_t;

offset_t* pass1(program_t* prog);

#endif
