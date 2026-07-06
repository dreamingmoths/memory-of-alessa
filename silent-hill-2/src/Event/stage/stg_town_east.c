#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/demoview.h"
#include "Event/item.h"

#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"

#include "Collision/cl_main.h"

#include "GFW/sh2gfw_2d_filters.h"

#include "sh2shd/sh2shd_shadow_model.h"

extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb11[8]; // @ 0x1F05580
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb12[7]; // @ 0x1F05800
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb18[4]; // @ 0x1F05A30
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb19[10]; // @ 0x1F05B70
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb20[10]; // @ 0x1F05E90
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb21[2]; // @ 0x1F061B0
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb49[14]; // @ 0x1F06250
extern /* static */ CL_HITPOLY_PLANE stg_town_east_clActWallList_cb52[2]; // @ 0x1F066B0

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgShadowOfSomenthing);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgSandersBack);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterStart);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterCorpse);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgFirstMonsterEnd);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgBloodSwamp);

/* static */ int stg_town_east_EvProgGetApartGateKey(void) {
    return EvSubItemGetAndAnim(APART_GATE_KEY, 18);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvProgUseApartGateKey);

/* static */ int stg_town_east_EvProgLookMemoFalled(void) {
    int i; // r5
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20001);
            EV_PROG_STEP(16);
            /* fallthrough */
        case 16:
            if (ev_cancel) {
                ev_prog_flag_set = 0;
                EV_PROG_STEP(13);
            } else if (PlayerEventAnimeSuccessFrame()) {
                shCharacterAnimePause(sh2jms.player);
                if (GET_GAME_FLAG(GAME_FLAG_51)) {
                    if (!GET_GAME_FLAG(GAME_FLAG_50)) {
                        EV_PROG_STEP(30);
                    } else {
                        EV_PROG_STEP(31);
                    }
                } else if (!GET_GAME_FLAG(GAME_FLAG_52) && !GET_GAME_FLAG(GAME_FLAG_54) && !GET_GAME_FLAG(GAME_FLAG_56) && !GET_GAME_FLAG(GAME_FLAG_58) && !GET_GAME_FLAG(GAME_FLAG_610)) {
                    EV_PROG_STEP(30);
                } else {
                    EV_PROG_STEP(31);
                }
            }
            break;
        
        case 30:
            if (GET_GAME_FLAG(GAME_FLAG_51)) {
                if (!EvSubMessage(26)) break;
            } else {
                if (!EvSubMessage(27)) break;
            }        
            EV_PROG_STEP(31);
            case 31:
                if ((!GET_GAME_FLAG(GAME_FLAG_51) || EvSubMessage(20)) && (!GET_GAME_FLAG(GAME_FLAG_53) || EvSubMessage(21)) && (!GET_GAME_FLAG(GAME_FLAG_55) || EvSubMessage(22)) && (!GET_GAME_FLAG(GAME_FLAG_57) || EvSubMessage(23)) && (!GET_GAME_FLAG(GAME_FLAG_59) || EvSubMessage(24)) && (!GET_GAME_FLAG(GAME_FLAG_611) || EvSubMessage(25))) {
                    if (ev_cancel) {
                        EV_PROG_STEP(13);
                        break;
                    }
                    shCharacterAnimeRestart(sh2jms.player);
                    EV_PROG_STEP(1);
                case 1:
                    if ((shCharacterAnimeIsEnd(sh2jms.player)) && (ev_cancel == 0)) {
                        EV_PROG_STEP(13);
                        case 13:
                            i = 0;
                            while (i < 5) {
                                UNSET_GAME_FLAG((i * 2) + 51);
                                i++;
                            }
                            SCNowPlayableEventSwitch(sh2jms.player, false);
                            return 1;
                    }
                    break;
                }
    }
    return 0;
}

/* static */ void stg_town_east_EvStageInit(void) {
    if (GET_GAME_FLAG(GAME_FLAG_1303)) 
        SET_GAME_FLAG(GAME_FLAG_1269);    
    if (GET_GAME_FLAG(GAME_FLAG_1302))
        SET_GAME_FLAG(GAME_FLAG_1268);    
    if (GET_GAME_FLAG(GAME_FLAG_1266))
        SET_GAME_FLAG(GAME_FLAG_1295);
}

