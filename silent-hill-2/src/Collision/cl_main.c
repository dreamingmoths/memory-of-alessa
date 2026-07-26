#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "vec.h"

#include "LoadBg/loadbg_cld.h"

#include "Chacter/m3_sc.h"

#include "Collision/cl_main.h"
#include "Collision/cl_calc2.h"

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

static CL_SELECT_MAP* clGetHitSectListVECHITInDoor(float* st, float* ed); // @note dwarf missed these args.

static int Line2PlaneBoundaryCheckXZ(float (* l0)[4], float (* l1)[4], float (* p0)[4], float (* p1)[4], float (* p2)[4], float (* p3)[4]);

static CL_SELECT_MAP* clGetHitSectListMOVEOutDoor(float* bpos);

static CL_SELECT_MAP* clGetHitSectListMOVEInDoor(float* bpos);

static void clCheckHitEyeVector(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorNoThru(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorAllNoThru(CL_VHIT_RESULT* res, u_int id, float* sp, float* ep);

static void clCheckHitEyeVectorWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_PLANE* pl, int* ptr);

static void clCheckHitEyeVectorBGColumn(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, CL_HITPOLY_COLUMN* cl, int* ptr);

static void clCheckHitEyeVectorDynamicWall(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitEyeVectorDynamicFloor(CL_VHIT_RESULT* res, float* sp, float* ep, float* min);

static void clCheckHitEyeVectorCharacter(CL_VHIT_RESULT* res, float* sp, float* ep, float* min, u_int id);

// @todo: figure out wtf these are
#define SMAP_WALL_BASE_START 88
#define SMAP_CL_STRIDE 16
#define SMAP_CL_START 8


#define FLOAT_MAX 3.4028235e+38f

void clAllInitCollisionData(void) {
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

void clFrameInitCollisionData(void) {
    clCharaListAct = clCharaListAct ? 0 : 1;
    clCharaListUse[clCharaListAct] = 0;
    clUseBattleQue = 0;
    clDynamicWallListAct = clDynamicWallListAct ? 0 : 1;
    clDynamicWallList[clDynamicWallListAct].use = 0;
    clDynamicFloorListAct = clDynamicFloorListAct ? 0 : 1;
    clDynamicFloorList[clDynamicFloorListAct].use = 0;
}

void clCollectCharaPosition(void) {
    int i; // r16
    sceVu0FVECTOR dif; // r29+0x30

    clCollectCharaALL();

    for (i = 0; i < clCharaListUse[clCharaListAct]; i++) {
        clCharaList[clCharaListAct][i].col.p[0][3] = 1.0f;
        vu0_sub_vector(dif, clCharaList[clCharaListAct][i].col.p[0], clCharaList[clCharaListAct][i].opos);
        clCharaList[clCharaListAct][i].sc->pos.x += dif[0];
        clCharaList[clCharaListAct][i].sc->pos.z += dif[2];
        clCharaList[clCharaListAct][i].sc->mat.d[3][0] += dif[0];
        clCharaList[clCharaListAct][i].sc->mat.d[3][2] += dif[2];
        vu0_add_vector(clCharaList[clCharaListAct][i].wcol.p[0], clCharaList[clCharaListAct][i].wcol.p[0], dif);
        
        clCharaList[clCharaListAct][i].wcol.p[0][3] = 1.0f;
        clCharaList[clCharaListAct][i].heightfunc(clCharaList[clCharaListAct][i].sc);
        dif[0] = clCharaList[clCharaListAct][i].sc->b_pos.y - clCharaList[clCharaListAct][i].sc->pos.y;

        if (float_abs(dif[0]) > (600.0f / shGetFPS()) && !(clCharaList[clCharaListAct][i].sc->status & (1 << SCP_STATUS_BIT_FREEFALL))) {
            dif[0] /= 2.0f;
            clCharaList[clCharaListAct][i].sc->pos.y += dif[0];
            clCharaList[clCharaListAct][i].sc->mat.d[3][1] += dif[0];
            clCharaList[clCharaListAct][i].wcol.p[0][1] += dif[0];
                
        }
    }
}


void clSetCharaHitColumn(CL_HITPOLY_COLUMN* col /* r17 */, CL_HITPOLY_COLUMN* wcol /* r19 */, SubCharacter* sc /* r18 */, void (* func)() /* r16 */) {
    sceVu0FVECTOR dif; // r29+0x50

    ASSERT(clCharaListUse[clCharaListAct] < 32);

   if (col->p[1][3] == 0.0f) {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].movflg = 0;
    } else {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].movflg = 1;
    }
    if (wcol->p[1][3] == 0.0f) {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].batflg = 0;
    } else {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].batflg = 1;
    }
    memcpy(&clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].col, col, sizeof(CL_HITPOLY_COLUMN));
    memcpy(&clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].wcol, wcol, sizeof(CL_HITPOLY_COLUMN));
    vu0_sub_vector(dif, &sc->pos, &sc->b_pos);
    vu0_sub_vector(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].pos, col->p[0], dif);
    vu0_sub_vector(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].col.p[0], col->p[0], dif);
    volatile_vec_copy(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].opos, col->p);
    clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].sc = sc;
    vu0_sub_vector(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mvec, &sc->pos, &sc->b_pos);

    if (clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mvec[0] == 0.0f && clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mvec[2] == 0.0f) {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mang = FLOAT_MAX;
    } else {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mang = shAtan2(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mvec[0], clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].mvec[2]);
    }
    vec_zero(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].ccvec);
    if (func == NULL) {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].heightfunc = clCollectCharaHeightNormal;
    } else {
        clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].heightfunc = func;
    }
    vec_zero(clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].wallcv);
    clCharaList[clCharaListAct][clCharaListUse[clCharaListAct]].wflg = 0;
    clCharaListUse[clCharaListAct] += 1;
}

void clAddDynamicWall(CL_HITPOLY_PLANE* pl /* r2 */) {
    clDynamicWallList[clDynamicWallListAct].dw[clDynamicWallList[clDynamicWallListAct].use] = pl;
    clDynamicWallList[clDynamicWallListAct].use++;
}

void clAddDynamicFloor(CL_HITPOLY_PLANE* pl /* r2 */) {
    clDynamicFloorList[clDynamicFloorListAct].dw[clDynamicFloorList[clDynamicFloorListAct].use] = pl;
    clDynamicFloorList[clDynamicFloorListAct].use++;
}

