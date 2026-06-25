#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/playing_info.h"

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

#include "Font/font.h"
#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"
#include "Effect/screen_effect.h"
#include "data/daily.thu/data_pic_out.h"

extern /* static */ char* stg_forest_dds_adr; // size: 0x4, address: 0x0
extern /* static */ float stg_forest_agl_pos_0[2][4]; // size: 0x20, address: 0x1F03A90
extern /* static */ float stg_forest_agl_pos_1[2][4]; // size: 0x20, address: 0x1F03AB0
extern /* static */ DramaDemo_PlayInfo stg_forest_grave; // @ 0x01F03B90
extern /* static */ DramaDemo_MessageTime stg_forest_movie_msg[6]; // @ 0x01F03AF0

extern /* static */ float stg_forest_forest_se_x; // size: 0x4, address: 0x1F03E18
extern /* static */ float stg_forest_forest_se_y; // size: 0x4, address: 0x1F03E20
extern /* static */ float stg_forest_forest_se_r; // size: 0x4, address: 0x1F03E28

extern /* static */ char* stg_forest_dds_adr_h; // size: 0x4, address: 0x1F02F80
extern /* static */ char* stg_forest_dds_adr_i; // size: 0x4, address: 0x1F02F88
extern /* static */ CharaData_DemoList stg_forest_chara_data[3]; // @ 0x01F03D10
extern /* static */ CharaData_DemoList D_01F03D10_fst[3]; // @ 0x01F03D10


extern fsFileIndex data_movie_hakaba_pss;
extern fsFileIndex data_demo_haka_agl_haka_agl_i_dds[1]; // size: 0x8, address: 0x3A12B8
extern fsFileIndex data_demo_haka_agl_haka_agl_h_dds[1]; // size: 0x8, address: 0x3A12B0
extern fsFileIndex data_demo_haka_agl_haka_agl_dds[1]; // size: 0x8, address: 0x3A12A8

#line 131
int stg_forest_EvProgFirstSaveWell(void) {
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

int stg_forest_EvProgAngelaInGrave(void) {
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
            if (DramaDemoMain(&stg_forest_grave)) EV_PROG_STEP(0xD);
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

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgGraveSureQuiet);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgGraveLookingFor);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgLastScene);

void stg_forest_EvProgGetChainsaw(void) {
    EvSubItemGetAndAnim(CHAINSAW, 4);
}

void stg_forest_EvStageInit(void) {
    CharaDataDeleteAll();
}

#line 529
void stg_forest_EvRoomInit(void) {
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
void stg_forest_EvSoundCallAfterLoad(void) {
    SeCallPos(10050, 1.0f, NULL, 8);
    stg_forest_forest_se_x = shRandF();
    stg_forest_forest_se_y = shRandF();
    stg_forest_forest_se_r = 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvAllTimeFunc);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_LinearTrim);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_Ca10_Hakaba_Angela_SetDrawEnv);
