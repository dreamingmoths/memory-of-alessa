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
#include "data/daily.thu/data_pic_etc.h"

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


TitleDataWork TitleData; // size: 0x94, address: 0x116D950
int title_after_data_set;
int title_start_point;                      // size: 0x4, address: 0x116D938
float analog_data;                          // size: 0x4, address: 0x116D930

extern int jump_menu_select;                       // size: 0x4, address: 0x11B6990

static int title_test_mode = TITLE_TEST_MODE_NONE; // size: 0x4, address: 0x116D788

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

    if ((title_test_mode != TITLE_TEST_MODE_NONE) && (jump_menu_select == 0) && (title_after_data_set == 0)) {
        title_after_data_set = 1;
        ItemGet(SH2_ITEM_17);
        ItemGet(SH2_ITEM_18);
        item.light_switch = 1;
        if (title_test_mode == TITLE_TEST_MODE_US) {
            switch (title_start_point) { /* switch 1; irregular */
                case 1:                  /* switch 1 */
                    ItemGet(SH2_ITEM_04);
                    for (i = 0; i < 3; i++) {
                        ItemGet(SH2_ITEM_05);
                    }
                    ItemGet(SH2_ITEM_11);
                    for (i = 0; i < 5; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    for (i = 0; i < 1; i++) {
                        ItemGet(FIRST_AID_KIT);
                    }
                    ItemGet(SH2_ITEM_16);
                    item.equip = 4;
                    SET_GAME_FLAG(25);
                    SET_GAME_FLAG(66);
                    SET_GAME_FLAG(35);
                    SET_GAME_FLAG(40);
                    SET_GAME_FLAG(41);
                    SET_GAME_FLAG(43);
                    SET_GAME_FLAG(49);
                    SET_GAME_FLAG(67);
                    playing.riddle_level = 0;
                    return;
                case 2: /* switch 1 */
                    ItemGet(SH2_ITEM_04);
                    for (i = 0; i < 3; i++) {
                        ItemGet(SH2_ITEM_05);
                    }
                    ItemGet(SH2_ITEM_06);
                    for (i = 0; i < 1; i++) {
                        ItemGet(SH2_ITEM_07);
                    }
                    ItemGet(SH2_ITEM_11);
                    ItemGet(SH2_ITEM_12);
                    for (i = 0; i < 8; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    for (i = 0; i < 2; i++) {
                        ItemGet(FIRST_AID_KIT);
                    }
                    ItemGet(SH2_ITEM_15);
                    ItemGet(SH2_ITEM_16);
                    item.equip = 4;
                    SET_GAME_FLAG(28);
                    SET_GAME_FLAG(35);
                    playing.riddle_level = 0;
                    return;
            }
        } else {
            switch (title_start_point) { /* switch 2; irregular */
                case 1:                  /* switch 2 */
                    ItemGet(SH2_ITEM_11);
                    ItemGet(SH2_ITEM_16);
                    for (i = 0; i < 16; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    item.equip = 11;
                    return;
                case 2: /* switch 2 */
                    SET_GAME_FLAG(15);
                    ItemGet(SH2_ITEM_11);
                    ItemGet(SH2_ITEM_04);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_05);
                    }
                    ItemGet(SH2_ITEM_12);
                    ItemGet(SH2_ITEM_16);
                    ItemGet(SH2_ITEM_15);
                    for (i = 0; i < 16; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    item.equip = 4;
                    return;
                case 3: /* switch 2 */
                    ItemGet(SH2_ITEM_11);
                    ItemGet(SH2_ITEM_04);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_05);
                    }
                    ItemGet(SH2_ITEM_06);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_07);
                    }
                    ItemGet(SH2_ITEM_12);
                    ItemGet(SH2_ITEM_16);
                    ItemGet(SH2_ITEM_15);
                    for (i = 0; i < 16; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    item.equip = 4;
                    return;
                case 4: /* switch 2 */
                    ItemGet(SH2_ITEM_04);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_05);
                    }
                    ItemGet(SH2_ITEM_06);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_07);
                    }
                    ItemGet(SH2_ITEM_08);
                    for (i = 0; i < 9; i++) {
                        ItemGet(SH2_ITEM_09);
                    }
                    ItemGet(SH2_ITEM_10);
                    ItemGet(SH2_ITEM_11);
                    ItemGet(SH2_ITEM_12);
                    ItemGet(SH2_ITEM_13);
                    for (i = 0; i < 16; i++) {
                        ItemGet(HEALTH_DRINK);
                    }
                    ItemGet(SH2_ITEM_15);
                    ItemGet(SH2_ITEM_16);
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
            TitleData.mode    = SH2_TITLE_DATA_MODE_0;
            TitleData.sel     = 0;
            TitleData.alpha   = 255;
            TitleData.alphar  = 0.0f;
            TitleData.timer   = 60.0f;
            for (i = 0; i < 10; i++) {
                TitleData.menu[i] = -1;
            }
            TitleData.pload0     = get_gp_data_buf_addr();
            TitleData.pload1     = get_gp_data_buf_addr() + 0x80000;
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
                    DEBUG_LOG_ON_LINE(642, "title.tex: read finished(%d.%02d)\n", (wait_loop / 60), ((wait_loop % 60) * 100) / 60);
                    sh2sys_step_3();
                    break;
                case 0: /* switch 2 */
                    DEBUG_LOG_ON_LINE(647, "!!! illegal fid=%d\n", fid);
                    break;
                case -1: /* switch 2 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(651, "title.tex: now reading(%d.)...\n", (wait_loop / 60));
                        break;
                    }
                    break;
                case -2: /* switch 2 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(656, "title.tex: now waiting(%d.)...\n", (wait_loop / 60));
                        return;
                    }
                    break;
                default: /* switch 2 */
                    DEBUG_LOG_ON_LINE(660, "illegal return value\n");
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
                    DEBUG_LOG_ON_LINE(681, "title.tex: read finished(%d.%02d)\n", (wait_loop / 60), (((wait_loop % 60) * 100) / 60));
                    sh2sys_step_2();
                    return;
                case 0: /* switch 3 */
                    DEBUG_LOG_ON_LINE(686, "!!! illegal fid=%d\n", fid);
                    return;
                case -1: /* switch 3 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(690, "title.tex: now reading(%d.)...\n", (wait_loop / 60));
                        return;
                    }
                    break;
                case -2: /* switch 3 */
                    if ((wait_loop % 60) == 0) {
                        DEBUG_LOG_ON_LINE(695, "title.tex: now waiting(%d.)...\n", (wait_loop / 60));
                        return;
                    }
                    break;
                default: /* switch 3 */
                    DEBUG_LOG_ON_LINE(699, "illegal return value\n");
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
    if (title_test_mode == TITLE_TEST_MODE_US) {
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
    if (title_test_mode == TITLE_TEST_MODE_US) {
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
            break;

        case 2:
            TitleData.timer            = 60.0f;
            TitleSprChgColor[12].timer = 0;
            title_after_data_set       = 0;
            if (title_test_mode == TITLE_TEST_MODE_US) {
                if (TitleData.sel != 4) {
                    title_start_point = TitleData.sel - 1;
                }
                playing.battle_level = 2;
                playing.riddle_level = 0;
                SeCall(15002, 1.0f, 0);
                sh2sys_set_2(6);
            } else {
                if (title_test_mode == TITLE_TEST_MODE_JP) {
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
                    if (title_test_mode == TITLE_TEST_MODE_JP) {
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
                    sh2sys_step_2();
                } else {
                    if ((select_option != 0) || (select_load != 0)) {
                        shSdCall(10002, 0, 0, 0);
                    } else {
                        SeCall(15002, 1.0f, 0);
                    }
                    sh2sys_set_2(6);
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


#ifdef NON_MATCHING
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
    if ((shPadTrigger(0, PAD_KEY_DPAD_UP) != 0) || (shPadRepeat(0, PAD_KEY_DPAD_UP) != 0) || (analog_data < -1.0f)) {
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
    } else if ((shPadTrigger(0, PAD_KEY_DPAD_DOWN) != 0) || (shPadRepeat(0, PAD_KEY_DPAD_DOWN) != 0) || analog_data > 1.0f) {
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
    } else if ((shPadTrigger(0, key_config.enter) != 0) || (shPadTrigger(0, PAD_KEY_SELECT) != 0)) {
        ret = 2;
    } else if (shPadTrigger(0, key_config.cancel) != 0) {
        ret = 3;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/title", titleCheckPad);
#endif

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
            if (title_test_mode != TITLE_TEST_MODE_US) {
                titleDrawSubMenu(2);
            }
            sh2sys_step_3();
            return;

        default:
            break;
    }

    if (ScreenEffectFadeCheck() != 0) {
        if (title_test_mode == TITLE_TEST_MODE_NONE) {
            connect_pos[0] = TitleJPStartPointList->pos_x;
            connect_pos[1] = TitleJPStartPointList->pos_y;
            connect_pos[2] = TitleJPStartPointList->pos_z;
            connect_pos[3] = TitleJPStartPointList->rot;
            playing.stage  = TitleJPStartPointList->stg;
        } else if (title_test_mode == TITLE_TEST_MODE_JP) {
            connect_pos[0] = TitleJPStartPointList[title_start_point].pos_x;
            connect_pos[1] = TitleJPStartPointList[title_start_point].pos_y;
            connect_pos[2] = TitleJPStartPointList[title_start_point].pos_z;
            connect_pos[3] = TitleJPStartPointList[title_start_point].rot;
            playing.stage  = TitleJPStartPointList[title_start_point].stg;
        }
        TitleData.mode = SH2_TITLE_DATA_MODE_3;
        return;
    }
    TitleSprChgColor->timer = TitleSprChgColor->cycle;
    titleDrawTitle();
    if (title_test_mode != TITLE_TEST_MODE_US) {
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
        if (title_test_mode == TITLE_TEST_MODE_US) {
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
        TitleData.mode = SH2_TITLE_DATA_MODE_5;
    }
    if (TitleData.timer > 0.0f) {
        TitleData.mode = SH2_TITLE_DATA_MODE_6;
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
    titleChangeColor(TitleSpr[0].rgba, TitleSprChgColor->start_rgba, TitleSprChgColor->end_rgba, TitleSprChgColor->timer, TitleSprChgColor->cycle, 0.5f);
    titleDrawSprite(-257, -103, 0);
}

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/Event/title", titleDrawSprite);
#endif

#line 2058
static void titleDrawMainMenu(void) {
    short cpos[8], cposy[8];   // r29+64, r29+80
    int i, j;           // r16, r17
    short ef_pos[7], w[7]; // r29+96, r29+112

    if (title_test_mode == TITLE_TEST_MODE_US) {
        cpos[0]  = -94;
        cpos[1]  = -86;
        cpos[2]  = -70;
        cpos[3]  = -78;
        cposy[0] = 77;
        cposy[1] = 99;
        cposy[2] = 121;
        cposy[3] = 143;
    } else {
        if (title_test_mode == TITLE_TEST_MODE_JP) {
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
    }


























    
    if (title_test_mode == TITLE_TEST_MODE_US) {
        ef_pos[0] = -80;
        ef_pos[1] = -71;
        ef_pos[2] = -50;
        ef_pos[3] = -60;
        w[0]      = 160;
        w[1]      = 142;
        w[2]      = 100;
        w[3]      = 120;
    } else {
        if (title_test_mode == TITLE_TEST_MODE_JP) {
            ef_pos[0] = -48;
            ef_pos[1] = -78;
            ef_pos[2] = -80;
            ef_pos[3] = -71;
            ef_pos[4] = -58;
            ef_pos[5] = -50;
            ef_pos[6] = -42;
            ef_pos[7] = -60; // @weird writing out of bounds??
            w[0]      = 96;
            w[1]      = 156;
            w[2]      = 160;
            w[3]      = 142;
            w[4]      = 116;
            w[5]      = 100;
            w[6]      = 84; 
            w[7]      = 120; // @weird writing out of bounds??
        } else {

            ef_pos[0] = -48;
            ef_pos[1] = -78;
            ef_pos[2] = -80;
            ef_pos[3] = -60;
            w[0]      = 96;
            w[1]      = 156;
            w[2]      = 160;
            w[3]      = 120;
        }
    }
    
    titleChangeSpriteColor2(11);
    TitleSpr[11].w = w[TitleData.sel - 1] + 8;
    titleDrawSprite((ef_pos[TitleData.sel - 1] - 4), cposy[TitleData.sel - 1] + 1, 11);
    
    
    
    
    
    if (title_test_mode == TITLE_TEST_MODE_US) {
    
        
        titleDrawSprite(-96, cposy[0], 3);
        
        titleDrawSprite(-96, cposy[1], 14);
        titleDrawSprite(-99, cposy[2], 13);
        
        
        
        titleChangeCursorSpriteColor();

        
        titleDrawSprite(cpos[TitleData.sel - 1], cposy[TitleData.sel - 1], 12);
    } else {
            if (title_test_mode == TITLE_TEST_MODE_JP) {
            for (i = 0; i < 2; i++) {
                if (TitleData.menu[i + 1] == -1) continue;
                    
                j = TitleData.menu[i + 1] - 1;
                
                
                titleDrawSprite(-96, cposy[i], j + 1);
            }
                
            titleDrawSprite(-96, cposy[2], 3);
            titleDrawSprite(-96, cposy[3], 14);
            titleDrawSprite(-96, cposy[4], 16);
            titleDrawSprite(-99, cposy[5], 13);
            titleDrawSprite(-96, cposy[6], 15);
            titleDrawSprite(-96, cposy[7], 4);
            
                
                
            titleChangeCursorSpriteColor();
            
                
            titleDrawSprite(cpos[TitleData.sel - 1], cposy[TitleData.sel - 1], 12);
            return;
        }
        
        for (i = 0; i < 4; i++) {
            
            if (TitleData.menu[i + 1] == -1) continue;

            j = TitleData.menu[i + 1] - 1;

        
            titleDrawSprite(-96, cposy[i], j + 1);
            if (TitleData.sel == (i + 1)) {
                
                
                
                
                titleChangeCursorSpriteColor();
                
                
                titleDrawSprite(cpos[j], cposy[i], 12);
            }
        }
    }

}

static void titleDrawSubMenu(int sel) {
    int i; // r4

    titleDrawSprite(-196, 60, 5);
    titleDrawSprite(11, 60, 6);
    if (sel == 0) {
        short x_pos; // r29+0x2A
        TitleSpr[11].h -= 7;
        titleChangeSpriteColor2(11);
        titleGetMenuEfctPosBattle(&x_pos, &TitleSpr[11].w, TitleData.sel);
        titleDrawSprite(x_pos, ((TitleData.sel * 18) + 66), 11);
        TitleSpr[11].h += 7;
        titleDrawSprite(-196, 80, 7);
        titleDrawSprite(-196, 98, 8);
        titleDrawSprite(-196, 115, 9);
        titleDrawSprite(11, 80, 7);
        titleDrawSprite(11, 98, 8);
        titleDrawSprite(11, 115, 9);
        titleChangeCursorSpriteColor();
        titleDrawSprite(titleGetCursorXPosBattle(TitleData.sel), TitleData.sel * 18 + 62, 12);
        return;
    }
    if (sel == 1) {
        short x_pos; // r29+0x2C
        TitleSpr[11].h -= 7;
        titleChangeSpriteColor2(11);
        titleGetMenuEfctPosRiddle(&x_pos, &TitleSpr[11].w, TitleData.sel);
        titleDrawSprite(x_pos, TitleData.sel * 18 + 66, 11);
        TitleSpr[11].h += 7;
        titleDrawSprite(11, 80, 7);
        titleDrawSprite(11, 98, 8);
        titleDrawSprite(11, 115, 9);
        switch (playing.battle_level) {
            case 1:                    
                titleDrawSprite(-196, 115, 9);
                break;
            case 2:
                titleDrawSprite(-196, 98, 8);
                break;
            case 3:
                titleDrawSprite(-196, 80, 7);
                break;
        }
        {
            short x_pos; // r29+0x2E
            for (i = 0; i < 4; i++) {
                TitleSpr[11].rgba[i] = TitleSprChgColor[11].end_rgba[i];
            }
            TitleSpr[11].h -= 7;
            titleGetMenuEfctPosBattle(&x_pos, &TitleSpr[11].w, titleGetCursorFromBattleLevel(playing.battle_level));
            titleDrawSprite(x_pos, (titleGetCursorFromBattleLevel(playing.battle_level) * 18) + 66, 11);
            TitleSpr[11].h += 7;
            titleChangeCursorSpriteColor();
            titleDrawSprite(titleGetCursorXPosRiddle(TitleData.sel), (TitleData.sel * 18) + 62, 12);
            return;
        }
    }
    switch (playing.battle_level) {
        case SH2_BATTLE_LEVEL_EASY:                    
            titleDrawSprite(-196, 115, 9);
            break;
        case SH2_BATTLE_LEVEL_NORMAL:
            titleDrawSprite(-196, 98, 8);
            break;
        case SH2_BATTLE_LEVEL_HARD:
            titleDrawSprite(-196, 80, 7);
            break;
    }
    switch (playing.riddle_level) {
        case SH2_RIDDLE_LEVEL_EASY:                    
            titleDrawSprite(11, 115, 9);
            return;
        case SH2_RIDDLE_LEVEL_NORMAL:
            titleDrawSprite(11, 98, 8);
            return;
        case SH2_RIDDLE_LEVEL_HARD:
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
            ASSERT_ON_LINE(0, 2608);
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

#ifdef NON_MATCHING
#line 2977
// really silly register issue?
static void titleChangeColor(int* rgba /* r20 */, int* start_rgba /* r19 */, int* end_rgba /* r18 */, float timer /* r29+128 */, float cycle_time /* r29+128 */, float cycle_sin /* r29+128 */) {
    sceVu0IVECTOR diff_color; // r29+112
    float ratio;              // r20
    int i;                    // r16

    
    ratio = shSinF(PI * (cycle_sin * (timer / cycle_time)));

    for (i = 0; i < 4; i++) {
        diff_color[i] = end_rgba[i] - start_rgba[i];
        rgba[i]       = start_rgba[i] + (diff_color[i] * ratio);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/title", titleChangeColor);
#endif

int GameendMain(void) {
    static float game_over_timer; // @ 18274584
    PicDraw_Data pic;             // r29+16

    switch (Sh2sys.step[4]) { /* irregular */
        case 0:
            FcRead(data_pic_etc_comingsoon_tex, TitleData.pload0);
            sh2sys_step_4();
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
                    picture_set_ap(&pic, TitleData.pload0);
                    pic.otp = 1;
                    PictureDraw(&pic);
                    d1cSend(spkDmaKick());
                    game_over_timer += shGetDT();
                    if ((shPadTrigger(0, key_config.action) != 0) || (shPadTrigger(0, key_config.cancel) != 0) || game_over_timer > 5.0f) {
                        return 1;
                    }
                    goto block_14;
            }
        block_14:
        default:
            return 0;
    }
}

OPD_W opd_w[6];  // size: 312, address: 18274272
OPD_W org_title; // size: 52, address: 18274208

static void opd_work_init(void) {
    int loop; // r3

    bzero(opd_w, sizeof(opd_w));
    bzero(&org_title, sizeof(org_title));

    for (loop = 0; loop < 2; loop++) {
        opd_w[loop].u0 = 0.0f;
        opd_w[loop].u1 = 160.0f;
        opd_w[loop].v0 = (loop + 1) * 48;
        opd_w[loop].v1 = 47.0f + opd_w[loop].v0;
        opd_w[loop].x0 = -80.0f;
        opd_w[loop].x1 = 80.0f;
        opd_w[loop].y0 = -24.0f;
        opd_w[loop].y1 = 47.0f + opd_w[loop].y0;
        opd_w[loop + 2] = opd_w[loop];
        opd_w[loop + 4] = opd_w[loop];
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
    static float game_over_timer;
    static int fid;

    switch (Sh2sys.step[4]) { /* irregular */
        case 0:
            game_over_timer = 0.0f;
            sh2sys_step_4();
            /* fallthrough */
        case 1:
            fontClear();
            fid = FcRead(data_pic_etc_gameover1_tex, get_gp_data_buf_addr());
            game_over_timer = 0.0f;
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
            break;

        case 3:
            return 1;
    }
    return 0;
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

    switch (org_title.step) { /* irregular */
        case 0:
            org_title.timer++;
            if (org_title.timer == 32) {
                org_title.step++;
                org_title.timer = 0;
            }
            break;
        default:
            break;
        case 1:
            org_title.rgb += 4;
            if (org_title.rgb == 96) {
                org_title.step++;
            }
            break;
        case 2:
            org_title.timer++;
            if (org_title.timer == 64) {
                org_title.step++;
                org_title.timer = 0;
            }
            break;
        case 3:
            org_title.rgb -= 8;
            if (org_title.rgb == 0) {
                org_title.step++;
            }
            break;
        case 4:
            return 1;
    }

    PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
    shQzero(&pic, sizeof(PicDraw_Data));
    picture_set_ap(&pic, get_gp_data_buf_addr());
    pic.otp       = 1;
    picture_set_alpha(&pic, 128);
    for (loop = 0; loop < 6; loop++) {
        rnd = (rand() % 30) - 15;
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
        pic.y0 = q4(rnd + opd_w[loop].y0);
        pic.x1 = q4(opd_w[loop].x1);
        pic.y1 = q4(rnd + opd_w[loop].y1);
        pic.status |= 2;
        PictureDraw(&pic);
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
    pic.status |= 2;
    PictureDraw(&pic);
    d1cSend(spkDmaKick());
    return 0;
}
