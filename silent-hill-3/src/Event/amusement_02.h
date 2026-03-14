#ifndef AMUSEMENT_02_H
#define AMUSEMENT_02_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define MEMORY_OF_ALESSA_CHARA_ID 0x215

typedef struct {
    float unk0;
    int unk4;
} D_01F7AB60_struct;

typedef struct {
    short id;
    u_char pad[0x12];
} Entry_01F763C0; // size: 0x14

void func_0013D250(int, int, float);
void func_0013D280(int);
void func_001602D0(int, int, int, float);
void func_001603E0(int, int);
int func_00160520(int);
float func_001643C0();
int func_0016BED0(int, int);
void func_0016C1A0();
int func_0016C1C0(int);
int func_0016C540(int *, int *);
void func_0016D500(int, int, int);
short RoomName();
void func_00190A20(int);
int func_00190C00();
void func_00199830(int);
void func_0019B4B0(int);
void func_0019B540(int);
void func_001C2290(int, float);
int func_001C2580(int);
void func_001D37E0(SubCharacter *, int, int, int, int);
void func_001DC9E0(SubCharacter *, int);
int func_001E2110(SubCharacter *);
void func_001E22F0(int, int, int);
void func_002FE570();
void func_00316C50(int);
int func_01F6F560_amusement_02();
void SeCall(float, float, int);
SubCharacter* shCharacterGetSubCharacter(int, short);

extern Entry_01F763C0 D_01F763C0_amusement_02[];

extern float D_01F76698_amusement_02;

extern int D_01F761A0_amusement_02;
extern int D_01F76200_amusement_02;
extern int D_01F76220_amusement_02;
extern int D_01F76280_amusement_02;
extern int D_01F762A0_amusement_02;
extern int D_01F762C0_amusement_02;
extern int D_01F76320_amusement_02;
extern int D_01F76340_amusement_02;
extern int D_01F763A0_amusement_02;
extern int D_01F76688_amusement_02;
extern int D_01F76690_amusement_02;
extern int D_01F76710_amusement_02;

extern int D_01F7AB50_amusement_02;
extern int D_01F7AB58_amusement_02;
extern D_01F7AB60_struct* D_01F7AB60_amusement_02;
extern int D_01F7AB68_amusement_02;
extern int D_01F7AB70_amusement_02;
extern int D_01F7AB78_amusement_02;

extern u_int D_01F7AB30_amusement_02[];
extern u_int D_01F7AB38_amusement_02[];

extern u_int D_1D316A0;
extern int D_1D316AC;

#endif
