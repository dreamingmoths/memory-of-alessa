#include "vc_newest.h"
#include "vec.h"
#include "SH2_common/sh_vu0.h"

#line 25
void vcEndProcessingVC_WORK(void) {
    vcWork.flags &= ~VC_SWITCH_NEAR_RD_DATA_F;

    vcWork.flags &= ~VC_ALL_WARP_FLAGS;

    vcWork.through_door_activate_init_f = 0;
}

// Symbols only show one arg to this? (`near_rd_p` is guess)
#line 40
void vcEndProcessingOldNearRoad(VC_NEAR_ROAD_DATA* near_rd_p, VC_WORK* w_p) {
    if (w_p->fix_man.exception_f) {
        w_p->fix_man.exception_f = 0;
    }
}

// @todo: weird line numbering in this func.
void vcCorrectCamMatAngForcibly(sceVu0FVECTOR ofs_cam_ang, VC_ROAD_DATA* road_ary) {
    float ofs_lr_lim_ang_y;
    float ofs_rr_lim_ang_y;
    float deflt_lr_lim_ang_y;
    float deflt_rr_lim_ang_y;
    VC_ROAD_DATA rd_data;

    rd_data = *road_ary;

    switch (rd_data.cam_mv_type) {
        case VC_MV_CHASE:
            if (rd_data.flags & VC_RD_CAM_LIKE_SETTLE_F) {
                deflt_lr_lim_ang_y = rd_data.tmp.chs.lr_lim_ang_y;
                deflt_rr_lim_ang_y = rd_data.tmp.chs.rr_lim_ang_y;
            } else {
                return;
            }
            break;

        case VC_MV_SETTLE:
            deflt_lr_lim_ang_y = rd_data.tmp.stl.lr_lim_ang_y;
            deflt_rr_lim_ang_y = rd_data.tmp.stl.rr_lim_ang_y;
            break;

        default:
            return;
    }

    if (deflt_lr_lim_ang_y != -TO_RAD(999.9f) || deflt_rr_lim_ang_y != TO_RAD(999.9f)) {
        ofs_lr_lim_ang_y = shAngleRegulate(ofs_cam_ang[1] - deflt_lr_lim_ang_y);
        ofs_rr_lim_ang_y = shAngleRegulate(ofs_cam_ang[1] - deflt_rr_lim_ang_y);
        if (ofs_lr_lim_ang_y >= 0.0f && ofs_rr_lim_ang_y <= 0.0f) {
            ofs_cam_ang[1] = shAngleRegulate(ofs_cam_ang[1]);
        } else if (float_abs(ofs_lr_lim_ang_y) < float_abs(ofs_rr_lim_ang_y)) {
            ofs_cam_ang[1] = shAngleRegulate(deflt_lr_lim_ang_y);
        } else {
            ofs_cam_ang[1] = shAngleRegulate(deflt_rr_lim_ang_y);
        }
    }
}

#line 106
void vcWarpForFixAngCam(VC_WORK* v_p) {
    float ofs_ang_y;
    float actual_ang_y;

#line 125
    ofs_ang_y = shAngleRegulate(v_p->cur_near_road.road_p->tmp.chs.ratio_r_xz + v_p->fix_man.add_ang_y);

#line 130
    actual_ang_y = float_abs(shAngleRegulate(v_p->chara_eye_ang_y - ofs_ang_y));


    if (actual_ang_y >= TO_RAD(135.0f) && v_p->cur_near_road.road_p->kind_id == 1) {


        vcWork.flags |= VC_ALL_WARP_FLAGS;

#line 175
        v_p->fix_man.exception_f = v_p->fix_man.exception_f ? 0 : 1;


        if (v_p->fix_man.exception_f != 0) v_p->fix_man.add_ang_y += PI;
        else v_p->fix_man.add_ang_y -= PI;

        switch (v_p->cur_near_road.rd_dir_type) {
            case 0:
                if (TO_RAD(-90.0f) <= ofs_ang_y && ofs_ang_y < TO_RAD(90.0f)) {
                    v_p->fix_man.add_rd_z += 800.0f;
                } else {
                    v_p->fix_man.add_rd_z -= 800.0f;
                }
                break;
            case 1:
                if (ofs_ang_y > 0.0f) {
                    v_p->fix_man.add_rd_x += 800.0f;
                } else {
                    v_p->fix_man.add_rd_x -= 800.0f;
                }
                break;
        }



    }
}

// @todo: Likely a static in vcRetCirRadiusReduction (vc_main.c also seems to have a separate `far_tgt_watch_cir_r_0x003905C0` var.)
extern float far_tgt_watch_cir_r_0x00399F40[];

#line 210
float vcRetCirRadiusReduction(VC_WORK* w_p) {
    float real_r;
    float deflt_r;
    float cam2chr_xz_dist;
    float ofs_ang_y;
    float x;
    float z;
    float rate;
    cam2chr_xz_dist = vec3_dist_xz(w_p->chara_pos, w_p->cam_pos);
    cam2chr_xz_dist /= 2.0f;
    ofs_ang_y = shAtan2(w_p->chara_pos[2] - w_p->cam_pos[2],
                        w_p->chara_pos[0] - w_p->cam_pos[0]);



    deflt_r = far_tgt_watch_cir_r_0x00399F40[w_p->cur_near_road.road_p->area_size_type];



    z = cam2chr_xz_dist * shSinF(ofs_ang_y) + deflt_r * shSinF(w_p->chara_eye_ang_y);


    x = cam2chr_xz_dist * shCosF(ofs_ang_y) + deflt_r * shCosF(w_p->chara_eye_ang_y);



    real_r = SQRT(z * z + x * x);

    rate = float_abs(shAngleRegulate(w_p->chara_eye_ang_y - ofs_ang_y) / PI);




    rate = 1.0f - rate;

    return real_r * rate;
}

#line 255
void vcChangeProjByDist(VC_NEAR_ROAD_DATA* near_rd_p, float mv_vec_y) {
    if ((VC_AREA_SIZE_TYPE)near_rd_p->road_p->area_size_type == VC_AREA_OUTDOOR &&
        (near_rd_p->road_p->mv_y_type == VC_MV_LOCUS_CIRCLE || near_rd_p->road_p->mv_y_type == VC_MV_THROUGH_DOOR)) {



        near_rd_p->road_p->projection = 448.0f + (1.2f * float_abs(-1375.0f - mv_vec_y));



        vcSetProjectionValue(near_rd_p->road_p->projection, 0);
    }
}
