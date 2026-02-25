#include "ast.h"
#include "assembler.h"
#include "opcode.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
