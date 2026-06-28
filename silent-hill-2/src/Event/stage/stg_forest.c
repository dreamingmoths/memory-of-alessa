#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/mem_share.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/chara_admin.h"
#include "Event/demoview.h"
#include "Event/item.h"
#include "Event/chara_data_load.h"

#include "Chacter/m3_sc.h"
#include "Chacter/m3_angela.h"
#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/sh2_character_manage.h"

#include "Collision/cl_main.h"
#include "Effect/screen_effect.h"
#include "Font/font.h"
#include "GFW/sh2_DrawEnvData.h"
#include "GFW/sh2_set_drawenv.h"
#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"
#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"

#include "data/daily.thu/data_demo_mry_yarinaoshi_i.h"
#include "data/daily.thu/data_pic_out.h"
#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_haka_agl.h"
#include "data/daily.thu/data_chr_agl.h"
#include "data/daily.thu/data_chr_jms.h"
#include "data/daily.thu/data_chr_lau.h"

#define FOREST_SOUND_EFFECT_RADIUS 20000.0f

/* unmigrated data */
extern /* static */ CL_HITPOLY_PLANE stg_forest_clActWallList_ca19[3]; // size: 0xF0, address: 0x1F03650
extern /* static */ CL_HITPOLY_PLANE stg_forest_clActWallList_ca20[6]; // size: 0x1E0, address: 0x1F03740

/* data */
extern /* static */ float stg_forest_agl_pos_0[2][4] = {
    /* 1C90 01F03A90 DDE91745 */ 2430.616455f,
    /* 1C94 01F03A94 1ACA2445 */ 2636.631348f,
    /* 1C98 01F03A98 089BD5C4 */ -1708.844727f,
    /* 1C9C 01F03A9C 00000000 */ 0.0f,
    /* 1CA0 01F03AA0 BD3786B5 */ -9.9999999e-07f,
    /* 1CA4 01F03AA4 BD3706B7 */ -7.9999998e-06f,
    /* 1CA8 01F03AA8 00000000 */ 0.0f,
    /* 1CAC 01F03AAC 00000000 */ 0.0f,
}; // size: 0x20, address: 0x1F03A90
extern /* static */ float stg_forest_agl_pos_1[2][4] = {
    781.1212769f,
    2505.674072f,
    -394.2832031f,
    0.0f,
    0.0f,
    0.0f,
    1.9999999e-06f,
    0.0f,
}; // size: 0x20, address: 0x1F03AB0

/* bss */
static char* stg_forest_dds_adr = NULL; // size: 0x4, address: 0x01F03E00
static char* stg_forest_dds_adr_h = NULL; // size: 0x4, address: 0x1F03E08
static char* stg_forest_dds_adr_i = NULL; // size: 0x4, address: 0x1F03E10
static float stg_forest_forest_se_x = 0.0f; // size: 0x4, address: 0x1F03E18
static float stg_forest_forest_se_y = 0.0f; // size: 0x4, address: 0x1F03E20
static float stg_forest_forest_se_r = 0.0f; // size: 0x4, address: 0x1F03E28

#line 131
/* static */ int stg_forest_EvProgFirstSaveWell(void) {
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(2);
            /* fallthrough */
        case 2:
            if (!EvSubFileLoadAndFadeOut(NULL, &data_pic_out_p_redpaper_tex, 0))
                break;
            ScreenEffectFadeStart(4, 0.0f);
            EV_PROG_STEP(3);

                
        case 3:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) EV_PROG_STEP(8);
            break;

        case 8:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel)))
                EV_PROG_STEP(10);
            break;
        
        case 10:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (!EvSubMessage(0)) break;
            ScreenEffectFadeStart(11, 0.0f);
            EV_PROG_STEP(4);
            break;
        
        case 4:
            if (!ScreenEffectFadeCheck()) break;
            EV_PROG_STEP(13);

        case 13:
            SET_GAME_FLAG(5);
            SetSavePointName(2);
            SeCall(10051, 1.0f, 0);
            sh2sys_set_2(9);
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return 1;
    }

    return 0;
}

