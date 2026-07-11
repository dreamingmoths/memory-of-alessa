#include "vc_main.h"
#include "vb_main.h"
#include "vc_calc.h"
#include "vc_newest.h"
#include "vc_play.h"
#include "vc_prio.h"
#include "vw_calc.h"
#include "Chacter/sh_character_status.h"
#include "Event/event.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"

const VC_WATCH_MV_PARAM watch_mv_prm_user = {7.539823f, 13.823008f, 1.3823007f, 4.3982296f};

const VC_WATCH_MV_PARAM watch_mv_prm_nrml = {6.031858f, 11.058406f, 1.1058406f, 3.5185838f};

const VC_WATCH_MV_PARAM watch_mv_prm_outdoor = {8.4822998f, 15.550882f, 1.5550883f, 4.9480085f};

const VC_WATCH_MV_PARAM watch_mv_prm_on_boat = {2.2619469f, 4.1469026f, 1.1058406f, 3.5185838f};

const VC_WATCH_MV_PARAM self_view_watch_mv_prm = {10.555752f, 19.352209f, 2.7646015f, 8.796459f};

const VC_CAM_MV_PARAM cam_mv_prm_user = {5000.0f, 1500.0f, 3000.0f, 1000.0f};

const VC_CAM_MV_PARAM cam_mv_prm_nrml = {4000.0f, 1500.0f, 2400.0f, 1000.0f};

const VC_CAM_MV_PARAM cam_mv_prm_outdoor = {5625.0f, 1687.5f, 3375.0f, 1125.0f};

const VC_CAM_MV_PARAM cam_mv_prm_on_boat = {1500.0f, 450.0f, 2400.0f, 800.0f};

const float nml_tgt_watch_cir_r[4] = {400.0f, 600.0f, 1000.0f, 1200.0f};

const float nml_cam2wth_min_dist[4] = {1400.0f, 1800.0f, 2800.0f, 3200.0f};

const float far_tgt_watch_cir_r_0x003905C0[4] = {1600.0f, 2800.0f, 5000.0f, 6000.0f};

const float mv_nml_chr2cam_r[4] = {600.0f, 800.0f, 1000.0f, 1250.0f};

const float mv_nml_no_adj_max_dist[4] = {400.0f, 600.0f, 800.0f, 1000.0f};

const float mv_nml_full_adj_min_dist[4] = {1200.0f, 1600.0f, 2400.0f, 2800.0f};

const float extra_boundary_width[4] = {75.0f, 125.0f, 175.0f, 250.0f};

const float excl_max_rate[4] = {0.7f, 0.85f, 0.95f, 1.0f};

#line 364
void vcInitVCSystem(VC_ROAD_DATA** vc_road_ary_list) {
    vcWork.view_cam_active_f = 0;


    
    if (vc_road_ary_list == NULL) {
        vcWork.vc_road_ary_list = vcNullRoadArrayList;
    } else {
        vcWork.vc_road_ary_list = vc_road_ary_list;
    }









    

    
    
    vcWork.cur_near_road = vcNullNearRoad;
    vcWork.old_cam_excl_area_r = -1.0f;
    vcWork.watch_tgt_max_y = 50000.0f;
    
    vcSelfViewTimer = 0.0f;

    
    vcWatchMvPrmSt.ang_accel_x = 0.0f;
    vcWatchMvPrmSt.ang_accel_y = 0.0f;
    vcWatchMvPrmSt.max_ang_spd_x = 0.0f;
    vcWatchMvPrmSt.max_ang_spd_y = 0.0f;
    
    vcCamMvPrmSt.accel_xz = 0.0f;
    vcCamMvPrmSt.accel_y = 0.0f;
    vcCamMvPrmSt.max_spd_xz = 0.0f;
    vcCamMvPrmSt.max_spd_y = 0.0f;
}

#line 420
void vcStartCameraSystem(void) {
    vcWork.view_cam_active_f = 1;
}

#line 506
void vcSetFirstCamWork(sceVu0FVECTOR cam_pos, float chara_eye_ang_y, int use_through_door_cam_f) {
    vec_zero(vcWork.ofs_cam_ang_spd);
    
    vcWork.flags = VC_ALL_WARP_FLAGS;

    
    vec_copy(vcWork.cam_pos, cam_pos);
    vcWork.cam_mv_ang_y = 0.0f;
    vec_zero(vcWork.cam_velo);
    vec_copy(vcWork.cam_tgt_pos, cam_pos);
    vec_zero(vcWork.cam_tgt_velo);
    vcWork.cam_mv_ang_y = 0.0f;
    vcWork.cam_tgt_spd = 0.0f;
    vcWork.cam_chara2ideal_ang_y = shAngleRegulate(chara_eye_ang_y + TO_RAD(180.0f));
    
    vcWork.cur_near_road = vcNullNearRoad;

    
    vcWork.through_door_activate_init_f = use_through_door_cam_f;
    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_END);


    
}

#line 604
void vcUserWatchTarget(sceVu0FVECTOR watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, float rot_z, int warp_watch_f) {
    vcWork.flags &= ~(VC_USER_WATCH_F | VC_VISIBLE_CHARA_F);
    
    vcWork.flags |= VC_USER_WATCH_F;

    
    if (warp_watch_f) vcWork.flags |= VC_WARP_WATCH_F;

    
    vec_copy(vcWork.watch_tgt_pos, watch_tgt_pos);

    
    vcWork.watch_tgt_ang_z = rot_z;

    
    if (watch_prm_p == NULL) {
        vcWork.user_watch_mv_prm = watch_mv_prm_user;
    } else {
        vcWork.user_watch_mv_prm = *watch_prm_p;
    }
}

#line 650
void vcUserCamTarget(sceVu0FVECTOR cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, int warp_cam_f) {
    vcWork.flags &= ~(VC_USER_CAM_F | VC_WARP_CAM_F);
    
    vcWork.flags |= VC_USER_CAM_F;
    if (warp_cam_f) vcWork.flags |= VC_WARP_CAM_F;

    
    vec_copy(vcWork.cam_tgt_pos, cam_tgt_pos);

    
    if (cam_prm_p == NULL) {
        vcWork.user_cam_mv_prm = cam_mv_prm_user;
    } else {
        vcWork.user_cam_mv_prm = *cam_prm_p;
    }
}

#line 682
void vcGetNowWatchPos(sceVu0FVECTOR watch_pos) {
    float cos_x;
    float sin_x;
    float cos_y;
    float sin_y;
    float r;

















    
    cos_x = shCosF(vcWork.cam_mat_ang[0]);
    sin_x = shSinF(vcWork.cam_mat_ang[0]);
    cos_y = shCosF(vcWork.cam_mat_ang[1]);
    sin_y = shSinF(vcWork.cam_mat_ang[1]);

    r = vec3_dist_reverse(vcWork.watch_tgt_pos, vcWork.cam_pos);

    
    watch_pos[0] = vcWork.cam_pos[0] + (cos_x * (r * sin_y));
    watch_pos[2] = vcWork.cam_pos[2] + (cos_x * (r * cos_y));
    watch_pos[1] = vcWork.cam_pos[1] - (r * sin_x);
    
}

#line 738
void vcGetNowCamPos(sceVu0FVECTOR cam_pos) {
    vec_copy(cam_pos, vcWork.cam_pos);
    
}

#line 759
void vcReturnPreAutoCamWork(int warp_f) {
    if (warp_f) vcWork.flags |= VC_ALL_WARP_FLAGS;
    
    vcWork.flags &= ~(VC_USER_CAM_F | VC_USER_WATCH_F);
    
    vcSetProjectionValue(vcWork.cur_near_road.road_p->projection, 0);
}

#line 802
void vcSetSubjChara(sceVu0FVECTOR chara_pos, float chara_bottom_y, float chara_top_y, float chara_grnd_y, sceVu0FVECTOR chara_head_pos, float chara_mv_spd, float chara_mv_ang_y, float chara_ang_spd_y, float chara_eye_ang_y, float chara_eye_ang_wy, float chara_watch_xz_r) {
    vec_copy(vcWork.chara_pos, chara_pos);
    vcWork.chara_bottom_y = chara_bottom_y;
    vcWork.chara_top_y = chara_top_y;
    vcWork.chara_center_y = (chara_bottom_y + chara_top_y) / 2.0f;
    vcWork.chara_grnd_y = chara_grnd_y;
    vec_copy(vcWork.chara_head_pos, chara_head_pos);
    vcWork.chara_mv_spd = chara_mv_spd;
    vcWork.chara_mv_ang_y = chara_mv_ang_y;
    vcWork.chara_ang_spd_y = chara_ang_spd_y;
    vcWork.chara_eye_ang_y = chara_eye_ang_y;
    vcWork.chara_eye_ang_wy = chara_eye_ang_wy;
    vcWork.chara_watch_xz_r = chara_watch_xz_r;
}

#line 833
int vcExecCamera(void) {
	VC_ROAD_FLAGS cur_rd_flags;
	VC_CAM_MV_TYPE cur_cam_mv_type;
	u_char cur_rd_area_size; // Type should be VC_AREA_SIZE_TYPE but causes mismatch..
	float far_watch_rate, self_view_eff_rate;
	sceVu0FVECTOR sv_old_cam_pos, sv_old_cam_mat_ang;
	VC_WATCH_MV_PARAM* watch_mv_prm_p;
	VC_CAM_MV_PARAM* cam_mv_prm_p;
    int warp_f, smooth_f; // smooth_f is unused?
    vec_copy_reverse(vcWork.cam_pos, sv_old_cam_pos);
    vec_copy_reverse(vcWork.cam_mat_ang, sv_old_cam_mat_ang);
    
    if (vcWork.view_cam_active_f == 0) return 0;
    
    vcSetAllNpcDeadTimer();


    
    vcPreSetDataInVC_WORK(&vcWork, vcWork.vc_road_ary_list);







    
    warp_f = vcSetCurNearRoadInVC_WORK(&vcWork);
    
    ASSERT(vcWork.cur_near_road.road_p != 0L);

    
    cur_rd_flags = vcWork.cur_near_road.road_p->flags;
    cur_rd_area_size = vcWork.cur_near_road.road_p->area_size_type;
    
    cur_cam_mv_type = vcRetCurCamMvType(&vcWork);
    
    far_watch_rate = vcRetFarWatchRate(vcWork.flags & VC_PRS_F_VIEW_F, cur_cam_mv_type, &vcWork);
    
    self_view_eff_rate = vcRetSelfViewEffectRate(cur_cam_mv_type, far_watch_rate, &vcWork);

    
    if (!(vcWork.flags & (VC_USER_CAM_F | VC_USER_WATCH_F))) {
        vcSetFlagsByCamMvType(cur_cam_mv_type, far_watch_rate, warp_f);
    }
    if (vcWork.flags & VC_WARP_CAM_TGT_F) {
        vcWork.old_cam_excl_area_r = -1.0f;
    }





    
    vcGetUseWatchAndCamMvParam(&watch_mv_prm_p, &cam_mv_prm_p, self_view_eff_rate, far_watch_rate, &vcWork);



    
    if (!(vcWork.flags & VC_USER_CAM_F)) {
        vcAutoRenewalCamTgtPos(&vcWork, cur_cam_mv_type, cam_mv_prm_p, cur_rd_flags, cur_rd_area_size, far_watch_rate);
    }



    
    vcRenewalCamData(&vcWork, cam_mv_prm_p);

    
    if (!(vcWork.flags & VC_USER_CAM_F)) {
        
        vcChangeProjectionValue(&vcWork);
    }
    if (!(vcWork.flags & VC_USER_WATCH_F)) {
        
        vcAutoRenewalWatchTgtPosAndAngZ(&vcWork, cur_cam_mv_type, cur_rd_area_size, far_watch_rate, self_view_eff_rate);
        
        
        
        
        if ((vcWork.cur_near_road.road_p->flags & VC_RD_LIM_UP_FAR_VIEW_F) && (vcWork.cur_near_road.road_p->cam_mv_type == 0 || cur_cam_mv_type == VC_MV_SELF_VIEW)) {
            
            
            
            
            
            vcAdjustWatchYLimitHighWhenFarView(vcWork.watch_tgt_pos, vcWork.cam_pos);
        }
    }

    
    vcRenewalCamMatAng(&vcWork, watch_mv_prm_p, cur_cam_mv_type, vcWork.flags & VC_VISIBLE_CHARA_F);
    
    
    
    
    
    
    vcSetDataToVwSystem(&vcWork, cur_cam_mv_type);
    
    
    vcEndProcessingVC_WORK();






    
    // big gap, commented out code? (maybe uses the unused `smooth_f`)







    
    return vcRetSmoothCamMvF(sv_old_cam_pos, vcWork.cam_pos, sv_old_cam_mat_ang, vcWork.cam_mat_ang);












}

const u_char unkPadding_00390668[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // @hack: Weird padding after ASSERT strings.

#line 981
void vcSetAllNpcDeadTimer(void) {
    SubCharacter* sc_p;
    int i;

    for(i = 0; i < 20; i++) {
        sc_p = shCameraGetNearTarget(i, 0);
        if (sc_p != NULL) {
            
            if (sc_p->battle.status & 2)
                sc_p->battle.dead_timer += shGetDT();
            else
                sc_p->battle.dead_timer = 0.0f;
            
            if (sc_p->battle.dead_timer > 10.0f) sc_p->battle.dead_timer = 10.0f;
        }
    }
}

#line 1023
int vcRetSmoothCamMvF(sceVu0FVECTOR old_pos, sceVu0FVECTOR now_pos, sceVu0FVECTOR old_ang, sceVu0FVECTOR now_ang) {
    int intrpt;
    float rot_y;
    float rot_x;
    float mv_vec;

    intrpt = shGetDF();
    intrpt = CLAMP(intrpt, 1.0f, 4.0f);
















    





    mv_vec = vec3_dist(now_pos, old_pos) / (float)intrpt;

    
    if (mv_vec > 100.0f) return 0;

    
    rot_x = float_abs(now_ang[0] - old_ang[0]) / (float)intrpt;
    
    if (rot_x > TO_RAD(20.0f)) return 0;
    
    rot_y = float_abs(shAngleRegulate(now_ang[1] - old_ang[1])) / (float)intrpt;
    rot_y = rot_y * shCosF(now_ang[0]);
    
    if (rot_y > TO_RAD(30.0f)) return 0;

    
    return 1;
}

#line 1087
VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p) {
    if (w_p->through_door.active_f) {
        if (!vcRetThroughDoorCamEndF(w_p)) {
            return VC_MV_THROUGH_DOOR;
        }
        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(w_p, VC_TDSC_END);
    }


    
    return w_p->cur_near_road.road_p->cam_mv_type;
}

#line 1115
int vcRetThroughDoorCamEndF(VC_WORK* w_p) {
    VC_THROUGH_DOOR_CAM_PARAM* prm_p;
    float rail2chara_dist;
    float abs_ofs_ang_y;
    prm_p = &w_p->through_door;
    rail2chara_dist = prm_p->rail_sta_to_chara_dist;
    
    if (!prm_p->active_f) return 1;
    
    if (prm_p->timer > 1.2f && (w_p->nearest_enemy_xz_dist < 600.0f)) {


        
        return 1;
    }
    
    if (rail2chara_dist > 800.0f) {
        
        return 1;
    } else if (rail2chara_dist > 250.0f) {


        
        abs_ofs_ang_y = float_abs(
            shAngleRegulate(w_p->chara_eye_ang_y - 
                            shAtan2(w_p->chara_pos[2] - w_p->through_door.rail_sta_pos[2], 
                                    w_p->chara_pos[0] - w_p->through_door.rail_sta_pos[0])));
        
        
        
        
        
        
        
        
        if (abs_ofs_ang_y > TO_RAD(70.0f)) return 1;
    }

    
    return 0;
}

