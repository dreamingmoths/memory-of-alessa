#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "Collision/cl_main.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/sh2_character_manage.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/picture.h"
#include "Event/demoview.h"
#include "Event/chara_admin.h"

#include "Effect/screen_effect.h"
#include "sound/sh_sound.h"
#include "Multi_thr/filesys/fcread.h"
#include "GFW/sh2_DrawEnvData.h"
#include "view/vc_main.h"

static int EvProgUseYardKey(void);
static int EvProgGetApartMap(void);
static int EvProgGetApartWestMap(void);
static int EvProgGetCannedJuice(void);
static int EvProgApartBoss(void);
static int EvProgApartBossSiren(void);
static int EvProgApartBossEnd(void);
static void EvRoomInit(void);

UNMIGRATED(CL_HITPOLY_PLANE stg_apart_stair_clActWallList_ap88[2]); // size: 0xA0, address: 0x1F03030

extern /* static */ u_char ev_pos[482]; // size: 0x1E2, address: 0x1F02BA0
extern /* static */ struct Event_List ev_list[36]; // size: 0x240, address: 0x1F02D90
extern /* static */ struct Item_List gi_list[6]; // size: 0x60, address: 0x1F02FD0
extern /* static */ struct _CL_HITPOLY_PLANE clActWallList_ap88[2]; // size: 0xA0, address: 0x1F03030
extern /* static */ float stg_apart_stair_colvec[4]; // size: 0x10, address: 0x1F030D0
extern /* static */ float stg_apart_stair_colref[4]; // size: 0x10, address: 0x1F030E0
extern /* static */ float stg_apart_stair_ldir[4]; // size: 0x10, address: 0x1F030F0
extern /* static */ struct DynamicLight stg_apart_stair_DynamicLW; // size: 0x40, address: 0x1F03100
extern /* static */ int (* ev_prog[8])(); // size: 0x20, address: 0x1F03140
extern /* static */ struct Model_List mdl_list[2]; // size: 0x60, address: 0x1F03160
extern /* static */ struct Enemy_List en_list[2]; // size: 0x28, address: 0x1F031D0
extern struct Stage_Data stage_apart_stair; // size: 0x44, address: 0x1F03200
extern /* static */ float siren_vlm; // size: 0x4, address: 0x0
extern /* static */ float water_se; // size: 0x4, address: 0x0
extern fsFileIndex data_pic_map_apartmape1f_tex[1]; // size: 0x8, address: 0x3A1D50
extern fsFileIndex data_pic_map_apartmapw_tex[1]; // size: 0x8, address: 0x3A1D88
extern fsFileIndex data_chr_scu_scu_anm[1]; // size: 0x8, address: 0x3A1060
extern fsFileIndex data_chr_red_red_anm[1]; // size: 0x8, address: 0x3A1048
extern fsFileIndex data_demo_ap_boss_scu_anm[1]; // size: 0x8, address: 0x3A1198
extern fsFileIndex data_demo_ap_boss_red_anm[1]; // size: 0x8, address: 0x3A1190
extern fsFileIndex data_demo_ap_boss_ap_boss_dds[1]; // size: 0x8, address: 0x3A1178
extern float ev_timer; // size: 0x4, address: 0x11263A0
extern int* Get_NowMapId(void);

static inline void shVectorCrossProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2) {
    asm volatile("\
	lqc2    vf5, 0x0(%1);\
	lqc2    vf6, 0x0(%2);\
	vsub.w  vf4, vf0, vf0;\
	vopmula.xyz	ACC, vf5, vf6;\
	vopmsub.xyz	vf4, vf6, vf5;\
	sqc2    vf4, 0x0(%0);\
	": : "r" (v0) , "r" (v1) ,"r" (v2) : "memory");
}


