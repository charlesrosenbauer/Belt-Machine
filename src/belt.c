#include "belt.h"










inline void getBeltItems(BELT* belt, OPCODE op, REGISTER* a, REGISTER* b){
  int iA = (op & OPMASK_A) >> OPSHIFT_A;
  int iB = (op & OPMASK_B) >> OPSHIFT_B;

  a = &(belt->entries[(iA + belt->offset) % 32]);
  b = &(belt->entries[(iB + belt->offset) % 32]);
}
