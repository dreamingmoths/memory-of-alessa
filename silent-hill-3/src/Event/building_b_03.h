#ifndef BUILDING_B_03_H
#define BUILDING_B_03_H

#include "common.h"

#define BUILDING_OTHERWORLD_MATCHBOOK_ROOM 0x90
#define BUILDING_OTHERWORLD_GALLERY_ROOM   0x92
#define BUILDING_OTHERWORLD_ELEVATOR       0x93

int   RoomName();
void  SeCall(float, float, long);
float shGetDT();
void  func_0016C1A0();
void  func_0016C1B0();
int   func_0016C1C0(int);
void  func_00190A20(int);
void  func_001C2290(int, float);
void  func_001DE5B0(void*, int, int);
extern void func_01F6DC90_building_b_03(int);

extern int   D_01F6FC00_building_b_03;
extern float D_01F6FC08_building_b_03;
extern int   D_01F6FC10_building_b_03;
extern float D_01F6FC18_building_b_03;
extern float D_01F6FC20_building_b_03;
extern int   D_01F6FC28_building_b_03;
extern int   D_01F6FC30_building_b_03;
extern int   D_01F6FC40_building_b_03;
extern u_int D_1D31670;
extern u_int D_1D31674;
extern u_int D_1D316F4;
extern u_int D_1D31714;
extern u_int D_1D31718;
extern u_int D_1D317B0;

#endif
