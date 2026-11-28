#include "sh2_common.h"

#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/chara_list.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/chara_data_load.h"
#include "Event/chara_admin.h"
#include "Event/demoview.h"

#include "SH2_common/mem_share.h"

#include "GFW/sh2gfw_2d_filters.h"

#include "view/vc_main.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "sound/sh_sd_call.h"

#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_demo_tenbou.h"
#include "data/daily.thu/data_chr_mar.h"
#include "data/daily.thu/data_demo_mar_isho_i.h"
#include "data/daily.thu/data_pic_out.h"

static short stg_ovservation_ovservation_anim_01F02CE8[2] = { 0x0460, 0x0000 }; // @ 0x01F02CE8

static DramaDemo_MessageTime stg_ovservation_msg_time_01F02CF0[22] = {
    { 0x023A, 0x02FA }, 
    { 0x02FA, 0x034E }, 
    { 0x0366, 0x03F6 }, 
    { 0x03F6, 0x0468 },
    { 0x0468, 0x0501 },
    { 0x0501, 0x056A },
    { 0x056A, 0x05AF },
    { 0x067E, 0x06E1 },
    { 0x06E1, 0x07B9 },
    { 0x07B9, 0x0813 },
    { 0x0813, 0x08E8 },
    { 0x08E8, 0x0957 },
    { 0x0957, 0x09DE },
    { 0x09DE, 0x0A92 },
    { 0x0A92, 0x0B2E },
    { 0x0B2E, 0x0C03 },
    { 0x0C03, 0x0C84 },
    { 0x0C84, 0x0D08 },
    { 0x0D08, 0x0E13 },
    { 0x0E13, 0x0E91 },
    { 0x0E91, 0x0F72 },
    { 0xFFFF, 0xFFFF }
}; // @ 0x01F02CF0

static DramaDemo_PlayInfo stg_ovservation_letter_01F02D50 = {
    /* .demo_no = */      2,
    /* .adr_dds_top = */  MemShare_gp_data_buf,
    /* .adr_anim = */     &stg_ovservation_ovservation_anim_01F02CE8,
    /* .adr_msg_time = */ &stg_ovservation_msg_time_01F02CF0,
    /* .msg_start = */    7,
    /* .voice_sd_no = */  0,
    /* .adr_voice = */    NULL,
    /* .stream_no = */    0xEAB0, 
    /* .stream_start = */ 570.0f,
    /* .add_pos_x = */    0.0f,
    /* .add_pos_z = */    0.0f
}; // @ 0x01F02D50


static CharaData_DemoList stg_ovservation_chara_data_01F02D80[2] = {
    {
        /* .kind = */      HHH_JMS_CHARA_KIND,
        /* .model = */     data_chr_jms_hhh_jms_notex_mdl,
        /* .animation = */ data_demo_tenbou_hhh_jms_anm,
        /* .shadow = */    data_chr_jms_hhh_jms_kg1,
        /* .cluster = */   data_demo_tenbou_hhh_jms_cls
    },
    {
        /* .kind = */      0,
        /* .model = */     NULL,
        /* .animation = */ NULL,
        /* .shadow = */    NULL,
        /* .cluster = */   NULL
    }
}; // @ 0x01F02D80

static float stg_ovservation_pos_01F02DB0[4] = { 19350.25f, 0.0f, -507.7399902f, 0.0f };

static int stg_ovservation_px_01F02DC0 = -774;
static int stg_ovservation_py_01F02DC8 = -506;

/* static */ int stg_ovservation_EvProgLetterFromMary(void) {
    
    float pos[4]; // @note: not present in DWARF
    int ret;

    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_tenbou_tenbou_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_ovservation_chara_data_01F02D80, 0);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            ret = DramaDemoMain(&stg_ovservation_letter_01F02D50);
            if (demo_frame > 1400.0f) {
                SET_GAME_FLAG(GAME_FLAG_517);
            }
            if ((shPadTrigger(0, key_config.skip) != 0) || (ret && !(shSdStat() & 0xF0))) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            pos = stg_ovservation_pos_01F02DB0;
            shCharacterSetPosAfterDemo(sh2jms.player,pos, 0.0f);
            SET_GAME_FLAG(GAME_FLAG_1322);
            SET_GAME_FLAG(GAME_FLAG_1276);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgItemInCar);

/* static */ int stg_ovservation_EvProgNothingTakeInCar(void) {
    return EvSubPictureDisplay(data_pic_out_p_incar_tex, 3);
}

