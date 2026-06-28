#include "sh2_common.h"
#include "Event/event.h"

#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_first_toilet.h"


INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_EvProgPrologueInToilet);

/* static */ void stg_toilet_EvStageInit(void) {
    return;
}

/* static */ int stg_toilet_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_36)) {
        return 1;
    }
    return !GET_GAME_FLAG(GAME_FLAG_33) ? 4 : 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_Kari_hisyakai); // https://decomp.me/scratch/9YV5c

/* static */ float stg_toilet_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_Toilet_Dof_Filter); // https://decomp.me/scratch/dHOre
