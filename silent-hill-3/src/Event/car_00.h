#ifndef CAR_00_H
#define CAR_00_H

#include "common.h"

typedef union DWORD
{
    u_int u32[2];
    float fv[2];
} DWORD;

int func_0013D080(int, int, int, int);
void func_0013D250(int, int, float);
void func_0013D280(int);
void func_0015E780(int);
void func_001603E0(int, int, int);
int func_00160520(int);
float func_001643C0(void);
int func_001646C0(void);
int func_001646F0(void);
int func_0016C540(int *, int *);
void func_0016DCE0(int);
void func_00190A20(int);
void func_001C2290(int, float);
void func_001DA020(int, int (*)[4], int (*)[4]);

extern DWORD D_01F6DB98_car_00;
extern int D_01F6DBA0_car_00[4];
extern int D_01F6DBB0_car_00;
extern int D_01F6DC10_car_00;
extern int D_01F6DC80_car_00[4];
extern int D_01F6DC98_car_00;
extern int D_1D316AC;

extern DWORD *D_01F6DC90_car_00;

extern int state_01F6DCA0_car_00; // state

#define CAR_00_INIT 0
#define CAR_00_PLAY 1

#endif
