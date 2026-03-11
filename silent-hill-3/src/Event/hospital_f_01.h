#ifndef HOSPITAL_F_01_H
#define HOSPITAL_F_01_H

#include "common.h"

#define HOSPITAL_2F_ELEVATOR_HALLWAY 0xA6
#define HOSPITAL_2F_WOMENS_LOCKER_ROOM 0xA7
#define HOSPITAL_2F_M_CORRIDOR 0xA8
#define HOSPITAL_2F_EXAMINING_ROOM_3 0xA9
#define HOSPITAL_2F_M4_ROOM 0xAA //this is the clock room
#define HOSPITAL_2F_M5_ROOM 0xAB

int RoomName();
int func_0012D080();
int func_0016BED0(u_int, u_int);
int func_00199BB0();
void func_0012CFA0();
void func_0012CFC0();
void func_00190A20(int);

extern u_int D_1D31644;
extern u_int D_1D31680;
extern u_int D_1D31684;
extern u_int D_1D31688;
extern u_int D_1D316F4;
extern u_int D_1D31720;

#endif