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
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
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
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
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









inline REGISTER umulOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
          ret.val.u8[ 0] = a.val.u8[ 0] * b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] * b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] * b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] * b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] * b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] * b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] * b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] * b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] * b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] * b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] * b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] * b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] * b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] * b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] * b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] * b.val.u8[15];
    }break;
    case 2:{
          ret.val.u16[0] = a.val.u16[0] * b.val.u16[0];
          ret.val.u16[1] = a.val.u16[1] * b.val.u16[1];
          ret.val.u16[2] = a.val.u16[2] * b.val.u16[2];
          ret.val.u16[3] = a.val.u16[3] * b.val.u16[3];
          ret.val.u16[4] = a.val.u16[4] * b.val.u16[4];
          ret.val.u16[5] = a.val.u16[5] * b.val.u16[5];
          ret.val.u16[6] = a.val.u16[6] * b.val.u16[6];
          ret.val.u16[7] = a.val.u16[7] * b.val.u16[7];
      }break;
    case 4:{
        ret.val.u32[0] = a.val.u32[0] * b.val.u32[0];
        ret.val.u32[1] = a.val.u32[1] * b.val.u32[1];
        ret.val.u32[2] = a.val.u32[2] * b.val.u32[2];
        ret.val.u32[3] = a.val.u32[3] * b.val.u32[3];
    }break;
    case 8:{
        ret.val.i64[0] = a.val.i64[0] * b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] * b.val.i64[1];
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
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
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









inline REGISTER ssubOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
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










inline REGISTER smulOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:{
          ret.val.u8[ 0] = a.val.u8[ 0] * b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] * b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] * b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] * b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] * b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] * b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] * b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] * b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] * b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] * b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] * b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] * b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] * b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] * b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] * b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] * b.val.u8[15];
    }break;
    case 2:{
          ret.val.i16[0] = a.val.i16[0] * b.val.i16[0];
          ret.val.i16[1] = a.val.i16[1] * b.val.i16[1];
          ret.val.i16[2] = a.val.i16[2] * b.val.i16[2];
          ret.val.i16[3] = a.val.i16[3] * b.val.i16[3];
          ret.val.i16[4] = a.val.i16[4] * b.val.i16[4];
          ret.val.i16[5] = a.val.i16[5] * b.val.i16[5];
          ret.val.i16[6] = a.val.i16[6] * b.val.i16[6];
          ret.val.i16[7] = a.val.i16[7] * b.val.i16[7];
      }break;
    case 4:{
        ret.val.i32[0] = a.val.i32[0] * b.val.i32[0];
        ret.val.i32[1] = a.val.i32[1] * b.val.i32[1];
        ret.val.i32[2] = a.val.i32[2] * b.val.i32[2];
        ret.val.i32[3] = a.val.i32[3] * b.val.i32[3];
    }break;
    case 8:{
        ret.val.u64[0] = a.val.u64[0] * b.val.u64[0];
        ret.val.u64[1] = a.val.u64[1] * b.val.u64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER xorOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:
    case 2:
    case 4:
    case 8:{
        // Vector stuff is simplified here, because every bit is independent
        ret.val.i64[0] = a.val.i64[0] ^ b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] ^ b.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER andOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:
    case 2:
    case 4:
    case 8:{
        // Vector stuff is simplified here, because every bit is independent
        ret.val.i64[0] = a.val.i64[0] & b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] & b.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER orOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:
    case 2:
    case 4:
    case 8:{
        // Vector stuff is simplified here, because every bit is independent
        ret.val.i64[0] = a.val.i64[0] | b.val.i64[0];
        ret.val.i64[1] = a.val.i64[1] | b.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER notOp(REGISTER a){
  REGISTER ret;
  ret.swidth = a.swidth;
  ret.vwidth = a.vwidth;
  switch(a.swidth){
    case 1:
    case 2:
    case 4:
    case 8:{
        // Vector stuff is simplified here, because every bit is independent
        ret.val.i64[0] = ~a.val.i64[0];
        ret.val.i64[1] = ~a.val.i64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER shlOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
          ret.val.u8[ 0] = a.val.u8[ 0] << b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] << b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] << b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] << b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] << b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] << b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] << b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] << b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] << b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] << b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] << b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] << b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] << b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] << b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] << b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] << b.val.u8[15];
    }break;
    case 2:{
          ret.val.i16[0] = a.val.i16[0] << b.val.i16[0];
          ret.val.i16[1] = a.val.i16[1] << b.val.i16[1];
          ret.val.i16[2] = a.val.i16[2] << b.val.i16[2];
          ret.val.i16[3] = a.val.i16[3] << b.val.i16[3];
          ret.val.i16[4] = a.val.i16[4] << b.val.i16[4];
          ret.val.i16[5] = a.val.i16[5] << b.val.i16[5];
          ret.val.i16[6] = a.val.i16[6] << b.val.i16[6];
          ret.val.i16[7] = a.val.i16[7] << b.val.i16[7];
      }break;
    case 4:{
        ret.val.i32[0] = a.val.i32[0] << b.val.i32[0];
        ret.val.i32[1] = a.val.i32[1] << b.val.i32[1];
        ret.val.i32[2] = a.val.i32[2] << b.val.i32[2];
        ret.val.i32[3] = a.val.i32[3] << b.val.i32[3];
    }break;
    case 8:{
        ret.val.u64[0] = a.val.u64[0] << b.val.u64[0];
        ret.val.u64[1] = a.val.u64[1] << b.val.u64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}










