#include "common.h"
#include "Font/font.h"
#include "Font/fj_man.h"

INCLUDE_ASM("asm/nonmatchings/Font/font", func_00157D30);

void fontClear()
{
    font.w_st_num = 0;
    font.st_num = 0;
    fontSetColor(0);
    font.rgb_s[0] = 0;
    font.shadow_max = 1;
    font.unk20C0 = 0;
    font.shadow_now = 0;
    font.alpha_base = 0x80;
    font.alpha = 0x80;
    font.fonttype = 0;
    font.wait_type = 0;
    font.flag = font.flag & 0x70f8 | 1;
    fontSetStreamMax(0x200, 0x180, 0x200);
    *D_01D08FA0 = 0;
}

void fontSetStreamMax(u_short s_max, u_short ws_max, u_short ms_max)
{
    font.stream_max = s_max;
    font.w_stream_max = ws_max;
    font.m_stream_max = ms_max;

    font.stream = (FONT_STREAM_DATA *)(D_01D08FB0);
    font.w_stream = (WFONT_STREAM_DATA *)(font.stream + s_max);
    font.m_stream = (MFONT_STREAM_DATA *)(font.w_stream + ws_max);

    fjAssert(
        ((u32)(font.m_stream + ms_max) - (u32)font_stream_buf) <= FONT_STREAM_BUFFER_SIZE,
        "font.c",
        0x129);
}


INCLUDE_ASM("asm/nonmatchings/Font/font", fontLoad);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontGetData);

void fontSet(u_short code, u_short x, u_short y)
{
    int num;

    // this check isn't in sh2:
    if (func_0019B580(0x10u) != 0)
    {
        y = (y - 0x800) * 8 / 7 + 0x800;
    }

    // uses 0x800, not 0x400
    if (font.flag & 0x800)
    {
        WFONT_STREAM_DATA *fstream;

        if (font.w_st_num >= font.w_stream_max)
        {
            debugPrintf("wfont over.\n");
            return;
        }

        num = fontLoad(code);
        fstream = font.w_stream + font.w_st_num;
        fstream->x = x << 4;
        fstream->y = y << 4;
        fstream->u = (num % 0x19) * 0x14;
        fstream->v = (num / 0x19) * 0x1e;
        fstream->rgb_u = font.rgb_u | font.alpha << 0x18;
        fstream->rgb_d = font.rgb_d | font.shadow_now << 0x18;
        fstream->w = D_003585A8[font.fonttype][0] << 4;
        fstream->h = D_003585AA[font.fonttype][0] << 4;
        fstream->vw = font.wide_w << 4;
        fstream->vh = font.wide_h << 4;
        font.w_st_num++;
    }
    else
    {
        FONT_STREAM_DATA *fstream;
        if (font.st_num >= font.stream_max)
        {
            debugPrintf("font over.\n");
            return;
        }
        num = fontLoad(code);
        fstream = font.stream + font.st_num;
        fstream->x = x << 4;
        fstream->y = y << 4;
        fstream->u = (num % 0x19) * 0x14;
        fstream->v = (num / 0x19) * 0x1e;
        fstream->rgb_u = font.rgb_u | font.alpha << 0x18;
        fstream->rgb_d = font.rgb_d | font.shadow_now << 0x18;
        fstream->w = D_003585A8[font.fonttype][0] << 4;
        fstream->h = D_003585AA[font.fonttype][0] << 4;
        font.st_num++;
    }
}


void fontSetBlankBox(int x0, int x1, int y)
{
    FONT_STREAM_DATA *fstream;
    if (font.st_num >= font.stream_max)
    {
        return;
    }

    // this check isn't in sh2:
    if (func_0019B580(0x10u) != 0)
    {
        y = (y - 0x800) * 8 / 7 + 0x800;
    }

    fstream = font.stream + font.st_num;
    fstream->x = x0 << 4;
    fstream->y = y << 4;
    fstream->u = x1 << 4;
    fstream->v = 0xfff7;
    fstream->rgb_u = font.rgb_u | font.alpha << 0x18;
    fstream->rgb_d = font.rgb_d | font.shadow_now << 0x18;
    fstream->h = D_003585AA[font.fonttype][0] << 4; // changed from 1 to 0 in sh3?
    font.st_num = font.st_num + 1;
}

void fontSetLine(int x, int w, int y)
{
    u_int b;
    u_int g;
    u_int r;
    FONT_STREAM_DATA *fstream;

    if (font.st_num >= font.stream_max)
    {
        debugPrintf("font over.\n");
        return;
    }

    // this check isn't in sh2:
    if (func_0019B580(0x10u) != 0)
    {
        y = (y - 0x800) * 8 / 7 + 0x800;
    }

    fstream = font.stream + font.st_num;
    fstream->x = x << 4;

    if (font.flag & 0x800)
    {
        fstream->y = (((y + font.wide_h / 2) >> 1) << 5);
    }
    else
    {
        // another 1 -> 0
        fstream->y = ((y + D_003585AA[font.fonttype][0] / 2) >> 1) << 5;
    }

    fstream->u = (x + w) * 0x10 - 1;
    fstream->v = 0xfe00;

    r = ((font.rgb_u & 0xff) + (font.rgb_d & 0xff)) >> 1;
    g = (((font.rgb_u >> 8) & 0xff) + ((font.rgb_d >> 8) & 0xff)) >> 1;
    b = (((font.rgb_u >> 16) & 0xff) + ((font.rgb_d >> 16) & 0xff)) >> 1;
    fstream->rgb_u =
        (b << 0x10) | (r | g << 8) |
        (font.alpha << 24);
    fstream->rgb_d = font.shadow_now;
    font.st_num++;
}


INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStr);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStrNum);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStrMain);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_00159C70);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_00159D10);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015A540);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetColor);

void fontSetColorDirect(u_char r, u_char g, u_char b, u_char alp)
{
    font.rgb_u = font.rgb_d = (b << 0x10) | (r | g << 8);
    font.alpha = alp;
}


INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015A9D0);

void fontSetAlpha(u_char alp)
{
    font.alpha = alp;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015AA10);

#ifdef NON_MATCHING
void fontBarBlink()
{
    if ((font.bar_blink += shGetDT()) >= 1.0f)
        font.bar_blink -= 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontBarBlink);
#endif

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlush);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlushNoSPR);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C310);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C410);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPutYesNoSelectBar);

void *fontTexLoad(int texadr, int clutadr)
{
    font_dma_data[0x04] =
        ((long)(int)texadr << 32) | (0x14080000ULL << 32);

    font_dma_data[0x14] =
        ((long)(int)clutadr << 32) | (0x00010000ULL << 32);

    font.tex0 =
        (long)(int)texadr |
        (0x00066542ULL << 16) |
        ((long)(int)clutadr << 37) |
        (0x20000000ULL << 32);

    return font_dma_data;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C9E0);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C9F0);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPreload);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015CEF0);

void func_0015CF10(u_short *dest, u_short *src) {
    u_short val;
    do {
        val = *src++;
        *dest++ = val;
    } while (val != 0xFFFF);
}

#ifdef NON_MATCHING
void fontPushButton()
{
    if (font.wait_type == 4) {
        font.st_num = 0;
        font.wait_type = 5;
        SeCall(1.0f, 0.0f, 0x2712);
        return;
    }
    if (((font.wait_type & 7u) != 2) && !(font.flag & 0x10)) {
        font.wait_count = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontPushButton);
#endif

#ifdef NON_MATCHING
void fontPushButton2()
{
    if (((font.wait_type & 7u) != 2) && !(font.flag & 0x10))
    {
        font.wait_count = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontPushButton2);
#endif

#ifdef NON_MATCHING
void fontSelectUp()
{
    if (font.wait_type == 4)
    {
        if (font.sel_max == -1)
        {
            font.sel_now = 0;
        }
        else
        {
            if (--font.sel_now < 0)
            {
                font.sel_now = font.sel_max - 1;
            }
        }
        SeCall(1.0f, 0.0f, 10000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectUp);
#endif


#ifdef NON_MATCHING
void fontSelectDown()
{
    if (font.wait_type == 4)
    {
        if (font.sel_max == -1)
        {
            font.sel_now = 1;
            return;
        }
        if (++font.sel_now >= font.sel_max)
        {
            font.sel_now = 0;
        }
        SeCall(1.0f, 0.0f, 10000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectDown);
#endif

#ifdef NON_MATCHING
u_short *fontGetMesAdr(u_short *str, u_short num)
{
    if (str == NULL)
    {
        return NULL;
    }
    if (num >= *str)
    {
        debugPrintf("message number over! (%d/%d)\n", num, *str);
        return NULL;
    }
    return str + str[num + 1];
}
#else
INCLUDE_ASM("asm/nonmatchings/Font/font", fontGetMesAdr);
#endif

INCLUDE_ASM("asm/nonmatchings/Font/font", fontMessageNum);

void fontMessage(u_short *str)
{
    if (str == NULL)
    {
        font.mes_str_now = NULL;
        return;
    }

    font.mes_str = str;
    font.flag &= 0xfffffffe;
    fontNextMessage();

    if (font.prl_count == 0 && font.wait_type > 0 && font.wait_type < 8)
    {
        font.prl_str = font.mes_str;
        font.prl_count = 1;
        font.flag &= 0xffffffbf;
    }
}

void fontNextMessage()
{
    u_int wm;

    font.st_num = 0;
    if (font.flag & 1)
    {
        font.mes_str_now = NULL;
        return;
    }

    fontSetColor(0);
    font.flag &= ~8;
    font.mes_str_now = font.mes_str;
    wm = fontPrintStrMain(&font.mes_str, 0);

    if (font.sel_max != 0)
    {
        font.wait_type = 4;
        font.wait_count = -1;
    }
    else
    {
        font.wait_type = wm >> 0xc;
        if (((font.wait_type & 7) == 1) || ((font.wait_type & 7) == 0))
        {
            font.wait_count = -1;
        }
        else
        {
            u_int iVar4 = func_0019B580(0x10) ? 0x32 : 0x3C;
            font.wait_count = ((wm & 0xfff) * iVar4) / 0x3c;
        }
    }

    font.flag |= 2;
}

int fontGetStatus()
{
    if (font.wait_type == 5)
    {
        return font.sel_now;
    }
    return font.st_num == 0 ? -2 : -1;
}

void fontWide(u_short w, u_short h)
{
    font.flag |= 0x800; // sh2 uses 0x400 here
    font.wide_w = w;
    font.wide_h = h;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015D470);

void fontAllCenterOn()
{
    font.flag |= 0x100;
}

void fontAllCenterOff()
{
    font.flag = font.flag & ~0x100;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015D4D0);

void fontShadowOff()
{
    if (font.shadow_now < 4)
    {
        font.shadow_now += 4;
    }
}

void fontCrushOn()
{
    font.fonttype = 1;
}

void fontCrushOff()
{
    font.fonttype = 0;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015D570);

INCLUDE_ASM("asm/nonmatchings/Font/font", mfontFlush);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015DA10);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015DA60);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015DA90);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015DAF0);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015DB00);
