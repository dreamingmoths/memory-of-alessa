#ifndef EE_EEKERNEL_H
#define EE_EEKERNEL_H

#include "common.h"

typedef struct
{
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    u_int attr;
    u_int option;
} SemaParam;

int CreateSema(SemaParam *param);
int SignalSema(int);
int iSignalSema(int);
int WaitSema(int);
int DeleteSema(int);

#endif
