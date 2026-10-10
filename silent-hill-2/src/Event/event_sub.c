#include "Event/event_sub.h"
#include "Event/event.h"
#include "Event/item.h"
#include "Event/picture.h"
#include "Event/stg_name.h"

#include "Chacter/m3_sc.h"
#include "Chacter/sh2_character_manage.h"
#include "Chacter/m3_play_event.h"

#include "Effect/screen_effect.h"

#include "Font/font.h"

#include "GFW/sh2_GsAllEnv.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "GFW/sh2gfw_viewclip.h"

#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/filesys/fcread.h"

#include "movie/movie_main.h"

#include "SH2_common/sh_vu0.h"

#include "sound/sh_sound.h"
#include "sound/sh_sd_call.h"

#include "gamemain.h"

// @todo: clean up
// @todo: migrate bss

static short item_to_chara[75] = {
    0,
    ITEM_X_DRINK_CHARA_KIND,
    ITEM_X_FIRSTAID_CHARA_KIND,
    ITEM_X_AMPLE_CHARA_KIND,
    ITEM_X_HANDGUN_CHARA_KIND,
    ITEM_X_HANDBUL_CHARA_KIND,
    ITEM_X_WP_SHOTGUN_CHARA_KIND,
    ITEM_X_SHOTBUL_CHARA_KIND,
    ITEM_X_WP_RIFLGUN_CHARA_KIND,
    ITEM_X_RIFLEBUL_CHARA_KIND,
    ITEM_X_WP_SP_CHARA_KIND,
    ITEM_X_KAKUZAI_CHARA_KIND,
    ITEM_X_WP_PIPE_CHARA_KIND,
    0x50C,
    ITEM_X_WP_CSAW_CHARA_KIND,
    ITEM_X_JLIGHT_CHARA_KIND,
    ITEM_X_RADIO_CHARA_KIND,
    0x70C,
    ITEM_X_LETTERM_CHARA_KIND,
    0,
    ITEM_X_VIDEO_CHARA_KIND,
    0,
    0,
    ITEM_X_KEYGATE_CHARA_KIND,
    ITEM_X_KEY202_CHARA_KIND,
    0x41F,
    ITEM_X_KEYEMERG_CHARA_KIND,
    ITEM_X_KEYCOURT_CHARA_KIND,
    ITEM_X_KEYLYNE_CHARA_KIND,
    ITEM_X_KEYNORTH_CHARA_KIND,
    0,
    ITEM_X_KEYROOF_CHARA_KIND,
    ITEM_X_KEYPURPLE_CHARA_KIND,
    ITEM_X_KEYRAPIS_CHARA_KIND,
    ITEM_X_KEYELEVATOR_CHARA_KIND,
    ITEM_X_KEYBASE_CHARA_KIND,
    ITEM_X_KEYHOS_CHARA_KIND,
    ITEM_X_KEYBRONZE_CHARA_KIND,
    ITEM_X_KEYSPIRAL_CHARA_KIND,
    ITEM_X_KEYFALSE_CHARA_KIND,
    ITEM_X_KEY312_CHARA_KIND,
    0,
    ITEM_X_KEYEMPLOY_CHARA_KIND,
    ITEM_X_KEYBAR_CHARA_KIND,
    ITEM_X_KEYFISH_CHARA_KIND,
    ITEM_X_KEY3F_CHARA_KIND,
    ITEM_X_JUICE_CHARA_KIND,
    ITEM_X_COINSNAKE_CHARA_KIND,
    ITEM_X_COINELDER_CHARA_KIND,
    ITEM_X_COINPRISONER_CHARA_KIND,
    ITEM_X_HAIR_CHARA_KIND,
    ITEM_X_NEEDLE_CHARA_KIND,
    ITEM_X_BATTERY_CHARA_KIND,
    ITEM_X_RINGCOPPER_CHARA_KIND,
    ITEM_X_RINGLEAD_CHARA_KIND,
    ITEM_X_SPANNER_CHARA_KIND,
    ITEM_X_PLATE_KICK_CHARA_KIND,
    ITEM_X_PLATE_PIG_CHARA_KIND,
    ITEM_X_PLATE_FEMALE_CHARA_KIND,
    ITEM_X_HORSE_CHARA_KIND,
    ITEM_X_LIGHTER_CHARA_KIND,
    ITEM_X_WAXDOLL_CHARA_KIND,
    ITEM_X_PLIER_CHARA_KIND,
    ITEM_X_THINNER_CHARA_KIND,
    ITEM_X_MERMAID_CHARA_KIND,
    ITEM_X_CINDERELLA_CHARA_KIND,
    ITEM_X_SNOW_CHARA_KIND,
    ITEM_X_CANOPEN_CHARA_KIND,
    ITEM_X_LIGHTBULB_CHARA_KIND,
    0,
    0,
    ITEM_X_LOSTMEMORY_CHARA_KIND,
    ITEM_X_REDRELIG_CHARA_KIND,
    ITEM_X_OIL_CHARA_KIND,
    ITEM_X_CUP_CHARA_KIND
};

