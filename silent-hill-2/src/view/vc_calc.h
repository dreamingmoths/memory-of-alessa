#ifndef VC_CALC_H
#define VC_CALC_H

#include "view/vc_main.h"

// @todo: check float*/float[] types
float vcRetNearRatioSwitchAreaInXZPos(float* chr_pos, float* cam_tgt_pos);
float vcRetNearRatioSwitchAreaForCircleCam(float* chr_pos);
void vcTransRotRoadArea(float* v0, float m[4], float* v1);
void vcRotTransRoadArea(float* v0, float m[4], float* v1);
float vcGetMinInRoadDist(void);
void vcConvertCamFile(VC_ROAD_DATA* road_ary);

#endif // VC_CALC_H
