/*
 * args.c
 *
 * Licensed under MIT license
 *
 */

#include "args.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int args_parse(struct args_s *args, const int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid number of arguments\n");
    return (EXIT_FAILURE);
  }

  /* Initialize the path string */
  args->path = malloc(strlen(argv[1])+1);
  if (args->path == NULL)
  {
    fprintf(stderr, "Memory allocation error\n");
    return (EXIT_FAILURE);
  }
  memset(args->path, '\0', strlen(args->path));

  /* Load its value */
  strcpy(args->path, argv[1]);

  return (EXIT_SUCCESS);
}

void args_free(struct args_s *args)
{
  free(args->path);
}
