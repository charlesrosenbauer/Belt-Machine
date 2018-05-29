#ifndef __CORE_HEADER__
#define __CORE_HEADER__

#include "belt.h"
#include "alu.h"










typedef struct{
  REGISTER retires[16];   // Retire stations for load/store
}RETIRE;










typedef enum {
  DSM_REGISTER = 0,
  DSM_LOAD     = 1
} DELAYSLOTMODE;

typedef struct{
  REGISTER r;
  DELAYSLOTMODE mode;
}DELAYSLOT;










typedef struct{
  DELAYSLOT slots [24][33];
  uint32_t  activeMask[33];
  int       timeIndex;
  /*
     0- 8 are  1 cycle READ slots
     9-16 are  1 cycle ALU  slots
    17-18 are  3 cycle ALU  slots
    19-20 are 10 cycle ALU  slots
    21-24 are variable delay LOAD slots

    CALL and PICK stages aren't handled via delay, as they have no virtual delay
    The WRITE stage produces no belt outputs, so nothing needed there.

    activeMask features a bit for each slot. If a slot's corresponding bit is
    zero, it will NOT be put on the belt.
  */
}DELAYGRID;










typedef struct{
  BELT belt;

  DELAYGRID delays;

  RETIRE retire;  // Retire stations
}BELTCORE;










void coreStep(BELTCORE*);
uint16_t* printDecode(uint16_t*);
void addOp_1Par(uint16_t*, int*, int, int);
void addOp_2Par(uint16_t*, int*, int, int, int);
void addOp_3Par(uint16_t*, int*, int, int, int, int);
void addInsHead(uint16_t*, int*, uint32_t);



#endif
