#include "Multi_thr/scf/sh2_scf.h"

#define TZ_UTC_0 0
static sceScfT10kConfig sh2ScfInfo = {
    /* .TimeZone     = */ TZ_UTC_0,
    /* .Aspect       = */ SCE_ASPECT_43,
    /* .DateNotation = */ SCE_DATE_YYYYMMDD,
    /* .Language     = */ SCE_JAPANESE_LANGUAGE,
    /* .Spdif        = */ SCE_SPDIF_ON,
    /* .SummerTime   = */ SCE_SUMMERTIME_OFF,
    /* .TimeNotation = */ SCE_TIME_24HOUR
};

void sh2ScfInit(void) {
    ps2ScfInit();
    sh2ScfInfo.TimeZone     = ps2ScfGetTimeZone();
    sh2ScfInfo.Aspect       = ps2ScfGetAspect();
    sh2ScfInfo.DateNotation = ps2ScfGetDateNotation();
    sh2ScfInfo.Language     = ps2ScfGetLanguage();
    sh2ScfInfo.Spdif        = ps2ScfGetSpdif();
    sh2ScfInfo.SummerTime   = ps2ScfGetSummerTime();
    sh2ScfInfo.TimeNotation = ps2ScfGetTimeNotation();
}


SPEC_LANG_O sh2ScfGetDefaultLanguage(void) {
    switch(sh2ScfInfo.Language) {
        case SCE_ENGLISH_LANGUAGE:
        case SCE_DUTCH_LANGUAGE:
        case SCE_PORTUGUESE_LANGUAGE:
        default:                     return SPEC_LANG_ENG_O;
        case SCE_JAPANESE_LANGUAGE:  return SPEC_LANG_JPN_O;
        case SCE_FRENCH_LANGUAGE:    return SPEC_LANG_FRN_O;
        case SCE_SPANISH_LANGUAGE:   return SPEC_LANG_SPN_O;
        case SCE_GERMAN_LANGUAGE:    return SPEC_LANG_GER_O;
        case SCE_ITALIAN_LANGUAGE:   return SPEC_LANG_ITA_O;
    }
}




u_int UtilBCDToDecimal(u_int bcd) {
    u_int dec = 0; // r2
    int keta = 1; // r5
    while (bcd != 0) {
        dec += (bcd & 0xF) * keta;
        bcd >>= 4;
        keta *= 10;
    }
    return dec;
}



















int sh2ScfMakeDateStr(s_char* datestr, u_int year, u_int month, u_int day) {
    switch (sh2ScfInfo.DateNotation) {              /* irregular */
        case SCE_DATE_YYYYMMDD:
            sprintf(datestr, "%04d/%02d/%02d", year, month, day);
            break;
        case SCE_DATE_MMDDYYYY:
            sprintf(datestr, "%02d/%02d/%04d", month, day, year);
            break;
        case SCE_DATE_DDMMYYYY:
            sprintf(datestr, "%02d/%02d/%04d", day, month, year);
            break;
    }


    return 10;
}













int sh2ScfMakeDateStrByLocalTimeFromJST(s_char* datestr, sceCdCLOCK* jst) {
    u_int year; // r16
    u_int month; // r17
    u_int day; // r2
    sceCdCLOCK rtc[1]; // r29+0x68
    *rtc = *jst;
    ps2ScfGetLocalTimefromRTC(rtc);
    year = UtilBCDToDecimal(rtc->year) + 2000;
    month = UtilBCDToDecimal(rtc->month);
    day = UtilBCDToDecimal(rtc->day);


    if (rtc->year == 153 && jst->year == 0) year -= 100;
    if (rtc->year == 0 && jst->year == 153) year += 100;

    return sh2ScfMakeDateStr(datestr, year, month, day);
}






int sh2ScfMakeTimeStr(s_char* timestr, u_int hour24, u_int minute, u_int second) {
    if (sh2ScfInfo.TimeNotation == SCE_TIME_24HOUR) {
        sprintf(timestr, "%02d:%02d:%02d", hour24, minute, second);
        return 8;
    }
    sprintf(timestr, "%2d:%02d:%02d %cM", ((hour24 + 11) % 12) + 1, minute, second, hour24 < 12 ? 'A' : 'P');

    return 12;

}


int sh2ScfMakeTimeStrFromRTC(s_char* timestr, sceCdCLOCK* rtc) {
    u_int hour; // r16
    u_int minute; // r17
    u_int second; // r2

    hour   = UtilBCDToDecimal(rtc->hour);
    minute = UtilBCDToDecimal(rtc->minute);
    second = UtilBCDToDecimal(rtc->second);

    return sh2ScfMakeTimeStr(timestr, hour, minute, second);
}


int sh2ScfMakeTimeStrByLocalTimeFromJST(s_char* datestr, sceCdCLOCK* jst) {
    sceCdCLOCK rtc[1]; // r29+0x28
    *rtc = *jst;
    ps2ScfGetLocalTimefromRTC(rtc);
    return sh2ScfMakeTimeStrFromRTC(datestr, rtc);
}

