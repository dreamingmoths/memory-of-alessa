#include "sh2_common.h"
#include "Font/font.h"
#include "Font/fj_man.h"
#include "libgraph.h"
#include "eestruct.h"
#include "SH2_common/pad.h"
#include "gs.h"

#pragma fast_fptosi on

extern /* static */ short FontSize[2][2];
extern /* static */ u_long font_dma_data[34];
extern /* static */ u_long font_after_env[8];

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
    font.base_z = 0xFFFFFF;
    fontClear();
    
    font.top = -1;
    
    font.flag = 1;
    for (i = 0; i < MES_V_COUNT; i++) {
        memcpy(&font.mes_v[i], &defmes, sizeof defmes);
        font.mes_v[i][4] += i;
    }

    
    font.m_w = 32;
    font.m_h = 32;
    font.m_sx = 9;
    font.m_sy = 10;
    font.m_top = -1;
    font.m_base_x = 0x7000;
    font.m_base_y = 0x7000;
    font.m_base_z = 0xFFFFFF;
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

    return &font;
}

void fontClear(void) {
    font.w_st_num = 0;
    font.st_num = 0;
    fontSetColor(0);
    font.rgb_s[0] = 0;
    font.shadow_max = 1;
    font.shadow_now = 0;
    font.alpha_base = 0x80;
    font.alpha = 0x80;
    font.fonttype = 0;
    font.flag = font.flag & 0x38F8 | 1;
    fontSetStreamMax(0x200, 0x40, 0x200);
}

INCLUDE_RODATA("asm/nonmatchings/Font/font", @565);

INCLUDE_RODATA("asm/nonmatchings/Font/font", @566);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetStreamMax);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontLoad);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontGetData);

const char rodata_631[] = "wfont over.\n";
const char rodata_632[] = "font over.\n";

void fontSet(u_short code /* r2 */, u_short x /* r17 */, u_short y /* r16 */) {        
    int num; // r2   
    struct WFONT_STREAM_DATA* fstream_w; // r3 I changed name here
    struct FONT_STREAM_DATA* fstream; // r3

    if (font.flag & 0x400) {
        if (font.w_st_num >= font.w_stream_max) {
            printf(rodata_631);
        } else {
            num = fontLoad(code);
            fstream_w = &font.w_stream[font.w_st_num];
            fstream_w->x = x << 4;
            fstream_w->y = y << 4;
            fstream_w->u = (num % 25) * 20;
            fstream_w->v = (num / 25) * 30;
            fstream_w->rgb_u = font.rgb_u | (font.alpha << 24);
            fstream_w->rgb_d = font.rgb_d | (font.shadow_now << 24);
            fstream_w->w = FontSize[font.fonttype][0] << 4;
            fstream_w->h = FontSize[font.fonttype][1] << 4;
            fstream_w->vw = font.wide_w << 4;
            fstream_w->vh = font.wide_h << 4;
            font.w_st_num++;
        }
    } else if (font.st_num >= font.stream_max) {
        printf(rodata_632);
    } else {
        num = fontLoad(code);
        fstream = &font.stream[font.st_num];
        fstream->x = x << 4;
        fstream->y = y << 4;
        fstream->u = (num % 25) * 20;
        fstream->v = (num / 25) * 30;
        fstream->rgb_u = font.rgb_u | (font.alpha << 24);
        fstream->rgb_d = font.rgb_d | (font.shadow_now << 24);
        fstream->w = FontSize[font.fonttype][0] << 4;
        fstream->h = FontSize[font.fonttype][1] << 4;
        font.st_num++;
    }
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetWide);

void fontSetBlankBox(int x0, int x1, int y) {
    FONT_STREAM_DATA* fstream;

    if (font.st_num >= font.stream_max) {
        debugPrintf(rodata_632);
        return;
    }
    
    
    
    fstream = &font.stream[font.st_num];
    fstream->x = x0 * 0x10;
    fstream->y = y * 0x10;
    fstream->u = x1 * 0x10;
    fstream->v = 0xfff7;
    fstream->rgb_u = font.rgb_u | (font.alpha << 0x18);
    fstream->rgb_d = font.rgb_d | (font.shadow_now << 0x18);
    fstream->h = FontSize[font.fonttype][1] * 0x10;

    font.st_num++;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetLine);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStr);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStrNum);

const char rodata_954[] = "font: double stack!\n";

const char rodata_955[] = "x >= (4096-SCREEN_WIDTH)/2";

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStrMain);

const char rodata_1377_0x003914C0[] = "num >= 0 && num <= 16";

const char rodata_1810[] = "fontSetMes: Illegal number!\n";

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintDec);

void fontSetYesNo(int y) {
    int w = fontPrintWord(fontGetMesAdr(&msg_station, 0), 0xC8, y, 1, 0);
    int w2 = fontPrintWord(fontGetMesAdr(&msg_station, 1), 0x138, y, 1, 0);

    if (w2 < w) {
        font.sel_yu[1] = (u_short) w;
        return;
    }
    font.sel_yu[1] = (u_short) w2;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintWord);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPrintStrWide);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontGetMesWidth);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetColor);

void fontSetColorDirect(u_char r /* r2 */, u_char g /* r2 */, u_char b /* r2 */, u_char alp /* r2 */) {
    font.rgb_u = font.rgb_d = COLOR_RGB(r, g, b);
    font.alpha = alp;
}

void fontSetAlpha(u_char alp /* r2 */) {
    font.alpha = alp;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontBarBlink);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlush);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontFlushNoSPR);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPut);

