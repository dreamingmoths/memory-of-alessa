#ifndef SUBWAY_02_H
#define SUBWAY_02_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define SUBWAY_TRAIN_CAR_1        0x3E // savepoint
#define SUBWAY_TRAIN_CAR_2        0x3F // first numb body
#define SUBWAY_TRAIN_CAR_3        0x40  
#define SUBWAY_TRAIN_CAR_4        0x41 // big numb body
#define SUBWAY_TRAIN_CAR_5        0x42 // medikit and ammo (only on easy?)
#define SUBWAY_TRAIN_CAR_6        0x43
#define SUBWAY_TRAIN_CAR_7        0x44 // @todo: check in which one of these 2 spawns a insane cancer (normal+ action level)
#define SUBWAY_TRAIN_CAR_8        0x45 // last car before sewer
#define SUBWAY_TRAIN_TAIL_END     0x46 // death from falling from the train

typedef struct
{
    float  unk0;
    u_char unk4;
} func_001C7C80_struct;

static inline float vec3_length(void* v)
{
    float d;

    asm
    ("\
        lwc1 %1, 0(%0)\n\
        lwc1 f8, 4(%0)\n\
        lwc1 f9, 8(%0)\n\
        mula.s %1, %1\n\

        madda.s f8, f8\n\
        madd.s %1, f9, f9\n\
        sqrt.s %1, %1"
    : "+r"(v), "+f"(d) :: "f8", "f9"
    );

    return d;
}

static inline float vec3_dot_product(void* v, void* w)
{
    float d;

    asm volatile
    ("\
        lwc1 %0, 0(%1)\n\
        lwc1 f8, 0(%2)\n\
        lwc1 f9, 4(%1)\n\
        lwc1 f10, 4(%2)\n\
        mula.s %0, f8\n\
        lwc1 %0, 8(%1)\n\
        lwc1 f8, 8(%2)\n\
        madda.s f9, f10\n\
        madd.s %0, %0, f8"
    : "=f"(d): "r"(v), "r"(w): "f8", "f9", "f10"
    );

    return d;
}

SubCharacter* shCharacterGetSubCharacter(int, short);
void func_001C2290(int, float);
int func_0016C540(int *, int *);
int func_001646F0(void);
void func_001DA020(int, Q *, Q *);
float func_001643C0(void);
void func_0013D250(int, int *, float);
void func_001DC9E0(SubCharacter *, int);
void func_001BE4B0(int);
int func_00190A20(int);
void func_00190C40(void);
void func_0013D280(int);
int RoomName(void);
int func_001C2580(int);
int func_00190940(void);
void clAddDynamicWall(int *);
int func_001643D0(void);
void func_00170620(float*, int); // second arg here is a room id
float shGetDT(void);
void func_001C2AE0(int, sceVu0FMATRIX *);
void func_001C2A80(int, sceVu0FMATRIX *);
void func_001C18C0(sceVu0FVECTOR *);
void sh3gde_getCameraDir(sceVu0FMATRIX *);
int func_0019B580(int);
void func_001C7C80(sceVu0FVECTOR *, sceVu0FVECTOR *, sceVu0FVECTOR *, int);

int func_01F6D680_subway_02(void);
void func_01F6D8B0_subway_02(void);
void func_01F6D9A0_subway_02(void);
void func_01F6DBE0_subway_02(int);
void func_01F6DCF0_subway_02(int, int, int);
void func_01F6DE80_subway_02(sceVu0FVECTOR *);
void func_01F6E140_subway_02(sceVu0FVECTOR *);

extern int D_01F6F080_subway_02;
extern int D_01F6F088_subway_02;
extern int D_01F6EF10_subway_02;
extern int D_01F6EF70_subway_02;
extern int D_01F6ED90_subway_02;
extern int D_01F6EDD0_subway_02;
extern int D_01F6EE30_subway_02;
extern int D_01F6EC50_subway_02;
extern float D_01F6F0A0_subway_02;
extern float D_01F6F0C8_subway_02;
extern float D_01F6F0CC_subway_02;
extern float D_01F6F0D0_subway_02;
extern float D_01F6F0C0_subway_02;
extern float D_01F6F0A8_subway_02;
extern float D_01F6F0B8_subway_02;
extern float D_01F6F0B0_subway_02;

extern Q D_01F6EF90_subway_02;
extern Q D_01F6F090_subway_02;

extern sceVu0FVECTOR D_01F6EFA0_subway_02;
extern sceVu0FVECTOR D_01F6EFB0_subway_02;
extern sceVu0FVECTOR D_01F6EFC0_subway_02;

#endif
