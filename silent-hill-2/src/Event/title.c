#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh_vu0.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"
#include "Multi_thr/dma/dma1cmd.h"

#include "jump_menu.h"
#include "connect.h"
#include "gamemain.h"
#include "sh2gfw_drawloop_main.h"

#include "Chacter/sh2_battle_list.h"
#include "Effect/screen_effect.h"
#include "MC/mc.h"
#include "Fog/spack.h"
#include "data/fs_structs.h"

#include "sound/sh_sd_call.h"
#include "sound/sh_sound.h"

#include "Event/title.h"
#include "Event/event.h"
#include "Event/item.h"
#include "Event/picture.h"
#include "Event/stg_overlay.h"

static void titleChangeMainMenu(void);
static void titleDrawMainMenu(void);
static void titleDrawTitle(void);
static int titleGetCursorFromBattleLevel(u_char battle_level);
static int titleCheckPad(void);
static void titleBacktoMainMenuFromLevelMenu(void);
static void titleDrawSubMenu(int sel);
static int titleGetCursorFromRiddleLevel(u_char riddle_level);
static u_char titleGetBattleLevelFromCursor(int cur);
static u_char titleGetRiddleLevelFromCursor(int cur);
static void titleRenewChangeColorManagement(float* timer, float cycle, int repeat);
static void titleChangeColor(int* rgba, int* start_rgba, int* end_rgba, float timer, float cycle_time, float cycle_sin);
static int draw_opd_wowk_main(void);
static void titleInit(void);
static void titleFadeIn(void);
static void titleCreateMainMenu(void);
static void titleMainSelect(void);
static void titleBattleSelect(void);
static void titleRiddleSelect(void);
static void titleFadeOutNewGame(void);
static void titleFadeOut(void);
static void titleExit(void);
static void titleDrawSprite(short x, short y, short id);
static short titleGetCursorXPosBattle(int cur);
static void titleGetMenuEfctPosBattle(short* x_pos, short* w, int cur);
static short titleGetCursorXPosRiddle(int cur);
static void titleGetMenuEfctPosRiddle(short* x_pos, short* w, int cur);
static void titleChangeSpriteColor2(short id);
static void titleChangeCursorSpriteColor(void);
static void opd_work_init(void);

TitleSprWork TitleSpr[17] = {
    {
        /* .u0 = */     0,
        /* .v0 = */     0,
        /* .u1 = */     512,
        /* .v1 = */     96,
        /* .w = */      512,
        /* .h = */      84,
        /* .rgba = */   {128, 128, 128, 0}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     96,
        /* .u1 = */     192,
        /* .v1 = */     128,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     128,
        /* .u1 = */     192,
        /* .v1 = */     160,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     160,
        /* .u1 = */     192,
        /* .v1 = */     192,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     192,
        /* .u1 = */     192,
        /* .v1 = */     224,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     96,
        /* .u1 = */     384,
        /* .v1 = */     128,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     256,
        /* .u1 = */     384,
        /* .v1 = */     288,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     288,
        /* .u1 = */     384,
        /* .v1 = */     320,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     320,
        /* .u1 = */     384,
        /* .v1 = */     352,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     352,
        /* .u1 = */     384,
        /* .v1 = */     384,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     384,
        /* .u1 = */     384,
        /* .v1 = */     416,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     192,
        /* .v0 = */     416,
        /* .u1 = */     384,
        /* .v1 = */     448,
        /* .w = */      192,
        /* .h = */      29,
        /* .rgba = */   {128, 128, 128, 0}
    },
    {
        /* .u0 = */     480,
        /* .v0 = */     96,
        /* .u1 = */     512,
        /* .v1 = */     128,
        /* .w = */      32,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     224,
        /* .u1 = */     192,
        /* .v1 = */     256,
        /* .w = */      198,
        /* .h = */      33,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     256,
        /* .u1 = */     192,
        /* .v1 = */     288,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     288,
        /* .u1 = */     192,
        /* .v1 = */     320,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    },
    {
        /* .u0 = */     0,
        /* .v0 = */     320,
        /* .u1 = */     192,
        /* .v1 = */     352,
        /* .w = */      192,
        /* .h = */      32,
        /* .rgba = */   {128, 128, 128, 128}
    }
};

