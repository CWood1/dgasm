#include "opcode.h"
#include "eval.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

instruction_t instruction_tbl[] = {
  // Opcode      Size   Base encoding       Encoding type
  { "NIOS",      1,     0b0110000001000000, ENCODING_IONOXFER },
  { "SKPDN",     1,     0b0110011101000000, ENCODING_IONOXFER },
  { "SKPBZ",     1,     0b0110011101000000, ENCODING_IONOXFER },
  { "DIAS",      1,     0b0110000101000000, ENCODING_IO },
  { "DOAS",      1,     0b0110001001000000, ENCODING_IO },

  { "JMP",       1,     0b0000000000000000, ENCODING_FLOW },
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

void encode_ionoxfer_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  if (opcode->operands->count != 1) {
    printf("Instruction %s requires 1 operand, found %d\n", opcode->mnemonic, opcode->operands->count);
    exit(1);
  }
  if (opcode->operands->items[0]->kind != OPERAND_EXPR) {
    printf("Instruction %s requries a device number.\n", opcode->mnemonic);
    exit(1);
  }

  uint16_t device = eval(opcode->operands->items[0]->u.expr, symbols);

  if (device > 077) {
    printf("Instruction %s requires a device. Device 0%o is out of bounds.\n", opcode->mnemonic, device);
    exit(1);
  }

  encoding |= device;
  (*buffer)[offset] = encoding;
}

void encode_io_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  if (opcode->operands->count != 2) {
    printf("Instruction %s requires 2 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
    exit(1);
  }
  if (opcode->operands->items[1]->kind != OPERAND_EXPR) {
    printf("Instruction %s requries a device number.\n", opcode->mnemonic);
    exit(1);
  }

  uint16_t accumulator = eval(opcode->operands->items[0]->u.expr, symbols) << 11;
  if (accumulator > 0x2000) {
    printf("Accumulator out of range. Should be 0, 1, 2, or 3.\n");
    exit(1);
  }
  uint16_t device = eval(opcode->operands->items[1]->u.expr, symbols);

  if (device > 077) {
    printf("Instruction %s requires a device. Device 0%o is out of bounds.\n", opcode->mnemonic, device);
    exit(1);
  }

  encoding |= device;
  encoding |= accumulator;
  (*buffer)[offset] = encoding;
}

void encode_flow_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;
  uint16_t x = 0;

  if (opcode->operands->count == 1) {
    x = 0x100;
  } else if (opcode->operands->count == 2) {
    x = eval(opcode->operands->items[0]->u.expr, symbols) << 8;

    if (x > 0x300) {
      printf("Invalid mode for %s. Expected 0, 1, 2, or 3, got %d.\n", opcode->mnemonic, x);
      exit(1);
    }
  } else {
    printf("Instruction %s requires 1 or 2 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
  }

  uint16_t displacement = 0;

  if (opcode->operands->count == 1) {
    displacement = eval(opcode->operands->items[0]->u.expr, symbols);
  } else {
    displacement = eval(opcode->operands->items[1]->u.expr, symbols);
  }
  if (x == 0x100) {
    displacement -= offset;      
  }

  if (displacement > 0xFF && displacement < 0xFF00) {
    printf("Instruction %s requires 8 bit displacement. 0%o is out of bounds.\n", opcode->mnemonic, displacement);
  }
  displacement &= 0xFF;

  encoding |= x;
  encoding |= displacement;
  (*buffer)[offset] = encoding;
}

int encode_instruction(uint16_t** buffer, int offset, opcode_t* opcode, symboltbl_t* symbols) {
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

  switch (instruction->encoding_type) {
  case ENCODING_CONSTANT:
    (*buffer)[offset] = instruction->base_encoding;
    break;
  case ENCODING_IONOXFER:
    encode_ionoxfer_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  case ENCODING_FLOW:
    encode_flow_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  case ENCODING_IO:
    encode_io_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  default:
    printf("Attempted to encode an instruction of a type not yet supported: %d.\n", instruction->encoding_type);
    exit(1);
  }

  return instruction->size;
}
