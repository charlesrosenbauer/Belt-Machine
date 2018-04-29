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



#endif
