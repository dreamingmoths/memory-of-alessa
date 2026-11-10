#ifndef LIB_SH_PAD_H
#define LIB_SH_PAD_H

#include "sh2_common.h"

extern u_short libShPadStep[2][4]; // size: 0x10, address: 0x2B64D0

// We dont have symbols for this TU
void libShPadEnable00(void);

void libShPadEnable10(void);

void libShPadInit(void);

void libShPadStart(int port, int slot);

void libShPadSetMode(int port, int slot, u_int arg2, u_int arg3, u_int arg4, u_int arg5);

u_short libShPadSlotTrans(int port, int slot);

u_short libShPadSlotTransSub(int port, int slot, u_short step);

int libShPadPortTrans(int port);
//@note: ^ last three functions may be static.
int libShPadTrans(void);

s_char libShPadRead(int port, int slot, void* data);

int libShPadSend(int port, int slot, u_short pow0, u_short pow1);
//@note: ^ last two functions are subject to change.

#endif // LIB_SH_PAD_H
