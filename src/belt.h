#ifndef __BELT_HEADER__
#define __BELT_HEADER__

#include "cstdint.h"








typedef uint16_t METADATA;
const uint16_t MD_VOID       = 0x0000;
const uint16_t MD_NONE       = 0x1000;
const uint16_t MD_NAR        = 0x2000;
const uint16_t MD_VALID      = 0x3000;
const uint16_t MD_MASK_VALID = 0x3000;
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










typedef uint16_t OPCODE;
const uint16_t OPMASK_A = 0xF800;
const uint16_t OPMASK_B = 0x07C0;
const uint16_t OPMASK_X = 0x003F;
const int OPSHIFT_A     = 11;
const int OPSHIFT_B     =  6;
const int OPSHIFT_X     =  0;










void getBeltItems(Belt*, OPCODE, REGISTER*, REGISTER*);


#endif
