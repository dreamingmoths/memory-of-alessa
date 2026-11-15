#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "vec.h"

#include "Effect/ef_common.h"
#include "Effect/ef_malloc.h"

#include "Chacter/m3_sc.h"

static void GetGunFireObjectSize(int weapon_kind, sceVu0FVECTOR width, sceVu0FVECTOR height, sceVu0FVECTOR depth);

static u_int InitEffectVertexGunFire(sceVu0FVECTOR Pos, float width, float height, float depth, u_char* rgba, EFCTVertexData** pVertex);

static void SetEffectVertexGunFire(sceVu0FVECTOR Pos /* @note not in dwarf */, float width, float height, float depth, EFCTVertexData* VertexData);

static void GunFireLocalRotV(EFCTVertexData* pVertex, sceVu0FVECTOR Direction, float Angle);

static void GetGunSmokeObjectSize(int weapon_kind, sceVu0FVECTOR width, sceVu0FVECTOR height);

static void GetGunFireColor(u_char light, u_char* rgba);

static void GetGunSmokeColor(u_char light, u_char* rgba);

static void SetBloodSprayGravityParam(EFCTObject* pObj);

static void SetBloodSprayObjectPos(EFCTObject* pObj);

static void SetBloodDropObjectPos(EFCTObject* pObj);

static void SetBloodPoolObjectPos(EFCTObject* pObj);

static void SetGunSmokeObjectPos(EFCTObject* pObj);

static void SetBloodSpraySTValue(EFCTObject* pObj);

static void SetGunFireSTValue(EFCTObject* pObj);

static void SetGunSmokeSTValue(EFCTObject* pObj);

static void EFCTDecreaseAlpha(EFCTObject* pObj);

#line 173
int InitEffectObjectGunFire(EFCTObject* pObj, int nIndex, sceVu0FVECTOR Pos, sceVu0FVECTOR vec, int wep_kind, u_char light_status) {
    float ZAng;
    int i;
    float width, height, depth;
    u_char rgba[4];

    pObj->Index = nIndex;
    shVectorCopy(pObj->Pos, Pos);
   
    
    if (!InitEffectAnimData(1, 0.025f, 0, &pObj->pAnimData)) {
        return false;
    }
    
    
    GetGunFireObjectSize(wep_kind, &width, &height, &depth);
    
    
    pObj->width = width;
    pObj->height = height;
    
    
    GetGunFireColor(light_status, rgba);
    
    
    pObj->VertexNum = InitEffectVertexGunFire(pObj->Pos, width, height, depth, rgba, &pObj->pVertex);
    if (pObj->VertexNum == 0) {
        return 0;
    }
   
    
    for (i = 0; i < 12; i++) {
        ZAng = GetSpriteRotAngle(TAU, 12, i, 30);
        GunFireLocalRotV(&pObj->pVertex[4 * i], vec, 
                         ZAng);
    }
    
    shVectorZero(pObj->trans);
    shVectorZero(pObj->rot);

    
    SetGunFireSTValue(pObj);
    
    return true;
}

// @hack weird inlines needed for match. seems to be a meme
static inline float shSwayWidth(float x) { float n = -x; float h = x / 2.0f; return shSway1f(n, h); }
static inline float shSwayHeight(float x) { float h = x / 2.0f; float n = -x; return shSway1f(n, h); }

