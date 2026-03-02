#include "common.h"

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", getFIFOindex);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", setD3_CHCR);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", setD4_CHCR_0x0028C550);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", scTag2);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufCreate);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufReset);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufBeginPut);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufEndPut);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufAddDMA);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufStopDMA);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufRestartDMA);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufDelete);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufFlush);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufModifyPts);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufPutTs);

INCLUDE_ASM("asm/nonmatchings/movie/pss_vibuf", viBufGetTs);
