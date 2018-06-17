#ifndef __MEM_HEADER__
#define __MEM_HEADER__

#include "stdint.h"










// Not going to simulate caches until later
typedef struct{
  uint8_t* bytes;
  int size;
}RAM;









// @TODO: Adjust these to deal with NARs and invalid addresses, etc.
RAM     initRAM  (int);
uint8_t  readByte(RAM*, uint64_t);
uint16_t readHalf(RAM*, uint64_t);
uint32_t readWord(RAM*, uint64_t);
uint64_t readDWrd(RAM*, uint64_t);
void    writeByte(RAM*, uint64_t, uint8_t );
void    writeHalf(RAM*, uint64_t, uint16_t);
void    writeWord(RAM*, uint64_t, uint32_t);
void    writeDWrd(RAM*, uint64_t, uint64_t);









#endif
