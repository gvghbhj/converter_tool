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
#define ANSI_ESCAPE_CODE_BLUE "\033[34;1m"
#define ANSI_ESCAPE_CODE_RESET "\033[0m"

enum base
{
  HEX = 'h',
  BIN = 'b',
  DEC = 'd'
};

void print_hex(enum base format, char **number);
void print_dec(enum base format, char **number);
void print_bin(enum base format, char **number);

void print_help(void);
#endif
