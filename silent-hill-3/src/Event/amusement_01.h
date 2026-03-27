#ifndef AMUSEMENT_01_H
#define AMUSEMENT_01_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define DANNY_CHARA_ID 0x1043
#define DANNY_ID 0x171

#define BORLEY_HAUNTED_MANSION_DINING_ROOM  0xDB
#define BORLEY_HAUNTED_MANSION_DANNY_ROOM   0xDC
#define BORLEY_HAUNTED_MANSION_SPIKE_ROOM   0xDD
#define BORLEY_HAUNTED_MANSION_MAZE_1_ROOM  0xDE
#define BORLEY_HAUNTED_MANSION_MAZE_2_ROOM  0xDF

typedef struct Amusement01Work
{
    u_char unk_0x0[0x20];
    float x;      // 0x20
    float y;      // 0x24
    float z;      // 0x28
    float f_0x2c; // 0x2c
    float f_0x30; // 0x30
    float angle;  // 0x34
} Amusement01Work;

typedef struct Amusement01Pair {
    float start;
    float end;
} Amusement01Pair;

typedef union DWORD
{
    u_int u32[2];
    float fv[2];
} DWORD;

int func_01F6D680_amusement_01(void);

void func_001C0EB0(void (*)(u_long128 *, int *, u_long128 *, int *, int *), int, int);

void func_01F6DCB0_amusement_01();

void func_01F6DDC0_amusement_01();

void func_01F703B0_amusement_01(float, float);

extern float func_001643C0(void);
extern int func_0016C540(float *, float *);
extern void func_001C2290(int, float);
extern void func_0018FE60(u_long128 *);
extern void func_0016CF70(void);
extern int func_0016CF80(int, int, int *);
extern SubCharacter *shCharacterGetSubCharacter(int, short);
extern u_char GetActionLevel(void);
extern int D_01F713D0_amusement_01;
extern u_int D_1D3169C;

extern int SeCall(float, float, int);
extern float shAngleRegulate(float);
extern float shGetDT(void);
extern float shSinF(float);
extern int RoomName(void);
extern void func_001C2A60(int, float);
extern void func_0016C3C0(void);
extern int func_0016C1C0(int);
extern void func_00190A20(int a0);
extern void ItemGet(u_int);
extern int func_00190C00(void);
extern void func_00317420(u_int);
extern void func_00317490(int, float);
extern void func_003174B0(float);
extern void func_001602D0(int, int, int, float);
extern int func_00160520(int);
extern void func_00160AF0(int);
extern void func_0019A940(void);
extern int func_0019A9B0(float a0);
extern int func_0015DCD0(float, float, int, float *, int, int);
extern void func_001C2A70(int, float);
extern void func_001DC9E0(SubCharacter *, int);
extern int func_001DD9F0(SubCharacter *);
extern void func_001433A0(SubCharacter *, int, int);
extern void func_0016D8F0(int);
extern void func_0013D250(int, int*, float);
extern void func_0013D280(int);
extern int func_0016CB70(void);
extern void func_0016E400(int, int);
extern int func_0016E650(int);
extern int func_001C2580(int);

extern int func_0016BED0(int, int);
extern int GetRiddleLevel(void);
extern int func_001C2580(int);

extern int func_0015DFC0(int, int);
extern void func_001BE4B0(int);
extern void func_001C2A80(int, sceVu0FMATRIX*);
extern int func_00190950(void);
extern void func_001C2AE0(int, sceVu0FMATRIX*);
extern void func_001C2B80(int, float*);
extern void func_001E0130(float*, float*, float*, int);
extern int func_01F6E220_amusement_01(void);
extern int func_01F70750_amusement_01(void);

extern void func_0016CA80(int);
extern void func_0016E150(int);
extern void func_001C0EE0(int a0);
extern void func_001C7C80(u_long128*, u_long128*, u_long128*, int);
extern float shGetDT(void);
extern int func_0016E0F0(void);

extern void shRotMatrixY(float (* m0)[4] /* r2 */, float (* m1)[4] /* r2 */, float);
extern void shRotMatrixX(float (* m0)[4] /* r2 */, float (* m1)[4] /* r2 */, float);
extern void shMulMatrix(float (* m0)[4] /* r2 */, float (* m1)[4] /* r2 */, float (* m2)[4] /* r2 */);


