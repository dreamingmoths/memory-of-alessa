#include "sound/sh_sd_call.h"
#include "eekernel.h"
#include "Multi_thr/filesys/sh_cdvd.h"
#include "DBG/dbflag.h"

static int shSdWaitExcl(void);
static int shSdSignalExcl(void);
static int sd_stat_now_cd_using(void);
static int shSdCallCheck(int i0 /* r16 */);
static int shSdCallCheck(int i0);

extern /* static */ int excl_sid; // size: 0x4, address: 0x37B8D8
extern /* static */ int cd_sd_now_access; // size: 0x4, address: 0x122B308

static int shSdWaitExcl(void) {
    return WaitSema(excl_sid);
}

static int shSdSignalExcl(void) {
    return SignalSema(excl_sid);
}

int shSdInit(void) {
    if (excl_sid == -1) {
        excl_sid = CreateSema2(0, 1, 0);
    }
    shSdSignalExcl();
    return 1;
}

static int sd_stat_now_cd_using(void) {
    int stat; // r2
    int ret; // r4
    
    stat = sd_stat();
    ret = (stat & 0xF) != 0;
    ret |= ((1 << ((stat >> 4) & 0xF)) & ~0x21) != 0;
    return ret;
}

void shSdVSync(void) {
    if (!dbFlag(1)) {
        shSdWaitExcl();
        if ((cd_sd_now_access == 0) && (sd_stat_now_cd_using() != 0)) {
            cd_sd_now_access = 1;
            shCdSdStart();
        }
        sd_vsync();
        if ((cd_sd_now_access != 0) && (sd_stat_now_cd_using() == 0)) {
            shCdSdEnd();
            cd_sd_now_access = 0;
        }
        sd_stat();
        shSdSignalExcl();
    }
}

static int shSdCallCheck(int i0) {
    if (dbFlag(1)) {
        return 0;
    }
    switch (i0) {
        case 0x5DC:
            if (!dbFlag(2)) {
                return 0;
            }
            break;        
        default:
            if ((i0 < 0x1388 || 0x13D6 < i0) && (i0 < 0xEA60 || 0xEAB6 < i0)) {
                if (i0 >= 0x1770 && i0 < 0x17B0) {
                    if (!dbFlag(2)) {
                        return 0;
                    }
                } 
                else if (i0 >= 0xF618) {
                    if (!dbFlag(2)) {
                        return 0;
                    }
                }
            }
    }    
    return 1;
}

int shSdCall(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */) {
    int ret; // r16
    if (!shSdCallCheck(i0)) return 0;
    shSdWaitExcl();
    ret = sd_call(i0, i1, i2, i3);
    shSdSignalExcl();
    return ret;
}

int shSdSeStop(int i0 /* r16 */) {
    int ret; // r16
    if (!shSdCallCheck(i0)) return 0;    
    shSdWaitExcl();
    ret = sd_se_stop(i0);
    shSdSignalExcl();
    return ret;
}


int shSdStat(void) {
    int ret; // r16
    if (!shSdCallCheck(0)) return 0;    
    shSdWaitExcl();
    ret = sd_stat();
    shSdSignalExcl();
    return ret;
}

int shSd3dCall(int i0 /* r18 */, int i1 /* r17 */, int i2 /* r16 */, float f0 /* r21 */, float f1 /* r20 */) {
    int ret; // r16
    if (!shSdCallCheck(0)) return 0;
    shSdWaitExcl();
    ret = sd_3d_call(i0, i1, i2, f0, f1);
    shSdSignalExcl();
    return ret;
}

int shSd3dMove(int i0 /* r18 */, int i1 /* r17 */, int i2 /* r16 */, float f0 /* r21 */, float f1 /* r20 */) {
    int ret; // r16
    if (!shSdCallCheck(0)) return 0;
    shSdWaitExcl();
    ret = sd_3d_move(i0, i1, i2, f0, f1);
    shSdSignalExcl();
    return ret;
}

void shSd3dStop(int i0 /* r16 */) {
    if (shSdCallCheck(0)) {
        shSdWaitExcl();
        sd_3d_stop(i0);
        shSdSignalExcl();
    }
}

void shSd3dAllStop(void) {
    if (shSdCallCheck(0)) {
        shSdWaitExcl();
        sd_3d_allstop();
        shSdSignalExcl();
    }
}

int shSdSeChange(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */) {
    int ret; // r16
    if (shSdCallCheck(0) == 0) return 0;    
    shSdWaitExcl();
    ret = sd_se_change(i0, i1, i2, i3);
    shSdSignalExcl();
    return ret;
}

int shSdTrack(int i0 /* r17 */, int i1 /* r16 */) {
    int ret; // r16
    if (!shSdCallCheck(0)) return 0;
    shSdWaitExcl();
    ret = sd_track(i0, i1);
    shSdSignalExcl();
    return ret;
}

int shSdRadio(int i0 /* r19 */, int i1 /* r18 */, int i2 /* r17 */, int i3 /* r16 */) {
    int ret; // r16
    if (!shSdCallCheck(0)) return 0;
    shSdWaitExcl();
    ret = sd_radio(i0, i1, i2, i3);
    shSdSignalExcl();
    return ret;
}

void* shSd3dAdrs(void) {
    void* ret; // r16
    shSdWaitExcl();
    ret = sd_3d_adrs();
    shSdSignalExcl();
    return ret;
}
