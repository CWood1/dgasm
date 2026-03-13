#include "opcode.h"
#include "eval.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>

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

  { "EJMP",      2,     0b1000010000111000, ENCODING_EXTENDEDFLOW },
  { "EJSR",      2,     0b1000110000111000, ENCODING_EXTENDEDFLOW },
  { "EISZ",      2,     0b1001010000111000, ENCODING_EXTENDEDFLOW },
  { "EDSZ",      2,     0b1001110000111000, ENCODING_EXTENDEDFLOW },

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
  { "ESTB",      2,     0b1010010001111000, ENCODING_EXTENDEDLOAD },
  { "DSPA",      2,     0b1100010001111000, ENCODING_EXTENDEDLOAD },
  { "ELDB",      2,     0b1000010001111000, ENCODING_EXTENDEDLOAD },

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

  { "ANC",       1,     0b1000000110001000, ENCODING_TWOACC },
  { "BTO",       1,     0b1000010000001000, ENCODING_TWOACC },
  { "BTZ",       1,     0b1000010001001000, ENCODING_TWOACC },
  { "CLM",       1,     0b1000010011111000, ENCODING_TWOACC },
  { "COB",       1,     0b1000010110001000, ENCODING_TWOACC },
  { "DAD",       1,     0b1000000010001000, ENCODING_TWOACC },
  { "DLSH",      1,     0b1000001011001000, ENCODING_TWOACC },
  { "DSB",       1,     0b1000000011001000, ENCODING_TWOACC },
  { "IOR",       1,     0b1000000100001000, ENCODING_TWOACC },
  { "LDB",       1,     0b1000010111001000, ENCODING_TWOACC },
  { "LOB",       1,     0b1000010100001000, ENCODING_TWOACC },
  { "LRB",       1,     0b1000010101001000, ENCODING_TWOACC },
  { "LSH",       1,     0b1000001010001000, ENCODING_TWOACC },
  { "PSH",       1,     0b1000011001001000, ENCODING_TWOACC },
  { "POP",       1,     0b1000011010001000, ENCODING_TWOACC },
  { "XOR",       1,     0b1000000101001000, ENCODING_TWOACC },
  { "SGE",       1,     0b1000001001001000, ENCODING_TWOACC },
  { "SGT",       1,     0b1000001000001000, ENCODING_TWOACC },
  { "SNB",       1,     0b1000010111111000, ENCODING_TWOACC },
  { "STB",       1,     0b1000011000001000, ENCODING_TWOACC },
  { "SYC",       1,     0b1000011101001000, ENCODING_TWOACC },
  { "SZB",       1,     0b1000010010001000, ENCODING_TWOACC },
  { "SZBO",      1,     0b1000000110010000, ENCODING_TWOACC },
  { "XCH",       1,     0b1000000111001000, ENCODING_TWOACC },

  { "FAD",       1,     0b1000000001101000, ENCODING_TWOACC },
  { "FAS",       1,     0b1000000000101000, ENCODING_TWOACC },
  { "FCMP",      1,     0b1000011100101000, ENCODING_TWOACC },
  { "FDD",       1,     0b1000000111101000, ENCODING_TWOACC },
  { "FDS",       1,     0b1000000110101000, ENCODING_TWOACC },
  { "FFAS",      1,     0b1000010110101000, ENCODING_TWOACC },
  { "FLAS",      1,     0b1000010100101000, ENCODING_TWOACC },
  { "FMD",       1,     0b1000000101101000, ENCODING_TWOACC },
  { "FMOV",      1,     0b1000011101101000, ENCODING_TWOACC },
  { "FMS",       1,     0b1000000100101000, ENCODING_TWOACC },
  { "FSD",       1,     0b1000000011101000, ENCODING_TWOACC },
  { "FSS",       1,     0b1000000010101000, ENCODING_TWOACC },

  { "MSP",       1,     0b1000011011111000, ENCODING_ONEACC },
  { "HLV",       1,     0b1100011011111000, ENCODING_ONEACC },
  { "XCT",       1,     0b1010011011111000, ENCODING_ONEACC },

  { "FAB",       1,     0b1100011000101000, ENCODING_ONEACC },
  { "FEXP",      1,     0b1010011001101000, ENCODING_ONEACC },
  { "FHLV",      1,     0b1110011001101000, ENCODING_ONEACC },
  { "FINT",      1,     0b1100011001101000, ENCODING_ONEACC },
  { "FNEG",      1,     0b1110011000101000, ENCODING_ONEACC },
  { "FNOM",      1,     0b1000011000101000, ENCODING_ONEACC },
  { "FRH",       1,     0b1010011000101000, ENCODING_ONEACC },
  { "FSCAL",     1,     0b1000011001101000, ENCODING_ONEACC },

  { "ADDI",      2,     0b1110011111111000, ENCODING_EXTENDEDIMMEDIATE },
  { "ANDI",      2,     0b1100011111111000, ENCODING_EXTENDEDIMMEDIATE },
  { "IORI",      2,     0b1000011111111000, ENCODING_EXTENDEDIMMEDIATE },
  { "XORI",      2,     0b1010011111111000, ENCODING_EXTENDEDIMMEDIATE },
};