TitleSprChgColorWork TitleSprChgColor[17] = {
    {
        /* .start_rgba = */            {255, 255, 255, 128},
        /* .end_rgba = */              {38, 38, 38, 8},
        /* .cycle = */                 7.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {32, 32, 32, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 1.5,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {70, 70, 70, 38},
        /* .end_rgba = */              {255, 255, 255, 128},
        /* .cycle = */                 3.5999999046325684,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {96, 96, 255, 128},
        /* .end_rgba = */              {32, 32, 160, 128},
        /* .cycle = */                 2.4000000953674316,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    },
    {
        /* .start_rgba = */            {128, 128, 128, 128},
        /* .end_rgba = */              {128, 128, 128, 128},
        /* .cycle = */                 0.0f,
        /* .timer = */                 0.0f
    }
};

TitlePointList TitleUSPStartPointList[3] = {
    {
        /* .pos_x = */                 -19606.599609375f,
        /* .pos_y = */                 18.829999923706055f,
        /* .pos_z = */                 20429.55078125f,
        /* .rot = */                   0.0f,
        /* .stg = */                   Stg_toilet,
        /* .jump_nemu_id = */          16
    },
    {
        /* .pos_x = */                 -20150.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 21200.0f,
        /* .rot = */                   TO_RAD(180),
        /* .stg = */                   Stg_apart_e2f,
        /* .jump_nemu_id = */          11
    },
    {
        /* .pos_x = */                 -60000.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 63600.0f,
        /* .rot = */                   TO_RAD(180),
        /* .stg = */                   Stg_prison_n,
        /* .jump_nemu_id = */          12
    }
};

TitlePointList TitleJPStartPointList[5] = {
    {
        /* .pos_x = */                 -19606.599609375f,
        /* .pos_y = */                 18.829999923706055f,
        /* .pos_z = */                 20429.55078125f,
        /* .rot = */                   0.0f,
        /* .stg = */                   Stg_toilet,
        /* .jump_nemu_id = */          16
    },
    {
        /* .pos_x = */                 -100000.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 -22000.0f,
        /* .rot = */                   0.0f,
        /* .stg = */                   Stg_apart_stair,
        /* .jump_nemu_id = */          7
    },
    {
        /* .pos_x = */                 -20000.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 -16800.0f,
        /* .rot = */                   0.0f,
        /* .stg = */                   Stg_hospital_1f_f,
        /* .jump_nemu_id = */          8
    },
    {
        /* .pos_x = */                 -20800.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 21788.5,
        /* .rot = */                   0.0f,
        /* .stg = */                   Stg_society,
        /* .jump_nemu_id = */          9
    },
    {
        /* .pos_x = */                 -60400.0f,
        /* .pos_y = */                 0.0f,
        /* .pos_z = */                 16000.0f,
        /* .rot = */                   TO_RAD(-90),
        /* .stg = */                   Stg_hotel_1f_f,
        /* .jump_nemu_id = */          10
    }
};


static int title_test_mode; // size: 0x4, address: 0x116D788
int title_after_data_set;
TitleDataWork TitleData; // size: 0x94, address: 0x116D950

extern int title_start_point;                      // size: 0x4, address: 0x116D938
extern int jump_menu_select;                       // size: 0x4, address: 0x11B6990
extern float analog_data;                          // size: 0x4, address: 0x116D930





/* not from here */

extern fsFileIndex data_pic_etc_start01_tex[1];    // size: 0x8, address: 0x3A1C78
extern fsFileIndex data_pic_etc_start00_tex[1];    // size: 0x8, address: 0x3A1C70
extern fsFileIndex data_pic_etc_comingsoon_tex[1]; // size: 0x8, address: 0x3A1C30
extern fsFileIndex data_pic_etc_gameover1_tex[1];  // size: 0x8, address: 0x3A1C38

#define SH2_TITLE_DATA_MODE_5 5

int TitleMain(void) {
    static void (*g0_step_func[8])() = {
        titleInit,
        titleFadeIn,
        titleMainSelect,
        titleBattleSelect,
        titleRiddleSelect,
        titleFadeOutNewGame,
        titleFadeOut,
        titleExit,
    }; // @ 0x0033BEA0
    spkResetOT();
    fontClear();
    g0_step_func[Sh2sys.step[2]]();
    d1cSend(spkDmaKick());
    if (TitleData.mode == SH2_TITLE_DATA_MODE_5) {
        all_Frame_Buffer_Clear();
    }
    return TitleData.mode;
}

void titleSetDataStartPoint(void) {
    int i; // r16

    if ((title_test_mode != 0) && (jump_menu_select == 0) && (title_after_data_set == 0)) {
        title_after_data_set = 1;
        ItemGet(17);
        ItemGet(18);
        item.light_switch = 1;
        if (title_test_mode == 2) {
            switch (title_start_point) { /* switch 1; irregular */
                case 1:                  /* switch 1 */
                    ItemGet(4);
                    for (i = 0; i < 3; i++) {
                        ItemGet(5);
                    }
                    ItemGet(11);
                    for (i = 0; i < 5; i++) {
                        ItemGet(1);
                    }
                    for (i = 0; i < 1; i++) {
                        ItemGet(2);
                    }
                    ItemGet(16);
                    item.equip = 4;
                    game_flag.flag[0] |= 33554432;
                    game_flag.flag[2] |= 4;
                    game_flag.flag[1] |= 8;
                    game_flag.flag[1] |= 256;
                    game_flag.flag[1] |= 512;
                    game_flag.flag[1] |= 2048;
                    game_flag.flag[1] |= 131072;
                    game_flag.flag[2] |= 8;
                    playing.riddle_level = 0;
                    return;
                case 2: /* switch 1 */
                    ItemGet(4);
                    for (i = 0; i < 3; i++) {
                        ItemGet(5);
                    }
                    ItemGet(6);
                    for (i = 0; i < 1; i++) {
                        ItemGet(7);
                    }
                    ItemGet(11);
                    ItemGet(12);
                    for (i = 0; i < 8; i++) {
                        ItemGet(1);
                    }
                    for (i = 0; i < 2; i++) {
                        ItemGet(2);
                    }
                    ItemGet(15);
                    ItemGet(16);
                    item.equip = 4;
                    game_flag.flag[0] |= 268435456;
                    game_flag.flag[1] |= 8;
                    playing.riddle_level = 0;
                    return;
            }
        } else {
            switch (title_start_point) { /* switch 2; irregular */
                case 1:                  /* switch 2 */
                    ItemGet(11);
                    ItemGet(16);
                    for (i = 0; i < 16; i++) {
                        ItemGet(1);
                    }
                    item.equip = 11;
                    return;
                case 2: /* switch 2 */
                    game_flag.flag[0] |= 32768;
                    ItemGet(11);
                    ItemGet(4);
                    for (i = 0; i < 9; i++) {
                        ItemGet(5);
                    }
                    ItemGet(12);
                    ItemGet(16);
                    ItemGet(15);
                    for (i = 0; i < 16; i++) {
                        ItemGet(1);
                    }
                    item.equip = 4;
                    return;
                case 3: /* switch 2 */
                    ItemGet(11);
                    ItemGet(4);
                    for (i = 0; i < 9; i++) {
                        ItemGet(5);
                    }
                    ItemGet(6);
                    for (i = 0; i < 9; i++) {
                        ItemGet(7);
                    }
                    ItemGet(12);
                    ItemGet(16);
                    ItemGet(15);
                    for (i = 0; i < 16; i++) {
                        ItemGet(1);
                    }
                    item.equip = 4;
                    return;
                case 4: /* switch 2 */
                    ItemGet(4);
                    for (i = 0; i < 9; i++) {
                        ItemGet(5);
                    }
                    ItemGet(6);
                    for (i = 0; i < 9; i++) {
                        ItemGet(7);
                    }
                    ItemGet(8);
                    for (i = 0; i < 9; i++) {
                        ItemGet(9);
                    }
                    ItemGet(10);
                    ItemGet(11);
                    ItemGet(12);
                    ItemGet(13);
                    for (i = 0; i < 16; i++) {
                        ItemGet(1);
                    }
                    ItemGet(15);
                    ItemGet(16);
                    item.equip = 4;
                    break;
            }
        }
    }
}

static void titleInit(void) {
    static int fid;       // @ 18274600
    static int wait_loop; // @ 18274592
    int i;                // r5

    switch (Sh2sys.step[3]) {
        case 0:
            TitleData.memcard = -1;
            TitleData.mode    = 0;
            TitleData.sel     = 0;
            TitleData.alpha   = 255;
            TitleData.alphar  = 0.0f;
            TitleData.timer   = 60.0f;
            for (i = 0; i < 10; i++) {
                TitleData.menu[i] = -1;
            }
            TitleData.pload0     = get_gp_data_buf_addr();
            TitleData.pload1     = get_gp_data_buf_addr() + 524288;
            playing.battle_level = 2;
            playing.riddle_level = 1;
            ScreenEffectInit();
            ScreenEffectFadeStart(3, 0.0f);
            fid       = FcRead(data_pic_etc_start00_tex, TitleData.pload0);
            wait_loop = 0;
            mcStepInit();
            analog_data = 0.0f;
            sh2sys_step_3();
            return;

        case 1: /* switch 1 */
            wait_loop += 1;
            switch (fsSync(1, fid)) { /* switch 2; irregular */
                case 1:               /* switch 2 */
                    DEBUG_LOG_ON_LINE(642, "title.tex: read finished(%d.%02d)", (wait_loop / 60), ((wait_loop % 60) * 100) / 60);
                    sh2sys_step_3();
                    break;
                case 0: /* switch 2 */
                    DEBUG_LOG_ON_LINE(647, "!!! illegal fid=%d", fid);
                    break;
                case -1: /* switch 2 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(651, "title.tex: now reading(%d.)...", (wait_loop / 60));
                        break;
                    }
                    break;
                case -2: /* switch 2 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(656, "title.tex: now waiting(%d.)...", (wait_loop / 60));
                        return;
                    }
                    break;
                default: /* switch 2 */
                    DEBUG_LOG_ON_LINE(660, "illegal return value");
                    break;
            }
            break;

        case 2: /* switch 1 */
            fid       = FcRead(data_pic_etc_start01_tex, TitleData.pload1);
            wait_loop = 0;
            sh2sys_step_3();
            return;

        case 3: /* switch 1 */
            titleChangeMainMenu();
            wait_loop += 1;
            switch (fsSync(1, fid)) { /* switch 3; irregular */
                case 1:               /* switch 3 */
                    DEBUG_LOG_ON_LINE(681, "title.tex: read finished(%d.%02d)", (wait_loop / 60), (((wait_loop % 60) * 100) / 60));
                    sh2sys_step_2();
                    return;
                case 0: /* switch 3 */
                    DEBUG_LOG_ON_LINE(686, "!!! illegal fid=%d", fid);
                    return;
                case -1: /* switch 3 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(690, "title.tex: now reading(%d.)...", (wait_loop / 60));
                        return;
                    }
                    break;
                case -2: /* switch 3 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(695, "title.tex: now waiting(%d.)...", (wait_loop / 60));
                        return;
                    }
                    break;
                default: /* switch 3 */
                    DEBUG_LOG_ON_LINE(699, "illegal return value");
                    break;
            }
            break;
    }
}

static void titleFadeIn(void) {
    TitleSprChgColor->timer    = TitleSprChgColor->cycle;
    TitleSprChgColor[11].timer = 0;
    switch (Sh2sys.step[3]) {
        case 0:
            titleChangeMainMenu();
            ScreenEffectFadeStart(4, 2.0f);
            titleDrawTitle();
            titleDrawMainMenu();
            sh2sys_step_3();
            break;

        default:
            titleChangeMainMenu();
            titleDrawTitle();
            titleDrawMainMenu();
            if (ScreenEffectFadeCheck() != 0) {
                mc.status |= 8;
                sh2sys_set_2(2);
                return;
            }
            if (shPadTrigger(0, key_config.cancel) != 0) {
                ScreenEffectFadeStop();
                mc.status |= 8;
                sh2sys_set_2(2);
            }
    }
}

static void titleChangeMainMenu(void) {
    int card; // r2
    if (title_test_mode == 2) {
        titleCreateMainMenu();
        return;
    }
    card = mcStartCheck2();
    if (card != TitleData.memcard) {
        TitleData.memcard = card;
        titleCreateMainMenu();
    }
}

static void titleCreateMainMenu(void) {
    if (title_test_mode == 2) {
        TitleData.menu[0] = -1;
        TitleData.menu[1] = 3;
        TitleData.menu[2] = 14;
        TitleData.menu[3] = 13;
        TitleData.menu[4] = -1;
        TitleData.menu[5] = -1;
        if (TitleData.sel == 0) {
            TitleData.sel = 1;
        }
    } else if (title_test_mode == 1) {
        if (TitleData.memcard == 0) {
            if (TitleData.sel != 8) {
                TitleData.sel = 3;
            }
            TitleData.menu[1] = -1;
            TitleData.menu[2] = -1;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 14;
            TitleData.menu[5] = 16;
            TitleData.menu[6] = 13;
            TitleData.menu[7] = 15;
            TitleData.menu[8] = 4;
            TitleData.menu[9] = -1;
            return;
        } else if (TitleData.memcard == 1) {
            TitleData.sel     = 2;
            TitleData.menu[1] = 1;
            TitleData.menu[2] = 2;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 14;
            TitleData.menu[5] = 16;
            TitleData.menu[6] = 13;
            TitleData.menu[7] = 15;
            TitleData.menu[8] = 4;
            TitleData.menu[9] = -1;
            return;
        } else if (TitleData.memcard == 2) {
            TitleData.sel     = 2;
            TitleData.menu[1] = -1;
            TitleData.menu[2] = 2;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 14;
            TitleData.menu[5] = 16;
            TitleData.menu[6] = 13;
            TitleData.menu[7] = 15;
            TitleData.menu[8] = 4;
            TitleData.menu[9] = -1;
            return;
        } else {
            TitleData.sel     = 2;
            TitleData.menu[1] = -1;
            TitleData.menu[2] = 1;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 14;
            TitleData.menu[5] = 16;
            TitleData.menu[6] = 13;
            TitleData.menu[7] = 15;
            TitleData.menu[8] = 4;
            TitleData.menu[9] = -1;
            return;
        }
    } else {
        if (TitleData.memcard == 0) {
            if (TitleData.sel != 4) {
                TitleData.sel = 3;
            }
            TitleData.menu[1] = -1;
            TitleData.menu[2] = -1;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 4;
            return;
        } else if (TitleData.memcard == 1) {
            TitleData.sel     = 2;
            TitleData.menu[1] = 1;
            TitleData.menu[2] = 2;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 4;
            return;
        } else if (TitleData.memcard == 2) {
            TitleData.sel     = 2;
            TitleData.menu[1] = -1;
            TitleData.menu[2] = 2;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 4;
            return;
        } else {
            TitleData.sel     = 2;
            TitleData.menu[1] = -1;
            TitleData.menu[2] = 1;
            TitleData.menu[3] = 3;
            TitleData.menu[4] = 4;
            return;
        }
    }
}

static void titleMainSelect(void) {
    int pad_ret;           // r2
    int select_game_start; // r3
    int select_option;     // r4
    int select_load;       // r2

    titleChangeMainMenu();
    titleDrawTitle();
    titleDrawMainMenu();
    pad_ret = titleCheckPad();
    switch (pad_ret) { /* irregular */
        case 0:
            break;
        case 1:
            TitleData.timer = 60.0f;
            shSdCall(10000, 0, 0, 0);
            TitleSprChgColor[11].timer = 0;
            return;

        case 2:
            TitleData.timer            = 60.0f;
            TitleSprChgColor[12].timer = 0;
            title_after_data_set       = 0;
            if (title_test_mode == 2) {
                if (TitleData.sel != 4) {
                    title_start_point = TitleData.sel - 1;
                }
                playing.battle_level = 2;
                playing.riddle_level = 0;
                SeCall(15002, 1.0f, 0);
                sh2sys_set_2(6);
            } else {
                if (title_test_mode == 1) {
                    select_game_start = TitleData.sel >= 3;
                    if (select_game_start != 0) {
                        select_game_start = TitleData.sel < 8;
                    }
                    select_option = TitleData.sel == 8;
                    select_load   = TitleData.sel == 1;
                } else {
                    select_game_start = TitleData.sel == 3;
                    select_option     = TitleData.sel == 4;
                    select_load       = TitleData.sel == 1;
                }
                if (select_game_start != 0) {
                    if (title_test_mode == 1) {
                        title_start_point = TitleData.sel - 3;
                    }
                    TitleData.menu[0] = -1;
                    TitleData.menu[1] = 1;
                    TitleData.menu[2] = 2;
                    TitleData.menu[3] = 3;
                    TitleData.menu[4] = -1;
                    TitleData.menu[5] = -1;
                    TitleData.menu[6] = -1;
                    TitleData.menu[7] = -1;
                    TitleData.menu[8] = -1;
                    TitleData.menu[9] = -1;
                    TitleData.sel     = titleGetCursorFromBattleLevel(playing.battle_level);
                    TitleData.alphar  = 0.0f;
                    TitleData.timer   = 60.0f;
                    shSdCall(10002, 0, 0, 0);
                    Sh2sys.step[2] += 1;
                    Sh2sys.step[3] = 0;
                    Sh2sys.step[4] = 0;
                    Sh2sys.step[5] = 0;
                    Sh2sys.step[6] = 0;
                    Sh2sys.step[7] = 0;
                } else {
                    if ((select_option != 0) || (select_load != 0)) {
                        shSdCall(10002, 0, 0, 0);
                    } else {
                        SeCall(15002, 1.0f, 0);
                    }
                    Sh2sys.step[2] = 6;
                    Sh2sys.step[3] = 0;
                    Sh2sys.step[4] = 0;
                    Sh2sys.step[5] = 0;
                    Sh2sys.step[6] = 0;
                    Sh2sys.step[7] = 0;
                }
            }
            break;
        case 3:
            break;
        default:
            ASSERT_ON_LINE(0, 1080);
    }

    TitleData.timer -= shGetDT();
    if (TitleData.timer <= 0.0f) {
        Sh2sys.step[2] = 7;
        Sh2sys.step[3] = 0;
        Sh2sys.step[4] = 0;
        Sh2sys.step[5] = 0;
        Sh2sys.step[6] = 0;
        Sh2sys.step[7] = 0;
    }

    TitleData.alphar += 0.06981317f;
    TitleData.alpha = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
    return;
}
// static inline float yay(float x) {
//     float dt = shGetDT();
//     return x / 19.2f * dt;
// }

static int titleCheckPad(void) {
    int ret; // r16
    int an;  // r2

    ret = 0;
    an  = shPadPress(0, 128);
    if ((an >= 97) && (an < 160)) {
        analog_data = 0.0f;
    } else if (an < 128) {
        if (analog_data == 0.0f) {
            analog_data = -1.000001f;
        } else {
            analog_data -= ((96 - an) / 19.2f) * shGetDT();
        }
    } else if (analog_data == 0.0f) {
        analog_data = 1.000001f;
    } else {
        analog_data += ((an - 160) / 19.2f) * shGetDT();
    }
    if ((shPadTrigger(0, 1024) != 0) || (shPadRepeat(0, 1024) != 0) || (analog_data < -1.0f)) {
        analog_data += 1.0f;
        if (analog_data > 0.0f) {
            analog_data = 0.0f;
        }
        if (TitleData.menu[TitleData.sel - 1] != -1) {
            TitleData.sel -= 1;
        } else {
            TitleData.sel = 9;
            while (TitleData.menu[TitleData.sel] == -1) {
                TitleData.sel--;
            }
        }
        ret = 1;
    } else if ((shPadTrigger(0, 2048) != 0) || (shPadRepeat(0, 2048) != 0) || !(analog_data <= 1.0f)) {
        analog_data -= 1.0f;
        if (analog_data < 0.0f) {
            analog_data = 0.0f;
        }
        if (TitleData.menu[TitleData.sel + 1] != -1) {
            TitleData.sel += 1;
        } else {
            TitleData.sel = 0;

            while (TitleData.menu[TitleData.sel] == -1) {
                TitleData.sel += 1;
            }
        }
        ret = 1;
    } else if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, 4) != 0)) {
        ret = 2;
    } else if (shPadTrigger(0, key_config.cancel) != 0) {
        ret = 3;
    }
    return ret;
}

