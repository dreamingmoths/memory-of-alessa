#include "cl_main.h"
#include "LoadBg/loadbg_cld.h"
#include "SH2_common/sh_vu0.h"

static void clCheckColumn2WallHit(CL_HITRESULT* cres /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, CL_HITPOLY_COLUMN* col /* r16 */);
static void clCheckHitWallCollision(CL_HITPOLY_COLUMN* col /* r19 */, int* whnum /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, int* ptr /* r16 */);
static void clCheckColumn2ColumnHit(CL_HITPOLY_COLUMN* col /* r19 */, int* whnum /* r18 */, CL_HITPOLY_COLUMN* cl /* r17 */, int* ptr /* r16 */);
static void clCollectCharaHeightNormal(struct SubCharacter* sc /* r17 */);
static CL_SELECT_MAP* clGetHitSectListMOVEInDoor(void);

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

INCLUDE_RODATA("asm/nonmatchings/Collision/cl_main", @1021_0x0038DC80);

INCLUDE_RODATA("asm/nonmatchings/Collision/cl_main", @1022_0x0038DCA0);

void clAddDynamicWall(CL_HITPOLY_PLANE* pl /* r2 */) {
    clDynamicWallList[clDynamicWallListAct].dw[clDynamicWallList[clDynamicWallListAct].use] = pl;
    clDynamicWallList[clDynamicWallListAct].use++;
}

void clAddDynamicFloor(CL_HITPOLY_PLANE* pl /* r2 */) {
    clDynamicFloorList[clDynamicFloorListAct].dw[clDynamicFloorList[clDynamicFloorListAct].use] = pl;
    clDynamicFloorList[clDynamicFloorListAct].use++;
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCollectCharaALL);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clAddCollectVector);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckBg2Chara);

static void clCheckHitWallCollision(CL_HITPOLY_COLUMN* col, int* whnum, CL_HITPOLY_PLANE* pl, int* ptr) {
    CL_HITRESULT cres;

    while (*ptr != -1) {
        // check if column intersects wall
        clCheckColumn2WallHit(&cres, &pl[*ptr], col);
        if (cres.chk != 0) {
            ASSERT_ON_LINE(*whnum < 32, 1194);
            // store result in clWallHitData
            clWallHitData[*whnum].kind = cres.chk;
            clWallHitData[*whnum].pl = (CL_HITPOLY_PLANE*) cres.pd;
            cres.cv[1] = 0.0f; // zero out y value of collision vector, since this is wall collision
            volatile_vec_copy(&clWallHitData[*whnum].cv, &cres.cv);

            *whnum += 1;
        }
        ptr++;
    }
}

static void clCheckHitDynamicWallCollision(CL_HITPOLY_COLUMN* col, int* whnum) {
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
                ASSERT_ON_LINE(*whnum < 32, 1237);

                // store result in clWallHitData
                clWallHitData[*whnum].kind = cres.chk;
                clWallHitData[*whnum].pl = (CL_HITPOLY_PLANE*) cres.pd;
                cres.cv[1] = 0.0f; // zero out y value of collision vector, since this is wall collision
                volatile_vec_copy(&clWallHitData[*whnum].cv, &cres.cv);

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


static void clCheckColumn2ColumnHit(CL_HITPOLY_COLUMN* col, int* whnum, CL_HITPOLY_COLUMN* cl, int* ptr) {
    CL_HITRESULT cres; // r29+0x50
    int* cur;
    
    for (cur = ptr; *cur != -1; cur++) {
        int hitchk; // r2
        hitchk = clCheckSubColumnToColumn(&cres, &cl[*cur].p, &col->p);
        
        if (hitchk == 1) {
            ASSERT_ON_LINE(*whnum < 32, 1658);
            
            clWallHitData[*whnum].kind = 3;
            cres.cv[1] = 0.0f;
            volatile_vec_copy(clWallHitData[*whnum].cv, cres.cv);
            *whnum += 1;
        }
    }
}

static void clCollectCharaHeightNormal(SubCharacter* sc) {
    float st[4]; // r29+0x30
    Vector4* pos = &sc->pos; // r2
    float ed[4]; // r29+0x40
    CL_VHIT_RESULT res; // r29+0x50

    st[0] = pos->x;
    st[1] = -500.0f + pos->y;
    st[2] = pos->z;
    st[3] = 1.0f;
    ed[0] = pos->x;
    ed[1] = 1500.0f + pos->y;
    ed[2] = pos->z;
    ed[3] = 1.0f;
    
    clCheckHitEyesOnlyFloor(&res, 0, &st, &ed);
    if (res.kind == 1) {
        // @bug duplicated line?
        pos->y = res.hobj.wall.cp[1];
        pos->y = res.hobj.wall.cp[1];

        vec_copy(&sc->grnd_normal, &res.hobj.wall.nl);
        sc->grnd_height = res.hobj.wall.cp[1];
    }
}

void clBattleAddQue(CL_BATTLE_QUE* que) {
    ASSERT_ON_LINE(clUseBattleQue < 64, 1729);
    memcpy(&clBattleQue[clUseBattleQue], que, sizeof(CL_BATTLE_QUE));
    clUseBattleQue += 1;
}

#ifdef NON_MATCHING
CL_BATTLE_RESULT* clBattleGetResult(u_int id, CL_BATTLE_RESULT* before) {
    CL_BATTLE_RESULT* temp_v0;
    int i;

    for (i = before == 0 ? 0 : 1 - before->enable; i < clUseBattleResult; i++) {
        if (id == clBattleResult[i].id) {
            if (clBattleResult[i].enable > 0) {
                clBattleResult[i].enable = -i;
                return &clBattleResult[i];
            }
        }
    }

    return &clBattleResult[0x40];
}
#else
INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clBattleGetResult);
#endif

