#include "core.h"
#include "stdio.h"









// Temporary techniques
inline void printOp_2Par(uint16_t ins){
  int a = ins & 0x1F;
  int b = (ins >> 5) & 0x1F;
  int op= ins >> 10;
  printf("  %i b%i b%i\n", op, a, b);
}

inline void printOp_3Par(uint16_t ins){
  int a = ins & 0x1F;
  int b = (ins >>  5) & 0x1F;
  int c = (ins >> 10) & 0x1F;
  int op= ins >> 15;
  printf("  %i b%i b%i b%i\n", op, a, b, c);
}










void printDecode(uint16_t* ip){
  if(ip[0] | ip[1]){ // If not NOP
    uint32_t header = (((uint32_t)ip[0]) << 16) | ip[1];

    printf("%x\n\n", header);

    int index = 2;
    for(int slot = 0; slot < 32; slot++){

      if(slot < 8){
        if(slot ==  0) printf("Read Phase:\n");
        // Read Phase
        if((1 << slot) & header){
          // Decode Instruction
          printOp_2Par(ip[index]);
          index++;
        }
      }else if(slot < 16){
        if(slot ==  8) printf("Exec Phase:\n");
        // Exec Phase
        if((1 << slot) & header){
          // Decode Instruction
          printOp_2Par(ip[index]);
          index++;
        }
      }else if(slot < 24){
        if(slot == 16) printf("Call Phase:\n");
        // Call Phase
        if((1 << slot) & header){
          // Decode Instruction
          printOp_2Par(ip[index]);
          index++;
        }
      }else if(slot < 28){
        if(slot == 24) printf("Pick Phase:\n");
        // Pick Phase
        if((1 << slot) & header){
          // Decode Instruction
          printOp_3Par(ip[index]);
          index++;
        }
      }else{
        if(slot == 28) printf("Write Phase:\n");
        // Write Phase
        if((1 << slot) & header){
          // Decode Instruction
          printOp_2Par(ip[index]);
          index++;
        }
      }

    }
  }else{
    printf("NOP\n");
  }
}










void coreStep(BELTCORE* core){

}