void clCollectCharaALL(void) {
    int i; // r16
    int j; // r20
    int hit; // r17
    int limit; // r18
    
    for (limit = 0; limit < 5; limit++) {
        CL_HITPOLY_COLUMN* col0, *col1; /* r19, r21 */
        for (i = 0; i < clCharaListUse[clCharaListAct]; i++) {
            CL_HITRESULT cres; /* r29+0x70 */
            float dist; /* r29+0xE0 */
            col0 = &clCharaList[clCharaListAct][i].col;

            volatile_vec_copy(clCharaList[clCharaListAct][i].pos, &col0->p);
            
            
            if (clCharaList[clCharaListAct][i].ccvec[0] == 0.0f)
                col0->p[0][0] += clCharaList[clCharaListAct][i].mvec[0];
            
            
            else if ((clCharaList[clCharaListAct][i].ccvec[0] * clCharaList[clCharaListAct][i].mvec[0]) < 0.0f)
                col0->p[0][0] += clCharaList[clCharaListAct][i].ccvec[0];
            
            
            else if (float_abs(clCharaList[clCharaListAct][i].ccvec[0]) > float_abs(clCharaList[clCharaListAct][i].mvec[0]))
                col0->p[0][0] += clCharaList[clCharaListAct][i].ccvec[0];
            else
                col0->p[0][0] += clCharaList[clCharaListAct][i].mvec[0];
            
            
            
            if (clCharaList[clCharaListAct][i].ccvec[2] == 0.0f)
                col0->p[0][2] += clCharaList[clCharaListAct][i].mvec[2];
            
            
            else if ((clCharaList[clCharaListAct][i].ccvec[2] * clCharaList[clCharaListAct][i].mvec[2]) < 0.0f)
                col0->p[0][2] += clCharaList[clCharaListAct][i].ccvec[2];
            
            
            else if (float_abs(clCharaList[clCharaListAct][i].ccvec[2]) > float_abs(clCharaList[clCharaListAct][i].mvec[2]))
                col0->p[0][2] += clCharaList[clCharaListAct][i].ccvec[2];
            else
                col0->p[0][2] += clCharaList[clCharaListAct][i].mvec[2];



            
            vu0_sub_vector(clCharaList[clCharaListAct][i].mvec, col0->p[0], clCharaList[clCharaListAct][i].pos);
            
            

            dist = vec_length(clCharaList[clCharaListAct][i].mvec);
            dist = (col0->p[1][3] /  dist);
            if (dist < 1.0f) 
               vu0_scale_vector(clCharaList[clCharaListAct][i].mvec, clCharaList[clCharaListAct][i].mvec, dist);
            

            if (clCharaList[clCharaListAct][i].mvec[0] == 0.0f && clCharaList[clCharaListAct][i].mvec[2] == 0.0f) {
            
                
                clCharaList[clCharaListAct][i].mang = FLOAT_MAX;
            } else {
                
                
                clCharaList[clCharaListAct][i].mang = shAtan2(clCharaList[clCharaListAct][i].mvec[0], clCharaList[clCharaListAct][i].mvec[2]);
            }
            
            
            if (clCharaList[clCharaListAct][i].movflg != 0) {
            
                clCheckBg2Chara(i);
                if (clCharaList[clCharaListAct][i].wflg != 0)
                   vu0_add_vector(col0->p,  col0->p, clCharaList[clCharaListAct][i].wallcv);
            }
            vec_zero(clCharaList[clCharaListAct][i].ccvec);
            
            for (j = 0; j < clCharaListUse[clCharaListAct]; j++) {
            
                if (i != j) {
                
                    
                    if (clCharaList[clCharaListAct][i].movflg && clCharaList[clCharaListAct][j].movflg != 0) {

                        sceVu0FVECTOR vec1; /* r29+0xB0 */
                        int wt; /* r2 */ 


                        
                        
                        col1 = &clCharaList[clCharaListAct][j].col;






                        if (clCheckSubColumnToColumn(&cres, col1->p, col0->p) != 0) {
                            
                            
                            
                            cres.cv[1] = 0.0f;
                            
                            vu0_add_vector(col0->p[0], col0->p[0], cres.cv);
                            {
                            
                                
                                
                                float div[5] = { 1.0f, 0.98f, 0.94f, 0.89f, 0.86f }; // r29+0xC0
                                float dist; /* r29+0xE0 */
                                wt = (col0->weight - col1->weight);
                                if (wt < 0)
                                    wt = 0;
                                else
                                    wt = (col0->weight - col1->weight) + 1;
                                
                                
                                vu0_scale_vector(vec1, cres.cv, 1.0f - div[wt]);
                                
                                
                                
                                vec1[0] *= -1.0f;
                                vec1[2] *= -1.0f;
                                
                                
                                
                                

                                
                                dist = vec_length(vec1);
                                dist = col0->p[1][3] / dist;
                                if (dist < 1.0f)
                                    vu0_scale_vector(cres.cv, cres.cv, -1.0f);


                                clAddCollectVector(clCharaList[clCharaListAct][j].ccvec, &vec1[0]);
                                
                                hit++;
                            }
                        }
                    }
                }


















































































































            }
            vec_zero(clCharaList[clCharaListAct][i].mvec);
            if (clCharaList[clCharaListAct][i].movflg) {

                
                clCheckBg2Chara(i);
                if (clCharaList[clCharaListAct][i].wflg)
                   vu0_add_vector(col0->p, col0->p, clCharaList[clCharaListAct][i].wallcv);
            }
        }
        
        if (hit == 0)
            break;
        
        else hit = 0;
    }
}

static void clAddCollectVector(float* v0 /* r2 */, float* v1 /* r2 */) {
    float tv[4]; // r29

    vu0_add_vector(tv, v0, v1);

    if (v0[0] > v1[0])
        tv[0] = tv[0] < v1[0] ? v1[0] : MIN(tv[0], v0[0]);
    else
        tv[0] = tv[0] < v0[0] ? v0[0] : MIN(tv[0], v1[0]);

    if (v0[2] > v1[2])
        tv[2] = tv[2] < v1[2] ? v1[2] : MIN(tv[2], v0[2]);
    else
        tv[2] = tv[2] < v0[2] ? v0[2] : MIN(tv[2], v1[2]);

    volatile_vec_copy(v0, tv);
}



// @weird
static inline float q4_round_trip(void* out, void* x) {
    asm("lqc2 vf4, 0(%1); vftoi4 vf5, vf4; vitof4 vf4, vf5; sqc2 vf4, 0(%0)" : "=r"(out): "r"(x));
    return ((float*)x)[0];
}

static void clCheckBg2Chara(int no /* r18 */) {

    int whnum; // r29+0x5C
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wl; // r2
    CL_HITPOLY_PLANE* sw; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float tmp[4]; // r29+0x40
    float mang; // r29+0x60
    whnum = 0;
    clCharaList[clCharaListAct][no].wflg = 0;
    vec_zero(clCharaList[clCharaListAct][no].wallcv);
    clCheckHitDynamicWallCollision(&clCharaList[clCharaListAct][no].col, &whnum);
    smap = clGetHitSectListMOVE(clCharaList[clCharaListAct][no].col.p[0]);
    smapsv = smap;
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wl = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitWallCollision(&clCharaList[clCharaListAct][no].col, &whnum, wl, cl);
           
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wl = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 3]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 3]; // ???
            clCheckHitWallCollision(&clCharaList[clCharaListAct][no].col, &whnum, wl, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wl = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckColumn2ColumnHit(&clCharaList[clCharaListAct][no].col, &whnum, wl, cl);
        }
    }
    vu0_sub_vector(tmp, clCharaList[clCharaListAct][no].col.p[0], clCharaList[clCharaListAct][no].opos);
    vu0_add_vector(tmp, &clCharaList[clCharaListAct][no].sc->pos, tmp);
    vu0_sub_vector(tmp, tmp, &clCharaList[clCharaListAct][no].sc->b_pos);
    if ((tmp[0] == 0.0f) && (tmp[2] == 0.0f)) {
        mang = FLOAT_MAX;
    } else {
        mang = shAtan2(tmp[0], tmp[2]);
    }
    if (clMakeWallHitCollectVector(clCharaList[clCharaListAct][no].sc, clCharaList[clCharaListAct][no].wallcv, mang, &clCharaList[clCharaListAct][no].wflg, whnum) == 0) {
        vu0_add_vector(clCharaList[clCharaListAct][no].col.p[0], clCharaList[clCharaListAct][no].col.p[0], clCharaList[clCharaListAct][no].wallcv);
        vu0_sub_vector(clCharaList[clCharaListAct][no].wallcv, &clCharaList[clCharaListAct][no].sc->b_pos, clCharaList[clCharaListAct][no].col.p[0]);
    }
    q4_round_trip(clCharaList[clCharaListAct][no].wallcv, clCharaList[clCharaListAct][no].wallcv);
}


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

