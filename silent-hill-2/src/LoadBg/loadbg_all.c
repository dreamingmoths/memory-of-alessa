#include "LoadBg/loadbg_all.h"
#include "LoadBg/loadbg_common.h"
#include "LoadBg/loadbg_2x2.h"

loadBgAll_2x2Info lbAll_2x2Info; // size: 0xC0, address: 0x1202DB0

static void loadBgAll_Set2x2Block(int id, int glb_crd, int block_no, int bx, int bz, float dist2);
static void loadBgAll_Sort2x2Block(void);
static int loadBgAll_SetLoadRequestOutdoor2x2(void);
static int loadBgAll_SetCheckRequestOutdoor2x2(void);
static int loadBgAll_SetCheckActivateOutdoor2x2(loadBgAll_2x2Block* block);
static int loadBgAll_2x2LoadRequest(int cleanup, int* ret3p, int* ret1p);
static int loadBgAll_2x2CheckRequest(int* ret5p);
static int loadBgAll_2x2ActivateRequestOutdoor(int* ret2p);
static int loadBgAll_ExecLoadRequestOutdoor2x2(int* needUnits, int* remUnits, int* reqUnits, int* miss);
static int loadBgAll_SetLoadRequestIndoor2x2(int rid, int glb_crd, int* mid4);
static int loadBgAll_2x2ActivateRequestIndoor(int* mid4, int* ret2p);
static int loadBgAll_ExecLoadRequestIndoor2x2(int rid, int glb_crd, int* blocks, int* reqUnits, int* miss);

void loadBgAll_Init(void) {
    
    loadBg2x2_CheckLoadWork();
}

static void loadBgAll_Set2x2Block(int id, int glb_crd, int block_no, int bx, int bz, float dist2) {
    int mid = 0;
    if ((glb_crd != 0) && (block_no != 0)) mid = (glb_crd << 0x10) | block_no;
    
    lbAll_2x2Info.block[id].mid = mid;
    lbAll_2x2Info.block[id].bx = bx;
    lbAll_2x2Info.block[id].bz = bz;
    lbAll_2x2Info.block[id].dist2 = dist2;
}

static void loadBgAll_Sort2x2Block(void) {
    loadBgAll_2x2Block* block = lbAll_2x2Info.block;
    loadBgAll_2x2Block** sort = &lbAll_2x2Info.sort[0];
    float nx, nz, nxz;   
    float fx, fz, fxz;
    
    *sort++ = block;
    nx = block[1].dist2;
    nz = block[2].dist2;
    nxz = block[3].dist2;    
    fx = block[5].dist2;
    fz = block[6].dist2; 
    fxz = block[7].dist2; 
    if (nx <= nz) {
        
        *sort++ = &block[1];
        *sort++ = &block[2];
        
        if (nxz <= fz) {
            *sort++ = &block[3];
            *sort++ = &block[6];
            
            if (fx <= fxz) {
                *sort++ = &block[5];
                *sort++ = &block[7];
            } else {
                *sort++ = &block[7];
                *sort++ = &block[5];
            }
        } else {
            *sort++ = &block[6];
            
            if (nxz <= fx) {
                *sort++ = &block[3];
            
                if (fx <= fxz) {
                    *sort++ = &block[5];
                    *sort++ = &block[7];
                } else {
                    *sort++ = &block[7];
                    *sort++ = &block[5];
                }
            } else {
                *sort++ = &block[5];
                *sort++ = &block[3];
                *sort++ = &block[7];
            }
        }
    } else {
        *sort++ = &block[2];
        *sort++ = &block[1];
        
        if (nxz <= fx) {
            *sort++ = &block[3];
            *sort++ = &block[5];
        
            if (fz <= fxz) {
                *sort++ = &block[6];
                *sort++ = &block[7];
            } else {
                *sort++ = &block[7];
                *sort++ = &block[6];
            }
        } else {
            *sort++ = &block[5];
            
            if (nxz <= fz) {
                *sort++ = &block[3];
            
                if (fz <= fxz) {
                    *sort++ = &block[6];
                    *sort++ = &block[7];
                } else {
                    *sort++ = &block[7];
                    *sort++ = &block[6];
                }
            } else {
                *sort++ = &block[6];
                *sort++ = &block[3];
                *sort++ = &block[7];
            }
        }
    }
    
    *sort = NULL;
}

