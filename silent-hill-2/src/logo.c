#include "sh2_common.h"
#include "SH2_common/sh2sys.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/pad.h"

#include "gs.h"
#include "gamemain.h"
#include "logo.h"

#include "sce/libgraph.h"

#include "shared/Font/font.h"

#include "Event/event.h"
#include "Event/picture.h"

#include "sound/sh_sound.h"

#include "Effect/screen_effect.h"

#include "MC/mc.h"

#include "Fog/spack.h"

#include "data/daily.thu/data_pic_etc.h"

static int logoTellYesNo(void);
static void logoDrawTexture(void);

// @note foward declaration required for match
extern u_short* fontGetMesAdr(u_short*, int);

static int logoDispTimer;
static PicDraw_Data Pic0;

void logoCheckingMemcard(void) {
    static int msg_fid;
    static short msg_id;
    int sts;

    switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
        case 0:
            msg_fid = DataLoadMessage(4);
            ScreenEffectInit();
            sh2sys_step_2();
            return;
        case 1:
            if (fsSync(1, msg_fid) >= 0) {

                msg_id = 0;
                mcInit();
                sh2sys_step_2();
            }
            break;

        case 2:
            sts = mcStartCheck();
            fontClear();
            if (msg_id == 74 || msg_id == 75) {
                int t = sts - 2;

                if (t == 0 || t == 1 || t == 2) {
                    fontPrintWord(fontGetMesAdr(msg_buffer, msg_id), 256, 240, 1, 1);
                }
            } else if (msg_id == 44) {
                fontSetColor(FontColorBlue);
                fontPrintWord(fontGetMesAdr(msg_buffer, msg_id), 256, 240, 1, 1);
                if (--logoDispTimer <= 0 || shPadTrigger(0, key_config.enter)) {
                    sh2sys_set_2(3);
                    break;
                }
            } else if (msg_id) {
                fontSetColor(FontColorBlue);
                fontPrintWord(fontGetMesAdr(msg_buffer, msg_id), 256, 112, 1, 0);
                if (sts == 0 && mcw->menu_yesno) {
                    switch (logoTellYesNo()) {
                        case 1:
                            sh2sys_set_2(3);
                            return;
                        case 2:
                            mcStepInit();
                            break;
                    }
                }
            }

            switch (sts) {
                case 1:
                    sh2sys_set_2(3);
                    return;
                case 2:
                    msg_id = 74;
                    return;
                case 3:
                    msg_id = 75;
                    return;
                case 4:
                    fontPrintWord(fontGetMesAdr(msg_buffer, 76), 256, 320, 1, 1);
                    mcStepInit();
                    ExtGameData();
                    Sh2sys.main_status |= 32;
                    sh2sys_set_2(4);
                    return;
                case -2:
                    msg_id          = 51;
                    mcw->menu_yesno = 2;
                    return;
                case -1:
                    msg_id          = 52;
                    mcw->menu_yesno = 2;
                    return;
                case -3:
                    msg_id        = 44;
                    logoDispTimer = (int) (3.0f * shGetFPS());
                    return;
            }
            break;
        case 3:
            if (Sh2sys.step[SH2SYS_CONNECT] == 1) {
                fontClear();
                ScreenEffectFadeStart(1, 0.3f);
            }
            if (Sh2sys.step[SH2SYS_CONNECT] < 2) {
                sh2sys_step_3();
                return;
            }
            if (ScreenEffectFadeCheck()) {
                sh2sys_set_1(5);
                return;
            }
            break;
        case 4:
            if (Sh2sys.step[SH2SYS_CONNECT] == 1) {
                fontClear();
                SeCall(SH2_SOUND_15002, 1.0f, 0);
                ScreenEffectFadeStart(1, 3.0f);
            }
            if (Sh2sys.step[SH2SYS_CONNECT] < 2) {
                sh2sys_step_3();
                return;
            }
            if (ScreenEffectFadeCheck()) {
                sh2sys_set_1(13);
                sh2sys_set_2(1);
            }
            break;
    }
}

