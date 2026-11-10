#include "DBG/dbsw_all.h"

static void dbSwitchHelpPrint(void);

void dbSwitchAllInit(int enable) {
    dbSwitchDispEnable(enable != false);
    if (enable) {
        dbSwitchSysInit();
        dbSwitchMapInit();
    }
}

static void dbSwitchHelpPrint(void) {
    int X; // r29+0x38
    int Y; // r29+0x3C
    int on; // r16
    s_char* help; // r17

    help = NULL;
    on = dbSwitchGetPos(&X, &Y);
    switch (X) {                                 /* irregular */
    case 0: help = dbSwitchSysHelp(Y); break;
    case 1: help = dbSwitchMapHelp(Y); break;
    }

    if (help == NULL) {
        help = "(NO HELP)";
    }

    dbfntprintfR("%s:%s\n", help, on ? "ON " : "OFF");
}

int dbSwitchIsVisible(void) {
    int port; // r16
    int notonlyport1; // r2
    int disp; // r2

    port = shPadGetPort();
    notonlyport1 = dbSwitchSysPrintNotOnlyPort1();
    disp = port == 1;
    if (!disp) {
        disp = notonlyport1 != false;
    }
    return disp;
}

void dbSwitchAllPrint(void) {
    int X; // r29+0x6C
    int loop; // r16
    int disp; // r18

    disp = dbSwitchIsVisible();

    dbSwitchGetPos(&X, 0);
    dbfntlocateR(508, 44);
    if (disp) {
        dbSwitchDispIndicator(disp,
                               shPadRepeat(1, PAD_KEY_CIRCLE)     != false,
                               shPadRepeat(1, PAD_KEY_CROSS)      != false,
                              (shPadRepeat(1, PAD_KEY_DPAD_RIGHT) != false) - (shPadRepeat(1, PAD_KEY_DPAD_LEFT) != false),
                              (shPadRepeat(1, PAD_KEY_DPAD_UP)    != false) - (shPadRepeat(1, PAD_KEY_DPAD_DOWN) != false));

    } else {
        dbSwitchDispIndicator(disp, 0, shPadRepeat(1, PAD_KEY_CROSS) != false, 0, 0);
    }
    if (shPadPress(1, PAD_KEY_L1)) {
        if (shPadPress(1, PAD_KEY_SQUARE)   && shPadTrigger(1, PAD_KEY_TRIANGLE)
        ||  shPadPress(1, PAD_KEY_TRIANGLE) && shPadTrigger(1, PAD_KEY_SQUARE)) {
            dbSwitchAllInit(!dbSwitchDispEnable(-1));
            } else {
                if (shPadTrigger(1, PAD_KEY_TRIANGLE)) {
                    dbSwitchInit((u_char)X, 0xFFFFFFFFL);
                }
                if (shPadTrigger(1, PAD_KEY_SQUARE)) {
                    dbSwitchInit((u_char)X, 0);
                }
            }
    }
    if (disp) {
        dbfntlocateR(496, 44);
        if (dbSwitchSysPrintHelp()) {
            dbSwitchHelpPrint();
        }

        for (loop = 0; loop < 2; loop++) {
            if ((loop == X) || dbSwitchSysPrintAllPages()) {
                switch (loop) {                   /* irregular */
                    case 0: dbSwitchSysPrint(); break;
                    case 1: dbSwitchMapPrint(); break;
                }
            }
        }
    }
}