#line 1272
static int clMakeWallHitCollectVector(SubCharacter* sc /* r21 */, float* wcv /* r20 */, float mang /* r20 */, int* flg /* r19 */, int num /* r18 */) {
    int i, j; // r16, r17
    float ang0, ang1, newpos[4], dif; // r21, r29+0x90, r29+0x80, r29+0x90

    switch (num) {
        
        case 1:
            clAddWallCollectVector(wcv, clWallHitData->cv, flg);
        
            break;
        case 0:
            break;
        default:
            for (i = 0; i < num; i++) {
                
                if (clWallHitData[i].kind == 3) continue;

                
                clCalcPlaneEquation(clWallHitData[i].pl, clWallHitData[i].normal);
                vec_normalize(clWallHitData[i].normal, clWallHitData[i].normal);
                clWallHitData[i].nang = shAtan2(clWallHitData[i].normal[0], clWallHitData[i].normal[2]);
                
                if (mang != FLOAT_MAX) {
                
                    
                    
                    
                    if (clWallHitData[i].kind == 2) {
                    
                        
                        
                        for (j = 0; j < num; j++) {
                        
                            if (i == j) continue;
                            
                            
                            if (clWallHitData[j].kind != 1) continue;
                            
                            
                            vu0_add_vector(newpos, clWallHitData[j].cv, &sc->pos); 
                            vu0_sub_vector(newpos, newpos, &sc->b_pos); 
                            ang0 = shAtan2(newpos[0], newpos[2]);
                            ang0 = clWallHitData[i].nang - ang0;
                            ang0 = shAngleRegulate(ang0);
                            if ((ang0 < TO_RAD(89)) && ang0 > -TO_RAD(89)) {
                                
                                clWallHitData[i].kind = -1;
                                break;
                            }
                        }
                    }
                    
                    if (clWallHitData[i].kind != -1) {

                        ang0 = clWallHitData[i].nang - mang;
                        ang0 = shAngleRegulate(ang0);
                        if ((ang0 < TO_RAD(75)) && ang0 > -TO_RAD(75))
                            clWallHitData[i].kind = -1;
                    }
                }
            }



            
            for (i = 0; i < num; i++) {
            
                if (clWallHitData[i].kind != 2) continue;
                
                    
                for (j = 0; j < num; j++) {

                    if (i == j) continue;
                    
                    
                    if (clWallHitData[j].kind != 1) continue;
                    
                    
                    ang0 = clWallHitData[j].nang - clWallHitData[i].nang;
                    dif = shAngleRegulate(ang0);
                    if ((dif < TO_RAD(2)) && dif > -TO_RAD(2)) {
                        
                        
                        clWallHitData[i].kind = -1;
                        break;
                    }
                }
            }


            
            
            if (sc->status & 0x10000) {
            
                sc->colis_fall_timer = (double) shGetFPS(); // @note
            }
            
            if (sc->colis_fall_timer != 0) {
            
                for (i = 0; i < num; i++) {
                
                    
                    
                    if (clWallHitData[i].kind == -1) continue;

                        
                    ang0 = clWallHitData[i].nang - mang;
                    ang0 = shAngleRegulate(ang0);
                    if ((ang0 < QUARTER_TURN) && ang0 > -QUARTER_TURN) {
                        float len;
                        len = vec_length(&clWallHitData[i].cv);
                        len = (500.0f / shGetFPS()) / len;
                        if (len < 1.0f)
                            vu0_scale_vector(clWallHitData[i].cv, clWallHitData[i].cv, len);
                    }
                }
                sc->colis_fall_timer -= 1;
            }

            
            if ((sc->battle.status == 1) || (sc->battle.status == 2)) {
            
                
                for (i = 0; i < num - 1; i++) {
                
                    if (clWallHitData[i].kind != -1) {
                    
                        
                        for (j = i + 1; j < num; j++) {
                        
                            if (clWallHitData[j].kind == -1) continue;

                            
                            if (clWallHitData[i].cv[0] != 0.0f || clWallHitData[i].cv[2] != 0.0f) {


                                
                                if (clWallHitData[j].cv[0] != 0.0f || clWallHitData[j].cv[2] != 0.0f) {
                                
                                    
                                    
                                    ang0 = shAtan2(clWallHitData[i].cv[0], clWallHitData[i].cv[2]);
                                    ang1 = shAtan2(clWallHitData[j].cv[0], clWallHitData[j].cv[2]);
                                    ang0 = ang0 - ang1;
                                    ang0 = shAngleRegulate(ang0);
                                    if (ang0 > TO_RAD(120) || ang0 < -TO_RAD(120)) {
                                        clWallHitData[i].kind = -2;
                                        clWallHitData[j].kind = -2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (i = 0; i < num; i++) {
                if (clWallHitData[i].kind >= 0) {
                    clAddWallCollectVector(wcv, clWallHitData[i].cv, flg);
                }
            }
            break;
    }
    return 1;
}


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

// yuck
static void clCheckColumn2WallHit(CL_HITRESULT* cres /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, CL_HITPOLY_COLUMN* col /* r16 */) {
    CL_HITRESULT tmp; // r29+0x40
    sceVu0FVECTOR normal; // r29+0x80
    sceVu0FVECTOR pos; // r29+0x90
    int hitchk; // r2
    sceVu0FVECTOR vec; // r29+0xA0
    float iv0; // r29+0xD0
    float iv1; // r29+0xD0
    sceVu0FVECTOR vp[2]; // r29+0xB0
    float temp_f1, temp_f2;
    cres->chk = 0;
    vu0_sub_vector(col->p[0], pl->p[2], col->p[0]);
    clCalcPlaneEquation(pl, &normal[0]);
    if (!(vec3_dot_product(normal, normal) < 0.0f) && (clCheckSubWallToColumn(&tmp, pl->p[0], pl->p[2], col->p[0]) == 1)) {
        volatile_vec_copy(vp[0], pl->p[0]);
        volatile_vec_copy(vp[1], pl->p[3]);
        vu0_sub_vector(col->p[0], pl->p[2], col->p[0]);
        vec[1] = 0.0f;
        pos[1] = 0.0f;
        temp_f1 = vec3_dot_product(normal, normal);
        vu0_sub_vector(col->p[0], pl->p[2], col->p[0]);
        vu0_sub_vector(col->p[0], pl->p[2], col->p[0]);
        vec[1] = 0.0f;
        pos[1] = 0.0f;
        temp_f2 = vec3_dot_product(normal, normal);
        if (((temp_f1 < 0.0f) && !(temp_f2 < 0.0f)) || (!(temp_f1 < 0.0f) && (temp_f2 < 0.0f))) {
            asm("lqc2 vf1, 0(%0)\n\
                 lqc2 vf2, 0(%1)\n\
                 \
                 vsub.xz vf3, vf1, vf2\n\
                 vmul.xz vf3, vf3, vf3\n\
                 vaddz.x vf3, vf3, vf3z\n\
                 \
                 qmfc2 t0, vf3\n\
                 mtc1 t0, f12\n\
                 sw t0, 0(%2)":: "r"(vp[0]), "r"(tmp.cv), "r"(temp_f1) : "t0");
            asm("lqc2 vf1, 0(%0)\n\
                 lqc2 vf2, 0(%1)\n\
                 \
                 vsub.xz vf3, vf1, vf2\n\
                 vmul.xz vf3, vf3, vf3\n\
                 vaddz.x vf3, vf3, vf3z\n\
                 \
                 qmfc2 t0, vf3\n\
                 mtc1 t0, f12\n\
                 sw t0, 0(%2)":: "r"(vp[0]), "r"(tmp.cv), "r"(temp_f1) : "t0");
            if (!(temp_f1 < temp_f1)) {
                // M2C_ERROR(/* unknown instruction: vadd.xz vf5, vf0, vf7 */);
            }
            asm("\
                lqc2 vf6, 0x10(v1)\n\
                vaddw.w vf6, vf0, vf6w\n\
                vaddw.x vf6, vf0, vf6w\n\
                vwaitq\n\
                vsubq.x vf6, vf6, Q\n\
                vaddq.x vf4, vf0, Q\n\
                 vdiv Q, vf6x, vf4x\n\
                 vmove.yw vf5, vf0\n\
                vwaitq\n\
                vmulq.xz vf5, vf5, Q\n\
                 vnop\n\
                 sqc2 vf5, 0(a1)");
            cres->chk = 2;
        } else {
            cres->chk = 1;
        }
        cres->pd = (CL_HITPOLY_HEAD* ) pl;
        volatile_vec_copy(cres->cv, tmp.cv);
    }
}


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

CL_BATTLE_RESULT* clBattleGetResult(u_int id, CL_BATTLE_RESULT* before) {
    int i;

    if (before == 0) {
        i = 0;
    } else {
        i = 1 - before->enable;
    }

    for (; i < clUseBattleResult; i++) {
        if (id == clBattleResult[i].id) {
            if (clBattleResult[i].enable > 0) {
                clBattleResult[i].enable = -i;
                return &clBattleResult[i];
            }
        }
    }

    return &clBattleResult[CL_BATTLE_RESULT_SIZE - 1];
}

void clBattleCheckExec(void) {
    int i; // r16
    CL_VHIT_RESULT vres; // r29+0x20
    sceVu0FVECTOR dirc; // r29+0x60

    clUseBattleResult = 0;

    for (i = 0; i < clUseBattleQue; i++) {

        switch (clBattleQue[i].kind) {
            case 2:
                clCheckHitSwordWeapon(&vres, (u_int) clBattleQue[i].sc, clBattleQue[i].svs, clBattleQue[i].sve, clBattleQue[i].evs, clBattleQue[i].eve);
                if (vres.kind != 0) {
                    vu0_sub_vector(dirc, clBattleQue[i].eve, clBattleQue[i].sve);
                    clSetOneBattleResult(&clBattleQue[i], &vres, dirc);
                }
                break;

            case 3:
            case 4:
                clCheckHitGunWeapon(&vres, (u_int) clBattleQue[i].sc, clBattleQue[i].svs, clBattleQue[i].sve);
                if (vres.kind != 0) {
                    vu0_sub_vector(dirc, clBattleQue[i].sve, clBattleQue[i].svs);
                    clSetOneBattleResult(&clBattleQue[i], &vres, dirc);
                }
                break;

            case 5:
            case 6:
                clCheckHitGunWeapon(&vres, (u_int) clBattleQue[i].sc, clBattleQue[i].svs, clBattleQue[i].sve);
                if (((vres.kind != 3) || ((vres.hobj.chara.sc->kind == LLL_JMS_CHARA_KIND)) || (vres.hobj.chara.sc->kind == HLL_JMS_CHARA_KIND)) && (vres.kind != 0)) {

                    vu0_sub_vector(dirc, clBattleQue[i].sve, clBattleQue[i].svs);
                    clSetOneBattleResult(&clBattleQue[i], &vres, dirc);
                }
                break;

            case 1:
                clCheckHitSwordWeaponThrust((u_int) clBattleQue[i].sc, clBattleQue[i].svs, clBattleQue[i].sve, clBattleQue[i].evs, clBattleQue[i].eve);

                    vu0_sub_vector(dirc, clBattleQue[i].eve, clBattleQue[i].sve);
                clSetThrustBattleResult(&clBattleQue[i], dirc);
                break;

            case 7:
                clCheckHitGunWeaponThrust((u_int) clBattleQue[i].sc, clBattleQue[i].svs, clBattleQue[i].sve);

                    vu0_sub_vector(dirc, clBattleQue[i].sve, clBattleQue[i].svs);
                clSetThrustBattleResult(&clBattleQue[i], dirc);
                break;

            default:
                ASSERT(0);
        }
    }
    
    clModifiedBattleData();
}


#line 1892
void clModifiedBattleData(void) {
    int i; // r3
    int j; // r4
    int k; // r5

    for (i = 0; i < clUseBattleResult; i++) {
        
        if (clBattleResult[i].enable <= 0) continue;
    
        
        
        if ((clBattleResult[i].kind == 6) && (clBattleResult[i].atr == 1)) {
            
            
            for (j = 0; j < clUseBattleResult; j++) {

                if (clBattleResult[j].enable <= 0) continue;
                
                if (i == j) continue;


                if (clBattleResult[j].atr == 4 && clBattleResult[i].id == clBattleResult[j].id) {

                    
                    clBattleResult[i].enable = -1;
                    break;
                }
            }
            
            if (clBattleResult[i].enable == -1) {
            
                for (j = 0; j < clUseBattleResult; j++) {
                
                    if (clBattleResult[j].enable <= 0) continue;
                    
                    if (i == j) continue;
    
    
                    if (clBattleResult[j].atr == 4 && clBattleResult[i].id == (u_int) clBattleResult[j].obj.en)
    
                        
                        clBattleResult[j].enable = -1;
                }
            }
        }

        
        if ((clBattleResult[i].atr == 4) && (clBattleResult[i].kind == 6) && (clBattleResult[i].enable > 0)) {

        
            
            for (j = 0; j < clUseBattleResult; j++) {
            
                if (clBattleResult[j].enable <= 0) continue;
                
                if (i == j) continue;


                if (clBattleResult[j].atr == 4 && clBattleResult[i].id == clBattleResult[j].id) {


                    
                    clBattleResult[i].enable = -1;
                    
                    for (k = 0; k < clUseBattleResult; k++) {
                        
                        if (clBattleResult[k].enable <= 0) continue;
                
                        if (i == k) continue;

                        
                        if ((clBattleResult[k].kind == 6) && (clBattleResult[k].atr == 1) && ((u_int) clBattleResult[k].obj.en == clBattleResult[i].id))
                        
                            
                            clBattleResult[k].enable = -1;
                    }

                }
            }
        }
    }
}


#line 1993
static void clSetOneBattleResult(CL_BATTLE_QUE* que /* r2 */, CL_VHIT_RESULT* vres /* r2 */, float* vec /* r2 */) {
    ASSERT(clUseBattleResult < 64);

    switch (vres->kind) {

        
        case 1:
            clBattleResult[clUseBattleResult].enable = 1;
            clBattleResult[clUseBattleResult].id = (u_int) que->sc;
            clBattleResult[clUseBattleResult].atr = 2;
            clBattleResult[clUseBattleResult].kind = que->kind;
            clBattleResult[clUseBattleResult].btlid = que->btlid;
            volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (vres->hobj).wall.cp);
            clBattleResult[clUseBattleResult].obj.en = (vres->hobj).wall.pd;
            clUseBattleResult++;
            break;

        
        case 2:
            clBattleResult[clUseBattleResult].enable = 1;
            clBattleResult[clUseBattleResult].id = (u_int) que->sc;
            clBattleResult[clUseBattleResult].atr = 3;
            clBattleResult[clUseBattleResult].kind = que->kind;
            clBattleResult[clUseBattleResult].btlid = que->btlid;
            volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (vres->hobj).wall.cp);
            clBattleResult[clUseBattleResult].obj.en = (vres->hobj).wall.pd;
            clUseBattleResult++;
            break;

        
        case 3:
            clBattleResult[clUseBattleResult].enable = 1;
            clBattleResult[clUseBattleResult].id = (u_int) que->sc;
            clBattleResult[clUseBattleResult].atr = 1;        
            volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (vres->hobj).wall.nl);
            clBattleResult[clUseBattleResult].kind = que->kind;
            clBattleResult[clUseBattleResult].btlid = que->btlid;
            clBattleResult[clUseBattleResult].obj.en = (vres->hobj).chara.sc;
            clUseBattleResult++;
            
            clBattleResult[clUseBattleResult].enable = 1;
            clBattleResult[clUseBattleResult].id = (u_int) (vres->hobj).chara.sc;
            clBattleResult[clUseBattleResult].atr = 4;
            volatile_vec_copy(&clBattleResult[clUseBattleResult].pos, (vres->hobj).wall.nl);
            volatile_vec_copy(&clBattleResult[clUseBattleResult].vec, vec);
            clBattleResult[clUseBattleResult].kind = que->kind;
            clBattleResult[clUseBattleResult].btlid = que->btlid;
            clBattleResult[clUseBattleResult].obj.en = que->sc;
            clUseBattleResult++;
            break;
    }
}

void clSetThrustBattleResult(CL_BATTLE_QUE* que, float* vec) {
    int i; // r7
    int j; // r9

    for (i = 0; i < clVHitListUse; i++) {
        switch (clVHitResult[i].kind) {

        
            case 1:
                clBattleResult[clUseBattleResult].enable = 1;
                clBattleResult[clUseBattleResult].id = (u_int) que->sc;
                clBattleResult[clUseBattleResult].atr = 2;
                clBattleResult[clUseBattleResult].kind = que->kind;
                clBattleResult[clUseBattleResult].btlid = que->btlid;
                volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (clVHitResult[i].hobj).wall.cp);
                clBattleResult[clUseBattleResult].obj.en = (clVHitResult[i].hobj).wall.pd;
                clUseBattleResult++;
                break;
    
            
            case 2:
                clBattleResult[clUseBattleResult].enable = 1;
                clBattleResult[clUseBattleResult].id = (u_int) que->sc;
                clBattleResult[clUseBattleResult].atr = 3;
                clBattleResult[clUseBattleResult].kind = que->kind;
                clBattleResult[clUseBattleResult].btlid = que->btlid;
                volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (clVHitResult[i].hobj).wall.cp);
                clBattleResult[clUseBattleResult].obj.en = (clVHitResult[i].hobj).wall.pd;
                clUseBattleResult++;
                break;
    
            
            case 3:
                for (j = 0; j < i; j++) {
                    if (clVHitResult[i].hobj.chara.sc == clVHitResult[j].hobj.chara.sc) {
                        j = -1;
                        break;
                    }
                }
                if (j != -1) {
                    clBattleResult[clUseBattleResult].enable = 1;
                    clBattleResult[clUseBattleResult].id = (u_int) que->sc;
                    clBattleResult[clUseBattleResult].atr = 1;        
                    volatile_vec_copy(clBattleResult[clUseBattleResult].pos, (clVHitResult[i].hobj).wall.nl);
                    clBattleResult[clUseBattleResult].obj.en = clVHitResult[i].hobj.chara.sc;
                    clBattleResult[clUseBattleResult].kind = que->kind;
                    clBattleResult[clUseBattleResult].btlid = que->btlid;
                    clUseBattleResult++;
                    
                    clBattleResult[clUseBattleResult].enable = 1;
                    clBattleResult[clUseBattleResult].id = (u_int) (clVHitResult[i].hobj).chara.sc;
                    clBattleResult[clUseBattleResult].atr = 4;
                    volatile_vec_copy(&clBattleResult[clUseBattleResult].pos, (clVHitResult[i].hobj).wall.nl);
                    volatile_vec_copy(&clBattleResult[clUseBattleResult].vec, vec);
                    clBattleResult[clUseBattleResult].kind = que->kind;
                    clBattleResult[clUseBattleResult].btlid = que->btlid;
                    clBattleResult[clUseBattleResult].obj.en = que->sc;
                    clUseBattleResult++;
                }
                break;
        }
    }
}

static void clCheckHitSwordWeapon(CL_VHIT_RESULT* res /* r22 */, u_int id /* r21 */, float* svs /* r20 */, float* sve /* r19 */, float* evs /* r18 */, float* eve /* r17 */) {
    int i; // r16
    sceVu0FVECTOR st; // r29+0x80
    sceVu0FVECTOR ed; // r29+0x90
    sceVu0FVECTOR tmp; // r29+0xA0

    for (i = 0; i < 5; i++) {
        vu0_scale_vector(st, svs, clswPerc[i]);
        vu0_scale_vector(tmp, evs, clswPerc[4 - i]);
        vu0_add_vector(st, st, tmp);
        vu0_scale_vector(ed, sve, clswPerc[i]);
        vu0_scale_vector(tmp, eve, clswPerc[4 - i]);
        vu0_add_vector(ed, ed, tmp);
        
        clCheckHitSwordVector(res, id, st, ed);

        if (res->kind) {
            break;
        }
    }
}

static void clCheckHitGunWeapon(CL_VHIT_RESULT* res /* r2 */, u_int id /* r2 */, float* st /* r2 */, float* ed /* r2 */) {
    clCheckHitEyeVector(res, id, st, ed);
}

static void clCheckHitSwordVector(CL_VHIT_RESULT* res /* r21 */, u_int id /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x7C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
    res->kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitSwordVectorDynamicWall(res, sp, ep, &min);
    clCheckHitSwordVectorDynamicFloor(res, sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(res, sp, ep, &min, wall, cl);
        }
    }
    clCheckHitEyeVectorCharacter(res, sp, ep, &min, id);
}

static inline vec_dist_squared(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float* ptr) {
    asm("lqc2 vf1, 0(%0)\n\
        lqc2 vf2, 0(%1)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%2)":: "r"(v0), "r"(v1), "r"(ptr): "t0");
}

#line 2360
static void clCheckHitSwordVectorWall(CL_VHIT_RESULT* res /* r21 */, float* sp /* r20 */, float* ep /* r19 */, float* min /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, int* ptr /* r16 */) {
    int ret; // r2
    CL_HITRESULT cres; // r29+0x70
    float dist; // r29+0xBC

    for (; *ptr != -1; ptr = ptr + 1) {
        
        if (pl[*ptr].material == MATERIAL_TYPE_12) continue;

        
        if (pl[*ptr].shape == 0)
            ret = clCheckSubLineToPlane3(&cres,
                                         sp, ep, 
                                         pl[*ptr].p, pl[*ptr].p + 1, pl[*ptr].p + 2);
        else
            ret =clCheckSubLineToPlane(&cres,
                                       sp, ep,
                                       &pl[*ptr].p[0], &pl[*ptr].p[1],&pl[*ptr].p[2],&pl[*ptr].p[3]);

        
        if (ret != 0) {
            // @note: not an inline in other functions??
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist < *min) {
            
                
                *min = dist;
                res->kind = 1;
                volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                clCalcPlaneEquation(pl + *ptr,(res->hobj).wall.nl);
                (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(pl + *ptr);
            }
        }
    }
}

static void clCheckHitNoThruVectorWall(CL_VHIT_RESULT* res /* r21 */, float* sp /* r20 */, float* ep /* r19 */, float* min /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, int* ptr /* r16 */) {
    int ret; // r2
    CL_HITRESULT cres; // r29+0x70
    float dist; // r29+0xBC
    for (; *ptr != -1; ptr = ptr + 1) {
        if (pl[*ptr].shape == 0)
            ret = clCheckSubLineToPlane3(&cres,
                                         sp, ep, 
                                         pl[*ptr].p, pl[*ptr].p + 1, pl[*ptr].p + 2);
        else
            ret =clCheckSubLineToPlane(&cres,
                                       sp, ep,
                                       &pl[*ptr].p[0], &pl[*ptr].p[1],&pl[*ptr].p[2],&pl[*ptr].p[3]);

        
        if (ret != 0) {
            // @note: not an inline in other functions??
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist < *min) {
            
                
                *min = dist;
                res->kind = 1;
                volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                clCalcPlaneEquation(pl + *ptr,(res->hobj).wall.nl);
                (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(pl + *ptr);
            }
        }
    }
}

static void clCheckHitSwordVectorDynamicWall(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicWallListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicWallList[ac].use; i++) {
        for (j = 0; clDynamicWallList[ac].dw[i][j].kind != 0; j++) {
        
            if (clDynamicWallList[ac].dw[i][j].material == MATERIAL_TYPE_12) continue;
    
            
            if (clDynamicWallList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicWallList[ac].dw[i][j].p, clDynamicWallList[ac].dw[i][j].p + 1, clDynamicWallList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicWallList[ac].dw[i][j].p[0], &clDynamicWallList[ac].dw[i][j].p[1],&clDynamicWallList[ac].dw[i][j].p[2],&clDynamicWallList[ac].dw[i][j].p[3]);
    
            
            if (ret != 0) {
                // @note: not an inline in other functions??
                vec_dist_squared(sp, cres.cp, &dist);
                if (dist < *min) {
                
                    
                    *min = dist;
                    res->kind = 1;
                    volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                    clCalcPlaneEquation(&clDynamicWallList[ac].dw[i][j], (res->hobj).wall.nl);
                    (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicWallList[ac].dw[i][j]);
                }
            }
        }
    }
}