/* static */ int stg_forest_EvProgAngelaInGrave(void) {
    static short stg_forest_grave_anim_01F03AD0[10] = {
        /* 1CD0 01F03AD0 */ 0x41F,
        /* 1CD2 01F03AD2 */ 0xDB5,
        /* 1CD4 01F03AD4 */ 0x420,
        /* 1CD6 01F03AD6 */ 0xDB6,
        /* 1CD8 01F03AD8 */ 0x421,
        /* 1CDA 01F03ADA */ 0xDB7,
        /* 1CDC 01F03ADC */ 0x422,
        /* 1CDE 01F03ADE */ 0xDB8,
        /* 1CE0 01F03AE0 */ 0x423,
        /* 1CE2 01F03AE2 */ 0xDB9
    }; // @ 0x01F03AD0 @note: not present in dwarf
    static DramaDemo_MessageTime stg_forest_movie_msg[6] = {
        {
            /* 1CF0 01F03AF0 */ 0x234,
            /* 1CF2 01F03AF2 */ 0x270,
        },
        {
            /* 1CF4 01F03AF4 */ 0x276,
            /* 1CF6 01F03AF6 */ 0x2D0,
        },
        {
            /* 1CF8 01F03AF8 */ 0x2D0,
            /* 1CFA 01F03AFA */ 0x33F,
        },
        {
            /* 1CFC 01F03AFC */ 0x33F,
            /* 1CFE 01F03AFE */ 0x399,
        },
        {
            /* 1D00 01F03B00 */ 0x3DB,
            /* 1D02 01F03B02 */ 0x402,
        },
        {
            /* 1D04 01F03B04 */ 0xFFFF,
            /* 1D06 01F03B06 */ 0xFFFF,
        },
    }; // @ 0x01F03AF0
    static DramaDemo_MessageTime stg_forest_grave_movie_time_01F03B10[29] = {
        { 0xC,   0xA5    },
        { 0xA5,  0xED    },
        { 0xED,  0x168   },
        { 0x168, 0x1A4   },
        { 0x1A4, 0x1E9   },
        { 0x1E9, 0x207   },
        { 0x207, 0x22E   },
        { 0x22E, 0x2A6   },
        { 0x2CD, 0x3A2   },
        { 0x3A2, 0x402   },
        { 0x402, 0x447   },
        { 0x447, 0x4EC   },
        { 0x4EC, 0x56D   },
        { 0x56D, 0x5BB   },
        { 0x5BB, 0x5F1   },
        { 0x5F1, 0x696   },
        { 0x696, 0x708   },
        { 0x708, 0x753   },
        { 0x76E, 0x7D7   },
        { 0x7D7, 0x828   },
        { 0x828, 0x8C7   },
        { 0x8C7, 0x92D   },
        { 0x92D, 0x9ED   },
        { 0x9ED, 0xA6E   },
        { 0xAB0, 0xBA9   },
        { 0xBB8, 0xC30   },
        { 0xC30, 0xC90   },
        { 0xC90, 0xCC6   },
        { 0xFFFF, 0xFFFF }
    }; // @ 0x01F03B10 @note not present in dwarf
    static DramaDemo_PlayInfo stg_forest_grave = {
        /* .demo_no = */ 3,
        /* .adr_dds_top = */ NULL,
        /* .adr_anim = */ &stg_forest_grave_anim_01F03AD0,
        /* .adr_msg_time = */ &stg_forest_grave_movie_time_01F03B10,
        /* .msg_start = */ 10,
        /* .voice_sd_no = */ 0,
        /* .adr_voice = */ NULL,
        /* .stream_no = */ 60023,
        /* .stream_start = */ 0.0f,
        /* .add_pos_x = */ 0.0f,
        /* .add_pos_z = */ 0.0f
    }; // @ 0x01F03B90
    SubCharacter* scp; // r16
    int hide_ca11 = 0; // r16


    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            ScreenEffectFadeStart(7, 1.5f);
            SeBgmCall(2);
            EV_PROG_STEP(16);
        /* fallthrough */

        case 16:
            if (!ScreenEffectFadeCheck() || shSdStat() & 0xF) break;
            hide_ca11 = 1;
            shCharacterSetPosAfterDemo(sh2jms.player, (sceVu0FVECTOR){-20.84499931f, 2473.030029f,-1332.314941f, 0.0f}, -2.3561945f);
            EV_PROG_STEP(40);
            break;

        case 40:
            hide_ca11 = 1;
            EvSubMovieReady(&data_movie_hakaba_pss, stg_forest_movie_msg, 5);
            if (EvSubMovieStart(1)) {
                EV_PROG_STEP(43);
            }
            break;

        case 43:
            if (movieGetLastExitStatus()) {
                hide_ca11 = 1;
                EV_PROG_STEP(44);
            } else {
                EV_PROG_STEP(47);
            }
            break;

        case 44:
            hide_ca11 = 1;
            EvSubMovieEnd();
            stg_forest_grave.adr_dds_top = stg_forest_dds_adr;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            ScreenEffectFadeStart(5, 0.0f);
            EV_PROG_STEP(22);
            /* fallthrough */

        case 22:
            if (DramaDemoMain(&stg_forest_grave)) EV_PROG_STEP(13);
            else hide_ca11 = 1;
            break;

        case 47:
            EvSubMovieEnd();
            EV_PROG_STEP(13);
            break;

        case 13:
            ScreenEffectFadeStart(5, 0.0f);
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            SCNowDemoEventSwitch(sh2jms.player, 0);
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);

            if (shRandI() & 1) {
                SET_GAME_FLAG(37);
            }

            shCharacterSetPosAfterDemo(sh2jms.player, (sceVu0FVECTOR){-20.84499931f, 2473.030029f, -1332.314941f, 0.0f}, -3.0f * PI / 4.0f);
            scp = shCharacterGetSubCharacter(AGL_CHARA_KIND, 0);
            shCharacterHumanAGLAnimeSetP(scp, 3902);
            shCharacterSetPosAfterDemo(scp, stg_forest_agl_pos_1[0], PI);
            SeBgmCall(3);
            return 1;
    }

    if (hide_ca11) {
        loadBgCommon_HideMapBlockOutdoor(0x1000B);
    }

    return 0;
}

