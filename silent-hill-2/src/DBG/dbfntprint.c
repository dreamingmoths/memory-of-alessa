#include "dbfntprint.h"

void dbfntlocate(int x, int y) {
    d_0x0033BEC0.x = x;
    d_0x0033BEC0.xofs = x;
    d_0x0033BEC0.y = y;
    d_0x0033BEC0.yofs = y;
}

void dbfntlocateR(int x, int y) {
    d_0x0033BEC0.xofsR = x;
    d_0x0033BEC0.yR = y;
    d_0x0033BEC0.yofsR = y;
}

int printline(char* cp, char* top) {
    char line[128]; // r29+0x20
    int l; // r16
    l = cp - top;
    if (l > 0) {
        // ensure less than 128 lines
        if (l >= 0x80u) l = 0x7F;
        memcpy(line, top, l);
        line[l] = 0;
        _shDBG_print_string((char* ) &line, d_0x0033BEC0.x, d_0x0033BEC0.y);
    } else {
        l = 0;
    }

    return l;
}

#ifdef NON_MATCHING
int printlineR(char* cp, char* top) {
    char line[128]; // r29+0x20
    int l; // r16

    l = cp - top;
    if (l > 0) {
        // wrap?
        if (l >= 0x80U) {
            top += l - 0x7F;
            l = 0x7F;
        }
        memcpy(line, top, l);
        line[l] = 0;
        _shDBG_print_string((char* ) line, d.xofsR - (l * d.w), d.yR);
    } else {
        l = 0;
    }
    return l;
}
#else
INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", printlineR);
#endif

void _dbfntprint(char* buf) {
    char * cp; // r16
    char * t; // r2
    cp = buf, t = buf;

    while (*cp != 0) {
        switch (*cp) {
            case '\n':
                printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x = d_0x0033BEC0.xofs;
                d_0x0033BEC0.y += d_0x0033BEC0.h;
            default:
                break;
            case '\t':
                d_0x0033BEC0.x += d_0x0033BEC0.w * printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x += d_0x0033BEC0.w * d_0x0033BEC0.tab;
                break;
            case '\r':
                printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x = d_0x0033BEC0.xofs;
                break;
            case '\b':
                d_0x0033BEC0.x += d_0x0033BEC0.w * printline(cp, t);
                t = cp + 1;
                d_0x0033BEC0.x -= d_0x0033BEC0.w;
                break;
            }
        cp++;
    }
    printline(cp, t);
}

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", _dbfntprintR);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntprint);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntprintR);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", _dbfntvsnprintf);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntprintf);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntprintfR);
