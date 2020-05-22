/*
 * util.c
 *
 * Licensed under MIT license
 *
 */

#include "util.h"

#include <stdio.h>

/* This function may not be worthy at first glance, but boy does it clean my code */
int retstr(const int ret, const char *str, const char *file, const int line)
{
  fprintf(stderr, str, file, line);
  return (ret);
}