/* static */ int stg_forest_EvProgGraveSureQuiet(void) {
    static short stg_forest_grave_anim_01F03BE0[2] = {0x424, 0xDBA}; // @ 01F03BE0 @note: not present in dwarf
    static DramaDemo_MessageTime stg_forest_grave_movie_msg_01F03BF0[4] = {
        {
            /* 1DF0 01F03BF0 */ 0x0057,
            /* 1DF2 01F03BF2 */ 0x008D,
        },
        {
            /* 1DF4 01F03BF4 */ 0x008D,
            /* 1DF6 01F03BF6 */ 0x012F,
        },
        {
            /* 1DF8 01F03BF8 */ 0x012F,
            /* 1DFA 01F03BFA */ 0x0168,
        },
        {
            /* 1DFC 01F03BFC */ 0xFFFF,
            /* 1DFE 01F03BFE */ 0xFFFF,
        }
    }; // @ 0x01F03BF0 @note: not present in dwarf
    static DramaDemo_PlayInfo stg_forest_grave = {
        /* .demo_no = */ 4,
        /* .adr_dds_top = */ NULL,
        /* .adr_anim = */ &stg_forest_grave_anim_01F03BE0,
        /* .adr_msg_time = */ &stg_forest_grave_movie_msg_01F03BF0,
        /* .msg_start = */ 38,
        /* .voice_sd_no = */ 0,
        /* .adr_voice = */ NULL,
        /* .stream_no = */ 60024,
        /* .stream_start = */ 0.0f,
        /* .add_pos_x = */ 0.0f,
        /* .add_pos_z = */ 0.0f
    }; 
    SubCharacter* scp;

    switch (ev_p_step) {
        case 0:
            stg_forest_grave.adr_dds_top = stg_forest_dds_adr_h;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_forest_grave))
                EV_PROG_STEP(13);

            break;

        case 13:
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            shCharacterSetPosAfterDemo(sh2jms.player, (sceVu0FVECTOR){-179.0050049, 2487.649902, -1286.689941, 0}, TO_RAD(-75.6899f));
            scp = shCharacterGetSubCharacter(AGL_CHARA_KIND, 0);
            shCharacterHumanAGLAnimeSetP(scp, 3902);
            shCharacterSetPosAfterDemo(scp, *stg_forest_agl_pos_1, PI);
            if (shRandI() & 1) {
                SET_GAME_FLAG(37);
            } else {
                UNSET_GAME_FLAG(37);
            }
            return 1;
    }

    
    return 0;
}

