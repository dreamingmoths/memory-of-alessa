#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/demoview.h"
#include "Event/chara_admin.h"
#include "Event/chara_data_load.h"
#include "Event/stg_name.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_eddie.h"

#include "Collision/cl_main.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "movie/movie_main.h"

#include "Effect/screen_effect.h"

#include "SH2_common/pad.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "view/vc_main.h"

#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_gero_edi.h"
#include "data/daily.thu/data_pic_apt.h"

// @todo: migrate data

extern /* static */ CL_HITPOLY_PLANE stg_apart_e1f_clActWallList_ap100[4]; // @ 0x01F02B30

extern /* static */ float stg_apart_e1f_edi_vec[2][4]; // @ 0x01F02DC0

extern /* static */ DramaDemo_PlayInfo stg_apart_e1f_vomit; // @ 0x01F02E60

extern /* static */ DramaDemo_PlayInfo stg_apart_e1f_info_h; // @ 0x01F02ED0

extern /* static */ DramaDemo_PlayInfo stg_apart_e1f_info_i; // @ 0x01F02F00

extern /* static */ CharaData_DemoList stg_apart_e1f_chara_data_01F02F30[3]; // @ 0x01F02F30

extern /* static */ float stg_apart_e1f_pos_01F02F70[4]; // @ 0x01F02F70

// @todo: migrate bss

extern /* static */ char* stg_apart_e1f_dds_adr_h; // size: 0x4, address: 0x01F02F80
extern /* static */ char* stg_apart_e1f_dds_adr_i; // size: 0x4, address: 0x01F02F88


/* static */ int stg_apart_e1f_EvProgVomitEddie(void) {
    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_gero_edi_gero_edi_dds, MemShare_gp_data_buf);
            fsSync(0, -1);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            ScreenEffectFadeStart(3, 0.0f);
            EV_PROG_STEP(40);
            /* fallthrough */
        case 40:
            EvSubMovieReady(data_movie_gero_pss, NULL, 0);
            if (EvSubMovieStart(1)) {
                EV_PROG_STEP(43);
            }
            break;
            
        case 43:
            if (movieGetLastExitStatus()) {
                EV_PROG_STEP(44);
            } else {
                EV_PROG_STEP(47);
            }
            break;
        case 44:
            EvSubMovieEnd();
            ScreenEffectFadeStart(5, 0.0f);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain(&stg_apart_e1f_vomit)) {
                EV_PROG_STEP(13);
            }
            break;
        case 47:
            EvSubMovieEnd();
            EV_PROG_STEP(13);
            /* fallthrough */
        case 13:
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            shCharacter_Manage_Delete(NULL, HHH_EDI_CHARA_KIND, 0);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_87);
            return 1;
    }
    return 0;
}

/* static */ int stg_apart_e1f_EvProgVomitEddieAfter(void) {
    struct SubCharacter * scp; // r2
    int ret; // r2 idk where this is used
    
    switch (ev_p_step) {
        case 0:
            stg_apart_e1f_info_h.adr_dds_top = stg_apart_e1f_dds_adr_h;
            stg_apart_e1f_info_i.adr_dds_top = stg_apart_e1f_dds_adr_i;
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(22);
            /* fallthrough */
        case 22:
            if (DramaDemoMain((GET_GAME_FLAG(GAME_FLAG_87)) ? &stg_apart_e1f_info_h : &stg_apart_e1f_info_i)) {
                EV_PROG_STEP(13);
            }
            break;
            
        case 13:
            shCharacter_Manage_Delete(NULL, HHH_JMS_CHARA_KIND, 0);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            if (!GET_GAME_FLAG(GAME_FLAG_87)) {
                sh2jms.player->rot.y = -2.5585005f;
            }
            scp = shCharacterGetSubCharacter(HHH_EDI_CHARA_KIND, 0);
            scp->pos.x = stg_apart_e1f_edi_vec[0][0];
            scp->pos.y = stg_apart_e1f_edi_vec[0][1];
            scp->pos.z = stg_apart_e1f_edi_vec[0][2];
            scp->rot.z = 0.0f;
            scp->rot.x = 0.0f;
            scp->rot.y = PI;
            shCharacterHumanEDIAnimeSetP(scp, EDDIE_PLAY_ANIM_4801);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            return 1;
    }
    
    return 0;
}

/* static */ int stg_apart_e1f_EvProgTouristGuideRead(void) {
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            if (GET_GAME_FLAG(GAME_FLAG_84)) {
                EV_PROG_STEP(2);
            }
            EV_PROG_STEP(30);
            break;
            
        case 30:
            if (EvSubMessage(1)) {
                EV_PROG_STEP(2);
            case 2:
                if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_tourist_tex, NULL)) {
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
            }
            break;
            
        case 8:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) {
                EV_PROG_STEP(10);
            }
            break;
            
        case 10:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubMessage(0)) {
                ScreenEffectFadeStart(1, 0.0f);
                EV_PROG_STEP(4);
            }
            break;
            
        case 4:
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(13);
                ScreenEffectFadeStart(4, 0.0f);
            case 13:
                SCNowPlayableEventSwitch(sh2jms.player, false);
                return 1;
            }
            break;
    }
    
    return 0;
}

/* static */ int stg_apart_e1f_EvCharaDataClear(int room) {
    if ((room == 0x1E) && !GET_GAME_FLAG(GAME_FLAG_88)) // @todo: add defines
        return 1;    
    return 0;
}

/* static */ void stg_apart_e1f_EvRoomInit(void) {
    float pos[4];

    if ((RoomNameJms() == 0x1E) && !GET_GAME_FLAG(GAME_FLAG_88)) { // @todo: add defines
        CharaDataLoadDemo(stg_apart_e1f_chara_data_01F02F30, 0);
        if (GET_GAME_FLAG(GAME_FLAG_85)) {
            pos = stg_apart_e1f_pos_01F02F70;
            shCharacterHumanEDIAnimeSetP(CharaWorkCreate(HHH_EDI_CHARA_KIND, 0, *stg_apart_e1f_edi_vec, &pos, 0), EDDIE_PLAY_ANIM_4801);
            stg_apart_e1f_dds_adr_h = CharaDataLoadExtra(data_demo_gero_edi_gero_edi_h_dds, 512);
            stg_apart_e1f_dds_adr_i = CharaDataLoadExtra(data_demo_gero_edi_gero_edi_i_dds, 512);
            fsSync(0, -1);
        }
    }
}

/* static */ void stg_apart_e1f_EvAllTimeFunc(void) {
    if ((RoomNameJms() == 0x1E) && !GET_GAME_FLAG(GAME_FLAG_88)) { // @todo: add defines
        clAddDynamicWall(stg_apart_e1f_clActWallList_ap100);
    }
}
