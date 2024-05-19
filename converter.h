#ifndef _CONVERTER_H
#define _CONVERTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_BASE 2
#define DECIMAL_BASE 10
#define HEX_BASE 16
#define MAX_INT_LEN 64
#define NUM_BASES 3
#define MIN_ARGS 3

enum base {
  HEX = 'h',
  BIN = 'b',
  DEC = 'd'
};

void print_hex(enum base format, char **number);
void print_dec(enum base format, char **number);
void print_bin(enum base format, char **number);

void print_help(void);
#endif
