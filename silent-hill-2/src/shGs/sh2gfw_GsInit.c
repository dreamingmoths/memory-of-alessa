#include "sh2gfw_GsInit.h"

#pragma divbyzerocheck off

#define SH2GFW_ENV_COUNT 3

void shGs_InitDefTBuff(shGsAllEnv* shGsEnv, short draw_psm, short disp_psm, short w, short h, short ztest, short zpsm)
{
    u_int i; // r16

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsSetDefTBuffDispEnv(&shGsEnv->DispEnv[i], disp_psm, w, h, 0, 0);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsSetDefTBuffDrawEnv(&shGsEnv->DrawEnv[i].draw, draw_psm, w, h, ztest, zpsm);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        sceGsSetDefClear(&shGsEnv->DrawEnv[i].clear, ztest, 2048 - (w >> 1), 2048 - (h >> 1), w, h, 0, 0, 0, 0, 0);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        SCE_GIF_CLEAR_TAG(&shGsEnv->DrawEnv[i].giftag);

        shGsEnv->DrawEnv[i].giftag.NLOOP = 19;
        shGsEnv->DrawEnv[i].giftag.EOP = SCE_GS_TRUE;
        shGsEnv->DrawEnv[i].giftag.NREG = 1;
        shGsEnv->DrawEnv[i].giftag.REGS0 = SCE_GIF_PACKED_AD;
        shGsEnv->DrawEnv[i].giftag_nc = shGsEnv->DrawEnv[i].giftag;

        shGsEnv->DrawEnv[i].giftag_nc.NLOOP = 13;
        shGsEnv->DrawEnv[i].draw_nc = shGsEnv->DrawEnv[i].draw;
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsEnv->DispEnv[i].dispfb.FBP = shGsEnv->LoopEnv.GsNowDispFBPs[i];
        shGsEnv->DrawEnv[i].draw.frame1.FBP = shGsEnv->LoopEnv.GsDrawFBPs[i];
        shGsEnv->DrawEnv[i].draw_nc.frame1.FBP = shGsEnv->LoopEnv.GsDrawFBPs[i];

        shGsEnv->DrawEnv[i].gifad_frame_normal.ui32[3] = 0;
        shGsEnv->DrawEnv[i].gifad_frame_normal.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
        shGsEnv->DrawEnv[i].gifad_frame_normal.ui32[1] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        ) >> 32;
        shGsEnv->DrawEnv[i].gifad_frame_normal.ui32[0] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        );

        shGsEnv->DrawEnv[i].frame_normal.ui32[0] =
            shGsEnv->DrawEnv[i].draw.frame1.PSM << GS_FRAME_PSM_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBW << GS_FRAME_FBW_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBP << GS_FRAME_FBP_O;
        shGsEnv->DrawEnv[i].frame_normal.ui32[1] = 0;
        shGsEnv->DrawEnv[i].frame_normal.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->DrawEnv[i].gifad_frame_mskalpha = shGsEnv->DrawEnv[i].gifad_frame_normal;

        shGsEnv->DrawEnv[i].frame_mskalpha.ui32[0] =
            shGsEnv->DrawEnv[i].draw.frame1.PSM << GS_FRAME_PSM_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBW << GS_FRAME_FBW_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBP << GS_FRAME_FBP_O;
        shGsEnv->DrawEnv[i].frame_mskalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 255);
        shGsEnv->DrawEnv[i].frame_mskalpha.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->DrawEnv[i].gifad_frame_mskDalpha = shGsEnv->DrawEnv[i].gifad_frame_normal;

        shGsEnv->DrawEnv[i].frame_mskDalpha.ui32[0] =
            shGsEnv->DrawEnv[i].draw.frame1.PSM << GS_FRAME_PSM_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBW << GS_FRAME_FBW_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBP << GS_FRAME_FBP_O;
        shGsEnv->DrawEnv[i].frame_mskDalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 128);
        shGsEnv->DrawEnv[i].frame_mskDalpha.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->DrawEnv[i].gifad_frame_mskRGB = shGsEnv->DrawEnv[i].gifad_frame_normal;

        shGsEnv->DrawEnv[i].frame_mskRGB.ui32[0] =
            shGsEnv->DrawEnv[i].draw.frame1.PSM << GS_FRAME_PSM_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBW << GS_FRAME_FBW_O |
            shGsEnv->DrawEnv[i].draw.frame1.FBP << GS_FRAME_FBP_O;
        shGsEnv->DrawEnv[i].frame_mskRGB.ui32[1] = COLOR_RGBA(255, 255, 255, 0);
        shGsEnv->DrawEnv[i].frame_mskRGB.ul64[1] = SCE_GS_FRAME_1;
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsEnv->DrawEnv[i].drawq2[0].ui32[0] =
            draw_psm << GS_FRAME_PSM_O |
            (w / 64) << GS_FRAME_FBW_O |
            shGsEnv->LoopEnv.GsDrawFBPs[i] << GS_FRAME_FBP_O;
        shGsEnv->DrawEnv[i].drawq2[0].ui32[1] = 0;
        shGsEnv->DrawEnv[i].drawq2[0].ul64[1] = SCE_GS_FRAME_2;

        shGsEnv->DrawEnv[i].drawq2[1].ul64[1] = SCE_GS_ZBUF_2;
        shGsEnv->DrawEnv[i].drawq2[1].ul64[0] =
            (u_long) (zpsm & 0xF) << GS_ZBUF_PSM_O |
            (u_long) SCE_GS_TRUE << GS_ZBUF_ZMSK_O |
            (u_long) 448 << GS_ZBUF_ZBP_O;

        shGsEnv->DrawEnv[i].drawq2[2].ul64[1] = SCE_GS_XYOFFSET_2;
        shGsEnv->DrawEnv[i].drawq2[2].ul64[0] = ((Q_WORDDATA *) &shGsEnv->DrawEnv[i].draw.xyoffset1)->ul64[0];

        shGsEnv->DrawEnv[i].drawq2[3].ul64[1] = SCE_GS_SCISSOR_2;
        shGsEnv->DrawEnv[i].drawq2[3].ul64[0] = ((Q_WORDDATA *) &shGsEnv->DrawEnv[i].draw.scissor1)->ul64[0];

        shGsEnv->DrawEnv[i].drawq2[4].ul64[1] = SCE_GS_TEST_2;
        shGsEnv->DrawEnv[i].drawq2[4].ul64[0] = ((Q_WORDDATA *) &shGsEnv->DrawEnv[i].draw.test1)->ul64[0];

        shGsEnv->DrawEnv[i].drawq2_nc[0] = shGsEnv->DrawEnv[i].drawq2[0];
        shGsEnv->DrawEnv[i].drawq2_nc[1] = shGsEnv->DrawEnv[i].drawq2[1];
        shGsEnv->DrawEnv[i].drawq2_nc[2] = shGsEnv->DrawEnv[i].drawq2[2];
        shGsEnv->DrawEnv[i].drawq2_nc[3] = shGsEnv->DrawEnv[i].drawq2[3];
        shGsEnv->DrawEnv[i].drawq2_nc[4] = shGsEnv->DrawEnv[i].drawq2[4];
    }
}

