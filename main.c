#include "ast.h"
#include "parser.h"
#include "assembler.h"
#include "symbol_tbl.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern FILE* yyin;

void usage() {
  printf("Usage:\n");
  printf("dgasm -t <cpu> -o <output> -f <format> input.s\n\n");
  printf("CPU options:\n\tnova1\n\tnova3\n\tnova4\n\teclipse140\n\n");
  printf("Output format options:\n\tbinary\n\toctal\n");
}

int main(int argc, char** argv) {
  char* fn = NULL;
  for(; optind < argc; optind++) {
    fn = argv[optind];
  }

  if (fn == NULL) {
    usage();
    return 1;
  }

  FILE* f = fopen(fn, "r");
  if (!f) {
    perror("Could not open input file");
    return 1;
  }
  
  program_t* prog = malloc(sizeof(program_t));
  prog->constanttbl = NULL;
  prog->devicetbl = NULL;
  prog->head = NULL;
  prog->tail = NULL;

  yyin = f;
  yyparse(prog);

  offset_t* offsets = pass1(prog);
  symboltbl_t* symbols = resolve_symbols(prog, offsets);
  printf("Symbol AP0 = %o\n", find_symbol(symbols, "AP0"));
  printf("Symbol start = %o\n", find_symbol(symbols, "start"));
  printf("Symbol bar = %o\n", find_symbol(symbols, "bar"));
}
