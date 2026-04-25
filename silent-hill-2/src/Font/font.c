#include "sh2_common.h"
#include "Font/font.h"

extern /* static */ short FontSize[2][2];

// @todo: does this have an SH3 equivalent?
void fontSetYesNo(int y) {
    int w;
    int w2;

    w = fontPrintWord(fontGetMesAdr((u_short*)&msg_station, 0), 0xC8, y, 1, 0);
    w2 = fontPrintWord(fontGetMesAdr((u_short*)&msg_station, 1), 0x138, y, 1, 0);

    if (w2 < w) {
        font.sel_yu[1] = (u_short) w;
        return;
    }
    font.sel_yu[1] = (u_short) w2;
}

void fontCopyMessage(u_short* pto, u_short* pfrom) {
    u_short n;
    do {
        n = *pfrom++;
        *pto++ = n;
    } while (n != 0xffff);
}

#ifdef NON_MATCHING
void fontEachTurn() {
    if (font.tex0 != 0) {
        if (font.prl_count != 0) {
            fontPreload();
        } else if (font.bottom < 0x190) {
            fontLoad(++font.preload);
        }
        if (font.flag & 2) {
            font.flag &= 0xfffffffd;
        } else if (!(font.flag & 0x20)) {
            if ((short) font.sel_max == -1) {
                if (shPadTrigger(0, 0x200) != 0) {
                    fontSelectUp();
                }
                if (shPadTrigger(0, 0x100) != 0) {
                    fontSelectDown();
                }
            } else {
                if (shPadRepeat(0, 0x400) != 0) {
                    fontSelectUp();
                }
                if (shPadRepeat(0, 0x800) != 0) {
                    fontSelectDown();
                }
            }
            if (shPadTrigger(0, key_config.enter) != 0) {
                fontPushButton();
            }
            if (shPadTrigger(0, key_config.cancel) != 0) {
                fontPushButton2();
            }
        }
        if (((font.wait_type & 7u) != 0) && (font.wait_type != 4)) {
            if (font.wait_count > 0 && !(font.flag & 0x10)) {
                font.wait_count = font.wait_count - (short) shGetDF();
            }
            if (font.wait_count == 0) {
                if (font.wait_type & 8u) {
                    font.st_num = 0;
                    font.sel_max = 0;
                    font.wait_type = 0;
                    return;
                }
                fontNextMessage();
            }
        }
    }
}
#endif

void fontMessageNum(u_short* str /* r2 */, u_short num /* r2 */) {
    fontMessage(fontGetMesAdr(str, num));
}

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

void fontMessage(u_short* str /* r2 */)  {
    if (str == 0) {
        font.mes_str_now = 0;
        return;
    }
    font.mes_str = str;
    UNSET_BIT(font.flag, 0x1);
    fontNextMessage();
    if ((font.prl_count == 0) && (font.wait_type > 0) && (font.wait_type < 8)) {
        font.prl_str = font.mes_str;
        font.prl_count = 1;
        UNSET_BIT(font.flag, 0x40);
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
    UNSET_BIT(font.flag, 0x8);
    font.mes_str_now = font.mes_str;
    wm = fontPrintStrMain(&font.mes_str, 0);
    if (font.sel_max != 0) {
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
    SET_BIT(font.flag, 0x2);
}

void fontSet(u_short code /* r2 */, u_short x /* r17 */, u_short y /* r16 */) {        
    int num; // r2   
    struct WFONT_STREAM_DATA* fstream_w;// r3 I changed name here
    struct FONT_STREAM_DATA* fstream; // r3

    if (font.flag & 0x400) {
        if (font.w_st_num >= font.w_stream_max) {
            printf("wfont over.\n");
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
        printf("font over.\n");
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