void logoDrawWarningCESA(void) {
    static int fid;
    static int wait_loop;
    switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
        case 0:
            fontClear();
            ScreenEffectInit();
            ScreenEffectFadeStart(3, 0.0f);
            fid       = FcRead(data_pic_etc_cesa_tex, get_gp_data_buf_addr());
            wait_loop = 0;
            Sh2sys.step[SH2SYS_PLAYABLE_MAIN]++;
            sh2sys_set_3(0);
            return;
        case 1:
            wait_loop++;
            switch (fsSync(1, fid)) {
                case 1:
                    ScreenEffectFadeStart(4, 0.3f);
                    logoDrawTexture();
                    DEBUG_LOG_ON_LINE(388, "title.tex: read finished(%d.%02d)\n", wait_loop / 60, (wait_loop % 60 * 100) / 60);
                    Sh2sys.step[SH2SYS_PLAYABLE_MAIN]++;
                    sh2sys_set_3(0);
                    return;
                case 0:
                    DEBUG_LOG_ON_LINE(393, "!!! illegal fid=%d\n", fid);
                    return;
                case -1:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(397, "title.tex: now reading(%d.)...\n", wait_loop / 60);
                        break;
                    }
                    break;
                case -2:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(402, "title.tex: now waiting(%d.)...\n", wait_loop / 60);
                        return;
                    }
                    break;
                default:
                    DEBUG_LOG_ON_LINE(406, "illegal return value\n");
                    return;
            }
            break;
        case 2:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                logoDispTimer = (int) (3.0f * shGetFPS());
                Sh2sys.step[SH2SYS_PLAYABLE_MAIN]++;
                sh2sys_set_3(0);
                return;
            }
            break;
        case 3:
            logoDrawTexture();
            logoDispTimer--;
            if (logoDispTimer <= 0) {
                ScreenEffectFadeStart(1, 0.3f);
                Sh2sys.step[SH2SYS_PLAYABLE_MAIN]++;
                sh2sys_set_3(0);
                return;
            }
            break;
        case 4:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                Sh2sys.step[SH2SYS_GAME_MAIN]++;
                sh2sys_set_2(0);
            }
            break;
    }
}
void logoDrawWarningSCE(void) {
    static int fid;
    static int wait_loop;
    switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
        case 0:
            ScreenEffectFadeStart(3, 0.0f);
            fid       = FcRead(data_pic_etc_sce_tex, get_gp_data_buf_addr());
            wait_loop = 0;
            sh2sys_step_2();
            return;
        case 1:
            wait_loop++;
            switch (fsSync(1, fid)) {
                case 1:
                    ScreenEffectFadeStart(4, 0.3f);
                    logoDrawTexture();
                    DEBUG_LOG_ON_LINE(494, "title.tex: read finished(%d.%02d)\n", wait_loop / 60, (wait_loop % 60 * 100) / 60);
                    sh2sys_step_2();
                    return;
                case 0:
                    DEBUG_LOG_ON_LINE(499, "!!! illegal fid=%d\n", fid);
                    return;
                case -1:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(503, "title.tex: now reading(%d.)...\n", wait_loop / 60);
                        break;
                    }
                    break;
                case -2:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(508, "title.tex: now waiting(%d.)...\n", wait_loop / 60);
                        return;
                    }
                    break;
                default:
                    DEBUG_LOG_ON_LINE(512, "illegal return value\n");
                    return;
            }
            break;
        case 2:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                logoDispTimer = (int) (3.0f * shGetFPS());
                sh2sys_step_2();
                return;
            }
            break;
        case 3:
            logoDrawTexture();
            logoDispTimer--;
            if (logoDispTimer <= 0) {
                ScreenEffectFadeStart(2, 0.3f);
                sh2sys_step_2();
                return;
            }
            break;
        case 4:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                sh2sys_step_1();
            }
            break;
    }
}

