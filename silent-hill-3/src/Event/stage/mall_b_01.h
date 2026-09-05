#ifndef MALL_B_01
#define MALL_B_01

#include "common.h"
#include "sce/libvu0.h"

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

int SeCall(int, float, float);
int func_0016CB70(void);
int func_0016C1C0(int);
extern u_int D_01D31640;
extern u_int D_1D31704;

int GetActionLevel(void);
extern int D_01F727B0_mall_b_01;

void func_001E0130(float*, float*, float*, int);

extern int D_01F719C0_mall_b_01;
extern int D_01F728C0_mall_b_01;
extern int D_01F728C8_mall_b_01;

int func_0016D240(float, float, int, float (*)[4], int, int);
int RoomName(void);
void func_0016CC50(int, int, sceVu0FMATRIX*, sceVu0FVECTOR*);
void func_0016CBD0(sceVu0FMATRIX*[], sceVu0FMATRIX*[], int);
void func_00196770();
void func_00300E70();
void func_003010F0();
void func_00311410();
extern int D_01F72890_mall_b_01;
extern sceVu0FVECTOR D_01F728E0_mall_b_01;
extern int D_01F728F0_mall_b_01;

extern float D_01F72880_mall_b_01;
extern float D_01F72888_mall_b_01;
extern int D_01F728A8_mall_b_01;
extern int D_01F728B8_mall_b_01;
extern int D_01F728D8_mall_b_01;

#endif
