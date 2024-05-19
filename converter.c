#include "converter.h"

int main(int argc, char *argv[])
{
  enum base convert_from = argv[1][0];
  enum base convert_to = argv[1][1];
  void (*function_ptr) (enum base format, char **number);

  if (convert_to == HEX)
  {
    function_ptr = print_hex;
  }
  else if (convert_to == BIN) 
  {
    function_ptr = print_bin;
  }
  else if (convert_to == DEC)
  {
    function_ptr = print_dec;
  }
  else 
  {
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 2; i < argc; i++)
  {
    (*function_ptr) (convert_from, &(argv[i]));
  }

  exit(EXIT_SUCCESS);
}

void print_hex(enum base format, char **number)
{
  if (format == DEC)
  {
    char *endptr;
    printf("%lx\n", strtol(*number, &endptr, DECIMAL_BASE));
  }
  else if (format == BIN)
  {
    char *endptr;
    printf("%lx\n", strtol(*number, &endptr, BINARY_BASE));
  }
  else 
  {
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }
}

void print_bin(enum base format, char **number)
{
  char *endptr;
  long long int decimal; // though var name is decimal, it is not necessarily so

  if (format == DEC)
  {
    decimal = strtol(*number, &endptr, DECIMAL_BASE);
  }

  else if (format == HEX)
  {
    decimal = strtol(*number, &endptr, HEX_BASE);
  }
  else 
  {  
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }

  char *binary = malloc(MAX_INT_LEN + 1);
  char *original_binary = binary;

  if(binary == NULL)
      exit(EXIT_FAILURE);

  binary += MAX_INT_LEN;
  *binary = '\0';

  if(decimal == 0)
  {
      --binary;
      *binary = '0';
  }

  while(decimal > 0)
  {
      --binary;
      *binary = decimal % 2 + '0';
      decimal = decimal / 2;
  }

  printf("%s\n", binary);

  free(original_binary);
}

void print_dec(enum base format, char **number)
{
  if (format == BIN)
  {
    char *endptr;
    printf("%ld\n", strtol(*number, &endptr, BINARY_BASE));
  }
  else if (format == HEX)
  {
    char *endptr;
    printf("%ld\n", strtol(*number, &endptr, HEX_BASE));
  }
  else 
  {
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }
}
