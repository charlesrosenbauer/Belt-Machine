#ifndef __ALU_HEADER__
#define __ALU_HEADER__

#include "cstdint.h"
#include "belt.h"










// Handles a pair of ALUs, in case multiple parameters are passed into one
void aluOp(Belt* b, uint16_t, uint16_t);

#endif
