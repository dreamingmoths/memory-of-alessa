#ifndef SH2GFW_GS_NEWLOOPENV_H
#define SH2GFW_GS_NEWLOOPENV_H

#include "GFW/sh2_GsAllEnv.h"

extern void sceGsPutDispEnv(sceGsDispEnv* dispenv);

void sh2gfw_setREF_gsctl(Q_WORDDATA* gt);
void sh2gfw_setREF_TEXFLUSH(void);

int sh2gfw_RotateTBuff(shGsAllEnv* shGsEnv /* r16 */);
int sh2gfw_ReturnTBuff(shGsAllEnv* shGsEnv /* r16 */);
int sh2gfw_RotateNext2(shGsAllEnv* stdb /* r16 */);
void sh2gfw_set_LoopDrawEnv(shGsAllEnv* stdb);
u_long128* sh2gfw_Get_FrameNormalRegAddr(void);
u_long128* sh2gfw_Get_FrameAlphaRegAddr(void);
void sh2gfw_StartShadowEnv(shGsAllEnv* stdb /* r16 */);
u_int sh2gfw_GetStencilFBP(shGsAllEnv* stdb);
u_int sh2gfw_GetFilterFBP(shGsAllEnv* stdb, u_int page);
void sh2gfw_StartShadowFilter(shGsAllEnv* stdb /* r17 */, u_int page /* r16 */);
void sh2gfw_ChangeMask_ShadowFilter(shGsAllEnv* stdb, int mode, int pageno);
void sh2gfw_ChangeClear_StencilBuf(shGsAllEnv* stdb, u_int r, u_int g, u_int b, u_int a);
u_int sh2gfw_InclimentLoopCounter(shGsAllEnv* stdb);
u_int sh2gfw_DeclimentLoopCounter(shGsAllEnv* stdb);
int sh2gfw_ForceSet_MovieDrawLoopCounter(void);
u_int sh2gfw_GetNowDispFBP(shGsAllEnv* stdb);
u_int sh2gfw_GetTexTBP0(shGsAllEnv* stdb, u_int page);
u_int sh2gfw_GetSendingClutTBP0(shGsAllEnv* stdb, u_int page);
u_int sh2gfw_Get_BaseTBP0for2D(void);

#endif // SH2GFW_GS_NEWLOOPENV_H