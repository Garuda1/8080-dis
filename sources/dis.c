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

static char *8080_opcode[] =
{
  /* 0x00 */
  "NOP",
  "LXI B",
  "STAX B",
  "INX B",
  "INR B",
  "DCR B",
  "MVI B",
  "RLC",

  /* 0x08 */
  "NOP",
  "DAD B",
  "LDAX B",
  "DCX B",
  "INR C",
  "DCR C",
  "MVI C",
  "RRC",

  /* 0x10 */
  "NOP",
  "LXI D",
  "STAX D",
  "INX D",
  "INR D",
  "DCR D",
  "MVI D",
  "RAL",

  /* 0x18 */
  "NOP",
  "DAD D",
  "LDAX D",
  "DCX D",
  "INR E",
  "DCR E",
  "MVI E",
  "RAR",

  /* 0x20 */
  "NOP",
  "NOP",
  "LXI H",
  "SHLD",
  "INX H",
  "INR H",
  "DCR H",
  "MVI H",
  "DAA",

  /* 0x28 */
  "NOP",
  "DAD H",
  "LHLD",
  "DCX H",
  "INR L",
  "DCR L",
  "MVI L",
  "CMA",

  /* 0x30 */
  "NOP",
  "LXI SP",
  "STA",
  "INX SP",
  "INR M",
  "DCR M",
  "MVI M",
  "STC",

  /* 0x38 */
  "NOP",
  "DAD SP",
  "LDA",
  "DCX SP",
  "INR A",
  "DCR A",
  "MVI A",
  "CMC",

  /* 0x40 */
  "MOV B, B",
  "MOV B, C",
  "MOV B, D",
  "MOV B, E",
  "MOV B, H",
  "MOV B, L",
  "MOV B, M",
  "MOV B, A",

  /* 0x48 */
  "MOV C, B",
  "MOV C, C",
  "MOV C, D",
  "MOV C, E",
  "MOV C, H",
  "MOV C, L",
  "MOV C, M",
  "MOV C, A",

  /* 0x50 */
  "MOV D, B",
  "MOV D, C",
  "MOV D, D",
  "MOV D, E",
  "MOV D, H",
  "MOV D, L",
  "MOV D, M",
  "MOV D, A",

  /* 0x58 */
  "MOV E, B",
  "MOV E, C",
  "MOV E, D",
  "MOV E, E",
  "MOV E, H",
  "MOV E, L",
  "MOV E, M",
  "MOV E, A",

  /* 0x60 */
  "MOV H, B",
  "MOV H, C",
  "MOV H, D",
  "MOV H, E",
  "MOV H, H",
  "MOV H, L",
  "MOV H, M",
  "MOV H, A",

  /* 0x68 */
  "MOV L, B",
  "MOV L, C",
  "MOV L, D",
  "MOV L, E",
  "MOV L, H",
  "MOV L, L",
  "MOV L, M",
  "MOV L, A",

  /* 0x70 */
  "MOV M, B",
  "MOV M, C",
  "MOV M, D",
  "MOV M, E",
  "MOV M, H",
  "MOV M, L",
  "HLT",
  "MOV M, A",

  /* 0x78 */
  "MOV A, B",
  "MOV A, C",
  "MOV A, D",
  "MOV A, E",
  "MOV A, H",
  "MOV A, L",
  "MOV A, M",
  "MOV A, A",

  /* 0x80 */
  "ADD B",
  "ADD C",
  "ADD D",
  "ADD E",
  "ADD H",
  "ADD L",
  "ADD M",
  "ADD A",

  /* 0x88 */
  "ADC B",
  "ADC C",
  "ADC D",
  "ADC E",
  "ADC H",
  "ADC L",
  "ADC M",
  "ADC A",

  /* 0x90 */
  "SUB B",
  "SUB C",
  "SUB D",
  "SUB E",
  "SUB H",
  "SUB L",
  "SUB M",
  "SUB A",

  /* 0x98 */
  "SBB B",
  "SBB C",
  "SBB D",
  "SBB E",
  "SBB H",
  "SBB L",
  "SBB M",
  "SBB A",

  /* 0xA0 */
  "ANA B",
  "ANA C",
  "ANA D",
  "ANA E",
  "ANA H",
  "ANA L",
  "ANA M",
  "ANA A",

  /* 0xA8 */
  "XRA B",
  "XRA C",
  "XRA D",
  "XRA E",
  "XRA H",
  "XRA L",
  "XRA M",
  "XRA A",

  /* 0xB0 */
  "ORA B",
  "ORA C",
  "ORA D",
  "ORA E",
  "ORA H",
  "ORA L",
  "ORA M",
  "ORA A",

  /* 0xB8 */
  "CMP B",
  "CMP C",
  "CMP D",
  "CMP E",
  "CMP H",
  "CMP L",
  "CMP M",
  "CMP A",

  /* 0xC0 */
  "RNZ",
  "POP B",
  "JNZ",
  "JMP",
  "CNZ",
  "PUSH B",
  "ADI",
  "RST 0",

  /* 0xC8 */
  "RZ",
  "RET",
  "JZ",
  "JMP",
  "CZ",
  "CALL",
  "ACI",
  "RST 1",

  /* 0xD0 */
  "RNC",
  "POP D",
  "JNC",
  "OUT",
  "CNC",
  "PUSH D",
  "SUI",
  "RST 2"

  /* 0xD8 */
  "RC",
  "RET",
  "JC",
  "IN",
  "CC",
  "CALL",
  "SBI",
  "RST 3",

  /* 0xE0 */
  "RPO",
  "POP H",
  "JPO",
  "XTHL",
  "CPO",
  "PUSH H",
  "ANI",
  "RST 4",

  /* 0xE8 */
  "RPE",
  "PCHL",
  "JPE",
  "XCHG",
  "CPE",
  "CALL",
  "XRI",
  "RST 5",

  /* 0xF0 */
  "RP",
  "POP PSW",
  "JP",
  "DI",
  "CP",
  "PUSH PSW",
  "ORI",
  "RST 6",

  /* 0xF8 */
  "RM",
  "SPHL",
  "JM",
  "EI",
  "CM",
  "CALL",
  "CPI",
  "RST 7"
};

int disassemble(const uint8_t *code, const size_t size)
{
  size_t i;

  for (i=0; i<size; ++i)
  {
    printf("%s", 8080_opcode[code[i]]);

    switch(code[i])
    {
      /* LXI B, d16 */
      case 0x01:
        printf(", 0x%04X", code[i+1] | code[i+2] << 8);
        i += 2;
        break;

      /* MVI B, d8 */
      case 0x06:
        printf(", 0x%02X", code[i+1]);
        ++i;
        break;

      /* MVI C, D8 */
      case 0x0E:
        printf(", 0x%02X", code[i+1]);
        ++i;
        break;

      /* LXI D, D16 */
      case 0x11:
        printf(", 0x%04X", code[i+1] | code[i+2] << 8);
        i +=2;
        break;
    }

    printf("\n");
  }

  return (EXIT_SUCCESS);
}