void fontPutSelectBar(void) {
    /* v0 */ int x0; /* v0 */ int y0; /* v0 */ int x1; /* v0 */ int y1; /* v0 */ int z;  /* v0 */ int a;
    /* s0 */ u_long* pCur = font.pCur;

    x0 = FP16(font.sel_xl) + font.base_x;
    x1 = FP16(font.sel_xr) + font.base_x;
    y0 = FP16(font.sel_yu[font.sel_now] + 1) + font.base_y;
    y1 = FP16(font.sel_yd[font.sel_now] + 1) + font.base_y;
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
    /* v0 */ int x0; /* v0 */ int y0; /* v0 */ int x1; /* v0 */ int y1; /* v0 */ int z;  /* v0 */ int a;
    /* s0 */ u_long* pCur = font.pCur;
    if (font.sel_now == 0) {
        x0 = X_COORD(264.0);
    } else {
        x0 = X_COORD(376.0);
    }
    x0 += font.base_x;
    x1 = x0 + FP16(font.sel_yu[1] / 2 + 4);
    x0 -= FP16(font.sel_yu[1] / 2 + 4);
    y0 = FP16(font.sel_yu[0] + 1) + font.base_y;
    y1 = FP16(font.sel_yd[0] + 1) + font.base_y;
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

void* fontAfterEnv(void) {
    return &font_after_env;
}

void fontEachTurn() {
    if (!font.tex0)
        return;
    if (font.prl_count) {
        fontPreload();
    } 
    else if (font.bottom < 0x190) {
        fontLoad(++font.preload);
    }

    if (font.flag & 2) {
        font.flag &= ~2;
    } else if (!(font.flag & 0x20)) {
        if ((short) font.sel_max == -1) {
            if (shPadTrigger(0, 0x200)) {
                fontSelectUp();
            }
            if (shPadTrigger(0, 0x100)) {
                fontSelectDown();
            }
        } else {
            if (shPadRepeat(0, 0x400)) {
                fontSelectUp();
            }
            if (shPadRepeat(0, 0x800)) {
                fontSelectDown();
            }
        }
        if (shPadTrigger(0, key_config.enter)) {
            fontPushButton();
        }
        if (shPadTrigger(0, key_config.cancel)) {
            fontPushButton2();
        }
    }

    if (font.wait_type & 7 && font.wait_type != 4) {
        if (font.wait_count > 0 && !(font.flag & 0x10)) {
            font.wait_count = font.wait_count - (short) shGetDF();
        }
        if (font.wait_count == 0) {
            if (font.wait_type & 8) {
                font.st_num = 0;
                font.sel_max = 0;
                font.wait_type = 0;
                return;
            }
            fontNextMessage();
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPreload);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSetMes);

void fontCopyMessage(u_short* pto, u_short* pfrom) {
    u_short n;
    do {
        n = *pfrom++;
        *pto++ = n;
    } while (n != 0xffff);
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPushButton);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontPushButton2);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectUp);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontSelectDown);

u_short* fontGetMesAdr(u_short* str /* r2 */, u_short num /* r2 */) {
    if (str == NULL) {
        return NULL;
    }
    if (num >= str[0]) {
        printf("message number over! (%d/%d)\n", num, *str);
        return NULL;
    }
    return str + str[num + 1];
}

void fontMessageNum(u_short* str /* r2 */, u_short num /* r2 */) {
    fontMessage(fontGetMesAdr(str, num));
}

void fontMessage(u_short* str /* r2 */)  {
    if (str == 0) {
        font.mes_str_now = 0;
        return;
    }
    font.mes_str = str;
    UNSET_BIT(font.flag, 0);
    fontNextMessage();
    if ((font.prl_count == 0) && (font.wait_type > 0) && (font.wait_type < 8)) {
        font.prl_str = font.mes_str;
        font.prl_count = 1;
        UNSET_BIT(font.flag, 6);
    }
}

void fontNextMessage(void) {
    u_int wm; // r5
    
    font.st_num = 0;
    if (GET_BIT(font.flag, 0)) {
        font.mes_str_now = NULL;
        return;
    }
    fontSetColor(0);
    UNSET_BIT(font.flag, 3);  
    font.mes_str_now = font.mes_str;
    wm = fontPrintStrMain(&font.mes_str, 0);
    if (font.sel_max) {
        font.wait_type = 4;
        font.wait_count = -1;
    } else {
        font.wait_type = wm >> 12;
        if ((font.wait_type & 7) == 1 || (font.wait_type & 7) == 0) {
            font.wait_count = -1;
        } else {
            font.wait_count = (((wm & 0xFFF) * 0x3C) / 60);
        }
    }
    SET_BIT(font.flag, 1);
}

int fontGetStatus(void) {
    if (font.wait_type == 5) {
        return font.sel_now;
    }
    return font.st_num == 0 ? -2 : -1;
}

void fontWide(u_short w /* r2 */, u_short h /* r2 */) {
    SET_BIT(font.flag, 10);
    font.wide_w = w;
    font.wide_h = h;
}

void fontAllCenterOn(void) {
    SET_BIT(font.flag, 8); // 0x100
}

void fontAllCenterOff(void) {
    UNSET_BIT(font.flag, 8); // 0x100
}

INCLUDE_ASM("asm/nonmatchings/Font/font", fontAllCenter2On);

INCLUDE_ASM("asm/nonmatchings/Font/font", fontAllCenter2Off);

void fontShadowOff(void) {
    if (font.shadow_now < 4) {
        font.shadow_now += 4;
    }
}

void fontCrushOn(void) {
    font.fonttype = 1;
}

void fontCrushOff(void) {
    font.fonttype = 0;
}

INCLUDE_ASM("asm/nonmatchings/Font/font", mfontClear);

INCLUDE_ASM("asm/nonmatchings/Font/font", mfontFlush);
