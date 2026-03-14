#ifndef HOSPITAL_F_01_H
#define HOSPITAL_F_01_H

#include "common.h"

#define HOSPITAL_2F_ELEVATOR_HALLWAY 0xA6
#define HOSPITAL_2F_WOMENS_LOCKER_ROOM 0xA7
#define HOSPITAL_2F_M_CORRIDOR 0xA8
#define HOSPITAL_2F_EXAMINING_ROOM_3 0xA9
#define HOSPITAL_2F_M4_ROOM 0xAA // this is the clock room
#define HOSPITAL_2F_M5_ROOM 0xAB

void func_0012CFA0();
void func_0012CFC0();
int func_0012D080();
void func_0016C1A0();
void func_0016C1B0();
int func_0016C1C0(int);
void func_0016C3C0();
void func_0016CA40(int);
int func_0016BED0(u_int, u_int);
int func_00168440();
void func_00190A20(int);
void func_001C2290(int, float);
void func_0029F330(float*, float*);
int func_002A47C0(float, float);
int GetExtraNewGame();
int GetRiddleLevel(void);
int RoomName();
void SeCall(float, float, int);
float shGetDT();
int shRandI(void);

extern int D_01F71000_hospital_f_01;
extern int D_01F71140_hospital_f_01;
extern int D_01F711E0_hospital_f_01;
extern int D_01F71680_hospital_f_01;
extern int D_01F71688_hospital_f_01;
extern float D_01F71690_hospital_f_01;

extern u_int D_01D31640[];

extern u_int D_1D31644;
extern u_int D_1D31680;
extern u_int D_1D31684;
extern u_int D_1D31688;
extern u_int D_1D316F4;
extern u_int D_1D31720;
extern u_int D_1D317B8;
extern u_int D_1D318DC; // clock code
extern u_int D_1D318E0; // case code

#endif
