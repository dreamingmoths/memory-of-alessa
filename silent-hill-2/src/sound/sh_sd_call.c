#include "sound/sh_sd_call.h"

static int shSdCallCheck(int i0 /* r16 */);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdWaitExcl);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdSignalExcl);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdInit);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", sd_stat_now_cd_using);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdVSync);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdCallCheck);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdCall);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdSeStop);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdStat);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSd3dCall);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSd3dMove);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSd3dStop);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSd3dAllStop);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdSeChange);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdTrack);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSdRadio);

INCLUDE_ASM("asm/nonmatchings/sound/sh_sd_call", shSd3dAdrs);
