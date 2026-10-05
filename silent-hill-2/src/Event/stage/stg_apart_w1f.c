#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/mem_share.h"
#include "SH2_common/playing_info.h"

#include "vec.h"

#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_knife_agl.h"
#include "data/daily.thu/data_pic_apt.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/sh2_battle_list.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/picture.h"
#include "Event/demoview.h"
#include "Event/chara_admin.h"

#include "Effect/screen_effect.h"
#include "sound/sh_sound.h"
#include "Multi_thr/filesys/fcread.h"

/**
 * In the coin puzzle, there are 3 coin types and 5 slots.
 *
 * The three coin types are:
 *
 * - the prisoner,
 * - the elder,
 * - the snake.
 *
 * The arrangement of the coins depends on the riddle level.
 *
 * The coins are mapped to game flags in the following way:
 *
 * coin_flag = 126 + coin_kind * 5 + coin_slot
 *
 * where 126 is the base coin flag.
 *
 * So, COIN_PUZZLE_FLAG(i, j) is true when the ith coin type is in the jth slot. 
 */
#define COIN_PUZZLE_FLAG(kind, slot) (GAME_FLAG_126 + (kind) * 5 + (slot))

/* static */ int stg_apart_w1f_EvProgLookThreeCoin(void);
/* static */ int stg_apart_w1f_EvProgSetThreeCoin(void);
/* static */ void stg_apart_w1f_EvProgSubDrawCoin(void);
/* static */ int stg_apart_w1f_EvProgSubCoinCursor(void);
/* static */ int stg_apart_w1f_EvProgAngelaWithKnife(void);
/* static */ int stg_apart_w1f_EvProgGetCoinOfPrisoner(void);
/* static */ int stg_apart_w1f_EvProgGetWhiteChrism(void);
/* static */ int stg_apart_w1f_EvProgGetLyneKey(void);
/* static */ int stg_apart_w1f_EvProgLookFamilyPicture(void);
/* static */ void stg_apart_w1f_EvAllTimeFunc(void);
/* static */ int stg_apart_w1f_EvBgmControl(void);
/* static */ void stg_apart_w1f_TrimColorFilter(void);

extern /* static */ char ev_pos[302]; // size: 0x12E, address: 0x1F03D00
extern /* static */ struct Event_List ev_list[32]; // size: 0x200, address: 0x1F03E30
extern /* static */ struct Item_List gi_list[9]; // size: 0x90, address: 0x1F04030
extern /* static */ int (* ev_prog[8])(); // size: 0x20, address: 0x1F040C0
extern /* static */ GfwFunc gfw_func; // size: 0x10, address: 0x1F040E0
extern /* static */ Model_List mdl_list[20]; // size: 0x3C0, address: 0x1F040F0
extern /* static */ Enemy_List en_list[5]; // size: 0x64, address: 0x1F044B0
extern Stage_Data stage_apart_w1f; // size: 0x44, address: 0x1F04520

extern /* static */ sceVu0FVECTOR stg_apart_w1f_key_lyne[2]; // size: 0x20, address: 0x1F04570
extern /* static */ char cam_change; // size: 0x1, address: 0x1F04A00
extern /* static */ bool stg_apart_w1f_cam_change; // size: 0x1, address: 0x1F04A00
extern float stg_apart_w1f_coin_alpha[3]; // size: 0xC, address: 0x1F04A20
extern bool stg_apart_w1f_coin_hole; // size: 0x1, address: 0x1F04A10
extern bool stg_apart_w1f_coin_kind; // size: 0x1, address: 0x1F04A18
extern bool stg_apart_w1f_coin_onoff; // size: 0x1, address: 0x1F04A08
extern /* static */ char coin_pad; // size: 0x1, address: 0x0

