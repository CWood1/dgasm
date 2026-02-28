#include "ast.h"
#include "assembler.h"
#include "opcode.h"
#include "eval.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_MEMORY_WORDS 65536

offset_t* pass1(program_t* prog) {
  // Default to starting at 0100 - just after the zero page
  uint16_t current_address = 0100;

  offset_t* head = malloc(sizeof(offset_t));
  offset_t* cur = head;

  statement_t* current_statement = prog->head;
  while (current_statement != NULL) {
    switch (current_statement->type) {
    case STMT_OPCODE:
      // Instructions are easy - simply add the encoding size of the instruction to the current address
      instruction_t inst = find_instruction(current_statement->opcode->mnemonic);
      current_address += inst.size;
      break;

    case STMT_LABEL:
      // Labels need to be treated as offsets. Simply, compute the offset and add it to the table
      cur->next = malloc(sizeof(offset_t));
      cur = cur->next;

      cur->name = strdup(current_statement->label);
      cur->address = current_address;
      break;

    case STMT_VARIABLE:
      // For variables, add them to the offset table, but then we also need to work out the size and
      // progress the current address by that far.
      cur->next = malloc(sizeof(offset_t));
      cur = cur->next;

      cur->name = strdup(current_statement->variable->name);
      cur->address = current_address;

      switch (current_statement->variable->type) {
      case VARIABLE_STRING:
	current_address += strlen(current_statement->variable->value.str) + 1;
	break;
      case VARIABLE_NUMBER:
	current_address += 1;
	break;
      case VARIABLE_RESV:
	current_address += current_statement->variable->value.resv;
	break;
      }
      break;

    case STMT_DIRECTIVE:
      // The only directive we currently support is org, which changes the current address.
      switch (current_statement->directive->type) {
      case DIRECTIVE_ORG:
	current_address = current_statement->directive->org;
	break;
      }
      break;
    }

    current_statement = current_statement->next;
  }

  return head;
}

output_t pass2(program_t* prog, symboltbl_t* symbols) {
  output_t out = {0};
  uint16_t* buffer = calloc(MAX_MEMORY_WORDS, sizeof(uint16_t));
  if (buffer == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }

  uint16_t min_addr = 0xFFFF;
  uint16_t max_addr = 0x0000;

  // Start at 0100, until we're told otherwise
  uint16_t current_addr = 0100;
  for (statement_t* stmt = prog->head; stmt != NULL; stmt = stmt->next) {
    switch (stmt->type) {
    case STMT_DIRECTIVE:
      switch (stmt->directive->type) {
      case DIRECTIVE_ORG:
	current_addr = stmt->directive->org;
	break;
      }
      break;

    case STMT_OPCODE: {
      int size = encode_instruction(&buffer, current_addr, stmt->opcode, symbols);

      if (current_addr < min_addr)
	min_addr = current_addr;

      current_addr += size;
      if (current_addr > max_addr)
	max_addr = current_addr;

      break;
    }

    case STMT_VARIABLE: {
      int size = 0;

      switch (stmt->variable->type) {
      case VARIABLE_STRING:
	for(int c = 0; stmt->variable->value.str[c] += 0; c++) {
	  buffer[current_addr + c] = stmt->variable->value.str[c];
	}
	buffer[current_addr + strlen(stmt->variable->value.str) + 1] = 0;
	size = strlen(stmt->variable->value.str) + 1;
	break;
      case VARIABLE_NUMBER:
	buffer[current_addr] = eval(stmt->variable->value.number, symbols);
	size = 1;
	break;
      case VARIABLE_RESV:
	size = stmt->variable->value.resv;
	break;
      }

      if (current_addr < min_addr)
	min_addr = current_addr;

      current_addr += size;
      if (current_addr > max_addr)
	max_addr = current_addr;

      break;
    }

    default:
      // Don't do anything
    }
  }

  uint16_t used_size = (max_addr - min_addr) + 1;
  uint16_t* trimmed = malloc(used_size * sizeof(uint16_t));
  if (trimmed == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }

  memcpy(trimmed, &buffer[min_addr], used_size * sizeof(uint16_t));

  free(buffer);

  out.data = trimmed;
  out.size = used_size;
  out.start_addr = min_addr;

  return out;
}
