#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/item.h"
#include "Event/stg_name.h"
#include "Event/chara_data_load.h"
#include "Event/chara_admin.h"
#include "Event/demoview.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "GFW/sh2_DrawEnvData.h"

#include "Effect/screen_effect.h"

#include "Enemy/en_common.h"
#include "Enemy/en_insect.h"

#include "sound/sh_sound.h"

#include "Chacter_Draw/sh2gfw_Draw_Character.h"

#include "SH2_common/sh2dt.h"
#include "SH2_common/pad.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "Font/font.h"

#include "view/vc_main.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "DS_Pad/dsr_data.h"

#include "data/daily.thu/data_demo_kao.h"
#include "data/daily.thu/data_demo_ana.h"
#include "data/daily.thu/data_demo_ana_c.h"
#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_item.h"
#include "data/daily.thu/data_pic_apt.h"

// @todo: migrate data

extern /* static */ float stg_apart_e2f_tv_pos[4]; // = { -58082.375f, -356.5f , 19011.39062, 0.0f }; // @ 0x01F07240

extern /* static */ DramaDemo_PlayInfo stg_apart_e2f_info_hole_01F07500; // @ 0x01F07500

/*
static DramaDemo_PlayInfo stg_apart_e2f_info_hole_01F07500 = {
    .demo_no = 11,
    .adr_dds_top = MemShare_gp_data_buf,
    .adr_anim = (short*)&D_01F074F0_aey,
    .adr_msg_time = NULL,
    .msg_start = 0,
    .voice_sd_no = 0,
    .adr_voice = (int*)0x0000EA61,
    .stream_no = 0,
    .stream_start = 108.0f,
    .add_pos_x = 0.0f,
    .add_pos_z = 0.0f
};
*/

extern /* static */ CharaData_DemoList stg_apart_e2f_chara_data_01F07530[4]; // @ 0x01F07530

/*
static CharaData_DemoList stg_apart_e2f_chara_data_01F07530[] = {
    {
        .kind = HHH_JMS_CHARA_KIND,
        .model = data_chr_jms_hhh_jms_notex_mdl,
        .animation = data_demo_ana_hhh_jms_anm,
        .shadow = data_chr_jms_hhh_jms_kg1,
        .cluster = data_demo_ana_hhh_jms_cls
    },
    {
        .kind = ITEM_I_J_LIGHT_CHARA_KIND,
        .model = data_chr_item_i_j_light_mdl,
        .animation = data_demo_ana_i_j_light_anm,
        .shadow = NULL,
        .cluster = NULL
    },
    {
        .kind = ITEM_I_KEY_CLOCK_CHARA_KIND,
        .model = data_chr_item_i_key_clock_mdl,
        .animation = data_demo_ana_i_key_clock_anm,
        .shadow = NULL,
        .cluster = NULL
    },
    0
};
*/

extern /* static */ DramaDemo_PlayInfo stg_apart_e2f_info_hole_01F07590; // @ 0x01F07590

/*
static DramaDemo_PlayInfo stg_apart_e2f_info_hole_01F07590 = {
    .demo_no = 11,
    .adr_dds_top = MemShare_gp_data_buf,
    .adr_anim = (short*)&D_01F07580_aey,
    .adr_msg_time = NULL,
    .msg_start = 0,
    .voice_sd_no = 0,
    .adr_voice = NULL,
    .stream_no = 0,
    .stream_start = 0.0f,
    .add_pos_x = 0.0f,
    .add_pos_z = 0.0f
};
*/

extern /* static */ CharaData_DemoList stg_apart_e2f_chara_data_01F075C0[4]; // @ 0x01F075C0

/*
static CharaData_DemoList stg_apart_e2f_chara_data_01F075C0[4] = {
    {
        .kind = HHH_JMS_CHARA_KIND,
        .model = data_chr_jms_hhh_jms_notex_mdl,
        .animation = data_demo_ana_c_hhh_jms_anm,
        .shadow = data_chr_jms_hhh_jms_kg1,
        .cluster = data_demo_ana_c_hhh_jms_cls
    },
    {
        .kind = ITEM_I_J_LIGHT_CHARA_KIND,
        .model = data_chr_item_i_j_light_mdl,
        .animation = data_demo_ana_c_i_j_light_anm,
        .shadow = NULL,
        .cluster = NULL
    },
    {
        .kind = ITEM_I_KEY_CLOCK_CHARA_KIND,
        .model = data_chr_item_i_key_clock_mdl,
        .animation = data_demo_ana_c_i_key_clock_anm,
        .shadow = NULL,
        .cluster = NULL
    },
    0
};
*/