void shGs_TrimDispArea(int xx, int yy)
{
    int i; // r3

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGs_AllEnv.DispEnv[i].dispfb.DBX += xx;
        shGs_AllEnv.DispEnv[i].dispfb.DBY += yy;
    }
}

void shGs_SetDefaultDispArea(void)
{
    int i; // r7

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGs_AllEnv.DispEnv[i].dispfb.DBX = 0;
        shGs_AllEnv.DispEnv[i].dispfb.DBY = 32;
    }
}

void shGsSetDefTBuffDispEnv(sceGsDispEnv* disp, short psm, short w, short h, short dx, short dy)
{
    if ((w % 64) != 0)
    {
        printf("sceGsSetDefDispEnv:The value of w is incorrect\n");
    }
    else
    {
        *(u_long *) &disp->pmode = SCE_GS_SET_PMODE(SCE_GS_FALSE, SCE_GS_TRUE, 1, 1, 1, SCE_GS_FALSE, 0);

        if (sceGsGetGParam()->sceGsInterMode != SCE_GS_NOINTERLACE)
        {
            if (sceGsGetGParam()->sceGsFFMode != SCE_GS_FIELD)
            {
                *(u_long *) &disp->smode2 = SCE_GS_SET_SMODE2(SCE_GS_INTERLACE, SCE_GS_FRAME, 0);
            }
            else
            {
                *(u_long *) &disp->smode2 = SCE_GS_SET_SMODE2(SCE_GS_INTERLACE, SCE_GS_FIELD, 0);
            }
        }
        else
        {
            *(u_long *) &disp->smode2 = SCE_GS_SET_SMODE2(SCE_GS_NOINTERLACE, SCE_GS_FRAME, 0);
        }

        if (sceGsGetGParam()->sceGsOutMode == SCE_GS_NTSC)
        {
            *(u_long *) &disp->dispfb =
                ((u_long) psm & 0xF) << GS_DISPFB2_PSM_O |
                (u_long) ((w >> 6) & 0x3F) << GS_DISPFB2_FBW_O;
            disp->dispfb.DBY = 32;
        }
        else
        {
            *(u_long *) &disp->dispfb =
                ((u_long) psm & 0xF) << GS_DISPFB2_PSM_O |
                (u_long) ((w >> 6) & 0x3F) << GS_DISPFB2_FBW_O;
            disp->dispfb.DBY = 0;
        }

        if (sceGsGetGParam()->sceGsOutMode == SCE_GS_NTSC)
        {
            if (sceGsGetGParam()->sceGsInterMode == SCE_GS_INTERLACE)
            {
                *(u_long *) &disp->display =
                    (u_long) ((h - 64) * 2 - 1) << GS_DISPLAY2_DH_O |
                    (u_long) ((w + 2559) / w - 1) << GS_DISPLAY2_MAGH_O |
                    (((u_long) (dx * (2560 / w)) + 0x28C) & 0xFFF) << GS_DISPLAY2_DX_O |
                    (u_long) ((dy + 50) & 0xFFF) << GS_DISPLAY2_DY_O |
                    (u_long) 2559 << GS_DISPLAY2_DW_O;
            }
            else
            {
                *(u_long *) &disp->display =
                    (u_long) ((w + 2559) / w - 1) << GS_DISPLAY2_MAGH_O |
                    (u_long) (h - 1) << GS_DISPLAY2_DH_O |
                    (((u_long) (dx * (2560 / w)) + 0x28C) & 0xFFF) << GS_DISPLAY2_DX_O |
                    (u_long) ((dy + 25) & 0xFFF) << GS_DISPLAY2_DY_O |
                    (u_long) 2559 << GS_DISPLAY2_DW_O;
            }
        }
        else
        {
            printf("sceGsDefDispEnv:Not support displaymode except for NTSC yet!!\n\0");
        }

        *(u_long *) &disp->bgcolor = SCE_GS_SET_BGCOLOR(0, 0, 0);
    }
}

