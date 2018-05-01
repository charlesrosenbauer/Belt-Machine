#include "stdio.h"
#include "stdlib.h"
#include "belt.h"
#include "memory.h"
#include "core.h"










int main(){
  RAM ram = initRAM(1048576);

  uint16_t* program = malloc(16);
  int index = 0;
  addInsHead(program, &index, 0xC0000080);
  addOp_2Par(program, &index, RET__OP, 2, 3);
  addOp_1Par(program, &index, IMM__OP, 52);
  addOp_3Par(program, &index, PICK_OP, 2, 3, 4);

  printDecode(program);
}
