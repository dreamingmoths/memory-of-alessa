#include "DBG/dbfntprint.h"

static int printline(s_char* cp /* r2 */, s_char* top /* r2 */);

static int printlineR(s_char* cp /* r2 */, s_char* top /* r2 */);

static void _dbfntprint(s_char* buf);

static void _dbfntprintR(s_char* buf /* r2 */);

static int _dbfntvsnprintf(void (* dbfntprintfunc)(s_char *) /* r19 */, s_char* buf /* r18 */, int limit /* r17 */, s_char* fmt /* r2 */, s_char* argp /* r2 */);

static DebugPrintInfo d = {
        /* .xofs = */ 0,
        /* .yofs = */ 0,
        /* .x = */ 0,
        /* .y = */ 0,
        /* .w = */ 8,
        /* .h = */ 8,
        /* .tab = */ 4,
        /* .xofsR = */ 512,
        /* .yofsR = */ 0,
        /* .yR = */ 0,
    };

#line 39
void dbfntlocate(int x, int y) {
    d.x = x; d.xofs = x;
    d.y = y; d.yofs = y;
}

void dbfntlocateR(int x, int y) {
    d.xofsR = x;
    d.yR = y; d.yofsR = y;
}

int printline(s_char* cp, s_char* top) {

    s_char line[128]; // r29+0x20
    int l; // r16
    l = cp - top;
    if (l > 0) {
        // ensure less than 128 lines
        if (l >= 0x80u) l = 0x7F;
        memcpy(line, top, l);
        line[l] = 0;
        _shDBG_print_string((s_char* ) &line, d.x, d.y);
    } else {
        l = 0;
    }
    return l;
}

//thanks: Lazy Pig (anon)
int printlineR(s_char* cp, s_char* top) {
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
        _shDBG_print_string(line, d.xofsR - (l * d.w), d.yR);
    } else {
        l = 0;
    }
    return l;
}

void _dbfntprint(s_char* buf) {
    s_char * cp; // r16
    s_char * t; // r2
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

static void _dbfntprintR(s_char* buf /* r2 */) {
    s_char* cp; // r16
    s_char* t; // r2
    t = cp = buf;

    while(*cp != 0) {
        switch (*cp) {                              /* irregular */
            case '\n':
            case '\t':
            case '\b':
                printlineR(cp, t);
                t = cp + 1;
                d.yR += d.h;
                break;
            case '\r':
                printlineR(cp, t);
                t = cp + 1;
                break;
            default:
                break;
        }
        cp++;
    }
    printlineR(cp, t);
}

void dbfntprint(s_char* buf /* r16 */) {
    if (dbSwitchDispEnable(-1)) _dbfntprint(buf);
}

void dbfntprintR(s_char* buf /* r16 */) {
    if (dbSwitchDispEnable(-1)) _dbfntprintR(buf);
}

static int _dbfntvsnprintf(void (* dbfntprintfunc)(s_char *) /* r19 */, s_char* buf /* r18 */, int limit /* r17 */, s_char* fmt /* r2 */, s_char* argp /* r2 */) {
    int len; // r16

    len = vsprintf(buf, fmt, argp);
    if (!(len < limit)) {
        printf(DEBUG_TEXT_ON_LINE(247, "_dbfntvsnprintf strbuf overflow!!\n")
               DEBUG_TEXT_ON_LINE(248, "%s")
               DEBUG_TEXT_ON_LINE(249, "halted by error\n", buf));

        BLOCK_WHILE(true);
    }

    dbfntprintfunc(buf);
    return len;
}

int dbfntprintf(s_char* fmt, ...) {
    s_char buf[512]; // r29+0x20
    va_list argp; // r16


    va_start(argp, fmt);






    if (dbSwitchDispEnable(-1)) return _dbfntvsnprintf(&dbfntprint, buf, sizeof(buf), fmt, argp);
    return 0;


}

int dbfntprintfR(s_char * fmt /* r29+0x228 */, ...){
    s_char buf[512]; // r29+0x20
    va_list argp; // r16


    va_start(argp, fmt);






    if (dbSwitchDispEnable(-1)) return _dbfntvsnprintf(&dbfntprintR, buf, sizeof(buf), fmt, argp);
    return 0;


}
