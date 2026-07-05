#include "vc_main.h"
#include "vb_main.h"
#include "Chacter/sh_character_status.h"
#include "Event/event.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"

const VC_WATCH_MV_PARAM watch_mv_prm_user = {7.539823f, 13.823008f, 1.3823007f, 4.3982296f};

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", watch_mv_prm_nrml);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", watch_mv_prm_outdoor);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", watch_mv_prm_on_boat);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", self_view_watch_mv_prm);

const VC_CAM_MV_PARAM cam_mv_prm_user = {5000.0f, 1500.0f, 3000.0f, 1000.0f};

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", cam_mv_prm_nrml);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", cam_mv_prm_outdoor);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", cam_mv_prm_on_boat);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", nml_tgt_watch_cir_r);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", nml_cam2wth_min_dist);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", far_tgt_watch_cir_r_0x003905C0);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", mv_nml_chr2cam_r);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", mv_nml_no_adj_max_dist);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", mv_nml_full_adj_min_dist);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", extra_boundary_width);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", excl_max_rate);

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
    vcWork.cam_chara2ideal_ang_y = shAngleRegulate(chara_eye_ang_y + PI);
    
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

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcGetNowWatchPos);

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

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1129);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1130);

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

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRetSmoothCamMvF);

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
        
        
        
        
        
        
        
        
        if (abs_ofs_ang_y > 1.2217305f) return 1;
    }

    
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRetFarWatchRate);

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

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1198);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetFlagsByCamMvType);

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

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetNearestEnemyDataInVC_WORK);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetNearestItemDataInVC_WORK);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetNearRoadAryByCharaPos);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1402);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1403_0x00390720);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRetRoadUsePriority);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetCurNearRoadInVC_WORK);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcGetBestNewCurNearRoad);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcGetNearestNEAR_ROAD_DATA);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1526_0x00390760);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1706);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1732);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdvantageDistOfOldCurRoad);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1782);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAutoRenewalWatchTgtPosAndAngZ);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeNormalWatchTgtPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMixSelfViewEffectToWatchTgtPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeFarWatchTgtPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetWatchTgtXzPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetWatchTgtYParam);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjustWatchYLimitHighWhenFarView);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @1828);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2084);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAutoRenewalCamTgtPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRetMaxTgtMvXzLen);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeIdealCamPosByHeadPos);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeIdealCamPosForFixAngCam);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeIdealCamPosForThroughDoorCam);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeIdealCamPosForLocusCircleCam);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeIdealCamPosUseVC_ROAD_DATA);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeBasicCamTgtMvVec);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2472);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjTgtMvVecYByCurNearRoad);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcCamTgtMvVecIsFlipedFromCharaFront);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcFlipFromCamExclusionArea);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcGetUseWatchAndCamMvParam);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRenewalCamData);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRenewalCamMatAng);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2549);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2550);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2740);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeNewBaseCamAng);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcRenewalBaseCamAngAndAdjustOfsCamAng);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeOfsCamTgtAng);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjCamOfsAngByCharaInScreen);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcAdjCamOfsAngByOfsAngSpd);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcMakeCamMatAndCamAngByBaseAngAndOfsAng);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetDataToVwSystem);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcCamMatNoise);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcGetXZSumDistFromLimArea);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetEventCamParamRefView);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcSetProjectionValue);

INCLUDE_ASM("asm/nonmatchings/view/vc_main", vcChangeProjectionValue);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2813);

INCLUDE_RODATA("asm/nonmatchings/view/vc_main", @2814);
