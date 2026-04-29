#include "Effect/screen_effect.h"
#include "GFW/sh2gfw_2d_filters.h"
#include "SH2_common/sh2dt.h"

void ScreenEffectInit(void) {
    scr_efct.fade_status = 0;
    scr_efct.fade_type = 0;
    scr_efct.fade_timer_max = 0;
    scr_efct.fade_timer_now = 0;
}

void ScreenEffectManager(void) {
    scr_efct.fade_timer_now += shGetDT();
    if (scr_efct.fade_timer_now >= scr_efct.fade_timer_max) {
        scr_efct.fade_timer_now = scr_efct.fade_timer_max;
        if (scr_efct.fade_status == 1)
            scr_efct.fade_status = 2;
        if (scr_efct.fade_status == 3)
            scr_efct.fade_status = 0;
    }
}

void ScreenEffectFadeStart(int type /* r2 */, float time /* r29+0x10 */) {
    if (time == 0.0f) {
        time = 1.2f;
    }

    switch (type) {
        case 0:
            break;
        case 1:
        case 2:
        case 6:
        case 7:
        case 11:
            if (1u >= scr_efct.fade_status - 1) {
                return;
            }
            scr_efct.fade_status = 1;
            break;
        case 3:
        case 8:
            if (scr_efct.fade_status == 2)
                return;
            scr_efct.fade_status = 2;
            break;
        case 4:
        case 9:
        case 12:
            if ((scr_efct.fade_status == 3 || scr_efct.fade_status == 0)) {
                return;
            }
            scr_efct.fade_status = 3;
            break;
        case 5:
        case 10:
            if (scr_efct.fade_status == 0) {
                return;
            }
            scr_efct.fade_status = 0;
            break;
    }

    scr_efct.fade_type = type;
    scr_efct.fade_timer_now = 0.0f;
    scr_efct.fade_timer_max = time;

    switch (type) {
        case 0:
            break;
        case 1:
            sh2gfw_Set_FadeOutRetain_Black(time);
            break;
        case 2:
            sh2gfw_Set_FadeOut_Black(time);
            break;
        case 3:
            sh2gfw_Set_FadeOut_Black(-1.0f);
            break;
        case 4:
            sh2gfw_Set_FadeIn_Black(time);
            break;
        case 5:
            sh2gfw_Set_FadeIn_Black(-1.0f);
            break;
        case 6:
            sh2gfw_Set_FadeOutRetain_White(time);
            break;
        case 7:
            sh2gfw_Set_FadeOut_White(time);
            break;
        case 8:
            sh2gfw_Set_FadeOut_White(-1.0f);
            break;
        case 9:
            sh2gfw_Set_FadeIn_White(time);
            break;
        case 10:
            sh2gfw_Set_FadeIn_White(-1.0f);
            break;
        case 11:
            sh2gfw_Set_FadeOutRetain_Red(time);
            break;
        case 12:
            sh2gfw_Set_FadeIn_Red(time);
            break;
        default:
            break;
    }
}

int ScreenEffectFadeCheck(void) {
    return scr_efct.fade_status == 0 || scr_efct.fade_status == 2;
}

void ScreenEffectFadeStop(void) {
    sh2gfw_Reset_FilterCommand();
    ScreenEffectInit();
}
