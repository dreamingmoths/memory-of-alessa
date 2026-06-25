#ifndef VC_UTIL_H
#define VC_UTIL_H

#include "view/vc_main.h"
#include "view/vc_play.h"

void vcInitCamera(VC_ROAD_DATA** roadarray_list);
void vcSetCameraUseWarp(float* chr_pos, float chr_ang_y);
int vcRetCamMvSmoothF(void);
void vcMoveAndSetCamera(int in_connect_f, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcMakeHeroHeadPos(float* head_pos);
void vcAddOfsToPos(float* out_pos, float* in_pos, float ofs_xz_r, float ang_y, float ofs_y);
void vcSetRefPosAndSysRef2CamParam(float* ref_pos, SYS_W* sys_p, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcSetRefPosAndCamPosAngByPad(void);

#endif // VC_UTIL_H
