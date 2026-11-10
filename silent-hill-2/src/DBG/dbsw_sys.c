#include "DBG/dbsw_sys.h"

#pragma divbyzerocheck off

static int dbSwitchSys(int Y /* r2 */);

static void dbSwitchSetSys(int Y /* r2 */, int on /* r2 */);

static void printR_date(void);

static void printR_cmdserv(CmdServStat* stat /* r18 */, char* prefix /* r17 */, int* exec /* r2 */);

static void printR_fileserv(void);

static void printR_loadinit(void);

static void printR_test(void);

static void printR_padstep(int port /* r8 */, int slot /* r2 */);

static void printR_paddata(s_char* paddata /* r2 */);

static void printR_keydata(shGameKeyData* key /* r16 */);

static void printR_padport(int port /* r22 */, int slot /* r21 */, int pad_normalize /* r20 */, int pad_adjust /* r19 */, int dispstep /* r18 */, int disppad /* r17 */, int dispkey /* r16 */);

static void printR_pad00(void);

static void printR_pad10(void);

static void printR_lang(void);

s_char* dbSwitchSysHelp(int Y /* r2 */) {
    s_char* help = NULL;
    switch (Y) {
        case 0:
            help = "display this help";
            break;
        case 1:
            help = "enable pad port for debug";
            break;
        case 2:
            help = "display switch indicator not-only port 1";
            break;
        case 3:
            help = "display all switch pages";
            break;
        case 4:
            help = "display RTC";
            break;
        case 5:
            help = "display File Server status";
            break;
        case 6:
            help = "display Load and Init command Server status";
            break;
        case 7:
            help = "verbose at command server status";
            break;
        case 8:
            help = "display default language by ps2 system configuration";
            break;
        case 19:
            help = "diaplay special characters(0x20-0x9F)";
            break;
        case 9:
            help = "display allinfo at pad(0,0)";
            break;
        case 10:
            help = "display pad step at pad(0,0).";
            break;
        case 11:
            help = "display paddata at pad(0,0).";
            break;
        case 12:
            help = "display keydata at pad(0,0).";
            break;
        case 13:
            help = "display allinfo at pad(1,0).";
            break;
        case 14:
            help = "display pad step at pad(1,0).";
            break;
        case 15:
            help = "display paddata at pad(1,0).";
            break;
        case 16:
            help = "display keydata at pad(1,0).";
            break;
        case 17:
            help = "semaphore param.";
            break;
        case 18:
            help = "thread param.";
            break;
        case 30:
            help = "debug menu from soft reset.";
            break;
        case 31:
            help = "movie dummy step.";
        default:
            break;
    }
    return help;
}

static int dbSwitchSys(int Y /* r2 */) {
    return dbSwitch(0, Y);
}

static void dbSwitchSetSys(int Y /* r2 */, int on /* r2 */) {
    dbSwitchSet(0, Y, on);
}

// thanks: Bl00D4NGEL
static void printR_date(void) {
    Old_Rtc rtc[1];
    s_char strbuf[32]; // r29+0x20
    s_char* str; // r16

    shCdReadClock(&rtc);
    str = strbuf;
    str += sh2ScfMakeDateStrByLocalTimeFromJST(strbuf, &rtc);
    str += sprintf(str, " ");
    sh2ScfMakeTimeStrByLocalTimeFromJST(str, &rtc);
    dbfntprintfR("%s\n", strbuf);
}

static void printR_cmdserv(CmdServStat* stat /* r18 */, char* prefix /* r17 */, int* exec /* r2 */) {
    s_char syms[4] = {'|', '/', '-', '\x81'};
    s_char sym = ' ';
    if (exec != NULL) {
        if (stat->clen) {
            sym = syms[(*exec)++ % 4];
        } else {
            *exec = 0;
        }
    }
    dbfntprintfR(
    dbSwitchSys(7)
    ? "%s: %3d%1c(%03d-%03d) (%3d/%3d)\n"
    : "%s: %3d%1c\n",
    prefix,
    stat->clen % 1000,
    sym,
    stat->id % 1000,
    stat->last_id % 1000,
    stat->qlen % 1000,
    stat->qsize % 1000);
}
// thanks: Sassy Gaur (Anon)
static void printR_fileserv(void) {
    static int exec[1] = {0};  // @ 0x0034DB98
    CmdServStat stat[1]; // r29+0x10

    fsGetStat(stat);
    printR_cmdserv(stat, "fs", exec);
}

