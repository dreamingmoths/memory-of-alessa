#include "sh2_common.h"
#include "vec.h"
#include "SH2_common/sh_vu0.h"
#include "Effect/ef_malloc.h"
#include "Effect/ef_smoke.h"

static EFCTSmokeObject smoke_obj[32];

static EFCTSmokeObject* CreateSmokeObject(EFCTObject* pObj, u_char kind);

static void SetSmokeDiffusionParam(EFCTSmokePlane* plane);

static void SetSmokeSpeed(EFCTSmokePlane* plane);

static u_int InitEffectVertexSmoke(EFCTVertexData** pVertex);

static void SetSmokeSTValue(EFCTObject* pObj);

static EFCTSmokeObject* GetSmokeObject(EFCTObject* pObj);

static void CountSmokeDiffusionTimer(EFCTSmokeObject* smoke);

static void RenewSmokeRGBA(EFCTObject* pObj, EFCTSmokeObject* smoke);

static void DiffuseSmoke(EFCTObject* pObj, EFCTSmokeObject* smoke);

static void SetSmokeVertex(float* pos, float width, float height, float* trans, EFCTVertexData* VertexData);

static void RenewSmokePos(EFCTSmokePlane* smoke);

static int IsFinishSmoke(EFCTSmokeObject* smoke);

static inline float setDiffusionRate(float rate) { // @note: used for match hack
    float r = shRandF();
    r = 1.05f * r;
    r = rate + r;
    r = 300.0f * r;
    return r;
}

#line 25
int InitEffectObjectSmoke(EFCTObject* pObj, int nIndex, float* pos, u_char kind) {
    pObj->Index = nIndex;
    shVectorCopy(pObj->Pos, pos);

    
    if (kind == 0) {
        pObj->Pos[0] += 125.0f;
    }
    else if (kind == 1) {
        pObj->Pos[0] -= 125.0f;
    }
    

    
    if (CreateSmokeObject(pObj, kind) == NULL) {
        
        return 0;
    }

    shVectorZero(pObj->trans);
    shVectorZero(pObj->rot);
    
    
    pObj->width = 300.0f;
    pObj->height = 300.0f;
    
    
    pObj->VertexNum = InitEffectVertexSmoke(&pObj->pVertex);
    if (pObj->VertexNum == 0) {
        return 0;
    }
    
    
    SetSmokeSTValue(pObj);
    
    return 1;
}

#line 64
static EFCTSmokeObject* CreateSmokeObject(EFCTObject* pObj, u_char kind) {
    EFCTSmokeObject* smoke = NULL;
    int i;

    
    for (i = 0; i < 32; i++) {
        if (smoke_obj[i].use == 0) {
            
            smoke_obj[i].use = 1;
            smoke_obj[i].base_obj = pObj;
            smoke = &smoke_obj[i];
            break;
        }   
    }
    
    
    if (smoke != NULL) {

        
        smoke->index = i;
        
        
        smoke->kind = kind;

        for (i = 0; i < 16; i++) {
            
            
            smoke->plane[i].valid = 1;
            
            
            SetSmokeDiffusionParam(&smoke->plane[i]);
            
            
            smoke->plane[i].timer = 0;
            
            
            
            shVectorZero(smoke->plane[i].trans);
            smoke->plane[i].trans[0] = shSway1f(-300.0f, 300.0f);
            smoke->plane[i].trans[1] = shSway1f(-80.0f,  80.0f);
            smoke->plane[i].trans[2] = shSway1f(-300.0f, 300.0f);
            
            
            SetSmokeSpeed(smoke->plane[i].trans);
        }
    }
    else {
        ASSERT_ON_LINE(0, 111);
    }   
    
    return smoke;
}

#line 122
static void SetSmokeDiffusionParam(EFCTSmokePlane* plane) {
    float rate = 1.0f;
    plane->cycle = 5.95f + shSway1f(1.5f, 1.5f);
    
    
    plane->width_cycle_param = setDiffusionRate(rate);
    
    plane->height_cycle_param = 300.0f * (1.05f + (rate * shRandF()));
    
}

static void SetSmokeSpeed(EFCTSmokePlane* plane) {
    float rate1 = 110.0f;
    float rate2 = -110.0f;
    
    
    plane->speed[0] = shSway1f(rate2, rate1);
    
    
    plane->speed[1] = 40.0f + (100.0f * shRandF());
    
    
    
    plane->speed[2] = shSway1f(rate2, rate1);

}