static void stg_apart_stair_AP_Hosei_Light(void) {
    int* mp = Get_NowMapId(); // r2
    Q_WORDDATA tmp; // r29+0x10
    float inner; // r29+0x50
    float factor; // r29+0x50

    switch (*mp) {
        case 0x9000A:
            tmp = Env_ctl.compo_shadow_col;
            tmp.ui32[3] = 10;
            sh2gfw_Set_FilterData(sh2gfw_Get_NightOrDay(), 0, &tmp);
            Env_ctl.camera_parms[3] = 50.0f;
            break;
        
        case 0x90058: {
            sceVu0FVECTOR tmp;
            sceVu0FVECTOR plane; // r29+0x30
            sceVu0FVECTOR aimdir; // r29+0x40
            if (DramaDemoNumber() == 19) {
                sh2gfw_Set_DemoRefrectionHighLight(stg_apart_stair_ldir, stg_apart_stair_colref);
                break;
            }
            
            sceVu0CopyVector(stg_apart_stair_DynamicLW.BeforeCamDir, stg_apart_stair_DynamicLW.NowCamDir);
            sceVu0CopyVector(stg_apart_stair_DynamicLW.BeforeDir, stg_apart_stair_DynamicLW.NowDir);
            sh2gde_Get_EyeDir(&stg_apart_stair_DynamicLW);
            inner /* inner product */ = vec3_dot_product(stg_apart_stair_DynamicLW.NowCamDir, stg_apart_stair_DynamicLW.BeforeDir);
            shVectorCrossProduct(plane, stg_apart_stair_DynamicLW.NowCamDir, stg_apart_stair_DynamicLW.BeforeDir);
            shNormalizeVector(plane, plane);
            shVectorCrossProduct(aimdir, stg_apart_stair_DynamicLW.BeforeDir, plane);
            factor = 0.1f / (2.0f + inner);
            if (factor < 0.0333f) {
                factor = 0;
            }
            shScaleVector(aimdir, aimdir, factor);
            shAddVector(tmp, aimdir, stg_apart_stair_DynamicLW.BeforeDir);
            shNormalizeVector(tmp,stg_apart_stair_DynamicLW.NowDir);
            sh2gfw_Set_DemoRefrectionHighLight(stg_apart_stair_DynamicLW.NowDir, stg_apart_stair_colref);
            sh2gfw_Set_PallarelLight(stg_apart_stair_DynamicLW.NowDir, stg_apart_stair_colvec, 1);
            break;
        }
    }
}

#line 122
static int stg_apart_stair_EvProgUseYardKey(void) {
    EvSubItemUse0(SH2_ITEM_26,     4,
                  SH2_SOUND_19025, 0,
                  (sceVu0FVECTOR){-98800.0f, -500.0f, -16800.0f, 0.0f}, 1);
}

#line 132
static int stg_apart_stair_EvProgGetApartMap(void) {
    EvSubMapGet(data_pic_map_apartmape1f_tex,
                2);
}

#line 141
static int stg_apart_stair_EvProgGetApartWestMap(void) {
    EvSubMapGet(data_pic_map_apartmapw_tex,
                3);
}

#line 149
static int stg_apart_stair_EvProgGetCannedJuice(void) {
    EvSubItemGetAndAnim(46, // kind
                        1); // message
}

#line 157
static int stg_apart_stair_EvProgApartBoss(void) {
    extern /* static */ CharaData_DemoList stg_apart_stair_chara_data_01F032A0[4]; // @ 0x01F032A0
    extern /* static */ DramaDemo_PlayInfo stg_apart_stair_boss; // @ 0x01F03270
    extern /* static */ u_long128* stg_apart_stair_red_play_anim_adr; // @ 0x01F03408
    extern /* static */ u_long128* stg_apart_stair_scu_play_anim_adr; // @ 0x01F03400
    extern /* static */ sceVu0FMATRIX stg_apart_stair_vec_01F032F0; // @ 0x01F032F0
    int ret; // r16

    #line 187
    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_ap_boss_ap_boss_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_stair_chara_data_01F032A0, 0);
            stg_apart_stair_red_play_anim_adr = (u_long128*) &MemShare_gp_data_buf[(FcGetFileSize(data_demo_ap_boss_ap_boss_dds) + 0x7FF) & ~0x7FF]; // @todo: add align macro
            
            stg_apart_stair_scu_play_anim_adr = stg_apart_stair_red_play_anim_adr + ((FcGetFileSize(data_demo_ap_boss_red_anm) + 0x7FF) & ~0x7FF);
            
            FcRead(data_demo_ap_boss_red_anm, stg_apart_stair_red_play_anim_adr);
            FcRead(data_demo_ap_boss_scu_anm, stg_apart_stair_scu_play_anim_adr);
            fsSync(0, -1);
            stg_apart_stair_red_play_anim_adr = CharaDataAnimSetExtra(EN_RED_CHARA_KIND, data_demo_ap_boss_red_anm, stg_apart_stair_red_play_anim_adr, 0);
            
            stg_apart_stair_scu_play_anim_adr = CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_demo_ap_boss_scu_anm, stg_apart_stair_scu_play_anim_adr, 0);
            
            SCNowDemoEventSwitch(sh2jms.player, true);
            CharaAdminPlayableDisplay(0);
            EV_PROG_STEP(22);
            break;
        
        case 22:
            ret = DramaDemoMain(&stg_apart_stair_boss);
            shCharacterSetWeaponRED(shCharacterGetSubCharacter(EN_RED_CHARA_KIND, 0), 1);
        
            if (ret) EV_PROG_STEP(13);
            break;
        
        case 13:
            CharaDataDeleteOne(HHL_JMS_CHARA_KIND);
            SCNowDemoEventSwitch(sh2jms.player, 0);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            CharaDataAnimSetExtra(EN_RED_CHARA_KIND, data_chr_red_red_anm, stg_apart_stair_red_play_anim_adr, 1);
        
            CharaAdminReCreate(EN_RED_CHARA_KIND, 8, 0, stg_apart_stair_vec_01F032F0[0], stg_apart_stair_vec_01F032F0[1], 6);
            
            CharaDataAnimSetExtra(EN_SCU_CHARA_KIND, data_chr_scu_scu_anm, stg_apart_stair_scu_play_anim_adr, 1);
            
            CharaAdminReCreate(EN_SCU_CHARA_KIND, 9, 0, stg_apart_stair_vec_01F032F0[2], stg_apart_stair_vec_01F032F0[3], 13);
            
            
            sh2sys_set_2(11);
            ScreenEffectFadeStart(1, 1.0f);
            
            return true;
    }
    return false;
}