static int titleGetCursorFromBattleLevel(u_char battle_level /* r2 */) {
    int ret; // r2

    switch (battle_level) { /* irregular */
        case SH2_BATTLE_LEVEL_HARD:
            ret = 1;
            break;
        case SH2_BATTLE_LEVEL_NORMAL:
            ret = 2;
            break;
        case SH2_BATTLE_LEVEL_EASY:
            ret = 3;
            break;
        default:
            ASSERT_ON_LINE(0, 1279);
    }

    return ret;
}

static void titleBattleSelect(void) {
    int pad_ret; // r2

    titleDrawTitle();
    titleDrawSubMenu(0);
    TitleData.timer -= shGetDT();
    pad_ret = titleCheckPad();
    switch (pad_ret) { /* irregular */
        case 0:
            break;
        case 1:
            TitleData.timer = 60.0f;
            shSdCall(10000, 0, 0, 0);
            TitleSprChgColor[11].timer = 0;
            break;
        case 2:
            TitleSprChgColor[12].timer = 0;
            TitleSprChgColor[11].timer = 0;
            playing.battle_level       = titleGetBattleLevelFromCursor(TitleData.sel);
            TitleData.timer            = 60.0f;
            TitleData.sel              = titleGetCursorFromRiddleLevel(playing.riddle_level);
            TitleData.alphar           = 0.0f;
            shSdCall(10002, 0, 0, 0);
            sh2sys_step_2();
            break;
        case 3:
            TitleSprChgColor[12].timer = 0;
            TitleSprChgColor[11].timer = 0;
            playing.battle_level       = titleGetBattleLevelFromCursor(TitleData.sel);
            titleBacktoMainMenuFromLevelMenu();
            break;
        default:
            ASSERT_ON_LINE(0, 1368);
            break;
    }

    if (TitleData.timer <= 0.0f) {
        TitleSprChgColor[12].timer = 0;
        TitleSprChgColor[11].timer = 0;
        playing.battle_level       = titleGetBattleLevelFromCursor(TitleData.sel);
        titleBacktoMainMenuFromLevelMenu();
    }
    TitleData.alphar += 0.06981317f;
    TitleData.alpha = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
    return;
}