extern int D_01F74D00_amusement_01;
extern sceVu0FVECTOR D_01F74670_amusement_01;
extern sceVu0FVECTOR D_01F74690_amusement_01[];
extern int D_01F74D98_amusement_01;
extern int D_01F74CB0_amusement_01;
extern u_long128 D_01F74680_amusement_01;
extern int D_01F74CB0_amusement_01;
extern int D_01F714A0_amusement_01;
extern int D_01F714D0_amusement_01;
extern int D_01F71500_amusement_01;
extern int D_01F71530_amusement_01;
extern int D_01F74B10_amusement_01[];
extern float D_01F748F0_amusement_01;
extern float D_01F74950_amusement_01;
extern float D_01F74970_amusement_01;
extern float D_01F749D0_amusement_01;
extern float D_01F749F0_amusement_01;
extern float D_01F74A50_amusement_01;
extern int D_01F71460_amusement_01;
extern float D_01F746C0_amusement_01;
extern int D_01F74D90_amusement_01;
extern int D_01F74CF8_amusement_01;
extern int D_01F74C80_amusement_01;
extern int D_01F74C90_amusement_01;
extern int D_01F74CB8_amusement_01;
extern int D_01F74CF8_amusement_01;
extern float D_01F74DB0_amusement_01;
extern int D_01F74370_amusement_01;
extern float D_01F74A90_amusement_01;
extern float D_01F74AF0_amusement_01;
extern int D_01F74D08_amusement_01;
extern DWORD D_01F74A70_amusement_01;
extern DWORD *D_01F74D10_amusement_01;

extern u_int D_1D316A0;
extern u_int D_1D316AC;
extern u_int D_1D31648;
extern u_int D_1D316A0;

extern float D_01F74590_amusement_01;
extern float D_01F745F0_amusement_01;
extern float D_01F74510_amusement_01;
extern float D_01F74570_amusement_01;
extern int D_01F74C88_amusement_01;
extern float D_01F74C98_amusement_01;
extern float D_01F74CA0_amusement_01;

extern u_long128 D_01F748B0_amusement_01;
extern float D_01F748B8_amusement_01;
extern float D_01F748C8_amusement_01;
extern int D_01F74D18_amusement_01;

extern int D_01F74D88_amusement_01;
extern float D_01F74DB8_amusement_01;
extern float D_01F74DC0_amusement_01;

extern u_long128 D_01F748C0_amusement_01;
extern sceVu0FVECTOR D_01F748D0_amusement_01;
extern sceVu0FVECTOR D_01F748E0_amusement_01;

extern int D_01F72DA0_amusement_01;
extern int D_01F72F30_amusement_01;
extern int D_01F72FD0_amusement_01;
extern int D_01F73070_amusement_01;
extern int D_01F73160_amusement_01;
extern int D_01F73250_amusement_01;
extern int D_01F73340_amusement_01;
extern int D_01F73480_amusement_01;
extern int D_01F735C0_amusement_01;
extern int D_01F737A0_amusement_01;
extern int D_01F738E0_amusement_01;
extern int D_01F73B60_amusement_01;
extern int D_01F73C50_amusement_01;
extern int D_01F73D40_amusement_01;
extern int D_01F73E80_amusement_01;
extern int D_01F73F20_amusement_01;
extern int D_01F74010_amusement_01;
extern int D_01F741A0_amusement_01;
extern int D_01F74290_amusement_01;

extern Amusement01Pair D_01F74610_amusement_01[];
extern sceVu0FVECTOR D_01F74640_amusement_01;
extern sceVu0FVECTOR D_01F74650_amusement_01;
extern sceVu0FVECTOR D_01F74660_amusement_01;

extern int D_01F71400_amusement_01;
extern int D_01F74CA8_amusement_01;
extern int D_01F74DA0_amusement_01;
extern float D_01F74DA8_amusement_01;

// @hack thanks `func_0015DCD0` :')
/* begin candles, holy rituals to bend float arguments to our will */
#define UNCURSE_AMUSEMENT_BLOOD()                       \
void blood_candle_amusement_01(float a0, float a1) {    \
    sceVu0FVECTOR sp10;                                 \
    do {                                                \
        do {                                            \
            SeCall(a0, 0.0f, 666);                      \
            SeCall(a1, 0.0f, 666);                      \
            SeCall(a1, 0.0f, 666);                      \
        } while(1);                                     \
    } while (0);                                        \
}

#define UNCURSE_AMUSEMENT_MOON()                          \
float moon_candle_amusement_01(float x, float y) {        \
    float charm;                                          \
    float gem;                                            \
    charm *= x;                                           \
    gem *= y;                                             \
    return charm * charm + gem + gem;                     \
}
/* end candles */

#endif
