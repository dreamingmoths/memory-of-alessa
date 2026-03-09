#ifndef HOSPITAL_F_00_H
#define HOSPITAL_F_00_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define HOSPITAL_1F                 0x9F
#define HOSPITAL_1F_RECEPTION       0xA0
#define HOSPITAL_1F_DOCTORS_LOUNGE  0xA1
#define HOSPITAL_1F_VISITING_ROOM   0xA2
#define HOSPITAL_1F_C_CORRIDOR      0xA3
#define HOSPITAL_1F_C2_ROOM         0xA4
#define HOSPITAL_1F_C4_ROOM         0xA5

int RoomName();
void func_0016ECE0(int);
void func_00316C50(int);
void func_0016CA40(int);
void func_01F6EB00_hospital_f_00();
void func_01F6E3C0_hospital_f_00();
void func_01F6E850_hospital_f_00();
void func_01F6E890_hospital_f_00();
int func_0016BED0(int, int);
void func_0016CD00(int*);
void func_00190A20(int);
void func_0012CFA0();
void func_0012CFC0();
int func_0012D080();
int func_001E2110(SubCharacter*);
SubCharacter *shCharacterGetSubCharacter(short kind, short id);
int shCharacter_Manage_Delete(u_short kind, u_short id);
void SeCall(float, float, int);
void func_0016C1A0();
void func_0016C1B0();
void func_001C2290(int, float);
float shGetDT();

extern int D_01F6FA88_hospital_f_00;
extern int D_01F6FA98_hospital_f_00;
extern int D_01F6FAC0_hospital_f_00;
extern int D_01F6F920_hospital_f_00;
extern int D_01F6F9C0_hospital_f_00;
extern float D_01F6FA90_hospital_f_00;

extern u_int D_1D31644;
extern u_int D_1D31680;
extern u_int D_1D31684;
extern u_int D_1D31688;
extern u_int D_1D3168C;
extern u_int D_1D316F4;
extern u_int D_1D3171C;
extern u_int D_1D31720;
extern u_int D_1D317B4;

#endif