static void titleBacktoMainMenuFromLevelMenu(void) {
    TitleData.memcard = mcStartCheck2();
    titleCreateMainMenu();
    TitleData.timer = 60.0f;
    TitleData.sel   = 3;
    shSdCall(10003, 0, 0, 0);
    sh2sys_set_2(2);
}

static u_char titleGetBattleLevelFromCursor(int cur /* r2 */) {
    u_char ret; // r2

    switch (cur) { /* irregular */
        case 1:
            ret = 3;
            break;
        case 2:
            ret = 2;
            break;
        case 3:
            ret = 1;
            break;
        default:
            ASSERT_ON_LINE(0, 1452);
    }

    return ret;
}

static int titleGetCursorFromRiddleLevel(u_char riddle_level /* r2 */) {
    int ret; // r2

    switch (riddle_level) { /* irregular */
        case 2:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        case 0:
            ret = 3;
            break;
        default:
            ASSERT_ON_LINE(0, 1494);
    }

    return ret;
}

static void titleRiddleSelect(void) {
    int pad_ret; // r2
    titleDrawTitle();
    titleDrawSubMenu(1);
    TitleData.timer -= shGetDT();
    pad_ret = titleCheckPad();
    switch (pad_ret) { /* irregular */
        case 0:
            break;
        case 1:
            TitleData.timer = 60.0f;
            shSdCall(10000, 0, 0, 0);
            TitleSprChgColor[11].timer = 0;
            break;
        case 2:
            TitleSprChgColor[12].timer = 0;
            TitleSprChgColor[11].timer = 0;
            playing.riddle_level       = titleGetRiddleLevelFromCursor(TitleData.sel);
            title_after_data_set       = 0;
            TitleData.timer            = 60.0f;
            SeCall(15002, 1.0f, 0);
            sh2sys_set_2(5);
            break;
        case 3:
            TitleSprChgColor[12].timer = 0;
            TitleSprChgColor[11].timer = 0;
            playing.riddle_level       = titleGetRiddleLevelFromCursor(TitleData.sel);
            TitleData.sel              = titleGetCursorFromBattleLevel(playing.battle_level);
            TitleData.alphar           = 0.0f;
            TitleData.timer            = 60.0f;
            shSdCall(10003, 0, 0, 0);
            sh2sys_backstep_2();
            break;
        default:
            ASSERT_ON_LINE(0, 1580);
    }

    if (TitleData.timer <= 0.0f) {
        TitleSprChgColor[12].timer = 0;
        TitleSprChgColor[11].timer = 0;
        playing.riddle_level       = titleGetRiddleLevelFromCursor(TitleData.sel);
        titleBacktoMainMenuFromLevelMenu();
    }
    TitleData.alphar += 0.06981317f;
    TitleData.alpha = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
}

