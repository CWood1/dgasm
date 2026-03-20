#include "ast.h"
#include "parser.h"
#include "lexer.h"
#include "assembler.h"
#include "symbol_tbl.h"
#include "error.h"
#include "opcode.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    YY_BUFFER_STATE buffer;
    char* fn;
    int lineno;
} include_frame_t;

extern include_frame_t include_stack[];

extern FILE* yyin;
int yylex_destroy(void);

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

int write_octal_simh(FILE *stream, const output_t* out) {
  if (!stream || !out)
    return -1;

  uint16_t addr = out->start_addr;

  for (uint16_t i = 0; i < out->size; i++, addr++) {
    fprintf(stream, "dep %06o %06o\n",
	    addr,
	    out->data[i]);
  }

  return 0;
}

int write_octal_eclipse(FILE *stream, const output_t *out) {
  if (!stream || !out)
    return -1;

  uint16_t addr = out->start_addr;

  fprintf(stream, "K0%o/%#o\n", addr, out->data[0]);

  for (uint16_t i = 1; i < out->size; i++, addr++) {
    fprintf(stream, "%#o\n",
	    out->data[i]);
  }

  fprintf(stream, "K\n");

  return 0;
}

void usage(const char* progname) {
  printf("Usage: %s [options] <input.s>\n\n", progname);

  printf("Options:\n");
  printf("  -t <cpu>      Specify target CPU architecture (required).\n");
  printf("  -o <file>     Set output filename (default: stdout)\n");
  printf("  -f <format>   Set output format (default: binary)\n");
  printf("  -h            Display this help message\n\n");

  printf("CPU architectures (-t):\n");
  printf("  nova1, nova3, nova4, eclipse_s140\n\n");

  printf("Output formats (-f):\n");
  printf("  binary        Raw machine code\n");
  printf("  octal         Human-readable octal dump\n");
  printf("  eclipse       DG Eclipse-compatible object format\n");
  printf("  simh          SIMH-compatible loadable format\n\n");
    
  printf("Example:\n");
  printf("  %s -t nova3 -f simh -o boot.out main.s\n", progname);
}

void version() {
  printf("dgasm version %s\n", DGASM_VERSION);
  printf("Copyright (c) 2026 Connor Wood (Venos)\n");
}

int main(int argc, char** argv) {
  char* fn = NULL;
  char* outputfn = NULL;
  char* outputformat = "bin";

  int cpu = CPU_NOVA1;

  int opt;

  while((opt = getopt(argc, argv, "o:f:t:h")) != -1) {
    switch(opt) {
    case 'o':
      outputfn = optarg;
      break;

    case 'h':
      usage(argv[0]);
      return 0;
      break;

    case 'f':      
      if (strcmp(optarg, "bin") == 0 ||
	  strcmp(optarg, "octal") == 0 ||
	  strcmp(optarg, "eclipse") == 0 ||
	  strcmp(optarg, "simh") == 0) {
	outputformat = optarg;
      } else {
	fprintf(stderr,
		"Invalid format '%s'. Use 'bin' or 'octal'.\n",
		optarg);
	return 1;
      }
      break;

    case 't':
      if (strcmp(optarg, "nova1") == 0)
	cpu = CPU_NOVA1;
      if (strcmp(optarg, "nova3") == 0)
	cpu = CPU_NOVA3;
      if (strcmp(optarg, "nova4") == 0)
	cpu = CPU_NOVA4;
      if (strcmp(optarg, "eclipse_s140") == 0)
	cpu = CPU_ECLIPSE_S140;
      break;

    default:
      usage(argv[0]);
      return 1;
    }
  }

  if (optind >= argc) {
    usage(argv[0]);
    return 1;
  }

  for(; optind < argc; optind++) {
    fn = argv[optind];
  }

  if (fn == NULL) {
    usage(argv[0]);
    return 1;
  }

  include_stack[0].fn = strdup(fn);
  include_stack[0].lineno = 1;
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
  yylex_destroy();

  if (get_err_count()) {
    return 1;
  }

  offset_t* offsets = pass1(prog, cpu);
  symboltbl_t* symbols = resolve_symbols(prog, offsets);
  output_t output = pass2(prog, symbols, cpu);

  free(prog);
  free_symbol_table(symbols);
  free_offsets(offsets);
  free_lines();

  if (get_err_count()) {
    return 1;
  }

  if (strcmp(outputformat, "bin") == 0) {
    if (outputfn == NULL) {
      usage(argv[0]);
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

      if (strcmp(outputformat, "octal") == 0)
	write_octal_listing(out, &output);
      else if (strcmp(outputformat, "eclipse") == 0)
	write_octal_eclipse(out, &output);
      else if (strcmp(outputformat, "simh") == 0)
	write_octal_simh(out, &output);
      fclose(out);
    } else {
      if (strcmp(outputformat, "octal") == 0)
	write_octal_listing(stdout, &output);
      else if (strcmp(outputformat, "eclipse") == 0)
	write_octal_eclipse(stdout, &output);
      else if (strcmp(outputformat, "simh") == 0)
	write_octal_simh(stdout, &output);
    }
  }

  free(output.data);

  return 0;
}