static void clCheckHitSwordVectorDynamicWallNoThru(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicWallListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicWallList[ac].use; i++) {
        for (j = 0; clDynamicWallList[ac].dw[i][j].kind != 0; j++) {        
            if (clDynamicWallList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicWallList[ac].dw[i][j].p, clDynamicWallList[ac].dw[i][j].p + 1, clDynamicWallList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicWallList[ac].dw[i][j].p[0], &clDynamicWallList[ac].dw[i][j].p[1],&clDynamicWallList[ac].dw[i][j].p[2],&clDynamicWallList[ac].dw[i][j].p[3]);
    
            
            if (ret != 0) {
                // @note: not an inline in other functions??
                vec_dist_squared(sp, cres.cp, &dist);
                if (dist < *min) {
                
                    
                    *min = dist;
                    res->kind = 1;
                    volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                    clCalcPlaneEquation(&clDynamicWallList[ac].dw[i][j], (res->hobj).wall.nl);
                    (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicWallList[ac].dw[i][j]);
                }
            }
        }
    }
}

static void clCheckHitSwordVectorDynamicFloor(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicFloorListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicFloorList[ac].use; i++) {
        for (j = 0; clDynamicFloorList[ac].dw[i][j].kind != 0; j++) {
        
            if (clDynamicFloorList[ac].dw[i][j].material == MATERIAL_TYPE_12) continue;
    
            
            if (clDynamicFloorList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicFloorList[ac].dw[i][j].p, clDynamicFloorList[ac].dw[i][j].p + 1, clDynamicFloorList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicFloorList[ac].dw[i][j].p[0], &clDynamicFloorList[ac].dw[i][j].p[1],&clDynamicFloorList[ac].dw[i][j].p[2],&clDynamicFloorList[ac].dw[i][j].p[3]);
    
            
            if (ret != 0) {
                // @note: not an inline in other functions??
                vec_dist_squared(sp, cres.cp, &dist);
                if (dist < *min) {
                
                    
                    *min = dist;
                    res->kind = 1;
                    volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                    clCalcPlaneEquation(&clDynamicFloorList[ac].dw[i][j], (res->hobj).wall.nl);
                    (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicFloorList[ac].dw[i][j]);
                }
            }
        }
    }
}