static u_char titleGetRiddleLevelFromCursor(int cur /* r2 */) {
    u_char ret; // r2

    switch (cur) { /* irregular */
        case 1:
            ret = 2;
            break;
        case 2:
            ret = 1;
            break;
        case 3:
            ret = 0;
            break;
        default:
            ASSERT_ON_LINE(0, 1639);
    }

    return ret;
}

static void titleFadeOutNewGame(void) {
    s32 temp_a0;

    switch (Sh2sys.step[3]) {
        case 0:
            ScreenEffectFadeStart(2, 2.0f);
            TitleData.alpha = 255;
            titleDrawTitle();
            if (title_test_mode != 2) {
                titleDrawSubMenu(2);
            }
            sh2sys_step_3();
            return;

        default:
            break;
    }

    if (ScreenEffectFadeCheck() != 0) {
        if (title_test_mode == 0) {
            connect_pos[0] = TitleJPStartPointList->pos_x;
            connect_pos[1] = TitleJPStartPointList->pos_y;
            connect_pos[2] = TitleJPStartPointList->pos_z;
            connect_pos[3] = TitleJPStartPointList->rot;
            playing.stage  = TitleJPStartPointList->stg;
        } else if (title_test_mode == 1) {
            connect_pos[0] = TitleJPStartPointList[title_start_point].pos_x;
            connect_pos[1] = TitleJPStartPointList[title_start_point].pos_y;
            connect_pos[2] = TitleJPStartPointList[title_start_point].pos_z;
            connect_pos[3] = TitleJPStartPointList[title_start_point].rot;
            playing.stage  = TitleJPStartPointList[title_start_point].stg;
        }
        TitleData.mode = 3;
        return;
    }
    TitleSprChgColor->timer = TitleSprChgColor->cycle;
    titleDrawTitle();
    if (title_test_mode != 2) {
        titleDrawSubMenu(2);
    }
    return;
}

static void titleFadeOut(void) {

    switch (Sh2sys.step[3]) {
        case 0:
            ScreenEffectFadeStart(2, 2.0f);
            TitleData.alphar = 0.0f;
            TitleData.alpha  = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
            titleDrawTitle();
            titleDrawMainMenu();
            sh2sys_step_3();
            return;

        default:
            break;
    }

    if (ScreenEffectFadeCheck() != 0) {
        if (title_test_mode == 2) {
            connect_pos[0] = TitleUSPStartPointList[title_start_point].pos_x;
            connect_pos[1] = TitleUSPStartPointList[title_start_point].pos_y;
            connect_pos[2] = TitleUSPStartPointList[title_start_point].pos_z;
            connect_pos[3] = TitleUSPStartPointList[title_start_point].rot;
            playing.stage  = TitleUSPStartPointList[title_start_point].stg;
        }
        TitleData.mode = TitleData.menu[TitleData.sel];
        return;
    }

    TitleData.alphar += QUARTER_TURN;
    TitleData.alpha         = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
    TitleSprChgColor->timer = TitleSprChgColor->cycle;
    titleDrawTitle();
    titleDrawMainMenu();
}

static void titleExit(void) {

    switch (Sh2sys.step[3]) {
        case 0:
            ScreenEffectFadeStart(2, 2.0f);
            TitleData.alphar = 0.0f;
            TitleData.alpha  = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
            titleDrawTitle();
            titleDrawMainMenu();

            sh2sys_step_3();
            return;

        default:
            break;
    }

    if (ScreenEffectFadeCheck() != 0) {
        TitleData.mode = 5;
    }
    if (!(TitleData.timer <= 0.0f)) {
        TitleData.mode = 6;
        return;
    }

    TitleData.alphar += 0.06981317f;
    TitleData.alpha = (int) (191.0f + (63.0f * shCosF(TitleData.alphar)));
    titleDrawTitle();
    titleDrawMainMenu();
}

static void titleDrawTitle(void) {
    TitleSprChgColorWork* chg_color_info;

    PictureLoadImage((struct sh2gfw_AREA_HEAD*) TitleData.pload0, 0, -1, -1);
    shQzero(&TitleData.pic0, sizeof(PicDraw_Data));
    picture_set_ap(&TitleData.pic0, TitleData.pload0);
    TitleData.pic0.otp = 1;
    picture_set_xy(&TitleData.pic0, -4096, -3584, 4096, 3584);
    picture_set_uvst(&TitleData.pic0, 0, 0, 512, 512);
    PictureDraw(&TitleData.pic0);
    PictureLoadImage((struct sh2gfw_AREA_HEAD*) TitleData.pload1, 2, -1, -1);
    titleRenewChangeColorManagement(&TitleSprChgColor->timer, TitleSprChgColor->cycle, 1);
    titleChangeColor(&TitleSpr->rgba[1], TitleSprChgColor->start_rgba, TitleSprChgColor->end_rgba, TitleSprChgColor->timer, TitleSprChgColor->cycle, 0.5f);
    titleDrawSprite(-257, -103, 0);
}

