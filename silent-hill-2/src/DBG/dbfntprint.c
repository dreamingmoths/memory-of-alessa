#include "dbfntprint.h"

void dbfntlocate(int x, int y) {
    d.x = x;
    d.xofs = x;
    d.y = y;
    d.yofs = y;
}

void dbfntlocateR(int x, int y) {
    d.xofsR = x;
    d.yR = y;
    d.yofsR = y;
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
        _shDBG_print_string((char* ) &line, d.x, d.y);
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
                d.x = d.xofs;
                d.y += d.h;
            default:
                break;
            case '\t':
                d.x += d.w * printline(cp, t);
                t = cp + 1;
                d.x += d.w * d.tab;
                break;
            case '\r':
                printline(cp, t);
                t = cp + 1;
                d.x = d.xofs;
                break;
            case '\b':
                d.x += d.w * printline(cp, t);
                t = cp + 1;
                d.x -= d.w;
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
