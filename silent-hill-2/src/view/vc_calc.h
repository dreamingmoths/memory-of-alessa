#ifndef VC_CALC_H
#define VC_CALC_H

#include "view/vc_main.h"

// @todo: check float*/float[] types
float vcRetNearRatioSwitchAreaInXZPos(VC_NEAR_ROAD_DATA cur_near_road, sceVu0FVECTOR chr_pos, sceVu0FVECTOR cam_tgt_pos);
float vcRetNearRatioSwitchAreaForCircleCam(VC_NEAR_ROAD_DATA cur_near_road, VC_CIR_CAM_MANAGER cir_man, sceVu0FVECTOR chr_pos);
void vcTransRotRoadArea(sceVu0FVECTOR v0, sceVu0FMATRIX m, sceVu0FVECTOR v1);
void vcRotTransRoadArea(sceVu0FVECTOR v0, sceVu0FMATRIX m, sceVu0FVECTOR v1);
float vcGetMinInRoadDist(void);
void vcConvertCamFile(VC_ROAD_DATA* road_ary);

#endif // VC_CALC_H
