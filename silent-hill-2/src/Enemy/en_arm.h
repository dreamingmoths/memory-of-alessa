#ifndef EN_ARM_H
#define EN_ARM_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

void enARMInitData(EnLOCAL_DATA* dp);
void enARMCtrlMain(EnLOCAL_DATA* dp);
void enARMGetHandPos(float* vec, EnLOCAL_DATA* dp, int d);

#endif // EN_ARM_H
