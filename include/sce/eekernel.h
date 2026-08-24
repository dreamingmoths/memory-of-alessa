#ifndef EE_EEKERNEL_H
#define EE_EEKERNEL_H

#include "common.h"

#define DMAC_VIF0               0
#define DMAC_VIF1               1
#define DMAC_GIF                2
#define DMAC_FROM_IPU           3
#define DMAC_TO_IPU             4
#define DMAC_FROM_SPR           8
#define DMAC_TO_SPR             9

#define ExitHandler()           __asm__ volatile("sync.l; ei")

typedef struct
{
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    u_int attr;
    u_int option;
} SemaParam;

typedef struct ThreadParam {
    int     status;
    void    (*entry)(void *);
    void    *stack;
    int     stackSize;
    void    *gpReg;
    int     initPriority;
    int     currentPriority;
    u_int   attr;
    u_int   option;
    int     waitType;
    int     waitId;
    int     wakeupCount;
} ThreadParam;

int CreateSema(SemaParam* param);
int SignalSema(int);
int iSignalSema(int);
int WaitSema(int);
int DeleteSema(int);
int SetAlarm(u_short, void (*)(int, u_short, void*), void*);
void InvalidDCache(void*, void*);
void SyncDCache(void*, void*);
int StartThread(int, void *arg);
int GetThreadId(void);

#endif
