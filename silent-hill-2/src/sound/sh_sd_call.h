#ifndef SH_SD_CALL_H
#define SH_SD_CALL_H

#include "common.h"

int shSdInit(void);
void shSdVSync(void);
int shSdCall(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */);
int shSdSeStop(int i0 /* r16 */);
int shSdStat(void);
int shSd3dCall(int i0 /* r18 */, int i1 /* r17 */, int i2 /* r16 */, float f0 /* r21 */, float f1 /* r20 */);
int shSd3dMove(int i0 /* r18 */, int i1 /* r17 */, int i2 /* r16 */, float f0 /* r21 */, float f1 /* r20 */);
void shSd3dStop(int i0 /* r16 */);
void shSd3dAllStop(void);
int shSdSeChange(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */);
int shSdTrack(int i0 /* r17 */, int i1 /* r16 */);
int shSdRadio(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */);
void* shSd3dAdrs(void);

#endif // SH_SD_CALL_H
