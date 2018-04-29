#include "core.h"
#include "stdio.h"










void printDecode(uint16_t* ip){
  if(ip[0] | ip[1]){ // If not NOP
    uint32_t header = (((uint32_t)ip[0]) << 16) | ip[1];

    int index = 2;
    for(int slot = 0; slot < 32; slot++){

      if(slot < 8){
        if(slot ==  0) printf("Read Phase:\n");
        // Read Phase
        if((1 << slot) & header){
          // Decode Instruction
          index++;
        }
      }else if(slot < 16){
        if(slot ==  8) printf("Exec Phase:\n");
        // Exec Phase
        if((1 << slot) & header){
          // Decode Instruction
          index++;
        }
      }else if(slot < 24){
        if(slot == 16) printf("Call Phase:\n");
        // Call Phase
        if((1 << slot) & header){
          // Decode Instruction
          index++;
        }
      }else if(slot < 28){
        if(slot == 24) printf("Pick Phase:\n");
        // Pick Phase
        if((1 << slot) & header){
          // Decode Instruction
          index++;
        }
      }else{
        if(slot == 28) printf("Write Phase:\n");
        // Write Phase
        if((1 << slot) & header){
          // Decode Instruction
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
