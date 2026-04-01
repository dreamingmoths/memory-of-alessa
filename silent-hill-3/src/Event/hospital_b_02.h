#ifndef HOSPITAL_B_02_H
#define HOSPITAL_B_02_H

#include "common.h"
#include "Chacter/m3_sc.h"

typedef struct {
    int unk0;
    int unk4;
    u_char pad8[8];
    float unk10;
    float unk14;
    float unk18;
} unk_01F6D680_hospital_b_02_struct;

typedef struct {
    u_char pad[0x8A0];
    u_int unk8A0;
    float unk8A4;
    u_int unk8A8;
    u_int unk8AC;
} unk_01F6E700_hospital_b_02_struct;

int func_00190A20(int);
void* func_00190AC0(void);
int func_0013D080(int, int, int, int);
int func_0016BED0(int, int);
int SeCall(float, float, int);
void func_001916F0(void);
void func_0029FA30(void);
int GetRiddleLevel(void);
void func_0029F9B0(void);
void shQzero(void *, int);
int func_00151150(int, int); 
void* func_00156410(int);
void func_0016BBF0(void);
void func_0016BC00(int);
void func_0016C1A0(void);
void func_0016C1B0(void);
int func_0016C1C0(int);
void func_0016F550(int, int);
void func_001C2290(int, float);
int func_001C2580(int);
float shGetDT(void);
int func_0019B580(int);
void func_001C7BC0(Q *, Q *, Q *, int);
void func_0016D170(int, Vector4*, int, int, float, float, int);
void func_0018FE60(u_long128 *);
int func_001DDAE0(SubCharacter*);
SubCharacter* shCharacterGetSubCharacter(int, int);

extern u_int D_1D31680[];
extern u_int D_1D31694[];
extern u_int D_1D318EC;
extern u_int D_01D31640[];
extern int D_1D316FC[];
extern u_int D_1D31698[];
extern u_int D_1D3172C[];
extern u_int D_1D317C0[];

extern Q D_01F73FC0_hospital_b_02;
extern Q D_01F73FD0_hospital_b_02;
extern Q D_01F73FE0_hospital_b_02;

extern int D_01F74100_hospital_b_02;
extern float D_01F74108_hospital_b_02;
extern int D_01F74110_hospital_b_02;
extern float D_01F74118_hospital_b_02;
extern int D_01F74140_hospital_b_02;
extern int D_01F74148_hospital_b_02;

#endif