static int loadBgAll_SetLoadRequestOutdoor2x2(void) {
    loadBgAll_2x2Block** sort;
    float dist2; 
    int ret; int reduceRate8; 
    int cleanup;   
    int idx;   
    cleanup = 0;
    for (sort = lbAll_2x2Info.sort; *sort != NULL; sort++) {
        idx = *sort - lbAll_2x2Info.block;
        
        reduceRate8 = 0;
        if (lbAll_2x2Info.block[idx ^ 4].mid != 0) {
            dist2 = (*sort)->dist2;
            reduceRate8 += dist2 > 56250000.0f;
            reduceRate8 += dist2 > 72250000.0f;
            reduceRate8 += dist2 > 90250000.0f;
            reduceRate8 += dist2 > 110250000.0f;
            reduceRate8 += dist2 > 132250000.0f;
            reduceRate8 += dist2 > 156250000.0f;
            reduceRate8 += dist2 > 196000000.0f;
        }
        if (dist2 < 306250000.0f) {
            
            cleanup += loadBg2x2_SetRequestOutdoor(0,
                                               reduceRate8,
                                               (*sort)->bx,
                                               (*sort)->bz,
                                               (*sort)->mid);            
        }       
    }
    ret = cleanup;
    return ret;
}

static int loadBgAll_SetCheckRequestOutdoor2x2(void) {
    loadBgAll_2x2Block** sort; 
    float dist2;
    int ret = 0;
    for (sort = lbAll_2x2Info.sort; *sort != NULL; sort++) {
        dist2 = (*sort)->dist2;
        if (dist2 < 27562500.0f) {
            ret++;
            
            loadBg2x2_SetRequestOutdoor(ret,
                                        0,
                                        (*sort)->bx,
                                        (*sort)->bz,
                                        (*sort)->mid);
            
        }
    }
    return ret;
}

static int loadBgAll_SetCheckActivateOutdoor2x2(loadBgAll_2x2Block* block) {
    float dist2;
    
    dist2 = block->dist2;
    if (dist2 < 100000000.0f) {
        
        loadBg2x2_SetRequestOutdoor(1, 
                                    0, 
                                    block->bx, 
                                    block->bz, 
                                    block->mid);
    }
    
    return loadBg2x2_GetOutdoorBlockSection(block->bx, block->bz);
}

static int loadBgAll_2x2LoadRequest(int cleanup, int* ret3p, int* ret1p) {
    int ret1, ret2, ret3;
    loadBg2x2_SetRequest();
    if (cleanup != 0) loadBg2x2_CleanupNonRequest();
    ret1 = loadBg2x2_LoadRequest();
    ret2 = loadBg2x2_CheckRequest(&ret3);
    if (ret1p != NULL) *ret1p = ret1;
    if (ret3p != NULL) *ret3p = ret3;
    return ret2;
}

static int loadBgAll_2x2CheckRequest(int* ret5p) {
    int ret4, ret5;
    loadBg2x2_SetRequest();
    ret4 = loadBg2x2_CheckRequest(&ret5);
    if (ret5p != NULL) *ret5p = ret5;
    return ret4;
}