#line 240
static int stg_apart_stair_EvProgApartBossSiren(void) {
    SeCallPos(SH2_SOUND_10006, 0.0f, NULL, 8);
    return true;
}

#line 249
static int stg_apart_stair_EvProgApartBossEnd(void) {
    extern /* static */ Event_CamSetData cam_data; // @ 0x01F03350
    extern /* static */ float light[4]; // @ 0x01F03330
    extern /* static */ float clr[4]; // @ 0x01F03340

    #line 258
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            CharaAdminPlayableDisplay(0);
            shCharacter_Manage_Delete(NULL, EN_RED_CHARA_KIND, 8);
            SeCallPos(SH2_SOUND_19023, 1.0f, (sceVu0FVECTOR) {98804.95312f, -450.0f, -98578.19531, 0.0f}, 4);

            
            SeCallPos(SH2_SOUND_16021, 0.0f, (sceVu0FVECTOR) {98804.95312f, -450.0f, -98578.19531, 0.0f}, 12);
            
            
            ev_timer = 0.0f;
            SET_GAME_FLAG(GAME_FLAG_147);
            EV_PROG_STEP(22);
            /* fallthrough */
        
        case 22:
            DramaDemoFade();
        
            vcSetEventCamParamRefView(cam_data.pos, NULL, cam_data.itr, NULL, cam_data.roll, 1);
            
            vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
            sh2gfw_Set_PallarelLight(light, clr, 2);
            ev_timer += shGetDT();
            if (ev_timer > 4.0f) EV_PROG_STEP(13);
            break;

        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_148);
            Se2dManageDataTimer(SH2_SOUND_10006, 1);
            return true;
    }
    return false;
}

#line 300
static void stg_apart_stair_EvRoomInit(void) {
    UNSET_GAME_FLAG(GAME_FLAG_87);
}

#line 306
static void stg_apart_stair_EvAllTimeFunc(void) {
    float vol; // r29+0x20
    float time; // r29+0x20
    int disp_ctrl_list[3]; // r29+0x10
    int work; // r2

    disp_ctrl_list[0] = 0;
    
    switch (RoomNameJms()) {  
        case 16:
            work = !GET_GAME_FLAG(GAME_FLAG_25) ? 0 : -1;
            
            EvDispControlModelEntry(disp_ctrl_list, 25, work);
            break;
        case 32:
            work = !GET_GAME_FLAG(GAME_FLAG_26) ? 0 : -1;
            
            EvDispControlModelEntry(disp_ctrl_list, 110, work);
            break;
        case 33:
            if (!GET_GAME_FLAG(GAME_FLAG_148))
                clAddDynamicWall(stg_apart_stair_clActWallList_ap88);
            if (!GET_GAME_FLAG(GAME_FLAG_149) && 
                 GET_GAME_FLAG(GAME_FLAG_148)) {
                SET_GAME_FLAG(GAME_FLAG_149);
                SeStop(SH2_SOUND_10006);
            }
            time = Se2dManageDataTimer(SH2_SOUND_10006, 0);
            if (time >= 0.0f) {
                if GET_GAME_FLAG(GAME_FLAG_148) vol = 1.0f - time / 3.4f; // @info this if & else are missing from the line numbers
                else vol = time / 2.2f;
            
                Se2dManageDataVolumeChange(SH2_SOUND_10006, vol);
            }
            time = Se2dManageDataTimer(SH2_SOUND_16021, 0);
            if (time >= 0.0f) {
                if (time < 4.5f) vol = 2.0f * time;
                else vol = 1.0f - ((time - 4.5f) / 1.5f);
                Se2dManageDataVolumeChange(SH2_SOUND_16021, vol);
            }
            break;
    }
    EvDispControlModelExec(disp_ctrl_list);
}
