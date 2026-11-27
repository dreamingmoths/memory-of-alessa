#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/playing_info.h"

#include "gs.h"
#include "sce/libgraph.h"
#include "mw/mw_stdarg.h"

#include "Chacter/sh2_battle_list.h"
#include "Chacter/player_result.h"

#include "Font/font.h"
#include "Font/dic.h"
#include "Event/event.h"
#include "Fog/spack.h"
#include "Multi_thr/filesys/fcread.h"
#include "data/daily.thu/data_menu_mc.h"
#include "Effect/screen_effect.h"

#pragma fast_fptosi on

#define TIME_MIN_SEC(_time) ((int) (_time) / 60) % 60, (int) (_time) % 60
#define TIME_HMS(_time) (int) (_time) / 3600, TIME_MIN_SEC(_time)

// game result
static u_short result_message[15] = { 1, 2, 6, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 }; // size: 0x1E, address: 0x37D1B0

#line 58
static void font_print(int num, int x, int y, int align) {
    fontPrintWord(fontGetMesAdr(msg_buffer, num), x, y, align, 0);
}

#line 63
static void font_printf(char* str, int x, int y, int align, ...) {
    char buf[256]; // r29+0x30
    char* argp; // r2
    va_start(argp, align);
    vsprintf(buf, str, argp);
    
    fontPrintWord(dicSetStr(buf), x, y, align, 0);
}

#line 73
static void clear_screen(void) {
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 4),
                   GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2), -MAX_INT - 1, 0);
    *spack.pos++ = SCE_GS_TEX0_1;
    *spack.pos++ = SCE_GS_SET_RGBAQ(0, 0, 0, 128, 0);
    *spack.pos++ = SCE_GS_SET_XYZ3(X_COORD(64), Y_COORD(-16), 0);
    *spack.pos++ = SCE_GS_SET_XYZ3(X_COORD(576), Y_COORD(496), 0);
    spkCloseGiftag();
}

#line 84
static void color1(void) {
    fontSetColor(FontColorGray);
}

#line 89
static void color2(void) {
    fontSetColor(FontColorTeal);
}