/* static */ int stg_forest_EvProgGraveLookingFor(void) {
    static short stg_forest_grave_anim_01F03C40[2] = {0x425, 0xDBB}; // @ 01F03C40 @note: not present in dwarf
    static DramaDemo_MessageTime stg_forest_grave_movie_msg_01F03C48[3] = {
        {
            /* 1E48 01F03C48 */ 0x0054,
            /* 1E4A 01F03C4A */ 0x0096,
        },
        {
            /* 1E4C 01F03C4C */ 0x0096,
            /* 1E4E 01F03C4E */ 0x00C3,
        },
        {
            /* 1E50 01F03C50 */ 0xFFFF,
            /* 1E52 01F03C52 */ 0xFFFF,
        }
    }; // @ 0x01F03C48 @note: not present in dwarf
    static DramaDemo_PlayInfo stg_forest_grave = {
        /* .demo_no = */ 4,
        /* .adr_dds_top = */ NULL,
        /* .adr_anim = */ &stg_forest_grave_anim_01F03C40,
        /* .adr_msg_time = */ &stg_forest_grave_movie_msg_01F03C48,
        /* .msg_start = */ 41,
        /* .voice_sd_no = */ 0,
        /* .adr_voice = */ NULL,
        /* .stream_no = */ 60025,
        /* .stream_start = */ 0.0f,
        /* .add_pos_x = */ 0.0f,
        /* .add_pos_z = */ 0.0f
    }; // 0x01F03C60 
    SubCharacter* scp;

    switch (ev_p_step) {
        case 0:
            stg_forest_grave.adr_dds_top = stg_forest_dds_adr_i;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_forest_grave))
                EV_PROG_STEP(13);

            break;

        case 13:
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            shCharacterSetPosAfterDemo(sh2jms.player, (sceVu0FVECTOR){-493.0f, 2510.1899f, -1093.55f, 0.0f}, TO_RAD(-98.990835f));
            scp = shCharacterGetSubCharacter(AGL_CHARA_KIND, 0);
            shCharacterHumanAGLAnimeSetP(scp, 3902);
            shCharacterSetPosAfterDemo(scp, *stg_forest_agl_pos_1, PI);
            if (shRandI() & 1) {
                SET_GAME_FLAG(37);
            } else {
                UNSET_GAME_FLAG(37);
            }
            return 1;
    }

    
    return 0;
}

/* static */ int stg_forest_EvProgLastScene(void) {
    static short stg_forest_forest_anim_01F03CA0[2] = {0x3CF, 0x9EC}; // @ 01F03CA0 @note: not present in dwarf
    static DramaDemo_PlayInfo stg_forest_info = {
        /* .demo_no = */ 86,
        /* .adr_dds_top = */ MemShare_gp_data_buf,
        /* .adr_anim = */ &stg_forest_forest_anim_01F03CA0,
        /* .adr_msg_time = */ NULL,
        /* .msg_start = */ 0x0,
        /* .voice_sd_no = */ 0,
        /* .adr_voice = */ NULL,
        /* .stream_no = */ 0x0,
        /* .stream_start = */ 0.0f,
        /* .add_pos_x = */ 0.0f,
        /* .add_pos_z = */ 0.0f
    }; // @ 0x01F03CB0
    static CharaData_DemoList stg_forest_chara_data[2] = {
        {
            /* .kind = */      LAU_CHARA_KIND,
            /* .model = */     data_chr_lau_lau_mdl,
            /* .animation = */ data_demo_mry_yarinaoshi_i_lau_anm,
            /* .shadow = */    NULL,
            /* .cluster = */   data_demo_mry_yarinaoshi_i_lau_cls
        },
        0
    }; // @ 0x01F03CE0
    static u_long128* stg_forest_anim_adr = NULL; // @ 0x01F03E30

    switch (ev_p_step) {
        case 0: 
            FcRead(&data_demo_mry_yarinaoshi_i_mry_yarinaoshi_i_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_forest_chara_data, 0);
            stg_forest_anim_adr = CharaDataLoadExtra(&data_demo_mry_yarinaoshi_i_lll_jms_anm, 0x200);
            fsSync(0, -1);
            stg_forest_anim_adr = CharaDataAnimAdressExchange(sh2jms.player, stg_forest_anim_adr);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(22);
            /* fallthrough */

        case 22:
            if (DramaDemoMain(&stg_forest_info)) {
                ScreenEffectFadeStart(1, 0.0f);
                EV_PROG_STEP(4);
            }
            break;

        case 4: 
            if (ScreenEffectFadeCheck())
                EV_PROG_STEP(40);

            break;

        case 40:
            EvSubMovieReady(&data_movie_ending_pss, NULL, 0);
            if (EvSubMovieStart(1))
                EV_PROG_STEP(43);

            break;

        case 43:
            if (movieGetLastExitStatus())
                EV_PROG_STEP(13);

            break;

        case 13:
            EvSubMovieEnd();
            stg_forest_anim_adr = CharaDataAnimAdressExchange(sh2jms.player, stg_forest_anim_adr);
            playing.clear_end_kind |= 1;

            switch (playing.riddle_level) {
                case 0:
                    playing.clear_end_kind |= 1 << 5;
                    break;
                case 1:
                    playing.clear_end_kind |= 1 << 6;
                    break;
                case 2:
                    playing.clear_end_kind |= 1 << 7;
                    break;
                default:
                    playing.clear_end_kind -= 1 << 7;
                    break;
            }

            playing.clear_end_number++;
            sh2sys_set_2(10);
            return 1;
    }

    return 0;
}

