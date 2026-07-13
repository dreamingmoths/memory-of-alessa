#include "common.h"
#include "Font/font.h"
#include "Font/fj_man.h"
#include "SH3_common/sh3dt.h"
#include "sce/libgraph.h"
#include "sce/eestruct.h"
#include "gs.h"
#include "shared/Font/font.h"

struct FONT_DATA font;

FONT_DATA* fontInit(void) {
    int i;
    // @todo: figure out what this translates to
    u_short defmes[8] = {
        0x112, 0xD89, 0x95C,  0xADF,
        0x172, 0x113, 0xFFFF, 0x8000
    };

    shQzero(&font, sizeof font);
    ((u_int*) font_dma_data)[29] = (u_int) font.texbuf;
    ((u_int*) font_dma_data)[61] = (u_int) font.clut;

    
    font.clut[0] = 0;
    for (i = 1; i < 7; i++) {
        font.clut[i] = FONT_CLUT(i);
    }

    
    font.base_y = 0, font.base_x = 0;
    font.base_z = 0;
    fontClear();
    
    font.top = -1;
    
    font.flag = 1;
    for (i = 0; i < MES_V_COUNT; i++) {
        memcpy(&font.mes_v[i], &defmes, sizeof defmes);
        font.mes_v[i][4] += i; // @todo the `4` could be wrong here?
    }

    
    font.m_w = 32;
    font.m_h = 32;
    font.m_sx = 9;
    font.m_sy = 10;
    font.m_top = -1;
    font.m_base_x = 0x7000;
    font.m_base_y = 0x7000;
    font.m_base_z = 0;
    font.m_rgba = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, 0x50, 0);

    
    {
        // @todo: figure out what this translates to
        u_short fake_mes[22] = {
            0x0,     0x237,    0x24E,    0xFA,
            0x242,   0x232,    0x225,    0x237,
            0x203,   0x201,    0xBD0,    0x1B3,
            0x1CE,   0x1F3,    0x1F0,    0xFA,
            0x1D6,   0x1C6,    0x1F6,    0xE8,
            0xFFFD,  0xFFFF
        }; // r29+0x40
        u_short* str = &fake_mes; // r16
        u_short c; // r2

        while ((c = *str++) != 0xFFFF) {
            if (c == 0xFFFD) {
                while ((font.bottom % 25) != 0) {
                    fontLoad(0);
                    (&font.page_sound)[font.bottom] = 0x7FFF;
                }
            } else {
                fontLoad(c);
                (&font.page_sound)[font.bottom] = 0x7FFF;
            }
        }
    }

    D_01D08FA0[0] = 0;

    return &font;
}

void fontClear()
{
    font.w_st_num = 0;
    font.st_num = 0;
    fontSetColor(0);
    font.rgb_s[0] = 0;
    font.shadow_max = 1;
    font.unk200C0 = 0;
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
        ((u_int)(font.m_stream + ms_max) - (u_int)font_stream_buf) <= FONT_STREAM_BUFFER_SIZE,
        "font.c",
        0x129);
}


INCLUDE_ASM("asm/nonmatchings/Font/font", fontLoad);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontGetData);

void fontSet(u_short code, u_short x, u_short y)
{
    int num;

    // this check isn't in sh2:
    if (func_0019B580(0x10) != 0)
    {
        y = FONT_CORRECT_Y(y);
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
    if (func_0019B580(0x10) != 0)
    {
        y = FONT_CORRECT_Y(y);
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
    if (func_0019B580(0x10) != 0)
    {
        y = FONT_CORRECT_Y(y);
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

void fontBarBlink()
{
    if ((font.bar_blink += shGetDT()) >= 1.0f)
        font.bar_blink -= 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlush);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlushNoSPR);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C310);

void fontPutSelectBar(void) {
    int z, x0, y0, x1, y1, a;
    u_long* pCur = font.pCur;

    x0 = FP16(font.sel_xl) + font.base_x;
    x1 = FP16(font.sel_xr) + font.base_x;

    if (func_0019B580(0x10)) {
        y0 = FP16(FONT_CORRECT_Y(font.sel_yu[font.sel_now]) + 1) + font.base_y;
        y1 = FP16(FONT_CORRECT_Y(font.sel_yd[font.sel_now]) + 1) + font.base_y;
    } else {
        y0 = FP16(font.sel_yu[font.sel_now] + 1) + font.base_y;
        y1 = FP16(font.sel_yd[font.sel_now] + 1) + font.base_y;
    }

    z = font.base_z;

    fontBarBlink();
    if (font.bar_blink > 0.5f) {
        a = 64.0f * ((1.0f - font.bar_blink) / 0.5f);
    } else {
        a = 64.0f * (font.bar_blink / 0.5f);
    }

    *pCur++ = SCE_GIF_SET_TAG(3, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, /* Alpha blend */ SCE_GS_TRUE, 0, 0, 0, 0), SCE_GIF_PACKED, 1);
    
    
    *pCur++ = SCE_GIF_PACKED_AD;
    *pCur++ = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_CD, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);
    *pCur++ = SCE_GS_ALPHA_1;
    *pCur++ = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    *pCur++ = SCE_GS_TEST_1;
    *pCur++ = SCE_GS_SET_PABE(SCE_GS_FALSE);
    *pCur++ = SCE_GS_PABE;

    *pCur++ = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_FALSE, NULL, SCE_GIF_REGLIST, 3);
    *pCur++ = GIF_REG(SCE_GS_RGBAQ, 0) | GIF_REG(SCE_GS_XYZ2, 1) | GIF_REG(SCE_GS_XYZ2, 2);
    *pCur++ = SCE_GS_SET_RGBAQ(16, 32, 192, a + 16, 0);
    *pCur++ = ASM_GS_SET_XYZ(x0, y0, z);
    *pCur++ = ASM_GS_SET_XYZ(x1, y1, z);
    *pCur++ = 0;
    
    font.pCur = pCur;
}