static void titleDrawSprite(short x /* r17 */, short y /* r16 */, short id /* r18 */) {
    shQzero(&TitleData.pic0, sizeof(PicDraw_Data));
    picture_set_ap(&TitleData.pic0, TitleData.pload1);
    picture_set_rgb(&TitleData.pic0, &TitleSpr[id].rgba);
    picture_set_alpha(&TitleData.pic0, TitleSpr[id].rgba[3]); // @todo: probably inline is wrong...

    if (id == 11) {
        TitleData.pic0.otp = 3;
    } else {
        TitleData.pic0.otp = 5;
    }
    TitleData.pic0.x0 = x * 16;
    TitleData.pic0.y0 = y * 16;
    TitleData.pic0.x1 = TitleSpr[id].w * 16;
    TitleData.pic0.y1 = TitleSpr[id].h * 16;
    TitleData.pic0.status |= 2;
    TitleData.pic0.us0 = TitleSpr[id].u0 * 16;
    TitleData.pic0.vt0 = TitleSpr[id].v0 * 16;
    TitleData.pic0.us1 = TitleSpr[id].u1 * 16;
    TitleData.pic0.vt1 = TitleSpr[id].v1 * 16;
    TitleData.pic0.status |= 4;
    PictureDraw(&TitleData.pic0);
}

static void titleDrawMainMenu(void) {
    short cpos[8];   // r29+64
    short cposy[8];  // r29+80
    int i;           // r16
    int j;           // r17
    short ef_pos[7]; // r29+96
    short w[7];      // r29+112

    s32 temp_s1;
    s32 loop;
    s32 loop_2;
    u32 temp_v0;
    u32 temp_v1_2;
    void* temp_v0_2;
    void* temp_v1;

    if (title_test_mode == 2) {
        cpos[0]  = -94;
        cpos[1]  = -86;
        cpos[2]  = -70;
        cpos[3]  = -78;
        cposy[0] = 77;
        cposy[1] = 99;
        cposy[2] = 121;
        cposy[3] = 143;
    } else if (title_test_mode == 1) {
        cpos[0]  = -68;
        cpos[1]  = -92;
        cpos[2]  = -94;
        cpos[3]  = -86;
        cpos[4]  = -74;
        cpos[5]  = -70;
        cpos[6]  = -62;
        cpos[7]  = -78;
        cposy[0] = 8;
        cposy[1] = 30;
        cposy[2] = 52;
        cposy[3] = 74;
        cposy[4] = 96;
        cposy[5] = 118;
        cposy[6] = 140;
        cposy[7] = 162;
    } else {
        cpos[0]  = -68;
        cpos[1]  = -92;
        cpos[2]  = -94;
        cpos[3]  = -78;
        cposy[0] = 74;
        cposy[1] = 96;
        cposy[2] = 118;
        cposy[3] = 140;
    }
    if (title_test_mode == 2) {
        ef_pos[0] = -80;
        ef_pos[1] = -71;
        ef_pos[2] = -50;
        ef_pos[3] = -60;
        w[1]      = 160;
        w[2]      = 142;
        w[3]      = 100;
        w[4]      = 120;
    } else if (title_test_mode == 1) {
        ef_pos[0] = -48;
        ef_pos[1] = -78;
        ef_pos[2] = -80;
        ef_pos[3] = -71;
        ef_pos[4] = -58;
        ef_pos[5] = -50;
        ef_pos[6] = -42;
        w[0]      = -60;
        w[1]      = 96;
        w[2]      = 156;
        w[3]      = 160;
        w[4]      = 142;
        w[5]      = 116;
        w[6]      = 100;
        w[7]      = 84; //????
        w[8]      = 120;
    } else {
        ef_pos[0] = -48;
        ef_pos[1] = -78;
        ef_pos[2] = -80;
        ef_pos[3] = -60;
        w[1]      = 96;
        w[2]      = 156;
        w[3]      = 160;
        w[4]      = 120;
    }
    titleChangeSpriteColor2(11);
    TitleSpr[11].w = w[TitleData.sel - 1] + 8;
    titleDrawSprite((s16) ((s64) ((cpos[TitleData.sel - 1] - 4) << 48) >> 48), (s16) ((s64) (((&cpos[7])[TitleData.sel] + 1) << 48) >> 48), 11);
    if (title_test_mode == 2) {
        titleDrawSprite(-96, cposy[0], 3);
        titleDrawSprite(-96, cposy[1], 14);
        titleDrawSprite(-99, cposy[2], 13);
        titleChangeCursorSpriteColor();
        titleDrawSprite(cpos[TitleData.sel], (&cpos[7])[TitleData.sel], 12);
        return;
    }
    if (title_test_mode == 1) {
        loop = 0;
    loop_17:
        if (loop < 2) {
            temp_v0 = (&TitleData.menu[1])[loop];
            if (temp_v0 != -1U) {
                titleDrawSprite(-96, cposy[loop], (s16) ((s64) ((temp_v0 - 1 + 1) << 48) >> 48));
            }
            loop += 1;
            goto loop_17;
        }
        titleDrawSprite(-96, cposy[2], 3);
        titleDrawSprite(-96, cposy[3], 14);
        titleDrawSprite(-96, cposy[4], 16);
        titleDrawSprite(-99, cposy[5], 13);
        titleDrawSprite(-96, cposy[6], 15);
        titleDrawSprite(-96, cposy[7], 4);
        titleChangeCursorSpriteColor();
        titleDrawSprite(cpos[TitleData.sel - 1], (&cpos[7])[TitleData.sel], 12);
        return;
    }
    loop_2 = 0;
loop_24:
    if (loop_2 < 4) {
        temp_v1_2 = (&TitleData.menu[1])[loop_2];
        if (temp_v1_2 != -1U) {
            temp_s1 = temp_v1_2 - 1;
            titleDrawSprite(-96, cposy[loop_2], (s16) ((s64) ((temp_s1 + 1) << 48) >> 48));
            if (TitleData.sel == (loop_2 + 1)) {
                titleChangeCursorSpriteColor();
                titleDrawSprite(cpos[temp_s1], cposy[loop_2], 12);
            }
        }
        loop_2 += 1;
        goto loop_24;
    }
}