int shGsSetDefTBuffDrawEnv(sceGsDrawEnv1* draw, short psm, short w, short h, short ztest, short zpsm)
{
    u_int zb;

    draw->frame1addr = SCE_GS_FRAME_1;
    *(u_long *) &draw->frame1 = SCE_GS_SET_FRAME_1(0, (w >> 6) & 0x3F, psm & 0xF, 0);

    draw->zbuf1addr = SCE_GS_ZBUF_1;

    zb = 512 - ((zpsm & 2) != 0 ? 64 : 128);

    if (ztest == 0)
    {
        *(u_long *) &draw->zbuf1 = SCE_GS_SET_ZBUF_1(zb, zpsm & 0xF, SCE_GS_TRUE);
    }
    else
    {
        *(u_long *) &draw->zbuf1 = SCE_GS_SET_ZBUF_1(zb, zpsm & 0xF, SCE_GS_FALSE);
    }

    draw->xyoffset1addr = SCE_GS_XYOFFSET_1;
    *(u_long *) &draw->xyoffset1 = SCE_GS_SET_XYOFFSET_1((2048L - (w >> 1)) * 16, (2048L - (h >> 1)) * 16);

    draw->scissor1addr = SCE_GS_SCISSOR_1;
    *(u_long *) &draw->scissor1 = SCE_GS_SET_SCISSOR_1(0, w - 1, 0, h - 1);

    draw->prmodecontaddr = SCE_GS_PRMODECONT;
    draw->prmodecont.AC = SCE_GS_TRUE;

    draw->colclampaddr = SCE_GS_COLCLAMP;
    draw->colclamp.CLAMP = SCE_GS_TRUE;

    draw->dtheaddr = SCE_GS_DTHE;

    if ((psm & 2) != 0) draw->dthe.DTHE = SCE_GS_TRUE;
    else draw->dthe.DTHE = SCE_GS_FALSE;

    draw->test1addr = SCE_GS_TEST_1;

    if (ztest)
    {
        *(u_long *) &draw->test1 = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, ztest & 3);
    }
    else
    {
        *(u_long *) &draw->test1 = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_FALSE, SCE_GS_ZNOUSE);
    }

    asm volatile("sync.l");

    return 8;
}