#line 221
int InitEffectObjectGunSmoke(EFCTObject* pObj, int nIndex, sceVu0FVECTOR Pos, int wep_kind, u_char light_status) {
    u_char rgba[4];
    float ang;
    float width, height;

    pObj->Index = nIndex;
    shVectorCopy(pObj->Pos, Pos);
   
    
    if (!InitEffectAnimData(8, 0.1f, 0, &pObj->pAnimData)) {
        return false;
    }
    
    
    GetGunSmokeObjectSize(wep_kind, &width, &height);
    
    
    pObj->width = width;
    pObj->height = height;
    
    
    shVectorZero(pObj->trans);
    pObj->trans[0] = shSwayWidth(0.1f * width);
    pObj->trans[1] = shSwayHeight(0.1f * height);

    
    GetGunSmokeColor(light_status, rgba);

    
    shVectorZero(pObj->rot);
    ang = shRandI() % 361 + -180;
    pObj->rot[2] = TO_RAD(ang);
    pObj->VertexNum = InitEffectVertexSprite(pObj->Pos, pObj->width, pObj->height, 0, &pObj->pVertex, pObj->rot, rgba);
    if (pObj->VertexNum == 0) {
        return 0;
    }
    
    
    SetGunSmokeSTValue(pObj);
    
    return true;
}


#line 267
static void GetGunFireObjectSize(int weapon_kind, float* width, float* height, float* depth) {
    switch (weapon_kind) {
        case 1:
            #line 271
            *width  = 96.0f;
            *height = 96.0f;
            *depth  = 144.0f;
            return;
        
        case 2:
            *width  = 288.0f;
            *height = 288.0f;
            *depth  = 96.0f;
            return;
        
        case 3:
            *width  = 72.0f;
            *height = 72.0f;
            *depth  = 180.0f;
            return;
       
        
        default:
            ASSERT(0);
    }
    return;
}


#line 297
static u_int InitEffectVertexGunFire(sceVu0FVECTOR Pos, float width, float height, float depth, u_char* rgba, EFCTVertexData** pVertex) {
    int i;

    
    if (*pVertex != NULL) {
        EfctFree(*pVertex);
        *pVertex = NULL;
    }
    *pVertex = EfctMalloc(0x1200);
    if (*pVertex == NULL) {
        // no vertices
        return 0;
    }
    
    
    SetEffectVertexGunFire(Pos, width, height, depth, *pVertex);
    
    for (i = 0; i < 48; i++) {
    
        (*pVertex)[i].rgba[0] = rgba[0];
        (*pVertex)[i].rgba[1] = rgba[1];
        (*pVertex)[i].rgba[2] = rgba[2];
        (*pVertex)[i].rgba[3] = rgba[3];
        
        (*pVertex)[i].is_valid = true;
    }
    
    return 48;
}


#line 329
static void SetEffectVertexGunFire(sceVu0FVECTOR Pos, float width, float height, float depth, EFCTVertexData* VertexData) {
    int i;

    for (i = 0; i < 12; i++) {
        VertexData[4 * i + 0].LocalPos[0] = -width / 2.0f;
        VertexData[4 * i + 0].LocalPos[1] = 0;
        VertexData[4 * i + 0].LocalPos[2] = 0;
        VertexData[4 * i + 0].LocalPos[3] = 1.0f;
        
        VertexData[4 * i + 1].LocalPos[0] = width / 2.0f;
        VertexData[4 * i + 1].LocalPos[1] = 0;
        VertexData[4 * i + 1].LocalPos[2] = 0;
        VertexData[4 * i + 1].LocalPos[3] = 1.0f;
        
        VertexData[4 * i + 2].LocalPos[0] = -width / 2.0f;
        VertexData[4 * i + 2].LocalPos[1] = height / 2.0f;
        VertexData[4 * i + 2].LocalPos[2] = depth;
        VertexData[4 * i + 2].LocalPos[3] = 1.0f;
        
        VertexData[4 * i + 3].LocalPos[0] = width / 2.0f;
        VertexData[4 * i + 3].LocalPos[1] = height / 2.0f;
        VertexData[4 * i + 3].LocalPos[2] = depth;
        VertexData[4 * i + 3].LocalPos[3] = 1.0f;
    }
}



#line 358
static void GunFireLocalRotV(EFCTVertexData* pVertex, sceVu0FVECTOR Direction, float Angle) {
    sceVu0FMATRIX mtx;
    sceVu0FVECTOR rot;
    int i;

    #line 374
    vwVectorToAngle(rot, Direction);
    rot[2] = Angle;

    shUnitMatrix(mtx);
    shRotMatrixZ(mtx, mtx, rot[2]); shRotMatrixX(mtx, mtx, rot[0]); shRotMatrixY(mtx, mtx, rot[1]);


    
    for (i = 0; i < 4; i++) {
       shVectorTransform(pVertex[i].LocalPos, mtx);
       
        #line 386
    }
}

