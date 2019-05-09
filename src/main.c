/*
 * main.c
 *
 * Licensed under MIT License
 *
 */

#include "args.h"
#include "dis.h"
#include "util.h"
#include "text.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  struct args_s args;
  size_t input_file_size;
  uint8_t *code_buffer;
  FILE *input_file;

  /* Parse the shell arguments */
  if (args_parse(&args, argc, argv) == EXIT_FAILURE)
    return (retstr(EXIT_FAILURE, ERR_ARGS, __FILE__, __LINE__));

  /* Open the input file */
  if ((input_file = fopen(args.path, "r")) == NULL)
  {
    args_free(&args);
    return (retstr(EXIT_FAILURE, ERR_FILE, __FILE__, __LINE__));
  }

  /* Get its size */
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);

  /* Allocate memory for the code */
  if ((code_buffer = malloc(input_file_size)) == NULL)
  {
    args_free(&args);
    fclose(input_file);
    return (retstr(EXIT_FAILURE, ERR_MALLOC, __FILE__, __LINE__));
  }

  /* Load the code to the buffer */
  if (fread(code_buffer, sizeof(uint8_t), input_file_size, input_file) != input_file_size)
  {
    args_free(&args);
    fclose(input_file);
    free(code_buffer);
    return (retstr(EXIT_FAILURE, ERR_FILE, __FILE__, __LINE__));
  }

  /* Actual disassembly */
  if (disassemble(code_buffer, input_file_size) == EXIT_FAILURE)
  {
    args_free(&args);
    fclose(input_file);
    free(code_buffer);
    return (retstr(EXIT_FAILURE, ERR_DISASSEMBLY, __FILE__, __LINE__));
  }

  return (EXIT_SUCCESS);
}