inline REGISTER shrOp(REGISTER a, REGISTER b){
  REGISTER ret;
  if((a.swidth != b.swidth) || (a.vwidth != b.vwidth)){
    ret.swidth = 1;
    ret.vwidth = 1;
    ret.metadata[0] = MD_NAR;
    return ret;
  }
  switch(a.swidth){
    case 1:{
          ret.val.u8[ 0] = a.val.u8[ 0] >> b.val.u8[ 0];
          ret.val.u8[ 1] = a.val.u8[ 1] >> b.val.u8[ 1];
          ret.val.u8[ 2] = a.val.u8[ 2] >> b.val.u8[ 2];
          ret.val.u8[ 3] = a.val.u8[ 3] >> b.val.u8[ 3];
          ret.val.u8[ 4] = a.val.u8[ 4] >> b.val.u8[ 4];
          ret.val.u8[ 5] = a.val.u8[ 5] >> b.val.u8[ 5];
          ret.val.u8[ 6] = a.val.u8[ 6] >> b.val.u8[ 6];
          ret.val.u8[ 7] = a.val.u8[ 7] >> b.val.u8[ 7];
          ret.val.u8[ 8] = a.val.u8[ 8] >> b.val.u8[ 8];
          ret.val.u8[ 9] = a.val.u8[ 9] >> b.val.u8[ 9];
          ret.val.u8[10] = a.val.u8[10] >> b.val.u8[10];
          ret.val.u8[11] = a.val.u8[11] >> b.val.u8[11];
          ret.val.u8[12] = a.val.u8[12] >> b.val.u8[12];
          ret.val.u8[13] = a.val.u8[13] >> b.val.u8[13];
          ret.val.u8[14] = a.val.u8[14] >> b.val.u8[14];
          ret.val.u8[15] = a.val.u8[15] >> b.val.u8[15];
    }break;
    case 2:{
          ret.val.i16[0] = a.val.i16[0] >> b.val.i16[0];
          ret.val.i16[1] = a.val.i16[1] >> b.val.i16[1];
          ret.val.i16[2] = a.val.i16[2] >> b.val.i16[2];
          ret.val.i16[3] = a.val.i16[3] >> b.val.i16[3];
          ret.val.i16[4] = a.val.i16[4] >> b.val.i16[4];
          ret.val.i16[5] = a.val.i16[5] >> b.val.i16[5];
          ret.val.i16[6] = a.val.i16[6] >> b.val.i16[6];
          ret.val.i16[7] = a.val.i16[7] >> b.val.i16[7];
      }break;
    case 4:{
        ret.val.i32[0] = a.val.i32[0] >> b.val.i32[0];
        ret.val.i32[1] = a.val.i32[1] >> b.val.i32[1];
        ret.val.i32[2] = a.val.i32[2] >> b.val.i32[2];
        ret.val.i32[3] = a.val.i32[3] >> b.val.i32[3];
    }break;
    case 8:{
        ret.val.u64[0] = a.val.u64[0] >> b.val.u64[0];
        ret.val.u64[1] = a.val.u64[1] >> b.val.u64[1];
    }break;
    default:{
        ret.vwidth = 1;
        ret.swidth = 1;
        ret.metadata[0] = MD_NAR;
    }break;
  }
  return correctWidth(ret);
}









inline void insertBeltcore(REGISTER x, BELTCORE* core, int latency, int slot){

  DELAYSLOT d;
  d.r = x;
  d.mode = DSM_REGISTER;

  int del = (core->delays.timeIndex + latency) % 33;

  core->delays.activeMask[del] |= (1 << slot);
  core->delays.slots[slot][del] = d;
}










/*
  @FIX : This needs to be adapted to better take into account None and Invalid values.
*/
int aluOp(BELTCORE* core, int slot, OPCODE op, REGISTER* argA, REGISTER* argB){

  int opcode = op & OPMASK_X;

  if(opcode == 0) return 0; // Only nops, no need to do anything.

  REGISTER ra, rb;

  getBeltItems(&(core->belt), opcode, &ra, &rb);

  int argsSet = 0;

  if(opcode){
    switch(opcode){
      case IADD_OP:{
        insertBeltcore(saddOp(ra, rb), core, 1, slot);
      }break;

      case ISUB_OP:{
        insertBeltcore(ssubOp(ra, rb), core, 1, slot);
      }break;

      case IMUL_OP:{
        insertBeltcore(smulOp(ra, rb), core, 3, slot);
      }break;


      case UADD_OP:{
        insertBeltcore(uaddOp(ra, rb), core, 1, slot);
      }break;

      case USUB_OP:{
        insertBeltcore(usubOp(ra, rb), core, 1, slot);
      }break;

      case UMUL_OP:{
        insertBeltcore(umulOp(ra, rb), core, 3, slot);
      }break;


      case AND__OP:{
        insertBeltcore(andOp(ra, rb), core, 1, slot);
      }break;

      case XOR__OP:{
        insertBeltcore(xorOp(ra, rb), core, 1, slot);
      }break;

      case OR___OP:{
        insertBeltcore(orOp(ra, rb), core, 1, slot);
      }break;

      case NOT__OP:{
        insertBeltcore(notOp(ra), core, 1, slot);
      }break;

      case SHL__OP:{
        insertBeltcore(shlOp(ra, rb), core, 1, slot);
      }break;

      case SHR__OP:{
        insertBeltcore(shrOp(ra, rb), core, 1, slot);
      }break;

      case ARGX_OP:{
        if((slot%2)==0){
          *argA = ra;
          *argB = rb;
        }else{
          return -1;
        }
      }break;
    }
  }


  return 0;
}
