#include "common.h"

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgShadowOfSomenthing);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgSandersBack);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterStart);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterCorpse);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterEnd);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgBloodSwamp);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgGetApartGateKey);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgUseApartGateKey);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgLookMemoFalled);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvStageInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvCharaDataClear);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvAllTimeFunc);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvBgmControl);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvLockSetCb46);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvCorpseSetCb18);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvCorpseSetCb26);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvWallSetCb19);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvWallSetCb20);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvWallSetCb21);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvWallSetCb49);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvWallSetCb52);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb27);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb28);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb29);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb35);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb36);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb37);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvTapeSetCb11);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvTapeSetCb12);

/* static */ float stg_town_east_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_CB_1stMoster_FogHosei);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_CB_1stMonster_Filter);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Draw_CB_Tonnel);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Monster1st_Look);
