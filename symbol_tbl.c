#include "symbol_tbl.h"
#include "ast.h"
#include "assembler.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

symboltbl_t* resolve_symbols(program_t* prog, offset_t* offsets) {
  symboltbl_t* head = malloc(sizeof(symboltbl_t));
  symboltbl_t* cur = head;

  constant_t* current_const = prog->constanttbl;
  while (current_const != NULL) {
    cur->next = malloc(sizeof(symboltbl_t));
    cur = cur->next;

    cur->name = strdup(current_const->name);
    if (current_const->value->kind != EXPR_INTEGER) {
      printf("%s has not been resolved properly.\n", cur->name);
      exit(1);
    }

    cur->value = current_const->value->u.number & 0xFFFF;
    current_const = current_const->next;
  }

  device_t* current_device = prog->devicetbl;
  while (current_device != NULL) {
    cur->next = malloc(sizeof(symboltbl_t));
    cur = cur->next;

    cur->name = current_device->name;
    cur->value = current_device->value & 0xFFFF;

    current_device = current_device->next;
  }

  offset_t* current_offset = offsets->next;
  while (current_offset != NULL) {
    cur->next = malloc(sizeof(symboltbl_t));
    cur = cur->next;

    cur->name = current_offset->name;
    cur->value = current_offset->address;

    current_offset = current_offset->next;
  }

  return head;
}

uint32_t find_symbol(symboltbl_t* symbols, char* symbol) {
  symboltbl_t* cur = symbols->next;  // Head is always empty due to the way the list is constructed

  while (cur != NULL && strcmp(cur->name, symbol) != 0) {
    cur = cur->next;
  }

  if (cur == NULL) {
    return 0xFFFFFFFF;
  }

  return cur->value;
}
