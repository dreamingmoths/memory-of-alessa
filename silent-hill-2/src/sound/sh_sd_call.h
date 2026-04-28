#ifndef SH_SD_CALL_H
#define SH_SD_CALL_H

#include "common.h"

int shSdInit(void);
int shSdStat(void);
int shSdCall(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */);
void shSd3dAllStop(void);
void shSd3dStop(int i0 /* r16 */);
int shSdSeStop(int i0 /* r16 */);

#endif // SH_SD_CALL_H