void shGs_InitGsStencilBuff(shGsAllEnv* shGsEnv, short w, short h, short ztest, short zpsm)
{
    u_int i; // r18

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGs_InitStencilDrawEnv(&shGsEnv->StencilBuf[i], w, h, ztest, zpsm);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        sceGsSetDefClear(&shGsEnv->StencilBuf[i].clear, ztest, 2048 - (w >> 1), 2048 - (h >> 1), w, h, 128, 128, 128, 0, 0);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        SCE_GIF_CLEAR_TAG(&shGsEnv->StencilBuf[i].giftag);

        shGsEnv->StencilBuf[i].giftag.NLOOP = 22;
        shGsEnv->StencilBuf[i].giftag.EOP = SCE_GS_TRUE;
        shGsEnv->StencilBuf[i].giftag.NREG = 1;
        shGsEnv->StencilBuf[i].giftag.REGS0 = SCE_GIF_PACKED_AD;
        shGsEnv->StencilBuf[i].giftag_nc = shGsEnv->StencilBuf[i].giftag;

        shGsEnv->StencilBuf[i].giftag_nc.NLOOP = 15;
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsEnv->StencilBuf[i].draw.frame1.FBP = shGsEnv->LoopEnv.GsShadowFBP[i];
        shGsEnv->StencilBuf[i].draw_nc.frame1.FBP = shGsEnv->LoopEnv.GsShadowFBP[i];

        shGsEnv->StencilBuf[i].frame.ui32[0] =
            (w / 64) << GS_FRAME_FBW_O |
            SCE_GS_PSMCT16S << GS_FRAME_PSM_O |
            shGsEnv->LoopEnv.GsShadowFBP[i] << GS_FRAME_FBP_O;
        shGsEnv->StencilBuf[i].frame.ui32[1] = COLOR_RGBA(0, 0, 0, 255);
        shGsEnv->StencilBuf[i].frame.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->StencilBuf[i].gifad_frame_normal.ui32[3] = 0;
        shGsEnv->StencilBuf[i].gifad_frame_normal.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
        shGsEnv->StencilBuf[i].gifad_frame_normal.ui32[1] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        ) >> 32;
        shGsEnv->StencilBuf[i].gifad_frame_normal.ui32[0] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        );
        shGsEnv->StencilBuf[i].frame_normal = shGsEnv->StencilBuf[i].frame;
        shGsEnv->StencilBuf[i].frame_normal.ui32[1] = 0;

        shGsEnv->StencilBuf[i].gifad_frame_mskalpha.ui32[3] = 0;
        shGsEnv->StencilBuf[i].gifad_frame_mskalpha.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
        shGsEnv->StencilBuf[i].gifad_frame_mskalpha.ui32[1] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        ) >> 32;
        shGsEnv->StencilBuf[i].gifad_frame_mskalpha.ui32[0] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        );
        shGsEnv->StencilBuf[i].frame_mskalpha = shGsEnv->StencilBuf[i].frame;

        shGsEnv->StencilBuf[i].gifad_frame_mskDalpha.ui32[3] = 0;
        shGsEnv->StencilBuf[i].gifad_frame_mskDalpha.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
        shGsEnv->StencilBuf[i].gifad_frame_mskDalpha.ui32[1] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        ) >> 32;
        shGsEnv->StencilBuf[i].gifad_frame_mskDalpha.ui32[0] = SCE_GIF_SET_TAG(
            1,
            SCE_GS_TRUE,
            SCE_GS_FALSE,
            0,
            SCE_GIF_PACKED,
            1
        );
        shGsEnv->StencilBuf[i].frame_mskDalpha = shGsEnv->StencilBuf[i].frame;
        shGsEnv->StencilBuf[i].frame_mskDalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 128);
    }

    for (i = 0; i < SH2GFW_ENV_COUNT; i++)
    {
        shGsEnv->StencilBuf[i].alpha1.ul64[1] = SCE_GS_ALPHA_1;
        shGsEnv->StencilBuf[i].alpha1.ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);
        shGsEnv->StencilBuf[i].alpha1_nc = shGsEnv->StencilBuf[i].alpha1;

        shGsEnv->StencilBuf[i].drawq2[0].ul64[1] = SCE_GS_FRAME_2;
        shGsEnv->StencilBuf[i].drawq2[0].ul64[0] = shGsEnv->StencilBuf[i].frame.ul64[0];

        shGsEnv->StencilBuf[i].drawq2[1].ul64[1] = SCE_GS_ZBUF_2;
        shGsEnv->StencilBuf[i].drawq2[1].ul64[0] = ((Q_WORDDATA *) &shGsEnv->StencilBuf[i].draw.zbuf1)->ul64[0];

        shGsEnv->StencilBuf[i].drawq2[2].ul64[1] = SCE_GS_XYOFFSET_2;
        shGsEnv->StencilBuf[i].drawq2[2].ul64[0] = ((Q_WORDDATA *) &shGsEnv->StencilBuf[i].draw.xyoffset1)->ul64[0];

        shGsEnv->StencilBuf[i].drawq2[3].ul64[1] = SCE_GS_SCISSOR_2;
        shGsEnv->StencilBuf[i].drawq2[3].ul64[0] = ((Q_WORDDATA *) &shGsEnv->StencilBuf[i].draw.scissor1)->ul64[0];

        shGsEnv->StencilBuf[i].drawq2[4].ul64[1] = SCE_GS_ALPHA_2;
        shGsEnv->StencilBuf[i].drawq2[4].ul64[0] = SCE_GS_SET_ALPHA_2(SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_CS, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);

        shGsEnv->StencilBuf[i].drawq2[5].ul64[1] = SCE_GS_TEST_2;
        shGsEnv->StencilBuf[i].drawq2[5].ul64[0] = ((Q_WORDDATA *) &shGsEnv->StencilBuf[i].draw.test1)->ul64[0];

        shGsEnv->StencilBuf[i].alpha1_nc = shGsEnv->StencilBuf[i].alpha1;

        shGsEnv->StencilBuf[i].drawq2_nc[0] = shGsEnv->StencilBuf[i].drawq2[0];
        shGsEnv->StencilBuf[i].drawq2_nc[1] = shGsEnv->StencilBuf[i].drawq2[1];
        shGsEnv->StencilBuf[i].drawq2_nc[2] = shGsEnv->StencilBuf[i].drawq2[2];
        shGsEnv->StencilBuf[i].drawq2_nc[3] = shGsEnv->StencilBuf[i].drawq2[3];
        shGsEnv->StencilBuf[i].drawq2_nc[4] = shGsEnv->StencilBuf[i].drawq2[4];
        shGsEnv->StencilBuf[i].drawq2_nc[5] = shGsEnv->StencilBuf[i].drawq2[5];
    }
}

