#ifndef SH2GFW_GSINIT_H
#define SH2GFW_GSINIT_H

#include "GFW/sh2_GsAllEnv.h"

int printf(const char* fmt, ...);

void shGs_InitDefTBuff(shGsAllEnv* shGsEnv /* r22 */, short draw_psm /* r21 */, short disp_psm /* r23 */, short w /* r20 */, short h /* r19 */, short ztest /* r18 */, short zpsm /* r17 */);
void shGs_TrimDispArea(int xx, int yy);
void shGs_SetDefaultDispArea(void);
void shGsSetDefTBuffDispEnv(sceGsDispEnv* disp /* r21 */, short psm /* r20 */, short w /* r16 */, short h /* r19 */, short dx /* r18 */, short dy /* r17 */);
int shGsSetDefTBuffDrawEnv(sceGsDrawEnv1* draw, short psm, short w, short h, short ztest, short zpsm);
void shGs_InitGsStencilBuff(shGsAllEnv* shGsEnv /* r17 */, short w /* r16 */, short h /* r21 */, short ztest /* r20 */, short zpsm /* r19 */);
int shGs_InitStencilDrawEnv(shGsStencilDrawEnv* ssb, short w, short h, short ztest, short zpsm);
void shGs_InitGsTinyStencilBuff(shGsAllEnv* shGsEnv, short w, short h);
void shGs_InitDefaultRegsEnv(shGsAllEnv* shGsEnv);

#endif // SH2GFW_GSINIT_H