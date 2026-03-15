#include "cl_main.h"

void clAllInitCollisionData() {
    clCharaListAct = 0;
    clDynamicWallListAct = 0;
    clDynamicFloorListAct = 0;
    clCharaListUse[0] = 0;
    clCharaListUse[1] = 0;
    clDynamicWallList->use = 0;
    clDynamicWallList[1].use = 0;
    clDynamicFloorList->use = 0;
    clDynamicFloorList[1].use = 0;
    clBattleResult[CL_BATTLE_RESULT_SIZE - 1].atr = 0;
    clUseBattleResult = 0;
    clCollisionEnable = 1;
}

void clFrameInitCollisionData() {
    clCharaListAct = clCharaListAct ? 0 : 1;
    clCharaListUse[clCharaListAct] = 0;
    clUseBattleQue = 0;
    clDynamicWallListAct = clDynamicWallListAct ? 0 : 1;
    clDynamicWallList[clDynamicWallListAct].use = 0;
    clDynamicFloorListAct = clDynamicFloorListAct ? 0 : 1;
    clDynamicFloorList[clDynamicFloorListAct].use = 0;
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaPosition);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clSetCharaHitColumn);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddDynamicWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddDynamicFloor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaALL);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddCollectVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckBg2Chara);

static void clCheckHitWallCollision(CL_HITPOLY_COLUMN* col, s32* whnum, CL_HITPOLY_PLANE* pl, s32* ptr) {
    CL_HITRESULT cres;

    while (*ptr != -1) {
        // check if column intersects wall
        clCheckColumn2WallHit(&cres, &pl[*ptr], col);
        if (cres.chk != 0) {
#ifdef DEBUG
            if (!(*whnum < 32)) {
                printf("cl_main.c:1194> assert:(%s)\n", "*whnum < 32");
                while (1) {};
            }
#endif
            // store result in clWallHitData
            clWallHitData[*whnum].kind = cres.chk;
            clWallHitData[*whnum].pl = (CL_HITPOLY_PLANE*) cres.pd;
            cres.cv[1] = 0.0f; // zero out y value of collision vector, since this is wall collision
            vec_copy(&clWallHitData[*whnum].cv, &cres.cv);

            *whnum += 1;
        }
        ptr++;
    }
}

static void clCheckHitDynamicWallCollision(CL_HITPOLY_COLUMN* col, s32* whnum) {
    int ac; // r2
    struct _CL_HITRESULT cres; // r29+0x60
    int i; // r16

    ac = clDynamicWallListAct ? 0 : 1;

    for (i = 0; i < clDynamicWallList[ac].use; i++) {
        int j; // r17
        for (j = 0; clDynamicWallList[ac].dw[i][j].kind != 0; j++) {
            // check if column intersects dynamic wall
            clCheckColumn2WallHit(&cres, &clDynamicWallList[ac].dw[i][j], col);

            if (cres.chk != 0) {
#ifdef DEBUG
                if (!(*whnum < 32)) {
                    printf("cl_main.c:1194> assert:(%s)\n", "*whnum < 32");
                    while (1) {};
                }
#endif

                // store result in clWallHitData
                clWallHitData[*whnum].kind = cres.chk;
                clWallHitData[*whnum].pl = (CL_HITPOLY_PLANE*) cres.pd;
                cres.cv[1] = 0.0f; // zero out y value of collision vector, since this is wall collision
                vec_copy(&clWallHitData[*whnum].cv, &cres.cv);

                *whnum += 1;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clMakeWallHitCollectVector);

void clAddWallCollectVector(float* v0, float* v1, int* flg) {
    float tv[4];

    if (*flg == 0) {
        vec_copy(v0, v1);
    } else {
        vec_add(v0, v1, tv);

        if (v0[0] > v1[0])
            tv[0] = tv[0] < v1[0] ? v1[0] : MIN(tv[0], v0[0]);
        else
            tv[0] = tv[0] < v0[0] ? v0[0] : MIN(tv[0], v1[0]);

        if (v0[2] > v1[2])
            tv[2] = tv[2] < v1[2] ? v1[2] : MIN(tv[2], v0[2]);
        else
            tv[2] = tv[2] < v0[2] ? v0[2] : MIN(tv[2], v1[2]);

        vec_copy(v0, &tv[0]);
    }

    *flg += 1;
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckColumn2WallHit);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckColumn2ColumnHit);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaHeightNormal);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clBattleAddQue);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clBattleGetResult);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clBattleCheckExec);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clModifiedBattleData);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clSetOneBattleResult);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clSetThrustBattleResult);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordWeapon);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitGunWeapon);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVectorWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitNoThruVectorWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVectorDynamicWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVectorDynamicWallNoThru);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVectorDynamicFloor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordVectorDynamicFloorNoThru);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitSwordWeaponThrust);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustSwordVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitGunWeaponThrust);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustGunVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustGunVectorCharacter);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListVECHIT);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListVECHITOutDoor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListVECHITInDoor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", Line2PlaneBoundaryCheckXZ);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckCrossLine2BoxXZ);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckCrossLine2LineXZ);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVE);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVEOutDoor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVEInDoor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyes);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyesOnlyFloor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyesOnlyFloorThru);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyesOnlyWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyesOnlyFloorCeil);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorNoThru);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorAllNoThru);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorBGColumn);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorDynamicWall);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorDynamicFloor);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitEyeVectorCharacter);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clPermitColumnExpansion);