extern /* static */ float stg_apart_e2f_cry_pos[4]; // = { -99400.0f, -500.0f, -10785.03027f, 0.0f }; // @ 0x01F076E0

extern /* static */ DramaDemo_PlayInfo stg_apart_e2f_info_01F076B0; // @ 0x01F076B0

/*
static DramaDemo_PlayInfo stg_apart_e2f_info_01F076B0 = {
    .demo_no = 10,
    .adr_dds_top = NULL,
    .adr_anim = (short*)&D_01F076A0_aey,
    .adr_msg_time = (DramaDemo_MessageTime*)&D_01F076A8_aey,
    .msg_start = 25,
    .voice_sd_no = 0,
    .adr_voice = (int*)0x0000EA85,
    .stream_no = 0,
    .stream_start = 0.0f,
    .add_pos_x = 0.0f,
    .add_pos_z = 0.0f
};
*/

extern /* static */ float stg_apart_e2f_pos_01F076F0[4]; // = { -100447.5f, -500.0f, -10785.03027f, 0.0f }; // @ 0x01F076F0

extern /* static */ float stg_apart_e2f_pos_01F07700[4]; // = { -99000.0f, -1500.0f, 13600.0f, 0.0f }; // @ 0x01F07700

extern /* static */ CharaData_DemoList stg_apart_e2f_chara_data_01F07710[2]; // @ 01F07710

/*
static CharaData_DemoList stg_apart_e2f_chara_data_01F07710[2] = {
    {
        .kind = HHL_JMS_CHARA_KIND,
        .model = data_chr_jms_hhl_jms_notex_mdl,
        .animation = data_demo_kao_hhl_jms_anm,
        .shadow = data_chr_jms_hhh_jms_kg1,
        .cluster = data_demo_kao_hhl_jms_cls
    },
    0
};
*/

extern /* static */ float stg_apart_e2f_pos_01F07740[4]; // = { -22800.0f, -700.0f, 59200.0f, 1.0f };

// @todo: migrate bss

extern /* static */ u_long128* stg_apart_e2f_kao_dds; // @ 0x01F077A0

/* static */ int stg_apart_e2f_EvProgThreeNameOnWall(void) {
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubMessage(7)) {
                if (ev_cancel == 0) {
                    EV_PROG_STEP(2);
                } else {
                    ev_prog_flag_set = 0;
                    EV_PROG_STEP(13);
                }
            }
            break;
        case 2:
            if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_clock_name_tex, 0)) {
                ScreenEffectFadeStart(4, 0.0f);
                EV_PROG_STEP(3);
            case 3:
                EvSubPictureStart();
                EvSubPictureDisplayOnly();
                EvSubPictureEnd();
                if (ScreenEffectFadeCheck()) {
                    EV_PROG_STEP(8);
                }
            }
            break;
        case 8:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) {
                EV_PROG_STEP(7);
            }
            break;
        case 7:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubMessage(8)) {
                EV_PROG_STEP(4);
                ScreenEffectFadeStart(1, 0.0f);
            }
            break;
        case 4:
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(13);
                ScreenEffectFadeStart(4, 0.0f);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgHintOfClockSet);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgClockTime);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgClockNeedleMove);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgSubClockNeedleDraw);

/* static */ int stg_apart_e2f_EvProgUseClockKey(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgTryMoveClock);

/* static */ int stg_apart_e2f_EvProgUseEmergencyKey(void) {
    return EvSubItemUse0(27, 24, 0, 0, 0, 1);
}

