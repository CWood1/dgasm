#include "symbol_tbl.h"
#include "ast.h"
#include "assembler.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int insert_symbol(symboltbl_t** head, const char* name, uint16_t value) {
  if (find_symbol(*head, name) != 0xFFFFFFFF) {
    return -1;
  }

  symboltbl_t* sym = malloc(sizeof(symboltbl_t));
  if (!sym) {
    exit(1);
  }

  sym->name = strdup(name);
  sym->value = value;
  sym->next = *head;
  *head = sym;

  return 0;
}

symboltbl_t* resolve_symbols(program_t* prog, offset_t* offsets) {
  symboltbl_t* head = NULL;

  constant_t* current_const = prog->constanttbl;
  while (current_const != NULL) {
    if (current_const->value->kind != EXPR_INTEGER) {
      printf("%s has not been resolved properly.\n", current_const->name);
      exit(1);
    }

    if (insert_symbol(&head, current_const->name, current_const->value->u.number & 0xFFFF) != 0) {
      printf("Multiple definitions for symbol %s.\n", current_const->name);
      exit(1);
    }

    current_const = current_const->next;
  }

  device_t* current_device = prog->devicetbl;
  while (current_device != NULL) {
    if (insert_symbol(&head, current_device->name, current_device->value & 0xFFFF) != 0) {
      printf("Multiple definitions for symbol %s.\n", current_const->name);
      exit(1);
    }

    current_device = current_device->next;
  }

  offset_t* current_offset = offsets->next;
  while (current_offset != NULL) {
    if (insert_symbol(&head, current_offset->name, current_offset->address) != 0) {
      printf("Multiple definitions for symbol %s.\n", current_offset->name);
      exit(1);
    }

    current_offset = current_offset->next;
  }

  return head;
}

uint32_t find_symbol(symboltbl_t* symbols, const char* symbol) {
  symboltbl_t* cur = symbols;

  while (cur != NULL && strcmp(cur->name, symbol) != 0) {
    cur = cur->next;
  }

  if (cur == NULL) {
    return 0xFFFFFFFF;
  }

  return cur->value;
}