static void titleDrawSubMenu(int sel /* r16 */) {
    short x_pos; // r29+42
    // short x_pos; // r29+44
    int i; // r4
    // short x_pos; // r29+46

    s16 sp2E;
    s16 sp2C;
    s16 sp2A;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_a0;

    titleDrawSprite(-196, 60, 5);
    titleDrawSprite(11, 60, 6);
    if (sel == 0) {
        TitleSpr[11].h -= 7;
        titleChangeSpriteColor2(11);
        titleGetMenuEfctPosBattle(&sp2A, &TitleSpr[11].w, TitleData.sel);
        titleDrawSprite(sp2A, (s16) ((s64) (((TitleData.sel * 18) + 66) << 48) >> 48), 11);
        TitleSpr[11].h += 7;
        titleDrawSprite(-196, 80, 7);
        titleDrawSprite(-196, 98, 8);
        titleDrawSprite(-196, 115, 9);
        titleDrawSprite(11, 80, 7);
        titleDrawSprite(11, 98, 8);
        titleDrawSprite(11, 115, 9);
        titleChangeCursorSpriteColor();
        temp_s0 = TitleData.sel;
        titleDrawSprite(titleGetCursorXPosBattle(temp_s0), (s16) ((s64) (((temp_s0 * 18) + 62) << 48) >> 48), 12);
        return;
    }
    if (sel == 1) {
        TitleSpr[11].h -= 7;
        titleChangeSpriteColor2(11);
        titleGetMenuEfctPosRiddle(&sp2C, &TitleSpr[11].w, TitleData.sel);
        titleDrawSprite(sp2C, (s16) ((s64) (((TitleData.sel * 18) + 66) << 48) >> 48), 11);
        TitleSpr[11].h += 7;
        titleDrawSprite(11, 80, 7);
        titleDrawSprite(11, 98, 8);
        titleDrawSprite(11, 115, 9);
        switch (playing.battle_level) { /* switch 1; irregular */
            case 1:                     /* switch 1 */
                titleDrawSprite(-196, 115, 9);
                break;
            case 2: /* switch 1 */
                titleDrawSprite(-196, 98, 8);
                break;
            case 3: /* switch 1 */
                titleDrawSprite(-196, 80, 7);
                break;
        }
        var_a0 = 0;
    loop_12:
        if (var_a0 < 4) {
            TitleSpr[11].rgba[var_a0] = (&TitleSprChgColor[13].end_rgba[2])[var_a0];
            var_a0 += 1;
            goto loop_12;
        }
        TitleSpr[11].h -= 7;
        titleGetMenuEfctPosBattle(&sp2E, &TitleSpr[11].w, titleGetCursorFromBattleLevel(playing.battle_level));
        titleDrawSprite(sp2E, (s16) ((s64) (((titleGetCursorFromBattleLevel(playing.battle_level) * 18) + 66) << 48) >> 48), 11);
        TitleSpr[11].h += 7;
        titleChangeCursorSpriteColor();
        temp_s0_2 = TitleData.sel;
        titleDrawSprite(titleGetCursorXPosRiddle(temp_s0_2), (s16) ((s64) (((temp_s0_2 * 18) + 62) << 48) >> 48), 12);
        return;
    }
    switch (playing.battle_level) { /* switch 2; irregular */
        case 1:                     /* switch 2 */
            titleDrawSprite(-196, 115, 9);
            break;
        case 2: /* switch 2 */
            titleDrawSprite(-196, 98, 8);
            break;
        case 3: /* switch 2 */
            titleDrawSprite(-196, 80, 7);
            break;
    }
    switch (playing.riddle_level) { /* switch 3; irregular */
        case 0:                     /* switch 3 */
            titleDrawSprite(11, 115, 9);
            return;
        case 1: /* switch 3 */
            titleDrawSprite(11, 98, 8);
            return;
        case 2: /* switch 3 */
            titleDrawSprite(11, 80, 7);
            return;
    }
}

static short titleGetCursorXPosBattle(int cur /* r2 */) {
    short ret; // r2

    switch (cur) {
        case 1:
            ret = -160;
            break;
        case 2:
            ret = -172;
            break;
        case 3:
            ret = -157;
            break;
        default:
            ASSERT_ON_LINE(0, 2505);
    }

    return ret;
}

static void titleGetMenuEfctPosBattle(short* x_pos /* r2 */, short* w /* r2 */, int cur /* r2 */) {
    switch (cur) {
        case 1:
            *x_pos = -141;
            *w     = 82;
            return;
        case 2:
            *x_pos = -156;
            *w     = 112;
            return;
        case 3:
            *x_pos = -138;
            *w     = 76;
            return;
        default:
            ASSERT_ON_LINE(0, 2562);
    }
}

static short titleGetCursorXPosRiddle(int cur /* r2 */) {
    short ret; // r2

    switch (cur) {
        case 1:
            ret = 47;
            break;
        case 2:
            ret = 35;
            break;
        case 3:
            ret = 50;
            break;

        default:
            ASSERT_ON_LINE(0, 2562);
    }

    return ret;
}

static void titleGetMenuEfctPosRiddle(short* x_pos /* r2 */, short* w /* r2 */, int cur /* r2 */) {
    switch (cur) {
        case 1:
            *x_pos = 66;
            *w     = 82;
            return;
        case 2:
            *x_pos = 51;
            *w     = 112;
            return;
        case 3:
            *x_pos = 69;
            *w     = 76;
            return;
        default:
            ASSERT_ON_LINE(0, 2664);
    }
}

static void titleChangeSpriteColor2(short id /* r2 */) {
    TitleSprChgColorWork* chg_color_info; // r16

    chg_color_info = &TitleSprChgColor[id];
    titleRenewChangeColorManagement(&chg_color_info->timer, chg_color_info->cycle, 0);
    titleChangeColor(TitleSpr[id].rgba, chg_color_info->start_rgba, chg_color_info->end_rgba, chg_color_info->timer, chg_color_info->cycle, 0.5f);
}

static void titleChangeCursorSpriteColor(void) {
    TitleSprChgColorWork* chg_color_info = &TitleSprChgColor[12]; // r16
    titleRenewChangeColorManagement(&chg_color_info->timer, chg_color_info->cycle, 1);
    titleChangeColor(TitleSpr[12].rgba, chg_color_info->start_rgba, chg_color_info->end_rgba, chg_color_info->timer, chg_color_info->cycle, 1.0f);
}

static void titleRenewChangeColorManagement(float* timer /* r16 */, float cycle /* r20 */, int repeat /* r2 */) {
    if (repeat == 1) {
        *timer += shGetDT();
        if (*timer >= cycle) {
            *timer = shGetDT();
        }
    } else if (*timer <= cycle) {
        *timer += shGetDT();
    }
}

static void titleChangeColor(int* rgba /* r20 */, int* start_rgba /* r19 */, int* end_rgba /* r18 */, float timer /* r29+128 */, float cycle_time /* r29+128 */, float cycle_sin /* r29+128 */) {
    int diff_color[4]; // r29+112
    float ratio;       // r20
    int i;             // r16

    ratio = shSinF(PI * (cycle_sin * (timer / cycle_time)));

    for (i = 0; i < 4; i++) {
        diff_color[i] = end_rgba[i] - start_rgba[i];
        rgba[i]       = (int) (start_rgba[i] + (ratio * diff_color[i]));
    }
}

int GameendMain(void) {
    static float game_over_timer; // @ 18274584
    PicDraw_Data pic;             // r29+16

    switch (Sh2sys.step[4]) { /* irregular */
        case 0:
            FcRead(data_pic_etc_comingsoon_tex, TitleData.pload0);
            Sh2sys.step[4] += 1;
            Sh2sys.step[5] = 0;
            Sh2sys.step[6] = 0;
            Sh2sys.step[7] = 0;
            /* fallthrough */
        case 1:
            if ((fsSync(1, -1) >= 0) && (ScreenEffectFadeCheck() != 0)) {
                sh2sys_step_4();
                case 2:
                    ScreenEffectFadeStart(4, 0.5f);
                    game_over_timer = 0.0f;
                    sh2sys_step_4();
                case 3:
                    PictureLoadImage((sh2gfw_AREA_HEAD*) TitleData.pload0, 0, -1, -1);
                    shQzero(&pic, sizeof(PicDraw_Data));
                    pic.ap   = (sh2gfw_AREA_HEAD*) TitleData.pload0;
                    pic.tex  = -1;
                    pic.clut = -1;
                    pic.status |= 1;
                    pic.otp = 1;
                    PictureDraw(&pic);
                    d1cSend(spkDmaKick());
                    game_over_timer += shGetDT();
                    if ((shPadTrigger(0, key_config.action) != 0) || (shPadTrigger(0, key_config.cancel) != 0) || !(game_over_timer <= 5.0f)) {
                        return 1;
                    }
                    goto block_14;
            }
        block_14:
        default:
            return 0;
    }
}

