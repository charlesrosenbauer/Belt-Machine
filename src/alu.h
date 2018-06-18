#ifndef __ALU_HEADER__
#define __ALU_HEADER__

#include "stdint.h"
#include "belt.h"
#include "core.h"










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
static const int FMA__OP = 31;  // (a * b) + c
static const int SMRI_OP = 32;
static const int SMRE_OP = 33;
static const int REMN_OP = 34;
static const int FIX__OP = 35;
static const int FLT__OP = 36;
static const int WIDE_OP = 37;
static const int NARW_OP = 38;
static const int SUMV_OP = 39;
static const int UADD_OP = 40;
static const int USUB_OP = 41;
static const int UMUL_OP = 42;
static const int UDIV_OP = 43;

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
static const int ROTS_OP =  7;
static const int ALLC_OP =  8;
static const int FREE_OP =  9;
static const int ALCS_OP = 10;










static const int V08x01 =  0;
static const int V16x01 =  1;
static const int V32x01 =  2;
static const int V64x01 =  3;
// No 128bit for not, V128x01 = 4;
static const int V08x02 =  5;
static const int V16x02 =  6;
static const int V32x02 =  7;
static const int V64x02 =  8;
// V128x02 = 9;
static const int V08x04 = 10;
static const int V16x04 = 11;
static const int V32x04 = 12;
static const int V64x04 = 13;
//empty
static const int V08x08 = 14;
static const int V16x08 = 15;
static const int V32x08 = 16;
//empty
//empty
static const int V08x16 = 17;
static const int V16x16 = 18;
//empty
//empty
//empty
static const int V08x32 = 18;















// Handles a pair of ALUs, in case multiple parameters are passed into one
int aluOp(BELTCORE*, int, OPCODE, REGISTER*, REGISTER*);

//For some reason I have to declare these here to avoid linker errors?
REGISTER uaddOp(REGISTER, REGISTER);
REGISTER usubOp(REGISTER, REGISTER);
REGISTER umulOp(REGISTER, REGISTER);
REGISTER saddOp(REGISTER, REGISTER);
REGISTER ssubOp(REGISTER, REGISTER);
REGISTER smulOp(REGISTER, REGISTER);

#endif
