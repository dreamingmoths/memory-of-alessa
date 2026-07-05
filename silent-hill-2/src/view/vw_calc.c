#include "vw_calc.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"

#pragma divbyzerocheck off // vwOresenHokan

#line 235
void vwRenewalXZVelocityToTargetPos(sceVu0FVECTOR velo_xz, sceVu0FVECTOR now_pos, sceVu0FVECTOR tgt_pos, float tgt_r, float accel, float total_max_spd, float dec_forwd_lim_spd, float dec_accel_side) {
    sceVu0FVECTOR cam2tgt_dir_vec, vec_xz;
    float spd, lim_spd, add_spd;
    float to_tgt_ang_y, to_tgt_dist;
    float cam_mv_ang_y;
    float cam2tgt_ang_y = shAtan2(tgt_pos[2] - now_pos[2], tgt_pos[0] - now_pos[0]);
    
    shSinCosV(&cam2tgt_dir_vec, cam2tgt_ang_y);

    
    cam_mv_ang_y = shAtanV(velo_xz);

    
    add_spd = accel * shGetDT();
    
    velo_xz[0] += add_spd * cam2tgt_dir_vec[0];
    velo_xz[2] += add_spd * cam2tgt_dir_vec[2];




    
    spd = vec_length(velo_xz);
    
    if (spd > total_max_spd) {
        float ang_y;
        
        ang_y = shAtanV(velo_xz);
        
        velo_xz[0] -= (spd - total_max_spd) * shSinF(ang_y);
        velo_xz[2] -= (spd - total_max_spd) * shCosF(ang_y);
    }









    
    
    vec_sub_xyz(tgt_pos, now_pos, vec_xz);
    
    to_tgt_ang_y = shAtanV(vec_xz);
    to_tgt_dist = vec_length(vec_xz);

    
    lim_spd = dec_forwd_lim_spd * (to_tgt_dist - tgt_r);
    lim_spd = float_max(lim_spd, 0.0f);
    
    vwLimitOverLimVector(velo_xz, lim_spd, to_tgt_ang_y);



    
    vwDecreaseSideOfVector(velo_xz, dec_accel_side * shGetDT(), lim_spd / 2.0f, to_tgt_ang_y);




    
}

#line 320
void vwLimitOverLimVector(sceVu0FVECTOR vec_xz, float lim_vec_len, float lim_vec_ang_y) {
    sceVu0FVECTOR lim_spd_dir_vec_xz;
    float over_spd;

    
    shSinCosV(lim_spd_dir_vec_xz, lim_vec_ang_y);

    
    over_spd = ((vec_xz[0] * lim_spd_dir_vec_xz[0]) + (vec_xz[2] * lim_spd_dir_vec_xz[2])) - lim_vec_len;
    
    
    
    if (over_spd > 0.0f) {
        
        vec_xz[0] -= (over_spd * lim_spd_dir_vec_xz[0]);
        vec_xz[2] -= (over_spd * lim_spd_dir_vec_xz[2]);
    }
}

#line 360
void vwDecreaseSideOfVector(sceVu0FVECTOR vec_xz, float dec_val, float max_side_vec_len, float dir_ang_y) {
    float side_val, sv_val;
    
    sv_val = side_val = (vec_xz[0] * shSinF(dir_ang_y + TO_RAD(90.0f))) + (vec_xz[2] * shCosF(dir_ang_y + TO_RAD(90.0f)));
    
    
    
    side_val = CLAMP(side_val, -max_side_vec_len, max_side_vec_len);
    
    if (side_val > dec_val) side_val -= dec_val;
    else if (side_val < -dec_val) side_val += dec_val;
    else side_val = 0.0f;
    
    vec_xz[0] += (side_val - sv_val) * shSinF(dir_ang_y + TO_RAD(90.0f));
    vec_xz[2] += (side_val - sv_val) * shCosF(dir_ang_y + TO_RAD(90.0f));
}

#line 405
float vwRetNewVelocityToTargetVal(float now_spd, float mv_pos, float tgt_pos, float accel, float total_max_spd, float dec_val_lim_spd) {
    float new_velo;
    float abs_lim_spd;
    float left;

    new_velo = tgt_pos - mv_pos;
    
    if (new_velo >= 0.0f) // removing braces fixes line numbers ?
        left = now_spd + (accel * shGetDT());
    else
        left = now_spd - (accel * shGetDT());

    
    left = CLAMP(left, -total_max_spd, total_max_spd);

    
    abs_lim_spd = dec_val_lim_spd * float_abs(new_velo);
    if (new_velo >= 0.0f) 
        return float_min(left, abs_lim_spd);
    else
        return float_max(left, -abs_lim_spd);

    
}

float vwRetNewAngSpdToTargetAng(float now_ang_spd, float now_ang, float tgt_ang, float accel_spd, float total_max_ang_spd, float dec_val_lim_spd) {
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0.0f, shAngleRegulate(tgt_ang - now_ang) / PI, accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

#line 765
void vwAngleToVector(sceVu0FVECTOR vec, sceVu0FVECTOR ang, float r) {
    float entou_r;

    entou_r = r * shCosF(ang[0]);
    vec[1] = -r * shSinF(ang[0]);
    vec[0] = entou_r * shSinF(ang[1]);
    vec[2] = entou_r * shCosF(ang[1]);
}

INCLUDE_ASM("asm/nonmatchings/view/vw_calc", vwVectorToAngle);

#line 828
int vwOresenHokan(int* y_ary, int y_suu, int input_x, int min_x, int max_x) {
    int amari;    // Remainder when calculating position within interval.
    int kukan_w;  // Width of each interval between Y values.
    int kukan_no; // Index of the interval containing `input_x` angle.
    int output_y; // Interpolated output Y value.

    if (input_x >= max_x)
        output_y = y_ary[y_suu - 1];
    else if (input_x < min_x)
        output_y = y_ary[0];
    else
    {


        
        kukan_w  = (max_x   - min_x) / (y_suu - 1);
        kukan_no = (input_x - min_x) / kukan_w;
        if (kukan_no >= (y_suu - 1))
            output_y = y_ary[y_suu - 1];
        else if (kukan_no < 0)
            output_y = y_ary[0];
        else
        {
            
            amari    = (input_x - min_x) % kukan_w;
            output_y = ((y_ary[kukan_no] * (kukan_w - amari)) + (y_ary[kukan_no + 1] * amari)) / kukan_w;
        }
    }

    
    return output_y;
}

#line 877
void vwRotMatrixYXZ(sceVu0FVECTOR rot, sceVu0FMATRIX mat) {
    
    shRotMatrixZ(mat, mat, rot[2]);
    shRotMatrixX(mat, mat, rot[0]);
    shRotMatrixY(mat, mat, rot[1]);
}

INCLUDE_ASM("asm/nonmatchings/view/vw_calc", vwMatrixToAngleYXZ);

#line 1005
float vwRet3DLength(float x, float y, float z) {
    return SQRT(x * x + y * y + z * z);
}
