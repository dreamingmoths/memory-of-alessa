#ifndef APART_00_H
#define APART_00_H

#include "common.h"
#include "Chacter/m3_sc.h"

#define APARTMENTS_HALLWAY          0x95
#define APARTMENTS_LIVING_ROOM      0x96
#define APARTMENTS_ROOFTOP          0x97
#define APARTMENTS_HARRYS_BEDROOM   0x98
#define APARTMENTS_HEATHERS_BEDROOM 0x99
#define APARTMENTS_OUTSIDE          0x9A

#define MISSIONARY_CHARA_ID 0x211
#define MISSIONARY_ID       0xF0

typedef struct Apart00Entry {
    int   unknown_0x0;
    float unknown_0x4;
    float unknown_0x8;
} Apart00Entry;

typedef struct Apart00Struct {
    char  unknown_0x0[0x1B8];
    float unknown_0x1B8;
    Apart00Entry entries[];
} Apart00Struct;

void func_001C2290(int, float);
void func_0016F550(int, int);
void shQzero(void*, int);
void func_0016DCE0(int);
int  func_0016C540(void*, void*);
int  func_00199C70(int);
int  func_001646C0(void);
void func_001602D0(int, int, int, float);
void func_001603E0(int, int);
int  func_0016C9B0(int*, int, int);
int  func_0016D5B0(void);
void func_00316C50(int);
void func_001DC9E0(SubCharacter*, int);
void func_001E22F0(int, int, int);
SubCharacter* shCharacterGetSubCharacter(int, short);

void func_01F6E050_apart_00(void);
void func_01F6EB70_apart_00(void);

extern void *D_01F6FD40_apart_00;
extern void *D_01F6FDC0_apart_00;
extern void *D_01F6FDA0_apart_00;
extern void *D_01F6FE20_apart_00;
extern char  D_01F6FB80_apart_00[];
extern float D_01F6FCC0_apart_00;
extern float D_01F6FD20_apart_00;
extern int   D_01F6FE40_apart_00;
extern int   D_01F70058_apart_00;
extern int   D_01F70060_apart_00;
extern u_int D_01D31640;
extern u_int D_1D31670[];
extern u_int D_1D316AC;
extern u_int D_1D3171C;

#endif
