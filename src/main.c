#include "stdio.h"
#include "belt.h"
#include "memory.h"
#include "core.h"










int main(){
  RAM ram = initRAM(1048576);

  /*
    I have to be careful writing programs this way. The translation to uint16_t
    doesn't play nicely with endianess, and bytes tend to get shuffled around in
    the decode function. I need to find a better way to do this.
  */
  char* program = "\x00\x01\x00\x00\xFF\xFF";

  printDecode((uint16_t*)program);
}
