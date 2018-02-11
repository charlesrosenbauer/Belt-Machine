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


#endif
