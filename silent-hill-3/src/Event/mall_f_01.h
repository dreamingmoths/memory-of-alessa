#ifndef MALL_F_01
#define MALL_F_01

#include "picture.h"

typedef struct
{
    // total size: 0x8
    float unk0; // offset 0x0, size 0x4
    int*  unk4; // offset 0x4, size 0x4
} D_01F72758_struct;

typedef struct
{
    // total size: 0x8
    float unk0; // offset 0x0, size 0x4
    int*  unk4; // offset 0x4, size 0x4
} D_01F727E0_struct;

void func_001C2290(int, float);
void func_0019B4B0(int);
int func_001C2580(int);
int func_0016C540(int *, int *);
float func_001643C0(void);
void func_0013D250(int, int *, float);
void func_0013D280(int);
void func_003272C0(void);
int shRandI(void);
float shRandF(void);
void func_003272E0(void);
int func_001646C0(void);
void func_001602D0(int, int, int, float);
void func_003272D0(void);
void func_0016C3C0(void);
void func_00317420(int);
int func_00190A20(int);
int func_0016C1C0(int);
int func_00168440(void);
void SeCall(float, float, int);
void ItemGet(u_int);
void func_00317490(int, float);
void func_003174B0(float);
int func_0012CFA0(void);
int func_0012D080(void);
int func_0012CFC0(void);
u_char GetRiddleLevel(void);
int func_0016BED0(int, int);
void shQzero(void* ptr, u_int size);
sh3gfw_AREA_HEAD* func_00170410(u_int index);
void func_002A2E70(Q*);
int func_002A47C0(float, float);
void func_0029F330(float*, float*);

int func_01F6D680_mall_f_01(void);
int func_01F6D820_mall_f_01(void);
int func_01F6DA20_mall_f_01(void);
int func_01F6DA70_mall_f_01(void);
int func_01F6DBD0_mall_f_01(void);
int func_01F6DCC0_mall_f_01(void);
void func_01F6DDB0_mall_f_01(void);
void func_01F6DF00_mall_f_01(PicLoadImage_Data* pic_load /* r17 */);
void func_01F6DF90_mall_f_01(PicLoadImage_Data* pic_load);
void func_01F6EE40_mall_f_01(int);
int func_01F70720_mall_f_01(void);

extern int D_01F72BC8_mall_f_01;
extern int D_01F72760_mall_f_01;
extern int D_01F727C0_mall_f_01;
extern u_int D_1D31644;
extern u_int D_1D31784;
extern int D_01F72810_mall_f_01;
extern int D_01F72870_mall_f_01;
extern int D_01F72BB8_mall_f_01;
extern float D_01F72BB0_mall_f_01;
extern int D_01F72890_mall_f_01;
extern int D_01F728F0_mall_f_01;
extern u_int D_1D3164C;
extern int D_01F72B80_mall_f_01;
extern u_int D_1D31BF4;
extern u_int D_1D316F0;
extern u_int D_1D31650;
extern int D_1D31700;

extern D_01F72758_struct* D_01F72BC0_mall_f_01;
extern D_01F72758_struct D_01F72758_mall_f_01;

extern D_01F727E0_struct D_01F727E0_mall_f_01;

extern Q D_01F72AB0_mall_f_01;

#endif