static void clCheckHitSwordVectorDynamicFloorNoThru(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicFloorListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicFloorList[ac].use; i++) {
        for (j = 0; clDynamicFloorList[ac].dw[i][j].kind != 0; j++) {

            if (clDynamicFloorList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicFloorList[ac].dw[i][j].p, clDynamicFloorList[ac].dw[i][j].p + 1, clDynamicFloorList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicFloorList[ac].dw[i][j].p[0], &clDynamicFloorList[ac].dw[i][j].p[1],&clDynamicFloorList[ac].dw[i][j].p[2],&clDynamicFloorList[ac].dw[i][j].p[3]);
    
            
            if (ret != 0) {
                // @note: not an inline in other functions??
                vec_dist_squared(sp, cres.cp, &dist);
                if (dist < *min) {
                
                    
                    *min = dist;
                    res->kind = 1;
                    volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                    clCalcPlaneEquation(&clDynamicFloorList[ac].dw[i][j], (res->hobj).wall.nl);
                    (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicFloorList[ac].dw[i][j]);
                }
            }
        }
    }
}

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


#line 2777
static int clCheckHitThrustSwordVector(u_int id /* r21 */, float* sp /* r20 */, float* ep /* r19 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x7C
    int whflg = 0; // r18

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
    clVHitResult[clVHitListUse].kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitSwordVectorDynamicWall(&clVHitResult[clVHitListUse], sp, ep, &min);
    clCheckHitSwordVectorDynamicFloor(&clVHitResult[clVHitListUse], sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitSwordVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitSwordVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitSwordVectorWall(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(&clVHitResult[clVHitListUse], sp, ep, &min, wall, cl);
        }
    }
    if (clVHitResult[clVHitListUse].kind != 0) {
        clVHitListUse++;
        whflg = 1;
    }
    clCheckHitThrustGunVectorCharacter(sp, ep, min, id);
    return whflg;
}

void clCheckHitGunWeaponThrust(u_int id, float* st, float* ed) {
    clVHitListUse = 0;
    clCheckHitThrustGunVector(id, st, ed);
}

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
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
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

static void clCheckHitThrustGunVectorCharacter(float* sp /* r20 */, float* ep /* r19 */, float min /* r20 */, u_int id /* r18 */) {
    int i; // r16
    int ret; // r2
    CL_HITRESULT cres; // r29+0x70
    float dist; // r29+0xBC

    
    int ac = clCharaListAct ? 0 : 1; // r2

    for (i = 0; i < clCharaListUse[ac]; i++) {
        
        if (id == (u_int) clCharaList[ac][i].sc) continue;

        
        if (clCharaList[ac][i].batflg != 0) {
        
            
            ret = clCheckSubLineToColumnPlus(&cres, sp, ep, &clCharaList[ac][i].wcol.p[0]);
            
            
            if (!ret) continue;
            
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist < min) {
            
                
                clVHitResult[clVHitListUse].kind = 3;
                volatile_vec_copy((clVHitResult[clVHitListUse].hobj).wall.nl, cres.cp);
                (clVHitResult[clVHitListUse].hobj).chara.sc = clCharaList[ac][i].sc;
                clVHitListUse++;
            }
        }
    }
}