#line 413
static void GetGunSmokeObjectSize(int weapon_kind, sceVu0FVECTOR width, sceVu0FVECTOR height) {
    switch (weapon_kind) {
        case 1:
            #line 417
            *width = 130.0f;
            *height = 130.0f;
            return;
        
        case 2:
            *width = 180.0f;
            *height = 180.0f;
            return;
        
        case 3:
            *width = 160.0f;
            *height = 160.0f;
            return;

        #line 432
        default:
            ASSERT(0);
    }
    return;
}


#line 440
static void GetGunFireColor(u_char light, u_char* rgba) {
    
    if (BgIsOut(0) || light) {
        rgba[0] = 40;
        rgba[1] = 40;
        rgba[2] = 40;
    } else {
    
        
        rgba[0] = 36;
        rgba[1] = 32;
        rgba[2] = 32;
    }
    
    rgba[3] = 38;
}



#line 460
static void GetGunSmokeColor(u_char light, u_char* rgba) {
    
    if (BgIsOut(0) || light) {
        rgba[0] = 42;
        rgba[1] = 42;
        rgba[2] = 42;
    } else {
    
        
        rgba[0] = 26;
        rgba[1] = 26;
        rgba[2] = 31;
    }
    
    rgba[3] = 96;
}


#line 480
void DrawBloodSpray(void* task) {
    EFCTTask* pTask = (EFCTTask*) task;
    int IsNext = false;
    
    
    if (pTask == NULL) {
        ASSERT(0);
    }
    
    
    

    #line 493
    IsNext = EFCTNextFrame(pTask->pObj, 0);
    
    
    
    
    
    
    
    
    
    
    #line 505
    if (IsNext == true) {
        
        SetBloodSprayObjectPos(pTask->pObj);
    }
    
    
    SetBloodSprayGravityParam(pTask->pObj);
    
    
    
    
    
    
    #line 519
    EFCTTinyThreeDWork(pTask->pObj);
    
    
    
    ClipEffectObject(pTask->pObj);
    
    
    SetBloodSpraySTValue(pTask->pObj);
    
    
    DrawPrimitive(pTask->pObj);
    
    
    if (pTask->pObj->pAnimData->Status == 2) {
        #line 541
        EFCTCutEffectTask(pTask);
    }




    #line 548
}


#line 552
void DrawBloodDrop(void* task) {
    EFCTTask* pTask;
    int IsNext = false;

    pTask = (EFCTTask*) task;
    if (pTask == NULL) {
        ASSERT(0);
    }


    
    IsNext = EFCTNextFrame(pTask->pObj, 0);
    
    #line 575
    if (IsNext == true) {
        
        SetBloodDropObjectPos(pTask->pObj);
    }
    
    
    EFCTThreeDWork(pTask->pObj);
    
    
    ClipEffectObject(pTask->pObj);
    
    
    DrawPrimitive(pTask->pObj);
    
    
    if (shCharacterGetSubCharacter(pTask->pObj->chara_kind, pTask->pObj->chara_id) == NULL) {
        
        EFCTCutEffectTask(pTask);
    }

}


#line 599
void DrawBloodPool(void* task) {
    EFCTTask* pTask;
    int IsNext = false;

    pTask = (EFCTTask*) task;
    if (pTask == NULL) {
        ASSERT(0);
    }


    
    IsNext = EFCTNextFrame(pTask->pObj, 0);

    #line 622
    if (IsNext == true) {
        
        SetBloodPoolObjectPos(pTask->pObj);
    }
    
    
    EFCTThreeDWork(pTask->pObj);
    
    
    ClipEffectObject(pTask->pObj);
    
    
    DrawPrimitive(pTask->pObj);
    
    
    if (shCharacterGetSubCharacter(pTask->pObj->chara_kind, pTask->pObj->chara_id) == NULL) {
        
        EFCTCutEffectTask(pTask);
    }

}


