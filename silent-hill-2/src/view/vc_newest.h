#ifndef VC_NEWEST_H
#define VC_NEWEST_H

#include "view/vc_main.h"

void vcEndProcessingVC_WORK(void);
void vcEndProcessingOldNearRoad(VC_NEAR_ROAD_DATA* near_rd_p, VC_WORK* w_p);
void vcCorrectCamMatAngForcibly(sceVu0FVECTOR ofs_cam_ang, VC_ROAD_DATA* road_ary);
void vcWarpForFixAngCam(VC_WORK* v_p);
float vcRetCirRadiusReduction(VC_WORK* w_p);
void vcChangeProjByDist(VC_NEAR_ROAD_DATA* near_rd_p, float mv_vec_y);

#endif // VC_NEWEST_H
