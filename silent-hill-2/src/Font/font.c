#include "sh2_common.h"
#include "Font/font.h"

// @todo: does this have an SH3 equivalent?
void fontSetYesNo(int y) {
    int w;
    int w2;

    w = fontPrintWord(fontGetMesAdr((u16*)&msg_station, 0), 0xC8, y, 1, 0);
    w2 = fontPrintWord(fontGetMesAdr((u16*)&msg_station, 1), 0x138, y, 1, 0);

    if (w2 < w) {
        font.sel_yu[1] = (u16) w;
        return;
    }
    font.sel_yu[1] = (u16) w2;
}

void fontCopyMessage(u16* pto, u16* pfrom) {
    u16 n;
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
            if ((s16) font.sel_max == -1) {
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
                font.wait_count = font.wait_count - (s16) shGetDF();
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