#line 646
void DrawGunFire(void* task) {
    EFCTTask* pTask;
    int IsNext = false; // @note unused

    pTask = (EFCTTask*) task;
    if (pTask == NULL) {
        ASSERT(0);
    }


    #line 657
    EFCTNextFrame(pTask->pObj, 0);

    #line 669
    EFCTThreeDWork(pTask->pObj);
    
    
    ClipEffectObject(pTask->pObj);
    
    
    DrawPrimitive(pTask->pObj);
    
    
    if (pTask->pObj->pAnimData->Status == 2) {
        #line 687
        EFCTCutEffectTask(pTask);
        #line 694
    }
}

#line 698
void DrawGunSmoke(void* task) {
    EFCTTask* pTask;
    int IsNext = false; // @note unused

    pTask = (EFCTTask*) task;
    if (pTask == NULL) {
        ASSERT(0);
    }

    #line 709
    EFCTNextFrame(pTask->pObj, 0);

    #line 721
    SetGunSmokeObjectPos(pTask->pObj);

    #line 729
    EFCTTinyThreeDWork(pTask->pObj);
    
    

    EFCTDecreaseAlpha(pTask->pObj);
    

    ClipEffectObject(pTask->pObj);
    

    DrawPrimitive(pTask->pObj);
    

    if (pTask->pObj->pAnimData->Status == 2) {
        #line 751
        EFCTCutEffectTask(pTask);
    }





}


#line 762
static void SetBloodSprayGravityParam(EFCTObject* pObj) {
    float t = (pObj->pAnimData->CurrentFrameNo + 1) * EFCTGetPassingTimePerFrame();
    
    pObj->trans[1] += 35.0f * t * t; // @note SQUARE macro doesn't match
}

#line 770
static void SetBloodSprayObjectPos(EFCTObject* pObj) {
    const float swayMax = 20.0f, zero = 0.0f; // @hack none of these const floats are in dwarf
    if (pObj->pAnimData->CurrentFrameNo == pObj->pAnimData->StartFrameNo) {
        const float swayMin = -20.0f, maxSwayHalf = 10.0f, minSwayHalf = -10.0f; // @hack not in dwarf
        switch (pObj->Index) {
            case 0:
                pObj->trans[0] = zero;
                pObj->trans[1] = zero;
                return;
            case 1:
                pObj->trans[0] = shSway1f(minSwayHalf + minSwayHalf, maxSwayHalf + maxSwayHalf);
                pObj->trans[1] = shSway1f(swayMax, swayMax);
                return;
            case 2:
                pObj->trans[0] = shSway1f(swayMax, swayMax);
                pObj->trans[1] = shSway1f(swayMax, swayMax);
                return;
            case 3:
                pObj->trans[0] = shSway1f(swayMin + maxSwayHalf, swayMax - maxSwayHalf);
                pObj->trans[1] = shSway1f(swayMax, swayMax);
                return;
            case 4:
                pObj->trans[0] = shSway1f(maxSwayHalf, maxSwayHalf);
                pObj->trans[1] = shSway1f(swayMax, swayMax);
                break;
        }
    }

}


#line 802
static void SetBloodDropObjectPos(EFCTObject* pObj) {
    
    if (pObj->pAnimData->CurrentFrameNo == pObj->pAnimData->StartFrameNo) {
        float width; // @bnote not in dwarf
        
        pObj->width = width = (32.0f + (32.0f * shRandF())) - 16.0f;
        pObj->height = width;
    } else {
        float scale = 33.8f; //@ note not in dwarf
        
        pObj->width *= scale * EFCTGetPassingTimePerFrame();
        pObj->height *= scale * EFCTGetPassingTimePerFrame();
    }

    
    if (pObj->pAnimData->CurrentFrameNo == pObj->pAnimData->StartFrameNo) {
    
        pObj->trans[0] = shSway1f(-96.0f, 96.0f);
        pObj->trans[2] = shSway1f(-96.0f, 96.0f);
    }

    #line 844
    SetEffectVertexSpriteXZ(pObj->width, pObj->height, pObj->pVertex);
    SpriteLocalRot(pObj->pVertex, (s32) pObj->VertexNum, pObj->rot);
}