#line 99
void ResultMain(void) {
    int i, n, t; // r16, r17, r2
    u_short buf[11]; u_int temp_ret; // r29+48
    clear_screen();
    fontClear();
    switch (Sh2sys.step[SH2SYS_CONNECT]) {
        
        case 0:
            GameSavePreviousTotalRank();
            GameSaveSprayPower();
            if (playing.battle_level == SH2_BATTLE_LEVEL_BEGINNER) {
                
                sh2sys_set_1(7);
                return;
            }
            ScreenEffectFadeStart(3, 0.0f);
            
            DataLoadMessage(SH2_MES_FILE_RESULT);
            
            if ((playing.clear_end_kind & (1 << 4)) && 
                (playing.language == 0)             && 
                (shPadPress(0, PAD_KEY_0))          && 
                (shPadPress(0, PAD_KEY_1))          && 
                (shPadPress(0, PAD_KEY_6) < 96)     && 
                (shPadPress(0, PAD_KEY_7) > 160)    && 
                (shPadPress(0, PAD_KEY_4) > 160)    && 
                (shPadPress(0, PAD_KEY_5) > 160)    && 
                (shPadPress(0, 0xFFF0C /* ??? */) == 0)) {
                FcRead(&data_menu_mc_result_msg_extra_mes, msg_buffer);
            }
            
            sh2sys_step_3();
            return;
        
        case 1:
            if (fsSync(1, -1) >= 0) {
                ScreenEffectFadeStart(4, 1.0f);
                sh2sys_step_3();
            }
            return;
        
        case 3:
            if (ScreenEffectFadeCheck()) {
        
                
                
                
                sh2sys_set_1(7);
            }
            
            return;
    }
    
    fontSetColor(FontColorRed);
    font_print(0, 256, 32, 1);
    
    fontCrushOn();
    fontSetColor(FontColorContrastGray);
    for (i = 0; i < 15; i++) {
        font_print(result_message[i], 240, (i * 26) + 72, 3);
    }
    
    if (GameCalcRankBattleLevel() >= 5) {
        color2();
    } else {
        color1();
    }
    font_print(playing.battle_level + 2, 256, 72, 0);
    
    if (GameCalcRankRiddleLevel() >= 5) {
        color2();
    } else {
        color1();
    }
    font_print(playing.riddle_level + 3, 256, 98, 0);
    
    color1();
    n = playing.clear_end_kind;
    if (n & (1 << 4)) {
        color2();
        n = 11;
    } else if (n & (1 << 3)) {
        color2();
        n = 10;
    } else if (n & (1 << 2)) {
        n = 9;
    } else if (n & (1 << 1)) {
        n = 8;
    } else if (n & (1 << 0)) {
        n = 7;
    }
    if (n) font_print(n, 256, 124, 0);
    
    if (GameCalcRankEndingKind() >= 20) {
        color2();
    } else {
        color1();
    }
    if (n & (1 << 4)) {
        font_printf("\\h%d/4(+1)", 256, 150, 0, 
                    playing.clear_end_number - 1);
    } else {
        font_printf("\\h%d/4", 256, 150, 0, 
                    playing.clear_end_number);
    }
    
    if (GameCalcRankSaveCount() >= 5) {
        color2();
    } else {
        color1();
    }
    font_printf("\\h%d", 256, 176, 0, playing.savecount);
   
    if (GameCalcRankClearTime() >= 10) {
        color2();
    } else {
        color1();
    }
    t = shFloatToInt(playing.time);
    font_printf("\\h%dh %02dm %02ds", 256, 202, 0, TIME_HMS(t));
    
    
    color1();
    font_printf("\\h%.2fkm", 256, 228, 0, (playing.walk_distance / 500.0f) / 1000.0f);
    
    
    font_printf("\\h%.2fkm", 256, 254, 0, (playing.run_distance / 500.0f) / 1000.0f);
    
    
    if (GameCalcRankItemGet() >= 10) {
        color2();
    } else {
        color1();
    }
    if (playing.hidden_item_get) {
        font_printf("\\h%d%s(+%d)", 256, 280, 0, playing.item_get, GameCalcRankHiddenItemGet() >= 5 ? "\\c4" : "\\c0", playing.hidden_item_get);
    
    
    } else {
        font_printf("\\h%d", 256, 280, 0, playing.item_get);
    }
    
    if (GameCalcRankKillByShot() >= 15) {
        color2();
    } else {
        color1();
    }
    font_printf("\\h%d", 256, 306, 0, playing.kill_by_shot);
    
    if (GameCalcRankKillByFight() >= 15) {
        color2();
    } else {
        color1();
    }
    font_printf("\\h%d", 256, 332, 0, playing.kill_by_fight);
    
    if (GameCalcRankBoatClearTime() >= 5) {
        color2();
    } else {
        color1();
    }
    t = shFloatToInt(playing.boat_clear_time);
    if (3600 <= t) {
        font_printf("\\h%dh %02dm %02ds", 256, 358, 0, TIME_HMS(t));
    
    } else {
        font_printf("\\h%dm %02ds", 256, 358, 0, TIME_MIN_SEC(t));
    }
    
    
    color1();
    font_printf("\\h%.2fm/s", 256, 384, 0, playing.boat_max_speed / 500.0f);
    
    
    if (GameCalcRankJamesDamage() >= 5) {
        color2();
    } else {
        color1();
    }
    font_printf("\\h%d pt", 256, 410, 0, shFloatToInt(playing.jms_damage_total));
    
    
    fontSetColor(FontColorTeal);
    n = GameCalcRankTotal();
    if (n < 10) {
        for (i = 0; i < n; i++) {
            buf[i] = 312; // star
        }
        buf[i] = 0xffff;
        font_printf(buf, 256, 436, 0);
    } else {
        for (i = 0; i < n / 10; i++) {
            buf[i] = 312; // star
        }
        buf[i] = 0xffff;
        fontCrushOff();
        fontPrintWord((u_short*) &buf, 256, 432, 0, 0);
        fontCrushOn();
        if (n % 10) {
            for (i = 0; i < (n % 10); i++) {
                buf[i] = 312;
            }
            buf[i] = 0xffff;
            fontPrintWord((u_short*) &buf, 256, 458, 0, 0);
        }
    }
    fontCrushOff();
    d1cSend(spkDmaKick());
    if (shPadTrigger(0, key_config.enter | (1 << 2))) {
        ScreenEffectFadeStart(1, 1.0f);
        sh2sys_step_3();
    }
    return;
}

