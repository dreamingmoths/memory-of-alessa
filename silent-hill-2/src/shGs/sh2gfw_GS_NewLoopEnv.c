#include "sh2gfw_GS_NewLoopEnv.h"

int sh2gfw_RotateTBuff(shGsAllEnv* shGsEnv)
{
    sceGsPutDispEnv(&shGsEnv->DispEnv[shGsEnv->loop3]);
    sh2gfw_setREF_gsctl((Q_WORDDATA *) &shGsEnv->DrawEnv[shGsEnv->loop3].giftag);
    sh2gfw_setREF_TEXFLUSH();

    return shGsEnv->loop3;
}

int sh2gfw_ReturnTBuff(shGsAllEnv* shGsEnv)
{
    sh2gfw_setREF_TEXFLUSH();
    sh2gfw_setREF_gsctl((Q_WORDDATA *) &shGsEnv->DrawEnv[shGsEnv->loop3].giftag_nc);
    sh2gfw_setREF_TEXFLUSH();

    return shGsEnv->loop3;
}

int sh2gfw_RotateNext2(shGsAllEnv* stdb)
{
    u_int idd[3] = {2, 0, 1}; // r29+0x20

    sh2gfw_setREF_TEXFLUSH();
    sh2gfw_setREF_gsctl((Q_WORDDATA *) &stdb->DrawEnv[idd[stdb->loop3]].giftag_nc);

    return stdb->loop3;
}

void sh2gfw_set_LoopDrawEnv(shGsAllEnv* stdb)
{
    stdb->Now_DrawEnv = stdb->DrawEnv[stdb->loop3];
}

u_long128* sh2gfw_Get_FrameNormalRegAddr(void)
{
    return (u_long128 *) &shGs_AllEnv.Now_DrawEnv.frame_normal;
}

u_long128* sh2gfw_Get_FrameAlphaRegAddr(void)
{
    return (u_long128 *) &shGs_AllEnv.Now_DrawEnv.frame_mskalpha;
}

void sh2gfw_StartShadowEnv(shGsAllEnv* stdb)
{
    sh2gfw_setREF_TEXFLUSH();
    sh2gfw_setREF_gsctl((Q_WORDDATA *) &stdb->StencilBuf[stdb->loop3].giftag);
    sh2gfw_setREF_TEXFLUSH();
}

u_int sh2gfw_GetStencilFBP(shGsAllEnv* stdb)
{
    return stdb->StencilBuf[stdb->loop3].draw.frame1.FBP;
}

u_int sh2gfw_GetFilterFBP(shGsAllEnv* stdb, u_int page)
{
    return stdb->StencilWork[stdb->loop3 * 2 + page].frame.ui32[0] & 0x1FF;
}

void sh2gfw_StartShadowFilter(shGsAllEnv* stdb, u_int page)
{
    sh2gfw_setREF_TEXFLUSH();
    sh2gfw_setREF_gsctl(&stdb->StencilWork[stdb->loop3 * 2 + page].giftag);
    sh2gfw_setREF_TEXFLUSH();
}

void sh2gfw_ChangeMask_ShadowFilter(shGsAllEnv* stdb, int mode, int pageno)
{
    u_int id = stdb->loop3 * 2; // r3

    switch (mode)
    {
        case 0:
            sh2gfw_setREF_gsctl(&stdb->StencilWork[id + pageno].gifad_normal);
            break;
        case 1:
            sh2gfw_setREF_gsctl(&stdb->StencilWork[id + pageno].gifad_mskalpha);
            break;
        default:
            sh2gfw_setREF_gsctl(&stdb->StencilWork[id + pageno].gifad_mskDalpha);
            break;
    }
}

void sh2gfw_ChangeClear_StencilBuf(shGsAllEnv* stdb, u_int r, u_int g, u_int b, u_int a)
{
    Q_WORDDATA* qwd = (Q_WORDDATA *) &stdb->StencilBuf[stdb->loop3].clear.rgbaq; // r9

    qwd->ui32[0] = r | (g << 8) | (b << 16) | (a << 24);
}

u_int sh2gfw_InclimentLoopCounter(shGsAllEnv* stdb)
{
    ++stdb->loop3;
    stdb->loop3 %= 3;
    ++stdb->loop_counter;
    ++stdb->loop;

    return stdb->loop;
}

u_int sh2gfw_DeclimentLoopCounter(shGsAllEnv* stdb)
{
    if (stdb->loop_counter != 0)
    {
        if (stdb->loop3 == 0) stdb->loop3 = 2;
        else --stdb->loop3;

        --stdb->loop_counter;
        --stdb->loop;
    }
    else
    {
        stdb->loop3 = 2;
        stdb->loop_counter = 2;
        stdb->loop = 2;
    }
}

int sh2gfw_ForceSet_MovieDrawLoopCounter(void)
{
    switch (shGs_AllEnv.loop3)
    {
        case 0:
            shGs_AllEnv.loop3 = 2;
            shGs_AllEnv.loop_counter += 2;
            shGs_AllEnv.loop += 2;

            return 0;
        case 1:
            shGs_AllEnv.loop3 = 2;
            ++shGs_AllEnv.loop_counter;
            ++shGs_AllEnv.loop;

            return 1;
        case 2:
            /* fallthrough */
        default:
            return 2;
    }
}

u_int sh2gfw_GetNowDispFBP(shGsAllEnv* stdb)
{
    return stdb->DispEnv[stdb->loop3].dispfb.FBP;
}

u_int sh2gfw_GetTexTBP0(shGsAllEnv* stdb, u_int page)
{
    return stdb->LoopEnv.GsTexTBPs[stdb->loop3 * 8 + page];
}

u_int sh2gfw_GetSendingClutTBP0(shGsAllEnv* stdb, u_int page)
{
    return stdb->LoopEnv.GsClutPage[page];
}

u_int sh2gfw_Get_BaseTBP0for2D(void)
{
    return sh2gfw_GetTexTBP0(&shGs_AllEnv, 1);
}