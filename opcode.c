#include "opcode.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

instruction_t instruction_tbl[] = {
  // Opcode    Size
  { "NIOS",      1 },
  { "NIOP",      1 },
  { "LDA",       1 },
  { "DOA",       1 },
  { "DOB",       1 },
};

instruction_t find_instruction(char* opcode) {
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);

  for (int cur = 0; cur < instruction_count; cur++) {
    if (strcmp(opcode, instruction_tbl[cur].opcode) == 0) {
      return instruction_tbl[cur];
    }
  }

  printf("Instruction %s does not exist\n", opcode);
  exit(1);
}
