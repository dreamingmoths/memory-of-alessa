#ifndef TH_VBS_H
#define TH_VBS_H

#include "sh2_common.h"

int ThreadVbsStart(void* stack, int stackSize, int prio, int option, int wait_sid);

#endif // TH_VBS_H
