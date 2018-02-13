#ifndef __ALU_HEADER__
#define __ALU_HEADER__

#include "stdint.h"
#include "belt.h"










// Handles a pair of ALUs, in case multiple parameters are passed into one
void aluOp(BELT* b, OPCODE, OPCODE);

#endif