static void printR_loadinit(void) {
    static int exec[1] = {0};  // @ 0x0034DB98
    CmdServStat stat[1]; // r29+0x10

    lisGetStat(stat);
    printR_cmdserv(stat, "lis", exec);
}

static void printR_test(void) {
    dbfntprintR("[ !\"#$%&' ()*+,-./]\n[01234567 89:;<=>?]\n[@ABCDEFG HIJKLMNO]\n[PQRSTUVW XYZ[\\]^_]\n[`abcdefg hijklmno]\n[pqrstuvw xyz{|}~\x7F]\n[\x80\x81\x82\x83\x84\x85\x86\x87 \x88\x89\x8A\x8B\x8C\x8D\x8E\x8F]\n[\x90\x91\x92\x93\x94\x95\x96\x97 \x98\x99\x9A\x9B\x9C\x9D\x9E\x9F]\n");
}

static void printR_padstep(int port /* r8 */, int slot /* r2 */) {
    dbfntprintfR("pad(%d,%d) trans step: %04x\n", port, slot, libShPadStep[port][slot]);
}

//thanks: Piccio23, dreamingmoths
static void printR_paddata(s_char* paddata /* r2 */) {
    u_int padp[8] = {0}; // r29+0x20
    int idx; // r2
    int ofs; // r5


    for (idx = 31; idx >= 0; idx--) {
        ofs = idx / 4;
        padp[ofs] = (padp[ofs] << 8);
        padp[ofs] |= (u_char)paddata[idx];
    }
    dbfntprintfR("%08x %08x\n%08x %08x\n%08x %08x\n%08x %08x\n", padp[1], padp[0], padp[3], padp[2], padp[5], padp[4], padp[7], padp[6]);
}


static void printR_keydata(shGameKeyData* key /* r16 */) {

    dbfntprintfR("type:%1d  DRINK:%1d\nRADIO:%1d  LIGHT:%1d\nITEM:%1d    MAP:%1d\nDECIDE:%1d CANCEL:%1d\n",
                 key->f.type,
                 key->f.DRINK,
                 key->f.RADIO,
                 key->f.LIGHT,
                 key->f.ITEM,
                 key->f.MAP,
                 key->f.DECIDE,
                 key->f.CANCEL);
    dbfntprintfR("SKIP:%1d  PAUSE:%1d\nACTION:%1d   DASH:%1d\nLSLIDE:%1d RSLIDE:%1d\nREADY:%1d   VIEW:%1d\n",
                 key->f.SKIP,
                 key->f.CANCEL, //@bug
                 key->f.ACTION,
                 key->f.DASH,
                 key->f.LSLIDE,
                 key->f.RSLIDE,
                 key->f.READY,
                 key->f.VIEW);
    dbfntprintfR("A(X,Y):(%+1d,%+1d)\nB(X,Y):(%+1d,%+1d)\nC(X,Y):(%+1d,%+1d)\nlen:%5d\n",
                 key->f.AX,
                 key->f.AY,
                 key->f.BX,
                 key->f.BY,
                 key->f.CX,
                 key->f.CY,
                 key->f.len);
}

static void printR_padport(int port /* r22 */, int slot /* r21 */, int pad_normalize /* r20 */, int pad_adjust /* r19 */, int dispstep /* r18 */, int disppad /* r17 */, int dispkey /* r16 */) {
    shGameKeyData key[1]; // r29+0xA8
    u_char paddata[32]; // r29+0x80

    if (disppad || dispkey) {
        libShPadRead(port, slot, paddata);
        if (pad_normalize) shSysKeyNormalize(paddata);
        if (pad_adjust) shSysKeyAdjust(paddata);
    }
    if (dispstep) {
        printR_padstep(port, slot);
    }
    if (disppad) {
        printR_paddata(paddata);
    }
    if (dispkey) {
        shGameKeyConvert(key, (u_char *)paddata);
        printR_keydata(key);
    }
}

