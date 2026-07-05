#ifndef VW_CALC_H
#define VW_CALC_H

#include "vc_main.h"

void vwRenewalXZVelocityToTargetPos(sceVu0FVECTOR velo_xz, sceVu0FVECTOR now_pos, sceVu0FVECTOR tgt_pos, float tgt_r, float accel, float total_max_spd, float dec_forwd_lim_spd, float dec_accel_side);
void vwLimitOverLimVector(sceVu0FVECTOR vec_xz, float lim_vec_len, float lim_vec_ang_y);
void vwDecreaseSideOfVector(sceVu0FVECTOR vec_xz, float dec_val, float max_side_vec_len, float dir_ang_y);
float vwRetNewVelocityToTargetVal(float now_spd, float mv_pos, float tgt_pos, float accel, float total_max_spd, float dec_val_lim_spd);
float vwRetNewAngSpdToTargetAng(float now_ang_spd, float now_ang, float tgt_ang, float accel_spd, float total_max_ang_spd, float dec_val_lim_spd);
void vwAngleToVector(sceVu0FVECTOR vec, sceVu0FVECTOR ang, float r);
float vwVectorToAngle(sceVu0FVECTOR ang, sceVu0FVECTOR vec);
int vwOresenHokan(int* y_ary, int y_suu, int input_x, int min_x, int max_x);
void vwRotMatrixYXZ(sceVu0FVECTOR rot, sceVu0FMATRIX mat);
void vwMatrixToAngleYXZ(sceVu0FVECTOR ang, sceVu0FMATRIX mat);
float vwRet3DLength(float x, float y, float z);

#endif // VW_CALC_H