static int ItemUseSeTiming(int kind, int boa);

int EvSubMessage(int msg) {
    switch (ev_s_step) { 
        case 0:
            fontMessageNum(msg_buffer, msg);
            ev_s_step++;
            break;
        case 1:
            if ((fontGetStatus() != -1) || (ev_cancel != 0)) {
                if (ev_cancel != 0) {
                    ev_prog_flag_set = 0;
                }
                fontClear();
                ev_s_step++;
            }
            break;
        case 2:
            return 1;           
    }
    return 0;
}

int EvSubQuestion(int msg)  {
    switch (ev_s_step) {
        case 0:
            fontMessageNum(msg_buffer, msg);
            ev_s_step++;
            break;    
        case 1:
            if (fontGetStatus() != -1) {
                fontClear();
                ev_s_step++;
            }
            break;
        case 2:
            return 1;
    }
    return 0;
}

int EvSubItemUse0(int kind, int message, int se, int stereo, float* pos, int xxx) {
    switch (ev_s_step) {
        case 0:
            if (xxx != 0) {
                SCNowPlayableEventSwitch(sh2jms.player, 1);
            }
            ItemUse(kind);
            fontMessageNum(msg_buffer, message);
            if ((se != 0) && (ItemUseSeTiming(kind, 0) != 0)) {
                if (pos != 0) {

                    SeCallPos(se, 1.0f, pos, 0);
                } else {
                    SeCall(se, 1.0f, stereo);
                }
            }
            ev_s_step++;
            break;
        case 1:
            if (fontGetStatus() == -2) {
                fontClear();
                if ((se != 0) && (ItemUseSeTiming(kind, 1))) {
                    if (pos != 0) {
                        SeCallPos(se, 1.0f, pos, 0);
                    } else {
                        SeCall(se, 1.0f, stereo);
                    }
                }
                ev_s_step++;
            }
            break;
        case 2:
            if (xxx != 0) {
                SCNowPlayableEventSwitch(sh2jms.player, 0);
            }
            return 1;
    }
    return 0;
}

static int ItemUseSeTiming(int kind, int boa) {
    switch (kind) {
        case 0x38:
        case 0x39:
        case 0x3A:
            if (boa == 0) {
                return 0;
            }
            break;
        default:
            if (boa != 0) {
                return 0;
            }
            break;
    }
    return 1;
}