#line 1176
float vcRetFarWatchRate(int far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p) {
    float far_watch_rate;

    if ((vcWork.flags & (VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)) | (w_p->cur_near_road.road_p->flags & VC_RD_INVALID_SV_F)) {

        
        far_watch_rate = 0.0f;
    } else
        switch (cur_cam_mv_type) {
            case 2:
                far_watch_rate = 0.0f;
                if (far_watch_button_prs_f && BgIsOut(0) == 0)
                    vcWarpForFixAngCam(w_p);
                break;
            case 3:
                far_watch_rate = 0.0f;
                break;
            case 0:
            case 1:
            case 4:
                if (far_watch_button_prs_f) far_watch_rate = 1.0f;
                else far_watch_rate = 0.0f;
                break;
            case 5:
                if (far_watch_button_prs_f) far_watch_rate = 1.0f;


                    
                else {
                    float dist = w_p->through_door.rail_sta_to_chara_dist;
                    
                    far_watch_rate = 0.9f - (dist * 0.9f) / 800.0f;


                    
                    far_watch_rate = float_max(far_watch_rate, 0.0f);
                    
                    if (w_p->through_door.rail_sta_to_chara_dist > 250.0f) {




                        
                        float abs_ofs_ang_y = float_abs(shAngleRegulate(w_p->chara_eye_ang_y - shAtan2(w_p->chara_pos[2] - w_p->through_door.rail_sta_pos[2], w_p->chara_pos[0] - w_p->through_door.rail_sta_pos[0])));
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        far_watch_rate = (far_watch_rate * (TO_RAD(70.0f) - abs_ofs_ang_y)) / (TO_RAD(70.0f));
                        
                        
                        
                        far_watch_rate = float_max(far_watch_rate, 0.0f);
                    }
                }
                break;
            
            default: ASSERT(0);
        }


    
    return far_watch_rate;
}

#line 1264
float vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, float far_watch_rate, VC_WORK* w_p) {
    float ret_eff_rate;
    float xyz_dist;
    float max_rate;
    float mul_rate;

    if (cur_cam_mv_type != VC_MV_THROUGH_DOOR && cur_cam_mv_type != VC_MV_SELF_VIEW) {
        return 0.0f;
    }








    
    if (cur_cam_mv_type == VC_MV_SELF_VIEW) max_rate = 1.0f;
    else max_rate = 0.35f;





















    
    xyz_dist = vec3_dist(w_p->cam_pos, w_p->chara_head_pos);

    
    if (xyz_dist < 250.0f) ret_eff_rate = max_rate;
    else if (xyz_dist > 600.0f) ret_eff_rate = 0.0f;
    else {
        ret_eff_rate = (max_rate * (600.0f - xyz_dist)) / 350.0f;
    }






    

    if (w_p->nearest_enemy_xz_dist > 2000.0f) {
        mul_rate = 1.0f;
    } else if (w_p->nearest_enemy_xz_dist < 1000.0f) {
        mul_rate = 0.0f;
    } else {
        mul_rate = (w_p->nearest_enemy_xz_dist - 1000.0f) / 1000.0f;
    }
    

    ret_eff_rate = ret_eff_rate * mul_rate;



    
    ret_eff_rate = CLAMP(ret_eff_rate, 0.0f, max_rate);


    
    return ret_eff_rate;
}

#line 1362 
void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, float far_watch_rate, int all_warp_f) {

    if (far_watch_rate != 0.0f)
        
        vcWork.flags &= ~VC_VISIBLE_CHARA_F;
    else {
        switch (cam_mv_type) {
            case VC_MV_CHASE:
            case VC_MV_SETTLE:
            case VC_MV_LOCUS_CIRCLE:
                vcWork.flags |= VC_VISIBLE_CHARA_F;
                break;
            case VC_MV_FIX_ANG:
            case VC_MV_SELF_VIEW:
            case VC_MV_THROUGH_DOOR:
                vcWork.flags &= ~VC_VISIBLE_CHARA_F;
                break;
            default: ASSERT(0);
        }
    }

    
    if (cam_mv_type == VC_MV_SELF_VIEW)
        vcWork.flags |= VC_WARP_CAM_F | VC_WARP_CAM_TGT_F;
    
    if (all_warp_f)
        vcWork.flags |= VC_ALL_WARP_FLAGS;
    
    if (far_watch_rate != 0.0f) 
        vcWork.flags |= VC_WARP_CAM_TGT_F;
}

#line 1418
void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA** vc_road_ary_list) {
    if (shGetDT() != 0.0f) {
        if (vcWork.flags & VC_PRS_F_VIEW_F)
            vcWork.flags |= VC_OLD_PRS_F_VIEW_F;
        else
            vcWork.flags &= ~VC_OLD_PRS_F_VIEW_F;
        
        if (PlayerSearchVIewButtonCheck())
            vcWork.flags |= VC_PRS_F_VIEW_F;
        else
            vcWork.flags &= ~VC_PRS_F_VIEW_F;
    }

    
    vcWork.scr_half_ang_wx = shAtan2(VbScreenInfo.scr_z, VbScreenInfo.sx) / 2.0f;
    vcWork.scr_half_ang_wy = shAtan2(VbScreenInfo.scr_z, VbScreenInfo.sy) / 2.0f;
    
    if (vcWork.through_door_activate_init_f) {
        
        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_START);
    }

    
    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_MAIN);



    
    vcSetNearestEnemyDataInVC_WORK(w_p);
    
    if (w_p->nearest_enemy_p == NULL) {
        
        vcSetNearestItemDataInVC_WORK(w_p);
    }


    
    vcSetNearRoadAryByCharaPos(w_p, vc_road_ary_list, 10000.0f, w_p->nearest_enemy_p != NULL);









    
    if (BgIsOut(0) != 0 || stage->glb_crd == 5) {
        w_p->ideal_cam_pos_h = -450.0f + vcWork.chara_top_y;
    } else {
        w_p->ideal_cam_pos_h = -200.0f + vcWork.chara_top_y;
    }
}

#line 1492
void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type) {

    VC_THROUGH_DOOR_CAM_PARAM* param;
    param = &w_p->through_door;

    switch (set_cmd_type) {
    case VC_TDSC_START:
        param->active_f = 1;
        param->timer = 0.0f;
        param->rail_ang_y = w_p->chara_eye_ang_y;
        
        vec_copy_xyz(param->rail_sta_pos, w_p->chara_pos);



        
        param->rail_sta_pos[1] = w_p->ideal_cam_pos_h;
        break;
    case VC_TDSC_END:
        param->active_f = 0;
        param->timer = 0.0f;
        break;
        
    case VC_TDSC_MAIN:
        if (param->active_f != 0) {
            param->rail_sta_to_chara_dist = vec3_dist_xz(w_p->through_door.rail_sta_pos, w_p->chara_pos);

            
            param->timer += shGetDT();
            
            if (param->timer <= 0.75f) {
                param->rail_sta_pos[1] += -250.0f * shGetDT();
            }
            
        }
        break;
    }
}

#line 1546
void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p) {
	/* 0x2 */ SubCharacter* sc_p;
	/* 0x10 */ SubCharacter* all_min_sc_p = NULL;
	/* 0x11 */ SubCharacter* active_min_sc_p = NULL;
	/* 0x14 */ float all_min_dist;
	/* 0x15 */ float active_min_dist;
	/* 0x12 */ int i;
    
    all_min_dist = active_min_dist = 7500.0f;
    
    if (sh2jms.player->battle.status & 0x10) {
        
        w_p->nearest_enemy_p = NULL;
        w_p->nearest_enemy_xz_dist = 7500.0f;
        return;
    }

    for (i = 0; i < 20; i++)
    {
	/* 0x1d */ sceVu0FVECTOR ofs_xz;
	/* 0x1d */ float xz_dist;
	/* 0x2 */ int adv_sc_f;
    /* 0x3 */ int set_active_data_f;
        sc_p = shCameraGetNearTarget(i, 0);
        
        if (sc_p == NULL) break;
        
        if ((sc_p->kind >> 8) == 2 && (sc_p->battle.dead_timer <= 1.5f || !(sc_p->battle.status & 2)) && !(sc_p->battle.status & 0x20)) {
            
            
            
            ofs_xz[0] = sc_p->pos.x - w_p->chara_pos[0];
            ofs_xz[2] = sc_p->pos.z - w_p->chara_pos[2];
            if (float_abs(ofs_xz[0]) < 7500.0f && 
                float_abs(ofs_xz[2]) < 7500.0f) {



                
                xz_dist = vec_length(ofs_xz);
                
                if (xz_dist < all_min_dist) {
                    all_min_dist = xz_dist;
                    all_min_sc_p = sc_p;
                }
                
                if (!(sc_p->battle.status & 4)) {
                    set_active_data_f = 1;
                } else
                    if (sc_p == (void*)&sh2jms.target && sh2jms.hold_type != -1) { // @bug this compares against a pointer to sh2jms.target, not the actual sh2jms.target ptr itself?
                        
                        
                        
                        set_active_data_f = 1;
                    } else {
                        set_active_data_f = 0;
                    }

                
                    if (set_active_data_f && xz_dist < active_min_dist) {
                        active_min_dist = xz_dist;
                        active_min_sc_p = sc_p;
                    }
    } } } // @weird
    
    if (active_min_sc_p != NULL) {
        w_p->nearest_enemy_p = active_min_sc_p;
        w_p->nearest_enemy_xz_dist = active_min_dist;
    } else {
        w_p->nearest_enemy_p = all_min_sc_p;
        w_p->nearest_enemy_xz_dist = all_min_dist;
    }
}

#line 1626
void vcSetNearestItemDataInVC_WORK(VC_WORK* w_p) {
    SubCharacter* sc_p;
    SubCharacter* all_min_sc_p = NULL;
    float all_min_dist;
    int i;

    all_min_dist = 5000.0f;
    
    if (sh2jms.player->battle.status & 0x20) {
        w_p->nearest_item_p = NULL;
        w_p->nearest_item_xz_dist = 5000.0f;
        return;
    }

    for (i = 0; i < 20; i++) {
        sceVu0FVECTOR ofs_xz;
        int adv_sc_f; // @unused
        float xz_dist;
        
        sc_p = shCameraGetNearTarget(i, 1);
        
        if (sc_p == NULL) break;


        
        ofs_xz[0] = sc_p->pos.x - w_p->chara_pos[0];
        ofs_xz[2] = sc_p->pos.z - w_p->chara_pos[2];
        if (float_abs(ofs_xz[0]) < 5000.0f && float_abs(ofs_xz[2]) < 5000.0f) {




            
            xz_dist = vec_length(ofs_xz);
            
            if (xz_dist < all_min_dist) {
                all_min_dist = xz_dist;
                all_min_sc_p = sc_p;
            }
    } } // @weird
    
    w_p->nearest_enemy_p = all_min_sc_p;
    w_p->nearest_enemy_xz_dist = all_min_dist;
}
 
