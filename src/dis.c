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
      /* 0x00 is undefined */

      case 0x01:
        printf("LXI B, 0x%04X\n", code[i+1] | code[i+2] << 8);
        i += 2;
        break;

      case 0x02:
        printf("STAX B\n");
        break;

      case 0x03:
        printf("INX B\n");
        break;

      case 0x04:
        printf("INR B\n");
        break;

      case 0x05:
        printf("DCR B\n");
        break;

      case 0x06:
        printf("MVI B, 0x%02X\n", code[i+1]);
        ++i;
        break;

      case 0x07:
        printf("RLC\n");
        break;

      /* 0x08 is undefined */

      case 0x09:
        printf("DAD B\n");
        break;

      case 0x0A:
        printf("LDAX B\n");
        break;

      case 0x0B:
        printf("DCX B\n");
        break;

      case 0x0C:
        printf("INR C\n");
        break;

      case 0x0D:
        printf("DCR C\n");
        break;

      case 0x0E:
        printf("MVI C, 0x%02X\n", code[i+1]);
        ++i;
        break;

      case 0x0F:
        printf("RRC\n");
        break;

      /* 0x10 is undefined */

      case 0x11:
        printf("LXI D, 0x%04X\n", code[i+1] | code[i+2] << 8);
        i +=2;
        break;

      case 0x12:
        printf("STAX D\n");
        break;

      case 0x13:
        printf("INX D\n");
        break;

      default:
        printf("NOP\n");
        break;
    }
  }
  return (EXIT_SUCCESS);
}
