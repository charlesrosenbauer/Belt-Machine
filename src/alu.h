#ifndef __ALU_HEADER__
#define __ALU_HEADER__

#include "stdint.h"
#include "belt.h"










typedef struct{
  REGISTER vals [32];
  int delay;
}DELAY;










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










static const int RET__OP = 0;
static const int IMM__OP = 1;
static const int NIL__OP = 2;
static const int NAR__OP = 3;
static const int ZER__OP = 4;
static const int ONE__OP = 5;
static const int FILL_OP = 6;

static const int IADD_OP =  0;
static const int ISUB_OP =  1;
static const int IMUL_OP =  2;
static const int IDIV_OP =  3;
static const int FADD_OP =  4;
static const int FSUB_OP =  5;
static const int FMUL_OP =  6;
static const int FDIV_OP =  7;
static const int AND__OP =  8;
static const int XOR__OP =  9;
static const int OR___OP = 10;
static const int NOT__OP = 11;
static const int SHL__OP = 12;
static const int SHR__OP = 13;
static const int INC__OP = 14;
static const int DEC__OP = 15;
static const int ILS__OP = 16;
static const int IGT__OP = 17;
static const int IZR__OP = 18;
static const int IEQ__OP = 19;
static const int CNIL_OP = 20;
static const int CNAR_OP = 21;
static const int FLS__OP = 22;
static const int FGT__OP = 23;
static const int FZR__OP = 24;
static const int FEQ__OP = 25;
static const int PCNT_OP = 26;
static const int ARGX_OP = 27;
static const int FMAS_OP = 28;  // (a * b) + (c * d), (a * b) - (c * d)
static const int IADS_OP = 29;  // a + b + c + d
static const int FADS_OP = 30;  // a + b + c + d

static const int ARGC_OP =  0;
static const int CALL_OP =  1;

static const int PICK_OP =  0;
static const int RECR_OP =  1;

static const int STR__OP =  0;
static const int LOD__OP =  1;
static const int BR___OP =  2;
static const int BRT__OP =  3;
static const int BRF__OP =  4;
static const int SPIL_OP =  5;
static const int EXIT_OP =  6;










// Handles a pair of ALUs, in case multiple parameters are passed into one
void  aluOp(BELT*, BELT*, ALU*, OPCODE, OPCODE);
void  fpuOp(BELT*, BELT*, FPU*, OPCODE, OPCODE);
DELAY makeDelay(int);
void  pushDelay(DELAY*, REGISTER);
void  popDelay (DELAY*, BELT*);

#endif