void validate_explicit_argument_count(statement_t* opcode_stmt, int expected) {
  if (opcode_stmt->opcode->operands == NULL && expected == 0) {
    return;
  }

  if (opcode_stmt->opcode->operands == NULL) {
    report_error(opcode_stmt, "Syntax error: Requires %d arguments, got none", expected);
    exit(1);
  }

  if (opcode_stmt->opcode->operands->count != expected) {
    report_error(opcode_stmt, "Syntax error: Requires %d arguments, got %d", expected, opcode_stmt->opcode->operands->count);
    exit(1);
  }
}

int validate_ranged_argument_count(statement_t* opcode_stmt, int lower, int upper) {
  if (opcode_stmt->opcode->operands == NULL && lower == 0) {
    return 0;
  }

  if (opcode_stmt->opcode->operands == NULL) {
    report_error(opcode_stmt, "Syntax error: Requires between %d and %d arguments, got none", lower, upper);
    exit(1);
  }

  if (opcode_stmt->opcode->operands->count < lower) {
    report_error(opcode_stmt, "Syntax error: Requires between %d and %d arguments, got %d", lower, upper, opcode_stmt->opcode->operands->count);
    exit(1);
  }

  if (opcode_stmt->opcode->operands->count > upper) {
    report_error(opcode_stmt, "Syntax error: Requires between %d and %d arguments, got %d", lower, upper, opcode_stmt->opcode->operands->count);
    exit(1);
  }

  return opcode_stmt->opcode->operands->count;
}

uint16_t get_device_number(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requries a device number");
    exit(1);
  }
  uint16_t device = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (device > 077) {
    report_error(opcode_stmt, "Requires a device. Device 0%o is out of bounds", device);
    exit(1);
  }

  return device;
}

uint16_t get_accumulator(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requries an accumulator");
    exit(1);
  }
  uint16_t acc = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (acc > 3) {
    report_error(opcode_stmt, "Requires an accumulator. Accumulator 0%o is out of bounds", acc);
    exit(1);
  }

  return acc;
}

uint16_t get_addressing_mode(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requires an index");
  }
  uint16_t x = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (x > 3) {
    report_error(opcode_stmt, "Invalid addressing mode. Expected 0, 1, 2, or 3, got %d", x);
    exit(1);
  }
}

uint16_t get_short_displacement(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset, int index) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR && opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_INDIRECT) {
    report_error(opcode_stmt, "Syntax error: Requires a displacement");
  }
  uint16_t displacement = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (index == 1) {
    displacement -= offset;
  }

  if (displacement & 0xFF00 != 0 && displacement & 0xFF80 != 0xFF80) {
    report_error(opcode_stmt, "Address out of range. Got %d, should be -128 - 127", (int16_t)displacement);
  }

  displacement &= 0xFF;

  if (opcode_stmt->opcode->operands->items[operand]->kind == OPERAND_INDIRECT) {
    displacement |= 0x400;
  }

  return displacement;
}

uint16_t get_long_displacement(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset, int index) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR && opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_INDIRECT) {
    report_error(opcode_stmt, "Syntax error: Requires a displacement");
  }
  uint16_t displacement = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (index == 1) {
    displacement -= (offset + 1);
  }

  if (displacement & 0x8000 != 0 && displacement & 0xC000 != 0xC000) {
    report_error(opcode_stmt, "Address out of range. Got %d, should be -0100000 - 077777", (int16_t)displacement);
  }

  displacement &= 0x7FFF;

  if (opcode_stmt->opcode->operands->items[operand]->kind == OPERAND_INDIRECT) {
    displacement |= 0x8000;
  }

  return displacement;
}

uint16_t get_long_imm(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requires an immediate");
  }
  return eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);
}

instruction_t find_instruction(statement_t* stmt) {
  if (stmt->type != STMT_OPCODE) {
    report_error(stmt, "Attempted to decode opcode on statement that isn't an opcode");
  }

  char* opcode = stmt->opcode->mnemonic;
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);

  for (int cur = 0; cur < instruction_count; cur++) {
    if (strcmp(opcode, instruction_tbl[cur].opcode) == 0) {
      return instruction_tbl[cur];
    }
  }

  report_error(stmt, "Syntax error: unrecognised instruction");
  exit(1);
}

void encode_ionoxfer_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  opcode_t* opcode = opcode_stmt->opcode;
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 1);
  uint16_t device = get_device_number(opcode_stmt, symbols, 0, offset);

  encoding |= device;
  (*buffer)[offset] = encoding;
}

void encode_io_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  opcode_t* opcode = opcode_stmt->opcode;
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 2);

  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset);
  uint16_t device = get_device_number(opcode_stmt, symbols, 1, offset);

  encoding |= device;
  encoding |= accumulator;
  (*buffer)[offset] = encoding;
}

