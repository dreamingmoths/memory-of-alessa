#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"

#include "vec.h"

#include "LoadBg/loadbg_cld.h"

#include "Collision/cl_main.h"

static void clCollectCharaALL(void);

static void clAddCollectVector(float* v0, float* v1);

static void clCheckBg2Chara(int no);

static void clCheckHitWallCollision(CL_HITPOLY_COLUMN* col, int* whnum, CL_HITPOLY_PLANE* pl, int* ptr);

static void clCheckHitDynamicWallCollision(CL_HITPOLY_COLUMN* col, int* whnum);

static int clMakeWallHitCollectVector(struct SubCharacter* sc, float* wcv, float mang, int* flg, int num);

static void clAddWallCollectVector(float* v0, float* v1, int* flg);

static void clCheckColumn2WallHit(CL_HITRESULT* cres, CL_HITPOLY_PLANE* pl, CL_HITPOLY_COLUMN* col);

static void clCheckColumn2ColumnHit(CL_HITPOLY_COLUMN* col, int* whnum, CL_HITPOLY_COLUMN* cl, int* ptr);

static void clCollectCharaHeightNormal(struct SubCharacter* sc);

static void clModifiedBattleData(void);

static void clSetOneBattleResult(CL_BATTLE_QUE* que, CL_VHIT_RESULT* vres, float* vec);

static void clSetThrustBattleResult(CL_BATTLE_QUE* que, float* vec);

static void clCheckHitSwordWeapon(CL_VHIT_RESULT* res, u_int id, float* svs, float* sve, float* evs, float* eve);

static void clCheckHitGunWeapon(CL_VHIT_RESULT* res, u_int id, float* st, float* ed);

static void clCheckHitSwordVector(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitSwordVectorWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_PLANE* pl, int* ptr);

static void clCheckHitNoThruVectorWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_PLANE* pl, int* ptr);

static void clCheckHitSwordVectorDynamicWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitSwordVectorDynamicWallNoThru(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitSwordVectorDynamicFloor(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitSwordVectorDynamicFloorNoThru(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitSwordWeaponThrust(u_int id, float* svs, float* sve, float* evs, float* eve);

static int clCheckHitThrustSwordVector(u_int id, float* sp, float* ep);

static void clCheckHitGunWeaponThrust(u_int id, float* st, float* ed);

static void clCheckHitThrustGunVector(u_int id, float* sp, float* ep);

static void clCheckHitThrustGunVectorCharacter(float* sp, float* ep, float min, u_int id);

static CL_SELECT_MAP* clGetHitSectListVECHITOutDoor(float* st, float* ed);

static CL_SELECT_MAP* clGetHitSectListVECHITInDoor(void);

static int Line2PlaneBoundaryCheckXZ(float (* l0)[4], float (* l1)[4], float (* p0)[4], float (* p1)[4], float (* p2)[4], float (* p3)[4]);

static CL_SELECT_MAP* clGetHitSectListMOVEOutDoor(float* bpos);

static CL_SELECT_MAP* clGetHitSectListMOVEInDoor(void);

static void clCheckHitEyeVector(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorNoThru(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorAllNoThru(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_PLANE* pl, int* ptr);

static void clCheckHitEyeVectorBGColumn(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_COLUMN* cl, int* ptr);

static void clCheckHitEyeVectorDynamicWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitEyeVectorDynamicFloor(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitEyeVectorCharacter(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, u_int id);

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

#line 2738
void clCheckHitSwordWeaponThrust(u_int id /* r21 */, float* svs /* r20 */, float* sve /* r19 */, float* evs /* r18 */, float* eve /* r17 */) {
    int i; // r16
    sceVu0FVECTOR st; // r29+0x70
    sceVu0FVECTOR ed; // r29+0x80
    sceVu0FVECTOR tmp; // r29+0x90
    clVHitListUse = 0;

    
    for (i = 0; i < 5; i++) {
    
        vu0_scale_vector(st, svs, clswPerc[i]);
        vu0_scale_vector(tmp, evs, clswPerc[4 - i]);
        vu0_add_vector(st, st, tmp);
        vu0_scale_vector(ed, sve, clswPerc[i]);
        vu0_scale_vector(tmp, eve, clswPerc[4 - i]);
        vu0_add_vector(ed, ed, tmp);
        
        if (clCheckHitThrustSwordVector(id, st, ed)) break;
        
    }
}

INCLUDE_ASM("asm/nonmatchings/Collision/cl_main", clCheckHitThrustSwordVector);

void clCheckHitGunWeaponThrust(u_int id, float* st, float* ed) {
    clVHitListUse = 0;
    clCheckHitThrustGunVector(id, st, ed);
}

// @todo: figure out wtf these are
#define SMAP_WALL_BASE_START 88
#define SMAP_CL_STRIDE 16
#define SMAP_CL_START 8

void clCheckHitThrustGunVector(u_int id, float* sp, float* ep) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x6C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep));
    clVHitResult[clVHitListUse].kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitEyeVectorDynamicWall(&clVHitResult[clVHitListUse], sp, ep, &min);
    clCheckHitEyeVectorDynamicFloor(&clVHitResult[clVHitListUse], sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitEyeVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitEyeVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitEyeVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
    }
    if (clVHitResult[clVHitListUse].kind != 0) {
        clVHitListUse++;
    }
    clCheckHitThrustGunVectorCharacter(sp, ep, min, id);
}

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
