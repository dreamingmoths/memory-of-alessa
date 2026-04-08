#ifndef MALL_B_01
#define MALL_B_01

#include "common.h"

typedef struct unk_struct01F6E180 {
    u_char pad[0xB0];
    int unkB0;
} unk_struct01F6E180;

typedef struct unk_struct {
    int unk0;
    float unk4;
    u_char pad[8];
    float unk10;
    float unk14;
    float unk18;
} unk_struct;

void func_0016D500(int, int, int*);
int func_00190A20(int);
void func_001C2290(int, float);
int func_001C2580(int);
extern int D_01F72640_mall_b_01;
extern int D_01F72918_mall_b_01;

void func_0016D0E0(int, int);
extern int D_01F72910_mall_b_01;
extern u_int D_1D31658;
int func_0012CFA0();
int func_0012CFC0();
int func_0012D080();
int func_0016BED0(int, int);
extern u_int D_1D31654;

unk_struct* func_00190AC0();

void func_01F6DF60_mall_b_01(void*);
void func_01F6E0F0_mall_b_01();

#endif
