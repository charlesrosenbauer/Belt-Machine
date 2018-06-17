#include "alu.h"
#include "belt.h"
#include "core.h"










REGISTER getMetaData_1Par(REGISTER a){
  REGISTER ret;
  for(int i = 0; i < 16; i++)
    ret.metadata[i] = a.metadata[i];
  ret.val.u64[0] = 0;
  ret.val.u64[1] = 0;
  return ret;
}










REGISTER getMetaData_2Par(REGISTER a, REGISTER b){
  REGISTER ret;
  /*
  if(((a.metadata & MD_MASK_VALID) == MD_VALID) && ((a.metadata & MD_MASK_VALID) == MD_VALID)){
    ret.metadata = MD_VALID;
  }else if(((a.metadata & MD_MASK_VALID) == MD_NONE) || ((a.metadata & MD_MASK_VALID) == MD_NONE)){
    ret.metadata = MD_NONE;
  }else if(((a.metadata & MD_MASK_VALID) == MD_NAR) || ((a.metadata & MD_MASK_VALID) == MD_NAR)){
    ret.metadata = MD_NAR;
  }else{
    ret.metadata = MD_VOID;
  }
  */
  ret.val.u64[0] = 0;
  ret.val.u64[1] = 0;
  return ret;
}










inline REGISTER correctWidth(REGISTER x){
  uint64_t mask = 0xFFFFFFFFFFFFFFFF;

  switch(x.vwidth){
    case 1:
      x.val.u64[0] &= 0x00000000000000FF;
      x.val.u64[1]  = 0;
    break;

    case 2:
      x.val.u64[0] &= 0x000000000000FFFF;
      x.val.u64[1]  = 0;
    break;

    case 4:
      x.val.u64[0] &= 0x00000000FFFFFFFF;
      x.val.u64[1]  = 0;
    break;

    case 8:
      x.val.u64[1]  = 0;
    break;

    case 16:
    break;

    default:
      x.vwidth = 1;
      x.swidth = 1;
      x.metadata[0] = MD_NAR;
    break;
  }

  return x;
}











inline REGISTER uaddOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
      switch(a.vwidth){
          ret.val.u8[ 0] = a.val.u8[ 0] + b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] + b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] + b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] + b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] + b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] + b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] + b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] + b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] + b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] + b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] + b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] + b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] + b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] + b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] + b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] + b.val.u8[15];
      }
    }break;
    case 2:{
          ret.val.u16[0] = a.val.u16[0] + b.val.u16[0];
          ret.val.u16[1] = a.val.u16[1] + b.val.u16[1];
          ret.val.u16[2] = a.val.u16[2] + b.val.u16[2];
          ret.val.u16[3] = a.val.u16[3] + b.val.u16[3];
          ret.val.u16[4] = a.val.u16[4] + b.val.u16[4];
          ret.val.u16[5] = a.val.u16[5] + b.val.u16[5];
          ret.val.u16[6] = a.val.u16[6] + b.val.u16[6];
          ret.val.u16[7] = a.val.u16[7] + b.val.u16[7];
      }break;
    case 4:{
        ret.val.u32[0] = a.val.u32[0] + b.val.u32[0];
        ret.val.u32[1] = a.val.u32[1] + b.val.u32[1];
        ret.val.u32[2] = a.val.u32[2] + b.val.u32[2];
        ret.val.u32[3] = a.val.u32[3] + b.val.u32[3];
    }break;
    case 8:{
        ret.val.u64[0] = a.val.u64[0] + b.val.u64[0];
        ret.val.u64[1] = a.val.u64[1] + b.val.u64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}









