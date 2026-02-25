#include "ast.h"
#include "assembler.h"

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
      // program this
      break;
    case STMT_LABEL:
      cur->next = malloc(sizeof(offset_t));
      cur = cur->next;

      cur->name = strdup(current_statement->label);
      cur->address = current_address;
      break;
    case STMT_VARIABLE:
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
      // program this
      break;
    }

    current_statement = current_statement->next;
  }

  return head;
}
