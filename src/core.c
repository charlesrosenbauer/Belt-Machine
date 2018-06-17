#include "core.h"
#include "stdio.h"
#include "alu.h"









inline void printOp_1IMM(uint16_t ins, char* opsym, char asym){
  int a = ins & 0x3FF;
  //int op= ins >> 10;
  printf("  %s %c%i\n", opsym, asym, a);
}

inline void printOp_1Par(uint16_t ins, char* opsym, char asym){
  int a = ins & 0x1F;
  //int op= ins >> 10;
  printf("  %s %c%i\n", opsym, asym, a);
}

inline void printOp_2Par(uint16_t ins, char* opsym, char asym, char bsym){
  int a = ins & 0x1F;
  int b = (ins >> 5) & 0x1F;
  //int op= ins >> 10;
  printf("  %s %c%i %c%i\n", opsym, asym, a, bsym, b);
}

inline void printOp_3Par(uint16_t ins, char* opsym, char asym, char bsym, char csym){
  int a = ins & 0x1F;
  int b = (ins >>  5) & 0x1F;
  int c = (ins >> 10) & 0x1F;
  //int op= ins >> 15;
  printf("  %s %c%i %c%i %c%i\n", opsym, asym, a, bsym, b, csym, c);
}










void addOp_1Par(uint16_t* program, int* index, int op, int a){
  uint16_t ins = (op << 10) | (a & 0x3FF);
  program[*index] = ins;
  (*index) += 1;
}










void addOp_2Par(uint16_t* program, int* index, int op, int a, int b){
  uint16_t ins = (op << 10) | ((b & 0x1F) << 5) | (a & 0x1F);
  program[*index] = ins;
  (*index) += 1;
}










void addOp_3Par(uint16_t* program, int* index, int op, int a, int b, int c){
  uint16_t ins = (op << 15) | ((c & 0x1F) << 10) | ((b & 0x1F) << 5) | (a & 0x1F);
  program[*index] = ins;
  (*index) += 1;
}










void addInsHead(uint16_t* program, int* index, uint32_t headercode){
  uint16_t header0 = headercode >> 16;
  uint16_t header1 = headercode & 0xFFFF;

  program[*index  ] = header0;
  program[*index+1] = header1;
  (*index) += 2;
}










