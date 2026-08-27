#include "sh2_common.h"

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

static void sh2gfw_Copy_FrameToWork(Q_WORDDATA** ppqwd);

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

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeOutRetain_Black);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeOut_Black);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeOutRetain_White);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeOutRetain_Red);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeOut_White);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeIn_Black);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeIn_White);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FadeIn_Red);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_FilterBlur);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_PauseRetain);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Reset_PauseRetain);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Reset_FilterCommand);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Get_FilterCommand);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Get_FilterCommandParams);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", sh2gfw_Set_CaptureNowFB);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", Exec_PostDraw_OVfunc);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", Check_Filter_Soft);

INCLUDE_ASM("asm/nonmatchings/GFW/sh2gfw_2d_filters", DemoFadeDraw2);

void Make_Filter_Packet(void* pb) {
    Q_WORDDATA* qwd = (Q_WORDDATA*) pb;
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

    if (shGsFilterWork.mode >= 19 && shGsFilterWork.mode < 22 && shGsFilterWork.GsFilterKind < 14 && shGsFilterWork.GsFilterKind != 0) {
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