void encode_flow_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;
  int argc = validate_ranged_argument_count(opcode_stmt, 1, 2);

  uint16_t index = (argc == 1) ? 1 : get_addressing_mode(opcode_stmt, symbols, 1, offset);
  uint16_t displacement = get_short_displacement(opcode_stmt, symbols, 0, offset, index);

  encoding |= index << 8;
  encoding |= displacement;
  (*buffer)[offset] = encoding;
}

void encode_extendedflow_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  opcode_t* opcode = opcode_stmt->opcode;
  uint16_t encoding = instruction->base_encoding;

  int argc = validate_ranged_argument_count(opcode_stmt, 1, 2);
  uint16_t index = (argc == 1) ? 1 : get_addressing_mode(opcode_stmt, symbols, 1, offset);
  uint16_t displacement = get_long_displacement(opcode_stmt, symbols, 0, offset, index);

  encoding |= index << 8;
  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = displacement;
}

void encode_load_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  opcode_t* opcode = opcode_stmt->opcode;
  uint16_t encoding = instruction->base_encoding;
  
  int argc = validate_ranged_argument_count(opcode_stmt, 2, 3);
  uint16_t index = (argc == 2) ? 0 : get_addressing_mode(opcode_stmt, symbols, 2, offset);
  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset) << 11;
  uint16_t displacement = get_short_displacement(opcode_stmt, symbols, 1, offset, index);

  encoding |= index << 8;
  encoding |= accumulator;
  encoding |= displacement;
  (*buffer)[offset] = encoding;
}

void encode_extendedload_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  opcode_t* opcode = opcode_stmt->opcode;
  uint16_t encoding = instruction->base_encoding;

  int argc = validate_ranged_argument_count(opcode_stmt, 2, 3);
  uint16_t index = (argc == 2) ? 0 : get_addressing_mode(opcode_stmt, symbols, 2, offset);
  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset) << 11;
  uint16_t displacement = get_long_displacement(opcode_stmt, symbols, 1, offset, index);

  encoding |= index << 8;
  encoding |= accumulator;
  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = displacement;
}

void encode_alu_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  int argc = validate_ranged_argument_count(opcode_stmt, 2, 3);

  uint16_t sourceaccumulator = get_accumulator(opcode_stmt, symbols, 0, offset);
  uint16_t destinationaccumulator = get_accumulator(opcode_stmt, symbols, 1, offset);
  uint16_t skip = 0;
  if (argc == 3) {
    if (opcode_stmt->opcode->operands->items[2]->kind != OPERAND_SKIP) {
      report_error(opcode_stmt, "Syntax error: Final parameter must be a skip");
      exit(1);
    }

    skip = opcode_stmt->opcode->operands->items[2]->u.skip;
  }

  if (opcode_stmt->opcode->ignoreresult == 1) {
    encoding |= 0x8;
  }

  encoding |= sourceaccumulator << 13;
  encoding |= destinationaccumulator << 11;
  encoding |= skip;
  (*buffer)[offset] = encoding;
}

void encode_save_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 1);
  uint16_t immediate = get_long_imm(opcode_stmt, symbols, 0, offset);

  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = immediate;
}

void encode_twoacc_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 2);
  uint16_t sourceaccumulator = get_accumulator(opcode_stmt, symbols, 0, offset);
  uint16_t destinationaccumulator = get_accumulator(opcode_stmt, symbols, 1, offset);

  encoding |= sourceaccumulator << 13;
  encoding |= destinationaccumulator << 11;
  (*buffer)[offset] = encoding;
}

void encode_oneacc_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 1);
  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset);

  encoding |= accumulator << 11;
  (*buffer)[offset] = encoding;
}

void encode_extended_immediate_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 2);
  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset) << 11;
  uint16_t immediate = get_long_imm(opcode_stmt, symbols, 1, offset);

  encoding |= accumulator;
  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = immediate;
}

int encode_instruction(uint16_t** buffer, int offset, statement_t* opcode_stmt, symboltbl_t* symbols) {
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);
  instruction_t instruction = find_instruction(opcode_stmt);
  opcode_t* opcode = opcode_stmt->opcode;

  switch (instruction.encoding_type) {
  case ENCODING_CONSTANT:
    validate_explicit_argument_count(opcode_stmt, 0);
    (*buffer)[offset] = instruction.base_encoding;
    break;
  case ENCODING_IONOXFER:
    encode_ionoxfer_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_FLOW:
    encode_flow_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_EXTENDEDFLOW:
    encode_extendedflow_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_IO:
    encode_io_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_LOAD:
    encode_load_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_EXTENDEDLOAD:
    encode_extendedload_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_ALU:
    encode_alu_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_SAVE:
    encode_save_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_TWOACC:
    encode_twoacc_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_ONEACC:
    encode_oneacc_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_EXTENDEDIMMEDIATE:
    encode_extended_immediate_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  default:
    report_error(opcode_stmt, "Attempted to encode an instruction of a type not yet supported: %d.\n", instruction.encoding_type);
    exit(1);
  }

  return instruction.size;
}