#ifdef NON_MATCHING
int EvSubItemGet(int kind, int message)  {
    switch (ev_s_step) {
        case 0:
            fontMessageNum(msg_buffer, message);
            ev_s_step++;
            break;
        case 1:
            if (fontGetStatus() == -2) {
                ItemGet(kind);
                shCharacter_Manage_Delete(0, item_to_chara[kind], 0);
                fontClear();
                ev_s_step++;
            }
            break;
        case 2:
            return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/event_sub", EvSubItemGet)
#endif

int EvSubItemGetAndAnim(int kind, int message) {
    SubCharacter* scp; 
    
    switch (ev_s_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            scp = shCharacterGetSubCharacter(item_to_chara[kind], 0);
            if (scp && (sh2jms.player->pos.y - scp->pos.y < 100.0f)) {
                PlayerEventAnimeSet(0x4E21);
                EV_SUB_STEP(9);
            } else {
                PlayerEventAnimeSet(0x65);
                EV_SUB_STEP(10);
            }
            break;
    
        case 9:
            if (ev_cancel) {
                ev_prog_flag_set = 0;
                EV_SUB_STEP(11);
            } else if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                EV_SUB_STEP(10);
            }
            break;
        case 10:
            fontMessageNum(msg_buffer, message);
            SeCall(11041, 1.0f, 0);
            EV_SUB_STEP(3);
            break;
        case 3:
            if (fontGetStatus() == -2 || ev_cancel) {
                ItemGet(kind);
                fontClear();
                scp = shCharacterGetSubCharacter(item_to_chara[kind], 0);
                if (scp && (sh2jms.player->pos.y - scp->pos.y < 100.0f)) {
                    shCharacterAnimeRestart(sh2jms.player);
                    EV_SUB_STEP(8);
                } else {
                    EV_SUB_STEP(11);
                }
                if (scp) {
                    shCharacter_Manage_Delete(scp, 0, 0);
                }
            }
            break;
        case 8:
            if (shCharacterAnimeIsEnd(sh2jms.player) || ev_cancel) {
                EV_SUB_STEP(11);
            }
            break;
        case 11:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return 1;
        }
    return 0;
}

int EvSubFileLoadAndFadeOut(int unk, fsFileIndex* file_0, fsFileIndex* file_1) {
    ASSERT_ON_LINE(file_0 || !file_1, 332);
    
    if (ev_s_step == 0) {
        if (file_0) {
            FcRead(file_0, get_gp_data_buf_addr());
            layer_adr = get_gp_data_buf_addr() + ((FcGetFileSize(file_0) + 0x7FF) & ~0x7FF);
        }
        if (file_1) FcRead(file_1, layer_adr);        
        ScreenEffectFadeStart(1, 0);
        ev_s_step = 3;
    }
    
    
    if ((fsSync(1, -1) >= 0) && (ScreenEffectFadeCheck())) return 1;    
    return 0;
}

void EvSubPictureDisplayAndFadeIn(float timer) {
    if (ev_s_step == 0) {
        ScreenEffectFadeStart(4, timer);
        ev_s_step = 3;
    }
    EvSubPictureStart();
    EvSubPictureDisplayOnly();
    EvSubPictureEnd();
    ScreenEffectFadeCheck();
}

int EvSubPictureDisplayOnly(void) {
    PicDraw_Data pic;
    
    PictureLoadImage((sh2gfw_AREA_HEAD*)get_gp_data_buf_addr(), 0, -1, -1);
    
    shQzero(&pic, sizeof(PicDraw_Data));
    
    picture_set_ap(&pic, get_gp_data_buf_addr());
    pic.otp = 1;
    PictureDraw(&pic);
    
    return 1;
}

void EvSubPictureDisplayAndFadeOut(float timer) {
    if (ev_s_step == 0) {
        ScreenEffectFadeStart(1, timer);
        ev_s_step = 3;
    }
    EvSubPictureStart();
    EvSubPictureDisplayOnly();
    EvSubPictureEnd();
    ScreenEffectFadeCheck();
}

int EvSubPictureDisplay(fsFileIndex* file, int msg) {
    switch (ev_s_step) {
        case 0:
            FcRead(file, get_gp_data_buf_addr());
            ScreenEffectFadeStart(1, 0);
            EvSubPictureInit();
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            ev_s_step = 4;
            break;
    
        case 4:
            if ((fsSync(1, -1) >= 0) && (ScreenEffectFadeCheck())) {
                ScreenEffectFadeStart(4, 0);
                ev_s_step = 7;
            }
            break;
        case 7:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) {
                ev_s_step = 2;
            }
            break;
        case 2:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) {
                fontMessageNum(msg_buffer, msg);
                ev_s_step = 3;
            }
            break;
        case 3:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (fontGetStatus() == -2) {
                fontClear();
                ScreenEffectFadeStart(2, 0);
                ev_s_step = 6;
            }
            break;
        case 6:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) {
                ev_s_step = 11;
            }
            break;
        case 11:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            ScreenEffectFadeStart(4, 0);
            return 1;
        }

    return 0;
}

