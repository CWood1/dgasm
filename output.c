#include "assembler.h"

#include <stdio.h>

int write_absolute_binary(const char* filename, const output_t *out) {
  FILE *f = fopen(filename, "wb");
  if (!f) {
    perror("fopen");
    return -1;
  }

  uint16_t addr = out->start_addr;
  uint16_t i = 0;

  while (i < out->size) {
    // First, output the block size
    int remaining = out->size - i;
    int16_t block_size = remaining > 16 ? 16 : (int16_t)remaining;
    block_size = -block_size;

    fwrite(&block_size, sizeof(int16_t), 1, f);

    // Next, output the address
    fwrite(&addr, sizeof(uint16_t), 1, f);

    // Next, output, the checksum
    uint16_t running_total = 0;
    for (uint16_t j = 0; j < -block_size; j++) {
      running_total += out->data[i + j];
    }
    uint16_t checksum = -(block_size + addr + running_total);
    fwrite(&checksum, sizeof(uint16_t), 1, f);

    // Lastly, output the data itself
    for (uint16_t j = 0; j < -block_size; j++) {
      fwrite(&(out->data[i + j]), sizeof(uint16_t), 1, f);
    }

    i += -block_size;
    addr += -block_size;
  }
  return 0;
}

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
