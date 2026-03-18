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

typedef struct
{
    int unk00;
    int unk04;
    int unk08;
    short unk0C;
    u_char unk0E;
    u_char unk0F;
} PictureLoad;

typedef struct
{
    int unk00;
    int unk04;
    int unk08;
    short unk0C;
    short unk0E;
    short unk10;
    short unk12;
    short unk14;
    short unk16;
    short unk18;
    short unk1A;
    u_int unk1C;
    u_int unk20;
    u_int unk24;
    u_int unk28;
    u_char unk2C;
    u_char unk2D;
    u_char unk2E;
    u_char unk2F;
    u_char unk30;
    u_char unk31;
    u_char unk32;
    u_char unk33;
    u_char unk34;
    u_char unk35;
    u_char unk36;
    u_char unk37;
    u_char unk38;
    u_char unk39;
    u_char unk3A;
    u_char unk3B;
    u_char unk3C;
    u_char unk3D;
    u_char unk3E;
    u_char unk3F;
    short unk40;
    short unk42;
} Picture;

typedef struct
{
    PictureLoad unk00;
    PictureLoad unk10;
    Picture unk20;
    Picture unk64;
    u_int unkA8;
    int unkAC;
    int unkB0;
} PictureGroup; // I think this is something specific for this overlay, this will work only here

typedef struct
{
    float unk0;
    int unk4;
} Struct_01F6DA80_hospital_f_00;

int RoomName(void);
int func_0012D080(void);
int func_0013D080(int, int, int, int);
int func_00151150(int, int);
int func_00168440(void);
int func_00170410(int);
int func_0019B580(int);
int func_001C2580(int);
int func_001E2110(SubCharacter *);
int shCharacter_Manage_Delete(u_short kind, u_short id);

int func_0016BED0(int, int);
int func_0016C1C0(u_int);
int func_0016C540(float *, float *);

float shGetDT(void);
float func_001643C0(void);

void func_0012CFA0(void);
void func_0012CFC0(void);
void func_0013D250(int, int, float);
void func_0013D280(int);
void func_0015DCD0(float, float, int, float *, int, int);

void func_0016CA40(int);
void func_0016CD00(int *);
void func_0016C1A0(void);
void func_0016C1B0(void);
void func_0016C3C0(void);
void ItemGet(u_int);
void func_0016ECE0(int);
void func_0016BBF0(void);
void func_0016BC00(int);
void func_0016F550(int, int);

void func_0018FE60(__int128 *);
void func_00190A20(int);
void func_001C2290(int, float);
void func_001C7BC0(Q *, Q *, Q *, int);
void func_00316C50(int);

void PictureDraw(void *);
void PictureLoadImage(void *);
void shQzero(void *, int);
void SeCall(float, float, int);

void func_001DE5B0(void (*)(), PictureGroup *, s32); // maybe this is the problem

void *func_00156410(int); // not sure
SubCharacter *shCharacterGetSubCharacter(short kind, short id);

extern Q D_01F6F9D0_hospital_f_00;
extern Q D_01F6F9E0_hospital_f_00;
extern Q D_01F6F9F0_hospital_f_00;

extern int D_01F6F920_hospital_f_00;
extern int D_01F6F9C0_hospital_f_00;

extern int D_01F6FA80_hospital_f_00;
extern int D_01F6FA88_hospital_f_00;
extern int D_01F6FA98_hospital_f_00;
extern int D_01F6FAA0_hospital_f_00;
extern int D_01F6FAA8_hospital_f_00;
extern int D_01F6FAB0_hospital_f_00;
extern int D_01F6FAC0_hospital_f_00;

extern float D_01F6FA90_hospital_f_00;
extern float D_01F6F940_hospital_f_00;
extern float D_01F6F9A0_hospital_f_00;

extern Struct_01F6DA80_hospital_f_00 D_01F6F930_hospital_f_00;
extern Struct_01F6DA80_hospital_f_00 *D_01F6FAB8_hospital_f_00;

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