/* static */ void stg_forest_EvProgGetChainsaw(void) {
    EvSubItemGetAndAnim(CHAINSAW, 4);
}

/* static */ void stg_forest_EvStageInit(void) {
    CharaDataDeleteAll();
}

#line 529
/* static */ void stg_forest_EvRoomInit(void) {
    static CharaData_DemoList stg_forest_chara_data[3] = {
        {
            /* .kind = */      HHH_JMS_CHARA_KIND,
            /* .model = */     data_chr_jms_hhh_jms_notex_mdl,
            /* .animation = */ data_demo_haka_agl_hhh_jms_anm,
            /* .shadow = */    data_chr_jms_hhh_jms_kg1,
            /* .cluster = */   data_demo_haka_agl_hhh_jms_cls
        },
        {
            /* .kind = */      AGL_CHARA_KIND,
            /* .model = */     data_chr_agl_agl_mdl,
            /* .animation = */ data_demo_haka_agl_agl_anm,
            /* .shadow = */    data_chr_agl_agl_kg1,
            /* .cluster = */   data_demo_haka_agl_agl_cls
        },
        0,
    }; // @ 0x01F03D10
    SubCharacter* scp; // r2
    float vec0[4]; // r29+0x10

    if (GET_GAME_FLAG(512)) return;
    CharaDataLoadDemo(stg_forest_chara_data, 0);
    stg_forest_dds_adr = CharaDataLoadExtra(data_demo_haka_agl_haka_agl_dds, 0x200);

    stg_forest_dds_adr_h = CharaDataLoadExtra(data_demo_haka_agl_haka_agl_h_dds, 0x200);
    
    stg_forest_dds_adr_i = CharaDataLoadExtra(data_demo_haka_agl_haka_agl_i_dds, 0x200);
    
    fsSync(0, -1);
    *(u_long128*) &vec0 = 0;
    vec0[1] = PI;
    if (GET_GAME_FLAG(36)) {
        scp = CharaWorkCreate(AGL_CHARA_KIND, 0, stg_forest_agl_pos_1[0], vec0, 0);
        shCharacterHumanAGLAnimeSetP(scp, 3902);
    } else {
        scp = CharaWorkCreate(AGL_CHARA_KIND, 0, stg_forest_agl_pos_0[0], vec0, 0);
        shCharacterHumanAGLAnimeSetP(scp, 3901);
    }
}

#line 565
/* static */ void stg_forest_EvSoundCallAfterLoad(void) {
    SeCallPos(10050, 1.0f, NULL, 8);
    stg_forest_forest_se_x = shRandF();
    stg_forest_forest_se_y = shRandF();
    stg_forest_forest_se_r = 0;
}