int EvSubMapGet(fsFileIndex* file, int msg) {
    EvSubPictureDisplay(file, msg);
}

void EvSubPictureLayer(int x0, int y0, int x1, int y1, int alpha) {
    PicDraw_Data pic;
    
    PictureLoadImage((sh2gfw_AREA_HEAD*)layer_adr, 2, -1, -1);    
    
    shQzero(&pic, sizeof(PicDraw_Data));
    
    picture_set_ap(&pic, (sh2gfw_AREA_HEAD*)layer_adr);
    pic.otp = 3;
    picture_set_xy(&pic, x0, y0, x1, y1);
    picture_set_alpha(&pic, alpha);
    PictureDraw(&pic);
}

void EvSubPictureFilter(void) {
    ev_filter_on = 1;
}

void EvSubPictureInit(void) {
    ev_filter_on = 0;
    ev_filter = 0.0f;
}

void EvSubPictureStart(void) {
    sh2gfw_Black_Clear();
    Sh2sys.main_status |=  1;
}

void EvSubPictureEnd(void) { // @todo: add inlines
    PicDraw_Data pic;

    if (ev_filter_on != 0) {
        ev_filter += shGetDT() * 4.0f;
        if (ev_filter > 1.0f) ev_filter = 1.0f;
    } else {
        ev_filter -= shGetDT() * 4.0f;
        if (ev_filter < 0.0f) ev_filter = 0.0f;
    }
    ev_filter_on = 0;
    
    if (ev_filter > 0.0f)  {
        shQzero(&pic, sizeof(PicDraw_Data));
        pic.r = 0; pic.g = 0; pic.b = 0; pic.status |= 0x10;
        
        pic.a = 0x80; pic.alpha_a = 2; pic.alpha_b = 1; pic.alpha_c = 2; pic.alpha_d = 1; pic.alpha_fix = FTOI(64.0f * ev_filter); pic.status |= 0x20;
        pic.otp = 8;
        PictureDraw(&pic);
    }
    
    d1cSend(spkDmaKick());
}

