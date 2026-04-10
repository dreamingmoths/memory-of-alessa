#ifndef CHURCH_02_H
#define CHURCH_02_H

#include "common.h"

#define CHURCH_LIBRARY 0xFD
//I will add all the others later
#define CHURCH_ALESSAS_BEDROOM 0x106

u_char GetRiddleLevel(void);
short RoomName(void);
int func_0016D5B0(void);
int GetExtraNewGame(void);
void func_001C2290(int, float);
int func_0016C540(float *, float *);
int func_00190A20(int);
int func_0016BED0(int, int);
int func_0016C1C0(int);
void func_0016C3C0(void);
void func_0016CD00(int *);
void func_0012CFA0(void);
void func_0012CFC0(void);
void func_0012CFE0(int);
void func_0029F330(float *, float *);
int func_002A47C0(float, float);
void ItemGet(u_int);
void SeCall(float, float, int);
int func_001646C0(void);
void func_0016C9C0(void);
void func_0019A940(void);
int func_0019A9B0(float);
int  func_001C2580(int);
void func_00317490(int, float);
void func_003174B0(float);
void func_01F6F940_church_02(void);
int func_0016BD90(int, int, float);
int func_001DE5B0(int*, int, int);
int func_01F6FE40_church_02(int);

extern float D_01F769C0_church_02;
extern float D_01F76A20_church_02;
extern float D_01F76A40_church_02;
extern float D_01F76AA0_church_02;
extern float D_01F76E10_church_02;
extern float D_01F76E70_church_02;
extern int D_01F76AC0_church_02;
extern int D_01F76AD0_church_02;
extern int D_01F77580_church_02;
extern int D_01F77590_church_02;
extern int D_01F77598_church_02;
extern int D_01F775C8_church_02;
extern int D_01F775C0_church_02;
extern int D_01F77600_church_02;
extern int D_01F77608_church_02;
extern int D_01F77610_church_02;
extern int D_01F77908_church_02;
extern int D_01F77890_church_02;
extern int D_01F77858_church_02[][3];
extern int func_01F715C0_church_02;
extern int D_01D31938[];

extern u_int D_1D316A8[];
extern u_int D_1D31644[];
extern u_int D_1D317D0[];
extern u_int D_1D316F8[];
extern u_int D_1D316A4[];
extern u_int D_1D316AC[];

#endif