uint16_t* printDecode(uint16_t* ip){

  int fail = 0;
  int index = 2;

  if(ip[0] | ip[1]){ // If not NOP
    uint32_t header = (((uint32_t)ip[0]) << 16) | ip[1];

    printf("\n\n%x\n", header);

    const uint32_t slotmask = 0x80000000;


    for(int slot = 0; slot < 32; slot++){

      if(slot < 8){
        if(slot ==  0) printf("Read Phase:\n");
        // Read Phase
        if((slotmask >> slot) & header){
          // Decode Instruction
          switch(ip[index] >> 10){
            case RET__OP : printOp_1Par(ip[index], "RET", 'r'); break;
            case IMM__OP : printOp_1IMM(ip[index], "IMM", 'x'); break;
            case NIL__OP : printOp_1Par(ip[index], "NIL", 'v'); break;
            case NAR__OP : printOp_1Par(ip[index], "NAR", 'v'); break;
            case ZER__OP : printOp_1Par(ip[index], "ZER", 'v'); break;
            case ONE__OP : printOp_1Par(ip[index], "ONE", 'v'); break;
            case FILL_OP : printOp_2Par(ip[index], "FILL", 's', 'v'); break;

            default : printf("  INVALID\n");
          }
          index++;
        }
      }else if(slot < 16){
        if(slot ==  8) printf("Exec Phase:\n");
        // Exec Phase
        if((slotmask >> slot) & header){
          // Decode Instruction
          switch(ip[index] >> 10){
            case IADD_OP : printOp_2Par(ip[index], "IADD", 'b', 'b'); break;
            case ISUB_OP : printOp_2Par(ip[index], "ISUB", 'b', 'b'); break;
            case IMUL_OP : printOp_2Par(ip[index], "IMUL", 'b', 'b'); break;
            case IDIV_OP : printOp_2Par(ip[index], "IDIV", 'b', 'b'); break;
            case UADD_OP : printOp_2Par(ip[index], "UADD", 'b', 'b'); break;
            case USUB_OP : printOp_2Par(ip[index], "USUB", 'b', 'b'); break;
            case UMUL_OP : printOp_2Par(ip[index], "UMUL", 'b', 'b'); break;
            case UDIV_OP : printOp_2Par(ip[index], "UDIV", 'b', 'b'); break;
            case FADD_OP : printOp_2Par(ip[index], "FADD", 'b', 'b'); break;
            case FSUB_OP : printOp_2Par(ip[index], "FSUB", 'b', 'b'); break;
            case FMUL_OP : printOp_2Par(ip[index], "FMUL", 'b', 'b'); break;
            case FDIV_OP : printOp_2Par(ip[index], "FDIV", 'b', 'b'); break;
            case AND__OP : printOp_2Par(ip[index], "AND" , 'b', 'b'); break;
            case OR___OP : printOp_2Par(ip[index], "OR"  , 'b', 'b'); break;
            case XOR__OP : printOp_2Par(ip[index], "XOR" , 'b', 'b'); break;
            case NOT__OP : printOp_2Par(ip[index], "NOT" , 'b', 'b'); break;
            case SHL__OP : printOp_2Par(ip[index], "SHL" , 'b', 'b'); break;
            case SHR__OP : printOp_2Par(ip[index], "SHR" , 'b', 'b'); break;
            case INC__OP : printOp_1Par(ip[index], "INC" , 'b'     ); break;
            case DEC__OP : printOp_1Par(ip[index], "DEC" , 'b'     ); break;
            case ILS__OP : printOp_2Par(ip[index], "ILS" , 'b', 'b'); break;
            case IGT__OP : printOp_2Par(ip[index], "IGT" , 'b', 'b'); break;
            case IZR__OP : printOp_2Par(ip[index], "IZR" , 'b', 'b'); break;
            case IEQ__OP : printOp_2Par(ip[index], "IEQ" , 'b', 'b'); break;
            case CNIL_OP : printOp_2Par(ip[index], "CNIL", 'b', 'b'); break;
            case FLS__OP : printOp_2Par(ip[index], "FLS" , 'b', 'b'); break;
            case FGT__OP : printOp_2Par(ip[index], "FGT" , 'b', 'b'); break;
            case FZR__OP : printOp_2Par(ip[index], "FZR" , 'b', 'b'); break;
            case FEQ__OP : printOp_2Par(ip[index], "FEQ" , 'b', 'b'); break;
            case CNAR_OP : printOp_2Par(ip[index], "CNAR", 'b', 'b'); break;
            case PCNT_OP : printOp_2Par(ip[index], "PCNT", 'b', 'b'); break;
            case ARGX_OP : printOp_2Par(ip[index], "ARGX", 'b', 'b'); break;
            case FMAS_OP : printOp_2Par(ip[index], "FMAS", 'b', 'b'); break;
            case IADS_OP : printOp_2Par(ip[index], "IADS", 'b', 'b'); break;
            case FADS_OP : printOp_2Par(ip[index], "FADS", 'b', 'b'); break;
            case FMA__OP : printOp_1Par(ip[index], "FMA" , 'b'     ); break;
            case SMRI_OP : printOp_1Par(ip[index], "SMRI", 'b'     ); break;
            case SMRE_OP : printOp_1Par(ip[index], "SMRE", 'b'     ); break;
            case REMN_OP : printOp_1Par(ip[index], "REMN", 'b'     ); break;
            case FIX__OP : printOp_1Par(ip[index], "FIX" , 'b'     ); break;
            case FLT__OP : printOp_1Par(ip[index], "FLT" , 'b'     ); break;
            case WIDE_OP : printOp_1Par(ip[index], "WIDE", 'b'     ); break;
            case NARW_OP : printOp_1Par(ip[index], "NARW", 'b'     ); break;
            case SUMV_OP : printOp_1Par(ip[index], "SUMV", 'b'     ); break;

            default : printf("  INVALID\n");
          }
          index++;
        }
      }else if(slot < 24){
        if(slot == 16) printf("Call Phase:\n");
        // Call Phase
        if((slotmask >> slot) & header){
          // Decode Instruction
          switch(ip[index] >> 10){
            case ARGC_OP : printOp_2Par(ip[index], "ARGC", 'b', 'b'); break;
            case CALL_OP : printOp_2Par(ip[index], "CALL", 'b', 'b'); break;

            default : printf("  INVALID\n");
          }
          index++;
        }
      }else if(slot < 28){
        if(slot == 24) printf("Pick Phase:\n");
        // Pick Phase
        if((slotmask >> slot) & header){
          // Decode Instruction
          switch(ip[index] >> 15){
            case PICK_OP : printOp_3Par(ip[index], "PICK", 'b', 'b', 'b'); break;
            case RECR_OP : printOp_3Par(ip[index], "RECR", 'b', 'b', 'b'); break;

            default : printf("  INVALID\n");
          }
          index++;
        }
      }else{
        if(slot == 28) printf("Write Phase:\n");
        // Write Phase
        if((slotmask >> slot) & header){
          // Decode Instruction
          switch(ip[index] >> 10){
            case STR__OP : printOp_2Par(ip[index], "STR" , 'r', 'b'); break;
            case LOD__OP : printOp_2Par(ip[index], "LOD" , 'b', 'v'); break;
            case BR___OP : printOp_1Par(ip[index], "BR"  , 'b'     ); break;
            case BRT__OP : printOp_2Par(ip[index], "BRT" , 'b', 'b'); break;
            case BRF__OP : printOp_2Par(ip[index], "BRF" , 'b', 'b'); break;
            case SPIL_OP : printOp_2Par(ip[index], "SPIL", 's', 'b'); break;
            case ROTS_OP : printOp_1Par(ip[index], "ROTS", 'b'     ); break;
            case ALLC_OP : printOp_1Par(ip[index], "ALLC", 'b'     ); break;
            case FREE_OP : printOp_1Par(ip[index], "FREE", 'b'     ); break;
            case ALCS_OP : printOp_1Par(ip[index], "ALCS", 'b'     ); break;
            case EXIT_OP : printf("  EXIT\n"); fail = 1;              break;

            default : printf("  INVALID\n");
          }
          index++;
        }
      }

    }
  }else{
    printf("NOP\n");
  }

  return fail? NULL : (ip + index);
}










void coreStep(BELTCORE* core){

}