#line 1705
void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA** road_ary_list, float half_w, int near_enemy_f) {
	/* 0x02 */ VC_ROAD_DATA* road_ary, *rd_p;
	/* 0x01 */ float get_min_x, get_max_x, get_min_z, get_max_z;
	/* 0x1d */ sceVu0FVECTOR tmpvec0, ppos;
	/* 0x1d */ VC_LIMIT_AREA rd, sw;
	/* 0x14 */ float rdrot, swrot;
	/* 0x1d */ sceVu0FMATRIX rd_rm, sw_rm;
	/* 0x16 */ float sw_min_x, sw_max_x, sw_min_z, sw_max_z, rd_min_x, rd_max_x, rd_min_z, rd_max_z, xl, zl;
	/* 0x1d */ sceVu0FVECTOR tmpvec1, tmpvec2;
	/* 0x11 */ VC_NEAR_ROAD_DATA* near_rd_p;
    /* 0x1d */ float add;
    
    vu0_unit_vector(tmpvec0);

    
    w_p->near_road_suu = 0;
    while (road_ary = *(road_ary_list++)) {
        for (rd_p = road_ary; !(rd_p->flags & VC_RD_END_DATA_F); rd_p++) {












            
            if (near_enemy_f) {
                if (rd_p->flags & VC_RD_USE_NO_ENEMY_F) 
                    continue;
            } else {
                if (rd_p->flags & VC_RD_USE_NEAR_ENEMY_F) 
                    continue;
            }





            
            xl = rd_p->lim_rd.x0 - rd_p->lim_rd.x1;
            zl = rd_p->lim_rd.z0 - rd_p->lim_rd.z1;
            
            rdrot = shAtan2(zl, xl);
            
            vu0_unit_matrix(rd_rm);
            shRotMatrixY(rd_rm, rd_rm, shAngleRegulate(-rdrot));
            rd_rm[3][0] = rd_p->lim_rd.x1;
            rd_rm[3][2] = rd_p->lim_rd.z1;

            
            tmpvec0[0] = rd_p->lim_rd.x0;
            tmpvec0[2] = rd_p->lim_rd.z0;
            vcTransRotRoadArea(tmpvec1, rd_rm, tmpvec0);
            tmpvec0[0] = rd_p->lim_rd.x2;
            tmpvec0[2] = rd_p->lim_rd.z2;
            vcTransRotRoadArea(tmpvec2, rd_rm, tmpvec0);
            
            if (tmpvec1[0] > tmpvec2[0]) { 
                rd.min_hx = tmpvec2[0]; 
                rd.max_hx = tmpvec1[0];
            } else { 
                rd.min_hx = tmpvec1[0]; 
                rd.max_hx = tmpvec2[0];
            }
            
            if (tmpvec1[2] > tmpvec2[2]) { 
                rd.min_hz = tmpvec2[2]; 
                rd.max_hz = tmpvec1[2];
            } else { 
                rd.min_hz = tmpvec1[2]; 
                rd.max_hz = tmpvec2[2];
            }

            xl = rd_p->lim_sw.x0 - rd_p->lim_sw.x1;
            zl = rd_p->lim_sw.z0 - rd_p->lim_sw.z1;
            
            swrot = shAtan2(zl, xl);
            
            vu0_unit_matrix(sw_rm);
            shRotMatrixY(sw_rm, sw_rm, shAngleRegulate(-swrot));
            sw_rm[3][0] = rd_p->lim_sw.x1;
            sw_rm[3][2] = rd_p->lim_sw.z1;

            
            tmpvec0[0] = rd_p->lim_sw.x0;
            tmpvec0[2] = rd_p->lim_sw.z0;
            vcTransRotRoadArea(tmpvec1, sw_rm, tmpvec0);
            tmpvec0[0] = rd_p->lim_sw.x2;
            tmpvec0[2] = rd_p->lim_sw.z2;
            vcTransRotRoadArea(tmpvec2, sw_rm, tmpvec0);
            
            if (tmpvec1[0] > tmpvec2[0]) { 
                sw.min_hx = tmpvec2[0]; 
                sw.max_hx = tmpvec1[0]; 
            } else { 
                sw.min_hx = tmpvec1[0]; 
                sw.max_hx = tmpvec2[0];
            }
            
            if (tmpvec1[2] > tmpvec2[2]) { 
                sw.min_hz = tmpvec2[2]; 
                sw.max_hz = tmpvec1[2];
            } else { 
                sw.min_hz = tmpvec1[2]; 
                sw.max_hz = tmpvec2[2];
            }

            
            tmpvec0[0] = w_p->chara_pos[0];
            tmpvec0[2] = w_p->chara_pos[2];
            vcTransRotRoadArea(ppos, sw_rm, tmpvec0);
            
            get_min_x = ppos[0] - half_w;
            get_max_x = ppos[0] + half_w;
            get_min_z = ppos[2] - half_w;
            get_max_z = ppos[2] + half_w;

            
            rd_min_x = rd.min_hx;
            rd_max_x = rd.max_hx;
            rd_min_z = rd.min_hz;
            rd_max_z = rd.max_hz;
            sw_min_x = sw.min_hx;
            sw_max_x = sw.max_hx;
            sw_min_z = sw.min_hz;
            sw_max_z = sw.max_hz;
            
            if (!(sw_min_x <= get_max_x && sw_max_x >= get_min_x && sw_min_z <= get_max_z && sw_max_z >= get_min_z) &&
                !(rd_min_x <= get_max_x && rd_max_x >= get_min_x && rd_min_z <= get_max_z && rd_max_z >= get_min_z)) {
                continue;
            }










            

            near_rd_p = &w_p->near_road_ary[w_p->near_road_suu];
            near_rd_p->road_p = rd_p;
            near_rd_p->chara2road_sum_dist = vcGetXZSumDistFromLimArea(
                &near_rd_p->chara2road_vec_x, &near_rd_p->chara2road_vec_z,
                ppos[0], ppos[2], sw_min_x, sw_max_x, sw_min_z, sw_max_z,
                near_rd_p->road_p->flags & VC_RD_MARGE_ROAD_F);




            
            

            if (near_rd_p->sw.min_hy < w_p->chara_pos[1])
                add = float_abs(w_p->chara_pos[1] - near_rd_p->sw.min_hy);
                
            else if (near_rd_p->sw.max_hy > w_p->chara_pos[1])
                add = float_abs(near_rd_p->sw.min_hy - w_p->chara_pos[1]);
                
            else 
                add = 0.0f;
            
            near_rd_p->chara2road_sum_dist += add;

            near_rd_p->rd_dir_type  = rd_p->rd_dir_type;
            near_rd_p->use_priority = vcRetRoadUsePriority(rd_p->rd_type);
            
            near_rd_p->rd.min_hx = rd_min_x; 
            near_rd_p->rd.max_hx = rd_max_x;
            near_rd_p->rd.min_hz = rd_min_z; 
            near_rd_p->rd.max_hz = rd_max_z;
            near_rd_p->sw.min_hx = sw_min_x; 
            near_rd_p->sw.max_hx = sw_max_x;
            near_rd_p->sw.min_hz = sw_min_z; 
            near_rd_p->sw.max_hz = sw_max_z;
            near_rd_p->sw.min_hy = rd_p->lim_sw.min_hy;
            near_rd_p->sw.max_hy = rd_p->lim_sw.max_hy;
            near_rd_p->rd.min_hy = rd_p->lim_rd.min_hy;
            near_rd_p->rd.max_hy = rd_p->lim_rd.max_hy;

            mat_copy(near_rd_p->rd_rzm, rd_rm);
            
            vu0_unit_matrix(rd_rm);
            shRotMatrixY(rd_rm, rd_rm, rdrot);
            rd_rm[3][0] = -rd_p->lim_rd.x1;
            rd_rm[3][2] = -rd_p->lim_rd.z1;
            mat_copy(near_rd_p->rd_rim, rd_rm);

            mat_copy(near_rd_p->sw_rzm, sw_rm);
            
            vu0_unit_matrix(sw_rm);
            shRotMatrixY(sw_rm, sw_rm, swrot);
            sw_rm[3][0] = -rd_p->lim_sw.x1;
            sw_rm[3][2] = -rd_p->lim_sw.z1;
            mat_copy(near_rd_p->sw_rim, sw_rm);

            w_p->near_road_suu++;
            ASSERT(w_p->near_road_suu <= 128);
            
        } }
}

#line 1930
int vcRetRoadUsePriority(VC_ROAD_TYPE rd_type) {
    
    switch (rd_type) {
        case 2:
            
            return (vcRetPrioStgEvnt(stage->glb_crd) != 0) ? 0 : 6;
            
        case 1: 
            return (vcRetPrioStgEvnt(stage->glb_crd) != 0) ? 0 : 5;
            
        case 4: return 3;
        case 0: return 2;
        case 3: return 1;
        case 5:
            return (vcWork.flags & VC_PRS_F_VIEW_F) ? 4 : 0;
    }







    
    return 0;
}

const u_char unkPadding_0039066X[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// @todo: Might fit into the empty space in vcSetCurNearRoadInVC_WORK?
#define VCWORK_SET_CUR_NEAR_ROAD(w_p, new_cur_p) \
    if (new_cur_p->road_p->flags & 2) { \
        ret_warp_f = 1; \
    } \
    if (w_p->cur_near_road.road_p->flags & 4) { \
        ret_warp_f = 1; \
    } \
    \
    w_p->cur_near_road = *new_cur_p; \
    \
    if (new_cur_p->road_p->proj_sec == 0.0f) { \
        proj_frame = 0; \
    } else { \
        proj_frame = new_cur_p->road_p->proj_sec * shGetFPS(); \
    } \
    vcSetProjectionValue(new_cur_p->road_p->projection, proj_frame); \
    vcWork.flags |= VC_SWITCH_NEAR_RD_DATA_F;

#line 1973
int vcSetCurNearRoadInVC_WORK(VC_WORK* w_p) {
    VC_NEAR_ROAD_DATA* n_rd_p;
    VC_NEAR_ROAD_DATA* new_cur_p;
    VC_NEAR_ROAD_DATA* old_cur_p;
    float new_cur_sum_dist;
    float adv_old_cur_dist;
    int ret_warp_f = 0, proj_frame;
    float ofs_ang_y, old_cur_rd_ang_y, old_cur_sum_dist;

    new_cur_sum_dist = vcGetBestNewCurNearRoad(&new_cur_p, VC_CHK_NEAREST_SWITCH_TYPE, w_p->chara_pos, w_p);





    
    for(n_rd_p = w_p->near_road_ary, old_cur_p = NULL;
        n_rd_p < &w_p->near_road_ary[w_p->near_road_suu];
        n_rd_p++)
    {
        if (n_rd_p->road_p == w_p->cur_near_road.road_p) 
            old_cur_p = n_rd_p;
    }




















    
    
    if (old_cur_p == NULL) {
        
        VCWORK_SET_CUR_NEAR_ROAD(w_p, new_cur_p);
        
        return ret_warp_f;
    }
    adv_old_cur_dist = vcAdvantageDistOfOldCurRoad(old_cur_p);



    
    if (old_cur_p->use_priority > new_cur_p->use_priority && old_cur_p->chara2road_sum_dist < (2.0f * adv_old_cur_dist)) {
        
        
        w_p->cur_near_road = *old_cur_p;
    } 
    else if (old_cur_p->use_priority < new_cur_p->use_priority && new_cur_p->chara2road_sum_dist <= 0.0f) {

        
        VCWORK_SET_CUR_NEAR_ROAD(w_p, new_cur_p);
    } else if ((old_cur_p->road_p->flags & VC_RD_NO_EXTRA_AREA_F) && (
        (old_cur_p->road_p->mv_y_type == VC_MV_THROUGH_DOOR && new_cur_p->road_p->mv_y_type == VC_MV_CHASE) || 
        (old_cur_p->road_p->mv_y_type == VC_MV_CHASE && new_cur_p->road_p->mv_y_type == VC_MV_THROUGH_DOOR))) {
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        VCWORK_SET_CUR_NEAR_ROAD(w_p, new_cur_p);
    } else {



        
        old_cur_sum_dist = old_cur_p->chara2road_sum_dist;

        
        switch (old_cur_p->rd_dir_type) {
            case 0: ofs_ang_y = TO_RAD(0.0f); break;
            case 1: ofs_ang_y = TO_RAD(90.0f); break;
            case 2: ofs_ang_y = TO_RAD(0.0f); break;
            default: ASSERT(0); break;
        }

        old_cur_rd_ang_y = shAngleRegulate(w_p->chara_mv_ang_y - ofs_ang_y);
        
        if (old_cur_rd_ang_y < TO_RAD(0.0f)) old_cur_rd_ang_y += TO_RAD(180.0f);
        if (old_cur_rd_ang_y > TO_RAD(90.0f)) old_cur_rd_ang_y = TO_RAD(180.0f) - old_cur_rd_ang_y;

        
        if ((old_cur_sum_dist - adv_old_cur_dist) <= new_cur_sum_dist) {
            w_p->cur_near_road = *old_cur_p;
        } 
        else if (old_cur_sum_dist < 0.0f && old_cur_rd_ang_y < TO_RAD(20.0f)) {
            w_p->cur_near_road = *old_cur_p;
        } else {
            VCWORK_SET_CUR_NEAR_ROAD(w_p, new_cur_p);
        }
    }


    
    if ((new_cur_p->road_p->flags & VC_RD_NOT_WARP_F) || 
        (old_cur_p->road_p->flags & VC_RD_NOT_WARP_F)) {
        
        ret_warp_f = 0;
    }
    
    if (vcWork.flags & VC_SWITCH_NEAR_RD_DATA_F) {
        vcEndProcessingOldNearRoad(old_cur_p, w_p);
    }
    return ret_warp_f;
}

// @todo: Might fit into the empty space in vcGetBestNewCurNearRoad?
#define UPDATE_BEST_ROAD_IF_BETTER(road_data_p, min_dist) \
    { \
        int renewal_f; \
        renewal_f = 0; \
        if ((road_data_p)) { \
            if ((road_data_p)->use_priority > new_cur_priority) { \
                if ((min_dist) <= 0.0f || (min_dist) < new_cur_dist) { \
                    renewal_f = 1; \
                } \
            } else if ((road_data_p)->use_priority < new_cur_priority) { \
                if (new_cur_dist > 0.0f && (min_dist) < new_cur_dist) { \
                    renewal_f = 1; \
                } \
            } else if ((min_dist) < new_cur_dist) { \
                renewal_f = 1; \
            } \
        } \
        if (renewal_f) { \
            new_cur_p = (road_data_p); \
            new_cur_dist = (min_dist); \
            new_cur_priority = (road_data_p)->use_priority; \
        } \
    }

#line 2126
float vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CHK_TYPE chk_type, float* pos, VC_WORK* w_p) {
	/* 0x10 */ VC_NEAR_ROAD_DATA* new_cur_p;
	/* 0x1d */ float new_cur_dist;
	/* 0x1d */ VC_NEAR_ROAD_DATA* road_nearest_p, *eff_nearest_p, *evnt_nearest_p;
	/* 0x18 */ float road_min_dist, eff_min_dist, evnt_min_dist;
	/* 0x1d */ VC_NEAR_ROAD_DATA* rd_high_nearest_p, *rd_low_nearest_p, *sv_only_nearest_p;
	/* 0x15 */ float rd_high_min_dist, rd_low_min_dist, sv_only_min_dist;
	/* 0x3 */ int new_cur_priority;
	/* 0x1d */ float dummy;
    
    new_cur_p = NULL;
    new_cur_dist = 3.4028235e38f;











    
    evnt_min_dist = vcGetNearestNEAR_ROAD_DATA(&evnt_nearest_p, chk_type, VC_RD_TYPE_EVENT, pos, w_p, 0);
    eff_min_dist = vcGetNearestNEAR_ROAD_DATA(&eff_nearest_p, chk_type, VC_RD_TYPE_EFFECT, pos, w_p, 0);
    road_min_dist = vcGetNearestNEAR_ROAD_DATA(&road_nearest_p, chk_type, VC_RD_TYPE_ROAD, pos, w_p, 0);
    
    rd_high_min_dist = vcGetNearestNEAR_ROAD_DATA(&rd_high_nearest_p, chk_type, VC_RD_TYPE_ROAD_PRIO_HIGH, pos, w_p, 0);
    
    rd_low_min_dist = vcGetNearestNEAR_ROAD_DATA(&rd_low_nearest_p, chk_type, VC_RD_TYPE_ROAD_PRIO_LOW, pos, w_p, 0);
    
    sv_only_min_dist = vcGetNearestNEAR_ROAD_DATA(&sv_only_nearest_p, chk_type, VC_RD_TYPE_SV_ONLY, pos, w_p, 0);
    
    
    
    
    
    new_cur_priority = 0;





















    

    UPDATE_BEST_ROAD_IF_BETTER(evnt_nearest_p, evnt_min_dist);
    UPDATE_BEST_ROAD_IF_BETTER(road_nearest_p, road_min_dist);
    UPDATE_BEST_ROAD_IF_BETTER(eff_nearest_p, eff_min_dist);

    UPDATE_BEST_ROAD_IF_BETTER(rd_high_nearest_p, rd_high_min_dist);
    UPDATE_BEST_ROAD_IF_BETTER(rd_low_nearest_p, rd_low_min_dist);
    UPDATE_BEST_ROAD_IF_BETTER(sv_only_nearest_p, sv_only_min_dist);


    
    if (new_cur_p == NULL) {

        
        new_cur_p = &vcNullNearRoad;
        new_cur_dist = vcGetXZSumDistFromLimArea(&dummy, &dummy, pos[0], pos[2], vcNullNearRoad.rd.min_hx, vcNullNearRoad.rd.max_hx, vcNullNearRoad.rd.min_hz, vcNullNearRoad.rd.max_hz, vcNullNearRoad.road_p->flags & 0x80);
    }









    
    *new_cur_pp = new_cur_p;
    
    return new_cur_dist;
}

