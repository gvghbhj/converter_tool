#include "converter.h"

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    printf("ERROR: Not enough args");
    print_help();
    exit(EXIT_FAILURE);
  }
  // Checking for a help flag in args
  static const char *help_flag = "--help";
  for (int i = 1; i < argc; i++)
  {
    if (strncmp(help_flag, argv[i], strlen(help_flag)) == 0)
    {
      print_help();
      exit(EXIT_SUCCESS);
    }
  }
  
  // need at least 3 args if no help flag
  if (argc < MIN_ARGS)
  {
    print_help();
    exit(EXIT_FAILURE);
  }
  

  // ./converter dh 10 for example, d is the decimal, base to convert from, h is hexadecimal base to convert to
  enum base convert_from = argv[1][0];
  enum base convert_to = argv[1][1];

  // A function pointer to the function that the for loop will execute
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

  printf("\n"); // for better formatting
  
  // execute the correct function for all members of argv
  for (int i = 2; i < argc; i++)
  {
    (*function_ptr) (convert_from, &(argv[i]));
  }

  exit(EXIT_SUCCESS);
}

// A function that takes in either a binary or decimal number, and prints the equivalent hex number
void print_hex(enum base format, char **number)
{
  if (format == DEC)
  {
    char *endptr;
    printf("%s in hex is: ", *number);
    printf(ANSI_ESCAPE_CODE_BLUE "0x%.2lx\n" ANSI_ESCAPE_CODE_RESET, strtol(*number, &endptr, DECIMAL_BASE)); // see man strtol
  }
  else if (format == BIN)
  {
    char *endptr;
    printf("%s in hex is: ", *number);
    printf(ANSI_ESCAPE_CODE_BLUE "0x%.2lx\n" ANSI_ESCAPE_CODE_RESET, strtol(*number, &endptr, BINARY_BASE));
  }
  else 
  {
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }
}

// A function that takes in either a hex or decimal number, and prints the equivalent binary number
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

  // array that stores binary number
  char *binary = malloc(MAX_INT_LEN + 1);
  char *original_binary = binary; // because we increment and decrement the binary pointer, to free binary, it is necessary to have a pointer to original binary.

  if(binary == NULL) // memory not allocated properly
      exit(EXIT_FAILURE);

  binary += MAX_INT_LEN; // go to last element in array
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

  printf("%s in binary is: ", *number);
  printf(ANSI_ESCAPE_CODE_BLUE "0b%s\n" ANSI_ESCAPE_CODE_RESET, binary);

  free(original_binary);
}

// A function that takes in either a binary or hex number, and prints the equivalent decimal number
void print_dec(enum base format, char **number)
{
  if (format == BIN)
  {
    char *endptr;
    printf("%s is decimal is: ", *number);
    printf(ANSI_ESCAPE_CODE_BLUE "%ld\n" ANSI_ESCAPE_CODE_RESET, strtol(*number, &endptr, BINARY_BASE));
  }
  else if (format == HEX)
  {
    char *endptr;
    printf("%s is decimal is: ", *number);
    printf(ANSI_ESCAPE_CODE_BLUE "%ld\n" ANSI_ESCAPE_CODE_RESET, strtol(*number, &endptr, HEX_BASE));
  }
  else 
  {
    printf("ERROR: Not a valid base to convert from\n");
    exit(EXIT_FAILURE);
  }
}

// prints out help info
void print_help(void)
{
  printf("converter: a tool that converts to/from binary, hexadecimal, and decimal. (base 2, 16, 10)\n\n");
  printf("FORMAT: ./converter (convert_from)(convert_to) [array of numbers in base of convert_from]\n\n");
  printf("FLAGS: --help (prints out this help message)\n\n");
  printf("EXAMPLE: to convert the decimal numbers 18 and 20 to hexadecimal: ./converter dh 18 20\n\n");
  printf("NOTE: DO NOT ADD 0x or 0b when giving hex or binary input\n");
}