CL_SELECT_MAP* clGetHitSectListVECHIT(float* st /* r17 */, float* ed /* r16 */) {
    if (BgIsOut(0)) {
        return clGetHitSectListVECHITOutDoor(st, ed);
    }
    return clGetHitSectListVECHITInDoor(st, ed);
}


static CL_SELECT_MAP* clGetHitSectListVECHITOutDoor(float* st /* r22 */, float* ed /* r21 */) {
    int j, k; // r16. r17
    int use = 0; // r18
    CL_CLDHEADER* ch; // r19
    float box[4][4]; // r29+0xC0
    void** list; // r29+0xB0

    if (clCollisionEnable != 0) {

        
        
        list = loadBgCLD_GetLoadedDataAddrList();
        for (; (ch = *list) != NULL; list++) {
            float sx, sz; // @note not in dwarf, but confirmed by line numbers and needed for match.



            
            if (ch->disable) continue;

            
            
            
            
            

            sx = ch->sx;
            sz = ch->sz;
            
            box[0][0] = sx;
            box[0][2] = sz;
            box[1][0] = sx;
            box[1][2] = 20000.0f + sz;
            box[2][0] = 20000.0f + sx;
            box[2][2] = 20000.0f + sz;
            box[3][0] = 20000.0f + sx;
            box[3][2] = sz;
            
            
            
            if (Line2PlaneBoundaryCheckXZ(st, ed, &box[0], &box[1], &box[2], &box[3])) continue;
            
            
            
            if (clCheckCrossLine2BoxXZ(&box[0], st, ed)) {
            
                for (j = 0; j < 4; j++) {
                
                    for (k = 0; k < 4; k++) {
                    
                        box[0][0] = sx + (5000.0f * (f32) k);
                        box[0][2] = sz + (5000.0f * (f32) j);
                        box[1][0] = box[0][0];
                        box[1][2] = 5000.0f + box[0][2];
                        box[2][0] = 5000.0f + box[0][0];
                        box[2][2] = 5000.0f + box[0][2];
                        box[3][0] = 5000.0f + box[0][0];
                        box[3][2] = box[0][2];
                        if ((Line2PlaneBoundaryCheckXZ(st, ed, &box[0], &box[1],  &box[2], &box[3]) == 0) && (clCheckCrossLine2BoxXZ(&box[0], st, ed) != 0)) {
                            clSelectMap[use].base = (u_char* ) ch;
                            clSelectMap[use].sect = k + (j * 4);
                            use++;
                        }
                    }
                }
            }
        }
    }
    clSelectMap[use].base = NULL;
    return clSelectMap;
}


static CL_SELECT_MAP* clGetHitSectListVECHITInDoor(float* st, float* ed) {
    int use; // r16
    CL_CLDHEADER* ch; // r4
    void** list; // r2

    void* temp_a0;
    void** var_v0;

    use = 0;
    if (clCollisionEnable != 0) {
        list = loadBgCLD_GetLoadedDataAddrList();

        for (; (ch = *list) != NULL; list++) {
            if (ch->disable) continue;
            clSelectMap[use].base = (u_char*) ch;
            clSelectMap[use].sect = 0;
            use++;
        }
    }
    clSelectMap[use].base = NULL;
    return clSelectMap;
}


static int Line2PlaneBoundaryCheckXZ(float (* l0)[4] /* r2 */, float (* l1)[4] /* r2 */, float (* p0)[4] /* r2 */, float (* p1)[4] /* r2 */, float (* p2)[4] /* r2 */, float (* p3)[4] /* r2 */) {
    int ret = 0; // r2

    asm("\
        lqc2     vf1,  0(%1)      ;\
        lqc2     vf2,  0(%2)      ;\
        lqc2     vf3,  0(%3)      ;\
        lqc2     vf4,  0(%4)      ;\
        lqc2     vf5,  0(%5)      ;\
        lqc2     vf6,  0(%6)      ;\
        vmax.xz  vf7,  vf3,  vf4  ;\
        vmax.xz  vf8,  vf5,  vf6  ;\
        vmini.xz vf9,  vf3,  vf4  ;\
        vmini.xz vf10, vf5,  vf6  ;\
        vmax.xz  vf7,  vf7,  vf8  ;\
        vmini.xz vf8,  vf1,  vf2  ;\
        vmini.xz vf9,  vf9,  vf10 ;\
        vmax.xz  vf10, vf1,  vf2  ;\
        vnop                      ;\
        ctc2     zero, vi16       ;\
        vsub.xz  vf7,  vf7,  vf8  ;\
        vsub.xz  vf8,  vf10, vf9  ;\
        vnop                      ;\
        vnop                      ;\
        vnop                      ;\
        vnop                      ;\
        vnop                      ;\
        cfc2     %0,   vi16"
        : "+r"(ret) : "r"(l0), "r"(l1), "r"(p0), "r"(p1), "r"(p2), "r"(p3) : );

    return ret & 0x80;
}

#line 3393
int clCheckCrossLine2BoxXZ(float (* box)[4] /* r19 */, float* st /* r18 */, float* ed /* r17 */) {
    int i; // r16
    sceVu0FVECTOR va, vb; // r29+0x50, r29+0x60
    float outer; // r1
    int jyun[5] = {0, 1, 2, 3, 0}; // r29+0x70

    // check if first endpoint is inside the box.
    for (i = 0; i < 4; i++) {
        // test direction of rotation. va = box wall, vb = line from box corner to first endpoint.
        vu0_sub_vector(va, box[jyun[i + 1]], box[jyun[i]]);
        vu0_sub_vector(vb, st, box[i]);
        outer = va[0] * vb[2] - va[2] * vb[0]; /* determinant */
        if (outer > 0.0f)
            break; // box is winding clockwise, but we have to wind counterclockwise.
    }
    if (i == 4)
        return 1;

    // check if second endpoint is inside the box.
    for (i = 0; i < 4; i++) {
        // test direction of rotation. va = box wall, vb = line from box corner to second endpoint.
        vu0_sub_vector(va, box[jyun[i + 1]], box[jyun[i]]);
        vu0_sub_vector(vb, ed, box[i]);
        outer = va[0] * vb[2] - va[2] * vb[0]; /* determinant */
        if (outer > 0.0f)
            break;
    }
    if (i == 4)
        return 1;

    // neither endpoint is inside the box, so check if line intersects any wall.
    for (i = 0; i < 4; i++) {
        // check if wall intersects line segment
        if (clCheckCrossLine2LineXZ(st, ed, box[jyun[i]], box[jyun[i + 1]]))
            return 1;
    }

    return 0;
}

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

