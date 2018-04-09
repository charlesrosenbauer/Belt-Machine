#ifndef __CORE_HEADER__
#define __CORE_HEADER__

#include "belt.h"
#include "alu.h"










typedef struct{
  REGISTER retires[16];   // Retire stations for load/store
}RETIRE;










typedef struct{
  BELT belt;

  ALU alu[2]; // 2 ALU gangs, 4 ALUs total
  FPU fpu[2]; // 2 FPU gangs, 4 FPUs total

  RETIRE retire;  // Retire stations
}BELTCORE;










void coreStep(BELTCORE*);



#endif
