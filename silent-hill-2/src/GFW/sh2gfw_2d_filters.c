#include "sh2_common.h"
#include "SH2_common/sh2dt.h"

#include "Event/event.h"

#include "sh2gfw_2d_filters.h"

#define SH2_GS_FILTER_KIND_BLUR 2
#define SH2_GS_FILTER_KIND_GLOW_BLUR 3
#define SH2_GS_FILTER_KIND_DARK_BLUR 4
#define SH2_GS_FILTER_KIND_SWAP_SOFT 5
#define SH2_GS_FILTER_KIND_GLOW_SOFT_6 6
#define SH2_GS_FILTER_KIND_GLOW_SOFT_7 7
#define SH2_GS_FILTER_KIND_SWAP_SOFT_8 8
#define SH2_GS_FILTER_KIND_SWAP_SOFT_9 9
#define SH2_GS_FILTER_KIND_SWAP_SOFT_10 10
#define SH2_GS_FILTER_KIND_FADE2_COLOR1 14
#define SH2_GS_FILTER_KIND_FADE2_COLOR0 15
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2 16
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1 17
#define SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0 18
#define SH2_GS_FILTER_KIND_FADE2_19 19
#define SH2_GS_FILTER_KIND_FADE2_20 20
#define SH2_GS_FILTER_KIND_FADE3 21
#define SH2_GS_FILTER_KIND_COPY_AND_RESET 22
#define SH2_GS_FILTER_KIND_RETAIN 23

// @todo: how did they write this?
#define SH2_FIO_RATIO 4.269999980926514

static void sh2gfw_Copy_FrameToWork(Q_WORDDATA** ppqwd);

extern double fabs(double);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Copy_FrameToWork);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Filter_JustCopy2);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Filter_Blur);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Filter_Dark_Blur);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Filter_Glow_Blur);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_test_MakeNoise);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Black_Clear);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_SendDraw_Noise);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Swap_Soft);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Swap_GlowSoft);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_FadeOut_Retain);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Filter_Retain);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Fade2);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Fade3);

void sh2gfw_Set_FadeOutRetain_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOut_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_COLOR1;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeOutRetain_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOutRetain_Red(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = 10.0f * ra;
    pfp->FO_timer = 0;
}

void sh2gfw_Set_FadeOut_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_COLOR0;
    shGsFilterWork.mode = shGsFilterWork.GsFilterKind;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_Black(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_19;
    shGsFilterWork.mode = 19;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_White(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE2_20;
    shGsFilterWork.mode = 20;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FadeIn_Red(float ra) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_FADE3;
    shGsFilterWork.mode = 21;

    pfp->FIO_ratio = SH2_FIO_RATIO * fabs(ra);
    pfp->TargetSec = ra;
    pfp->FO_timer = 0;
    pfp->Max_Timer = ra * shGetFPS();
}

void sh2gfw_Set_FilterBlur(int rt) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_BLUR;
    pfp->blurRatio = (s8) rt;
}

void sh2gfw_Set_PauseRetain(void) {
    if (shGsFilterWork.GsFilterKind != SH2_GS_FILTER_KIND_RETAIN) {
        sh2gfw_Get_FilterCommandParams();

        shGsFilterWork.Kind_History = shGsFilterWork.GsFilterKind;
        shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_RETAIN;
    }
}

void sh2gfw_Reset_PauseRetain(void) {
    if (shGsFilterWork.GsFilterKind == SH2_GS_FILTER_KIND_RETAIN) {
        sh2gfw_Get_FilterCommandParams();

        shGsFilterWork.GsFilterKind = shGsFilterWork.Kind_History;
        shGsFilterWork.Kind_History = SH2_GS_FILTER_KIND_RETAIN;
    }
}

void sh2gfw_Reset_FilterCommand(void) {
    int mm; // r16
    int kk; // r17
    int ss; // r18
    FilterParams* pfp; // r19

    mm = shGsFilterWork.mode;
    kk = shGsFilterWork.GsFilterKind;
    pfp = sh2gfw_Get_FilterCommandParams();
    ss = pfp->sw_flg;

    memset(&shGsFilterWork, 0, sizeof(shGsFilterWork));
    shGsFilterWork.mode = mm;
    shGsFilterWork.Kind_History = kk;
    pfp->sw_flg = ss;
}

int sh2gfw_Get_FilterCommand(void) {
    return shGsFilterWork.GsFilterKind;
}

void* sh2gfw_Get_FilterCommandParams(void) {
    return shGsFilterWork.FilterData;
}

int sh2gfw_Set_CaptureNowFB(void) {
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    shGsFilterWork.GsFilterKind = SH2_GS_FILTER_KIND_COPY_AND_RESET;
    pfp->sw_flg = 1;

    return 0x3400;
}

void Exec_PostDraw_OVfunc(void) {
    if (stage == NULL) return;
    if (stage->gfw_func == NULL) return;
    if (stage->gfw_func->PostDraw == NULL) return;
    stage->gfw_func->PostDraw();
}

