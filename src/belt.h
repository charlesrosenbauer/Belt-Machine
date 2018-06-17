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
  union{
    uint64_t u64[2];
    uint32_t u32[4];
    uint16_t u16[8];
    uint8_t  u8[16];

    int64_t  i64[2];
    int32_t  i32[4];
    int16_t  i16[8];
    int8_t   i8[16];

    double   f64[2];
    float    f32[4];
  }val;

  uint8_t  vwidth;
  uint8_t  swidth;
  METADATA metadata[16];
}REGISTER;










typedef struct{
  REGISTER entries[32];
  int offset;
}BELT;











typedef uint16_t OPCODE;
static const uint16_t OPMASK_A = 0xF800;
static const uint16_t OPMASK_B = 0x07C0;
static const uint16_t OPMASK_X = 0x003F;
static const int OPSHIFT_A     = 11;
static const int OPSHIFT_B     =  6;
static const int OPSHIFT_X     =  0;










void getBeltItems(BELT*, OPCODE, REGISTER*, REGISTER*);
void pushBelt(BELT*, REGISTER);
void pushNewBelt(BELT*, BELT*, REGISTER);


#endif
