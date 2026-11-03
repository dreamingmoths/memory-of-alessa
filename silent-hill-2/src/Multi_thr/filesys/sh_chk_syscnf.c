#include "Multi_thr/filesys/sh_chk_syscnf.h"

static int check_func(fsFile** fplist, void** buflist);

static u_long128 check_buf[1][128]; // size: 0x800, address: 0x1159280
static fsFile* check_fplist[2]     = {z_root_system_cnf__info}; // size: 0x8, address: 0x33B3F8
static void* check_buflist[2]      = {check_buf}; // size: 0x8, address: 0x33B400



























































static int check_func(fsFile** fplist /* r17 */, void** buflist /* r16 */)
{
    int size; // r4
    int disk_number; // r5
    fsFile realfp[1]; // r29+0x30
    s_char* chp; // r6
    s_char ch; // r2
    int step; // r7
    if (fsCmdCheckExistFile(*fplist) <= 0) return 0;
    if (fsCmdSetRealFile(realfp, *fplist) == 0) return 0;
    size = realfp->cd.size;
    if (size >= 0x7FE) {


        size = 0x7FE;
    }
    if (((s_char*)*buflist)[size - 1] == '\n') {

        ((s_char*)*buflist)[size] = 0;
    } else {

        ((s_char*)*buflist)[size] = '\n';
        ((s_char*)*buflist)[size + 1] = 0;
    }

    step = 0;
    disk_number = 0;
    for (chp = *buflist; (ch = *chp) != '\0'; chp++) {
        if (ch != '\r') {

            if (ch == '\n') {
                step = 0;
                continue;   }
                switch (step) {
                    case 0:
                        step = ch != 'B' ? 1 : 2;
                        break;
                    case 1:


                        break;
                    case 2:
                        if (ch == ':') {
                            disk_number = 1;
                            step++;
                        }
                        break;
                    default:

                        if (ch >= '0' && ch < ':') {
                            disk_number *= 10;
                            disk_number += ch - 0x30;
                            step++;
                        }
                        if (disk_number > 100000) {





                            if ((disk_number - 100000) != 20228)
                                return 0;
                            return (disk_number - 100000);
                        }
                }
        }

    }
    return -1;
}


int fcSetParamForSystemCnf(int debug) {
    u_int media_type; // r2
    //@todo: magic numbers
    media_type = 7;
    if (debug != 0) media_type |= 0x780;
    return fcSetParamForCheckDisk(media_type, &check_fplist, &check_buflist, check_func);

}
