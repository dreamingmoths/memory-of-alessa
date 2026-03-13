#ifndef CHURCH_00_H
#define CHURCH_00_H

#include "common.h"

struct ChurchStruct00 { float t; int id; };

int func_0013D080(int, int, int, int);
void func_0013D250(int, int, float);
void func_0013D280(int);
int func_001646C0(void);
float func_001643C0(void);
int func_0016BED0(int, int);
int func_0016C1C0(int);
int func_0016C540(void*, void*);
void func_0016CA40(int);
void func_0016DCE0(int);
void func_0016E400(int, int);
void func_0016ECE0(int);
void func_00190A20(int);
void func_0019A940(void);
int func_0019A9B0(float);
void func_001C0EB0(void*, int, int);
void func_001C0EE0(int);
void func_001C2290(int, float);
int func_001C2580(int);
void func_00300390(void);
void func_00316C50(int);
void func_01F6DCF0_church_00(Q*, int*, Q*, int*, int*);
void SeCall(float, float, int);
float shGetDT(void);

extern short D_01F6E550_church_00[];
extern short D_01F6E560_church_00[];

extern int D_01F6E600_church_00;
extern int D_01F6E608_church_00;

extern float D_01F6E610_church_00;

extern struct ChurchStruct00* D_01F6E618_church_00;
extern struct ChurchStruct00* D_01F6E620_church_00;
extern struct ChurchStruct00 D_01F6E3B0_church_00[];
extern struct ChurchStruct00 D_01F6E480_church_00[];

extern void* D_01F6E4D0_church_00;
extern void* D_01F6E530_church_00;

extern Q D_01F6E570_church_00;
extern Q D_01F6E580_church_00;

extern u_int D_1D31644;
extern u_int D_1D316A4;

// @hack thanks SeCall :')
#define UNCURSE_CHURCH()                                                   \
void uncurse(float a0, float a1, float a2, float a3, u_int a4, void* a5) { \
    float x;                                                               \
    float y;                                                               \
    do {                                                                   \
        SeCall(1.0f, 0.0f, 19000);                                         \
        do {                                                               \
            SeCall(a0, 0.0f, 19000);                                       \
            SeCall(a1, 0.0f, 19000);                                       \
            SeCall(a1, 0.0f, 19000);                                       \
        } while(1);                                                        \
    } while (0);                                                           \
}

#endif
