#ifndef SH2_SCF_H
#define SH2_SCF_H

#include "sh2_common.h"
#include "sce/libcdvd.h"
#include "sce/libscf.h"
#include "Multi_thr/scf/ps2_scf.h"

typedef enum SPEC_LANG_O {
    SPEC_LANG_JPN_O = 0,
    SPEC_LANG_ENG_O = 1,
    SPEC_LANG_FRN_O = 2,
    SPEC_LANG_GER_O = 3,
    SPEC_LANG_ITA_O = 4,
    SPEC_LANG_SPN_O = 5,
} SPEC_LANG_O;

void sh2ScfInit(void);

SPEC_LANG_O sh2ScfGetDefaultLanguage(void);

u_int UtilBCDToDecimal(u_int bcd);

int sh2ScfMakeDateStr(s_char* datestr, u_int year, u_int month, u_int day);

int sh2ScfMakeDateStrByLocalTimeFromJST(s_char* datestr, sceCdCLOCK* jst);

int sh2ScfMakeTimeStr(s_char* timestr, u_int hour24, u_int minute, u_int second);

int sh2ScfMakeTimeStrFromRTC(s_char* timestr, sceCdCLOCK* rtc);

int sh2ScfMakeTimeStrByLocalTimeFromJST(s_char* datestr, sceCdCLOCK* jst);

#endif // SH2_SCF_H