/* static */ int stg_apart_e2f_EvProgAnyoneInHole(void) {
    int ret;

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            FcRead(data_demo_ana_ana_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_e2f_chara_data_01F07530, true);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubQuestion(2)) {
                if (!fontGetStatus()) {
                    EV_PROG_STEP(2);
                } else {
                    CharaDataLoadCancel(stg_apart_e2f_chara_data_01F07530);
                    EV_PROG_STEP(13);
                }
            }
            break;
        case 2:
            if (fsSync(1, -1) >= 0) {
                CharaDataLoadDemo(stg_apart_e2f_chara_data_01F07530, 0);
                CharaAdminPlayableDisplay(0);
                sh2jms.player->status |= 0x8000;
                SCNowDemoEventSwitch(sh2jms.player, 1);
                if (item.light_switch == 0) {
                    item.light_switch = 1;
                    LightSpotOnOffSet();
                }
                EV_PROG_STEP(22);
            case 22:
                DramaDemoMain(&stg_apart_e2f_info_hole_01F07500);
                if (shPadTrigger(0, key_config.skip)) {
                    EV_PROG_STEP(18);
                }
                if (demo_frame > (total_demo_frame - 60.0f)) {
                    EV_PROG_STEP(9);
                }
                if ((demo_frame >= 298.0f) && (demo_frame < 303.0f)) {
                    DSR_Entry0(__otn_ana_00, 0, 1.0f); // @note: they forgot to include the header
                }
                if ((demo_frame >= 520.0f) && (demo_frame < 530.0f)) {
                    DSR_Entry0(__otn_ana_01, 0, 1.0f);
                }
            }
            break;
        case 9:
            ret = EvSubItemGetAndAnim(0x19, 19); // @todo: add item.h define
            if ((DramaDemoMain(&stg_apart_e2f_info_hole_01F07500) != 0) && (ret != 0)) {
                EV_PROG_STEP(6);
            }
            break;
        case 18:
            DramaDemoSkipLast(&stg_apart_e2f_info_hole_01F07500);
            if (EvSubItemGetAndAnim(0x19, 19)) {
                EV_PROG_STEP(6);
            }
            break;
        case 6:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_J_LIGHT_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_KEY_CLOCK_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            sh2jms.player->status &= ~0x8000;
            vcReturnPreAutoCamWork(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            game_flag.flag[2] |= 0x8000;
            EV_PROG_STEP(13);
            /* fallthrough */
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

/* static */ int stg_apart_e2f_EvProgNooneInHole(void) {
    int ret;

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            FcRead(data_demo_ana_c_ana_c_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_e2f_chara_data_01F075C0, 1);
            EV_PROG_STEP(2);
            /* fallthrough */
        case 2:
            if (fsSync(1, -1) >= 0) {
                CharaDataLoadDemo(stg_apart_e2f_chara_data_01F075C0, 0);
                CharaAdminPlayableDisplay(0);
                sh2jms.player->status |= 0x8000;
                SCNowDemoEventSwitch(sh2jms.player, true);
                if (item.light_switch == 0) {
                    item.light_switch = 1;
                    LightSpotOnOffSet();
                }
                EV_PROG_STEP(22);
            case 22:
                DramaDemoMain(&stg_apart_e2f_info_hole_01F07590);
                if (shPadTrigger(0, key_config.skip)) {
                    EV_PROG_STEP(18);
                }
                if (demo_frame > (total_demo_frame - 90.0f)) {
                    EV_PROG_STEP(9);
                }
            }
            break;
        case 9:
            ret = EvSubMessage(3);
            if ((DramaDemoMain(&stg_apart_e2f_info_hole_01F07590) != 0) && (ret != 0)) {
                EV_PROG_STEP(13);
            }
            break;
        case 18:
            DramaDemoSkipLast(&stg_apart_e2f_info_hole_01F07590);
            if (EvSubMessage(3)) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_J_LIGHT_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_KEY_CLOCK_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            sh2jms.player->status &= ~0x8000;
            vcReturnPreAutoCamWork(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            SCNowPlayableEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            return 1;
    }
    return 0;
}

/* static */ int stg_apart_e2f_EvProgLookDustChute(void) {
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(2);
            /* fallthrough */
        case 2:
            if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_dust_in_tex, 0)) {
                ScreenEffectFadeStart(4, 0.0f);
                EV_PROG_STEP(3);
            }
            break;
        case 3:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(7);
            }
            break;
        case 7:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel)) {
                EV_PROG_STEP(30);
            }
            break;
        case 30:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubMessage(15)) {
                if (playing.riddle_level > 0) {
                    ScreenEffectFadeStart(1, 0.0f);
                    EV_PROG_STEP(4);
                } else {
                    EV_PROG_STEP(31);
                }
            }
            break;
        case 31:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubMessage(16)) {
                ScreenEffectFadeStart(1, 0.0f);
                EV_PROG_STEP(4);
            }
            break;
        case 4:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            ScreenEffectFadeStart(4, 0.0f);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgUseCannedJuice);

/* static */ int stg_apart_e2f_EvProgNoFaceCorpse(void) {
    switch (ev_p_step) {
        case 0:
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            stg_apart_e2f_info_01F076B0.adr_dds_top = stg_apart_e2f_kao_dds;
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_apart_e2f_info_01F076B0)) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            CharaDataDeleteOne(HHL_JMS_CHARA_KIND);
            sh2jms.player->status |= 0x10;
            vcReturnPreAutoCamWork(1);
            CharaAdminPlayableDisplay(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            return 1;
    }
    return 0;
}