int shGs_InitStencilDrawEnv(shGsStencilDrawEnv* ssb, short w, short h, short ztest, short zpsm)
{
    u_int zb;

    ssb->draw.frame1addr = SCE_GS_FRAME_1;
    *(u_long *) &ssb->draw.frame1 = SCE_GS_SET_FRAME_1(0, (w >> 6) & 0x3F, SCE_GS_PSMCT16S, 0);

    ssb->draw.zbuf1addr = SCE_GS_ZBUF_1;
    *(u_long *) &ssb->draw.zbuf1 = SCE_GS_SET_ZBUF_1(zb = 448, zpsm & 0xF, SCE_GS_TRUE);

    ssb->draw.xyoffset1addr = SCE_GS_XYOFFSET_1;
    *(u_long *) &ssb->draw.xyoffset1 = SCE_GS_SET_XYOFFSET_1((2048L - (w >> 1)) * 16, (2048L - (h >> 1)) * 16);

    ssb->draw.scissor1addr = SCE_GS_SCISSOR_1;
    *(u_long *) &ssb->draw.scissor1 = SCE_GS_SET_SCISSOR_1(0, w - 1, 0, h - 1);

    ssb->draw.prmodecontaddr = SCE_GS_PRMODECONT;
    ssb->draw.prmodecont.AC = SCE_GS_TRUE;

    ssb->draw.colclampaddr = SCE_GS_COLCLAMP;
    ssb->draw.colclamp.CLAMP = SCE_GS_TRUE;

    ssb->draw.dtheaddr = SCE_GS_DTHE;
    ssb->draw.dthe.DTHE = SCE_GS_FALSE;

    ssb->draw.test1addr = SCE_GS_TEST_1;
    *(u_long *) &ssb->draw.test1 = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, ztest & 3);

    asm volatile("sync.l");

    return 8;
}

