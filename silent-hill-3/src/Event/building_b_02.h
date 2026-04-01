#ifndef BUILDING_B_02_H
#define BUILDING_B_02_H

#include "common.h"

#define BUILDING_OTHERWORLD_4F_HALL 0x88
#define BUILDING_OTHERWORLD_STAIRS_BEHIND_PAINTING 0x89
#define BUILDING_OTHERWORLD_4F_SLURPERS_CORRIDOR 0x8A
#define BUILDING_OTHERWORLD_4F_SILVER_COIN_CORRIDOR 0x8B
#define BUILDING_OTHERWORLD_4F_BED_ROOM 0x8C
#define BUILDING_OTHERWORLD_4F_SILVER_COIN_ROOM 0x8D

int RoomName(void);
int SeCall(float, float, int);
float shGetDT(void);
int shCharacterGetSubCharacter(int, short);
void func_0016C1A0(void);
void func_0016C1B0(void);
void func_0016CA40(int);
int func_00190950(void);
u_char GetActionLevel(void);
void clAddDynamicWall(void *);
void func_001C2290(int, float);
int func_001E2110(int);

extern int D_01F6EB80_building_b_02;
extern int D_01F6EF00_building_b_02;
extern float D_01F6EF08_building_b_02;
extern int D_01F6EF10_building_b_02;
extern int D_01F6EF28_building_b_02;
extern int D_01F6EE80_building_b_02[];
extern u_int D_1D31644;
extern u_int D_1D31670;
extern u_int D_1D31714;
extern u_int D_1D317AC;
extern u_int D_1D317B0;

#endif
