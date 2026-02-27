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

  { "ADC",       1,     0b1000010000000000, ENCODING_ALU },
  { "ADCZ",      1,     0b1000010000010000, ENCODING_ALU },
  { "ADCO",      1,     0b1000010000100000, ENCODING_ALU },
  { "ADCC",      1,     0b1000010000110000, ENCODING_ALU },
  { "ADCL",      1,     0b1000010001000000, ENCODING_ALU },
  { "ADCZL",     1,     0b1000010001010000, ENCODING_ALU },
  { "ADCOL",     1,     0b1000010001100000, ENCODING_ALU },
  { "ADCCL",     1,     0b1000010001110000, ENCODING_ALU },
  { "ADCR",      1,     0b1000010010000000, ENCODING_ALU },
  { "ADCZR",     1,     0b1000010010010000, ENCODING_ALU },
  { "ADCOR",     1,     0b1000010010100000, ENCODING_ALU },
  { "ADCCR",     1,     0b1000010010110000, ENCODING_ALU },
  { "ADCS",      1,     0b1000010011000000, ENCODING_ALU },
  { "ADCZS",     1,     0b1000010011010000, ENCODING_ALU },
  { "ADCOS",     1,     0b1000010011100000, ENCODING_ALU },
  { "ADCCS",     1,     0b1000010011110000, ENCODING_ALU },

  { "ADD",       1,     0b1000011000000000, ENCODING_ALU },
  { "ADDZ",      1,     0b1000011000010000, ENCODING_ALU },
  { "ADDO",      1,     0b1000011000100000, ENCODING_ALU },
  { "ADDC",      1,     0b1000011000110000, ENCODING_ALU },
  { "ADDL",      1,     0b1000011001000000, ENCODING_ALU },
  { "ADDZL",     1,     0b1000011001010000, ENCODING_ALU },
  { "ADDOL",     1,     0b1000011001100000, ENCODING_ALU },
  { "ADDCL",     1,     0b1000011001110000, ENCODING_ALU },
  { "ADDR",      1,     0b1000011010000000, ENCODING_ALU },
  { "ADDZR",     1,     0b1000011010010000, ENCODING_ALU },
  { "ADDOR",     1,     0b1000011010100000, ENCODING_ALU },
  { "ADDCR",     1,     0b1000011010110000, ENCODING_ALU },
  { "ADDS",      1,     0b1000011011000000, ENCODING_ALU },
  { "ADDZS",     1,     0b1000011011010000, ENCODING_ALU },
  { "ADDOS",     1,     0b1000011011100000, ENCODING_ALU },
  { "ADDCS",     1,     0b1000011011110000, ENCODING_ALU },

  { "AND",       1,     0b1000011100000000, ENCODING_ALU },
  { "ANDZ",      1,     0b1000011100010000, ENCODING_ALU },
  { "ANDO",      1,     0b1000011100100000, ENCODING_ALU },
  { "ANDC",      1,     0b1000011100110000, ENCODING_ALU },
  { "ANDL",      1,     0b1000011101000000, ENCODING_ALU },
  { "ANDZL",     1,     0b1000011101010000, ENCODING_ALU },
  { "ANDOL",     1,     0b1000011101100000, ENCODING_ALU },
  { "ANDCL",     1,     0b1000011101110000, ENCODING_ALU },
  { "ANDR",      1,     0b1000011110000000, ENCODING_ALU },
  { "ANDZR",     1,     0b1000011110010000, ENCODING_ALU },
  { "ANDOR",     1,     0b1000011110100000, ENCODING_ALU },
  { "ANDCR",     1,     0b1000011110110000, ENCODING_ALU },
  { "ANDS",      1,     0b1000011111000000, ENCODING_ALU },
  { "ANDZS",     1,     0b1000011111010000, ENCODING_ALU },
  { "ANDOS",     1,     0b1000011111100000, ENCODING_ALU },
  { "ANDCS",     1,     0b1000011111110000, ENCODING_ALU },
  
  { "COM",       1,     0b1000000000000000, ENCODING_ALU },
  { "COMZ",      1,     0b1000000000010000, ENCODING_ALU },
  { "COMO",      1,     0b1000000000100000, ENCODING_ALU },
  { "COMC",      1,     0b1000000000110000, ENCODING_ALU },
  { "COML",      1,     0b1000000001000000, ENCODING_ALU },
  { "COMZL",     1,     0b1000000001010000, ENCODING_ALU },
  { "COMOL",     1,     0b1000000001100000, ENCODING_ALU },
  { "COMCL",     1,     0b1000000001110000, ENCODING_ALU },
  { "COMR",      1,     0b1000000010000000, ENCODING_ALU },
  { "COMZR",     1,     0b1000000010010000, ENCODING_ALU },
  { "COMOR",     1,     0b1000000010100000, ENCODING_ALU },
  { "COMCR",     1,     0b1000000010110000, ENCODING_ALU },
  { "COMS",      1,     0b1000000011000000, ENCODING_ALU },
  { "COMZS",     1,     0b1000000011010000, ENCODING_ALU },
  { "COMOS",     1,     0b1000000011100000, ENCODING_ALU },
  { "COMCS",     1,     0b1000000011110000, ENCODING_ALU },
  
  { "INC",       1,     0b1000001100000000, ENCODING_ALU },
  { "INCZ",      1,     0b1000001100010000, ENCODING_ALU },
  { "INCO",      1,     0b1000001100100000, ENCODING_ALU },
  { "INCC",      1,     0b1000001100110000, ENCODING_ALU },
  { "INCL",      1,     0b1000001101000000, ENCODING_ALU },
  { "INCZL",     1,     0b1000001101010000, ENCODING_ALU },
  { "INCOL",     1,     0b1000001101100000, ENCODING_ALU },
  { "INCCL",     1,     0b1000001101110000, ENCODING_ALU },
  { "INCR",      1,     0b1000001110000000, ENCODING_ALU },
  { "INCZR",     1,     0b1000001110010000, ENCODING_ALU },
  { "INCOR",     1,     0b1000001110100000, ENCODING_ALU },
  { "INCCR",     1,     0b1000001110110000, ENCODING_ALU },
  { "INCS",      1,     0b1000001111000000, ENCODING_ALU },
  { "INCZS",     1,     0b1000001111010000, ENCODING_ALU },
  { "INCOS",     1,     0b1000001111100000, ENCODING_ALU },
  { "INCCS",     1,     0b1000001111110000, ENCODING_ALU },
  
  { "MOV",       1,     0b1000001000000000, ENCODING_ALU },
  { "MOVZ",      1,     0b1000001000010000, ENCODING_ALU },
  { "MOVO",      1,     0b1000001000100000, ENCODING_ALU },
  { "MOVC",      1,     0b1000001000110000, ENCODING_ALU },
  { "MOVL",      1,     0b1000001001000000, ENCODING_ALU },
  { "MOVZL",     1,     0b1000001001010000, ENCODING_ALU },
  { "MOVOL",     1,     0b1000001001100000, ENCODING_ALU },
  { "MOVCL",     1,     0b1000001001110000, ENCODING_ALU },
  { "MOVR",      1,     0b1000001010000000, ENCODING_ALU },
  { "MOVZR",     1,     0b1000001010010000, ENCODING_ALU },
  { "MOVOR",     1,     0b1000001010100000, ENCODING_ALU },
  { "MOVCR",     1,     0b1000001010110000, ENCODING_ALU },
  { "MOVS",      1,     0b1000001011000000, ENCODING_ALU },
  { "MOVZS",     1,     0b1000001011010000, ENCODING_ALU },
  { "MOVOS",     1,     0b1000001011100000, ENCODING_ALU },
  { "MOVCS",     1,     0b1000001011110000, ENCODING_ALU },
  
  { "NEG",       1,     0b1000000100000000, ENCODING_ALU },
  { "NEGZ",      1,     0b1000000100010000, ENCODING_ALU },
  { "NEGO",      1,     0b1000000100100000, ENCODING_ALU },
  { "NEGC",      1,     0b1000000100110000, ENCODING_ALU },
  { "NEGL",      1,     0b1000000101000000, ENCODING_ALU },
  { "NEGZL",     1,     0b1000000101010000, ENCODING_ALU },
  { "NEGOL",     1,     0b1000000101100000, ENCODING_ALU },
  { "NEGCL",     1,     0b1000000101110000, ENCODING_ALU },
  { "NEGR",      1,     0b1000000110000000, ENCODING_ALU },
  { "NEGZR",     1,     0b1000000110010000, ENCODING_ALU },
  { "NEGOR",     1,     0b1000000110100000, ENCODING_ALU },
  { "NEGCR",     1,     0b1000000110110000, ENCODING_ALU },
  { "NEGS",      1,     0b1000000111000000, ENCODING_ALU },
  { "NEGZS",     1,     0b1000000111010000, ENCODING_ALU },
  { "NEGOS",     1,     0b1000000111100000, ENCODING_ALU },
  { "NEGCS",     1,     0b1000000111110000, ENCODING_ALU },
  
  { "SUB",       1,     0b1000010100000000, ENCODING_ALU },
  { "SUBZ",      1,     0b1000010100010000, ENCODING_ALU },
  { "SUBO",      1,     0b1000010100100000, ENCODING_ALU },
  { "SUBC",      1,     0b1000010100110000, ENCODING_ALU },
  { "SUBL",      1,     0b1000010101000000, ENCODING_ALU },
  { "SUBZL",     1,     0b1000010101010000, ENCODING_ALU },
  { "SUBOL",     1,     0b1000010101100000, ENCODING_ALU },
  { "SUBCL",     1,     0b1000010101110000, ENCODING_ALU },
  { "SUBR",      1,     0b1000010110000000, ENCODING_ALU },
  { "SUBZR",     1,     0b1000010110010000, ENCODING_ALU },
  { "SUBOR",     1,     0b1000010110100000, ENCODING_ALU },
  { "SUBCR",     1,     0b1000010110110000, ENCODING_ALU },
  { "SUBS",      1,     0b1000010111000000, ENCODING_ALU },
  { "SUBZS",     1,     0b1000010111010000, ENCODING_ALU },
  { "SUBOS",     1,     0b1000010111100000, ENCODING_ALU },
  { "SUBCS",     1,     0b1000010111110000, ENCODING_ALU },

  { "LDA",       1,     0b0010000000000000, ENCODING_LOAD },
  { "LEF",       1,     0b0110000000000000, ENCODING_LOAD },
  { "STA",       1,     0b0100000000000000, ENCODING_LOAD },

  { "ELDA",      2,     0b1010010000111000, ENCODING_EXTENDEDLOAD },
  { "ELEF",      2,     0b1110010000111000, ENCODING_EXTENDEDLOAD },
  { "ESTA",      2,     0b1100010000111000, ENCODING_EXTENDEDLOAD },

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

  { "SAVE",      2,     0b1110011111001000, ENCODING_SAVE },

  { "PSH",       1,     0b1000011001001000, ENCODING_TWOACC },
  { "POP",       1,     0b1000011010001000, ENCODING_TWOACC },
  { "XOR",       1,     0b1000000101001000, ENCODING_TWOACC },
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