#line 2250
float vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, float* pos, VC_WORK* w_p, int chk_only_set_marge_f) {
	/* 0x10 */ VC_NEAR_ROAD_DATA* nearest_p, *n_rd_p;
	/* 0x14 */ float min_sum_dist;
	/* 0x1d */ float dummy;
	/* 0x1d */ sceVu0FVECTOR cppos;
	/* 0x15 */ float min_x, max_x, min_z, max_z, dist;
    
    nearest_p = 0;
    min_sum_dist = 3.4028235e38f;

    for (n_rd_p = w_p->near_road_ary; n_rd_p < &w_p->near_road_ary[w_p->near_road_suu]; n_rd_p++) {





        
        if (n_rd_p->road_p->rd_type == rd_type) {
            
            if (chk_only_set_marge_f) {
                if (!(n_rd_p->road_p->flags & VC_RD_MARGE_ROAD_F))
                    continue;
            }
            
            switch (chk_type) {
                case VC_CHK_NEAREST_ROAD_TYPE:
                    min_x = n_rd_p->rd.min_hx;
                    max_x = n_rd_p->rd.max_hx;
                    min_z = n_rd_p->rd.min_hz;
                    max_z = n_rd_p->rd.max_hz;
                    break;
                case VC_CHK_NEAREST_SWITCH_TYPE:
                    min_x = n_rd_p->sw.min_hx;
                    max_x = n_rd_p->sw.max_hx;
                    min_z = n_rd_p->sw.min_hz;
                    max_z = n_rd_p->sw.max_hz;
                    break;
                default: 
                    ASSERT(0);
            }

            
            vcTransRotRoadArea(cppos, n_rd_p->sw_rzm, pos);
            
            dist = vcGetXZSumDistFromLimArea(&dummy, &dummy, cppos[0], cppos[2], min_x, max_x, min_z, max_z, n_rd_p->road_p->flags & 0x80);
            
            
            
            
            
            
            
            if (dist <= min_sum_dist) {

                
                if (pos[1] <= n_rd_p->sw.min_hy && pos[1] >= n_rd_p->sw.max_hy) {

                    
                    min_sum_dist = dist;
                    nearest_p = n_rd_p;
                }
            }
    }   }
    
    *out_nearest_p_addr = nearest_p;
    
    return min_sum_dist;
}

#line 2340
float vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p) {
    if ((u_short)old_cur_p->road_p->flags & VC_RD_NO_EXTRA_AREA_F) {
        return 0.0f;
    }
    
    switch (old_cur_p->road_p->rd_type) {
        default: ASSERT(0);
        case VC_RD_TYPE_ROAD:
        case VC_RD_TYPE_ROAD_PRIO_LOW:
        case VC_RD_TYPE_ROAD_PRIO_HIGH:
        case VC_RD_TYPE_SV_ONLY:



            return extra_boundary_width[old_cur_p->road_p->area_size_type]; // change area_size_type to int
        case VC_RD_TYPE_EFFECT:
        case VC_RD_TYPE_EVENT:
            
            return 50.0f;
    }
}

#line 2386
void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, float far_watch_rate, float self_view_eff_rate) {
    sceVu0FVECTOR far_watch_pos, vec;

    vcMakeFarWatchTgtPos(far_watch_pos, w_p, cur_rd_area_size);



    
    switch (cam_mv_type) {
        default: ASSERT(0);
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
            vcMakeNormalWatchTgtPos(w_p->watch_tgt_pos, &w_p->watch_tgt_ang_z, w_p, cam_mv_type, cur_rd_area_size);
    
    
    
            
            if (far_watch_rate != 0.0f) {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
                if (playing.control_type == 1 && (vcWork.cur_near_road.road_p->cam_mv_type == 0 || vcWork.cur_near_road.road_p->cam_mv_type == 4)) {
                    vec_copy(w_p->watch_tgt_pos, w_p->chara_pos);
                    w_p->watch_tgt_pos[1] = 225.0f + w_p->chara_top_y;
                }
    
                
                vec_sub_xyz_reverse(w_p->watch_tgt_pos, far_watch_pos, vec);
                vec_scale_xyz(far_watch_rate, vec, vec);
                vec_add_xyz(w_p->watch_tgt_pos, vec, w_p->watch_tgt_pos);
                
            }
            break;
        case 3:
            vec_copy(w_p->watch_tgt_pos, far_watch_pos);
            
            break;
    }
    vcMixSelfViewEffectToWatchTgtPos(w_p->watch_tgt_pos, &w_p->watch_tgt_ang_z, self_view_eff_rate, w_p, vcPreInfo.hero_neck_wm[0], sh2jms.lower_now);







    
    if (w_p->watch_tgt_pos[1] > w_p->watch_tgt_max_y)
        w_p->watch_tgt_pos[1] = w_p->watch_tgt_max_y;
}

static inline void vec_add_reverse(void* x, void* y, void* out) {
    asm("\
        lqc2 vf4, 0(%1)\n\
        lqc2 vf5, 0(%0)\n\
        vadd.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
        : "+r"(x), "+r"(y), "+r"(out));
}

#line 2487
void vcMakeNormalWatchTgtPos(float* watch_tgt_pos, float* watch_tgt_ang_z_p, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size) {
    sceVu0FVECTOR ang;
    sceVu0FVECTOR vec;
    float watch_y;
    float cam2chara_dist;
    float min_cam2watch_dist;
    float tgt_chara2watch_cir_dist;
    float tgt_watch_cir_r;

    
    *watch_tgt_ang_z_p = 0.0f;
    
    if (cam_mv_type == VC_MV_FIX_ANG) {


        
        vu0_unit_vector(ang);
        ang[0] = w_p->cur_near_road.road_p->tmp.chs.ofs_hy;
        ang[1] = shAngleRegulate(w_p->cur_near_road.road_p->tmp.chs.ratio_r_xz + w_p->fix_man.add_ang_y);



        
        vwAngleToVector(vec, ang, w_p->cur_near_road.road_p->tmp.chs.rr_lim_ang_y);





        
        vec_add_reverse(w_p->cam_pos, vec, watch_tgt_pos);
        watch_tgt_pos[3] = 1.0f;
        
        return;
    }





    
    cam2chara_dist = vec3_dist_xz(w_p->cam_pos, w_p->chara_pos);
    
    switch (cam_mv_type) {
        default:
        case VC_MV_SELF_VIEW:
            ASSERT(0);
        case VC_MV_SETTLE:
            tgt_watch_cir_r = nml_tgt_watch_cir_r[cur_rd_area_size] / 2.0f;
            
            tgt_chara2watch_cir_dist = 0.0f;
            break;
        case VC_MV_THROUGH_DOOR:
        case VC_MV_CHASE:
        case VC_MV_LOCUS_CIRCLE:
            if (stage->glb_crd == 1 && sh2jms.player->pos.x >= -20000.0f) {
                tgt_watch_cir_r = 1.75f * nml_tgt_watch_cir_r[cur_rd_area_size];
                
                min_cam2watch_dist = 1.75f * nml_cam2wth_min_dist[cur_rd_area_size];
                
            } else if (sh2jms.player->status & 0x20000) {
                tgt_watch_cir_r = 2000.0f;
                min_cam2watch_dist = 5000.0f;
            } else {
                tgt_watch_cir_r = nml_tgt_watch_cir_r[cur_rd_area_size];
                min_cam2watch_dist = nml_cam2wth_min_dist[cur_rd_area_size];
            }
    
            
            if (cam2chara_dist < tgt_watch_cir_r + min_cam2watch_dist) {
                tgt_chara2watch_cir_dist = tgt_watch_cir_r + min_cam2watch_dist - cam2chara_dist;
                
            } else {
                tgt_chara2watch_cir_dist = 0.0f;
            }
    
            
            break;
    }
    watch_y = vcWork.cur_near_road.road_p->ofs_watch_hy + w_p->chara_bottom_y;
    
    vcSetWatchTgtXzPos(watch_tgt_pos, w_p->chara_pos, w_p->cam_pos, tgt_chara2watch_cir_dist, tgt_watch_cir_r, w_p->chara_eye_ang_y);



    
    vcSetWatchTgtYParam(watch_tgt_pos, w_p, cam_mv_type, watch_y);


    
}

#line 2607
void vcMixSelfViewEffectToWatchTgtPos(float* watch_tgt_pos, float* watch_tgt_ang_z_p, float effect_rate, VC_WORK* w_p, float* head_mat, int anim_status) {
    sceVu0FVECTOR cam_ang;
    sceVu0FVECTOR vec;
    sceVu0FVECTOR eff_pos;
    float ofs_ang;
    float chara2head_ofs_ang_y, chara2far_ofs_ang_y;
    float abs_ofs_ang_y;
    float add_ang_y;
    float view_xyz_len;
    float far_ang_x;
    float xz_dist;
    int jouge_val;

    vec_sub_xyz(watch_tgt_pos, w_p->cam_pos, vec);

    view_xyz_len = vec3_length(vec);

    xz_dist = vec_length(vec);
    
    far_ang_x = shAtan2(xz_dist, -vec[1]);
    far_ang_x = CLAMP(far_ang_x, TO_RAD(-70.0f), TO_RAD(70.0f));
    
    chara2far_ofs_ang_y = shAngleRegulate(shAtanV(vec) - sys.hero.ang[1]);


    
    vwMatrixToAngleYXZ(cam_ang, head_mat);
    
    chara2head_ofs_ang_y = shAngleRegulate(cam_ang[1] - sys.hero.ang[1]);





    
    // z switch
    switch (anim_status) {
        case 12:
        case 13:
        case 14:
            break;
        case 1:
            if (w_p->nearest_enemy_p != NULL) {
                cam_ang[2] = 0.0f;
            }
            break;
        default:
            cam_ang[2] /= 2.0f;
            break;
    }
    // y switch
    switch (anim_status) {
        case 15:
        case 16:
        default:
            cam_ang[1] = sys.hero.ang[1];
            break;
        case 1:
            if (w_p->nearest_enemy_p != NULL) {
                cam_ang[1] = sys.hero.ang[1];
            } else {
                cam_ang[1] += TO_RAD(30.0f);
            }
            break;                   
        case 24:
            break;
        case 3:




            
            abs_ofs_ang_y = float_abs(chara2head_ofs_ang_y);
            if (abs_ofs_ang_y > TO_RAD(4.0f)) {
                add_ang_y = TO_RAD(4.0f) + ((abs_ofs_ang_y - TO_RAD(4.0f)) / 8.0f);
                if (chara2head_ofs_ang_y < 0.0f) add_ang_y *= -1.0f;
            } else {
                add_ang_y = chara2head_ofs_ang_y;
            }
            
            cam_ang[1] = add_ang_y + sys.hero.ang[1];

            
            break;
        case 9:
        case 12:
        case 13:
        case 14:
        case 7:
        case 6:
            chara2head_ofs_ang_y = chara2head_ofs_ang_y / 8.0f;
            add_ang_y = CLAMP(chara2head_ofs_ang_y, TO_RAD(-10.0f), TO_RAD(10.0f));
            
            cam_ang[1] = add_ang_y + sys.hero.ang[1];
            break;
    }

    // x switch
    switch (anim_status) {
        case 3:






            
            cam_ang[0] += TO_RAD(-8.0f);
            break;
        case 1:
            if (w_p->nearest_enemy_p != NULL) {
                cam_ang[0] = TO_RAD(-7.0f);
            } else {
                cam_ang[0] += TO_RAD(-8.0f);
            }
            break;
        case 9:
        case 12:
        case 13:
        case 14:
            break;
        case 7:
        case 6:
            
            jouge_val = ((int)sys.hero.ang[1] >> 7) & 0xF;
            
            switch(jouge_val) {
                case 0:
                case 5:
                    cam_ang[0] += TO_RAD(-1.0f);
                    break;
            }
            
            cam_ang[0] += TO_RAD(-6.0f);
            break;
    }

    // @todo: switch? might explain gap
    if ((anim_status != 6) && (anim_status != 7) && (anim_status != 14) && (anim_status != 13) && (anim_status != 12) && (anim_status != 9) && (anim_status != 1) && (anim_status != 3)) {
    
        cam_ang[0] = 0.7f * far_ang_x;
    } else {







        
        cam_ang[0] += far_ang_x / 2.0f;
    }

    cam_ang[0] = CLAMP(cam_ang[0], TO_RAD(-80.0f), TO_RAD(80.0f));






    
    ofs_ang = shAngleRegulate(cam_ang[2] - *watch_tgt_ang_z_p);
    *watch_tgt_ang_z_p += ofs_ang * effect_rate;
    
    eff_pos[0] = w_p->cam_pos[0] + (shCosF(cam_ang[0]) * (view_xyz_len * shSinF(cam_ang[1])));

    
    eff_pos[2] = w_p->cam_pos[2] + (shCosF(cam_ang[0]) * (view_xyz_len * shCosF(cam_ang[1])));

    
    eff_pos[1] = w_p->cam_pos[1] - (view_xyz_len * shSinF(cam_ang[0]));

    
    vec_sub_xyz(eff_pos, watch_tgt_pos, eff_pos);
    vec_scale_xyz(effect_rate, eff_pos, eff_pos);
    vec_add_xyz(watch_tgt_pos, eff_pos, watch_tgt_pos);
    
}

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeFarWatchTgtPos);

#line 2966
void vcSetWatchTgtXzPos(sceVu0FVECTOR watch_pos, sceVu0FVECTOR center_pos, sceVu0FVECTOR cam_pos, float tgt_chara2watch_cir_dist, float tgt_watch_cir_r, float watch_cir_ang_y) {
    float cam2chr_ang;
    float chr2watch_x;
    float chr2watch_z;



    
    cam2chr_ang = shAtan2(center_pos[2] - cam_pos[2], center_pos[0] - cam_pos[0]);


    
    chr2watch_x = (tgt_chara2watch_cir_dist * shSinF(cam2chr_ang)) + (tgt_watch_cir_r * shSinF(watch_cir_ang_y));

    
    chr2watch_z = (tgt_chara2watch_cir_dist * shCosF(cam2chr_ang)) + (tgt_watch_cir_r * shCosF(watch_cir_ang_y));



    watch_pos[0] = center_pos[0] + chr2watch_x;
    watch_pos[2] = center_pos[2] + chr2watch_z;
}

#line 3011
void vcSetWatchTgtYParam(sceVu0FVECTOR watch_pos, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, float watch_y) {
    switch (cam_mv_type) {
        case VC_MV_SELF_VIEW:
            watch_pos[1] = w_p->chara_center_y;
            break;
        default:
            watch_pos[1] = watch_y;
    }
}

// @todo: Float arg issue with `shAtan2` call, matched at https://decomp.me/scratch/ngXcY
INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjustWatchYLimitHighWhenFarView);

static inline void vec_div_xyz_reverse(void* v, void* out, float s) {
    asm("lui t7, 0x3f80\n\
         mtc1 t7, f8\n\
         nop\n\
         div.s f8, f8, %1\n\
         lqc2 vf4, 0(%0)\n\
         mfc1 t7, f8;\
         qmtc2 t7, vf5\n\
         vmulx.xyz vf4, vf4, vf5x\n\
         sqc2 vf4, 0(%2)"
        : "+r"(v), "+f"(s), "+r"(out)::"t7");
}