void shGs_InitGsTinyStencilBuff(shGsAllEnv* shGsEnv, short w, short h)
{
    u_int fbp; // r9
    u_int i;   // r3

    shGsEnv->StencilWork[0].giftag.ui32[3] = 0;
    shGsEnv->StencilWork[0].giftag.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->StencilWork[0].giftag.ui32[1] = SCE_GIF_SET_TAG(
        5,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->StencilWork[0].giftag.ui32[0] = SCE_GIF_SET_TAG(
        5,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );

    shGsEnv->StencilWork[0].frame.ui32[0] = (w >> 6) << GS_FRAME_FBW_O;
    shGsEnv->StencilWork[0].frame.ui32[1] = 0;
    shGsEnv->StencilWork[0].frame.ul64[1] = SCE_GS_FRAME_1;

    shGsEnv->StencilWork[0].scissor.ul64[0] = SCE_GS_SET_SCISSOR_1(0, w - 1, 0, h - 1);
    shGsEnv->StencilWork[0].scissor.ul64[1] = SCE_GS_SCISSOR_1;

    shGsEnv->StencilWork[0].xyoffset.ul64[1] = SCE_GS_XYOFFSET_1;
    shGsEnv->StencilWork[0].xyoffset.ul64[0] = SCE_GS_SET_XYOFFSET_1((2048L - (w >> 1)) * 16, (2048L - (h >> 1)) * 16);

    shGsEnv->StencilWork[0].zbuf.ul64[1] = SCE_GS_ZBUF_1;
    shGsEnv->StencilWork[0].zbuf.ul64[0] = SCE_GS_SET_ZBUF_1(448, SCE_GS_PSMCT16S, SCE_GS_TRUE);

    shGsEnv->StencilWork[0].test.ul64[1] = SCE_GS_TEST_1;
    shGsEnv->StencilWork[0].test.ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 1, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    shGsEnv->StencilWork[0].gifad_normal.ui32[3] = 0;
    shGsEnv->StencilWork[0].gifad_normal.ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->StencilWork[0].gifad_normal.ui32[1] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->StencilWork[0].gifad_normal.ui32[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );
    shGsEnv->StencilWork[0].frame_normal = shGsEnv->StencilWork[0].frame;

    shGsEnv->StencilWork[0].gifad_mskalpha = shGsEnv->StencilWork[0].gifad_normal;
    shGsEnv->StencilWork[0].frame_mskalpha = shGsEnv->StencilWork[0].frame;
    shGsEnv->StencilWork[0].frame_mskalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 255);

    shGsEnv->StencilWork[0].gifad_mskDalpha = shGsEnv->StencilWork[0].gifad_normal;
    shGsEnv->StencilWork[0].frame_mskDalpha = shGsEnv->StencilWork[0].frame;
    shGsEnv->StencilWork[0].frame_mskDalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 128);

    for (i = 1; i < 6; i++)
    {
        shGsEnv->StencilWork[i] = shGsEnv->StencilWork[0];
    }

    for (i = 0; i < 6; i += 2)
    {
        fbp = shGsEnv->DispEnv[(i / 2 + 1) % 3].dispfb.FBP + 64;

        shGsEnv->StencilWork[i].frame.ui32[0] =
            (w >> 6) << GS_FRAME_FBW_O |
            fbp << GS_FRAME_FBP_O;
        shGsEnv->StencilWork[i].frame.ui32[1] = 0;
        shGsEnv->StencilWork[i].frame.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->StencilWork[i + 1].frame.ui32[0] =
            (w >> 6) << GS_FRAME_FBW_O |
            (fbp + 32) << GS_FRAME_FBP_O;
        shGsEnv->StencilWork[i + 1].frame.ui32[1] = 0;
        shGsEnv->StencilWork[i + 1].frame.ul64[1] = SCE_GS_FRAME_1;

        shGsEnv->StencilWork[i].frame_normal = shGsEnv->StencilWork[i].frame;
        shGsEnv->StencilWork[i + 1].frame_normal = shGsEnv->StencilWork[i + 1].frame;

        shGsEnv->StencilWork[i].frame_mskalpha = shGsEnv->StencilWork[i].frame;
        shGsEnv->StencilWork[i].frame_mskalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 255);
        shGsEnv->StencilWork[i + 1].frame_mskalpha = shGsEnv->StencilWork[i + 1].frame;
        shGsEnv->StencilWork[i + 1].frame_mskalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 255);

        shGsEnv->StencilWork[i].frame_mskDalpha = shGsEnv->StencilWork[i].frame;
        shGsEnv->StencilWork[i].frame_mskDalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 128);
        shGsEnv->StencilWork[i + 1].frame_mskDalpha = shGsEnv->StencilWork[i + 1].frame;
        shGsEnv->StencilWork[i + 1].frame_mskDalpha.ui32[1] = COLOR_RGBA(0, 0, 0, 128);
    }
}