/* static */ int stg_apart_e2f_EvProgAnyoneCry(void) {
    int anm; // r2

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20002);
            ev_timer = 0.0f;
            SeCallPos(40009, 1.0f, stg_apart_e2f_cry_pos, 6);
            EV_PROG_STEP(27);
    
        case 27:
            Se3dControl(40009, 1.0f, stg_apart_e2f_cry_pos);
            ev_timer += shGetDT();
            if (shCharacterAnimeIsEnd(sh2jms.player)) {
                if (ev_timer < 2.0f)
                    anm = 0;
                else
                    anm = EvSubMessage(0);

                if (anm) {
                    EV_PROG_STEP(13);                    
                }
            }
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }

    return 0;
}

/* static */ int stg_apart_e2f_EvProgGetLight(void) {
    int ret;

    ret = EvSubItemGetAndAnim(15, 20); // @todo: add define in item.h
    
    if (ret != 0) {
        item.light_switch = 1;
        LightSpotOnOffSet();
        if (GET_GAME_FLAG(GAME_FLAG_66) && GET_GAME_FLAG(GAME_FLAG_67)) {
            SET_GAME_FLAG(GAME_FLAG_68);
        }
        enEventDriven(2, 0);
    }
    return ret;
}

/* static */ int stg_apart_e2f_EvProgGetApart202Key(void) {
    return EvSubItemGetAndAnim(APART_202_KEY, 21);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintRecoveryRead);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintMariaRead);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintSuicideRead);

/* static */ int stg_apart_e2f_EvProgUseApart202Key(void) {
    float pos[4];
    pos = stg_apart_e2f_pos_01F076F0;
    return EvSubItemUse0(APART_202_KEY, 23, 19003, 0, pos, 1);
}

/* static */ int stg_apart_e2f_EvProgMonkeyKick206(void) {
    float pos[4]; // not present in DWARF
    if (!GET_GAME_FLAG(GAME_FLAG_69)) {
        pos = stg_apart_e2f_pos_01F07700;
        SeCallPos(40007, 1.0f, pos, 2); // @note: not line matched these 2 should be only one line
    }
    return 1;
}

/* static */ int stg_apart_e2f_EvCharaDataClear(int room) {
    if ((room == 0x18) && (GET_GAME_FLAG(GAME_FLAG_69) && !GET_GAME_FLAG(GAME_FLAG_71))) { // @todo: add room id
        return 1;
    } 
    return 0;       
}

/* static */ void stg_apart_e2f_EvRoomInit(void) {
    int room; // r16    
    float pos[4]; // not present in DWARF

    room = RoomNameJms();
    if ((room == 0x18) && (GET_GAME_FLAG(GAME_FLAG_69) && !GET_GAME_FLAG(GAME_FLAG_71))) {
        CharaDataLoadDemo(stg_apart_e2f_chara_data_01F07710, 0);
        stg_apart_e2f_kao_dds = CharaDataLoadExtra(data_demo_kao_kao_dds, EN_SCU_CHARA_KIND);
        fsSync(0, -1);
    }
    if (room == 0x16) {
        pos = stg_apart_e2f_pos_01F07740;
        enSetInsect(pos, 5);
        return;
    }
    enKillAllInsect();
}

/* static */ void stg_apart_e2f_EvSoundCallAfterLoad(void) {
    if (RoomNameJms() == 0x18) {
        if (GET_GAME_FLAG(GAME_FLAG_69)) {
            SeCallPos(16000, 0.3f, stg_apart_e2f_tv_pos, 12);
            sh2gfw_SetNoise_CharaTexture(ITEM_NOA_CHARA_KIND); // https://silenthillmuseum.org/?game=sh2&model=chr-item-noa
            SET_GAME_FLAG(GAME_FLAG_70);
            return;
        }
        sh2gfw_RemoveNoise_CharaTexture(ITEM_NOA_CHARA_KIND);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvAllTimeFunc);

/* static */ void stg_apart_e2f_Delete_RedPointLight(void) {
    int* mp; // r17
    DrawEnvData* ded; // r16

    mp = Get_NowMapId();
    ded = Get_NowDrawEnvData();
    if (*mp == 0x90032) {
        if (EventProgressCheck() == 4) {            
            if (ded->pointLNum < 5) {
                ded->pointLNum = 5;
            }
        } else if (ded->pointLNum > 4) {
            ded->pointLNum = 4;
        }
    }
}
