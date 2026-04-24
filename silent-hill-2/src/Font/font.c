#include "sh2_common.h"
#include "Font/font.h"

FONT_DATA font;
char font_stream_buf[FONT_STREAM_BUFFER_SIZE];

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
