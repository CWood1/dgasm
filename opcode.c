#include "opcode.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

instruction_t instruction_tbl[] = {
  // Opcode      Size   Base encoding       Encoding type
  { "NIOS",      1,     0b0110000001000000, ENCODING_IONOXFER },
  /* { "NIOP",      1 }, */
  /* { "LDA",       1 }, */
  /* { "DOA",       1 }, */
  /* { "DOB",       1 }, */
  { "HALT",      1,     0b0110011000111111, ENCODING_CONSTANT },
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

int encode_instruction(uint16_t** buffer, int offset, opcode_t* opcode) {
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);
  instruction_t* instruction = NULL;

  for (int cur = 0; cur < instruction_count; cur++) {
    if (strcmp(opcode->mnemonic, instruction_tbl[cur].opcode) == 0) {
      instruction = &instruction_tbl[cur];
    }
  }

  if (instruction == NULL) {
    printf("Instruction %s does not exist\n", opcode->mnemonic);
    exit(1);
  }

  printf("Instruction 0%o\n", instruction->base_encoding);

  switch (instruction->encoding_type) {
  case ENCODING_CONSTANT:
    (*buffer)[offset] = instruction->base_encoding;
    break;
  default:
    printf("Attempted to encode an instruction of a type not yet supported.");
    exit(1);
  }

  return instruction->size;
}
