#ifndef __BELT_HEADER__
#define __BELT_HEADER__

#include "stdint.h"








typedef uint16_t METADATA;
static const uint16_t MD_VOID       = 0x0000;
static const uint16_t MD_NONE       = 0x1000;
static const uint16_t MD_NAR        = 0x2000;
static const uint16_t MD_VALID      = 0x3000;
static const uint16_t MD_MASK_VALID = 0x3000;
/*
  @Extend with Vector Support Later
*/








typedef struct{
  uint64_t val;
  METADATA  metadata;
}REGISTER;










typedef struct{
  REGISTER entries[32];
  int offset;
}BELT;










typedef struct{
  // Internal ganging registers
  REGISTER a, b, c, d;

  // Registers for delayed instructions
  REGISTER quot [32];   // Delay = 24c
  REGISTER remn [32];   // "
  REGISTER mult [32];   // Delay =  3c
  int offset;
}ALU;










typedef struct{
  // Internal ganging registers
  REGISTER a, b, c, d;

  // Registers for delayed instructions
  REGISTER quot [32];   // Delay = 18c
  REGISTER remn [32];   // "
  REGISTER mult [32];   // Delay = 3c
  int offsetQ, offsetR, offsetM;
}FPU;










typedef struct{
  REGISTER retires[16];   // Retire stations for load/store
}RETIRE;










typedef uint16_t OPCODE;
static const uint16_t OPMASK_A = 0xF800;
static const uint16_t OPMASK_B = 0x07C0;
static const uint16_t OPMASK_X = 0x003F;
static const int OPSHIFT_A     = 11;
static const int OPSHIFT_B     =  6;
static const int OPSHIFT_X     =  0;










void getBeltItems(BELT*, OPCODE, REGISTER*, REGISTER*);


#endif
