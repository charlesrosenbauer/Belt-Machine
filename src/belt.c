#include "belt.h"










inline void getBeltItems(BELT* belt, OPCODE op, REGISTER* a, REGISTER* b){
  int iA = (op & OPMASK_A) >> OPSHIFT_A;
  int iB = (op & OPMASK_B) >> OPSHIFT_B;

  a = &(belt->entries[(iA + belt->offset) % 32]);
  b = &(belt->entries[(iB + belt->offset) % 32]);
}










inline void pushBelt(BELT* belt, REGISTER r){
  belt->entries[belt->offset] = r;
  belt->offset = (belt->offset + 1) % 32;
}










inline void pushNewBelt(BELT* belt, BELT* out, REGISTER r){
  *out = *belt;
  out->entries[out->offset] = r;
  out->offset = (out->offset + 1) % 32;
}
