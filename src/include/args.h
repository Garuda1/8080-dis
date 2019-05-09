/*
 * args.h
 *
 * Licensed under MIT license
 *
 */

#ifndef ARGS_H
#define ARGS_H

struct args_s
{
  char *path;
};

int args_parse(struct args_s *args, const int argc, char **argv);
void args_free(struct args_s *args);

#endif
