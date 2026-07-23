#ifndef MALL_B_02
#define MALL_B_02

#include "common.h"

typedef struct unk_01F6E770_mall_b_02_struct {
    float unk0;
    int* unk4; // not so sure about this
} unk_01F6E770_mall_b_02_struct;
/*
dlabel D_01F6E770_mall_b_02
     1170 01F6E770 00804A44  .word 0x444A8000
     1174 01F6E774 A0E5F601  .word D_01F6E5A0_mall_b_02
     1178 01F6E778 00809844  .word 0x44988000
     117C 01F6E77C 00E6F601  .word D_01F6E600_mall_b_02
     1180 01F6E780 0000BF44  .word 0x44BF0000
     1184 01F6E784 50E6F601  .word D_01F6E650_mall_b_02
     1188 01F6E788 0000D944  .word 0x44D90000
     118C 01F6E78C A0E6F601  .word D_01F6E6A0_mall_b_02
     1190 01F6E790 00000000  .word 0x00000000
     1194 01F6E794 00000000  .word 0x00000000
     1198 01F6E798 00000000  .word 0x00000000
     119C 01F6E79C 00000000  .word 0x00000000
enddlabel D_01F6E770_mall_b_02
*/

typedef struct unk_01F6E890_mall_b_02_struct {
    char pad00[0x4];
    int unk4;
    int unk8;
    int unkC;
    float unk10[3]; // or maybe 3 separete floats
} unk_01F6E890_mall_b_02_struct; 


// @todo: D_01D31640
extern u_int D_01D31640;
extern u_int D_1D31658;
extern u_int D_1D316AC;
extern u_int D_1D31708;
extern u_int D_1D31794;

#endif // MALL_B_02