void printR_pad00(void) {

    if (dbSwitchSys(9) && !dbSwitchSys(0xA) && !dbSwitchSys(0xB) && !dbSwitchSys(0xC)) {
        dbSwitchSet(0, 0xA, 1);
        dbSwitchSet(0, 0xB, 1);
        dbSwitchSet(0, 0xC, 1);
    }
    if (!dbSwitchSys(9) && dbSwitchSys(0xA) && dbSwitchSys(0xB) && dbSwitchSys(0xC)) {
        dbSwitchSet(0, 0xA, 0);
        dbSwitchSet(0, 0xB, 0);
        dbSwitchSet(0, 0xC, 0);
    }
    printR_padport(0, 0, 1, 1, dbSwitchSys(0xA), dbSwitchSys(0xB), dbSwitchSys(0xC));
}

void printR_pad10(void) {

    if (dbSwitchSys(0xD) && !dbSwitchSys(0xE) && !dbSwitchSys(0xF) && !dbSwitchSys(0x10)) {
        dbSwitchSet(0, 0xE, 1);
        dbSwitchSet(0, 0xF, 1);
        dbSwitchSet(0, 0x10, 1);
    }
    if (!dbSwitchSys(0xD) && dbSwitchSys(0xE) && dbSwitchSys(0xF) && dbSwitchSys(0x10)) {
        dbSwitchSet(0, 0xE, 0);
        dbSwitchSet(0, 0xF, 0);
        dbSwitchSet(0, 0x10, 0);
    }
    printR_padport(1, 0, 1, 1, dbSwitchSys(0xE), dbSwitchSys(0xF), dbSwitchSys(0x10));
}

void printR_lang(void) {
    s_char* str;
    switch (sh2ScfGetDefaultLanguage() & 0xFF) {
        case 0: str = "JPN"; break;
        case 1: str = "ENG"; break;
        case 2: str = "FRN"; break;
        case 3: str = "GER"; break;
        case 4: str = "ITA"; break;
        case 5: str = "SPN"; break;
    }
    dbfntprintfR("lang:%s\n", str);
}

void dbSwitchSysPrint(void) {
    int Y;
    for (Y = 0; Y < 32; Y++)
        switch (Y) {                               /* irregular */
            case 4:  if (dbSwitchSys(Y)) printR_date();     break;
            case 5:  if (dbSwitchSys(Y)) printR_fileserv(); break;
            case 6:  if (dbSwitchSys(Y)) printR_loadinit(); break;
            case 19: if (dbSwitchSys(Y)) printR_test();     break;
            case 9:                      printR_pad00();    break;
            case 13:                     printR_pad10();    break;
            case 8:  if (dbSwitchSys(Y)) printR_lang();     break;
            case 17:                                        break;
            case 18: if (dbSwitchSys(Y)) dbScrPrintThreAll();
            default:
                break;
        }
}

int dbSwitchSysPrintHelp(void) {
    dbSwitchSys(0);
}

int dbSwitchSysPadPort(void) {
    dbSwitchSys(1);
}

int dbSwitchSysPrintAllPages(void) {
    dbSwitchSys(3);
}

int dbSwitchSysPrintNotOnlyPort1(void) {
    dbSwitchSys(2);
}

void dbSwitchSysInit(void) {
    dbSwitchSetSys(1, 1);
    dbSwitchSetSys(2, 1);
    dbSwitchSetSys(3, 1);
    dbSwitchSetSys(5, 1);
    dbSwitchSetSys(6, 1);
    dbSwitchSetSys(30, 1);
    dbSwitchSetSys(31, 1);
}
