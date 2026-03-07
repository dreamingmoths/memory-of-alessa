#ifndef AMUSEMENT_01_H
#define AMUSEMENT_01_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define DANNY_CHARA_ID 0x1043
#define DANNY_ID 0x171

typedef struct Amusement01Work {
    u_char unk_0x0[0x20];
    float x; // 0x20
    float y; // 0x24
    float z; // 0x28
    float f_0x2c; // 0x2c
    float f_0x30; // 0x30
    float angle; // 0x34
} Amusement01Work;

int func_01F6D680_amusement_01();

void func_001C0EB0(void (*)(__int128*, int*, __int128*, int*, int*), int, int);

static void func_01F6DCF0_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4);

static void func_01F6F430_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4);

static void func_01F6DC70_amusement_01(__int128* arg0, int* arg1, __int128* arg2, int* arg3, int* arg4);

void func_01F703B0_amusement_01(float, float);

extern float func_001643C0();
extern int func_0016C540(float *, float *);
extern void func_001C2290(int, float);
extern void func_0018FE60(__int128*);
extern void func_0016CF70();
extern int func_0016CF80(int, int, int*);
extern SubCharacter* shCharacterGetSubCharacter(int, short);
extern u_char func_00199770();
extern int D_01F713D0_amusement_01;
extern u_int D_1D3169C;
extern int shCharacter_Manage_Delete(u16 kind, u16 id);

extern void SeCall(float, float, int);
extern void func_0016C3C0();
extern int func_0016C1C0(int);
extern void func_00190A20(int a0);
extern void  func_0016D6B0(u_int);
extern int func_00190C00();
extern void func_00317420(u_int);
extern void func_00317490(int, float);
extern void func_003174B0(float);
extern void func_001602D0(int, int, int, float);
extern int func_00160520(int);
extern void func_00160AF0(int);                                 /* extern */
extern void func_0019A940(void);
extern int func_0019A9B0(float a0);
extern void func_0015DCD0(float, float, int, float *, int, int);
extern void func_001C2A70(int, float);
extern void func_001DC9E0(SubCharacter*, int);
extern int func_001DD9F0(SubCharacter*);   
extern void func_001433A0(SubCharacter*, int, int);

extern sceVu0FVECTOR D_01F74670_amusement_01;
extern sceVu0FVECTOR D_01F74690_amusement_01[];
extern float D_01F74610_amusement_01[][2];
extern int D_01F74D98_amusement_01;
extern int D_01F74CB0_amusement_01;
extern __int128 D_01F74680_amusement_01;
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
extern int D_1D316AC;
extern int RoomName();
extern u_int D_1D31648;

extern float D_01F74590_amusement_01;
extern float D_01F745F0_amusement_01;
extern float D_01F74510_amusement_01;
extern float D_01F74570_amusement_01;
extern int D_01F74C88_amusement_01;
extern float D_01F74C98_amusement_01;
extern float D_01F74CA0_amusement_01;

extern __int128 D_01F748B0_amusement_01;
extern float D_01F748B8_amusement_01;
extern float D_01F748C8_amusement_01;
extern int D_01F74D18_amusement_01;

#endif
