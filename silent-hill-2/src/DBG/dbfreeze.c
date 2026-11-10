#include "DBG/dbfreeze.h"





void dbFreeze(void) {
    static int fz_step; // @ 0x011B6F48
    u_char paddata[32]; // r29+0x10
    int loop; // r5
    if (shPadGetPort() == 1) {
        do {

            dbFlowSetCheckPoint("dbfreeze loop");
            libShPadRead(1, 0, &paddata);
            shSysKeyNormalize(&paddata);

            loop = true;
            switch (fz_step) {
                case 0:
                    loop = false;
                    if (paddata[22])      fz_step = 1;
                    break;
                case 1:
                    if (!paddata[22])     fz_step = 2;
                    break;
                case 2:
                    if (paddata[22])      fz_step = 3;
                    else if (paddata[17]) fz_step = 4;
                    else if (paddata[19]) loop = false;
                    break;
                case 3:
                    if (!paddata[22]) fz_step = 0;
                    break;
                case 4:
                    loop = false;
                    fz_step = 5;
                    break;
                case 5:
                    if (!paddata[17]) fz_step = 2;
                    break;
            }
        } while (loop);
        dbFlowSetCheckPoint("exit dbfreeze");
    }
}