#line 219
/* static */ int stg_apart_w1f_EvProgLookThreeCoin(void) {
    int i; // r5

    switch (ev_p_step) {
        default:
            break;

        case 3:
        case 8: 
        case 5: 
        case 6: 
        case 7: 
        case 4: 
        case 30:
        case 31:
        case 32:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            if (ev_p_step - 6 <= 1u || ev_p_step == 4 || ev_p_step == 32) {
                stg_apart_w1f_EvProgSubDrawCoin();
            }
            if (ev_p_step - 30 <= 2u) {
                EvSubPictureFilter();
            }
            EvSubPictureEnd();
    }

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            for (i = 0; i < 3; i++) {
                stg_apart_w1f_coin_alpha[i] = 1.0f;
            }
            EV_PROG_STEP(2);
           
        case 2:
            if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_desk_hint_tex, 0)) {
                ScreenEffectFadeStart(4, 0.0f);
                EV_PROG_STEP(3);
        case 3:
                if (ScreenEffectFadeCheck())
                    EV_PROG_STEP(8);
            }
            break;

        case 8:
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel))
                EV_PROG_STEP(30);
            break;

        case 30:
            if (EvSubMessage(4))
                EV_PROG_STEP(31);
            break;

        case 31:
            if (playing.riddle_level == SH2_RIDDLE_LEVEL_EASY) {
                SET_GAME_FLAG(GAME_FLAG_609);
                if (!EvSubMessage(64)) break;
            } else if (playing.riddle_level == SH2_RIDDLE_LEVEL_NORMAL) {
                SET_GAME_FLAG(GAME_FLAG_123);
                if (!EvSubMessage(1)) break;
            } else if (playing.riddle_level == SH2_RIDDLE_LEVEL_HARD) {
                SET_GAME_FLAG(GAME_FLAG_124);
                if (!EvSubMessage(2)) break;
            } else {
                SET_GAME_FLAG(GAME_FLAG_125);
                if (!EvSubMessage(3)) break;
            }
            EV_PROG_STEP(5);
            break;

        case 5:
            if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_desk_coin_tex, data_pic_apt_p_desk_coin_coin_tex)) {
                ScreenEffectFadeStart(4, 0.0f);
                EV_PROG_STEP(6);
            }
            break;

        case 6:
            if (ScreenEffectFadeCheck()) EV_PROG_STEP(7);
            break;

        case 7:
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel))
                EV_PROG_STEP(32);
            break;

        case 32:
            if (EvSubMessage(5)) {
                EV_PROG_STEP(4);
                ScreenEffectFadeStart(1, 0.0f);
            }
            break;

        case 4:
            if (ScreenEffectFadeCheck())
                EV_PROG_STEP(13);
            break;

        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            ScreenEffectFadeStart(4, 0.0f);
            return true;
    }

    return false;
}

#line 330
/* static */ int stg_apart_w1f_EvProgSetThreeCoin(void) {
    extern /* static */ float chara_vec[5][2][4]; // @ 0x01F045A0
    extern /* static */ short chara_kind[4]; // @ 0x01F04590
    int i; // r16
    int j; // r17








    
    switch (ev_p_step) {
        case 3:
        case 10:
        case 8:  
        case 4:
        case 7: 
        case 16:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            stg_apart_w1f_EvProgSubDrawCoin();
            if (ev_p_step == 8) EvSubPictureCursor(0);
            EvSubPictureEnd();
    }

    
    switch (ev_p_step) {                           
        case 0:                                        
            SCNowPlayableEventSwitch(sh2jms.player, true);
            for (i = 0; i < 3; i++) stg_apart_w1f_coin_alpha[i] = 1.0f;
            if (GET_GAME_FLAG(GAME_FLAG_120) || GET_GAME_FLAG(GAME_FLAG_121) || GET_GAME_FLAG(GAME_FLAG_122))
                
                stg_apart_w1f_coin_onoff = true;
            else stg_apart_w1f_coin_onoff = false;
            ev_cursor_x = ev_cursor_y = 0.0f;
            EV_PROG_STEP(2);

        
        case 2:                                        
            if (!EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_desk_coin_tex, data_pic_apt_p_desk_coin_coin_tex)) break;
        
                
            ScreenEffectFadeStart(4, 0.0f);
            EV_PROG_STEP(3);
    
                
        case 3:                                    
            if (ScreenEffectFadeCheck()) 
                EV_PROG_STEP(10);
        break;

        case 10:                                       
            if (stg_apart_w1f_coin_onoff) {
                if (!EvSubMessage(6)) break;
            } else {
                if (!EvSubMessage(7)) break;
            }
            EV_PROG_STEP(8);
            break;
        
        case 8:                                        
            if (stg_apart_w1f_EvProgSubCoinCursor()) {
                EV_PROG_STEP(7);
            } else if (shPadTrigger(0, key_config.cancel)) {
                ScreenEffectFadeStart(1, 0.0f);
                EV_PROG_STEP(4);
            }
            break;
        
        case 7:                                        
            if (stg_apart_w1f_coin_onoff) {
                stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] += shGetDT();
                if (stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] > 1.0f) {
                    stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] = 1.0f;
                    ItemUse(0x2F + stg_apart_w1f_coin_kind);
                    EV_PROG_STEP(0x10);
                }
            } else {
                stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] -= shGetDT();
                if (stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] < 0.0f) {
                    stg_apart_w1f_coin_alpha[stg_apart_w1f_coin_kind] = 0.0f;
        
                    UNSET_GAME_FLAG(COIN_PUZZLE_FLAG(stg_apart_w1f_coin_kind, stg_apart_w1f_coin_hole));
                    ItemGet(0x2F + stg_apart_w1f_coin_kind);
                    EV_PROG_STEP(8);
                }
            }
            break;
        
        case 16:
            if (!shPadTrigger(0, key_config.enter) && !shPadTrigger(0, key_config.cancel))
                break;
            ScreenEffectFadeStart(1, 0.0f);
            EV_PROG_STEP(4);
            break;
        
        case 4:                                
            if (!ScreenEffectFadeCheck()) break;    
            for (i = 0; i < 15; i++)
                if (GET_GAME_FLAG(i + 126)) break;
            if (i < 15) SET_GAME_FLAG(GAME_FLAG_141);
            else UNSET_GAME_FLAG(GAME_FLAG_141);
            
            EV_PROG_STEP(13);

            if (
                (playing.riddle_level == SH2_RIDDLE_LEVEL_EASY   && GET_GAME_FLAG(COIN_PUZZLE_FLAG(0, 2)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(1, 0)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(2, 4))) ||
                (playing.riddle_level == SH2_RIDDLE_LEVEL_NORMAL && GET_GAME_FLAG(COIN_PUZZLE_FLAG(0, 4)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(1, 1)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(2, 2))) ||
                (playing.riddle_level == SH2_RIDDLE_LEVEL_HARD   && GET_GAME_FLAG(COIN_PUZZLE_FLAG(0, 3)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(1, 1)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(2, 4))) ||
                (playing.riddle_level == SH2_RIDDLE_LEVEL_EXTRA  && GET_GAME_FLAG(COIN_PUZZLE_FLAG(0, 2)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(1, 0)) && GET_GAME_FLAG(COIN_PUZZLE_FLAG(2, 3)))
            ) {
                SET_GAME_FLAG(GAME_FLAG_142);
                SeCall(16010, 1.0f, 0);
                CharaWorkCreate(ITEM_X_KEYLYNE_CHARA_KIND, 0, &stg_apart_w1f_key_lyne[0], &stg_apart_w1f_key_lyne[1], 0);
                EV_PROG_STEP(13);
            } else {
                EV_PROG_STEP(13); // @bug ev_prog_step is already 13
            }

            for (i = 0; i < 3; i++)
                shCharacter_Manage_Delete(NULL, chara_kind[i], 0);

            if (!GET_GAME_FLAG(GAME_FLAG_142)) {
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 5; j++)
                        if (GET_GAME_FLAG(COIN_PUZZLE_FLAG(i, j)))
                            CharaWorkCreate(chara_kind[i], 0, chara_vec[j][0], chara_vec[j][1], 0);
            }
            break;
        case 13:                                       
            ScreenEffectFadeStart(4, 0.0f);
            SCNowPlayableEventSwitch(sh2jms.player, false);
            UNSET_GAME_FLAG(GAME_FLAG_120);
            UNSET_GAME_FLAG(GAME_FLAG_121);
            UNSET_GAME_FLAG(GAME_FLAG_122);
            return true;
    }

    return false;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_w1f", stg_apart_w1f_EvProgSubDrawCoin);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_w1f", stg_apart_w1f_EvProgSubCoinCursor);


