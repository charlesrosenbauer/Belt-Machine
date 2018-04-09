#ifndef __ALU_HEADER__
#define __ALU_HEADER__

#include "stdint.h"
#include "belt.h"










typedef struct{
  // Internal ganging registers
  REGISTER a, b, c, d;

  // Registers for delayed instructions
  REGISTER quot [2][32];   // Delay = 24c
  REGISTER remn [2][32];   // "
  REGISTER mult [2][32];   // Delay =  3c
  int offset;
}ALU;










typedef struct{
  // Internal ganging registers
  REGISTER a, b, c, d;

  // Registers for delayed instructions
  REGISTER quot [2][32];   // Delay = 18c
  REGISTER remn [2][32];   // "
  REGISTER mult [2][32];   // Delay = 3c
  int offsetQ, offsetR, offsetM;
}FPU;










// Handles a pair of ALUs, in case multiple parameters are passed into one
void aluOp(BELT*, BELT*, ALU*, OPCODE, OPCODE);
void fpuOp(BELT*, BELT*, FPU*, OPCODE, OPCODE);

#endif