#line 3101
void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, float far_watch_rate) {
    sceVu0FVECTOR tgt_vec;
    sceVu0FVECTOR ideal_pos;
    float max_tgt_mv_xz_len;
    MAKE_CAM_TGT make_type;

    switch (cam_mv_type) {
        case VC_MV_SELF_VIEW:
            vcMakeIdealCamPosByHeadPos(ideal_pos, w_p, cur_rd_area_size);
            break;
        case VC_MV_FIX_ANG:
            vcMakeIdealCamPosForFixAngCam(ideal_pos, w_p);
            break;
        case VC_MV_THROUGH_DOOR:
            vcMakeIdealCamPosForThroughDoorCam(ideal_pos, w_p);
            break;
        case VC_MV_LOCUS_CIRCLE:
            vcMakeIdealCamPosForLocusCircleCam(ideal_pos, w_p);
            break;
        default:
            vcMakeIdealCamPosUseVC_ROAD_DATA(ideal_pos, w_p, cur_rd_area_size);
            break;
    }
    
    if (vcWork.flags & VC_WARP_CAM_TGT_F) {
        vec_copy(w_p->cam_tgt_pos, ideal_pos);
    }






    
    switch (cam_mv_type) {
        default:
            ASSERT(0);
        case VC_MV_CHASE:
        case VC_MV_SETTLE:
        case VC_MV_FIX_ANG:
        case VC_MV_LOCUS_CIRCLE:
        case VC_MV_THROUGH_DOOR:
            make_type = MAKE_CAM_TGT_BY_ROAD;
            break;
        case VC_MV_SELF_VIEW:
            make_type = MAKE_CAM_TGT_BY_CHARA_HEAD;
            break;
    }
    
    switch (make_type) {
        case MAKE_CAM_TGT_BY_ROAD:
            max_tgt_mv_xz_len = vcRetMaxTgtMvXzLen(w_p, cam_mv_prm_p);
            
            vcMakeBasicCamTgtMvVec(tgt_vec, ideal_pos, w_p, max_tgt_mv_xz_len);



            
            if ((cam_mv_type == VC_MV_CHASE || cam_mv_type == VC_MV_LOCUS_CIRCLE) && !(cur_rd_flags & VC_RD_NO_FRONT_FLIP_F)) {


                
                vcCamTgtMvVecIsFlipedFromCharaFront(tgt_vec, w_p, max_tgt_mv_xz_len, cur_rd_area_size);
            }



            
            if (cam_mv_type != VC_MV_THROUGH_DOOR) {
                vcAdjTgtMvVecYByCurNearRoad(tgt_vec, w_p);
            }


            
            break;

        
        case MAKE_CAM_TGT_BY_CHARA_HEAD:
            max_tgt_mv_xz_len = 500.0f;
            vcMakeBasicCamTgtMvVec(tgt_vec, ideal_pos, w_p, max_tgt_mv_xz_len);
            break;
    }





    
    w_p->cam_tgt_mv_ang_y = shAtanV(tgt_vec);
    
    if (shGetDT() != 0.0f || (vcWork.flags & VC_WARP_CAM_TGT_F)) {
        vec_add_xyz(w_p->cam_tgt_pos, tgt_vec, w_p->cam_tgt_pos);

        
        // flipped last 2 params
        vec_div_xyz_reverse(tgt_vec, w_p->cam_tgt_velo, shGetDT());


        
        w_p->cam_tgt_spd = vec_length(w_p->cam_tgt_velo);
    } else {
        w_p->cam_tgt_velo[0] = 0.0f;
        w_p->cam_tgt_velo[2] = 0.0f;
        w_p->cam_tgt_spd = 0.0f;
    }
    
    vcChangeProjByDist(&w_p->cur_near_road, w_p->cam_tgt_pos[1] - w_p->chara_bottom_y);

    
}

#line 3228
float vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p)
{
    float max_spd_xz;
    float max_spd_xz_stg;

    max_spd_xz = w_p->chara_mv_spd + 500.0f + float_abs(w_p->chara_ang_spd_y * 8.0f);

    
    if (BgIsOut(0) != 0 || stage->glb_crd == 5) {
        if (!(sh2jms.player->status & 0x20000)) {
            max_spd_xz_stg = 3300.0f;
        } else {
            max_spd_xz_stg = 1650.0f;
        }
    } else {
        max_spd_xz_stg = 1200.0f;
    }

    
    max_spd_xz = float_clamp(max_spd_xz, max_spd_xz_stg, cam_mv_prm_p->max_spd_xz);
    
    return max_spd_xz * shGetDT();
}

#line 3273
void vcMakeIdealCamPosByHeadPos(sceVu0FVECTOR ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size) {
    float chara2cam_ang_y;

    if (w_p->flags & VC_WARP_WATCH_F) {


        
        vec_copy_xyz(ideal_pos, w_p->chara_pos);
        ideal_pos[1] = w_p->chara_top_y;
    } else {


        
        chara2cam_ang_y = shAngleRegulate(w_p->chara_eye_ang_y + TO_RAD(170.0f));
        
        ideal_pos[1] = w_p->chara_head_pos[1] + 50.0f;
        ideal_pos[0] = w_p->chara_head_pos[0] + (90.0f * shSinF(chara2cam_ang_y));
        
        ideal_pos[2] = w_p->chara_head_pos[2] + (90.0f * shCosF(chara2cam_ang_y));

    }
}

#line 3314
void vcMakeIdealCamPosForFixAngCam(sceVu0FVECTOR ideal_pos, VC_WORK* w_p) {
    float abs_ofs_x, abs_ofs_z;
    sceVu0FVECTOR ang;
    VC_LIMIT_AREA lim_rd;
    sceVu0FVECTOR cppos;
    float full_front_dist, ratio, chara2cam_dist, front2cam_dist;
    float zero_front_dist, base_front_r, rate, lim2chara_dist, chara_front_r;
    
    if (vcWork.flags & VC_SWITCH_NEAR_RD_DATA_F) {
        w_p->fix_man.exception_f = 0;
        w_p->fix_man.add_ang_y = 0.0f;
        w_p->fix_man.add_rd_x = 0.0f;
        w_p->fix_man.add_rd_z = 0.0f;
    }
    
    vec_zero_xyz(ang);
    ang[0] = w_p->cur_near_road.road_p->tmp.chs.ofs_hy;
    ang[1] = shAngleRegulate(w_p->cur_near_road.road_p->tmp.chs.ratio_r_xz + w_p->fix_man.add_ang_y);
    
    
    
    
    
    
    
    
    lim_rd.min_hx = w_p->cur_near_road.rd.min_hx + w_p->fix_man.add_rd_x;
    lim_rd.max_hx = w_p->cur_near_road.rd.max_hx + w_p->fix_man.add_rd_x;
    lim_rd.min_hz = w_p->cur_near_road.rd.min_hz + w_p->fix_man.add_rd_z;
    lim_rd.max_hz = w_p->cur_near_road.rd.max_hz + w_p->fix_man.add_rd_z;






    
    vcTransRotRoadArea(cppos, w_p->cur_near_road.rd_rzm, w_p->chara_pos);
    
    vcGetXZSumDistFromLimArea(&abs_ofs_x, &abs_ofs_z, cppos[0], cppos[2], w_p->cur_near_road.rd.min_hx, w_p->cur_near_road.rd.max_hx, w_p->cur_near_road.rd.min_hz, w_p->cur_near_road.rd.max_hz, 0);
    
    
    
    
    
    
    
    
    abs_ofs_x = float_abs(abs_ofs_x);
    abs_ofs_z = float_abs(abs_ofs_z);
    lim2chara_dist = float_max(abs_ofs_x, abs_ofs_z);
    
    front2cam_dist = 1000.0f + (lim2chara_dist / 2.0f);














    
    ratio = w_p->cur_near_road.road_p->tmp.chs.rr_lim_ang_y / 2000.0f;
    rate = 350.0f * ratio;
    zero_front_dist = 3500.0f * ratio;
    full_front_dist = 750.0f * ratio;

    chara2cam_dist = vec3_dist_xz(w_p->cam_pos, w_p->chara_pos);
    
    if (chara2cam_dist >= zero_front_dist) {
        base_front_r = 0.0f;
    } else if (chara2cam_dist <= full_front_dist) {
        base_front_r = rate;
    } else {

        
        chara_front_r = ((chara2cam_dist - zero_front_dist) / (full_front_dist - zero_front_dist));

        
        base_front_r = chara_front_r * rate;
    }





















    
    ideal_pos[0] = w_p->chara_pos[0] + (base_front_r * shSinF(w_p->chara_eye_ang_y)) + (front2cam_dist * shSinF(ang[1] + TO_RAD(180.0f)));
    
    
    
    
    
    
    
    ideal_pos[2] = w_p->chara_pos[2] + (base_front_r * shCosF(w_p->chara_eye_ang_y)) + (front2cam_dist * shCosF(ang[1] + TO_RAD(180.0f)));
    
    
    
    
    
    
    
    
    
    ideal_pos[1] = w_p->chara_pos[1];
    w_p->chara_top_y += w_p->cur_near_road.road_p->tmp.chs.lr_lim_ang_y;




    
    vcTransRotRoadArea(ideal_pos, w_p->cur_near_road.rd_rzm, ideal_pos);
    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(ideal_pos, &ideal_pos[2], &lim_rd);



    
    vcRotTransRoadArea(ideal_pos, w_p->cur_near_road.rd_rim, ideal_pos);
}

#line 3474
void vcMakeIdealCamPosForThroughDoorCam(sceVu0FVECTOR ideal_pos, VC_WORK* w_p) {
    float cos_ang_y, abs_ofs_ang_y;
    float max_add_right_dist, cut_ang_y, base_forwd_dist, max_add_forwd_dist;
    float mv_forwd_dist, mv_right_dist;
    VC_THROUGH_DOOR_CAM_PARAM* prm_p = &w_p->through_door;

    if (prm_p->active_f == 0)
        return;
    
    if (w_p->through_door_activate_init_f != 0) {
        mv_forwd_dist = -650.0f;
        mv_right_dist = 0.0f;
    } else {
























        
        cut_ang_y = 0.7853982f;
        base_forwd_dist = 375.0f;
        max_add_forwd_dist = 350.0f;
        max_add_right_dist = 300.0f;




        
        abs_ofs_ang_y = float_abs(shAngleRegulate(w_p->chara_eye_ang_y - prm_p->rail_ang_y));



        
        cos_ang_y = float_max(0.0f, abs_ofs_ang_y - cut_ang_y);
        cos_ang_y = (cos_ang_y * PI) / (TO_RAD(180.0f) - cut_ang_y);
        mv_forwd_dist = -max_add_forwd_dist * shCosF(cos_ang_y) + base_forwd_dist;
        
        mv_right_dist = shSinF(w_p->chara_eye_ang_y - prm_p->rail_ang_y) * -max_add_right_dist;
    }




    
    ideal_pos[0] = prm_p->rail_sta_pos[0] + (mv_forwd_dist * shSinF(prm_p->rail_ang_y)) + (mv_right_dist * shCosF(prm_p->rail_ang_y));
    
    
    
    ideal_pos[2] = prm_p->rail_sta_pos[2] + (mv_forwd_dist * shCosF(prm_p->rail_ang_y)) + (mv_right_dist * -shSinF(prm_p->rail_ang_y));
    
    
    
    ideal_pos[1] = prm_p->rail_sta_pos[1];
}

#line 3556
void vcMakeIdealCamPosForLocusCircleCam(sceVu0FVECTOR ideal_pos, VC_WORK* w_p) {
    sceVu0FVECTOR origin;
    sceVu0FVECTOR sw_l;
    float ofs_ang_y;
    float cir_ang_y;
    float cir_radius;

    
    cir_ang_y = shAngleRegulate(w_p->cur_near_road.road_p->tmp.chs.lr_lim_ang_y);
    cir_radius = w_p->cur_near_road.road_p->tmp.chs.rr_lim_ang_y;

    
    if (vcWork.flags & VC_SWITCH_NEAR_RD_DATA_F) {
        vec_zero(w_p->cir_man.sw_l);
        vec_zero_xyz(w_p->cir_man.origin);
        
        w_p->cir_man.sw_l[0] = float_abs(w_p->cur_near_road.sw.max_hx - w_p->cur_near_road.sw.min_hx);


        
        w_p->cir_man.sw_l[2] = float_abs(w_p->cur_near_road.sw.max_hz - w_p->cur_near_road.sw.min_hz);



        
        if (TO_RAD(-180.0f) <= cir_ang_y && cir_ang_y < TO_RAD(-90.0f)) {
            w_p->cir_man.origin[0] = float_max(w_p->cur_near_road.road_p->lim_sw.x0, w_p->cur_near_road.road_p->lim_sw.x2);



            
            w_p->cir_man.origin[2] = float_max(w_p->cur_near_road.road_p->lim_sw.z0, w_p->cur_near_road.road_p->lim_sw.z2);



            
        } else if (TO_RAD(-90.0f) <= cir_ang_y && cir_ang_y < TO_RAD(0.0f)) {
            w_p->cir_man.origin[0] = float_max(w_p->cur_near_road.road_p->lim_sw.x0, w_p->cur_near_road.road_p->lim_sw.x2);



            
            w_p->cir_man.origin[2] = float_min(w_p->cur_near_road.road_p->lim_sw.z0, w_p->cur_near_road.road_p->lim_sw.z2);



            
        } else if (TO_RAD(0.0f) <= cir_ang_y && cir_ang_y < TO_RAD(90.0f)) {
            w_p->cir_man.origin[0] = float_min(w_p->cur_near_road.road_p->lim_sw.x0, w_p->cur_near_road.road_p->lim_sw.x2);



            
            w_p->cir_man.origin[2] = float_min(w_p->cur_near_road.road_p->lim_sw.z0, w_p->cur_near_road.road_p->lim_sw.z2);



            
        } else {
            w_p->cir_man.origin[0] = float_min(w_p->cur_near_road.road_p->lim_sw.x0, w_p->cur_near_road.road_p->lim_sw.x2);



            
            w_p->cir_man.origin[2] = float_max(w_p->cur_near_road.road_p->lim_sw.z0, w_p->cur_near_road.road_p->lim_sw.z2);



            
        }
        
    }
    
    if (w_p->cur_near_road.road_p->tmp.chs.ofs_hy != 0.0f && w_p->cur_near_road.road_p->tmp.chs.ratio_r_xz != 0.0f) {

        
        origin[0] = w_p->cur_near_road.road_p->tmp.chs.ofs_hy;
        origin[2] = w_p->cur_near_road.road_p->tmp.chs.ratio_r_xz;
    } else {
        vec_copy(origin, w_p->cir_man.origin);
    }



    
    vec_copy(sw_l, w_p->cir_man.sw_l);
    
    ofs_ang_y = shAtan2(w_p->chara_pos[2] - origin[2], w_p->chara_pos[0] - origin[0]);
    
    ofs_ang_y = (ofs_ang_y - cir_ang_y);
    ofs_ang_y *= 2.0f;



    
    if (TO_RAD(-180.0f) <= cir_ang_y && cir_ang_y < TO_RAD(-90.0f)) {
        if (ofs_ang_y > 0.0f) {
            ideal_pos[0] = (origin[0] - sw_l[0]) - (cir_radius * shSinF(ofs_ang_y));
            ideal_pos[2] = origin[2] - (sw_l[2] * shCosF(ofs_ang_y));
        } else if (ofs_ang_y < 0.0f) {
            ideal_pos[0] = origin[0] - (sw_l[0] * shCosF(ofs_ang_y));
            ideal_pos[2] = (origin[2] - sw_l[2]) - (cir_radius * -shSinF(ofs_ang_y));
        } else {
            ideal_pos[0] = origin[0] - sw_l[0];
            ideal_pos[2] = origin[2] - sw_l[2];
        }
    } else if (TO_RAD(-90.0f) <= cir_ang_y && cir_ang_y < TO_RAD(0.0f)) {
        if (ofs_ang_y > TO_RAD(0.0f)) {
            ideal_pos[0] = origin[0] - (sw_l[0] * shCosF(ofs_ang_y));
            ideal_pos[2] = origin[2] + sw_l[2] + (cir_radius * shSinF(ofs_ang_y));
        } else if (ofs_ang_y < TO_RAD(0.0f)) {
            ideal_pos[0] = (origin[0] - sw_l[0]) - (cir_radius * -shSinF(ofs_ang_y));
            ideal_pos[2] = origin[2] + (sw_l[2] * shCosF(ofs_ang_y));
        } else {
            ideal_pos[0] = origin[0] - sw_l[0];
            ideal_pos[2] = origin[2] + sw_l[2];
        }
    } else if (TO_RAD(0.0f) < cir_ang_y && cir_ang_y < TO_RAD(90.0f)) {
        if (ofs_ang_y > TO_RAD(0.0f)) {
            ideal_pos[0] = origin[0] + sw_l[0] + (cir_radius * shSinF(ofs_ang_y));
            ideal_pos[2] = origin[2] + (sw_l[2] * shCosF(ofs_ang_y));
        } else if (ofs_ang_y < TO_RAD(0.0f)) {
            ideal_pos[0] = origin[0] + (sw_l[0] * shCosF(ofs_ang_y));
            ideal_pos[2] = origin[2] + sw_l[2] + (cir_radius * -shSinF(ofs_ang_y));
        } else {
            ideal_pos[0] = origin[0] + sw_l[0];
            ideal_pos[2] = origin[2] + sw_l[2];
        }
    } else {
        if (ofs_ang_y > TO_RAD(0.0f)) {
            ideal_pos[0] = origin[0] + (sw_l[0] * shCosF(ofs_ang_y));
            ideal_pos[2] = (origin[2] - sw_l[2]) - (cir_radius * shSinF(ofs_ang_y));
        } else if (ofs_ang_y < TO_RAD(0.0f)) {
            ideal_pos[0] = origin[0] + sw_l[0] + (cir_radius * -shSinF(ofs_ang_y));
            ideal_pos[2] = origin[2] - (sw_l[2] * shCosF(ofs_ang_y));
        } else {
            ideal_pos[0] = origin[0] + sw_l[0];
            ideal_pos[2] = origin[2] - sw_l[2];
        }
    }


    
    ideal_pos[1] = w_p->ideal_cam_pos_h;







    
}