void encode_save_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  if (opcode->operands == NULL) {
    printf("Instruction %s requires 1 operand, found 0\n", opcode->mnemonic);
    exit(1);
  }
  if (opcode->operands->count != 1) {
    printf("Instruction %s requires 1 operand, found %d\n", opcode->mnemonic, opcode->operands->count);
    exit(1);
  }
  if (opcode->operands->items[0]->kind != OPERAND_EXPR) {
    printf("Instruction %s requries a number.\n", opcode->mnemonic);
    exit(1);
  }

  uint16_t immediate = eval(opcode->operands->items[0]->u.expr, symbols);

  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = immediate;
}

void encode_twoacc_instruction(uint16_t** buffer, int offset, instruction_t* instruction, opcode_t* opcode, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  if (opcode->operands->count != 2) {
    printf("Instruction %s requires 2 operands, found %d\n", opcode->mnemonic, opcode->operands->count);
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

  encoding |= sourceaccumulator << 13;
  encoding |= destinationaccumulator << 11;
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
  case ENCODING_SAVE:
    encode_save_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  case ENCODING_TWOACC:
    encode_twoacc_instruction(buffer, offset, instruction, opcode, symbols);
    break;
  default:
    printf("Attempted to encode an instruction of a type not yet supported: %d.\n", instruction->encoding_type);
    exit(1);
  }

  return instruction->size;
}
