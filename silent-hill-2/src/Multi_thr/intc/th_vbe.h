#ifndef TH_VBE_H
#define TH_VBE_H

#include "sh2_common.h"

int ThreadVbeStart(void* stack, int stackSize, int prio, int option, int wait_sid);

#endif // TH_VBE_H