inline REGISTER usubOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
      switch(a.vwidth){
          ret.val.u8[ 0] = a.val.u8[ 0] - b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] - b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] - b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] - b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] - b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] - b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] - b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] - b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] - b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] - b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] - b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] - b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] - b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] - b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] - b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] - b.val.u8[15];
      }
    }break;
    case 2:{
          ret.val.u16[0] = a.val.u16[0] - b.val.u16[0];
          ret.val.u16[1] = a.val.u16[1] - b.val.u16[1];
          ret.val.u16[2] = a.val.u16[2] - b.val.u16[2];
          ret.val.u16[3] = a.val.u16[3] - b.val.u16[3];
          ret.val.u16[4] = a.val.u16[4] - b.val.u16[4];
          ret.val.u16[5] = a.val.u16[5] - b.val.u16[5];
          ret.val.u16[6] = a.val.u16[6] - b.val.u16[6];
          ret.val.u16[7] = a.val.u16[7] - b.val.u16[7];
      }break;
    case 4:{
        ret.val.u32[0] = a.val.u32[0] - b.val.u32[0];
        ret.val.u32[1] = a.val.u32[1] - b.val.u32[1];
        ret.val.u32[2] = a.val.u32[2] - b.val.u32[2];
        ret.val.u32[3] = a.val.u32[3] - b.val.u32[3];
    }break;
    case 8:{
        ret.val.i64[0] = a.val.i64[0] - b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] - b.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER saddOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
      switch(a.vwidth){
          ret.val.i8[ 0] = a.val.i8[ 0] + b.val.i8[ 0];
          ret.val.i8[ 1] = a.val.i8[ 1] + b.val.i8[ 1];
          ret.val.i8[ 2] = a.val.i8[ 2] + b.val.i8[ 2];
          ret.val.i8[ 3] = a.val.i8[ 3] + b.val.i8[ 3];
          ret.val.i8[ 4] = a.val.i8[ 4] + b.val.i8[ 4];
          ret.val.i8[ 5] = a.val.i8[ 5] + b.val.i8[ 5];
          ret.val.i8[ 6] = a.val.i8[ 6] + b.val.i8[ 6];
          ret.val.i8[ 7] = a.val.i8[ 7] + b.val.i8[ 7];
          ret.val.i8[ 8] = a.val.i8[ 8] + b.val.i8[ 8];
          ret.val.i8[ 9] = a.val.i8[ 9] + b.val.i8[ 9];
          ret.val.i8[10] = a.val.i8[10] + b.val.i8[10];
          ret.val.i8[11] = a.val.i8[11] + b.val.i8[11];
          ret.val.i8[12] = a.val.i8[12] + b.val.i8[12];
          ret.val.i8[13] = a.val.i8[13] + b.val.i8[13];
          ret.val.i8[14] = a.val.i8[14] + b.val.i8[14];
          ret.val.i8[15] = a.val.i8[15] + b.val.i8[15];
      }
    }break;
    case 2:{
          ret.val.i16[0] = a.val.i16[0] + b.val.i16[0];
          ret.val.i16[1] = a.val.i16[1] + b.val.i16[1];
          ret.val.i16[2] = a.val.i16[2] + b.val.i16[2];
          ret.val.i16[3] = a.val.i16[3] + b.val.i16[3];
          ret.val.i16[4] = a.val.i16[4] + b.val.i16[4];
          ret.val.i16[5] = a.val.i16[5] + b.val.i16[5];
          ret.val.i16[6] = a.val.i16[6] + b.val.i16[6];
          ret.val.i16[7] = a.val.i16[7] + b.val.i16[7];
      }break;
    case 4:{
        ret.val.i32[0] = a.val.i32[0] + b.val.i32[0];
        ret.val.i32[1] = a.val.i32[1] + b.val.i32[1];
        ret.val.i32[2] = a.val.i32[2] + b.val.i32[2];
        ret.val.i32[3] = a.val.i32[3] + b.val.i32[3];
    }break;
    case 8:{
        ret.val.i64[0] = a.val.i64[0] + b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] + b.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}









inline REGISTER isubOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
      switch(a.vwidth){
          ret.val.u8[ 0] = a.val.u8[ 0] - b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] - b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] - b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] - b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] - b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] - b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] - b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] - b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] - b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] - b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] - b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] - b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] - b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] - b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] - b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] - b.val.u8[15];
      }
    }break;
    case 2:{
          ret.val.i16[0] = a.val.i16[0] - b.val.i16[0];
          ret.val.i16[1] = a.val.i16[1] - b.val.i16[1];
          ret.val.i16[2] = a.val.i16[2] - b.val.i16[2];
          ret.val.i16[3] = a.val.i16[3] - b.val.i16[3];
          ret.val.i16[4] = a.val.i16[4] - b.val.i16[4];
          ret.val.i16[5] = a.val.i16[5] - b.val.i16[5];
          ret.val.i16[6] = a.val.i16[6] - b.val.i16[6];
          ret.val.i16[7] = a.val.i16[7] - b.val.i16[7];
      }break;
    case 4:{
        ret.val.i32[0] = a.val.i32[0] - b.val.i32[0];
        ret.val.i32[1] = a.val.i32[1] - b.val.i32[1];
        ret.val.i32[2] = a.val.i32[2] - b.val.i32[2];
        ret.val.i32[3] = a.val.i32[3] - b.val.i32[3];
    }break;
    case 8:{
        ret.val.u64[0] = a.val.u64[0] - b.val.u64[0];
        ret.val.u64[1] = a.val.u64[1] - b.val.u64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










/*
  @FIX : This needs to be adapted to better take into account None and Invalid values.
*/
void aluOp(BELTCORE* core, int delIndex, OPCODE aop, OPCODE bop){

  int opA = aop & OPMASK_X;
  int opB = bop & OPMASK_X;

  if((opA | opB) == 0) return; // Only nops, no need to do anything.

  REGISTER argA, argB;  // In case of the argument operation
  argA.metadata[0] = MD_NONE;
  argA.swidth      = 1;
  argA.vwidth      = 1;
  argB.metadata[0] = MD_NONE;
  argB.swidth      = 1;
  argB.vwidth      = 1;

  int argsSet = 0;

  if(opA){
    switch(opA){
      case IADD_OP:{

      }break;

      case ISUB_OP:{

      }break;

      case UADD_OP:{

      }break;

      case USUB_OP:{

      }break;
    }
  }

  if(opB){

  }


}