const char rodata_1691[] = "cl_main.c:1869> assert:(%s)\n";

INCLUDE_RODATA("asm/nonmatchings/Collision/cl_main", @1692);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clBattleCheckExec);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clModifiedBattleData);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clSetOneBattleResult);

INCLUDE_RODATA("asm/nonmatchings/Collision/cl_main", @1813);

INCLUDE_RODATA("asm/nonmatchings/Collision/cl_main", @1814);

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

int clCheckCrossLine2LineXZ(float* va0, float* va1, float* vb0, float* vb1) {
    float bp[4]; // r29
    float p0[4]; // r29+0x10
    float p1[4]; // r29+0x20
    float outer0; // r4
    float outer1; // r1
    vec_sub(va1, va0, bp);
    vec_sub(vb0, va0, p0);
    vec_sub(vb1, va0, p1);
    outer0 = bp[0] * p0[2] - bp[2] * p0[0];
    outer1 = bp[0] * p1[2] - bp[2] * p1[0];
    if (outer0 == 0.0f && outer1 == 0.0f) {
        if ((va0[0] <= float_max(vb0[0], vb1[0])  &&
             va0[0] >= float_min(vb0[0], vb1[0])  &&
             va0[2] <= float_max(vb0[2], vb1[2])  &&
             va0[2] >= float_min(vb0[2], vb1[2])) ||
            (va1[0] <= float_max(vb0[0], vb1[0])  &&
             va1[0] >= float_min(vb0[0], vb1[0])  &&
             va1[2] <= float_max(vb0[2], vb1[2])  &&
             va1[2] >= float_min(vb0[2], vb1[2])) ||
            (vb0[0] <= float_max(va0[0], va1[0])  &&
             vb0[0] >= float_min(va0[0], va1[0])  &&
             vb0[2] <= float_max(va0[2], va1[2])  &&
             vb0[2] >= float_min(va0[2], va1[2])) ||
            (vb1[0] <= float_max(va0[0], va1[0])  &&
             vb1[0] >= float_min(va0[0], va1[0])  &&
             vb1[2] <= float_max(va0[2], va1[2])  &&
             vb1[2] >= float_min(va0[2], va1[2]))
        ) {
            return 1;
        }
        return 0;
    }

    if (outer0 * outer1 >= 0.0f) {
        return 0;
    }
    vec_sub(vb1, vb0, bp);
    vec_sub(va0, vb0, p0);
    vec_sub(va1, vb0, p1);
    outer0 = bp[0] * p0[2] - bp[2] * p0[0];
    outer1 = bp[0] * p1[2] - bp[2] * p1[0];
    if (outer0 * outer1 >= 0.0f) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVE);

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clGetHitSectListMOVEOutDoor);

static CL_SELECT_MAP* clGetHitSectListMOVEInDoor(void) {
    int use = 0;
    CL_CLDHEADER* ch;

    if (clCollisionEnable != 0) {
        void** list = loadBgCLD_GetLoadedDataAddrList();

        for (; ch = *list, ch != NULL; list++) {
            if (ch->disable) {
                continue;
            }

            clSelectMap[use].base = ch;
            clSelectMap[use].sect = 0;
            use++;
        }
    }

    clSelectMap[use].base = NULL;

    return clSelectMap;
}

void clCheckHitEyes(CL_VHIT_RESULT* res /* r2 */, u_int id /* r2 */, float* st /* r2 */, float* ed /* r2 */, int thru /* r2 */) {
    switch (thru) {
        case 1:
            clCheckHitEyeVector(res, id, st, ed);
            return;
        case 0:
            clCheckHitEyeVectorNoThru(res, id, st, ed);
            return;
        case 2:
            clCheckHitEyeVectorAllNoThru(res, id, st, ed);
            return;
    }
}

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
