#include "memory.h"
#include "stdlib.h"










RAM initRAM(int size){
  RAM ret;
  ret.size = size;
  ret.bytes = malloc(sizeof(uint8_t) * size);
  return ret;
}





// @TODO: Make these functions work with alignment, or find an alternate solution




uint8_t  readByte(RAM* ram, uint64_t ptr){
  uint8_t ret = 0;
  if(ptr < ram->size)
    ret = ram->bytes[ptr];
  return ret;
}










uint16_t readHalf(RAM* ram, uint64_t ptr){
  uint16_t ret = 0;
  uint16_t* bytes = (uint16_t*)ram->bytes;
  ptr = ptr << 1;   // Auto-alignment
  if(ptr < ram->size)
    ret = ram->bytes[ptr];
  return ret;
}










uint32_t readWord(RAM* ram, uint64_t ptr){
  uint32_t ret = 0;
  uint32_t* bytes = (uint32_t*)ram->bytes;
  ptr = ptr << 2;   // Auto-alignment
  if(ptr < ram->size)
    ret = ram->bytes[ptr];
  return ret;
}










uint64_t readDWrd(RAM* ram, uint64_t ptr){
  uint64_t ret = 0;
  uint64_t* bytes = (uint64_t*)ram->bytes;
  ptr = ptr << 3;   // Auto-alignment
  if(ptr < ram->size)
    ret = ram->bytes[ptr];
  return ret;
}










void writeByte(RAM* ram, uint64_t ptr, uint8_t val){
  if(ptr < ram->size)
    ram->bytes[ptr] = val;
}










void writeHalf(RAM* ram, uint64_t ptr, uint16_t val){
  ptr = ptr << 1;   // Auto-alignment
  uint16_t* bytes = (uint16_t*)ram->bytes;
  if(ptr < ram->size)
    bytes[ptr] = val;
}










void writeWord(RAM* ram, uint64_t ptr, uint32_t val){
  ptr = ptr << 2;   // Auto-alignment
  uint32_t* bytes = (uint32_t*)ram->bytes;
  if(ptr < ram->size)
    bytes[ptr] = val;
}










void writeDWrd(RAM* ram, uint64_t ptr, uint64_t val){
  ptr = ptr << 3;   // Auto-alignment
  uint64_t* bytes = (uint64_t*)ram->bytes;
  if(ptr < ram->size)
    bytes[ptr] = val;
}
