#include "alu.h"
#include "belt.h"










REGISTER getMetaData_1Par(REGISTER a){
  REGISTER ret;
  ret.metadata = a.metadata;
  ret.val = 0;
  return ret;
}










REGISTER getMetaData_2Par(REGISTER a, REGISTER b){
  REGISTER ret;
  if(((a.metadata & MD_MASK_VALID) == MD_VALID) && ((a.metadata & MD_MASK_VALID) == MD_VALID)){
    ret.metadata = MD_VALID;
  }else if(((a.metadata & MD_MASK_VALID) == MD_NONE) || ((a.metadata & MD_MASK_VALID) == MD_NONE)){
    ret.metadata = MD_NONE;
  }else if(((a.metadata & MD_MASK_VALID) == MD_NAR) || ((a.metadata & MD_MASK_VALID) == MD_NAR)){
    ret.metadata = MD_NAR;
  }else{
    ret.metadata = MD_VOID;
  }
  ret.val = 0;
  return ret;
}








/*
  @FIX : This needs to be adapted to better take into account None and Invalid values.
*/
void aluOp(BELT* belt, OPCODE aop, OPCODE bop){

  int opA = aop & OPMASK_X;
  int opB = bop & OPMASK_X;

  if((opA | opB) == 0) return; // Only nops, no need to do anything.

  REGISTER argA, argB;  // In case of the argument operation
  argA.metadata = MD_NONE;
  argA.val      = 0;
  argB.metadata = MD_NONE;
  argB.val      = 0;

  int argsSet = 0;

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
        argsSet = 1;
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
        argsSet = 1;
        break;
      }
    }else if(opA == 11){
      // ARGS
      q = a;
      r = b;
      argsSet = 1;
    }

    if((q.metadata & MD_MASK_VALID) != MD_VOID){
      // Push register
    }

    if((r.metadata & MD_MASK_VALID) != MD_VOID){
      // Push register
    }
  }


  if(opB){
    REGISTER a, b;
    getBeltItems(belt, bop, &a, &b);

    REGISTER q, r;

    uint16_t md_a    =    a.metadata & MD_MASK_VALID;
    uint16_t md_b    =    b.metadata & MD_MASK_VALID;
    uint16_t md_arga = argA.metadata & MD_MASK_VALID;
    uint16_t md_argb = argB.metadata & MD_MASK_VALID;

    if((md_a == MD_VALID) && (md_b == MD_VALID)){
      // Both registers are valid

      switch(opB){
        case 0: // NOP
        break;

        case 1: // ADD
        q.metadata = MD_VALID;
        q.val = a.val + b.val;
        q.val += argsSet? (argA.val + argB.val) : 0;
        break;

        case 2: // SUB
        q.metadata = MD_VALID;
        q.val = a.val - b.val;
        q.val -= argsSet? (argA.val + argB.val) : 0;
        break;

        case 3: // AND
        q.metadata = MD_VALID;
        q.val = a.val & b.val;
        q.val &= argsSet? (argA.val & argB.val) : 0xFFFFFFFFFFFFFFFF;
        break;

        case 4: // OR
        q.metadata = MD_VALID;
        q.val = a.val | b.val;
        q.val |= argsSet? (argA.val | argB.val) : 0;
        break;

        case 5: // XOR
        q.metadata = MD_VALID;
        q.val = a.val ^ b.val;
        q.val ^= argsSet? (argA.val ^ argB.val) : 0;
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
      }
    }

    if((q.metadata & MD_MASK_VALID) != MD_VOID){
      // Push register
    }

    if((r.metadata & MD_MASK_VALID) != MD_VOID){
      // Push register
    }
  }


}