#line 3731
void vcMakeIdealCamPosUseVC_ROAD_DATA(sceVu0FVECTOR ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size) {
    float adj_x, adj_z;
    sceVu0FVECTOR cppos;
    VC_NEAR_ROAD_DATA* use_near_p;
    float out_rd_len;
    float now_ang_y, abs_chr2cam_y, ofs_ang_y;
    float chara2ideal_r, real_chr2cam_r; // real_chr2cam_r currently unused..
    float full_adj_min_dist, no_adj_max_dist;

    now_ang_y = TO_RAD(180.0f) + w_p->chara_eye_ang_y;
    ofs_ang_y = shAngleRegulate(w_p->cam_chara2ideal_ang_y - now_ang_y);
    
    if (float_abs(w_p->chara_ang_spd_y) > 0.34906584f)
        ofs_ang_y = CLAMP(ofs_ang_y, -0.20943952f, 0.20943952f);
    else if (ofs_ang_y >= 0.0f)
         ofs_ang_y = 0.20943952f;
    else ofs_ang_y = -0.20943952f;


    
    if (playing.control_type == 1)
        w_p->cam_chara2ideal_ang_y = shAngleRegulate(now_ang_y);
    else
        w_p->cam_chara2ideal_ang_y = shAngleRegulate(ofs_ang_y + now_ang_y);
    




    
    if (stage->glb_crd == 1 && sh2jms.player->pos.x >= -20000.0f) {
        chara2ideal_r = 1.75f * mv_nml_chr2cam_r[cur_rd_area_size];
    } else if (sh2jms.player->status & 0x20000) {
        chara2ideal_r = 2000.0f;
    } else {
        chara2ideal_r = mv_nml_chr2cam_r[cur_rd_area_size];
    }
    
    ideal_pos[0] = w_p->chara_pos[0] + (chara2ideal_r * shSinF(w_p->cam_chara2ideal_ang_y));
    
    ideal_pos[2] = w_p->chara_pos[2] + (chara2ideal_r * shCosF(w_p->cam_chara2ideal_ang_y));

    
    switch (w_p->cur_near_road.road_p->cam_mv_type) {
    case 0:
        ideal_pos[1] = w_p->ideal_cam_pos_h + w_p->cur_near_road.road_p->tmp.chs.ofs_hy;
        
        break;
    case 1:
        ideal_pos[1] = w_p->ideal_cam_pos_h;
        
        break;
    }
    
    
    ideal_pos[3] = 1.0f;

    
    adj_x = 0.0f;
    adj_z = 0.0f;

    

    
    use_near_p = &w_p->cur_near_road;

    abs_chr2cam_y = float_abs(w_p->cam_pos[1] - w_p->chara_pos[1]);
    abs_chr2cam_y = float_max(abs_chr2cam_y - 750.0f, 0.0f);




    ideal_pos[1] = CLAMP(ideal_pos[1], use_near_p->road_p->lim_rd.max_hy, use_near_p->road_p->lim_rd.min_hy);

    
    vcTransRotRoadArea(cppos, use_near_p->rd_rzm, w_p->chara_pos);
    adj_x = cppos[0];
    adj_z = cppos[2];
    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&adj_x, &adj_z, &use_near_p->rd);



    
    vec_zero_xyz(cppos);
    cppos[0] = adj_x;
    cppos[2] = adj_z;
    vcRotTransRoadArea(cppos, use_near_p->rd_rim, cppos);
    adj_x = cppos[0];
    adj_z = cppos[2];






    
    out_rd_len = vwRet3DLength(adj_x - w_p->chara_pos[0], abs_chr2cam_y, adj_z - w_p->chara_pos[2]);


    
    if (stage->glb_crd == 1 && sh2jms.player->pos.x >= -20000.0f) {
        no_adj_max_dist = 1.75f * mv_nml_no_adj_max_dist[cur_rd_area_size];

        
        full_adj_min_dist = 1.75f * mv_nml_full_adj_min_dist[cur_rd_area_size];

        
    } else if (sh2jms.player->status & 0x20000) {
        no_adj_max_dist = 1600.0f;
        full_adj_min_dist = 5000.0f;
    } else {
        no_adj_max_dist = mv_nml_no_adj_max_dist[cur_rd_area_size];
        full_adj_min_dist = mv_nml_full_adj_min_dist[cur_rd_area_size];
    }
    
    if (out_rd_len > full_adj_min_dist) {
        chara2ideal_r = 200.0f;
    } else if (out_rd_len > no_adj_max_dist) {
        chara2ideal_r += ((200.0f - chara2ideal_r) * (out_rd_len - no_adj_max_dist)) / (full_adj_min_dist - no_adj_max_dist);
        
        // @hack needed to get extra nops here?
        if (((!w_p) && (!w_p)) && (!w_p))
        {
        }
    }


    
    ideal_pos[0] = w_p->chara_pos[0] + (chara2ideal_r * shSinF(w_p->cam_chara2ideal_ang_y));
    
    ideal_pos[2] = w_p->chara_pos[2] + (chara2ideal_r * shCosF(w_p->cam_chara2ideal_ang_y));



    vcTransRotRoadArea(cppos, use_near_p->rd_rzm, ideal_pos);
    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&cppos[0], &cppos[2], &use_near_p->rd);



    
    vcRotTransRoadArea(cppos, use_near_p->rd_rim, cppos);
    ideal_pos[0] = cppos[0];
    ideal_pos[2] = cppos[2];
    
}

#line 3896
void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(float* x_p, float* z_p, VC_LIMIT_AREA* lim_p) {
    float x = *x_p, z = *z_p;
    float min_in_road_dist;
    float min_x, max_x, min_z, max_z;
    
    min_in_road_dist = vcGetMinInRoadDist();

    min_x = lim_p->min_hx + min_in_road_dist;
    max_x = lim_p->max_hx - min_in_road_dist;
    min_z = lim_p->min_hz + min_in_road_dist;
    max_z = lim_p->max_hz - min_in_road_dist;

    
    if (min_x > max_x) min_x = max_x = (min_x + max_x) / 2.0f;
    if (min_z > max_z) min_z = max_z = (min_z + max_z) / 2.0f;

    
    x = CLAMP(x, min_x, max_x);
    z = CLAMP(z, min_z, max_z);

    *x_p = x; *z_p = z;
}

#line 3941
void vcMakeBasicCamTgtMvVec(sceVu0FVECTOR tgt_mv_vec, sceVu0FVECTOR ideal_pos, VC_WORK* w_p, float max_tgt_mv_xz_len) {
    sceVu0FVECTOR xz_vec;
    sceVu0FVECTOR sincos_y;
    float now2ideal_tgt_dist;
    float now2ideal_tgt_ang_y;



    
    vec_sub_xyz(ideal_pos, w_p->cam_tgt_pos, xz_vec);
    
    now2ideal_tgt_dist = vec_length(xz_vec);
    
    now2ideal_tgt_ang_y = shAtanV(xz_vec);
    
    if (now2ideal_tgt_dist < max_tgt_mv_xz_len) {
        vec_copy_xyz(tgt_mv_vec, xz_vec);
    } else {

        
        shSinCosV(sincos_y, now2ideal_tgt_ang_y);
        vec_scale_xyz(max_tgt_mv_xz_len, sincos_y, tgt_mv_vec);
    }


    
    if (shGetDT() == 0.0f && !(vcWork.flags & VC_WARP_CAM_TGT_F)) tgt_mv_vec[1] = 0.0f;
    else tgt_mv_vec[1] = ideal_pos[1] - w_p->cam_tgt_pos[1];
}

#line 3990 
void vcAdjTgtMvVecYByCurNearRoad(sceVu0FVECTOR tgt_mv_vec, VC_WORK* w_p) {
    float tgt_y;
    float abs_ofs_y;
    float min_dist, max_dist;
    float dist;
    float to_chara_dist;
    float near_ratio;
    VC_ROAD_DATA* cur_rd_p = w_p->cur_near_road.road_p; 
    float min_tgt_y, max_tgt_y;

    to_chara_dist = vec3_dist_xz(w_p->cam_tgt_pos, w_p->chara_pos);

    
    if (cur_rd_p->mv_y_type == VC_MV_LOCUS_CIRCLE || cur_rd_p->mv_y_type == VC_MV_THROUGH_DOOR) {

        
        if (w_p->cur_near_road.road_p->cam_mv_type != VC_MV_LOCUS_CIRCLE) {
            near_ratio = vcRetNearRatioSwitchAreaInXZPos(w_p->cur_near_road, w_p->chara_pos, w_p->cam_tgt_pos);


            
        } else {
            near_ratio = vcRetNearRatioSwitchAreaForCircleCam(w_p->cur_near_road, w_p->cir_man, w_p->chara_pos);



            
            if (cur_rd_p->tmp.chs.lr_lim_ang_y < TO_RAD(-180.0f) || cur_rd_p->tmp.chs.lr_lim_ang_y >= TO_RAD(180.0f)) {
                
                
                
                near_ratio = 1.0f - near_ratio;
            }
        }
    } else {
        dist = to_chara_dist;



        
        if (stage->glb_crd != 5 && stage->glb_crd != 2) {
            
            max_dist = 3500.0f;
            min_dist = 600.0f;
        } else {

            
            max_dist = 15500.0f;
            min_dist = 500.0f;
        }


        
        dist = float_clamp(dist, min_dist, max_dist);

        
        near_ratio = (max_dist - dist) * (1.0f / (max_dist - min_dist));
    }
    near_ratio = CLAMP(near_ratio, 0.0f, 1.0f);

    switch (w_p->cur_near_road.road_p->mv_y_type) {
        default:
            ASSERT(0);
        case VC_MV_CHASE:


            
            abs_ofs_y = float_max(0.0f, (to_chara_dist - 150.0f) / 4.0f);
            
            if (stage->glb_crd == 1 && sh2jms.player->pos.x >= -20000.0f) {
                max_tgt_y = -750.0f + (abs_ofs_y + w_p->chara_top_y);
                min_tgt_y = -750.0f + (-abs_ofs_y + w_p->chara_top_y);
            } else {
                max_tgt_y = -250.0f + (abs_ofs_y + w_p->chara_top_y);
                min_tgt_y = -250.0f + (-abs_ofs_y + w_p->chara_top_y);
            }
            
            break;
        case VC_MV_SETTLE:
            max_tgt_y = 
                min_tgt_y = 
                    cur_rd_p->lim_rd.min_hy * (1.0f - near_ratio) + cur_rd_p->lim_rd.max_hy * near_ratio;
            
            break;
        case VC_MV_FIX_ANG:
            max_tgt_y = 
                min_tgt_y = 
                    cur_rd_p->lim_rd.max_hy * (1.0f - near_ratio) + cur_rd_p->lim_rd.min_hy * near_ratio;

            break;
        case VC_MV_SELF_VIEW:


            
            min_tgt_y = cur_rd_p->lim_rd.max_hy;
            max_tgt_y = cur_rd_p->lim_rd.min_hy;
            break;
        case VC_MV_LOCUS_CIRCLE: {
            float ofs_y;

            
            if (BgIsOut(0) != 0 || stage->glb_crd == 5) ofs_y = -250.0f;
            else ofs_y = 0.0f;
            
            min_tgt_y = 
                max_tgt_y = 
                    (1.0f - near_ratio) * (ofs_y + (cur_rd_p->lim_rd.min_hy + w_p->chara_pos[1])) + w_p->ideal_cam_pos_h * near_ratio;


            
            break;
        }
        case VC_MV_THROUGH_DOOR: {
            float ofs_y;
            
            if (BgIsOut(0) != 0 || stage->glb_crd == 5) ofs_y = -250.0f;
            else ofs_y = 0.0f;
            
            max_tgt_y = 
                min_tgt_y = 
                    (1.0f - near_ratio) * (ofs_y + (cur_rd_p->lim_rd.max_hy + w_p->chara_pos[1])) + w_p->ideal_cam_pos_h * near_ratio;



            break;
        }
    }


    

    tgt_y = w_p->cam_tgt_pos[1] + tgt_mv_vec[1];
    tgt_y = CLAMP(tgt_y, min_tgt_y, max_tgt_y);
    tgt_mv_vec[1] = tgt_y - w_p->cam_tgt_pos[1];
    
}

