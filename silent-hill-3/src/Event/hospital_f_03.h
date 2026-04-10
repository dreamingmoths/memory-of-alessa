#ifndef HOSPITAL_F_03_H
#define HOSPITAL_F_03_H

#include "common.h"

int RoomName(void);
int func_0016BED0(u_int, u_int);
int func_0016C1C0(int);
void func_0016C3C0(void);
void func_0016C540(float *, float *);
void func_0016CA40(int);
void func_00190A20(int);
int func_00190C00(void);
int func_00199C70(int);
void func_00317420(u_int);
void func_00317490(int, float);
void func_003174B0(float);
int func_001DE5B0(int*, int, int);
int SeCall(float, float, int);
int shRandI(void);

extern float D_01F70580_hospital_f_03;
extern float D_01F705E0_hospital_f_03;

extern int D_01F70890_hospital_f_03;
extern int D_01F708D0_hospital_f_03;
extern int D_01F708D8_hospital_f_03;
extern int D_01F708E0_hospital_f_03;
extern int D_01F70908_hospital_f_03;
extern int D_01F70910_hospital_f_03;
extern int func_01F6E650_hospital_f_03;

extern u_int D_01D31640[];
extern u_int D_1D31644;
extern u_int D_1D31680;
extern u_int D_1D31684;
extern u_int D_1D31688;
extern u_int D_1D316F4;
extern u_int D_1D31724;
extern u_int D_1D318E4;

// @hack thanks SeCall :')
/* begin candles, holy rituals to bend SeCall to our will */
#define UNCURSE_HOSPITAL_MOON()                           \
float moon_candle_hospital(float x, float y) {            \
    float charm;                                          \
    float gem;                                            \
    charm *= x;                                           \
    gem *= y;                                             \
    return charm * charm + gem + gem;                     \
}
/* end candles */

#endif
