#ifndef SH2_SET_DRAWENV_H
#define SH2_SET_DRAWENV_H

#include "GFW/sh2gfw_blockman.h"

void sh2gfw_Set_Brightness(int pow);
void kari_sh2setGS_fogcolor(u_int fr, u_int fg, u_int fb);
void kari_sh2setGS_clearcolor(u_int cr, u_int cg, u_int cb, u_int ca);
void kari_sh2gfw_vu_change(sh2gfw_BLOCK_MAN* bm, u_int light_mode);
int sh2gfw_Rotate_CD11(void);
int sh2gfw_Jump_BlockPos(int mapidno, float* jv);
int sh2gfw_Reset_BlockPos(int mapidno);
void sh2gfw_Set_Fogfar(float fogfar);
void sh2gfw_Set_FogNear(float fogNear);
void sh2gfw_Set_FogMax(float fogMax);
// @bug: it seems this function was missed in the header; see `stg_forest_Ca10_Hakaba_Angela_SetDrawEnv`
/* void sh2gfw_Set_FogMin(float fogMin); */ 
void sh2gfw_Set_DepthFog(float fogfar, float fognear, float fmax, float fmin);
void sh2gfw_Set_DepthFogFAFB(void);
void sh2gde_SetSpot_JmsOrBG(int bg);
void sh2gde_ResetSpot_Jms(void);

#endif // SH2_SET_DRAWENV_H