/* static */ int stg_town_east_EvCharaDataClear(void) {
    return !GET_GAME_FLAG(GAME_FLAG_43);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvAllTimeFunc);

/* static */ int stg_town_east_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_518)) {
        return 4;
    }
    return GET_GAME_FLAG(GAME_FLAG_41) != 0;
}

/* static */ void stg_town_east_EvLockSetCb46(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_49)) {
        EvDispControlModelEntry(list, 0x2E, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x2E, 1);
}

/* static */ void stg_town_east_EvCorpseSetCb18(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb18);
        EvDispControlModelEntry(list, 0x12, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0x12, -1);
}

/* static */ void stg_town_east_EvCorpseSetCb26(void) {
    return;
}

/* static */ void stg_town_east_EvWallSetCb19(int* list) {
    EvDispControlModelEntry(list, 0x13, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x13, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb19);
    }
}

/* static */ void stg_town_east_EvWallSetCb20(int* list) {
    EvDispControlModelEntry(list, 0x14, -1); // @todo: add room id
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x14, 0);
        clAddDynamicWall(stg_town_east_clActWallList_cb20);
    }
}

/* static */ void stg_town_east_EvWallSetCb21(int* list) {
    EvDispControlModelEntry(list, 0x15, -1);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        clAddDynamicWall(stg_town_east_clActWallList_cb21);
        EvDispControlModelEntry(list, 0x15, 0);
        return;
    }
    sh2shd_add_map_to_shadow_off_work(0x15);
    sh2shd_off_obj(0x15, 8); // @todo: add room id and obj id
}

/* static */ void stg_town_east_EvWallSetCb49(int* list) {
    if (!GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x31, 1); // @todo: add room id
        clAddDynamicWall(&stg_town_east_clActWallList_cb49[4]);
        return;
    }
    EvDispControlModelEntry(list, 0x31, 0);
    clAddDynamicWall(stg_town_east_clActWallList_cb49);
}

/* static */ void stg_town_east_EvWallSetCb52(int* list) {
    sh2shd_add_map_to_shadow_off_work(0x34);
    if (GET_GAME_FLAG(GAME_FLAG_251)) {
        EvDispControlModelEntry(list, 0x34, 1);
        clAddDynamicWall(stg_town_east_clActWallList_cb52);
        sh2shd_off_obj(0x34, 0x37); // @todo: add room id and obj id
        return;
    }
    EvDispControlModelEntry(list, 0x34, 0);
    sh2shd_off_obj(0x34, 0x36);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb27);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb28);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb29);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb35);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb36);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_EvSignalControlCb37);

/* static */ void stg_town_east_EvTapeSetCb11(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xB, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xB, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb11);
}

/* static */ void stg_town_east_EvTapeSetCb12(int* list) {
    if (GET_GAME_FLAG(GAME_FLAG_43)) {
        EvDispControlModelEntry(list, 0xC, 0); // @todo: add room id
        return;
    }
    EvDispControlModelEntry(list, 0xC, 1);
    clAddDynamicWall(stg_town_east_clActWallList_cb12);
}

/* static */ float stg_town_east_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_CB_1stMoster_FogHosei);

/* static */ void stg_town_east_CB_1stMonster_Filter(void) {
    FilterParams* pfp; // r16
    sceVu0FVECTOR campos; // r29+0x20
    
    vwGetViewPosition(campos);
    if ((campos[2] < 50000.0f) && (campos[1] > -2000.0f) && ((DramaDemoNumber() == 6) || (DramaDemoNumber() == 7))) {
        pfp = sh2gfw_Get_FilterCommandParams();
        sh2gfw_Reset_FilterCommand();
        shGsFilterWork.GsFilterKind = 6;
        pfp->SoftIter = 3;
        pfp->SoftCit = 25;
        pfp->SoftAref = 216;
        pfp->SoftShift = -4;
        pfp->base_Ix = -8;
        pfp->base_Iy = -8;
        return;
    }
    if (shGsFilterWork.GsFilterKind < 15) {
        sh2gfw_Reset_FilterCommand();
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Draw_CB_Tonnel);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_town_east", stg_town_east_Monster1st_Look);
