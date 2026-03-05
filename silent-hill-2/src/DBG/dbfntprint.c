#include "dbfntprint.h"

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntlocate);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", dbfntlocateR);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", printline);

INCLUDE_ASM("asm/nonmatchings/DBG/dbfntprint", printlineR);

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
