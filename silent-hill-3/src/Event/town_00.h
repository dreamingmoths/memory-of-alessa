#ifndef TOWN_00_H
#define TOWN_00_H

#include "common.h"

typedef struct Town00Struct {
    int x;
    int y;
    int z;
    int w;
} Town00Struct;

int func_01F6D680_town_00();

int func_01F6D7A0_town_00();

void func_01F6D8A0_town_00();

void func_01F6D9D0_town_00();

void func_01F6D9F0_town_00();

void func_01F6DA00_town_00();

Town00Struct state_town_00; // 0x01F6E000

extern void PlayerEventMove(float*);                            
extern int func_0016C1C0(int);                               
extern int func_00190690();                                
extern void func_001908A0(float*, float*);                        
extern int func_00190A20(int);                               
extern void func_00190AD0();   

extern float D_01F6DF70_town_00;
extern int D_01F6DF74_town_00;
extern float D_01F6DF78_town_00;

extern float D_01F6DF80_town_00;
extern int D_01F6DF84_town_00;
extern float D_01F6DF88_town_00;
extern int D_01F6DF90_town_00;

extern int func_0012FD80(int, long);                         
extern int func_00199770(int);                             
extern int func_001E2110(int);                             
extern void shCharacter_Manage_Delete(int, u_short);                

extern u_int D_1D31684;

extern void func_001AED70();                                  
extern void func_001AF0B0();

#endif
