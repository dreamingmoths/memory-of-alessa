#include "dbfntprint.h"

int printline(char* cp, char* top) {
    char line[128]; // r29+0x20
    int l; // r16
    l = cp - top;
    if (l > 0) {
        // ensure less than 128 lines
        if (l >= 0x80u) l = 0x7F;
        memcpy(line, top, l);
        line[l] = 0;
        shDBG_print_string((char* ) &line, d.x, d.y);
    } else {
        l = 0;
    }

    return l;
}

void _dbfntprint(char* buf) {
    char * cp;
    char * t;
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

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", func_001DBD40);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", func_001DBD60);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", _dbfntvsnprintf);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", func_001DBE30);
