#include "opcode.h"
#include "eval.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

instruction_t instruction_tbl[] = {
  // Opcode      Size   Base encoding       Encoding type
  { "NIO",       1,     0b0110000000000000, ENCODING_IONOXFER },
  { "NIOS",      1,     0b0110000001000000, ENCODING_IONOXFER },
  { "NIOC",      1,     0b0110000010000000, ENCODING_IONOXFER },
  { "NIOP",      1,     0b0110000011000000, ENCODING_IONOXFER },

  { "SKPBN",     1,     0b0110011100000000, ENCODING_IONOXFER },
  { "SKPDN",     1,     0b0110011110000000, ENCODING_IONOXFER },
  { "SKPBZ",     1,     0b0110011101000000, ENCODING_IONOXFER },
  { "SKPDZ",     1,     0b0110011111000000, ENCODING_IONOXFER },

  { "DIA",       1,     0b0110000100000000, ENCODING_IO },
  { "DIAS",      1,     0b0110000101000000, ENCODING_IO },
  { "DIAC",      1,     0b0110000110000000, ENCODING_IO },
  { "DIAP",      1,     0b0110000111000000, ENCODING_IO },
  { "DOA",       1,     0b0110001000000000, ENCODING_IO },
  { "DOAS",      1,     0b0110001001000000, ENCODING_IO },
  { "DOAC",      1,     0b0110001010000000, ENCODING_IO },
  { "DOAP",      1,     0b0110001011000000, ENCODING_IO },
  
  { "DIB",       1,     0b0110001100000000, ENCODING_IO },
  { "DIBS",      1,     0b0110001101000000, ENCODING_IO },
  { "DIBC",      1,     0b0110001110000000, ENCODING_IO },
  { "DIBP",      1,     0b0110001111000000, ENCODING_IO },
  { "DOB",       1,     0b0110010000000000, ENCODING_IO },
  { "DOBS",      1,     0b0110010001000000, ENCODING_IO },
  { "DOBC",      1,     0b0110010010000000, ENCODING_IO },
  { "DOBP",      1,     0b0110010011000000, ENCODING_IO },
  
  { "DIC",       1,     0b0110010100000000, ENCODING_IO },
  { "DICS",      1,     0b0110010101000000, ENCODING_IO },
  { "DICC",      1,     0b0110010110000000, ENCODING_IO },
  { "DICP",      1,     0b0110010111000000, ENCODING_IO },
  { "DOC",       1,     0b0110011000000000, ENCODING_IO },
  { "DOCS",      1,     0b0110011001000000, ENCODING_IO },
  { "DOCC",      1,     0b0110011010000000, ENCODING_IO },
  { "DOCP",      1,     0b0110011011000000, ENCODING_IO },

  { "JMP",       1,     0b0000000000000000, ENCODING_FLOW },
  { "JSR",       1,     0b0000100000000000, ENCODING_FLOW },
  { "ISZ",       1,     0b0001000000000000, ENCODING_FLOW },
  { "DSZ",       1,     0b0001100000000000, ENCODING_FLOW },

  { "INC",       1,     0b1000001100000000, ENCODING_ALU },
  { "MOV",       1,     0b1000001000000000, ENCODING_ALU },

  { "LDA",       1,     0b0010000000000000, ENCODING_LOAD },

  { "ELEF",      2,     0b1110010000111000, ENCODING_EXTENDEDLOAD },

  { "LMP",       1,     0b1001011100001000, ENCODING_CONSTANT },
  { "HALT",      1,     0b0110011000111111, ENCODING_CONSTANT },
  { "IORST",     1,     0b0110010110111111, ENCODING_CONSTANT },
  { "RTN",       1,     0b1010111111001000, ENCODING_CONSTANT },
  { "PSHR",      1,     0b1000011111001000, ENCODING_CONSTANT },
  { "RSTR",      1,     0b1110111111001000, ENCODING_CONSTANT },
  { "POPJ",      1,     0b1001111111001000, ENCODING_CONSTANT },
  { "POPB",      1,     0b1000111111001000, ENCODING_CONSTANT },
  { "FTD",       1,     0b1100111011101000, ENCODING_CONSTANT },
  { "FTE",       1,     0b1100011011101000, ENCODING_CONSTANT },
  { "CTR",       1,     0b1110011110101000, ENCODING_CONSTANT },
  { "CMV",       1,     0b1101011110101000, ENCODING_CONSTANT },
  { "CMT",       1,     0b1110111110101000, ENCODING_CONSTANT },
  { "CMP",       1,     0b1101111110101000, ENCODING_CONSTANT },
  { "BLM",       1,     0b1011011111001000, ENCODING_CONSTANT },
  { "BAM",       1,     0b1001011111001000, ENCODING_CONSTANT },
  
  { "MULS",      1,     0b1100111111001000, ENCODING_CONSTANT },
  { "MUL",       1,     0b1100011111001000, ENCODING_CONSTANT },
  { "DIV",       1,     0b1101011111001000, ENCODING_CONSTANT },
  { "DIVS",      1,     0b1101111111001000, ENCODING_CONSTANT },
  { "DIVX",      1,     0b1011111111001000, ENCODING_CONSTANT },

  { "FCLE",      1,     0b1101011011101000, ENCODING_CONSTANT },
  { "FNS",       1,     0b1000011010101000, ENCODING_CONSTANT },
  { "FPOP",      1,     0b1110111011101000, ENCODING_CONSTANT },
  { "FPSH",      1,     0b1110011011101000, ENCODING_CONSTANT },
  { "FSA",       1,     0b1000111010101000, ENCODING_CONSTANT },
  { "FSEQ",      1,     0b1001011010101000, ENCODING_CONSTANT },
  { "FSGE",      1,     0b1010111010101000, ENCODING_CONSTANT },
  { "FSGT",      1,     0b1011111010101000, ENCODING_CONSTANT },
  { "FSLE",      1,     0b1011011010101000, ENCODING_CONSTANT },
  { "FSLT",      1,     0b1010011010101000, ENCODING_CONSTANT },
  { "FSND",      1,     0b1100111010101000, ENCODING_CONSTANT },
  { "FSNE",      1,     0b1001111010101000, ENCODING_CONSTANT },
  { "FSNER",     1,     0b1111111010101000, ENCODING_CONSTANT },
  { "FSNM",      1,     0b1100011010101000, ENCODING_CONSTANT },
  { "FSNO",      1,     0b1110011010101000, ENCODING_CONSTANT },
  { "FSNOD",     1,     0b1110111010101000, ENCODING_CONSTANT },
  { "FSNU",      1,     0b1101011010101000, ENCODING_CONSTANT },
  { "FSNUD",     1,     0b1101111010101000, ENCODING_CONSTANT },
  { "FSNUO",     1,     0b1111011010101000, ENCODING_CONSTANT },
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

void encode_load_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;
  uint16_t index = 0;

  if (opcode->operands->count == 2) {
    index = 0;
  } else if (opcode->operands->count == 3) {
    index = eval(opcode->operands->items[2]->u.expr, symbols);

    if (index > 3) {
      printf("Invalid mode for %s. Expected 0, 1, 2, or 3, got %d.\n", opcode->mnemonic, index);
      exit(1);
    }

    index <<= 8;
  } else {
    printf("Instruction %s requires 2 or 3 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
  }

  uint16_t accumulator = eval(opcode->operands->items[0]->u.expr, symbols) << 11;
  if (accumulator > 0x2000) {
    printf("Accumulator out of range. Should be 0, 1, 2, or 3.\n");
    exit(1);
  }

  uint16_t displacement = 0;

  displacement = eval(opcode->operands->items[1]->u.expr, symbols);
  if (index == 0x100) {
    displacement -= offset;      
  }

  if (displacement > 0xFF && displacement < 0xFF00) {
    printf("Instruction %s requires 8 bit displacement. 0%o is out of bounds.\n", opcode->mnemonic, displacement);
  }
  displacement &= 0xFF;

  encoding |= index;
  encoding |= accumulator;
  encoding |= displacement;
  (*buffer)[offset] = encoding;
}

void encode_extendedload_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;
  uint16_t index = 0;

  if (opcode->operands->count == 2) {
    index = 0;
  } else if (opcode->operands->count == 3) {
    index = eval(opcode->operands->items[2]->u.expr, symbols);

    if (index > 3) {
      printf("Invalid mode for %s. Expected 0, 1, 2, or 3, got %d.\n", opcode->mnemonic, index);
      exit(1);
    }

    index <<= 8;
  } else {
    printf("Instruction %s requires 2 or 3 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
  }

  uint16_t accumulator = eval(opcode->operands->items[0]->u.expr, symbols) << 11;
  if (accumulator > 0x2000) {
    printf("Accumulator out of range. Should be 0, 1, 2, or 3.\n");
    exit(1);
  }

  uint16_t displacement = 0;

  displacement = eval(opcode->operands->items[1]->u.expr, symbols);
  if (index == 0x100) {
    displacement -= offset;      
  }

  encoding |= index;
  encoding |= accumulator;
  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = displacement;
}

void encode_alu_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  if (opcode->operands->count < 2) {
    printf("Instruction %s requires at least 2 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
    exit(1);
  } else if (opcode->operands->count > 3) {
    printf("Instruction %s requires at most 3 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
    exit(1);
  }

  uint16_t sourceaccumulator = eval(opcode->operands->items[0]->u.expr, symbols);
  if (sourceaccumulator > 3) {
    printf("Accumulator out of range. Should be 0, 1, 2, or 3.\n");
    exit(1);
  }
  uint16_t destinationaccumulator = eval(opcode->operands->items[1]->u.expr, symbols);  
  if (destinationaccumulator > 3) {
    printf("Accumulator out of range. Should be 0, 1, 2, or 3.\n");
    exit(1);
  }

  uint16_t skip = 0;
  if (opcode->operands->count == 3) {
    if (opcode->operands->items[2]->kind != OPERAND_SKIP) {
      printf("Final parameter for an ALU instruction must be a skip.\n");
      exit(1);
    }

    skip = opcode->operands->items[2]->u.skip;
  }

  encoding |= sourceaccumulator << 13;
  encoding |= destinationaccumulator << 11;
  encoding |= skip;
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
  case ENCODING_LOAD:
    encode_load_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  case ENCODING_EXTENDEDLOAD:
    encode_extendedload_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  case ENCODING_ALU:
    encode_alu_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  default:
    printf("Attempted to encode an instruction of a type not yet supported: %d.\n", instruction->encoding_type);
    exit(1);
  }

  return instruction->size;
}
