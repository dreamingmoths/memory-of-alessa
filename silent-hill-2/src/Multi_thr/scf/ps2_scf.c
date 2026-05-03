#include "sh2_common.h"
#include "eekernel.h"
#include "libscf.h"

#define TZ_UTC_9 540

static sceScfT10kConfig ps2ScfDefault = {
    /* .TimeZone     = */ TZ_UTC_9,
    /* .Aspect       = */ SCE_ASPECT_43,
    /* .DateNotation = */ SCE_DATE_YYYYMMDD,
    /* .Language     = */ SCE_ENGLISH_LANGUAGE,
    /* .Spdif        = */ SCE_SPDIF_OFF,
    /* .SummerTime   = */ SCE_SUMMERTIME_OFF,
    /* .TimeNotation = */ SCE_TIME_24HOUR
};

static int excl_sid = -1;














void ps2ScfInit(void) {
    if (excl_sid == -1) {
        excl_sid = CreateSema2(NULL, 1, 0);
        sceScfSetT10kConfig(&ps2ScfDefault);
        SignalSema(excl_sid);
    }
}


int ps2ScfGetLanguage(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetLanguage();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetAspect(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetAspect();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetSpdif(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetSpdif();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetTimeZone(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetTimeZone();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetDateNotation(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetDateNotation();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetSummerTime(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetSummerTime();
    SignalSema(excl_sid);
    return ret;
}


int ps2ScfGetTimeNotation(void) {
    int ret;
    WaitSema(excl_sid);
    ret = sceScfGetTimeNotation();
    SignalSema(excl_sid);
    return ret;
}


void ps2ScfGetLocalTimefromRTC(sceCdCLOCK* rtc) {
    WaitSema(excl_sid);
    sceScfGetLocalTimefromRTC(rtc);
    SignalSema(excl_sid);
}