void logoDrawKonamiLogo(void) {
    static int fid;
    static int wait_loop;
    switch (Sh2sys.step[SH2SYS_PLAYABLE_MAIN]) {
        case 0:
            ScreenEffectFadeStart(3, 0.0f);
            fid       = FcRead(data_pic_etc_konami_r_tex, get_gp_data_buf_addr());
            wait_loop = 0;
            sh2sys_step_2();
            return;
        case 1:
            wait_loop++;
            switch (fsSync(1, fid)) {
                case 1:
                    ScreenEffectFadeStart(4, 0.3f);
                    logoDrawTexture();
                    DEBUG_LOG_ON_LINE(607, "title.tex: read finished(%d.%02d)\n", wait_loop / 60, (wait_loop % 60 * 100) / 60);
                    sh2sys_step_2();
                    return;
                case 0:
                    DEBUG_LOG_ON_LINE(612, "!!! illegal fid=%d\n", fid);
                    return;
                case -1:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(616, "title.tex: now reading(%d.)...\n", wait_loop / 60);
                        return;
                    }
                    break;
                case -2:
                    if (wait_loop % 60 == 0) {
                        DEBUG_LOG_ON_LINE(621, "title.tex: now waiting(%d.)...\n", wait_loop / 60);
                        return;
                    }
                    break;
                default:
                    DEBUG_LOG_ON_LINE(625, "illegal return value\n");
                    return;
            }
            break;
        case 2:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                logoDispTimer = (int) (3.0f * shGetFPS());
                sh2sys_step_2();
                return;
            }
            break;
        case 3:
            logoDrawTexture();
            logoDispTimer--;
            if (logoDispTimer <= 0) {
                ScreenEffectFadeStart(2, 0.3f);
                sh2sys_step_2();
                return;
            }
            break;
        case 4:
            logoDrawTexture();
            if (ScreenEffectFadeCheck()) {
                sh2sys_step_1();
            }
            break;
    }
}

static void logoDrawTexture(void) {
    spkResetOT();
    PictureLoadImage(get_gp_data_buf_addr(), 0, -1, -1);
    shQzero(&Pic0, sizeof(Pic0));
    Pic0.ap   = get_gp_data_buf_addr();
    Pic0.tex  = -1;
    Pic0.clut = -1;
    Pic0.status |= 1;
    Pic0.otp = 0;
    PictureDraw(&Pic0);
    d1cSend(spkDmaKick());
}

static int logoTellYesNo(void) {
#define LOGO_XY_COORD(x, y) ((2048 - (SCREEN_WIDTH) / 2 + (x)) << 4) | ((u_long) (2048 - (SCREEN_HEIGHT) / 2 + (y)) << 20)
    int x;
    int y;
    int a;
    int n;

    if ((mcw->menu_count += shGetDT()) > 1.0f) {
        mcw->menu_count -= 1.0f;
    }
    if (mcw->menu_count > 0.5f) {
        a = shFloatToInt(32.0f * ((1.0f - mcw->menu_count) / 0.5f));
    } else {
        a = shFloatToInt(32.0f * (mcw->menu_count / 0.5f));
    }

    y = 386;
    fontSetColor(FontColorGray);
    fontSetYesNo(y);

    if (shPadRepeat(0, PAD_KEY_DPAD_LEFT) || shPadRepeat(0, PAD_KEY_DPAD_RIGHT)) {
        SeCall(SH_SOUND_CHANGE_SELECTION_10000, 1.0f, 0);
        if (mcw->menu_yesno == 1) {
            mcw->menu_yesno = 2;
        } else {
            mcw->menu_yesno = 1;
        }
    }
    if (mcw->menu_yesno == 1) {
        x = 200;
    } else {
        x = 312;
    }
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 4), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ2), -65531, 0);
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
    (*spack.pos++) = COLOR_RGBA(128, 128, 32, a + 32);
    (*spack.pos++) = LOGO_XY_COORD(x + 24, y - 16);
    (*spack.pos++) = LOGO_XY_COORD(x + 104, y + 16);
    spkCloseGiftag();
    d1cSend(spkDmaKick());
    if (shPadTrigger(0, key_config.enter)) {
        n = mcw->menu_yesno;
        SeCall(SH_SOUND_ENTER_SELECTION_10002, 1.0f, 0);
        mcw->menu_yesno = 0;
        return n;
    }
    if (shPadTrigger(0, key_config.cancel)) {
        SeCall(SH_SOUND_CANCEL_SELECTION_10003, 1.0f, 0);
        mcw->menu_yesno = 0;
        return 2;
    }
    return 0;
}