static int loadBgAll_2x2ActivateRequestOutdoor(int* ret2p) {
    loadBgAll_2x2Block* block; 
    int retA[4]; 
    int retB[4];
    int ret1; int ret2; int i;  int slot;

    ret1 = 0;
    ret2 = 0;
    for (i = 0; i <= 3; i++) {
        loadBg2x2_ClearRequest();
        block = &lbAll_2x2Info.block[i];
        slot = loadBgAll_SetCheckActivateOutdoor2x2(block);
        loadBg2x2_SetRequest();
        retA[i] = loadBg2x2_ActivateRequestOutdoor(slot, block->mid, &retB[i]);
        ret1 += retA[i];
        ret2 += retB[i];
    }
    loadBg2x2_ActivateRequestOutdoor(4, 0, 0);
    if (ret2p != 0) *ret2p = ret2;
    return ret1;
}

static int loadBgAll_ExecLoadRequestOutdoor2x2(int* needUnits, int* remUnits, int* reqUnits, int* miss) {
    int ret1; int ret2; int ret3; int ret4; int ret5; int ret6; int ret7; int cleanup;
    
    
    loadBg2x2_ClearRequest();
    
    
    cleanup = loadBgAll_SetLoadRequestOutdoor2x2();

    ret2 = loadBgAll_2x2LoadRequest(cleanup, &ret3, &ret1);

    loadBg2x2_ClearRequest();

    loadBgAll_SetCheckRequestOutdoor2x2();

    ret4 = loadBgAll_2x2CheckRequest(&ret5);

    loadBgAll_2x2ActivateRequestOutdoor(&ret7);

    if (miss != NULL) *miss = ret1;
    if (reqUnits != NULL) *reqUnits = ret3;
    if (remUnits != NULL) *remUnits = ret2;
    if (needUnits != NULL) *needUnits = ret5;

    if (cleanup != 0) {
        ret4 += ret1;
    }
    return ret4;    
}

static int loadBgAll_SetLoadRequestIndoor2x2(int rid, int glb_crd, int* mid4) {
    int cleanup;


    loadBg2x2_ClearRequest();

    cleanup = loadBg2x2_SetRequestIndoor(rid, mid4);

    return cleanup != 0;
}

static int loadBgAll_2x2ActivateRequestIndoor(int* mid4, int* ret2p) {
    int ret1;
    int ret2;
    
    ret1 = loadBg2x2_ActivateRequestIndoor(mid4, &ret2);
    if (ret2p != NULL) *ret2p = ret2;
    return ret1;
}

static int loadBgAll_ExecLoadRequestIndoor2x2(int rid, int glb_crd, int* blocks, int* reqUnits, int* miss) {
    int ret1; int ret2; int ret3; int ret4; int ret5;
    int mid4[4]; 
    int cleanup; 
    int i; 
    int mid; int block_no;
    for (i = 0; i < 4; i++) {
        
        
        mid = 0;
        if (blocks[i]) mid = (glb_crd << 0x10) | blocks[i];
        mid4[i] = mid;
    }


    cleanup = loadBgAll_SetLoadRequestIndoor2x2(rid, glb_crd, mid4);

    ret2 = loadBgAll_2x2LoadRequest(cleanup, &ret3, &ret1);

    ret4 = loadBgAll_2x2ActivateRequestIndoor(mid4, &ret5);

    if (ret2 < ret4) ret2 = ret4;
    if (ret3 < ret5) ret3 = ret5;

    if (miss != NULL) *miss = ret1;
    if (reqUnits != NULL) *reqUnits = ret3;
    
    if (cleanup != 0) {
        ret2 += ret1;
    }
    
    return ret2;
}