#line 851
static void SetBloodPoolObjectPos(EFCTObject* pObj) {
    if (pObj->pAnimData->CurrentFrameNo == pObj->pAnimData->StartFrameNo) {
        float width = 150.0f; // @note not in dwarf
        pObj->width = width;
        pObj->height = width;
    } else {
        float scale = 30.88f; //@ note not in dwarf
        
        pObj->width *= scale * EFCTGetPassingTimePerFrame();
        pObj->height *= scale * EFCTGetPassingTimePerFrame();
    }
    
    
    if (pObj->pAnimData->CurrentFrameNo == pObj->pAnimData->StartFrameNo) {
        if (pObj->Index == 0) {
            pObj->trans[0] = -1.0f * shSway1f(112.5f, 112.5f);
            pObj->trans[2] = -1.0f * shSway1f(112.5f, 112.5f);
        } else {
            if (pObj->Index == 1) {
                pObj->trans[0] = shSway1f(112.5f, 112.5f);
                pObj->trans[2] = -1.0f * shSway1f(112.5f, 112.5f);
            } else {
                if (pObj->Index == 2) {
                    pObj->trans[0] = -1.0f * shSway1f(112.5f, 112.5f);
                    pObj->trans[2] = shSway1f(112.5f, 112.5f);
                } else {
                    if (pObj->Index == 3) {
                        pObj->trans[0] = shSway1f(112.5f, 112.5f);
                        pObj->trans[2] = shSway1f(112.5f, 112.5f);
                    }
                }
            }
        }
    }
    SetEffectVertexSpriteXZ(pObj->width, pObj->height, pObj->pVertex);
    SpriteLocalRot(pObj->pVertex, pObj->VertexNum, pObj->rot);
}



#line 892
static void SetGunSmokeObjectPos(EFCTObject* pObj) {
    float ratio;

    #line 899
    ratio = EFCTGetPassingTimePerFrame() / 0.8f;
    pObj->width += 130.0f * ratio;
    pObj->height += 130.0f * ratio;

    
    SetEffectVertexSpriteXY(pObj->width, pObj->height, pObj->pVertex);
    SpriteLocalRot(pObj->pVertex, pObj->VertexNum, pObj->rot);
}



#line 911
static void SetBloodSpraySTValue(EFCTObject* pObj) {
    u_int FrameNumber;
    int TopLeftS;
    int i;

    FrameNumber = pObj->pAnimData->CurrentFrameNo;

    
    if (pObj->pAnimData->Status != 1) {
        for (i = 0; i < pObj->VertexNum; i++) {
           
            pObj->pVertex[i].stq[0] = 0.0f;
            pObj->pVertex[i].stq[1] = 0.0f;
        }
        return;
    }

    
    switch (pObj->Index) {
        case 0:
            TopLeftS = 6;
            break;
        case 1:
            TopLeftS = 3;
            break;
        case 2:
            TopLeftS = 4;
            break;
        case 3:
            TopLeftS = 2;
            break;
        case 4:
            TopLeftS = 5;
            break;
    }

    
    pObj->pVertex[0].stq[0] = 0.125f * TopLeftS;
    pObj->pVertex[0].stq[1] = 0.125f * FrameNumber;
    pObj->pVertex[1].stq[0] = 0.125f * (TopLeftS + 1);
    pObj->pVertex[1].stq[1] = 0.125f * FrameNumber;
    pObj->pVertex[2].stq[0] = 0.125f * TopLeftS;
    pObj->pVertex[2].stq[1] = 0.125f * (FrameNumber + 1);
    pObj->pVertex[3].stq[0] = 0.125f * (TopLeftS + 1);
    pObj->pVertex[3].stq[1] = 0.125f * (FrameNumber + 1);
}