void shGs_InitDefaultRegsEnv(shGsAllEnv* shGsEnv)
{
    u_int i;
    Q_WORDDATA* qwd;

    shGsEnv->DefaultEnv[1].ul64[1] = SCE_GS_ALPHA_1;
    shGsEnv->DefaultEnv[1].ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_CD, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);

    shGsEnv->DefaultEnv[2].ul64[1] = SCE_GS_TEST_1;
    shGsEnv->DefaultEnv[2].ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_TRUE, SCE_GS_ALPHA_GREATER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGEQUAL);

    shGsEnv->DefaultEnv[3].ul64[1] = SCE_GS_CLAMP_1;
    shGsEnv->DefaultEnv[3].ul64[0] = SCE_GS_SET_CLAMP_1(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);

    shGsEnv->DefaultEnv[4].ul64[1] = SCE_GS_COLCLAMP;
    shGsEnv->DefaultEnv[4].ul64[0] = SCE_GS_SET_COLCLAMP(SCE_GS_TRUE);

    shGsEnv->DefaultEnv[5].ul64[1] = SCE_GS_ZBUF_1;
    shGsEnv->DefaultEnv[5].ul64[0] = SCE_GS_SET_ZBUF_1(448, SCE_GS_PSMZ16S, SCE_GS_FALSE);

    shGsEnv->DefaultEnv[6].ul64[0] = SCE_GS_SET_TEX1_1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    shGsEnv->DefaultEnv[6].ul64[1] = SCE_GS_TEX1_1;

    shGsEnv->DefaultEnv[7].ul64[1] = SCE_GS_FOGCOL;
    shGsEnv->DefaultEnv[7].ul64[0] = SCE_GS_SET_FOGCOL(0, 0, 0);

    shGsEnv->DefaultEnv[8].ul64[1] = SCE_GS_TEXA;
    shGsEnv->DefaultEnv[8].ul64[0] = SCE_GS_SET_TEXA(64, 0, 128);

    shGsEnv->DefaultEnv[0].ui32[3] = 0;
    shGsEnv->DefaultEnv[0].ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->DefaultEnv[0].ui32[1] = SCE_GIF_SET_TAG(
        9,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->DefaultEnv[0].ui32[0] = SCE_GIF_SET_TAG(
        9,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );

    shGsEnv->StencilEnv[1].ul64[1] = SCE_GS_ALPHA_1;
    shGsEnv->StencilEnv[1].ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_CS, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);

    shGsEnv->StencilEnv[2].ul64[1] = SCE_GS_TEST_1;
    shGsEnv->StencilEnv[2].ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);

    shGsEnv->StencilEnv[0].ui32[3] = 0;
    shGsEnv->StencilEnv[0].ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->StencilEnv[0].ui32[1] = SCE_GIF_SET_TAG(
        2,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->StencilEnv[0].ui32[0] = SCE_GIF_SET_TAG(
        2,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );

    shGsEnv->GsReg_ALPHA_A[0].ui32[3] = 0;
    shGsEnv->GsReg_ALPHA_A[0].ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->GsReg_ALPHA_A[0].ui32[1] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->GsReg_ALPHA_A[0].ui32[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );
    shGsEnv->GsReg_ALPHA_A[1] = shGsEnv->DefaultEnv[1];

    qwd = &shGsEnv->GsReg_ALPHA_A[0];

    for (i = 2; i < 10; i += 2)
    {
        qwd[i] = qwd[0];
        qwd[i + 1] = qwd[1];
    }

    shGsEnv->GsReg_ALPHA_B[1].ul64[1] = SCE_GS_ALPHA_1;
    shGsEnv->GsReg_ALPHA_B[1].ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);

    shGsEnv->GsReg_ALPHA_C[1].ul64[1] = SCE_GS_ALPHA_1;
    shGsEnv->GsReg_ALPHA_C[1].ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_CS, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);

    shGsEnv->GsReg_ALPHA_D[1].ul64[1] = SCE_GS_ALPHA_1;
    shGsEnv->GsReg_ALPHA_D[1].ul64[0] = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_ZERO, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_ZERO, 0);

    shGsEnv->GsReg_TEST_A[0] = shGsEnv->GsReg_ALPHA_A[0];
    shGsEnv->GsReg_TEST_A[1] = shGsEnv->DefaultEnv[2];

    qwd = &shGsEnv->GsReg_TEST_A[0];

    for (i = 2; i < 10; i += 2)
    {
        qwd[i] = qwd[0];
        qwd[i + 1] = qwd[1];
    }

    shGsEnv->GsReg_TEST_B[1].ul64[1] = SCE_GS_TEST_1;
    shGsEnv->GsReg_TEST_B[1].ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 1, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    shGsEnv->GsReg_TEST_C[1].ul64[1] = SCE_GS_TEST_1;
    shGsEnv->GsReg_TEST_C[1].ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_TRUE, 1, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    shGsEnv->GsReg_TEST_D[1].ul64[1] = SCE_GS_TEST_1;
    shGsEnv->GsReg_TEST_D[1].ul64[0] = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_TRUE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    shGsEnv->GsReg_FBA_A[0] = shGsEnv->GsReg_TEST_A[0];
    shGsEnv->GsReg_FBA_A[1].ul64[1] = SCE_GS_FBA_1;
    shGsEnv->GsReg_FBA_A[1].ul64[0] = SCE_GS_SET_FBA_1(SCE_GS_FALSE);

    shGsEnv->GsReg_FBA_B[0] = shGsEnv->GsReg_TEST_A[0];
    shGsEnv->GsReg_FBA_B[1].ul64[1] = SCE_GS_FBA_1;
    shGsEnv->GsReg_FBA_B[1].ul64[0] = SCE_GS_SET_FBA_1(SCE_GS_TRUE);

    shGsEnv->GsReg_TEXA_A[0] = shGsEnv->GsReg_TEST_A[0];
    shGsEnv->GsReg_TEXA_A[1].ul64[1] = SCE_GS_TEXA;
    shGsEnv->GsReg_TEXA_A[1].ul64[0] = SCE_GS_SET_TEXA(128, 1, 0);

    qwd = &shGsEnv->GsReg_TEXA_A[0];

    for (i = 2; i < 4; i += 2)
    {
        qwd[i] = qwd[0];
        qwd[i + 1] = qwd[1];
    }

    shGsEnv->GsReg_TEXA_B[1].ul64[1] = SCE_GS_TEXA;
    shGsEnv->GsReg_TEXA_B[1].ul64[0] = SCE_GS_SET_TEXA(128, 0, 0);

    shGsEnv->GsReg_ZBUF_A[0] = shGsEnv->GsReg_TEXA_A[0];
    shGsEnv->GsReg_ZBUF_A[1] = shGsEnv->DefaultEnv[5];

    shGsEnv->GsReg_ZBUF_B[0] = shGsEnv->GsReg_ZBUF_A[0];
    shGsEnv->GsReg_ZBUF_B[1].ul64[1] = SCE_GS_ZBUF_1;
    shGsEnv->GsReg_ZBUF_B[1].ul64[0] = SCE_GS_SET_ZBUF_1(448, SCE_GS_PSMCT16S, SCE_GS_TRUE);

    shGsEnv->GsSync_DummyLABEL[0].ui32[3] = 0;
    shGsEnv->GsSync_DummyLABEL[0].ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->GsSync_DummyLABEL[0].ui32[1] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->GsSync_DummyLABEL[0].ui32[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );
    shGsEnv->GsSync_DummyLABEL[1].ul64[1] = SCE_GS_LABEL;
    shGsEnv->GsSync_DummyLABEL[1].ui32[1] = 0;
    shGsEnv->GsSync_DummyLABEL[1].ui32[0] = 0;

    shGsEnv->GsSync_DummyTEXFLUSH[0].ui32[3] = 0;
    shGsEnv->GsSync_DummyTEXFLUSH[0].ui32[2] = GIF_REG(SCE_GIF_PACKED_AD, 0);
    shGsEnv->GsSync_DummyTEXFLUSH[0].ui32[1] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    ) >> 32;
    shGsEnv->GsSync_DummyTEXFLUSH[0].ui32[0] = SCE_GIF_SET_TAG(
        1,
        SCE_GS_TRUE,
        SCE_GS_FALSE,
        0,
        SCE_GIF_PACKED,
        1
    );
    shGsEnv->GsSync_DummyTEXFLUSH[1].ul64[1] = SCE_GS_TEXFLUSH;
    shGsEnv->GsSync_DummyTEXFLUSH[1].ul64[0] = 0;
}