/*
 * dis.c
 *
 * Licensed under MIT license
 *
 */

#include "dis.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int disassemble(const uint8_t *code, const size_t size)
{
  size_t i;

  for (i=0; i<size; ++i)
  {
    switch(code[i])
    {
      case 0x00:
        printf("NOP\n");
        break;
      case 0x01:
        printf("LXI 0x%02X, 0x%02X\n", code[i+1], code[i+2]);
        i += 2;
        break;
    }
  }
  return (EXIT_SUCCESS);
}