#line 1036
static void SetGunFireSTValue(EFCTObject* pObj) {
    int i;

    for (i = 0; i < 12; i++) {
        pObj->pVertex[4 * i + 0].stq[0] = 0.25f;
        pObj->pVertex[4 * i + 0].stq[1] = 0.875f;
        pObj->pVertex[4 * i + 1].stq[0] = 0.375f;
        pObj->pVertex[4 * i + 1].stq[1] = 0.875f;
        pObj->pVertex[4 * i + 2].stq[0] = 0.25f;
        pObj->pVertex[4 * i + 2].stq[1] = 0.75f;
        pObj->pVertex[4 * i + 3].stq[0] = 0.375f;
        pObj->pVertex[4 * i + 3].stq[1] = 0.75f;
    }
}


#line 1053
static void SetGunSmokeSTValue(EFCTObject* pObj) {
    int S;
    int T;

    #line 1070
    switch (shRandI() % 3) {
        case 0:
            S = 2;
            T = 7;
            break;
        case 1:
            S = 3;
            T = 6;
            break;
        case 2:
            S = 3;
            T = 7;
            break;
    }

    
    pObj->pVertex[0].stq[0] = 0.125f * S;
    pObj->pVertex[0].stq[1] = 0.125f * T;
    pObj->pVertex[1].stq[0] = 0.125f * (S + 1);
    pObj->pVertex[1].stq[1] = 0.125f * T;
    pObj->pVertex[2].stq[0] = 0.125f * S;
    pObj->pVertex[2].stq[1] = 0.125f * (T + 1);
    pObj->pVertex[3].stq[0] = 0.125f * (S + 1);
    pObj->pVertex[3].stq[1] = 0.125f * (T + 1);

}


#line 1099
u_short GetStageEffectLayerNum(short EffectKind) {
    u_short Ret;

    switch (EffectKind) {
        case 1:
            Ret = 5;
            break;
        case 2:
            Ret = 3;
            break;
        case 3:
            Ret = 3;
            break;
        case 4:
            Ret = 1;
            break;
        case 5:
            Ret = 3;
            break;
    }

    return Ret; // @info default case not accounted for
}

#line 1127
void InitBloodTexEnv(EFCTTexEnvInfo* pTexInfo) {
    pTexInfo->transparency = 0;
    pTexInfo->tfx = 0;
    pTexInfo->clut_id = 2;
}

#line 1155
void InitGunFireTexEnv(EFCTTexEnvInfo* pTexInfo) {
    pTexInfo->tfx = 0;
    pTexInfo->transparency = 1;
    pTexInfo->clut_id = 0;
    return;
}


#line 1164
void InitGunSmokeTexEnv(EFCTTexEnvInfo* pTexInfo) {
    pTexInfo->tfx = 0;
    pTexInfo->transparency = 1;
    pTexInfo->clut_id = 0;
    return;
}

#line 1186
static void EFCTDecreaseAlpha(EFCTObject* pObj) {
    int i;
    float val;

    do {
        if (pObj->pVertex->rgba[3] <= 0) {
            val = 0.0f;
            break;
        } else if (pObj->pVertex->rgba[3] < 10) {
            val = 30.0f * EFCTGetPassingTimePerFrame();
            break;
        } else if (pObj->pVertex->rgba[3] < 32) {
            val = 60.0f * EFCTGetPassingTimePerFrame();
            break;
        } else if (pObj->pVertex->rgba[3] < 48) {
            val = 120.0f * EFCTGetPassingTimePerFrame();
            break;
        }
        val = 150.0f * EFCTGetPassingTimePerFrame();
        break;
    } while (0);
    for (i = 0; i < pObj->VertexNum; i++) {
        pObj->pVertex[i].rgba[3] -= (int) val;
    }
}

