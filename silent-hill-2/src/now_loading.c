#include "now_loading.h"

void NowLoadingEnable(void) {
    D_01F01DD0 = 1;
}

void NowLoadingCheck(void) {
    float temp_f20;
    int fade;
    int time;


    fade = scr_efct.fade_type;
    switch (fade) {
        case 2:
        case 1:
            temp_f20 = scr_efct.fade_timer_max;
            if ((int) temp_f20 < 4.0f) {
                if (ScreenEffectFadeCheck() != 0) {
                    time = scr_efct.fade_timer_now;
                    ScreenEffectInit();
                    ScreenEffectFadeStart(1, 4.0f);
                    scr_efct.fade_timer_now = (float) time;
                    scr_efct.fade_timer_max = 4.0f;
                }
            } else if (((fade != 2) || !(scr_efct.fade_timer_now < temp_f20)) && !(scr_efct.fade_timer_now < 4.0f)) {
                if ((temp_f20 != 4.0f) || (fade != 1)) {
                    ScreenEffectInit();
                    ScreenEffectFadeStart(1, 4.0f);
                    scr_efct.fade_timer_now = 0.0f;
                    scr_efct.fade_timer_max = 4.0f;
                } else if (D_01F01DD0 != 0) {
                    D_01F01DD8 = 1;
                }
            }    
            break;
        default:
            break;
    }
    D_01F01DD0 = 0;
}

void NowLoadingDraw(void) {

    int y; // r16
    int x; // r17
    int count; // @ 0x01F01DE0 : count

    int var_v1;

    if (D_01F01DD8 != 0) {
        var_v1 = D_01F01DE0 & 0x3F;
        if ((D_01F01DE0 < 0) && (var_v1 != 0)) {
            var_v1 -= 0x40;
        }
        if (var_v1 == 0) {
            y = ((D_01F01DE0 * 0x2F6F) % 5) - 2;
            x = ((D_01F01DE0 * 0xCE5FDD) % 5) - 2;
            sh2gfw_InclimentLoopCounter(&shGs_AllEnv);
            fontSetColorDirect(0x80, 0x80, 0x80, 0x80);
            fontPrintStr(dicSetStr("\\c\\hNow loading"), x + 0x100, y + 0x100);
            fjFontDrawExecVif1();
            fontClear();
            sh2gfw_DeclimentLoopCounter(&shGs_AllEnv);
        }
        D_01F01DE0 += 1;
    } else {
        D_01F01DE0 = 0;
    }
    D_01F01DD8 = 0;
}