/* static */ int stg_apart_w1f_EvProgAngelaWithKnife(void) {
    extern /* static */ CharaData_DemoList chara_data[9]; // @ 0x01F04830
    extern /* static */ DramaDemo_MessageTime knife_msg_mov[2]; // @ 0x01F047F0
    extern /* static */ DramaDemo_PlayInfo knife; // @ 0x01F04800
    extern /* static */ sceVu0FVECTOR jms_pos; // @ 0x01F048F0
    extern /* static */ float jms_rot; // @ 0x01F04900
    sceVu0FVECTOR vec; // r29+0x20
    int ret; // r16

    switch (ev_p_step) {
        case 0:
            FcRead(data_demo_knife_agl_knife_agl_dds, MemShare_gp_data_buf);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            CharaDataLoadDemo(chara_data, 0);
            fsSync(0, -1);
            ScreenEffectFadeStart(3, 0.0f);
            EV_PROG_STEP(40);
           

        case 40:
            EvSubMovieReady(data_movie_knife_pss, knife_msg_mov, 12);
            if (EvSubMovieStart(1)) EV_PROG_STEP(43);
            break;

        case 43:
            if (movieGetLastExitStatus()) EV_PROG_STEP(44);
            else EV_PROG_STEP(47);
            break;

        case 44:
            EvSubMovieEnd();
            ScreenEffectFadeStart(5, 0.0f);
            EV_PROG_STEP(22);
           

        case 22:
            ret = DramaDemoMain(&knife);
            if (shCharacterGetSubCharacter(RHHH_JMS_CHARA_KIND, 0) == NULL) {
                vec_zero(vec);
                CharaWorkCreate(RHHH_JMS_CHARA_KIND, 0, vec, vec, 0);
                CharaWorkCreate(RAGL_CHARA_KIND, 0, vec, vec, 0);
                CharaWorkCreate(ITEM_RI_KNIFE_CHARA_KIND, 0, vec, vec, 0);
                CharaWorkCreate(ITEM_RI_PHOTO_CHARA_KIND, 0, vec, vec, 0);
            }
            if (demo_frame > total_demo_frame - 30.0f)
                ScreenEffectFadeStart(2, 1.0f);
            if (ret) EV_PROG_STEP(13);
            break;


        case 47:
            EvSubMovieEnd();
            EV_PROG_STEP(13);
           

        case 13:
            ScreenEffectFadeStart(3, 0.0f);
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(RHHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(AGL_CHARA_KIND);
            CharaDataDeleteOne(RAGL_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_KNIFE_CHARA_KIND);
            CharaDataDeleteOne(ITEM_RI_KNIFE_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_PHOTO_CHARA_KIND);
            CharaDataDeleteOne(ITEM_RI_PHOTO_CHARA_KIND);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            shCharacterSetPosAfterDemo(sh2jms.player, jms_pos, jms_rot);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            ScreenEffectFadeStart(4, 0.0f);
            ItemGet(21);
            return true;
    }

    return false;
}


/* static */ int stg_apart_w1f_EvProgGetCoinOfPrisoner(void) {
    EvSubItemGetAndAnim(49, 8);
}


/* static */ int stg_apart_w1f_EvProgGetWhiteChrism(void) {
    EvSubItemGetAndAnim(73, 10);
}


/* static */ int stg_apart_w1f_EvProgGetLyneKey(void) {
    EvSubItemGetAndAnim(28, 9);
}


/* static */ int stg_apart_w1f_EvProgLookFamilyPicture(void) {
    switch (ev_p_step) {                           
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20001);
            EV_PROG_STEP(27);
           

        case 27:
            if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                EV_PROG_STEP(10);
            }
            break;

        case 10:
            if (EvSubMessage(0)) EV_PROG_STEP(2);
            break;

        case 2:
            if (EvSubFileLoadAndFadeOut(NULL, data_pic_apt_p_family_tex, NULL)) {
                ScreenEffectFadeStart(4, 0.0f);
                EV_PROG_STEP(3);
            case 3:
                EvSubPictureStart();
                EvSubPictureDisplayOnly();
                EvSubPictureEnd();
                if (ScreenEffectFadeCheck()) EV_PROG_STEP(8);
            }
            break;

        case 8:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (shPadTrigger(0, key_config.enter) || shPadTrigger(0, key_config.cancel)) {
                ScreenEffectFadeStart(1, 0.0f);
                EV_PROG_STEP(4);
            }
            break;

        case 4:
            if (ScreenEffectFadeCheck()) {
                EV_PROG_STEP(28);
                shCharacterAnimeRestart(sh2jms.player);
                ScreenEffectFadeStart(4, 0.0f);

        case 28:
                if (shCharacterAnimeIsEnd(sh2jms.player)) EV_PROG_STEP(13);
            }
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return true;
    }

    return false;
}


