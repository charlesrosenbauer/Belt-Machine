#include "alu.h"
#include "belt.h"









void aluOp(BELT* belt, OPCODE aop, OPCODE bop){

  int opA = aop & OPMASK_X;
  int opB = bop & OPMASK_X;

  if((opA | opB) == 0) return; // Only nops, no need to do anything.

  REGISTER argA, argB;  // In case of the argument operation
  argA.metadata = MD_NONE;
  argB.metadata = MD_NONE;

  if(opA){
    REGISTER a, b;
    getBeltItems(belt, aop, &a, &b);

    REGISTER q, r;

    uint16_t md_a = a.metadata & MD_MASK_VALID;
    uint16_t md_b = b.metadata & MD_MASK_VALID;

    if((md_a == MD_VALID) && (md_b == MD_VALID)){
      // Both registers are valid

      switch(opA){
        case 0: // NOP
        break;

        case 1: // ADD
        q.metadata = MD_VALID;
        q.val = a.val + b.val;
        break;

        case 2: // SUB
        q.metadata = MD_VALID;
        q.val = a.val - b.val;
        break;

        case 3: // AND
        q.metadata = MD_VALID;
        q.val = a.val & b.val;
        break;

        case 4: // OR
        q.metadata = MD_VALID;
        q.val = a.val | b.val;
        break;

        case 5: // XOR
        q.metadata = MD_VALID;
        q.val = a.val ^ b.val;
        break;

        case 6: // SHL
        q.metadata = MD_VALID;
        q.val = a.val << b.val;
        break;

        case 7: // SHR
        q.metadata = MD_VALID;
        q.val = a.val >> b.val;
        break;

        case 8: // NOT
        q.metadata = MD_VALID;
        q.val = ~a.val;
        break;

        case 9: // INC
        q.metadata = MD_VALID;
        q.val = a.val + 1;
        break;

        case 10: // DEC
        q.metadata = MD_VALID;
        q.val = a.val - 1;
        break;

        case 11: // ARGS
        q = a;
        r = b;
        break;
      }
    }else if(md_a == MD_VALID){
      switch(opA){
        case 8: // NOT
        q.metadata = MD_VALID;
        q.val = ~a.val;
        break;

        case 9: // INC
        q.metadata = MD_VALID;
        q.val = a.val + 1;
        break;

        case 10: // DEC
        q.metadata = MD_VALID;
        q.val = a.val - 1;
        break;

        case 11: // ARGS
        q = a;
        r = b;
        break;
      }
    }else if(opA == 11){
      // ARGS
      q = a;
      r = b;
    }
  }

  /*
  if(opB){

  }*/
}