#line 153
static u_int InitEffectVertexSmoke(EFCTVertexData** pVertex) {
    int i;


    if (*pVertex != NULL) {
        EfctFree(*pVertex);
        *pVertex = NULL;
    }
    *pVertex = EfctMalloc(0x1800);
    if (*pVertex == NULL) {
        return 0;
    }

    for (i = 0; i < 64; i++) {
        (*pVertex)[i].rgba[0] = 112;
        (*pVertex)[i].rgba[1] = 104;
        (*pVertex)[i].rgba[2] = 104;
        (*pVertex)[i].rgba[3] = 20;
    
        (*pVertex)[i].is_valid = 1;
    }
    
    return 64;
}

#line 180
static void SetSmokeSTValue(EFCTObject* pObj) {
    int i;
    int s_index, t_index;

    for (i = 0; i < 16; i++) {
        
        switch (shRandI() % 3) {
            case 0:
                s_index = 2;
                t_index = 7;
                break;
            case 1:
                s_index = 3;
                t_index = 6;
                break;
            case 2:
                s_index = 3;
                t_index = 7;
                break;
        }
        
        pObj->pVertex[4*i].stq[0]   = 0.125f * s_index;
        pObj->pVertex[4*i].stq[1]   = 0.125f * t_index;
        pObj->pVertex[4*i+1].stq[0] = 0.125f * (s_index + 1);
        pObj->pVertex[4*i+1].stq[1] = 0.125f * t_index;
        pObj->pVertex[4*i+2].stq[0] = 0.125f * s_index;
        pObj->pVertex[4*i+2].stq[1] = 0.125f * (t_index + 1);
        pObj->pVertex[4*i+3].stq[0] = 0.125f * (s_index + 1);
        pObj->pVertex[4*i+3].stq[1] = 0.125f * (t_index + 1);
    }
}

#line 214
void InitSmokeTexEnv(EFCTTexEnvInfo* pTexInfo) {
    pTexInfo->tfx = 0;
    pTexInfo->transparency = 2;
    pTexInfo->clut_id = 1;
}

#line 222
void DrawSmoke(void* task) {
    EFCTTask* pTask;
    EFCTSmokeObject* smoke;

    pTask = task;
    if (pTask == NULL) {
        ASSERT_ON_LINE(0, 228);
    }
    
    
    
    smoke = GetSmokeObject(pTask->pObj);
    if (smoke == NULL) {
       ASSERT_ON_LINE(0, 235);
    }
    
   
    
    
    
    
    
    
    
    RenewSmokeRGBA(pTask->pObj, smoke);
    
    
    DiffuseSmoke(pTask->pObj, smoke);
    
    
    
    
    
    
    EFCTTinyThreeDWork(pTask->pObj);
    
    
    
    ClipEffectObject(pTask->pObj);
    
    
    
    DrawPrimitive(pTask->pObj);
    
    
    CountSmokeDiffusionTimer(smoke);
    
    
    if (IsFinishSmoke(smoke) == 1) {
    
        smoke->use = 0;
        
        
        EFCTCutEffectTask(pTask);
    }
    
}

#line 281
static EFCTSmokeObject* GetSmokeObject(EFCTObject* pObj) {
    int i;

    
    
    for (i = 0; i < 32; i++) {
        if (smoke_obj[i].use == 1 && smoke_obj[i].base_obj == pObj) {
            return &smoke_obj[i];
        } 
    }
    
    return NULL;
}

#line 297
static void CountSmokeDiffusionTimer(EFCTSmokeObject* smoke) {
    int i;

    if (smoke != NULL) {
        for (i = 0; i < 16; i++) {
            if (smoke->plane[i].valid == 1) {
               
                smoke->plane[i].timer += EFCTGetPassingTimePerFrame();
                
                if (smoke->plane[i].timer > smoke->plane[i].cycle) {
                
                    smoke->plane[i].timer = 0.0f;
                    
                    smoke->plane[i].valid = 0;
                }
            }   
        }
    }
    
}