int Check_Filter_Soft(void) {
    if (shGsFilterWork.GsFilterKind >= SH2_GS_FILTER_KIND_SWAP_SOFT && shGsFilterWork.GsFilterKind <= SH2_GS_FILTER_KIND_SWAP_SOFT_10) {
        return !shGsFilterWork.mode;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", DemoFadeDraw2);

void Make_Filter_Packet(void* pb) {
    Q_WORDDATA* qwd = pb;
    FilterParams* pfp = sh2gfw_Get_FilterCommandParams();

    if (pfp->sw_flg != 0) {
        d2sSync(0, -1);
        d1sSync(0, -1);
        sh2gfw_Copy_FrameToWork(&qwd);
        pfp->sw_flg = 0;
    }

    switch (shGsFilterWork.GsFilterKind) {
        case SH2_GS_FILTER_KIND_SWAP_SOFT:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_Soft(&qwd, pfp->SoftIter, 0x80, pfp->SoftShift, pfp->SoftAref, pfp->SoftCit, 0);
            break;

        case SH2_GS_FILTER_KIND_GLOW_SOFT_6:
        case SH2_GS_FILTER_KIND_GLOW_SOFT_7:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_GlowSoft(&qwd, pfp->SoftIter, pfp->SoftCit, pfp->SoftAref, pfp->SoftShift);
            break;

        default:
            sh2gfw_Filter_JustCopy2(&qwd);
            break;

        case SH2_GS_FILTER_KIND_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Blur(&qwd, (u_char) pfp->blurRatio);
            break;

        case SH2_GS_FILTER_KIND_GLOW_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Glow_Blur(&qwd, (u_char) (pfp->GreaterA + 224), (u_char) pfp->blurRatio, 0);
            break;

        case SH2_GS_FILTER_KIND_DARK_BLUR:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Filter_Dark_Blur(&qwd, (u_char) pfp->blurRatio, (u_char) (pfp->LesserA + 127));
            break;

        case SH2_GS_FILTER_KIND_FADE2_COLOR1:
            sh2gfw_Fade2(&qwd, 0, 1, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW1:
            sh2gfw_FadeOut_Retain(&qwd, 1);
            break;

        case SH2_GS_FILTER_KIND_FADE2_COLOR0:
            sh2gfw_Fade2(&qwd, 0, 0, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW0:
            sh2gfw_FadeOut_Retain(&qwd, 0);
            break;

        case SH2_GS_FILTER_KIND_FADEOUT_RETAIN_BORW2:
            sh2gfw_FadeOut_Retain(&qwd, 2);
            break;

        case SH2_GS_FILTER_KIND_FADE2_19:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            sh2gfw_Fade2(&qwd, 1, 1, 0);
            break;

        case SH2_GS_FILTER_KIND_FADE2_20:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            sh2gfw_Fade2(&qwd, 1, 0, 0);
            break;

        case SH2_GS_FILTER_KIND_FADE3:
            pfp->base_Ix = 0;
            pfp->base_Iy = 0;
            {   
                sceVu0IVECTOR col = {255, 0, 0, 0};
                sh2gfw_Fade3(&qwd, 1, col);
            }
            break;

        case SH2_GS_FILTER_KIND_RETAIN:
            sh2gfw_Filter_Retain(&qwd);
            break;

        case SH2_GS_FILTER_KIND_SWAP_SOFT_8:
        case SH2_GS_FILTER_KIND_SWAP_SOFT_9:
        case SH2_GS_FILTER_KIND_SWAP_SOFT_10:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Swap_Soft(&qwd, pfp->S1_iter, 128, pfp->S1_shift, pfp->S1_alpha, pfp->KeyAlpha + pfp->TrimAlpha, 1);
            sh2gfw_Swap_Soft(&qwd, pfp->S2_iter, 128, pfp->S2_shift, pfp->S2_alpha, pfp->KeyAlpha + pfp->TrimAlpha, 2);
            break;

        case SH2_GS_FILTER_KIND_COPY_AND_RESET:
            sh2gfw_Filter_JustCopy2(&qwd);
            qwd--;
            sh2gfw_Reset_FilterCommand();
            break;
    }

    if (shGsFilterWork.mode >= SH2_GS_FILTER_KIND_FADE2_19            && 
        shGsFilterWork.mode <= SH2_GS_FILTER_KIND_FADE3               && 
        shGsFilterWork.GsFilterKind < SH2_GS_FILTER_KIND_FADE2_COLOR1 && 
        shGsFilterWork.GsFilterKind != 0
    ) {
        switch (shGsFilterWork.mode) {
            case SH2_GS_FILTER_KIND_FADE2_19:
                sh2gfw_Fade2(&qwd, 1, 1, 1);
                return;

            case SH2_GS_FILTER_KIND_FADE2_20:
                sh2gfw_Fade2(&qwd, 1, 0, 1);
                return;

            case SH2_GS_FILTER_KIND_FADE3: {
                sceVu0IVECTOR col = {255, 0, 0, 0};
                sh2gfw_Fade3(&qwd, 1, col);
                break;
            }
        }
    }
}