void EvSubPictureCursor(int color) {
    PicDraw_Data pic;
    int px; int py; 
    float anx; float any; 
    u_char lsx; u_char lsy; 
    
    lsx = shPadPress(0, PAD_KEY_6); // @note: maybe add defines for these values? 
    if (lsx >= 0x9B) 
        anx = (lsx - 0x9B) / 100.0f;
    else if (lsx <= 0x64)
        anx = (lsx - 0x64) / 100.0f;
    else anx = 0.0f;
    lsy = shPadPress(0, PAD_KEY_7);
    if (lsy >= 0x9B) 
        any = (lsy - 0x9B) / 100.0f;
    else if (lsy <= 0x64) 
        any = (lsy - 0x64) / 100.0f;
    else any = 0.0f;       
    if ((anx != 0.0f) || (any != 0.0f)) {
        ev_cursor_x += anx * (153.6f * shGetDT());
        ev_cursor_y += any * (192.0f * shGetDT());
    } else {
        if (shPadPress(0, PAD_KEY_DPAD_RIGHT))     ev_cursor_x += 153.6f * shGetDT();        
        if (shPadPress(0, PAD_KEY_DPAD_LEFT))      ev_cursor_x -= 153.6f * shGetDT();        
        if (shPadPress(0, PAD_KEY_DPAD_DOWN))      ev_cursor_y += 192.0f * shGetDT();        
        if (shPadPress(0, PAD_KEY_DPAD_UP))        ev_cursor_y -= 192.0f * shGetDT();
        
    }
    ev_cursor_x = float_max(-256.0f, float_min(256.0f, ev_cursor_x));
    ev_cursor_y = float_max(-192.0f, float_min(192.0f, ev_cursor_y));

    PictureLoadImage((sh2gfw_AREA_HEAD *)&cursor_adr, 8, -1, -1);
    
    shQzero(&pic, sizeof(PicDraw_Data));
    
    picture_set_ap(&pic, cursor_adr);
    pic.otp = 9;
    picture_set_alpha(&pic, 0x80);    
    px = FTOI4(ev_cursor_x - 5.0f);
    py = FTOI4(ev_cursor_y - 6.0f);
    pic.x0 = px; pic.y0 = py; pic.x1 = px + 384; pic.y1 = py + 512; pic.status |= 2;
    
    pic.us0 = 1536; pic.vt0 = 1024; pic.us1 = 2288; pic.vt1 = 2032; pic.status |= 4;    
    switch (color) { // wtf T.T
        case 1: do { pic.r = 0x60; pic.g = 0x60; pic.b = 0x80; pic.status |= 0x10; } while(0); break;                      
        case 2: do { pic.r = 0x80; pic.g = 0x60; pic.b = 0x60; pic.status |= 0x10; } while(0); break;
        case 4: do { pic.r = 0x60; pic.g = 0x80; pic.b = 0x60; pic.status |= 0x10; } while(0); break;
    }
    PictureDraw(&pic);
}

void EvDispControlModelEntry(int* list, int room, int no) {
    int temp; // not present in DWARF
    int map_id;
    temp = stage->glb_crd << 16; temp |= room;
    
    for (; (map_id = *list, map_id != 0); list += 2) { if (map_id == temp) break; }
    if (map_id == 0) {
        list[1] = 0;
        list[2] = 0;
    }
    *list = temp;
    if (no >= 0) { list[1] |= 1 << no; }
}

void EvDispControlModelExec(int* list) {
    switch (BgIsOut(0)) {
        default:
            sh2gfw_Init_DispOnOffObj();
            for (; *list != 0; list = list + 2) {
                sh2gfw_FastSet_DispOnOffObj(*list,list[1]);
            }
            break;
        case 0:
            for (; *list != 0; list = list + 2) {
                sh2gfw_Set_DispOnOffObj(*list,list[1]);
            }
    }
  return;
}

void EvSubMovieReady(fsFileIndex* file, DramaDemo_MessageTime* msg_time, int msg_no)  {
    if (GET_BIT(Sh2sys.main_status, 6)) {
        demo_status |= 0x200;
        if (demo_frame < total_demo_frame - 30.0f) return;        
        if ((shSdStat() & 0xF0) && (shSdStat() & 0xF0) != 80) return;
    }
    if (MovieCheckSleep()) {
        Sh2sys.soft_reset = 0;
        MoviePreSet(file);
        movieSetSubTitleData(msg_buffer, msg_time, msg_no);
    }
}

int EvSubMovieStart(int demo) {
    int movie = MovieWaitReady();
    
    if ((movie != 0) && (demo != 0) && ((shGs_AllEnv.loop3 % 3U) == 1)) {
        sh2gfw_Set_PauseRetain();
        Sh2sys.step[SH2SYS_PLAYABLE_MAIN] = 14;
        Sh2sys.step[SH2SYS_CONNECT] = 0;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
        return 1;
    }
    return 0;
}

void EvSubMovieEnd(void) {
    Sh2sys.soft_reset = 1;
    sh2gfw_Reset_FilterCommand();
}
