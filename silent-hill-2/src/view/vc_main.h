#ifndef VC_MAIN_H
#define VC_MAIN_H

#include "sh2_common.h"
#include "Chacter/character.h"

// SH1-style CLAMP macro, used a lot in SH1 code, but most of SH2 uses `float_clamp`?
// Maybe only used in `vc` since this was reused from SH1.
#define CLAMP(x, min, max) \
    (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

typedef enum _VC_ROAD_TYPE { // : u_char
    VC_RD_TYPE_ROAD,
    VC_RD_TYPE_EFFECT,
    VC_RD_TYPE_EVENT,
    VC_RD_TYPE_ROAD_PRIO_LOW,
    VC_RD_TYPE_ROAD_PRIO_HIGH,
    VC_RD_TYPE_SV_ONLY,
    VC_RD_TYPE_SUU
} VC_ROAD_TYPE;

// @note: guessed name, enum was unnamed in symbols?
typedef enum { // : u_char
    VC_CHK_NEAREST_ROAD_TYPE,
    VC_CHK_NEAREST_SWITCH_TYPE
} VC_CHK_TYPE;

typedef enum _VC_FLAGS {
    VC_USER_CAM_F = 0x1,
    VC_USER_WATCH_F = 0x2,
    VC_WARP_CAM_F = 0x4,
    VC_WARP_WATCH_F = 0x8,
    VC_WARP_CAM_TGT_F = 0x10,
    VC_SWITCH_NEAR_RD_DATA_F = 0x20,
    VC_PROJ_MOMENT_CHANGE_F = 0x40,
    VC_VISIBLE_CHARA_F = 0x80,
    VC_INHIBIT_FAR_WATCH_F = 0x100,
    VC_PRS_F_VIEW_F = 0x200,
    VC_OLD_PRS_F_VIEW_F = 0x400,

    VC_INIT_FLAGS = 0x1c,
    VC_ALL_CAM_FLAGS = 0x5,
    VC_ALL_WATCH_FLAGS = 0x82,
    VC_USER_MODE_FLAGS = 0x3,
    VC_ALL_WARP_FLAGS = 0x1c
} VC_FLAGS;

typedef struct _VC_THROUGH_DOOR_CAM_PARAM {
    /* 0x00 */ int active_f;
    /* 0x04 */ float timer;
    /* 0x08 */ float rail_ang_y;
    /* 0x10 */ sceVu0FVECTOR rail_sta_pos;
    /* 0x20 */ float rail_sta_to_chara_dist;
} VC_THROUGH_DOOR_CAM_PARAM;

typedef struct _VC_CAM_MV_PARAM {
    /* 0x0 */ float accel_xz;
    /* 0x4 */ float accel_y;
    /* 0x8 */ float max_spd_xz;
    /* 0xc */ float max_spd_y;
} VC_CAM_MV_PARAM;

typedef struct _VC_WATCH_MV_PARAM {
    /* 0x0 */ float ang_accel_x;
    /* 0x4 */ float ang_accel_y;
    /* 0x8 */ float max_ang_spd_x;
    /* 0xc */ float max_ang_spd_y;
} VC_WATCH_MV_PARAM;

typedef struct _VC_FIX_CAM_MANAGER {
    /* 0x0 */ int exception_f;
    /* 0x4 */ float add_ang_y;
    /* 0x8 */ float add_rd_x;
    /* 0xc */ float add_rd_z;
} VC_FIX_CAM_MANAGER;

typedef struct _VC_CIR_CAM_MANAGER {
    /* 0x00 */ sceVu0FVECTOR origin;
    /* 0x10 */ sceVu0FVECTOR sw_l;
} VC_CIR_CAM_MANAGER;

typedef struct _VC_LIMIT_AREA {
    /* 0x00 */ float min_hx;
    /* 0x04 */ float max_hx;
    /* 0x08 */ float min_hz;
    /* 0x0c */ float max_hz;
    /* 0x10 */ float min_hy;
    /* 0x14 */ float max_hy;
} VC_LIMIT_AREA;

typedef enum _THROUGH_DOOR_SET_CMD_TYPE { // : u_char
    VC_TDSC_START,
    VC_TDSC_END,
    VC_TDSC_MAIN
} THROUGH_DOOR_SET_CMD_TYPE;

typedef struct _VC_ROAD_AREA {
    /* 0x0 */ float x0;
    /* 0x4 */ float z0;
    /* 0x8 */ float x1;
    /* 0xc */ float z1;
    /* 0x10 */ float x2;
    /* 0x14 */ float z2;
    /* 0x18 */ float min_hy;
    /* 0x1c */ float max_hy;
} VC_ROAD_AREA;

typedef struct _VC_CHASE_CAM_PARAM {
    /* 0x0 */ float ofs_hy;
    /* 0x4 */ float ratio_r_xz;
    /* 0x8 */ float lr_lim_ang_y;
    /* 0xc */ float rr_lim_ang_y;
} VC_CHASE_CAM_PARAM;

typedef struct _VC_SETTLE_CAM_PARAM {
    /* 0x0 */ float sta_base_ang_y;
    /* 0x4 */ float end_base_ang_y;
    /* 0x8 */ float lr_lim_ang_y;
    /* 0xc */ float rr_lim_ang_y;
} VC_SETTLE_CAM_PARAM;

typedef struct _VC_FIX_ANG_CAM_PARAM {
    /* 0x0 */ float ang_x;
    /* 0x4 */ float ang_y;
    /* 0x8 */ float ofs_hy;
    /* 0xc */ float cam2wth_dist;
} VC_FIX_ANG_CAM_PARAM;

typedef struct _VC_LOCUS_CIRCLE_CAM_PARAM {
    /* 0x0 */ float origin_x;
    /* 0x4 */ float origin_z;
    /* 0x8 */ float ang_y;
    /* 0xc */ float radius;
} VC_LOCUS_CIRCLE_CAM_PARAM;

typedef enum _VC_AREA_SIZE_TYPE { // : u_char
    VC_AREA_TINY,
    VC_AREA_SMALL,
    VC_AREA_WIDE,
    VC_AREA_OUTDOOR,
    VC_AREA_SUU
} VC_AREA_SIZE_TYPE;

typedef enum _VC_CAM_MV_TYPE { // : u_char
    VC_MV_CHASE,
    VC_MV_SETTLE,
    VC_MV_FIX_ANG,
    VC_MV_SELF_VIEW,
    VC_MV_LOCUS_CIRCLE,
    VC_MV_THROUGH_DOOR,
    VC_MV_SUU
} VC_CAM_MV_TYPE;

typedef enum _VC_ROAD_FLAGS { // : u_short
    VC_RD_NOFLAG = 0x0,
    VC_RD_END_DATA_F = 0x1,
    VC_RD_WARP_IN_F = 0x2,
    VC_RD_WARP_OUT_F = 0x4,
    VC_RD_WARP_IN_OUT_FS = 0x6,
    VC_RD_NO_FRONT_FLIP_F = 0x8,
    VC_RD_LIM_UP_FAR_VIEW_F = 0x10,
    VC_RD_USE_NO_ENEMY_F = 0x20,
    VC_RD_USE_NEAR_ENEMY_F = 0x40,
    VC_RD_MARGE_ROAD_F = 0x80,
    VC_RD_NO_EXTRA_AREA_F = 0x100,
    VC_RD_CAM_LIKE_SETTLE_F = 0x200,
    VC_RD_NOT_WARP_F = 0x400,
    VC_RD_INVALID_SV_F = 0x800
} VC_ROAD_FLAGS;

// @note Not included in symbols. Values taken from the `vrDispMsgVC_ROAD_DIR_TYPE` debug func (may 2001 proto only?).
typedef enum _VC_ROAD_DIR_TYPE {
    VC_RD_DIR_Z = 0,
    VC_RD_DIR_X = 1
} VC_ROAD_DIR_TYPE;

typedef struct _VC_ROAD_DATA {
    /* 0x0 */ VC_ROAD_AREA lim_sw;
    /* 0x20 */ VC_ROAD_AREA lim_rd;
    /* 0x40 */ int kind_id;
    /* 0x44 */ int flags; // `VC_ROAD_FLAGS`
    /* 0x48 */ int area_size_type; // `VC_AREA_SIZE_TYPE`
    /* 0x4c */ int rd_type;
    /* 0x50 */ VC_CAM_MV_TYPE mv_y_type; // Unsure if correct type, `cam_mv_type` likely uses this enum too, maybe both use it for diff reasons?
    /* 0x54 */ float ofs_watch_hy;
    /* 0x58 */ float trace_btm_hy;
    /* 0x5c */ int rd_dir_type; // `VC_ROAD_DIR_TYPE`
    /* 0x60 */ float projection;
    /* 0x64 */ float proj_volume;
    /* 0x68 */ float proj_sec;
    /* 0x6c */ int cam_mv_type; // `VC_CAM_MV_TYPE`
    union /* @anon3 */ {
        /* 0x70 */ u_char data[16];               // offset 0x0, size 0x10
        /* 0x70 */ VC_CHASE_CAM_PARAM chs;        // offset 0x0, size 0x10
        /* 0x70 */ VC_SETTLE_CAM_PARAM stl;       // offset 0x0, size 0x10
        /* 0x70 */ VC_FIX_ANG_CAM_PARAM fix;      // offset 0x0, size 0x10
        /* 0x70 */ VC_LOCUS_CIRCLE_CAM_PARAM cir; // offset 0x0, size 0x10
    } tmp;                                        // offset 0x70, size 0x10
} VC_ROAD_DATA;

typedef struct _VC_NEAR_ROAD_DATA {
    /* 0x000 */ VC_ROAD_DATA* road_p;
    /* 0x004 */ int rd_dir_type; // `VC_ROAD_DIR_TYPE`
    /* 0x008 */ int use_priority;
    /* 0x00c */ float chara2road_sum_dist;
    /* 0x010 */ float chara2road_vec_x;
    /* 0x014 */ float chara2road_vec_z;
    /* 0x018 */ VC_LIMIT_AREA rd;
    /* 0x030 */ VC_LIMIT_AREA sw;
    /* 0x050 */ sceVu0FMATRIX rd_rzm;
    /* 0x090 */ sceVu0FMATRIX rd_rim;
    /* 0x0d0 */ sceVu0FMATRIX sw_rzm;
    /* 0x110 */ sceVu0FMATRIX sw_rim;
} VC_NEAR_ROAD_DATA;

typedef struct _VC_WORK {
    /* 0x000 */ int view_cam_active_f;
    /* 0x004 */ VC_ROAD_DATA** vc_road_ary_list;
    /* 0x008 */ VC_FLAGS flags;
    /* 0x00c */ int through_door_activate_init_f;
    /* 0x010 */ VC_THROUGH_DOOR_CAM_PARAM through_door;
    /* 0x040 */ float scr_half_ang_wy;
    /* 0x044 */ float scr_half_ang_wx;
    /* 0x048 */ VC_CAM_MV_PARAM user_cam_mv_prm;
    /* 0x060 */ sceVu0FVECTOR cam_tgt_pos;
    /* 0x070 */ sceVu0FVECTOR cam_pos;
    /* 0x080 */ float cam_mv_ang_y;
    /* 0x090 */ sceVu0FVECTOR cam_velo;
    /* 0x0a0 */ float old_cam_excl_area_r;
    /* 0x0a4 */ float ideal_cam_pos_h;
    /* 0x0a8 */ VC_WATCH_MV_PARAM user_watch_mv_prm;
    /* 0x0c0 */ sceVu0FVECTOR watch_tgt_pos;
    /* 0x0d0 */ float watch_tgt_max_y;
    /* 0x0d4 */ float watch_tgt_ang_z;
    /* 0x0e0 */ sceVu0FVECTOR cam_mat_ang;
    /* 0x0f0 */ sceVu0FMATRIX cam_mat;
    /* 0x130 */ sceVu0FVECTOR ofs_cam_ang;
    /* 0x140 */ sceVu0FVECTOR ofs_cam_ang_spd;
    /* 0x150 */ sceVu0FVECTOR base_cam_ang;
    /* 0x160 */ sceVu0FVECTOR old_base_cam_ang;
    /* 0x170 */ float cam_chara2ideal_ang_y;
    /* 0x180 */ sceVu0FVECTOR cam_tgt_velo;
    /* 0x190 */ float cam_tgt_mv_ang_y;
    /* 0x194 */ float cam_tgt_spd;
    /* 0x1a0 */ sceVu0FVECTOR chara_pos;
    /* 0x1b0 */ float chara_bottom_y;
    /* 0x1b4 */ float chara_top_y;
    /* 0x1b8 */ float chara_center_y;
    /* 0x1bc */ float chara_grnd_y;
    /* 0x1c0 */ sceVu0FVECTOR chara_head_pos;
    /* 0x1d0 */ float chara_mv_spd;
    /* 0x1d4 */ float chara_mv_ang_y;
    /* 0x1d8 */ float chara_ang_spd_y;
    /* 0x1dc */ float chara_eye_ang_y;
    /* 0x1e0 */ float chara_eye_ang_wy;
    /* 0x1e4 */ float chara_watch_xz_r;
    /* 0x1e8 */ VC_FIX_CAM_MANAGER fix_man;
    /* 0x200 */ VC_CIR_CAM_MANAGER cir_man;
    /* 0x220 */ VC_NEAR_ROAD_DATA near_road_ary[128];
    /* 0xaa20 */ int near_road_suu;
    /* 0xaa30 */ VC_NEAR_ROAD_DATA cur_near_road;
    /* 0xab80 */ SubCharacter* nearest_enemy_p;
    /* 0xab84 */ float nearest_enemy_xz_dist;
    /* 0xab88 */ float enemy_input_watch_y;
    /* 0xab8c */ SubCharacter* nearest_item_p;
    /* 0xab90 */ float nearest_item_xz_dist;
} VC_WORK;

typedef struct _VC_CAMERA_INTINFO {
    /* 0x0 */ int mode;
    /* 0x4 */ int mv_smooth;
    /* 0x8 */ float ev_cam_rate;
} VC_CAMERA_INTINFO;

extern VC_WORK vcWork;
extern VC_CAMERA_INTINFO vcCameraInternalInfo;
extern VC_ROAD_DATA* vcNullRoadArrayList[2];
extern VC_NEAR_ROAD_DATA vcNullNearRoad;
extern float vcSelfViewTimer;
extern VC_WATCH_MV_PARAM vcWatchMvPrmSt;
extern VC_CAM_MV_PARAM vcCamMvPrmSt;
extern const VC_WATCH_MV_PARAM watch_mv_prm_user;
extern const VC_CAM_MV_PARAM cam_mv_prm_user;

// @todo: check float*/float[] types.
void vcInitVCSystem(VC_ROAD_DATA** vc_road_ary_list);
void vcStartCameraSystem(void);
void vcSetFirstCamWork(sceVu0FVECTOR cam_pos, float chara_eye_ang_y, int use_through_door_cam_f);
void vcUserWatchTarget(float* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, float rot_z, int warp_watch_f);
void vcUserCamTarget(float* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, int warp_cam_f);
void vcGetNowWatchPos(float* watch_pos);
void vcGetNowCamPos(float* cam_pos);
void vcReturnPreAutoCamWork(int warp_f);
void vcSetSubjChara(float* chara_pos, float chara_bottom_y, float chara_top_y, float chara_grnd_y, float* chara_head_pos, float chara_mv_spd, float chara_mv_ang_y, float chara_ang_spd_y, float chara_eye_ang_y, float chara_eye_ang_wy, float chara_watch_xz_r);
int vcExecCamera(void);
void vcSetAllNpcDeadTimer(void);
int vcRetSmoothCamMvF(float* old_pos, float* now_pos, float* old_ang, float* now_ang);
VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p);
int vcRetThroughDoorCamEndF(VC_WORK* w_p);
float vcRetFarWatchRate(int far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p);
float vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, float far_watch_rate, VC_WORK* w_p);
void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, float far_watch_rate, int all_warp_f);
void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA** vc_road_ary_list);
void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type);
void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p);
void vcSetNearestItemDataInVC_WORK(VC_WORK* w_p);
void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA** road_ary_list, float half_w, int near_enemy_f);
int vcRetRoadUsePriority(VC_ROAD_TYPE rd_type);
int vcSetCurNearRoadInVC_WORK(VC_WORK* w_p);
float vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CHK_TYPE chk_type, float* pos, VC_WORK* w_p);
float vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, float* pos, VC_WORK* w_p, int chk_only_set_marge_f);
float vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p);
void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, float far_watch_rate, float self_view_eff_rate);
void vcMakeNormalWatchTgtPos(float* watch_tgt_pos, float* watch_tgt_ang_z_p, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMixSelfViewEffectToWatchTgtPos(float* watch_tgt_pos, float* watch_tgt_ang_z_p, float effect_rate, VC_WORK* w_p, float head_mat[4], int anim_status);
void vcMakeFarWatchTgtPos(float* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcSetWatchTgtXzPos(float* watch_pos, float* center_pos, float* cam_pos, float tgt_chara2watch_cir_dist, float tgt_watch_cir_r, float watch_cir_ang_y);
void vcSetWatchTgtYParam(float* watch_pos, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, float watch_y);
void vcAdjustWatchYLimitHighWhenFarView(float* watch_pos, float* cam_pos);
void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, float far_watch_rate);
float vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);
void vcMakeIdealCamPosByHeadPos(float* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosForFixAngCam(float* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosForThroughDoorCam(float* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosForLocusCircleCam(float* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosUseVC_ROAD_DATA(float* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(float* x_p, float* z_p, VC_LIMIT_AREA* lim_p);
void vcMakeBasicCamTgtMvVec(float* tgt_mv_vec, float* ideal_pos, VC_WORK* w_p, float max_tgt_mv_xz_len);
void vcAdjTgtMvVecYByCurNearRoad(float* tgt_mv_vec, VC_WORK* w_p);
void vcCamTgtMvVecIsFlipedFromCharaFront(float* tgt_mv_vec, VC_WORK* w_p, float max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size);
float vcFlipFromCamExclusionArea(float* flip_ang_y_p, float* old_cam_excl_area_r_p, float* in_pos, float* chara_pos, float chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, float self_view_eff_rate, float far_watch_rate, VC_WORK* w_p);
void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);
void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, int visible_chara_f);
void vcMakeNewBaseCamAng(float* new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p);
void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, float* new_base_cam_ang);
void vcMakeOfsCamTgtAng(float* ofs_tgt_ang, float base_matT[4], VC_WORK* w_p);
void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(float* ofs_cam2chara_btm_ang, float* ofs_cam2chara_top_ang, float base_matT[4], float* cam_pos, float* chara_pos, float chara_bottom_y, float chara_top_y);
void vcAdjCamOfsAngByCharaInScreen(float* cam_ang, float* ofs_cam2chara_btm_ang, float* ofs_cam2chara_top_ang, VC_WORK* w_p);
void vcAdjCamOfsAngByOfsAngSpd(float* ofs_ang, float* ofs_ang_spd, float* ofs_tgt_ang, VC_WATCH_MV_PARAM* prm_p);
void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(float* cam_mat_ang, float cam_mat[4], float* base_cam_ang, float* ofs_cam_ang, float* cam_pos);
void vcSetDataToVwSystem(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type);
float vcCamMatNoise(float noise_w, float ang_spd1, float ang_spd2);
float vcGetXZSumDistFromLimArea(float* out_vec_x_p, float* out_vec_z_p, float chk_wld_x, float chk_wld_z, float lim_min_x, float lim_max_x, float lim_min_z, float lim_max_z, int can_ret_minus_dist_f);
void vcSetEventCamParamRefView(float* vp, VC_CAM_MV_PARAM* cam_prm_p, float* vr, VC_WATCH_MV_PARAM* watch_prm_p, float rot_z, int warp_flg);
void vcSetProjectionValue(float new, int framecnt);
void vcChangeProjectionValue(VC_WORK* w_p);

#endif // VC_MAIN_H
