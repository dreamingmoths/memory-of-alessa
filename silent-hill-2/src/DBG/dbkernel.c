#include "DBG/dbkernel.h"

static int ___dbPrintThre(int tid, /* r2 */ int (* printf)());

static void ___dbPrintThreAll(int (* printf)() /* r18 */);

#line 55
static int ___dbPrintThre(int tid, /* r2 */ int (* printf)()) {
    int ret; // r16;
    s_char str[256];                           // r29+0x20
    ThreadParam thre;                        // r29+0x120
    s_char* help;                             // r2
    ret = ReferThreadStatus(tid, &thre);
    if (ret) {

        help = (s_char *)(thre.option & 0x1FFFFFF);
        if (   (u_int)help <  0x100000
            || (u_int)help >= 0x2000000
            || help[0] != 'f'
            || help[1] != 'o'
            || help[2] != 'r')
                help = "?";
            UtilStrCpyL(str, help, 255);
            str[255] = 0;
    }







    return ret;
}


static void ___dbPrintThreAll(int (* printf)() /* r18 */) {

    int tid;       // r16
    int count = 0; // r17
    for (tid = 0; tid < 256; tid++) {


        if (___dbPrintThre(tid, printf)) count++;
    }

}







void dbScrPrintThreAll(void) {
    dbfntlocate(8, 128);
    ___dbPrintThreAll(&dbfntprintf);
}
