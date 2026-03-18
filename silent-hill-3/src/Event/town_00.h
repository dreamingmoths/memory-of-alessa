#ifndef TOWN_00_H
#define TOWN_00_H

#include "common.h"
#include "Chacter/m3_sc.h"

typedef struct Town00Struct
{
    int x;
    int y;
    int z;
    int w;
} Town00Struct;

int func_01F6D680_town_00(void);
int func_01F6D7A0_town_00(void);
void func_01F6D8A0_town_00(void);
void func_01F6D9D0_town_00(void);
void func_01F6D9F0_town_00(void);
void func_01F6DA00_town_00(void);

Town00Struct state_town_00; // 0x01F6E000

extern void PlayerEventMove(float *);
extern int func_0016C1C0(int);
extern int func_00190690(void);
extern void func_001908A0(float *, float *);
extern int func_00190A20(int);
extern void func_00190AD0(void);

extern float D_01F6DF70_town_00;
extern int D_01F6DF74_town_00;
extern float D_01F6DF78_town_00;
extern float D_01F6DF80_town_00;
extern int D_01F6DF84_town_00;
extern float D_01F6DF88_town_00;
extern int D_01F6DF90_town_00;

extern SubCharacter* shCharacterGetSubCharacter(int, long);
extern int GetActionLevel(int);
extern int func_001E2110(SubCharacter*);
extern void shCharacter_Manage_Delete(int, u_short);
extern u_int D_1D31684;
extern void func_001AED70(void);
extern void func_001AF0B0(void);

#endif
