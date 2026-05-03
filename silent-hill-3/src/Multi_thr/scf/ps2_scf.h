#ifndef PS2_SCF_H
#define PS2_SCF_H

#include "libscf.h"

void ps2ScfInit(void);


int ps2ScfGetAspect(void);


int ps2ScfGetSpdif(void);


int ps2ScfGetLanguage(void);


int func_0020EC10(int arg0);


int ps2ScfGetTimeZone(void);

int func_0020ECA0(void);


int func_0020ECF0(void);


int func_0020ED40(void);

void ps2ScfGetLocalTimefromRTC(sceCdCLOCK* rtc);


#endif
