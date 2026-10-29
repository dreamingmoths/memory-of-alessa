#ifndef PS2_SCF_H
#define PS2_SCF_H

#include "sh2_common.h"
#include "sce/eekernel.h"
#include "sce/libscf.h"

void ps2ScfInit(void);

int ps2ScfGetLanguage(void);

int ps2ScfGetAspect(void);

int ps2ScfGetSpdif(void);

int ps2ScfGetTimeZone(void);

int ps2ScfGetDateNotation(void);

int ps2ScfGetSummerTime(void);

int ps2ScfGetTimeNotation(void);

void ps2ScfGetLocalTimefromRTC(sceCdCLOCK* rtc);

#endif // PS2_SCF_H