#line 4149
void vcCamTgtMvVecIsFlipedFromCharaFront(sceVu0FVECTOR tgt_mv_vec, VC_WORK* w_p, float max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size) {
    float flip_ang_y, chk_near_dist, flip_dist, pre_nearest_dist, min_in_road_dist, min_x, max_x, min_z, max_z, mv_len, ang_y;
    VC_NEAR_ROAD_DATA* use_nearest_p;
    sceVu0FVECTOR pre_tgt_pos, chk_pos, post_tgt_pos, sincos_y, pos;
    
    vec_add_xyz(tgt_mv_vec, w_p->cam_tgt_pos, pre_tgt_pos);
    pre_tgt_pos[1] = 0;
    pre_tgt_pos[3] = 1.0f;
    
    flip_dist = vcFlipFromCamExclusionArea(&flip_ang_y, &w_p->old_cam_excl_area_r, pre_tgt_pos, w_p->chara_pos, w_p->chara_eye_ang_y, cur_rd_area_size);
    
    
    
    
    
    
    
    
    if (flip_dist <= 0.0f) {
        return;
    }





    
    if (flip_dist > 250.0f) chk_near_dist = 250.0f;
    else chk_near_dist = flip_dist;




    
    vec_zero(sincos_y);
    shSinCosV(&sincos_y, flip_ang_y);
    vec_scale_xyz(chk_near_dist, sincos_y, chk_pos);
    vec_add_xyz(pre_tgt_pos, chk_pos, chk_pos);
    

    if (!(w_p->cur_near_road.road_p->flags & VC_RD_MARGE_ROAD_F)) {
        
        use_nearest_p = &w_p->cur_near_road;
    } else {
        
        pre_nearest_dist = vcGetNearestNEAR_ROAD_DATA(&use_nearest_p, VC_CHK_NEAREST_ROAD_TYPE, w_p->cur_near_road.road_p->rd_type, pre_tgt_pos, w_p, 1);
        
        
        
        
        
        
        
        
        if (use_nearest_p == NULL)
            use_nearest_p = &vcNullNearRoad;
        else if (pre_nearest_dist > 0.0f)
            
            use_nearest_p = &w_p->cur_near_road;
        
    }



    
    vec_scale_xyz(flip_dist, sincos_y, post_tgt_pos);
    vec_add_xyz(pre_tgt_pos, post_tgt_pos, post_tgt_pos);





    
    ASSERT(use_nearest_p != 0L);

    min_in_road_dist = vcGetMinInRoadDist();
    
    min_x = use_nearest_p->rd.min_hx + min_in_road_dist;
    max_x = use_nearest_p->rd.max_hx - min_in_road_dist;
    min_z = use_nearest_p->rd.min_hz + min_in_road_dist;
    max_z = use_nearest_p->rd.max_hz - min_in_road_dist;
    if (min_x > max_x) min_x = max_x = (min_x + max_x) / 2.0f;
    if (min_z > max_z) min_z = max_z = (min_z + max_z) / 2.0f;



    
    vcTransRotRoadArea(pos, use_nearest_p->rd_rzm, post_tgt_pos);
    pos[0] = CLAMP(pos[0], min_x, max_x);
    pos[2] = CLAMP(pos[2], min_z, max_z);
    vcRotTransRoadArea(post_tgt_pos, use_nearest_p->rd_rim, pos);


    
    tgt_mv_vec[0] = post_tgt_pos[0] - w_p->cam_tgt_pos[0];
    tgt_mv_vec[2] = post_tgt_pos[2] - w_p->cam_tgt_pos[2];



    
    mv_len = vec_length(tgt_mv_vec);
    
    if (mv_len > max_tgt_mv_xz_len) {


        ang_y = shAtanV(tgt_mv_vec);




        
        shSinCosV(&sincos_y, ang_y);
        vec_scale_xyz(max_tgt_mv_xz_len, sincos_y, tgt_mv_vec);
    }


    
}

const u_char unkPadding_00390668X[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // @hack: Weird padding after ASSERT strings.

#line 4294
float vcFlipFromCamExclusionArea(float* flip_ang_y_p, float* old_cam_excl_area_r_p, sceVu0FVECTOR in_pos, sceVu0FVECTOR chara_pos, float chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size) {
    float cntr2pos_ang_y;
    float dist;
    float min_add_dist;
    float ret_flip_dist;
    float ofs_ang_y;
    float cam_excl_area_r;
    float rate;
    float add_dist;
    float cntr_z; // unused? the shAtan2 temporaries could be it, but line numbers show them on same line..
    float cntr_x; // unused? ^

    cntr2pos_ang_y = shAtan2(in_pos[2] - chara_pos[2], in_pos[0] - chara_pos[0]);






    ofs_ang_y = shAngleRegulate(cntr2pos_ang_y - chara_eye_ang_y);
    if (ofs_ang_y < 0.0f) ofs_ang_y *= -1.0f;
    
    if (stage->glb_crd == 1 && sh2jms.player->pos.x >= -20000.0f) {
        rate = 1.25f * excl_max_rate[cur_rd_area_size];
    } else {
        rate = excl_max_rate[cur_rd_area_size];
    }
    
    cam_excl_area_r = vwOresenHokan(excl_r_ary, sizeof(excl_r_ary) / sizeof(int), 
                                    ofs_ang_y * 4096.0f, // @todo: Q12 macro?
                                    0, 
                                    TO_RAD(180.0f) * 4096.0f);
    
    cam_excl_area_r = 500.0f * cam_excl_area_r;
    cam_excl_area_r = cam_excl_area_r / 4096.0f;
    cam_excl_area_r = rate * cam_excl_area_r;

    
    if (*old_cam_excl_area_r_p != -1.0f) {

        
        min_add_dist = -250.0f * shGetDT();
        add_dist = cam_excl_area_r - *old_cam_excl_area_r_p;
        
        if (add_dist < min_add_dist) {
            add_dist = min_add_dist;
        }
        cam_excl_area_r = *old_cam_excl_area_r_p + add_dist;
    }
    *old_cam_excl_area_r_p = cam_excl_area_r;



    
    dist = vec3_dist_xz(chara_pos, in_pos);
    
    if (dist < cam_excl_area_r) ret_flip_dist = cam_excl_area_r - dist;
    else ret_flip_dist = 0.0f;

    
    *flip_ang_y_p = cntr2pos_ang_y;
    
    return ret_flip_dist;
}

#line 4382
void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, float self_view_eff_rate, float far_watch_rate, VC_WORK* w_p) {
    
    if (w_p->flags & VC_USER_WATCH_F) {
        *watch_mv_prm_pp = &w_p->user_watch_mv_prm;
    } else {
        const VC_WATCH_MV_PARAM* wth_mv_prm_stg_p;
        float add_ang_accel_y;






        
        if (BgIsOut(0) != 0 || stage->glb_crd == 5) {
            if (!(sh2jms.player->status & 0x20000)) {
                wth_mv_prm_stg_p = &watch_mv_prm_outdoor;
            } else {
                wth_mv_prm_stg_p = &watch_mv_prm_on_boat;
            }
        } else {
            wth_mv_prm_stg_p = &watch_mv_prm_nrml;
        }



        
        vcWatchMvPrmSt.ang_accel_x = wth_mv_prm_stg_p->ang_accel_x + (self_view_eff_rate * (self_view_watch_mv_prm.ang_accel_x - wth_mv_prm_stg_p->ang_accel_x));
        
        
        
        vcWatchMvPrmSt.ang_accel_y = wth_mv_prm_stg_p->ang_accel_y + (self_view_eff_rate * (self_view_watch_mv_prm.ang_accel_y - wth_mv_prm_stg_p->ang_accel_y));
        
        
        
        vcWatchMvPrmSt.max_ang_spd_x = wth_mv_prm_stg_p->max_ang_spd_x + (self_view_eff_rate * (self_view_watch_mv_prm.max_ang_spd_x - wth_mv_prm_stg_p->max_ang_spd_x));
        
        
        
        vcWatchMvPrmSt.max_ang_spd_y = wth_mv_prm_stg_p->max_ang_spd_y + (self_view_eff_rate * (self_view_watch_mv_prm.max_ang_spd_y - wth_mv_prm_stg_p->max_ang_spd_y));
        
        *watch_mv_prm_pp = &vcWatchMvPrmSt;
        
        if (BgIsOut(0) == 0 && stage->glb_crd != 5) {
            vcWatchMvPrmSt.ang_accel_x += (wth_mv_prm_stg_p->ang_accel_x * far_watch_rate) / 2.0f;
            
            vcWatchMvPrmSt.ang_accel_y += (wth_mv_prm_stg_p->ang_accel_y * far_watch_rate) / 2.0f;
            
            vcWatchMvPrmSt.max_ang_spd_x += (wth_mv_prm_stg_p->max_ang_spd_x * far_watch_rate) / 2.0f;
            
            vcWatchMvPrmSt.max_ang_spd_y += (wth_mv_prm_stg_p->max_ang_spd_y * far_watch_rate) / 2.0f;
        }


        
        add_ang_accel_y = w_p->chara_mv_spd;
        add_ang_accel_y = CLAMP(add_ang_accel_y, 0.0f, 2.0f);
        vcWatchMvPrmSt.ang_accel_y += add_ang_accel_y;

        
    }
    if (w_p->flags & VC_USER_CAM_F) {
        *cam_mv_prm_pp = &w_p->user_cam_mv_prm;
    } else {
        const VC_CAM_MV_PARAM* cam_mv_prm_stg_p;
        float diameter;
        
        if (BgIsOut(0) != 0 || stage->glb_crd == 5) {
            if (!(sh2jms.player->status & 0x20000)) {
                cam_mv_prm_stg_p = &cam_mv_prm_outdoor;
                diameter = 1.0f;
            } else {
                cam_mv_prm_stg_p = &cam_mv_prm_on_boat;
                diameter = 1.0f;
            }
        } else {
            cam_mv_prm_stg_p = &cam_mv_prm_nrml;
            diameter = 1.0f + far_watch_rate;
        }
        
        vcCamMvPrmSt.accel_xz = cam_mv_prm_stg_p->accel_xz * diameter;
        vcCamMvPrmSt.accel_y = cam_mv_prm_stg_p->accel_y * diameter;
        vcCamMvPrmSt.max_spd_xz = cam_mv_prm_stg_p->max_spd_xz * diameter;
        vcCamMvPrmSt.max_spd_y = cam_mv_prm_stg_p->max_spd_y * diameter;
        
        *cam_mv_prm_pp = &vcCamMvPrmSt;
    

    }
}

#line 4490
void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) {
    if (w_p->flags & VC_WARP_CAM_F) {
        w_p->cam_mv_ang_y = shAtan2(
                                    w_p->cam_tgt_pos[2] - w_p->cam_pos[2], 
                                    w_p->cam_tgt_pos[0] - w_p->cam_pos[0]
                                   );

        vec_copy(w_p->cam_pos, w_p->cam_tgt_pos);
        vec_zero(w_p->cam_velo);
        return; // removing this return affects the 0.4f floats below, weird
    } else {
        sceVu0FVECTOR cpos, tpos;
        float dt;
        float dec_spd_per_dist_xz = 0.4f * cam_mv_prm_p->accel_xz;
        float dec_spd_per_dist_y = cam_mv_prm_p->accel_y;




        
        vec_copy(cpos, w_p->cam_pos);
        vec_copy(tpos, w_p->cam_tgt_pos);
        cpos[0] /= 500.0f;
        cpos[2] /= 500.0f;
        tpos[0] /= 500.0f;
        tpos[2] /= 500.0f;
        
        vwRenewalXZVelocityToTargetPos(w_p->cam_velo, 
                                       cpos, 
                                       tpos, 
                                       0.1f, 
                                       cam_mv_prm_p->accel_xz, 
                                       cam_mv_prm_p->max_spd_xz, 
                                       dec_spd_per_dist_xz, 
                                       6000.0f
                                      );
        
        
        
        w_p->cam_velo[1] = vwRetNewVelocityToTargetVal(
            w_p->cam_velo[1], 
            w_p->cam_pos[1] / 500.0f, 
            w_p->cam_tgt_pos[1] / 500.0f, 
            cam_mv_prm_p->accel_y, 
            cam_mv_prm_p->max_spd_y, 
            dec_spd_per_dist_y
            );


        
        w_p->cam_mv_ang_y = shAtanV(w_p->cam_velo);


        
        dt = shGetDT();
    
        // Not inline func based on line numbers  TODO: one bad 4546 line number here
        asm("lqc2 vf4, 0(%1)\n\
         lqc2 vf5, 0(%2)\n\
         mfc1 t7, %0\n\
         qmtc2 t7, vf6\n\
         vmulx.xyzw vf4, vf4, vf6x\n\
         vadd.xyzw vf4, vf4, vf5\n\
         sqc2 vf4, 0(%2)" \
        : : "f"(dt), "r"(w_p->cam_velo), "r"(w_p->cam_pos) : "t7");












        
    }
}

#line 4593
void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, int visible_chara_f) {
    sceVu0FVECTOR ofs_tgt_ang;
    sceVu0FVECTOR new_base_cam_ang;
    sceVu0FMATRIX new_base_matT;
    sceVu0FVECTOR ofs_cam2chara_btm_ang;
    sceVu0FVECTOR ofs_cam2chara_top_ang;

    vcMakeNewBaseCamAng(new_base_cam_ang, cam_mv_type, w_p);
    
    if (new_base_cam_ang[0] != w_p->base_cam_ang[0] || 
        new_base_cam_ang[1] != w_p->base_cam_ang[1] || 
        new_base_cam_ang[2] != w_p->base_cam_ang[2]) {


        
        vcRenewalBaseCamAngAndAdjustOfsCamAng(w_p, new_base_cam_ang);
    }
    vu0_unit_matrix(new_base_matT);
    vwRotMatrixYXZ(w_p->base_cam_ang, new_base_matT);
    vbTransposeMatrixWithoutTr(new_base_matT, new_base_matT);
    vcMakeOfsCamTgtAng(ofs_tgt_ang, new_base_matT, w_p);
    
    if (visible_chara_f) {



        
        vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(ofs_cam2chara_btm_ang, 
                                                    ofs_cam2chara_top_ang, 
                                                    new_base_matT, 
                                                    w_p->cam_pos, 
                                                    w_p->chara_pos, 
                                                    w_p->chara_bottom_y + w_p->cur_near_road.road_p->trace_btm_hy, 
                                                    w_p->chara_top_y);
        
        
        
        
        
        vcAdjCamOfsAngByCharaInScreen(ofs_tgt_ang, ofs_cam2chara_btm_ang, ofs_cam2chara_top_ang, w_p);
    }




    
    if (w_p->flags & VC_WARP_WATCH_F) {
        vec_copy(w_p->ofs_cam_ang, ofs_tgt_ang);
        vec_zero(w_p->ofs_cam_ang_spd);
    } else {
        
        vcAdjCamOfsAngByOfsAngSpd(w_p->ofs_cam_ang, w_p->ofs_cam_ang_spd, ofs_tgt_ang, watch_mv_prm_p);
    }





    
    if (!(vcWork.flags & (VC_USER_CAM_F | VC_USER_WATCH_F))) {
        vcCorrectCamMatAngForcibly(w_p->ofs_cam_ang, w_p->cur_near_road.road_p);
    }




    
    vcMakeCamMatAndCamAngByBaseAngAndOfsAng(w_p->cam_mat_ang, w_p->cam_mat, new_base_cam_ang, w_p->ofs_cam_ang, w_p->cam_pos);
    
    
    
    
    w_p->ofs_cam_ang[0] = shAngleRegulate(w_p->ofs_cam_ang[0]);
    w_p->ofs_cam_ang[1] = shAngleRegulate(w_p->ofs_cam_ang[1]);
    w_p->ofs_cam_ang[2] = shAngleRegulate(w_p->ofs_cam_ang[2]);
}

