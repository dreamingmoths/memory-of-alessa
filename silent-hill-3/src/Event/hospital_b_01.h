#ifndef HOSPITAL_B_01_H
#define HOSPITAL_B_01_H

#include "common.h"
#include "Chacter/m3_sc.h"

void clAddDynamicWall(int*);
float func_001643C0(void);
void func_001433A0(SubCharacter*, int, int);
void func_0016C1A0(void);
void func_0016C1B0(void);
int func_0016C540(float*, float*);
void func_0016CA40(int);
void func_0016CBD0(Q**, Q*, int);
void func_0016D0E0(int, int);
void func_0016D170(int, Vector4*, int, int, float, float, int);
void func_0016E400(int, int);
void func_0018A260(int);
void func_0018A310(int, int, int);
void func_001C2290(int, float);
int func_001C2580(int);
void func_001C2A80(int, sceVu0FMATRIX);
void func_002395A0(float);
int func_001DD9F0(SubCharacter*);
void func_01F6D740_hospital_b_01();
void func_01F6D970_hospital_b_01();
void func_01F6DC60_hospital_b_01();
int RoomName(void);
int SeCall(float, float, int);
SubCharacter* shCharacterGetSubCharacter(int, short);
float shGetDT(void);

extern Vector4 D_01F6EBB0_hospital_b_01;

extern float D_01F6EAF0_hospital_b_01;
extern float D_01F6EB50_hospital_b_01;
extern float D_01F6EB88_hospital_b_01;
extern float D_01F6EBA0_hospital_b_01;

extern int D_01F6E6B0_hospital_b_01;
extern int D_01F6E890_hospital_b_01;
extern int D_01F6EB80_hospital_b_01;
extern int D_01F6EB90_hospital_b_01;
extern int D_01F6EB98_hospital_b_01;
extern int D_01F6EBA8_hospital_b_01;
extern int D_01F6EBC0_hospital_b_01;

extern u_int D_1D31648;
extern u_int D_1D31694;
extern u_int D_1D31698;
extern u_int D_1D3172C;
extern u_int D_1D317C0[];

#endif
