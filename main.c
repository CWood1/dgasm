#include "ast.h"
#include "parser.h"
#include "assembler.h"
#include "symbol_tbl.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern FILE* yyin;

int write_raw_binary(const char *filename, const output_t *out) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("fopen");
        return -1;
    }

    fwrite(out->data, sizeof(uint16_t), out->size, f);

    fclose(f);
    return 0;
}

int write_octal_listing(FILE *stream, const output_t *out) {
    if (!stream || !out)
        return -1;

    uint16_t addr = out->start_addr;

    for (uint16_t i = 0; i < out->size; i++, addr++) {
        fprintf(stream, "%06o: %06o\n",
                addr,
                out->data[i]);
    }

    return 0;
}

void usage() {
  printf("Usage:\n");
  printf("dgasm -t <cpu> -o <output> -f <format> input.s\n\n");
  printf("CPU options:\n\tnova1\n\tnova3\n\tnova4\n\teclipse140\n\n");
  printf("Output format options:\n\tbinary\n\toctal\n");
}

int main(int argc, char** argv) {
  char* fn = NULL;
  char* outputfn = NULL;
  char* outputformat = "bin";

  int opt;

  while((opt = getopt(argc, argv, "o:f:")) != -1) {
    switch(opt) {
    case 'o':
      outputfn = optarg;
      break;

    case 'f':      
      if (strcmp(optarg, "bin") == 0 ||
	  strcmp(optarg, "octal") == 0) {
	outputformat = optarg;
      } else {
	fprintf(stderr,
		"Invalid format '%s'. Use 'bin' or 'octal'.\n",
		optarg);
	return 1;
      }
      break;

    default:
      usage();
      return 1;
    }
  }

  if (optind >= argc) {
    usage();
    return 1;
  }

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
  output_t output = pass2(prog);

  if (strcmp(outputformat, "bin") == 0) {
    if (outputfn == NULL) {
      usage();
      return 1;
    }

    if (write_raw_binary(outputfn, &output) != 0) {
      return 1;
    }
  } else {
    if (outputfn) {      
      FILE *out = fopen(outputfn, "w");
      if (!f) {
        perror("fopen");
        return -1;
      }

      write_octal_listing(out, &output);
      fclose(out);
    } else {
      write_octal_listing(stdout, &output);
    }
  }

  return 0;
}
