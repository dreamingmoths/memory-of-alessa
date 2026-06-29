#ifndef VC_UTIL_H
#define VC_UTIL_H

#include "view/vc_main.h"
#include "view/vc_play.h"

void vcInitCamera(VC_ROAD_DATA** roadarray_list);
void vcSetCameraUseWarp(sceVu0FVECTOR chr_pos, float chr_ang_y);
int vcRetCamMvSmoothF(void);
void vcMoveAndSetCamera(int in_connect_f, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcMakeHeroHeadPos(sceVu0FVECTOR head_pos);
void vcAddOfsToPos(sceVu0FVECTOR out_pos, sceVu0FVECTOR in_pos, float ofs_xz_r, float ang_y, float ofs_y);
void vcSetRefPosAndSysRef2CamParam(sceVu0FVECTOR ref_pos, SYS_W* sys_p, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcSetRefPosAndCamPosAngByPad(void);

#endif // VC_UTIL_H
