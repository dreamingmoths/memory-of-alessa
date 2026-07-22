#ifndef MALL_B_02
#define MALL_B_02

#include "common.h"

typedef struct unk_01F6E890_mall_b_02_struct {
    char pad00[0x4];
    int unk4;
    int unk8;
    int unkC;
    float unk10[3]; // or maybe 3 separete floats
} unk_01F6E890_mall_b_02_struct; 

extern void shQzero(void*, int);
extern void func_001603E0(int, int);
extern float shGetDT(void);
extern int func_001C2580(int);
extern void func_0012EA40(void);
extern void func_0013D280(int);
extern int func_00190240(void); // @note: this comes from m3_play_event, might be worth it check what this is
extern void func_001C2290(int, float);
extern void func_001EC5C0(int);
extern void func_001EC5E0(int); 
extern void func_001EC610(int);
extern void func_001EC630(int);
    
extern u_int D_1D31658;
extern u_int D_1D316AC;

#endif // MALL_B_02
