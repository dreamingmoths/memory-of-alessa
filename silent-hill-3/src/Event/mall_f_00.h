#ifndef MALL_F_00
#define MALL_F_00

#include "common.h"
#include "Chacter/m3_sc.h"
#include "Event/stg_name.h"

typedef struct
{
    float unk0;
    int*  unk4;
} D_01F6F890_struct;

typedef struct
{
    // total size: 0x20
    sceVu0FVECTOR unk0;  // offset 0x0, size 0x10
    int           unk10; // offset 0x10, size 0x4
    float         unk14; // offset 0x14, size 0x4
    float         unk18; // offset 0x18, size 0x4
    float         pad;   // offset 0x1C, size 0x4
} D_01F6F950_struct;

void func_001C2290(int, float);
int func_0016C540(int *, int *);
int func_0016C9B0(int *, int, int);
float func_001643C0(void);
int func_0015E880(void);
int func_0015E850(void);
void func_0013D250(int, int *, float);
void func_001603E0(int, int);
void func_0013D280(int);
int func_001646C0(void);
void func_001602D0(int, int, int, float);
void func_001646B0(float);
int func_0019B580(int);
void func_001300F0(sceVu0FMATRIX *, int, int, int);
void func_00213810(sceVu0FVECTOR *, D_01F6F950_struct *, int, int, float, float, Q *);
void func_002804E0(sceVu0FVECTOR *, sceVu0FVECTOR *, int, int);
void func_00143610(sceVu0FVECTOR *, sceVu0FVECTOR *);
void func_00281120(sceVu0FVECTOR *, sceVu0FVECTOR *, int);
void func_0023D820(sceVu0FVECTOR *, sceVu0FVECTOR *, int);
void func_00280430(sceVu0FVECTOR *, sceVu0FVECTOR *, int, int, int, short, float);
SubCharacter* shCharacterGetSubCharacter(int, short);
void func_001DC9E0(SubCharacter *, int);
void func_0016CBD0(sceVu0FMATRIX *[], sceVu0FMATRIX *[], int);
void func_0016CC50(int, int, sceVu0FMATRIX *, sceVu0FVECTOR *);
void func_002F2AF0(Vector4 *, SubCharacter *, int);
void func_00316C50(int);
void func_0016ECE0(int);
float shRandF(void);
int func_00190A20(int);
void SeCall(float, float, int);
float shGetDT(void);
int func_0016C1C0(int);
void func_0016C3C0(void);
void func_0016CD00(int *);
int func_0016BED0(int, int);
int func_00199C70(int);
int RoomName(void);
void func_0016D810(u_int);
void func_0016E400(int, int);
void func_0016DCE0(int);
void ItemGet(u_int);
void func_001999B0(void);
void func_0016CA40(u_int);

void func_01F6D680_mall_f_00(void);
int func_01F6D6E0_mall_f_00(void);
int func_01F6D8D0_mall_f_00(void);
void func_01F6DE40_mall_f_00(void);
int func_01F6DEF0_mall_f_00(void);
int func_01F6E0C0_mall_f_00(void);
void func_01F6E160_mall_f_00(void);
void func_01F6E380_mall_f_00(void);
void func_01F6E4B0_mall_f_00(void);
int func_01F6E5C0_mall_f_00(void);

extern int D_01F6FBF8_mall_f_00;
extern int D_01F6F810_mall_f_00;
extern int D_01F6F870_mall_f_00;
extern int D_01F6F8A0_mall_f_00;
extern int D_01F6FB80_mall_f_00;
extern int D_01F6F9F0_mall_f_00;
extern int D_01F6FA50_mall_f_00;
extern int D_01F6FB88_mall_f_00;
extern int D_01F6FB90_mall_f_00;
extern int D_01F6FB98_mall_f_00;
extern int D_01F6FBA0_mall_f_00;
extern float D_01F6F930_mall_f_00[];
extern float D_01F6F900_mall_f_00[];
extern int D_01F6F730_mall_f_00;
extern int D_01F6F6F0_mall_f_00;
extern int D_01F6F6B0_mall_f_00;
extern short D_01F6FA04_mall_f_00;
extern u_int D_1D316FC;
extern int D_01F6FAA0_mall_f_00;
extern u_int D_1D316AC;
extern u_int D_1D3164C;
extern int D_01F6FBE8_mall_f_00;
extern float D_01F6FBE0_mall_f_00;
extern float D_01F6FBD8_mall_f_00;
extern int D_01F6FB00_mall_f_00;
extern u_int D_1D31650;
extern int D_01F6FBD0_mall_f_00;
extern u_int D_01D31640;
extern u_int D_1D3169C;
extern u_int D_1D31644;
extern u_int D_1D31648;

extern D_01F6F890_struct* D_01F6FBF0_mall_f_00;
extern D_01F6F890_struct D_01F6F890_mall_f_00;

extern Q D_01F6FA70_mall_f_00;

extern D_01F6F950_struct D_01F6F950_mall_f_00[];

extern sceVu0FVECTOR D_01F6FA80_mall_f_00;
extern sceVu0FVECTOR D_01F6FA90_mall_f_00;
extern sceVu0FVECTOR D_01F6FBB0_mall_f_00;
extern sceVu0FVECTOR D_01F6FBC0_mall_f_00;

#endif