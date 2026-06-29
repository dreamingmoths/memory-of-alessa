#include "common.h"

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgLetterFromMary);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgItemInCar);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgNothingTakeInCar);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgHadBetterGetMap);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgCantGoBack);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgLastScene);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvAllTimeFunc);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvBgmControl);

/* static */ float stg_ovservation_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_OB_DemoBlur);
