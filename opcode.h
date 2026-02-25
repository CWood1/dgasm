#ifndef __OPCODE_H__
#define __OPCODE_H__

typedef struct {
  char* opcode;
  int size;
} instruction_t;

instruction_t find_instruction(char* opcode);

#endif
