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

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s16 unk0C;
    u8 unk0E;
    u8 unk0F;
} PictureLoad;

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 unk37;
    u8 unk38;
    u8 unk39;
    u8 unk3A;
    u8 unk3B;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
    s16 unk40;
    s16 unk42;
} Picture;

typedef struct {
    PictureLoad unk00;
    PictureLoad unk10;
    Picture unk20;
    Picture unk64;
    u32 unkA8;
    s32 unkAC;
    s32 unkB0;
} PictureGroup; //I think this is something specific for this overlay, this will work only here

typedef struct {
    float unk0;
    int unk4;
} Struct_01F6DA80_hospital_f_00;

int RoomName();
int func_0016BED0(int, int);
int func_0012D080();
int func_001E2110(SubCharacter*);
int shCharacter_Manage_Delete(u_short kind, u_short id);
int func_0016C1C0(u_int);
int func_0013D080(int, int, int, int);
int func_00151150(int, int);
int func_001C2580(int);
int func_00170410(int);
int func_0019B580(int);
int func_0016C540(float *, float *);

void func_0016ECE0(int);
void func_00316C50(int);
void func_0016CA40(int);
void func_01F6EB00_hospital_f_00();
void func_01F6E3C0_hospital_f_00();
void func_01F6E850_hospital_f_00();
void func_01F6E890_hospital_f_00();
void func_0016CD00(int*);
void func_00190A20(int);
void func_0012CFA0();
void func_0012CFC0();
void SeCall(float, float, int);
void func_0016C1A0();
void func_0016C1B0();
void func_0016BBF0();
void func_0016BC00(int);
void func_0016C3C0();
void func_0016F550(int, int);
void func_001C2290(int, float);
void shQzero(void*, int);
void PictureDraw(void *);
void PictureLoadImage(void *);
void func_001DE5B0(void (*)(), PictureGroup *, s32); //maybe this is the problem
void func_001C7BC0(Q*, Q*, Q*, int);
void func_0013D250(int, int, float);
void func_0013D280(int);

void *func_00156410(int); //not sure
SubCharacter *shCharacterGetSubCharacter(short kind, short id);

float shGetDT();
float func_001643C0();

extern Q D_01F6F9D0_hospital_f_00;
extern Q D_01F6F9E0_hospital_f_00;
extern Q D_01F6F9F0_hospital_f_00;

extern int D_01F6FA88_hospital_f_00;
extern int D_01F6FA98_hospital_f_00;
extern int D_01F6FAC0_hospital_f_00;
extern int D_01F6F920_hospital_f_00;
extern int D_01F6F9C0_hospital_f_00;

extern float D_01F6FA90_hospital_f_00;
extern float D_01F6F940_hospital_f_00;
extern float D_01F6F9A0_hospital_f_00;

extern Struct_01F6DA80_hospital_f_00 D_01F6F930_hospital_f_00;
extern Struct_01F6DA80_hospital_f_00* D_01F6FAB8_hospital_f_00;

extern u_int D_1D31644;
extern u_int D_1D31680;
extern u_int D_1D31684;
extern u_int D_1D31688;
extern u_int D_1D3168C;
extern u_int D_1D316AC;
extern u_int D_1D316F4;
extern u_int D_1D3171C;
extern u_int D_1D31720;
extern u_int D_1D317B4;
extern u_int D_1D317B8;
extern u_int D_01D31640[];

#endif