int loadBgAll_PrepareAround(int* loading, int* require) {
    loadBgCommon_Info_T* info = _loadBgCommon_Info;
    int nbdx; 
    int nbdz;
    int cpbx;
    int cpbz;
    float dx;
    float dz;
    int icx;
    int icz;
    int glb_crd;
    int rid;
    int prio;
    int force;
    int lockUnits;
    int needUnits;
    int remUnits;
    int reqUnits;
    int miss;
    float pfcx;
    float pfcz;



    loadBg2x2_CheckLoadWork();

    glb_crd = _loadBgCommon_Info->glb_crd;

    if (!glb_crd) return 0;

    
    icx = info->icx;
    icz = info->icz;

    
    cpbx = icx - info->minx;
    cpbz = icz - info->minz;

    rid = info->AroundID[cpbx][cpbz];

    
    
    if (BgIsOut(glb_crd)) {

        
        
        
        
        
        loadBgAll_Set2x2Block(0,
                              glb_crd,
                              rid,
                              icx,
                              icz,
                              0.0f);

        
        
        pfcx = info->px - info->fcx;
        pfcz = info->pz - info->fcz;

        
        nbdx = (pfcx >= 0.0f) ? 1 : -1;
        nbdz = (pfcz >= 0.0f) ? 1 : -1;

        
        dx = 10000.0f + ((nbdx < 0) ? pfcx : -pfcx);
        
        dz = 10000.0f + ((nbdz < 0) ? pfcz : -pfcz);

        
        loadBgAll_Set2x2Block(1,
                              glb_crd,
                              info->AroundID[cpbx + nbdx][cpbz],
                              icx + nbdx,
                              icz,
                              dx * dx);

        
        loadBgAll_Set2x2Block(2,
                              glb_crd,
                              info->AroundID[cpbx][cpbz + nbdz],
                              icx,
                              icz + nbdz,
                              dz * dz);

        
        loadBgAll_Set2x2Block(3,
                              glb_crd,
                              info->AroundID[cpbx + nbdx][cpbz + nbdz],
                              icx + nbdx,
                              icz + nbdz,
                              dx * dx + dz * dz);

        
        if (dx <= dz) {

            loadBgAll_Set2x2Block(4,
                                  glb_crd,
                                  info->AroundID[cpbx + nbdx + nbdx][cpbz],
                                  icx + nbdx + nbdx,
                                  icz,
                                  (20000.0f + dx) * (20000.0f + dx));

        
            loadBgAll_Set2x2Block(7,
                                  glb_crd,
                                  info->AroundID[cpbx + nbdx][cpbz - nbdz],
                                  icx + nbdx,
                                  icz - nbdz,
                                  dx * dx + (20000.0f - dz) * (20000.0f - dz));

        
        } else {
            
            loadBgAll_Set2x2Block(4,
                                  glb_crd,
                                  info->AroundID[cpbx][cpbz + nbdz + nbdz],
                                  icx,
                                  icz + nbdz + nbdz,
                                  (20000.0f + dz) * (20000.0f + dz));

            
            loadBgAll_Set2x2Block(7,
                                  glb_crd,
                                  info->AroundID[cpbx - nbdx][cpbz + nbdz],
                                  icx - nbdx,
                                  icz + nbdz,
                                  dz * dz + (20000.0f - dx) * (20000.0f - dx));
        }

        
        
        
        loadBgAll_Set2x2Block(5,
                              glb_crd,
                              info->AroundID[cpbx - nbdx][cpbz],
                              icx - nbdx,
                              icz,
                              (20000.0f - dx) * (20000.0f - dx));

        
        loadBgAll_Set2x2Block(6,
                              glb_crd,
                              info->AroundID[cpbx][cpbz - nbdz],
                              icx,
                              icz - nbdz,
                              (20000.0f - dz) * (20000.0f - dz));

        
        
        
        loadBgAll_Sort2x2Block();

        
        
        
        lockUnits = loadBgAll_ExecLoadRequestOutdoor2x2(&needUnits,
                                                        &remUnits,
                                                        &reqUnits,
                                                        &miss);
    
    
    } else {
        remUnits = loadBgAll_ExecLoadRequestIndoor2x2(rid,
                                                      glb_crd,
                                                      info->BlockID,
                                                      &reqUnits,
                                                      &miss);

        needUnits = reqUnits;
        lockUnits = remUnits;
    }

    if (loading != NULL) *loading = remUnits;
    if (require != NULL) *require = reqUnits;

    
    
    
    info->unit = reqUnits;
    info->load = remUnits;
    info->need = needUnits;
    info->lock = lockUnits;
    info->miss = miss;

    return lockUnits;
}
