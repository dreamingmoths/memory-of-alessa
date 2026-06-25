#ifndef VW_CALC_H
#define VW_CALC_H

// @todo: check float*/float[] types.
void vwRenewalXZVelocityToTargetPos(float* velo_xz, float* now_pos, float* tgt_pos, float tgt_r, float accel, float total_max_spd, float dec_forwd_lim_spd, float dec_accel_side);
void vwLimitOverLimVector(float* vec_xz, float lim_vec_len, float lim_vec_ang_y);
void vwDecreaseSideOfVector(float* vec_xz, float dec_val, float max_side_vec_len, float dir_ang_y);
float vwRetNewVelocityToTargetVal(float now_spd, float mv_pos, float tgt_pos, float accel, float total_max_spd, float dec_val_lim_spd);
float vwRetNewAngSpdToTargetAng(float now_ang_spd, float now_ang, float tgt_ang, float accel_spd, float total_max_ang_spd, float dec_val_lim_spd);
void vwAngleToVector(float* vec, float* ang, float r);
float vwVectorToAngle(float* ang, float* vec);
int vwOresenHokan(int* y_ary, int y_suu, int input_x, int min_x, int max_x);
void vwRotMatrixYXZ(float* rot, float mat[4]);
void vwMatrixToAngleYXZ(float* ang, float mat[4]);
float vwRet3DLength(float x, float y, float z);

#endif // VW_CALC_H
