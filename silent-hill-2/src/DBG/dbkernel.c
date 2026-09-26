#include "dbkernel.h"

#line 55
static int ___dbPrintThre(int tid, /* r2 */ int (* printf)()) {
    char * help;                             // r2
    char str[256];                           // r29+0x20
    ThreadParam thre;                        // r29+0x120
    int ret = ReferThreadStatus(tid, &thre); // r16;
    if (ret) {

        help = (char *)(thre.option & 0x1FFFFFF);
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


static void ___dbPrintThreAll(int (* printf)() /* r18 */){

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
