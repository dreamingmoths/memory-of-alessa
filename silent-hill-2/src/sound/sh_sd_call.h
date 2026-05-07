#ifndef SH_SD_CALL_H
#define SH_SD_CALL_H

#include "common.h"

// @todo: find a home for these

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_stat(void);

// M:\select\sound\sd0712\ee\sd_call.c
extern void sd_vsync(void);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_call(int call /* r19 */, int direct /* r18 */, int dist /* r17 */, int pitch /* r16 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_se_stop(int call /* r2 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_stat(void);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_3d_call(int call /* r2 */, int arg1 /* r2 */, int arg2 /* r2 */, float arg3 /* r29+0x10 */, float arg4 /* r29+0x10 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern void* sd_3d_adrs(void);

// M:\select\sound\sd0712\ee\sd_call.c
extern void sd_3d_allstop(void);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_3d_move(int no /* r2 */, int arg1 /* r2 */, int arg2 /* r2 */, float arg3 /* r29 */, float arg4); // arg4 was not present in the dwarf

// M:\select\sound\sd0712\ee\sd_call.c
extern void sd_3d_stop(int no /* r2 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_radio(int ch /* r2 */, int vol /* r2 */, int pan /* r2 */, int pitch /* r2 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_se_change(int call /* r2 */, int direct /* r2 */, int dist /* r2 */, int pitch /* r2 */);

// M:\select\sound\sd0712\ee\sd_call.c
extern int sd_track(int track /* r2 */, int vol /* r2 */);

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
