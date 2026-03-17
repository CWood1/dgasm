 #include "opcode.h"
#include "eval.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>

instruction_t instruction_tbl[] = {
  // Opcode      Size   Base encoding       Encoding type
  { "NIO",       1,     0b0110000000000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NIOS",      1,     0b0110000001000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NIOC",      1,     0b0110000010000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NIOP",      1,     0b0110000011000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "SKPBN",     1,     0b0110011100000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SKPDN",     1,     0b0110011110000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SKPBZ",     1,     0b0110011101000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SKPDZ",     1,     0b0110011111000000, ENCODING_IONOXFER, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "DIA",       1,     0b0110000100000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIAS",      1,     0b0110000101000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIAC",      1,     0b0110000110000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIAP",      1,     0b0110000111000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOA",       1,     0b0110001000000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOAS",      1,     0b0110001001000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOAC",      1,     0b0110001010000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOAP",      1,     0b0110001011000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "DIB",       1,     0b0110001100000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIBS",      1,     0b0110001101000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIBC",      1,     0b0110001110000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIBP",      1,     0b0110001111000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOB",       1,     0b0110010000000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOBS",      1,     0b0110010001000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOBC",      1,     0b0110010010000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOBP",      1,     0b0110010011000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "DIC",       1,     0b0110010100000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DICS",      1,     0b0110010101000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DICC",      1,     0b0110010110000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DICP",      1,     0b0110010111000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOC",       1,     0b0110011000000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOCS",      1,     0b0110011001000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOCC",      1,     0b0110011010000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DOCP",      1,     0b0110011011000000, ENCODING_IO, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "JMP",       1,     0b0000000000000000, ENCODING_FLOW, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "JSR",       1,     0b0000100000000000, ENCODING_FLOW, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ISZ",       1,     0b0001000000000000, ENCODING_FLOW, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DSZ",       1,     0b0001100000000000, ENCODING_FLOW, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "EJMP",      2,     0b1000010000111000, ENCODING_EXTENDEDFLOW, CPU_ECLIPSE_S140 },
  { "EJSR",      2,     0b1000110000111000, ENCODING_EXTENDEDFLOW, CPU_ECLIPSE_S140 },
  { "EISZ",      2,     0b1001010000111000, ENCODING_EXTENDEDFLOW, CPU_ECLIPSE_S140 },
  { "EDSZ",      2,     0b1001110000111000, ENCODING_EXTENDEDFLOW, CPU_ECLIPSE_S140 },

  { "ADC",       1,     0b1000010000000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCZ",      1,     0b1000010000010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCO",      1,     0b1000010000100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCC",      1,     0b1000010000110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCL",      1,     0b1000010001000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCZL",     1,     0b1000010001010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCOL",     1,     0b1000010001100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCCL",     1,     0b1000010001110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCR",      1,     0b1000010010000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCZR",     1,     0b1000010010010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCOR",     1,     0b1000010010100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCCR",     1,     0b1000010010110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCS",      1,     0b1000010011000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCZS",     1,     0b1000010011010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCOS",     1,     0b1000010011100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADCCS",     1,     0b1000010011110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "ADD",       1,     0b1000011000000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDZ",      1,     0b1000011000010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDO",      1,     0b1000011000100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDC",      1,     0b1000011000110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDL",      1,     0b1000011001000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDZL",     1,     0b1000011001010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDOL",     1,     0b1000011001100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDCL",     1,     0b1000011001110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDR",      1,     0b1000011010000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDZR",     1,     0b1000011010010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDOR",     1,     0b1000011010100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDCR",     1,     0b1000011010110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDS",      1,     0b1000011011000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDZS",     1,     0b1000011011010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDOS",     1,     0b1000011011100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ADDCS",     1,     0b1000011011110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "AND",       1,     0b1000011100000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDZ",      1,     0b1000011100010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDO",      1,     0b1000011100100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDC",      1,     0b1000011100110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDL",      1,     0b1000011101000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDZL",     1,     0b1000011101010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDOL",     1,     0b1000011101100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDCL",     1,     0b1000011101110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDR",      1,     0b1000011110000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDZR",     1,     0b1000011110010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDOR",     1,     0b1000011110100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDCR",     1,     0b1000011110110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDS",      1,     0b1000011111000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDZS",     1,     0b1000011111010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDOS",     1,     0b1000011111100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "ANDCS",     1,     0b1000011111110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "COM",       1,     0b1000000000000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMZ",      1,     0b1000000000010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMO",      1,     0b1000000000100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMC",      1,     0b1000000000110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COML",      1,     0b1000000001000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMZL",     1,     0b1000000001010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMOL",     1,     0b1000000001100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMCL",     1,     0b1000000001110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMR",      1,     0b1000000010000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMZR",     1,     0b1000000010010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMOR",     1,     0b1000000010100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMCR",     1,     0b1000000010110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMS",      1,     0b1000000011000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMZS",     1,     0b1000000011010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMOS",     1,     0b1000000011100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "COMCS",     1,     0b1000000011110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "INC",       1,     0b1000001100000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCZ",      1,     0b1000001100010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCO",      1,     0b1000001100100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCC",      1,     0b1000001100110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCL",      1,     0b1000001101000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCZL",     1,     0b1000001101010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCOL",     1,     0b1000001101100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCCL",     1,     0b1000001101110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCR",      1,     0b1000001110000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCZR",     1,     0b1000001110010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCOR",     1,     0b1000001110100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCCR",     1,     0b1000001110110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCS",      1,     0b1000001111000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCZS",     1,     0b1000001111010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCOS",     1,     0b1000001111100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "INCCS",     1,     0b1000001111110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "MOV",       1,     0b1000001000000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVZ",      1,     0b1000001000010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVO",      1,     0b1000001000100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVC",      1,     0b1000001000110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVL",      1,     0b1000001001000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVZL",     1,     0b1000001001010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVOL",     1,     0b1000001001100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVCL",     1,     0b1000001001110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVR",      1,     0b1000001010000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVZR",     1,     0b1000001010010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVOR",     1,     0b1000001010100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVCR",     1,     0b1000001010110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVS",      1,     0b1000001011000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVZS",     1,     0b1000001011010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVOS",     1,     0b1000001011100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MOVCS",     1,     0b1000001011110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "NEG",       1,     0b1000000100000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGZ",      1,     0b1000000100010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGO",      1,     0b1000000100100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGC",      1,     0b1000000100110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGL",      1,     0b1000000101000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGZL",     1,     0b1000000101010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGOL",     1,     0b1000000101100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGCL",     1,     0b1000000101110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGR",      1,     0b1000000110000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGZR",     1,     0b1000000110010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGOR",     1,     0b1000000110100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGCR",     1,     0b1000000110110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGS",      1,     0b1000000111000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGZS",     1,     0b1000000111010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGOS",     1,     0b1000000111100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "NEGCS",     1,     0b1000000111110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  
  { "SUB",       1,     0b1000010100000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBZ",      1,     0b1000010100010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBO",      1,     0b1000010100100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBC",      1,     0b1000010100110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBL",      1,     0b1000010101000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBZL",     1,     0b1000010101010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBOL",     1,     0b1000010101100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBCL",     1,     0b1000010101110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBR",      1,     0b1000010110000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBZR",     1,     0b1000010110010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBOR",     1,     0b1000010110100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBCR",     1,     0b1000010110110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBS",      1,     0b1000010111000000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBZS",     1,     0b1000010111010000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBOS",     1,     0b1000010111100000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "SUBCS",     1,     0b1000010111110000, ENCODING_ALU, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "LDA",       1,     0b0010000000000000, ENCODING_LOAD, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "LEF",       1,     0b0110000000000000, ENCODING_LOAD, CPU_ECLIPSE_S140 },
  { "STA",       1,     0b0100000000000000, ENCODING_LOAD, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },

  { "ELDA",      2,     0b1010010000111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },
  { "ELEF",      2,     0b1110010000111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },
  { "ESTA",      2,     0b1100010000111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },
  { "ESTB",      2,     0b1010010001111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },
  { "DSPA",      2,     0b1100010001111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },
  { "ELDB",      2,     0b1000010001111000, ENCODING_EXTENDEDLOAD, CPU_ECLIPSE_S140 },

  { "LMP",       1,     0b1001011100001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "HALT",      1,     0b0110011000111111, ENCODING_CONSTANT, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "IORST",     1,     0b0110010110111111, ENCODING_CONSTANT, CPU_NOVA1 | CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "RTN",       1,     0b1010111111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "PSHR",      1,     0b1000011111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "RSTR",      1,     0b1110111111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "POPJ",      1,     0b1001111111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "POPB",      1,     0b1000111111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FTD",       1,     0b1100111011101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FTE",       1,     0b1100011011101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "CTR",       1,     0b1110011110101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "CMV",       1,     0b1101011110101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "CMT",       1,     0b1110111110101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "CMP",       1,     0b1101111110101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "BLM",       1,     0b1011011111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "BAM",       1,     0b1001011111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  
  { "MULS",      1,     0b1100111111001000, ENCODING_CONSTANT, CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "MUL",       1,     0b1100011111001000, ENCODING_CONSTANT, CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIV",       1,     0b1101011111001000, ENCODING_CONSTANT, CPU_NOVA3 | CPU_NOVA4 | CPU_ECLIPSE_S140},
  { "DIVS",      1,     0b1101111111001000, ENCODING_CONSTANT, CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "DIVX",      1,     0b1011111111001000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },

  { "FCLE",      1,     0b1101011011101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FNS",       1,     0b1000011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FPOP",      1,     0b1110111011101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FPSH",      1,     0b1110011011101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSA",       1,     0b1000111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSEQ",      1,     0b1001011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSGE",      1,     0b1010111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSGT",      1,     0b1011111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSLE",      1,     0b1011011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSLT",      1,     0b1010011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSND",      1,     0b1100111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNE",      1,     0b1001111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNER",     1,     0b1111111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNM",      1,     0b1100011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNO",      1,     0b1110011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNOD",     1,     0b1110111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNU",      1,     0b1101011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNUD",     1,     0b1101111010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },
  { "FSNUO",     1,     0b1111011010101000, ENCODING_CONSTANT, CPU_ECLIPSE_S140 },

  { "SAVE",      2,     0b1110011111001000, ENCODING_SAVE, CPU_ECLIPSE_S140 },

  { "ANC",       1,     0b1000000110001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "BTO",       1,     0b1000010000001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "BTZ",       1,     0b1000010001001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "CLM",       1,     0b1000010011111000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "COB",       1,     0b1000010110001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "DAD",       1,     0b1000000010001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "DLSH",      1,     0b1000001011001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "DSB",       1,     0b1000000011001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "IOR",       1,     0b1000000100001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "LDB",       1,     0b1000010111001000, ENCODING_TWOACC, CPU_NOVA4 | CPU_ECLIPSE_S140 },
  { "LOB",       1,     0b1000010100001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "LRB",       1,     0b1000010101001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "LSH",       1,     0b1000001010001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "PSH",       1,     0b1000011001001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "POP",       1,     0b1000011010001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "XOR",       1,     0b1000000101001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SGE",       1,     0b1000001001001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SGT",       1,     0b1000001000001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SNB",       1,     0b1000010111111000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "STB",       1,     0b1000011000001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SYC",       1,     0b1000011101001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SZB",       1,     0b1000010010001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "SZBO",      1,     0b1000000110010000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "XCH",       1,     0b1000000111001000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },

  { "FAD",       1,     0b1000000001101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FAS",       1,     0b1000000000101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FCMP",      1,     0b1000011100101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FDD",       1,     0b1000000111101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FDS",       1,     0b1000000110101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FFAS",      1,     0b1000010110101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FLAS",      1,     0b1000010100101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FMD",       1,     0b1000000101101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FMOV",      1,     0b1000011101101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FMS",       1,     0b1000000100101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FSD",       1,     0b1000000011101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },
  { "FSS",       1,     0b1000000010101000, ENCODING_TWOACC, CPU_ECLIPSE_S140 },

  { "MSP",       1,     0b1000011011111000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "HLV",       1,     0b1100011011111000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "XCT",       1,     0b1010011011111000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },

  { "FAB",       1,     0b1100011000101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FEXP",      1,     0b1010011001101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FHLV",      1,     0b1110011001101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FINT",      1,     0b1100011001101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FNEG",      1,     0b1110011000101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FNOM",      1,     0b1000011000101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FRH",       1,     0b1010011000101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },
  { "FSCAL",     1,     0b1000011001101000, ENCODING_ONEACC, CPU_ECLIPSE_S140 },

  // Nova 3 instructions - these are all aliases to I/O instruction special encodings
  { "PSHA",      1,     0b0110001100000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "POPA",      1,     0b0110001110000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "SAV",       1,     0b0110010100000001, ENCODING_CONSTANT, CPU_NOVA3 | CPU_NOVA4 },
  { "MTSP",      1,     0b0110001000000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "MTFP",      1,     0b0110000000000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "MSFP",      1,     0b0110001010000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "MFFP",      1,     0b0110000010000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "RET",       1,     0b0110010110000001, ENCODING_ONEACC, CPU_NOVA3 | CPU_NOVA4 },
  { "TRAP",      1,     0b1000000000001000, ENCODING_TRAP, CPU_NOVA3 | CPU_NOVA4 },

  // Nova 4 instructions
  { "LDB",       1,     0b0110000100000001, ENCODING_NOVA4BYTE, CPU_NOVA4 },
  { "STB",       1,     0b0110010000000001, ENCODING_NOVA4BYTE, CPU_NOVA4 },
  { "MUL",       1,     0b0111011011000001, ENCODING_CONSTANT, CPU_NOVA4 },
  { "DIV",       1,     0b0111011001000001, ENCODING_CONSTANT, CPU_NOVA4 },
  { "MULS",      1,     0b0111111010000001, ENCODING_CONSTANT, CPU_NOVA4 },
  { "DIVS",      1,     0b0111111000000001, ENCODING_CONSTANT, CPU_NOVA4 },

  { "ADDI",      2,     0b1110011111111000, ENCODING_EXTENDEDIMMEDIATE, CPU_ECLIPSE_S140 },
  { "ANDI",      2,     0b1100011111111000, ENCODING_EXTENDEDIMMEDIATE, CPU_ECLIPSE_S140 },
  { "IORI",      2,     0b1000011111111000, ENCODING_EXTENDEDIMMEDIATE, CPU_ECLIPSE_S140 },
  { "XORI",      2,     0b1010011111111000, ENCODING_EXTENDEDIMMEDIATE, CPU_ECLIPSE_S140 },

  { "ADI",       1,     0b1000000000001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },
  { "DHXL",      1,     0b1000001110001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },
  { "DHXR",      1,     0b1000001111001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },
  { "HXL",       1,     0b1000001100001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },
  { "HXR",       1,     0b1000001101001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },
  { "SBI",       1,     0b1000000001001000, ENCODING_IMMEDIATE, CPU_ECLIPSE_S140 },

  { "FAMD",      2,     0b1000001001101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FAMS",      2,     0b1000001000101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FDMD",      2,     0b1000001111101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FDMS",      2,     0b1000001110101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FFMD",      2,     0b1000010111101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FLDD",      2,     0b1000010001101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FLDS",      2,     0b1000010000101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FLMD",      2,     0b1000010101101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FMMD",      2,     0b1000001101101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FMMS",      2,     0b1000001100101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FSMD",      2,     0b1000001011101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FSMS",      2,     0b1000001010101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FSTD",      2,     0b1000010011101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },
  { "FSTS",      2,     0b1000010010101000, ENCODING_FLOATEXLOAD, CPU_ECLIPSE_S140 },

  { "FLST",      2,     0b1010011011101000, ENCODING_FLOATEXLOADNOACC, CPU_ECLIPSE_S140 },
  { "FSST",      2,     0b1000011011101000, ENCODING_FLOATEXLOADNOACC, CPU_ECLIPSE_S140 },

  { "PSHJ",      2,     0b1000010010111000, ENCODING_PSHJ, CPU_ECLIPSE_S140 },
  { "XOP",       1,     0b1000000000011000, ENCODING_XOP, CPU_ECLIPSE_S140 },
  { "XOP1",      1,     0b1000000000111000, ENCODING_XOP1, CPU_ECLIPSE_S140 },
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
  }
  uint16_t device = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (device > 077) {
    report_error(opcode_stmt, "Requires a device. Device 0%o is out of bounds", device);
  }

  return device;
}

uint16_t get_accumulator(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requries an accumulator");
  }
  uint16_t acc = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (acc > 3) {
    report_error(opcode_stmt, "Requires an accumulator. Accumulator 0%o is out of bounds", acc);
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

  // If index is 0 (ie, zero page), the number is unsigned. Elsewise, it's signed
  if (index == 0 && (displacement & 0xFF00) != 0) {
    report_error(opcode_stmt, "Address out of range. Got %d, should be 0 - 255", (int16_t)displacement);
  } else if (index != 0 && (displacement & 0xFF00) != 0 && (displacement & 0xFF80) != 0xFF80) {
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

  if (index == 0 && (displacement & 0x8000) != 0) {
    report_error(opcode_stmt, "Address out of range. Got %d, should be 0 - 077777", (int16_t)displacement);
  } else if (index != 0 && (displacement & 0x8000) != 0 && (displacement & 0xC000) != 0xC000) {
    report_error(opcode_stmt, "Address out of range. Got %d, should be -040000 - 037777", (int16_t)displacement);
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

uint16_t get_short_imm(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requires an immediate");
  }
  uint16_t imm = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (imm > 4 || imm == 0) {
    report_error(opcode_stmt, "Immediate out of range. Must be 1-4, got %d", imm);
  }

  return imm - 1;
}

uint16_t get_ranged_imm(statement_t* opcode_stmt, symboltbl_t* symbols, int operand, int offset, uint16_t low, uint16_t high) {
  if (opcode_stmt->opcode->operands->items[operand]->kind != OPERAND_EXPR) {
    report_error(opcode_stmt, "Syntax error: Requires an immediate");
  }
  uint16_t imm = eval(opcode_stmt->opcode->operands->items[operand]->u.expr, symbols, offset);

  if (imm > high || imm < low) {
    report_error(opcode_stmt, "Immediate out of range. Must be %d - %d, got %d", imm, low, high);
  }

  return imm;
}

instruction_t find_instruction(statement_t* stmt, int cpu) {
  if (stmt->type != STMT_OPCODE) {
    report_error(stmt, "Attempted to decode opcode on statement that isn't an opcode");
  }

  char* opcode = stmt->opcode->mnemonic;
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);

  for (int cur = 0; cur < instruction_count; cur++) {
    if (strcmp(opcode, instruction_tbl[cur].opcode) == 0 && (instruction_tbl[cur].cpu_types & cpu)) {
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
  encoding |= accumulator<<11;
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

void encode_immediate_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  validate_explicit_argument_count(opcode_stmt, 2);
  uint16_t accumulator = get_accumulator(opcode_stmt, symbols, 0, offset) << 11;
  uint16_t immediate = get_short_imm(opcode_stmt, symbols, 1, offset) << 13;

  encoding |= accumulator;
  encoding |= immediate;
  (*buffer)[offset] = encoding;
}

void encode_floatexload_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  int argc = validate_ranged_argument_count(opcode_stmt, 2, 3);
  uint16_t index = (argc == 2) ? 1 : get_addressing_mode(opcode_stmt, symbols, 2, offset);
  uint16_t acc = get_accumulator(opcode_stmt, symbols, 0, offset);
  uint16_t disp = get_long_displacement(opcode_stmt, symbols, 1, offset, index);

  encoding |= acc << 11;
  encoding |= index << 13;

  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = disp;
}

void encode_floatexloadnoacc_instruction(uint16_t** buffer, int offset, instruction_t* instruction, statement_t* opcode_stmt, symboltbl_t* symbols) {
  uint16_t encoding = instruction->base_encoding;

  int argc = validate_ranged_argument_count(opcode_stmt, 1, 2);
  uint16_t index = (argc == 2) ? 1 : get_addressing_mode(opcode_stmt, symbols, 2, offset);
  uint16_t disp = get_long_displacement(opcode_stmt, symbols, 1, offset, index);

  encoding |= index << 11;

  (*buffer)[offset] = encoding;
  (*buffer)[offset + 1] = disp;
}

int encode_instruction(uint16_t** buffer, int offset, statement_t* opcode_stmt, symboltbl_t* symbols, int cpu) {
  int instruction_count = sizeof(instruction_tbl) / sizeof(instruction_t);
  instruction_t instruction = find_instruction(opcode_stmt, cpu);
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
  case ENCODING_IMMEDIATE:
    encode_immediate_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_FLOATEXLOAD:
    encode_floatexload_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_FLOATEXLOADNOACC:
    encode_floatexloadnoacc_instruction(buffer, offset, &instruction, opcode_stmt, symbols);
    break;
  case ENCODING_PSHJ: {
    int argc = validate_ranged_argument_count(opcode_stmt, 1, 2);
    uint16_t index = (argc == 1) ? 1 : get_addressing_mode(opcode_stmt, symbols, 1, offset);
    uint16_t displacement = get_long_displacement(opcode_stmt, symbols, 0, offset, index);

    (*buffer)[offset] = instruction.base_encoding | (index << 8);
    (*buffer)[offset + 1] = displacement;
    break;
  }

  case ENCODING_XOP: {
    validate_explicit_argument_count(opcode_stmt, 3);
    uint16_t acs = get_accumulator(opcode_stmt, symbols, 0, offset) << 13;
    uint16_t acd = get_accumulator(opcode_stmt, symbols, 1, offset) << 11;
    uint16_t op = get_ranged_imm(opcode_stmt, symbols, 2, offset, 0, 0x1F) << 6;

    (*buffer)[offset] = instruction.base_encoding | acs | acd | op;
    break;
  }

  case ENCODING_XOP1: {
    validate_explicit_argument_count(opcode_stmt, 3);
    uint16_t acs = get_accumulator(opcode_stmt, symbols, 0, offset) << 13;
    uint16_t acd = get_accumulator(opcode_stmt, symbols, 1, offset) << 11;
    uint16_t op = get_ranged_imm(opcode_stmt, symbols, 2, offset, 0, 0x0F) << 6;

    (*buffer)[offset] = instruction.base_encoding | acs | acd | op;
    break;
  }

  case ENCODING_TRAP: {
    validate_explicit_argument_count(opcode_stmt, 3);
    uint16_t acs = get_accumulator(opcode_stmt, symbols, 0, offset) << 13;
    uint16_t acd = get_accumulator(opcode_stmt, symbols, 1, offset) << 11;
    uint16_t op = get_ranged_imm(opcode_stmt, symbols, 2, offset, 0, 0x7F) << 4;

    (*buffer)[offset] = instruction.base_encoding | acs | acd | op;
    break;
  }

  case ENCODING_NOVA4BYTE: {
    validate_explicit_argument_count(opcode_stmt, 2);
    uint16_t acs = get_accumulator(opcode_stmt, symbols, 0, offset) << 6;
    uint16_t acd = get_accumulator(opcode_stmt, symbols, 1, offset) << 11;

    (*buffer)[offset] = instruction.base_encoding | acs | acd;
    break;
  }
    
  default:
    report_error(opcode_stmt, "Attempted to encode an instruction of a type not yet supported: %d.\n", instruction.encoding_type);
    exit(1);
  }

  return instruction.size;
}