#line 320
static void RenewSmokeRGBA(EFCTObject* pObj, EFCTSmokeObject* smoke) {
    float ratio;
    sceVu0IVECTOR rgba;
    int i;

    for (i = 0; i < 16; i++) {

        ratio = shSinF(PI * (0.5f * (1.0f + (smoke->plane[i].timer / smoke->plane[i].cycle))));
        rgba[0] = (u_short) (112.0f * ratio);
        rgba[1] = (u_short) (104.0f * ratio);
        rgba[2] = (u_short) (104.0f * ratio);
        
        ratio = shSinF(PI * (smoke->plane[i].timer / smoke->plane[i].cycle));
        rgba[3] = (u_short) (20.0f * ratio);
        EFCTResetRGBA(rgba, &pObj->pVertex[4*i]);
    }
}

#line 340
static void DiffuseSmoke(EFCTObject* pObj, EFCTSmokeObject* smoke) {
    int i;
    float delta_width, delta_height;
    float ratio;
    float width;
    float height;
    
    for (i = 0; i < 16; i++) {
    
        
        if (smoke->plane[i].timer == 0.0f) {
            
            SetSmokeDiffusionParam(&smoke->plane[i]);
            
            smoke->plane[i].trans[0] = shSway1f(-300.0f, 300.0f);
            smoke->plane[i].trans[1] = -80.0f * shRandF();
            smoke->plane[i].trans[2] = shSway1f(-300.0f, 300.0f);
            shVectorZero(smoke->plane[i].pos);
        
            SetSmokeSpeed(smoke->plane[i].trans);
        }
        
        
        ratio = shSinF(PI * (0.5f * (smoke->plane[i].timer / smoke->plane[i].cycle)));
        width = smoke->plane[i].width_cycle_param * ratio;
        height = smoke->plane[i].height_cycle_param * ratio;
        
        if ((width < 0.0f) || (height < 0.0f)) {
            ASSERT_ON_LINE(0, 368);
        }
        
        
        delta_width = pObj->width + width;
        delta_height = pObj->height + height;
        
        
        RenewSmokePos(&smoke->plane[i]);
        
        
        SetSmokeVertex(smoke->plane[i].pos, delta_width, delta_height, smoke->plane[i].trans, &pObj->pVertex[i*4]);
        
    }
        
}

#line 387
static void SetSmokeVertex(float* pos, float width, float height, float* trans, EFCTVertexData* VertexData) {
    VertexData[0].LocalPos[0] = trans[0] + (pos[0] + 0.5f * -width);
    VertexData[0].LocalPos[1] = trans[1] + (pos[1] + 0.75f * -height);
    VertexData[0].LocalPos[2] = pos[2] + trans[2];
    VertexData[0].LocalPos[3] = 1.0f;

    VertexData[1].LocalPos[0] = (trans[0] + (pos[0] + 0.5f * width));
    VertexData[1].LocalPos[1] = (trans[1] + (pos[1] + 0.75f * -height));
    VertexData[1].LocalPos[2] = (pos[2] + trans[2]);
    VertexData[1].LocalPos[3] = 1.0f;
    
    VertexData[2].LocalPos[0] = (trans[0] + (pos[0] + 0.5f * -width));
    VertexData[2].LocalPos[1] = (trans[1] + (pos[1] + 0.25f * height));
    VertexData[2].LocalPos[2] = (pos[2] + trans[2]);
    VertexData[2].LocalPos[3] = 1.0f;
    
    VertexData[3].LocalPos[0] = (trans[0] + (pos[0] + 0.5f * width));
    VertexData[3].LocalPos[1] = (trans[1] + (pos[1] + 0.25f * height));
    VertexData[3].LocalPos[2] = (pos[2] + trans[2]);
    VertexData[3].LocalPos[3] = 1.0f;
}

#line 411
static void RenewSmokePos(EFCTSmokePlane* smoke) {
    smoke->pos[0] = smoke->timer * smoke->speed[0];
    smoke->pos[1] = -1.0f * (smoke->timer * smoke->speed[1]);
    smoke->pos[2] = smoke->timer * smoke->speed[2];

}

#line 423
void SetFlameSmokeValid(u_int arg0, u_int arg1) { // @note: signature different from DWARF

}

#line 427
static int IsFinishSmoke(EFCTSmokeObject* smoke) {
    int i;
    int ret;

    ret = 1;

    for (i = 0; i < 16; i++) {

        if (smoke->plane[i].valid == 1) {
        
            ret = 0;
        }
    }
    
    return ret;
}
