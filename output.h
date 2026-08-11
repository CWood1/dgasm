#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "assembler.h"

int write_absolute_binary(const char* filename, const output_t *out);
int write_raw_binary(const char *filename, const output_t *out);
int write_octal_listing(FILE *stream, const output_t *out);
int write_octal_simh(FILE *stream, const output_t* out);
int write_octal_eclipse(FILE *stream, const output_t *out);

#endif