/* static */ void stg_apart_w1f_EvRoomInit(void) {
    switch (RoomNameJms()) {
        default:
            return;

        case 36:
            stg_apart_w1f_cam_change = false;
            break;
    }
}


/* static */ void stg_apart_w1f_EvAllTimeFunc(void) {
    int disp_ctrl_list[3]; // r29+0x10

    disp_ctrl_list[0] = 0;
    
    switch (RoomNameJms()) {
        case 34:
            EvDispControlModelEntry(disp_ctrl_list, 0x4E, !GET_GAME_FLAG(GAME_FLAG_142) ? 1 : 0);
            break;

        case 36:
            if (!GET_GAME_FLAG(GAME_FLAG_85) || GET_GAME_FLAG(GAME_FLAG_109)) {
                EvDispControlModelEntry(disp_ctrl_list, 0x57, 0);
            }
            if (shCharacterGetSubCharacter(ITEM_X_COINPRISONER_CHARA_KIND, 0) == NULL && shCharacterGetSubCharacter(ITEM_X_COINPRISONER_CHARA_KIND, 1) != NULL) {
                shCharacter_Manage_Delete(NULL, ITEM_X_COINPRISONER_CHARA_KIND, 1);
            }
            break;
    }

    EvDispControlModelExec(disp_ctrl_list);
}


/* static */ int stg_apart_w1f_EvBgmControl(void) {
    if (GET_BIT(Sh2sys.main_status, 6) && DramaDemoNumber() == 18) return 4;
    return 0;
}


/* static */ void stg_apart_w1f_TrimColorFilter(void) {
    int ix; // r2
    float ddt; // r29
   
    switch (playing.brightness_level) {
        case 0:
            return;
        case 1:
            return;
        case 2:
            return;
        default:
        case 3:
            return;
        case 4:
            return;
        case 5:
            return;
        case 6:
            return;
        case 7:
            return;
    }
}