void fontPutYesNoSelectBar(void) {
    int z, x0, y0, x1, y1, a;
    u_long* pCur = font.pCur;

    if (font.sel_now == 0) {
        x0 = X_COORD(264.0);
    } else {
        x0 = X_COORD(376.0);
    }

    x0 += font.base_x;
    x1 = x0 + FP16(font.sel_yu[1] / 2 + 4);
    x0 -= FP16(font.sel_yu[1] / 2 + 4);

    if (func_0019B580(0x10)) {
        y0 = FP16(FONT_CORRECT_Y(font.sel_yu[0]) + 1) + font.base_y;
        y1 = FP16(FONT_CORRECT_Y(font.sel_yd[0]) + 1) + font.base_y;
    } else {
        y0 = FP16(font.sel_yu[0] + 1) + font.base_y;
        y1 = FP16(font.sel_yd[0] + 1) + font.base_y;
    }

    z = font.base_z;

    fontBarBlink();
    if (font.bar_blink > 0.5f) {
        a = 64.0f * ((1.0f - font.bar_blink) / 0.5f);
    } else {
        a = 64.0f * (font.bar_blink / 0.5f);
    }
    
    *pCur++ = SCE_GIF_SET_TAG(3, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 0, 0, /* Alpha blend */ SCE_GS_TRUE, 0, 0, 0, 0), SCE_GIF_PACKED, 1);
    
    *pCur++ = SCE_GIF_PACKED_AD;
    *pCur++ = SCE_GS_SET_ALPHA_1(SCE_GS_ALPHA_CS, SCE_GS_ALPHA_CD, SCE_GS_ALPHA_AS, SCE_GS_ALPHA_CD, 0);
    *pCur++ = SCE_GS_ALPHA_1;
    *pCur++ = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    *pCur++ = SCE_GS_TEST_1;
    *pCur++ = SCE_GS_SET_PABE(SCE_GS_FALSE);
    *pCur++ = SCE_GS_PABE;
    
    *pCur++ = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_FALSE, NULL, SCE_GIF_REGLIST, 3);
    *pCur++ = GIF_REG(SCE_GS_RGBAQ, 0) | GIF_REG(SCE_GS_XYZ2, 1) | GIF_REG(SCE_GS_XYZ2, 2);
    *pCur++ = SCE_GS_SET_RGBAQ(16, 32, 192, a + 16, 0);
    *pCur++ = ASM_GS_SET_XYZ(x0, y0, z);
    *pCur++ = ASM_GS_SET_XYZ(x1, y1, z);
    *pCur++ = 0;
    
    font.pCur = pCur;
}

void* fontTexLoad(int texadr, int clutadr) {
    font_dma_data[0x04] = SCE_GS_SET_BITBLTBUF(0, 0, SCE_GS_PSMCT32, texadr, 512 / 64, SCE_GS_PSMT4);
    font_dma_data[0x14] = SCE_GS_SET_BITBLTBUF(0, 0, SCE_GS_PSMCT32, clutadr, 64 / 64, SCE_GS_PSMCT32);
    font.tex0 = SCE_GS_SET_TEX0(texadr, 512 / 64, SCE_GS_PSMT4, 9 /* 512 */, 9 /* 512 */, SCE_GS_TRUE, SCE_GS_MODULATE, clutadr, SCE_GS_PSMCT32, SCE_GS_FALSE, 0, 1);

    return font_dma_data;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C9E0);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015C9F0);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPreload);

INCLUDE_ASM("asm/nonmatchings/Font/font", func_0015CEF0);

void func_0015CF10(u_short *dest, u_short *src) {
    u_short n;
    do {
        n = *src++;
        *dest++ = n;
    } while (n != 0xFFFF);
}

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

void fontPushButton2()
{
    if (((font.wait_type & 7u) != 2) && !(font.flag & 0x10))
    {
        font.wait_count = 0;
    }
}

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
INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectUp);
INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectDown);
#endif

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

INCLUDE_ASM("asm/nonmatchings/Font/font", fontMessageNum);

void fontMessage(u_short *str)
{
    if (str == NULL)
    {
        font.mes_str_now = NULL;
        return;
    }

    font.mes_str = str;
    font.flag &= ~1;
    fontNextMessage();

    if (font.prl_count == 0 && font.wait_type > 0 && font.wait_type < 8)
    {
        font.prl_str = font.mes_str;
        font.prl_count = 1;
        font.flag &= ~0x40;
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