OPD_W org_title; // size: 52, address: 18274208
OPD_W opd_w[6];  // size: 312, address: 18274272

static void opd_work_init(void) {
    int loop; // r3

    OPD_W* var_a1;
    OPD_W* var_a3_2;
    OPD_W* var_t0;
    OPD_W* var_t1;
    f32 temp_a0_2;
    f32 temp_a2_2;
    f32* temp_a2;
    f32* temp_a3;
    s32 temp_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    bzero(opd_w, sizeof(opd_w));
    bzero(&org_title, sizeof(org_title));
    var_v1 = 0;
loop_6:
    if (var_v1 < 2) {
        temp_a0                 = var_v1 * 52;
        var_a1                  = &opd_w[var_v1];
        var_a1->u0              = 0.0f;
        *(&opd_w->u1 + temp_a0) = 160.0f;
        temp_a3                 = &opd_w->v0 + temp_a0;
        *temp_a3                = (f32) ((var_v1 + 1) * 48);
        *(&opd_w->v1 + temp_a0) = 47.0f + *temp_a3;
        *(&opd_w->x0 + temp_a0) = -80.0f;
        *(&opd_w->x1 + temp_a0) = 80.0f;
        temp_a2                 = &opd_w->y0 + temp_a0;
        *temp_a2                = -24.0f;
        *(&opd_w->y1 + temp_a0) = 47.0f + *temp_a2;
        var_t1                  = &(&opd_w[2])[var_v1];
        var_a3                  = 13;
        var_t0                  = var_a1;
        do {
            temp_a2_2 = var_t0->u0;
            var_t0 += 4;
            var_a3 -= 1;
            var_t1->u0 = temp_a2_2;
            var_t1 += 4;
        } while (var_a3 > 0);
        var_a3_2 = &(&opd_w[4])[var_v1];
        var_a2   = 13;
        do {
            temp_a0_2 = var_a1->u0;
            var_a1 += 4;
            var_a2 -= 1;
            var_a3_2->u0 = temp_a0_2;
            var_a3_2 += 4;
        } while (var_a2 > 0);
        var_v1 += 1;
        goto loop_6;
    }
    org_title.u0 = 0.0f;
    org_title.u1 = 160.0f;
    org_title.v0 = 0.0f;
    org_title.v1 = 48.0f;
    org_title.x0 = -80.0f;
    org_title.x1 = 80.0f;
    org_title.y0 = -24.0f;
    org_title.y1 = 47.0f + org_title.y0;
}

int GameoverMain(void) {
    static float game_over_timer; // @ 18274200
    static int fid;               // @ 18274192

    switch (Sh2sys.step[4]) { /* irregular */
        case 0:
            fid = 0.0f;
            sh2sys_step_4();
            /* fallthrough */
        case 1:
            fontClear();
            fid = FcRead(data_pic_etc_gameover1_tex, get_gp_data_buf_addr());
            fid = 0.0f;
            if (fid != -1) {
                fsSync(0, fid);
            }
            sh2sys_step_4();
            opd_work_init();
            ScreenEffectFadeStart(4, 0.0f);
            /* fallthrough */
        case 2:
            if (draw_opd_wowk_main() != 0) {
                sh2sys_step_4();
            }
        default:
            return 0;
        case 3:
            return 1;
    }
}
static inline int q4(float x) {
    int ret;
    asm("qmtc2 %1, vf4; vftoi4.x vf4, vf4; qmfc2 %0, vf4" : "=r"(ret) : "r"(x));
    return ret;
}

static int draw_opd_wowk_main(void) {
    PicDraw_Data pic; // r29+32
    int loop;         // r16
    int rnd;          // r3

    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_v1;

    switch (org_title.step) { /* irregular */
        case 0:
            org_title.timer += 1;
            if (org_title.timer == 32) {
                org_title.step += 1;
                org_title.timer = 0;
            }
            break;
        default:
            break;
        case 1:
            org_title.rgb += 4;
            if (org_title.rgb == 96) {
                org_title.step += 1;
            }
            break;
        case 2:
            org_title.timer += 1;
            if (org_title.timer == 64) {
                org_title.step += 1;
                org_title.timer = 0;
            }
            break;
        case 3:
            org_title.rgb -= 8;
            if (org_title.rgb == 0) {
                org_title.step += 1;
            }
            break;
        case 4:
            return 1;
    }
block_15:
    PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
    shQzero(&pic, sizeof(PicDraw_Data));
    pic.ap   = get_gp_data_buf_addr();
    pic.tex  = -1;
    pic.clut = -1;
    pic.status |= 1;
    pic.otp       = 1;
    pic.a         = 128;
    pic.alpha_a   = 0;
    pic.alpha_b   = 1;
    pic.alpha_c   = 0;
    pic.alpha_d   = 1;
    pic.alpha_fix = 128;
    pic.status    = temp_v0 | 32;
    loop          = 0;
loop_19:
    if (loop < 6) {
        temp_v1 = (rand() % 30) - 15;
        if (org_title.step >= 2) {
            pic.r = org_title.rgb;
            pic.g = org_title.rgb;
            pic.b = org_title.rgb;
            pic.status |= 16;
        }
        pic.us0 = q4(opd_w[loop].u0);
        pic.vt0 = q4(opd_w[loop].v0);
        pic.us1 = q4(opd_w[loop].u1);
        pic.vt1 = q4(opd_w[loop].v1);
        pic.status |= 4;
        pic.x0 = q4(opd_w[loop].x0);
        pic.y0 = q4(opd_w[loop].y0);
        pic.x1 = q4(opd_w[loop].x1);
        pic.y1 = q4(opd_w[loop].y1);
        pic.status |= 2;
        PictureDraw(&pic);
        loop += 1;
        goto loop_19;
    }
    pic.r = org_title.rgb;
    pic.g = org_title.rgb;
    pic.b = org_title.rgb;
    pic.status |= 16;
    pic.us0 = q4(org_title.u0);
    pic.vt0 = q4(org_title.v0);
    pic.us1 = q4(org_title.u1);
    pic.vt1 = q4(org_title.v1);
    pic.status |= 4;
    pic.x0     = q4(org_title.x0);
    pic.y0     = q4(org_title.y0);
    pic.x1     = q4(org_title.x1);
    pic.y1     = q4(org_title.y1);
    pic.status = temp_v0_3 | 2;
    PictureDraw(&pic);
    d1cSend(spkDmaKick());
    return 0;
}