CL_SELECT_MAP* clGetHitSectListMOVE(f32* bpos) {
    if (BgIsOut(0)) {
        return clGetHitSectListMOVEOutDoor(bpos);
    }
    return clGetHitSectListMOVEInDoor(bpos);
}

#line 3516
CL_SELECT_MAP* clGetHitSectListMOVEOutDoor(float* bpos) {
    int j, k; // r7, r9
    int use = 0; // r16
    CL_CLDHEADER* ch; // r3
    sceVu0FVECTOR pos, cpos, bcpos; // r29+0x30, r29+0x40, r29+0x50
    float dist; // r29+0x6C
    void** list; // r2
    volatile_vec_copy(pos, bpos);
    pos[1] = 0.0f;
    pos[3] = 1.0f;
    vec_zero(cpos);
    
    if (clCollisionEnable != 0) {
        int* ptr;

        
        list = loadBgCLD_GetLoadedDataAddrList();
        for (; (ch = *list) != NULL; list++) {
            float* x;
            
            
            
            
            if (ch->disable) continue;
            
            
            
            
            
            
            
            cpos[0] = ch->sx;
            cpos[2] = ch->sz;
            volatile_vec_copy(bcpos, cpos); 
            // @note: different from the rest! has no `y` computations. not an inline based on the line numbers.
            ptr = &dist;
            asm("lqc2 vf1, 0(%0)\n\
                 lqc2 vf2, 0(%1)\n\
                 \
                 vsub.xz vf3, vf1, vf2\n\
                 vmul.xz vf3, vf3, vf3\n\
                 vaddz.x vf3, vf3, vf3z\n\
                 \
                 qmfc2 t0, vf3\n\
                 mtc1 t0, f12\n\
                 sw t0, 0(%2)":: "r"(bpos), "r"(bcpos), "r"(ptr) : "t0");
           
            
            
            
            if (dist > 9e8f) continue;

            
            for (j = 0; j < 4; j++) {
            
                for (k = 0; k < 4; k++) {
                
                    cpos[2] += 5000.0f * j;
                    cpos[0] += 5000.0f * k;
                    asm("\
                        lqc2 vf1, 0(%0)\n\
                        lqc2 vf2, 0(%1)\n\
                        \
                        vsub.xz vf3, vf1, vf2\n\
                        vmul.xz vf3, vf3, vf3\n\
                        vaddz.x vf3, vf3, vf3z\n\
                        \
                        qmfc2 t0, vf3\n\
                        mtc1 t0, f12\n\
                        sw t0, 0(%2)":: "r"(pos), "r"(cpos), "r"(&dist) : "t0");
                    
                    
                    
                    
                    if (dist < 6.4e7f) {
                    
                        
                        
                        clSelectMap[use].base = (u_char* ) ch;
                        clSelectMap[use].sect = k + (j * 4);
                        
                        use++;
                    }
                    
                    volatile_vec_copy(cpos, bcpos); 
                }
            }
        }
    }

    clSelectMap[use].base = NULL;
    
    return clSelectMap;
}


static CL_SELECT_MAP* clGetHitSectListMOVEInDoor(float* bpos /* @note unused */) {
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

void clCheckHitEyesOnlyFloor(CL_VHIT_RESULT* res, int unknown, float* sp, float* ep) {   CL_SELECT_MAP* smap; // r2
    CL_SELECT_MAP* smapsv; // r16
    CL_HITPOLY_PLANE* wall; // r2
    int* ptr; // r2
    float min; // r29+0x5C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)":: "r"(&min), "r"(sp), "r"(ep): "t0");

    

    res->kind = 0;
    
    
    clCheckHitEyeVectorDynamicFloor(res, sp, ep, &min);

    
    smapsv = clGetHitSectListVECHIT(sp, ep);


    
    if (smapsv->base != NULL) {

        
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((CL_CLDHEADER* ) smap->base)->fldofs;
            ptr = smap->base + ((int*)smap->base)[smap->sect + 8];
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, ptr);
        }
    }
}


void clCheckHitEyesOnlyFloorThru(CL_VHIT_RESULT* res /* r19 */, int unknown, float* sp /* r18 */, float* ep /* r17 */) {
    CL_SELECT_MAP* smap; // r2
    CL_SELECT_MAP* smapsv; // r16
    CL_HITPOLY_PLANE* wall; // r2
    int* ptr; // r2
    float min; // r29+0x5C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)":: "r"(&min), "r"(sp), "r"(ep): "t0");

    

    res->kind = 0;
    
    
    clCheckHitEyeVectorDynamicFloor(res, sp, ep, &min);

    
    smapsv = clGetHitSectListVECHIT(sp, ep);


    
    if (smapsv->base != NULL) {

        
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((CL_CLDHEADER* ) smap->base)->fldofs;
            ptr = smap->base + ((int*)smap->base)[smap->sect + 8];
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, ptr);
        }
    }
}

void clCheckHitEyesOnlyWall(CL_VHIT_RESULT* res /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
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
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep));
    res->kind = 0;
    clCheckHitSwordVectorDynamicWall(res, sp, ep, &min);
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(res, sp, ep, &min, wall, cl);
        }
    }
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x001392C0 -> 0x00139414
*/
// Range: 0x1392C0 -> 0x139414
void clCheckHitEyesOnlyFloorCeil(CL_VHIT_RESULT* res /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    int* ptr; // r2
    float min; // r29+0x6C
CL_HITPOLY_COLUMN* cl; 
    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep));
    
    res->kind = 0;
    clCheckHitEyeVectorDynamicFloor(res, sp, ep, &min);
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
    }
}
static void clCheckHitEyeVector(CL_VHIT_RESULT* res /* r21 */, u_int id /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x7C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
    res->kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitEyeVectorDynamicWall(res, sp, ep, &min);
    clCheckHitEyeVectorDynamicFloor(res, sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitEyeVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(res, sp, ep, &min, wall, cl);
        }
    }
    clCheckHitEyeVectorCharacter(res, sp, ep, &min, id);
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x00139680 -> 0x001398D4
*/
// Range: 0x139680 -> 0x1398D4
static void clCheckHitEyeVectorNoThru(CL_VHIT_RESULT* res /* r21 */, u_int id /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x7C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
    res->kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitSwordVectorDynamicWall(res, sp, ep, &min);
    clCheckHitSwordVectorDynamicFloor(res, sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitSwordVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(res, sp, ep, &min, wall, cl);
        }
    }
    clCheckHitEyeVectorCharacter(res, sp, ep, &min, id);
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x001398E0 -> 0x00139B8C
*/
// Range: 0x1398E0 -> 0x139B8C
static void clCheckHitEyeVectorAllNoThru(CL_VHIT_RESULT* res /* r21 */, u_int id /* r20 */, float* sp /* r19 */, float* ep /* r18 */) {
    CL_SELECT_MAP* smap; // r16
    CL_SELECT_MAP* smapsv; // r17
    CL_HITPOLY_PLANE* wall; // r2
    CL_HITPOLY_COLUMN* cl; // r2
    int* ptr; // r2
    float min; // r29+0x7C

    ptr = &min;
    // not an inline based on the line numbers.
    asm("lqc2 vf1, 0(%1)\n\
        lqc2 vf2, 0(%2)\n\
        vsub.xyz vf3, vf1, vf2\n\
        vmul.xyz vf3, vf3, vf3\n\
        vaddz.x vf3, vf3, vf3z\n\
        vaddy.x vf3, vf3, vf3y\n\
        qmfc2 t0, vf3\n\
        mtc1 t0, f12\n\
        sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
    res->kind = 0;
    smap = clGetHitSectListVECHIT(sp, ep);
    smapsv = smap;
    clCheckHitSwordVectorDynamicWallNoThru(res, sp, ep, &min);
    clCheckHitSwordVectorDynamicFloorNoThru(res, sp, ep, &min);
    if (smap->base != NULL) {
        for (; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START]; // ???
            clCheckHitNoThruVectorWall(res, sp, ep, &min, wall, cl);
        }
       for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 1]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 1]; // ???
            clCheckHitNoThruVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 3]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 3]; // ???
            clCheckHitNoThruVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 2]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 2]; // ???
            clCheckHitNoThruVectorWall(res, sp, ep, &min, wall, cl);
        }
        for (smap = smapsv; smap->base != NULL; smap++) {
            wall = smap->base + ((int*)smap->base)[SMAP_WALL_BASE_START + 4]; // ???
            cl = smap->base + ((int*) (smap->base + smap->sect * 4))[SMAP_CL_START + SMAP_CL_STRIDE * 4]; // ???
            clCheckHitEyeVectorBGColumn(res, sp, ep, &min, wall, cl);
        }
    }
    clCheckHitEyeVectorCharacter(res, sp, ep, &min, id);
}

