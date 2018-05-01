#ifndef __CORE_HEADER__
#define __CORE_HEADER__

#include "belt.h"
#include "alu.h"










typedef struct{
  REGISTER retires[16];   // Retire stations for load/store
}RETIRE;










typedef struct{
  BELT belt;

  ALU alu[4]; // 2 ALU gangs, 4 ALUs total

  RETIRE retire;  // Retire stations
}BELTCORE;










void coreStep(BELTCORE*);
void printDecode(uint16_t*);
void addOp_2Par(uint16_t*, int*, int, int, int);
void addOp_3Par(uint16_t*, int*, int, int, int, int);
void addInsHead(uint16_t*, int*, uint32_t);



#endif
