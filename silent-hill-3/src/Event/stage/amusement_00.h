#ifndef AMUSEMENT_00_H
#define AMUSEMENT_00_H

#include "common.h"
#include "Event/picture.h"

// Amusement 00 Functions
void func_01F6DEA0_amusement_00(float);
void func_01F6E420_amusement_00(float);
int func_01F6ED00_amusement_00(void);

// Amusement 00 Structs
typedef struct {
    float unk0;
    int unk4;
} Amusement00Pair;

// Amusement 00 Data
extern int D_01F72D80_amusement_00;
extern int D_01F72D90_amusement_00;
extern int D_01F72DA0_amusement_00;
extern float D_01F72DB0_amusement_00;
extern float D_01F72D88_amusement_00;
extern int D_01F72DB8_amusement_00;
extern int D_01F72DC0_amusement_00;
extern int D_01F72DC8_amusement_00;
extern int D_01F72830_amusement_00;
extern int D_01F72890_amusement_00;
extern int D_01F728E0_amusement_00;
extern int D_01F72940_amusement_00;
extern int D_01F72AF0_amusement_00;
extern int D_01F72B50_amusement_00;
extern int D_01F72B90_amusement_00;
extern int D_01F72BF0_amusement_00;
extern Vector4 D_01F72C10_amusement_00;
extern Vector4 D_01F72C20_amusement_00;
extern Vector4 D_01F72C30_amusement_00;
extern int D_01F70290_amusement_00;
extern int D_01F70420_amusement_00;
extern int D_01F70510_amusement_00;
extern int D_01F706A0_amusement_00;
extern int D_01F70740_amusement_00;
extern int D_01F708D0_amusement_00;
extern int D_01F70970_amusement_00;
extern int D_01F70A10_amusement_00;
extern int D_01F71140_amusement_00;
extern int D_01F718C0_amusement_00;
extern int D_01F71960_amusement_00;
extern int D_01F71A00_amusement_00;
extern int D_01F71B40_amusement_00;
extern int D_01F71BE0_amusement_00;
extern int D_01F71C80_amusement_00;
extern int D_01F71D20_amusement_00;
extern int D_01F72360_amusement_00;
extern Vector4 D_01F72C40_amusement_00;
extern Vector4 D_01F72C50_amusement_00;
extern float D_01F72D98_amusement_00;
extern Amusement00Pair* D_01F728B0_amusement_00;
extern Amusement00Pair* D_01F72960_amusement_00;
extern Amusement00Pair* D_01F72B70_amusement_00;
extern Amusement00Pair* D_01F72DA8_amusement_00;
extern Amusement00Pair* D_01F72DD0_amusement_00;
extern Amusement00Pair* D_01F72DD8_amusement_00;

// General Functions
double func_0012BB10(double, double);
int func_0013D080(int, int, int, int);
void func_0013D250(int, int, float);
void func_0013D280(int);
int func_00151150(int, int);
void func_0015DCD0(float, float, int, Vector4*, int, int);
int func_0015E780(int);
void func_0015E650(void);
int func_0015E850(void);
void func_001602D0(int, int, int, float);
void func_001603E0(int, int);
int func_00163920(short, int);
void func_00164210(void);
float func_001643C0(void);
int func_001646C0(void);
void func_0016CA40(int);
void func_0016D170(int, Vector4*, int, int, float, float, int);
int func_001646D0(void);
int func_001646F0(void);
void func_0016BC00(int);
void func_0016BD90(int, int, float);
void func_0016C1A0(void);
void func_0016C1B0(void);
int func_0016C1C0(int);
int func_0016C540(int*, int*);
int func_0016CB70(void);
void func_0016D0E0(int, int);
int func_0016D240(float, float, int, Vector4*, int, int);
void func_0016DB80(int);
void func_0016DCE0(int);
void func_0016E400(int, int);
void func_0016ECE0(int);
void func_0016F550(int, int);
void func_0016F630(void);
long func_00170810(void);
void func_001908A0(float*, float*);
int func_00190950(void);
float func_00190A20(int);
int func_00190C00(void);
void func_00190C40(void);
void func_0019A940(void);
int func_0019A9B0(float);
void func_0019B4B0(int);
void func_001C18E0(float*);
void func_001C2290(float, int);
int func_001C2580(int);
void func_001EC590(int);
void func_00258910(void);
void func_00316C50(int);

void clAddDynamicWall(int*);
void ItemGet(unsigned int);
int SeCall(int, float, float);
float shRandF(void);

// General Data
extern u_int D_01D31640;
extern u_int D_1D31644;
extern u_int D_1D31648;
extern u_int D_1D3169C;
extern u_int D_1D316AC;

#endif