#line 575
/* static */ void stg_forest_EvAllTimeFunc(void) {
    int disp_ctrl_list[5] = {0}; // r29+0x10
    float se_vol; // r29+0x30


    disp_ctrl_list[0] = 0;
    if (GET_GAME_FLAG(12)) {
        clAddDynamicWall(stg_forest_clActWallList_ca19);
        clAddDynamicWall(stg_forest_clActWallList_ca20);
        EvDispControlModelEntry(disp_ctrl_list, 20, 0);

    } else EvDispControlModelEntry(disp_ctrl_list, 20, -1);

    
    
    if (GET_BIT(Sh2sys.main_status, 6)) EvDispControlModelEntry(disp_ctrl_list, 10, 0);

    else EvDispControlModelEntry(disp_ctrl_list, 10, -1);
    
    
    EvDispControlModelExec(disp_ctrl_list);
    
    stg_forest_forest_se_r += (((0.5f + (1.5f * stg_forest_forest_se_x)) * (PI * (2.0f * shGetDT()))) / 4.0f);
    
    if (stg_forest_forest_se_r > TAU) {
        stg_forest_forest_se_r -= TAU;
        stg_forest_forest_se_x = shRandF();
        stg_forest_forest_se_y = shRandF();
    }
    se_vol = 0.8f + (0.2f * stg_forest_forest_se_y * shSinF(stg_forest_forest_se_r));
    if (sh2jms.player->pos.x > -FOREST_SOUND_EFFECT_RADIUS && sh2jms.player->pos.z > -FOREST_SOUND_EFFECT_RADIUS) {
        se_vol *= 1.0f - ((FOREST_SOUND_EFFECT_RADIUS + float_min(sh2jms.player->pos.x, sh2jms.player->pos.z)) / FOREST_SOUND_EFFECT_RADIUS);
    
        if (se_vol <= 0.0f) se_vol = 0.001f;
    }
    Se2dManageDataVolumeChange(10050, se_vol);
}

static float stg_forest_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

static float stg_forest_FogParameters[4] = {
    17635.0f,
    10000.0f,
    21.0f,
    234.0f
}; // size: 0x10, address: 0x1F03D50
static float stg_forest_FarNear[4] = {
    18000.0f,
    0.0f,
    2.426470518f,
    0.0f
}; // size: 0x10, address: 0x1F03D60
static float stg_forest_MoveFog[4]; // size: 0x10, address: 0x0
static float stg_forest_Asahi_dir[4] = {
    -0.9300000072f,
    0.1159999967f,
    -0.3490000069f,
    0.1000000015f,
}; // size: 0x10, address: 0x1F03D70
static float stg_forest_Asahi_col[4] = {
    0.25f,
    0.20f,
    0.20f,
    0.10f,
}; // size: 0x10, address: 0x1F03D80

/* static */ void stg_forest_Ca10_Hakaba_Angela_SetDrawEnv(void) {
    
    float origin[4] = {0}; // r29+0x20
    float nowpos[4]; // r29+0x30
    float dist; // r29+0x40
    float fogfar, fognear; // r2, r20
    float az; // r3
    float fnpow, ffpow; // r21, r22
    float farcliptrim; // r4
    vwGetViewPosition(nowpos);
    
    
    
    
    
    
    
    
    
    
    
    
    if (DramaDemoNumber() != 0) {
        dist = 0.0f;
        farcliptrim = 0.0f;
    } else if (EventProgressCheck() == 2) {
        dist = vec3_dist_xz(origin, nowpos);
        farcliptrim = 2000.0f;
    } else {
        dist = 10000.0f;
        farcliptrim = 2000.0f;
    }

    if (dist > 10000.0f)
        dist = 10000.0f;

    
    az = stg_forest_LinearTrim(stg_forest_FarNear[0], 7500.0f, 0.0f, 10000.0f, dist);
    fogfar = stg_forest_LinearTrim(stg_forest_FogParameters[0], 5500.0f, 0.0f, 10000.0f, dist);
    fognear = stg_forest_LinearTrim(stg_forest_FogParameters[1], 3000.0f, 0.0f, 10000.0f, dist);
    fnpow = stg_forest_LinearTrim(stg_forest_FogParameters[3], 235.0f, 0.0f, 10000.0f, dist);
    ffpow = stg_forest_LinearTrim(stg_forest_FogParameters[2], 20.0f, 0.0f, 10000.0f, dist);
    
    Env_ctl.camera_parms2[2] = az + farcliptrim;
    sh2gfw_Set_Fogfar(fogfar);
    sh2gfw_Set_FogNear(fognear);
    sh2gfw_Set_FogMax(ffpow);
    sh2gfw_Set_FogMin(fnpow); // @bug: `sh2gfw_Set_FogMin` was not included in the header
    
    if (!sh2gfw_Check_ParallelDemoLight(0))
        sh2gfw_Set_PallarelLight(stg_forest_Asahi_dir, stg_forest_Asahi_col, 0); }