/* static */ int stg_ovservation_EvProgHadBetterGetMap(void) {

    static float stg_ovservation_pos_01F02EA0[4];

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubMessage(2)) {
                EV_PROG_STEP(27);
            }
            break;
            
        case 27:
            stg_ovservation_pos_01F02EA0[0] = sh2jms.player->pos.x;
            stg_ovservation_pos_01F02EA0[1] = sh2jms.player->pos.y;
            stg_ovservation_pos_01F02EA0[2] = sh2jms.player->pos.z - 500.0f;
            stg_ovservation_pos_01F02EA0[3] = 0.0f;
            EV_PROG_STEP(28);
            /* fallthrough */
        case 28:
            PlayerEventMove(stg_ovservation_pos_01F02EA0);
            if (PlayerEventMoveIsEnd()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

/* static */ int stg_ovservation_EvProgCantGoBack(void) {

    static float stg_ovservation_pos_01F02E90[4];

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubMessage(0)) {
                EV_PROG_STEP(27);
            }
            break;
        case 27:
            stg_ovservation_pos_01F02E90[0] = sh2jms.player->pos.x - 500.0f;
            stg_ovservation_pos_01F02E90[1] = sh2jms.player->pos.y;
            stg_ovservation_pos_01F02E90[2] = sh2jms.player->pos.z;
            stg_ovservation_pos_01F02E90[3] = 0.0f;
            EV_PROG_STEP(28);
            /* fallthrough */
        case 28:
            PlayerEventMove(stg_ovservation_pos_01F02E90);
            if (PlayerEventMoveIsEnd()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

/* static */ int stg_ovservation_EvProgLastScene(void) {

    static short stg_ovservation_ovservation_anim_01F02DD0[2] = { 0x03D1, 0x002C }; // @ 0x01F02DD0 @note: not present in dwarf

    static DramaDemo_PlayInfo stg_ovservation_info_01F02DE0 = {
        /* .demo_no = */      89,
        /* .adr_dds_top = */  MemShare_gp_data_buf,
        /* .adr_anim = */     &stg_ovservation_ovservation_anim_01F02DD0,
        /* .adr_msg_time = */ NULL,
        /* .msg_start = */    0x0,
        /* .voice_sd_no = */  0,
        /* .adr_voice = */    NULL,
        /* .stream_no = */    0x0,
        /* .stream_start = */ 0.0f,
        /* .add_pos_x = */    0.0f,
        /* .add_pos_z = */    0.0f
    }; // @ 0x01F02DE0

    static CharaData_DemoList stg_ovservation_chara_data_01F02E10[2] = {
        {
            /* .kind = */      LLL_MAR_CHARA_KIND,
            /* .model = */     data_chr_mar_lll_mar_mdl,
            /* .animation = */ data_demo_mar_isho_i_lll_mar_anm,
            /* .shadow = */    data_chr_mar_hhh_mar_kg1,
            /* .cluster = */   NULL
        },
        {
            /* .kind = */      0,
            /* .model = */     NULL,
            /* .animation = */ NULL,
            /* .shadow = */    NULL,
            /* .cluster = */   NULL
        }
    }; // @ 0x01F02E10

    static u_long128* stg_ovservation_anim_adr_01F02E80 = NULL;

    switch (ev_p_step) {
        case 0:
            FcRead(&data_demo_mar_isho_i_end_maria_i_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(&stg_ovservation_chara_data_01F02E10, 0);
            stg_ovservation_anim_adr_01F02E80 = (u_long128*) &MemShare_gp_data_buf[(FcGetFileSize(&data_demo_mar_isho_i_end_maria_i_dds) + 0x7FF) & ~0x7FF];
            FcRead(&data_demo_mar_isho_i_lll_jms_anm, stg_ovservation_anim_adr_01F02E80);
            fsSync(0, -1);
            stg_ovservation_anim_adr_01F02E80 = CharaDataAnimAdressExchange(sh2jms.player, stg_ovservation_anim_adr_01F02E80);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, 1);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_ovservation_info_01F02DE0) != 0) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            CharaDataDeleteOne(LAU_CHARA_KIND);
            stg_ovservation_anim_adr_01F02E80 = CharaDataAnimAdressExchange(sh2jms.player, stg_ovservation_anim_adr_01F02E80);
            SCNowDemoEventSwitch(sh2jms.player, 0);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            return 1;
    }
    return 0;
}

/* static */ void stg_ovservation_EvAllTimeFunc(void) {
    int disp_ctrl_list[3]; // r29+0x10

    disp_ctrl_list[0] = 0;
    EvDispControlModelEntry(disp_ctrl_list, 3, !GET_GAME_FLAG(GAME_FLAG_24) ? 0 : -1); // @todo: add room id
    EvDispControlModelExec(disp_ctrl_list);
}

/* static */ int stg_ovservation_EvBgmControl(void) {
    if (GET_BIT(Sh2sys.main_status, 6)) {
        return !GET_GAME_FLAG(GAME_FLAG_517) ? 4 : 14;
    }
    return GET_GAME_FLAG(GAME_FLAG_36) != 0;
}

/* static */ float stg_ovservation_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

/* static */ void stg_ovservation_OB_DemoBlur(void) {
    float blt; // r29+0x10
    float tm; // r29+0x10
    
    if (DramaDemoNumber()) {
        tm = demo_frame;
        if (tm > 1500.0f) {
            sh2gfw_Reset_FilterCommand();
            return;
        }
        if (tm < 0.0f) {
            tm = 0.0f;
        }
        blt = stg_ovservation_LinearTrim(0.0f, 1.0f, 1500.0f, 0.0f, tm);
        sh2gfw_Set_FilterBlur(blt);
    }
}