// Weird bit-level float hack, used when comparing float to 0.0f, @todo: Can this be emitted by compiler?
static inline float flush_denorm(float f1)
{
    __asm__ volatile (
        "nop\n\
        .set noreorder\n\
        lui     $t5, 0x7F80\n\
        mfc1    $t7, %0\n\
        lui     $t6, 0x3780\n\
        and     $t7, $t7, $t5\n\
        slt     $t7, $t7, $t6\n\
        bnel    $t7, $zero, 1f\n\
         mtc1   $zero, %0\n\
        .set reorder\n\
        1:"
        : "+f"(f1)
        :
        : "t5", "t6", "t7"
    );

    return f1;
}

#line 4689
void vcMakeNewBaseCamAng(sceVu0FVECTOR new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p) {
    sceVu0FVECTOR xyz_vec;
    float cam2watch_ang_y, cam2watch_ang_x;
    float deflt_sta_base_ang_y, deflt_end_base_ang_y;
    float ofs_sta_ang_y, ofs_end_ang_y, max_ang_y_spd, mv_ang_y;
    float new_base_ang_x, new_base_ang_y;

    vec_sub_xyz_reverse(w_p->cam_pos, w_p->watch_tgt_pos, xyz_vec);
    
    if (w_p->flags & VC_USER_WATCH_F) {
        vec_zero(new_base_ang);
    } else {
        switch (cam_mv_type) {
            default:
                ASSERT(0);
            case 0:
            case 2:
            case 3:
            case 4:
            case 5:
                vec_zero(new_base_ang);
                return;
            case 1:
                cam2watch_ang_x = shAtan2(vec_length(xyz_vec), -xyz_vec[1]);
                cam2watch_ang_y = shAtanV(&xyz_vec);







                
                deflt_sta_base_ang_y = w_p->cur_near_road.road_p->tmp.stl.sta_base_ang_y;
                
                deflt_end_base_ang_y = w_p->cur_near_road.road_p->tmp.stl.end_base_ang_y;


                
                ofs_sta_ang_y = shAngleRegulate(cam2watch_ang_y - deflt_sta_base_ang_y);
                
                ofs_end_ang_y = shAngleRegulate(cam2watch_ang_y - deflt_end_base_ang_y);

                
                if (ofs_sta_ang_y >= TO_RAD(0.0f) && ofs_end_ang_y <= TO_RAD(0.0f))

                    
                    new_base_ang_y = cam2watch_ang_y;
                else if (float_abs(ofs_sta_ang_y) < float_abs(ofs_end_ang_y))
                    
                    new_base_ang_y = deflt_sta_base_ang_y;
                else
                    new_base_ang_y = deflt_end_base_ang_y;
                

                
                if (w_p->flags & VC_WARP_WATCH_F) {
                    new_base_ang_y = new_base_ang_y; // @hack
                } else {
                    if (flush_denorm(w_p->chara_mv_spd) && float_abs(cam2watch_ang_x) < TO_RAD(75.0f)) {




                        
                        mv_ang_y = shAngleRegulate(new_base_ang_y - w_p->base_cam_ang[1]);

                        
                        max_ang_y_spd = TO_RAD(120.0f) * shGetDT();
                        
                        mv_ang_y = CLAMP(mv_ang_y, -max_ang_y_spd, max_ang_y_spd);
                        
                        new_base_ang_y = mv_ang_y + w_p->base_cam_ang[1];
                    } else {
                        new_base_ang_y = w_p->base_cam_ang[1];
                    }
                }
                
                new_base_ang_x = cam2watch_ang_x;
                if (new_base_ang_x < 0.0f) new_base_ang_x *= -1.0f;

                
                new_base_ang_x = vwOresenHokan(mv_stl_ang_ary, sizeof(mv_stl_ang_ary) / sizeof(int), 
                                               new_base_ang_x * 4096.0f,
                                               0, 
                                               TO_RAD(90.0f) * 4096.0f);
                
                new_base_ang_x = new_base_ang_x / 4096.0f;
                
                new_base_ang_x = CLAMP(new_base_ang_x, TO_RAD(0.0f), TO_RAD(90.0f));
                
                if (cam2watch_ang_x < 0.0f) new_base_ang_x *= -1.0f;
                
                vec_zero_xyz(new_base_ang);
                new_base_ang[0] = new_base_ang_x; 
                new_base_ang[1] = new_base_ang_y;
            
        }
    }
}

#line 4807
void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, sceVu0FVECTOR new_base_cam_ang) {
    sceVu0FMATRIX old_base_mat, new_base_mat, new_base_matT;
    sceVu0FMATRIX adj_ofs_mat, ofs_mat;

    vu0_unit_matrix(adj_ofs_mat);
    vu0_unit_matrix(old_base_mat);
    vu0_unit_matrix(new_base_mat);
    vu0_unit_matrix(ofs_mat);

    vwRotMatrixYXZ(w_p->base_cam_ang, old_base_mat);
    vwRotMatrixYXZ(new_base_cam_ang, new_base_mat);
    vbTransposeMatrixWithoutTr(new_base_matT, new_base_mat);
    
    vwRotMatrixYXZ(w_p->ofs_cam_ang, ofs_mat);
    shMulMatrix(adj_ofs_mat, new_base_matT, old_base_mat);
    shMulMatrix(ofs_mat, adj_ofs_mat, ofs_mat);
    vwMatrixToAngleYXZ(w_p->ofs_cam_ang, ofs_mat);
    vec_copy(w_p->base_cam_ang, new_base_cam_ang);
}

#line 4846
void vcMakeOfsCamTgtAng(sceVu0FVECTOR ofs_tgt_ang, sceVu0FMATRIX base_matT, VC_WORK* w_p) {
    sceVu0FVECTOR vec;

    
    vec_sub_xyz_reverse(w_p->cam_pos, w_p->watch_tgt_pos, vec);
    
    vbApplyMatrixWithoutTr(vec, base_matT, vec);
    vwVectorToAngle(ofs_tgt_ang, vec);
    ofs_tgt_ang[2] = w_p->watch_tgt_ang_z;
}

#line 4884
void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(sceVu0FVECTOR ofs_cam2chara_btm_ang, sceVu0FVECTOR ofs_cam2chara_top_ang, sceVu0FMATRIX base_matT, sceVu0FVECTOR cam_pos, sceVu0FVECTOR chara_pos, float chara_bottom_y, float chara_top_y) {
    sceVu0FVECTOR vec;

    
    vec_sub_xyz_reverse(cam_pos, chara_pos, vec);
    vec[1] = chara_bottom_y - cam_pos[1];

    
    vbApplyMatrixWithoutTr(vec, base_matT, vec);
    
    vwVectorToAngle(ofs_cam2chara_btm_ang, vec);
    
    vec_sub_xyz_reverse(cam_pos, chara_pos, vec);
    vec[1] = chara_top_y - cam_pos[1];

    
    vbApplyMatrixWithoutTr(vec, base_matT, vec);
    
    vwVectorToAngle(ofs_cam2chara_top_ang, vec);
}

#line 4928
void vcAdjCamOfsAngByCharaInScreen(sceVu0FVECTOR cam_ang, sceVu0FVECTOR ofs_cam2chara_btm_ang, sceVu0FVECTOR ofs_cam2chara_top_ang, VC_WORK* w_p) {
    float temp_f1_2;
    float watch2chr_ofs_ang_y;
    float watch2chr_bottom_ofs_ang_x;
    float watch2chr_top_ofs_ang_x;
    float adj_cam_ang_y;
    float adj_cam_ang_x;

    watch2chr_ofs_ang_y = shAngleRegulate(ofs_cam2chara_top_ang[1] - cam_ang[1]);
    
    watch2chr_bottom_ofs_ang_x = shAngleRegulate(ofs_cam2chara_btm_ang[0] - cam_ang[0]);

    
    watch2chr_top_ofs_ang_x = shAngleRegulate(ofs_cam2chara_top_ang[0] - cam_ang[0]);


    if (watch2chr_ofs_ang_y > w_p->scr_half_ang_wx) {
        adj_cam_ang_y = shAngleRegulate(watch2chr_ofs_ang_y - w_p->scr_half_ang_wx);
        
    } else if (watch2chr_ofs_ang_y < -w_p->scr_half_ang_wx) {
        adj_cam_ang_y = shAngleRegulate(watch2chr_ofs_ang_y + w_p->scr_half_ang_wx);
        
    } else {
        adj_cam_ang_y = 0.0f;
    }

    ASSERT(w_p->scr_half_ang_wy > ((3.14159265358979f/180.0f)*(5.0f))); // @todo: should be ASSERT(w_p->scr_half_ang_wy > TO_RAD(5.0f)), macro isn't being expanded?
    
    if (watch2chr_bottom_ofs_ang_x < -w_p->scr_half_ang_wy) {
        
        adj_cam_ang_x = watch2chr_bottom_ofs_ang_x + w_p->scr_half_ang_wy;
    } else {
        adj_cam_ang_x = 0.0f;
    }



    
    if (watch2chr_top_ofs_ang_x - adj_cam_ang_x > w_p->scr_half_ang_wy) {
        adj_cam_ang_x += (watch2chr_top_ofs_ang_x - adj_cam_ang_x) - w_p->scr_half_ang_wy;
    }

    
    adj_cam_ang_x = CLAMP(adj_cam_ang_x, TO_RAD(-30.0f), TO_RAD(30.0f));

    
    cam_ang[1] += adj_cam_ang_y;
    cam_ang[0] += adj_cam_ang_x;
}

// @todo: Issue with float args to `vwRetNewAngSpdToTargetAng`, matched at https://decomp.me/scratch/iIZHY
INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjCamOfsAngByOfsAngSpd);

#line 5085
void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(sceVu0FVECTOR cam_mat_ang, 
                                             sceVu0FMATRIX cam_mat, 
                                             sceVu0FVECTOR base_cam_ang, 
                                             sceVu0FVECTOR ofs_cam_ang, 
                                             sceVu0FVECTOR cam_pos) {
    sceVu0FMATRIX base_mat;
    sceVu0FMATRIX ofs_mat;






    
    
    vu0_unit_matrix(base_mat);
    vu0_unit_matrix(ofs_mat);
    
    vwRotMatrixYXZ(base_cam_ang, base_mat);
    vwRotMatrixYXZ(ofs_cam_ang, ofs_mat);
    
    shMulMatrix(cam_mat, base_mat, ofs_mat);
    
    vec_zero_xyz(cam_mat[3]);
    vec_copy_xyz(cam_mat[3], cam_pos);
    
    vwMatrixToAngleYXZ(cam_mat_ang, cam_mat);
}

// @todo: Issue with float args to `vcCamMatNoise`, matched at https://decomp.me/scratch/mlHnL
INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetDataToVwSystem);

#line 5181
float vcCamMatNoise(float noise_w, float ang_spd1, float ang_spd2) {
    float noise;

    ang_spd1 = shAngleRegulate(ang_spd1 * vcSelfViewTimer);
    ang_spd2 = shAngleRegulate(ang_spd2 * vcSelfViewTimer);
    
    noise = (shCosF(ang_spd1) + shCosF(ang_spd2)) / 2.0f;
    return noise * noise_w;

    
}

#line 5225
float vcGetXZSumDistFromLimArea(float* out_vec_x_p, float* out_vec_z_p, float chk_wld_x, float chk_wld_z, float lim_min_x, float lim_max_x, float lim_min_z, float lim_max_z, int can_ret_minus_dist_f) {
    float cntr_z;
    float cntr_x;
    float x_dist;
    float z_dist;
    float ret_dist;

    if (chk_wld_x > lim_max_x) {
        *out_vec_x_p = x_dist = lim_max_x - chk_wld_x;
        x_dist = -x_dist;
    } else if (chk_wld_x < lim_min_x) {
        *out_vec_x_p = x_dist = lim_min_x - chk_wld_x;
        
    } else {

        
        cntr_x = (lim_max_x + lim_min_x) / 2.0f;
        
        *out_vec_x_p = 0.0f;

        
        if(chk_wld_x >= cntr_x) x_dist = chk_wld_x - lim_max_x;
        else x_dist = lim_min_x - chk_wld_x;
    }

    
    if (chk_wld_z > lim_max_z) {
        *out_vec_z_p = cntr_z = lim_max_z - chk_wld_z;
        z_dist = -cntr_z;
    } else if (chk_wld_z < lim_min_z) {
        *out_vec_z_p = z_dist = lim_min_z - chk_wld_z;
        
    } else {

        
        cntr_z = (lim_max_z + lim_min_z) / 2.0f;
        
        *out_vec_z_p = 0.0f;

        
        if (chk_wld_z >= cntr_z) z_dist = chk_wld_z - lim_max_z;
        else z_dist = lim_min_z - chk_wld_z;
    }
    
    if (x_dist >= 0.0f) {
        if (z_dist >= 0.0f)
            ret_dist = x_dist + z_dist;
        else 
            ret_dist = x_dist;
    } else {
        if (z_dist >= 0.0f)
            ret_dist = z_dist;
        else
            ret_dist = float_max(x_dist, z_dist);
    }
    
    if (!can_ret_minus_dist_f && ret_dist < 0.0f) {
        ret_dist = 0.0f;
    }
    
    return ret_dist;
}

#line 5361
void vcSetEventCamParamRefView(sceVu0FVECTOR vp, VC_CAM_MV_PARAM* cam_prm_p, sceVu0FVECTOR vr, VC_WATCH_MV_PARAM* watch_prm_p, float rot_z, int warp_flg) {
    
    vcUserCamTarget(vp, cam_prm_p, warp_flg);
    
    vcUserWatchTarget(vr, watch_prm_p, rot_z, warp_flg);
}

#line 5387
void vcSetProjectionValue(float new, int framecnt) {
    if (new == 0.0f) {

        
        vcProjectionParam.new = 448.0f;
    } else {
        
        vcProjectionParam.new = new;
    }
    vcProjectionParam.old = VbScreenInfo.scr_z;

    
    if (vcWork.flags & VC_PROJ_MOMENT_CHANGE_F) {
        
        framecnt = 1;
        vcWork.flags &= ~VC_PROJ_MOMENT_CHANGE_F;
    }
    
    if (framecnt < 2)
        vcProjectionParam.flg = 2;
    else {
        
        vcProjectionParam.delta = (vcProjectionParam.new - vcProjectionParam.old) / framecnt;
       
        
        vcProjectionParam.flg = 1;
    }
}

#line 5432
void vcChangeProjectionValue(VC_WORK* w_p) {
    float new;
    // Could this be switch instead?
    if (vcProjectionParam.flg == 0)
        return;
    if (vcProjectionParam.flg == 2) {
        
        new = vcProjectionParam.new;
        vcProjectionParam.flg = 0;
    } else {

        
        new = VbScreenInfo.scr_z;
        new += vcProjectionParam.delta;
        
        if (vcProjectionParam.new > vcProjectionParam.old) {
            
            if (new > vcProjectionParam.new) {
                
                new = vcProjectionParam.new;
                vcProjectionParam.flg = 0;
            }
        } else {

            
            if (new < vcProjectionParam.new) {
                
                new = vcProjectionParam.new;
                vcProjectionParam.flg = 0;
            }
        }
    }

    
    VbScreenInfo.scr_z = new;
    vbCalcViewScreenMatrix();

    
    w_p->scr_half_ang_wx = shAtan2(VbScreenInfo.scr_z, VbScreenInfo.sx) / 2.0f;
    w_p->scr_half_ang_wy = shAtan2(VbScreenInfo.scr_z, VbScreenInfo.sy) / 2.0f;
}
