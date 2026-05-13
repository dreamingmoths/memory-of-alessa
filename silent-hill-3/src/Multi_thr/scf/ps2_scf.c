#include "common.h"
#include "Multi_thr/scf/ps2_scf.h"
#include "eekernel.h"
#include "libscf.h"

#define TZ_UTC_9 540

static const sceScfT10kConfig ps2ScfDefault = {
    /* .TimeZone     = */ TZ_UTC_9,
    /* .Aspect       = */ SCE_ASPECT_43,
    /* .DateNotation = */ SCE_DATE_YYYYMMDD,
    /* .Language     = */ SCE_JAPANESE_LANGUAGE,
    /* .Spdif        = */ SCE_SPDIF_OFF,
    /* .SummerTime   = */ SCE_SUMMERTIME_OFF,
    /* .TimeNotation = */ SCE_TIME_24HOUR
};

extern /* static */ int excl_sid;

void ps2ScfInit(void) {
    if (excl_sid == -1) {
        excl_sid = CreateSema_((SemaParam*) excl_sid);
        sceScfSetT10kConfig((void*) &ps2ScfDefault);
    }
}


int ps2ScfGetAspect(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetAspect();
    SignalSema_(excl_sid);
    return ret;
}


int ps2ScfGetSpdif(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetDateNotation();
    SignalSema_(excl_sid);
    return ret;
}


int ps2ScfGetLanguage(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetLanguage();
    SignalSema_(excl_sid);
    return ret;
}


int func_0020EC10(sceCdCLOCK* rtc) {
    WaitSema_(excl_sid);
    sceScfGetLocalTimefromRTC(rtc);
    SignalSema_(excl_sid);
}


int ps2ScfGetTimeZone(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetSpdif();
    SignalSema_(excl_sid);
    return ret;
}

int func_0020ECA0(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetSummerTime();
    SignalSema_(excl_sid);
    return ret;
}


int func_0020ECF0(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetTimeNotation();
    SignalSema_(excl_sid);
    return ret;
}


int func_0020ED40(void) {
    int ret;
    WaitSema_(excl_sid);
    ret = sceScfGetTimeZone();
    SignalSema_(excl_sid);
    return ret;
}


void ps2ScfGetLocalTimefromRTC(sceCdCLOCK* rtc) {
    WaitSema_(excl_sid);
    sceScfSetT10kConfig((void*) rtc);
    SignalSema_(excl_sid);
}