/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x00139B90 -> 0x00139D40
*/
// Range: 0x139B90 -> 0x139D40
static void clCheckHitEyeVectorWall(CL_VHIT_RESULT* res /* r21 */, float* sp /* r20 */, float* ep /* r19 */, float* min /* r18 */, CL_HITPOLY_PLANE* pl /* r17 */, int* ptr /* r16 */) {
    int ret; // r2
    CL_HITRESULT cres; // r29+0x70
    float dist; // r29+0xBC

    for (; *ptr != -1; ptr = ptr + 1) {
        
        if (pl[*ptr].material == MATERIAL_TYPE_9 || pl[*ptr].material == MATERIAL_TYPE_11 || pl[*ptr].material == MATERIAL_TYPE_12) continue;

        
        if (pl[*ptr].shape == 0)
            ret = clCheckSubLineToPlane3(&cres,
                                         sp, ep, 
                                         pl[*ptr].p, pl[*ptr].p + 1, pl[*ptr].p + 2);
        else
            ret =clCheckSubLineToPlane(&cres,
                                       sp, ep,
                                       &pl[*ptr].p[0], &pl[*ptr].p[1],&pl[*ptr].p[2],&pl[*ptr].p[3]);

        
        if (ret != 0) {
            // @note: not an inline in other functions??
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist < *min) {
            
                
                *min = dist;
                res->kind = 1;
                volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                clCalcPlaneEquation(pl + *ptr,(res->hobj).wall.nl);
                (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(pl + *ptr);
            }
        }
    }
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x00139D40 -> 0x00139E68
*/
// Range: 0x139D40 -> 0x139E68
static void clCheckHitEyeVectorBGColumn(CL_VHIT_RESULT* res /* r21 */, float* sp /* r20 */, float* ep /* r19 */, float* min /* r18 */, CL_HITPOLY_COLUMN* cl /* r17 */, int* ptr /* r16 */) {
    int ret; // r2
    CL_HITRESULT cres; // r29+0x70
    float dist; // r29+0xBC

    for (; *ptr != -1; ptr = ptr + 1) {
        ret = clCheckSubLineToColumnPlus(&cres, sp, ep, &cl[*ptr].p[0]);
        
        if (ret != 0) {
            // @note: not an inline in other functions??
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist < *min) {
            
                
                *min = dist;
                res->kind = 2;
                volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                *(u_long128*)(&res->hobj.wall.nl) = 0;
                (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&cl[*ptr]);
            }
        }
    }
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x00139E70 -> 0x0013A1F4
*/
// Range: 0x139E70 -> 0x13A1F4
static void clCheckHitEyeVectorDynamicWall(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicWallListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicWallList[ac].use; i++) {
        for (j = 0; clDynamicWallList[ac].dw[i][j].kind != 0; j++) {
        
            if (clDynamicWallList[ac].dw[i][j].material == MATERIAL_TYPE_9 || clDynamicWallList[ac].dw[i][j].material == MATERIAL_TYPE_11 || clDynamicWallList[ac].dw[i][j].material == MATERIAL_TYPE_12) continue;
    
            
            if (clDynamicWallList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicWallList[ac].dw[i][j].p, clDynamicWallList[ac].dw[i][j].p + 1, clDynamicWallList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicWallList[ac].dw[i][j].p[0], &clDynamicWallList[ac].dw[i][j].p[1],&clDynamicWallList[ac].dw[i][j].p[2],&clDynamicWallList[ac].dw[i][j].p[3]);
    
            
            if (ret == 0) continue;
            // @note: not an inline in other functions??
            vec_dist_squared(sp, cres.cp, &dist);
            if (dist >= *min) continue;
            
                
            *min = dist;
            res->kind = 1;
            volatile_vec_copy((res->hobj).wall.cp, cres.cp);
            clCalcPlaneEquation(&clDynamicWallList[ac].dw[i][j], (res->hobj).wall.nl);
            (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicWallList[ac].dw[i][j]);


        }
    }
}

/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x0013A200 -> 0x0013A584
*/
// Range: 0x13A200 -> 0x13A584
static void clCheckHitEyeVectorDynamicFloor(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */) {
    int i; // r16
    int j; // r17
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac = (clDynamicFloorListAct != 0) ? 0 : 1; // r2

    for (i = 0; i < clDynamicFloorList[ac].use; i++) {
        for (j = 0; clDynamicFloorList[ac].dw[i][j].kind != 0; j++) {
        
            if (clDynamicFloorList[ac].dw[i][j].material == MATERIAL_TYPE_9 || clDynamicFloorList[ac].dw[i][j].material == MATERIAL_TYPE_11 || clDynamicFloorList[ac].dw[i][j].material == MATERIAL_TYPE_12) continue;
    
            
            if (clDynamicFloorList[ac].dw[i][j].shape == 0)
                ret = clCheckSubLineToPlane3(&cres,
                                             sp, ep, 
                                             clDynamicFloorList[ac].dw[i][j].p, clDynamicFloorList[ac].dw[i][j].p + 1, clDynamicFloorList[ac].dw[i][j].p + 2);
            else
                ret =clCheckSubLineToPlane(&cres,
                                           sp, ep,
                                           &clDynamicFloorList[ac].dw[i][j].p[0], &clDynamicFloorList[ac].dw[i][j].p[1],&clDynamicFloorList[ac].dw[i][j].p[2],&clDynamicFloorList[ac].dw[i][j].p[3]);
    
            
            if (ret != 0) {
                // @note: not an inline in other functions??
                vec_dist_squared(sp, cres.cp, &dist);
                if (dist < *min) {
                
                    
                    *min = dist;
                    res->kind = 1;
                    volatile_vec_copy((res->hobj).wall.cp, cres.cp);
                    clCalcPlaneEquation(&clDynamicFloorList[ac].dw[i][j], (res->hobj).wall.nl);
                    (res->hobj).wall.pd = (CL_HITPOLY_HEAD*)(&clDynamicFloorList[ac].dw[i][j]);
                }
            }
        }
    }
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x0013A590 -> 0x0013A744
*/
// Range: 0x13A590 -> 0x13A744
static void clCheckHitEyeVectorCharacter(CL_VHIT_RESULT* res /* r22 */, float* sp /* r21 */, float* ep /* r20 */, float* min /* r19 */, u_int id /* r18 */) {
    int i; // r16
    int ret; // r2
    CL_HITRESULT cres; // r29+0x80
    float dist; // r29+0xCC
    int ac; // r2
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_s1;
    s32 var_s0;

    temp_s1 = (clCharaListAct != 0) ? 0 : 1;
    var_s0 = 0;
loop_7:
    if (var_s0 < clCharaListUse[temp_s1]) {
        if (id != clCharaList[temp_s1][var_s0].sc->id && (clCharaList[temp_s1][var_s0].batflg != 0) && (clCheckSubLineToColumnPlus(&cres, sp, ep, clCharaList[temp_s1][var_s0].wcol.p[0]) != 0)) {
            asm("lqc2 vf1, 0(%1)\n\
                lqc2 vf2, 0(%2)\n\
                vsub.xyz vf3, vf1, vf2\n\
                vmul.xyz vf3, vf3, vf3\n\
                vaddz.x vf3, vf3, vf3z\n\
                vaddy.x vf3, vf3, vf3y\n
                qmfc2 t0, vf3\n\
                mtc1 t0, f12\n\
                sw t0, 0(%0)": "=r"(ptr): "r"(sp), "r"(ep): "t0");
            dist = M2C_ERROR(/* unknown instruction: qmfc2.ni $t0, $vf3 */);
            if (dist < *min) {
                *min = dist;
                res->kind = 3;
                res->hobj.wall.nl = cres.cp;
                res->hobj.wall.cp = clCharaList[clCharaListAct][i].opos;
            }
        }
        var_s0 += 1;
        goto loop_7;
    }
}


/*
    Compile unit: E:\work\sh2(CVS全取得)\src\Collision\cl_main.c
    Producer: MW MIPS C Compiler
    Language: C
    Code range: 0x0013A750 -> 0x0013A780
*/
// Range: 0x13A750 -> 0x13A780
int clPermitColumnExpansion(void) {
    return clPermColExpFlg[RoomNameJms()];
}

