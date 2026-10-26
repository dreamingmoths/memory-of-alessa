#ifndef EN_INSECT_H
#define EN_INSECT_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

void enINSInitData(EnLOCAL_DATA* dp);

void enSetInsect(float* pos, int num);

void enKillAllInsect(void);

void enWaitAllInsect(void);

SubCharacter* enINSGetSubCharacter(EnLOCAL_DATA* dp);

void enINSCtrlMain(EnLOCAL_DATA* dp);

#endif // EN_INSECT_H
