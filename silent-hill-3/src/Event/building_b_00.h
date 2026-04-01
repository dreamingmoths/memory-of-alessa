#ifndef BUILDING_B_00_H
#define BUILDING_B_00_H

#include "common.h"

#define BUILDING_OTHERWORLD_1F_HALL 0x7E
#define BUILDING_OTHERWORLD_LIVER_ROOM 0x7F
#define BUILDING_OTHERWORLD_1F_SLURPERS_CORRIDOR 0x80
#define BUILDING_OTHERWORLD_1F_LAST_FAIRY_TAIL_PIECE_ROOM 0x81

int RoomName(void);
int SeCall(float, float, int);
int func_00168440(void);
void func_0016C1A0(void);
void func_0016C1B0(void);
int func_0016C1C0(u_int);
void func_0016C3C0(void);
void func_0016CA40(int);
void ItemGet(u_int);
void func_00189F00(u_short);
void func_00189FA0(int, int);
void func_00190A20(u_int);
void clAddDynamicWall(int *);
void clAddDynamicFloor(int *);
void func_001C2290(int, float);
void func_00317420(u_int);
void func_00317490(int, float);
void func_003174B0(float);
float shGetDT(void);

extern int D_01F6EC70_building_b_00;
extern int D_01F6F260_building_b_00;
extern int D_01F6F530_building_b_00;
extern int D_01F6F760_building_b_00;
extern int D_01F6FB00_building_b_00;
extern int D_01F6FB08_building_b_00;
extern float D_01F6FB10_building_b_00;
extern u_int D_1D31644;
extern u_int D_1D31670[3];
extern u_int D_1D31714;
extern int D_1D31710[4];
extern int D_1D317A8;

#endif
