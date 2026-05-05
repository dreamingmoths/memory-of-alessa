#ifndef SUBWAY_01_H
#define SUBWAY_01_H

#include "common.h"
#include "Chacter/m3_sc.h"

typedef struct
{
    float unk0;
    int*  unk4;
} D_01F70400_struct;

typedef struct
{
    float unk0;
    int*  unk4;
} D_01F70520_struct;

typedef struct
{
    /* 0x0 */   short unk0;
    /* 0x2 */   short unk2;
    /* 0x4 */   int   unk4;
    /* 0x8 */   int   unk8;
    /* 0xC */   short unkC;
    /* 0xE */   short unkE;
    /* 0x10 */  short unk10;
    /* 0x12 */  short unk12;
    /* 0x14 */  short unk14;
    /* 0x16 */  short unk16;
} D_01F6F7D0_struct;

typedef struct
{
    /* 0x0 */   int   unk0;
    /* 0x4 */   short unk4;
    /* 0x6 */   short unk6;
    /* 0x8 */   int   unk8[2];
    /* 0x10 */  float unk10;
    /* 0x14 */  float unk14;
    /* 0x18 */  float unk18;
    /* 0x1C */  int   unk1C[2];
    /* 0x24 */  float unk24;
    /* 0x28 */  int   unk28[2];
    /* 0x30 */  int   unk30;
    /* 0x34 */  int   unk34;
    /* 0x38 */  int   unk38[2];
} func_0016A080_struct;

int func_00190A20(int);
int func_0016CED0(int, int, int *);
short RoomName(void);
void func_001908A0(float *, float *);
SubCharacter* shCharacterGetSubCharacter(int, short);
void func_001DC9E0(SubCharacter *, int);
void func_001C2290(int, float);
void SeCall(float, float, int);
void func_0013D250(int, int *, float);
int func_0016C540(int *, int *);
float func_001643C0(void);
int func_001646C0(void);
int func_00151150(int, int);
void func_0019A940(void);
int func_0019A9B0(float);
void func_00190C40(void);
void func_0013D280(int);
float func_00190880(void);
void func_001BF720(int);
int func_0016E0F0(void);
void func_0016E400(int, int);
int func_0016B4E0(D_01F6F7D0_struct *);
void shQzero(func_0016A080_struct *, int);
void func_0016A080(func_0016A080_struct *);
void clAddDynamicWall(int *);
int func_001909B0(void);
void clAddDynamicFloor(int *);
void func_001DD650(SubCharacter *, int, sceVu0FVECTOR *, sceVu0FVECTOR *);
void func_001DD6F0(SubCharacter *, int, sceVu0FVECTOR *, sceVu0FVECTOR *);
void func_001E1F20(sceVu0FVECTOR *);
void func_001C0EB0(void (*)(), int, int);
void func_001C0EE0(int);
float shGetDT(void);

int func_01F6D680_subway_01(void);
int func_01F6D690_subway_01(void);
int func_01F6D720_subway_01(void);
int func_01F6DAA0_subway_01(void);
int func_01F6DBE0_subway_01(void);
int func_01F6DD70_subway_01(void);
void func_01F6DF90_subway_01(void);
void func_01F6E100_subway_01(void);
void func_01F6E270_subway_01(void);
void func_01F6E2D0_subway_01(void);
void func_01F6E320_subway_01(void);
void func_01F6E380_subway_01(void);
void func_01F6E7C0_subway_01(void);
void func_01F6E7D0_subway_01(void);
void func_01F6E900_subway_01(Q *, int *, Q *, int *, int *);
void func_01F6E960_subway_01(void);

extern int D_01F70700_subway_01;
extern int D_01F70370_subway_01;
extern int D_01F70380_subway_01;
extern int D_01F70384_subway_01;
extern int D_01F70180_subway_01;
extern int D_01F703E0_subway_01;
extern int D_01F70140_subway_01;
extern int D_01F70420_subway_01;
extern int D_01F70480_subway_01;
extern int D_01F70708_subway_01;
extern u_int D_1D31648;
extern int D_01F704A0_subway_01;
extern int D_01F70500_subway_01;
extern u_int D_1D3165C;
extern int D_01F70710_subway_01;
extern int D_01F705C0_subway_01;
extern int D_01F70620_subway_01;
extern int D_01F70220_subway_01;
extern u_int D_1D3177C;
extern int D_01F70640_subway_01;
extern int D_01F70650_subway_01;
extern int D_01F70000_subway_01;
extern int D_01F6FEC0_subway_01;
extern int D_01F6FF60_subway_01;
extern int D_01F6FE20_subway_01;
extern int D_01F6FD80_subway_01;
extern int D_01F6FB00_subway_01;
extern int D_01F6FCE0_subway_01;
extern int D_01F6F9C0_subway_01;
extern int D_01F6FA60_subway_01;
extern int D_01F70718_subway_01;
extern int D_01F70720_subway_01;
extern float D_01F70730_subway_01;
extern u_int D_1D31644;
extern float D_01F70728_subway_01;

extern D_01F70400_struct* D_01F70740_subway_01;
extern D_01F70400_struct D_01F70400_subway_01;

extern D_01F70520_struct* D_01F70738_subway_01;
extern D_01F70520_struct D_01F70520_subway_01;

extern D_01F6F7D0_struct D_01F6F7D0_subway_01;

extern Q D_01F70660_subway_01;
extern Q D_01F70670_subway_01;

#endif