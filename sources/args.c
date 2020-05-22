/*
 * args.c
 *
 * Licensed under MIT license
 *
 */

#include "args.h"
#include "util.h"
#include "text.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int args_parse(struct args_s *args, const int argc, char **argv)
{
  if (argc != 2)
    return (retstr(EXIT_FAILURE, ERR_ARGS, __FILE__, __LINE__));

  /* Initialize the path string */
  if ((args->path = malloc(strlen(argv[1])+1)) == NULL)
    return (retstr(EXIT_FAILURE, ERR_MALLOC, __FILE__, __LINE__));
  memset(args->path, '\0', strlen(args->path));

  /* Load its value */
  strcpy(args->path, argv[1]);

  return (EXIT_SUCCESS);
}

void args_free(struct args_s *args)
{
  free(args->path);
}
