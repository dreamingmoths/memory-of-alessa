#include "Effect/ef_common.h"
#include "Effect/ef_packet.h"
#include "Effect/ef_malloc.h"
#include "SH2_common/sh2dt.h"
#include "Event/item.h"
#include "Chacter/m3_play_event.h"
#include "Multi_thr/dma/dma1cmd.h"
#include "Effect/ef_stage.h"
#include "Effect/ef_broken_glass.h"
#include "Effect/ef_smoke.h"

static void EFCTInitEffectTask(void);
static void SetGunFire(float* Pos /* r21 */, float* vec /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */);
static void SetGunSmoke(float* Pos /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */);
static EFCTTask* EFCTEntryEffectTask(short Kind /* r17 */);
static u_short GetEffectLayerNum(short EffectKind /* r2 */);
static int EFCTDeleteOldBloodDropTask(void);
static void InitEffectTexEnv(int EffectKind /* r2 */);
static EFCTTask* EFCTEntryEffectTask(short Kind /* r17 */);
static int EFCTAutoNextFrame(EFCTObject* pObj /* r2 */);
/* static */ void EFCTDoCtrlDummy(void* ptr /* r2 */);

extern /* static */ void (* EFCTControlFunc[9])(void *);

void EFCTInit(void) {
    shTSKInitTaskList(EFCTTaskBuf, sizeof(EFCTTaskBuf));

    if (&efctheap)         
        EfctInitHeap(&efctheap, sizeof(efctheap));
    
    if (&efctPacket)
        shEfctPkInit(&efctPacket);
    
    EFCTInitEffectTask();
}

static void EFCTInitEffectTask(void) {   
    int i; // r16
    
    for (i = 0; i < 32; i++) {
        EFCTLocalDataBuffer[i].Using = 0;
        if (EFCTLocalDataBuffer[i].pAnimData) {
            EfctFree(EFCTLocalDataBuffer[i].pAnimData);
            EFCTLocalDataBuffer[i].pAnimData = NULL;
        }
        if (EFCTLocalDataBuffer[i].pVertex) {
            EfctFree(EFCTLocalDataBuffer[i].pVertex);
            EFCTLocalDataBuffer[i].pVertex = NULL;
        }
    }
    shTSKFreeTaskLine(4);
}

void EFCTDoTask(void) {
    shEfctPkReset();
    EFCTSetPassingTimePerFrame(shGetDT());
    shTSKExecuteTask(4);
}

void EFCTKickPacket(void) {
    void* addr = shEfctPkGetKickAddrByd1cSend(); // r2 
    d1cSend(addr);
}

void EFCTSetGunFire(float* Pos /* r19 */, float* vec /* r18 */) {          
    int weapon_kind; // r16
    u_char light; // r17
    
    weapon_kind = PlayerGetJamesWeapon();
    light = item.light_switch;
    SetGunFire(Pos, vec, weapon_kind, light);
    SetGunSmoke(Pos, weapon_kind, light);
}

void EFCTSetGunFireEddie(float* Pos /* r16 */, float* vec /* r2 */) {
    SetGunFire(Pos, vec, 1, 1);
    SetGunSmoke(Pos, 1, 1);
}

static void SetGunFire(float* Pos /* r21 */, float* vec /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */) {
    EFCTTask* pTask; // r22
    u_short LayerNum; // r16
    int i; // r17

    LayerNum = GetEffectLayerNum(4);
    for (i = 0; i < LayerNum; i++) {
        pTask = EFCTEntryEffectTask(4);
        if (pTask == NULL) {
            if (!EFCTDeleteOldBloodDropTask()) {
                return;
            }
            continue;
        }
        if (InitEffectObjectGunFire(pTask->pObj, i, Pos, vec, wep_kind, light) == 0) {
            EFCTCutEffectTask(pTask);
            return;
        }
        pTask->pObj->LayerNum = LayerNum;
    }
    InitEffectTexEnv(4);
}

void EFCTSetGunSmoke(float* pos) {
    return;
}

static void SetGunSmoke(float* Pos /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */) {
    EFCTTask* pTask; // r21
    int i; // r16
    u_short LayerNum; // r17
    
    LayerNum = GetEffectLayerNum(5);
    for (i = 0; i < LayerNum; i++) {
        pTask = EFCTEntryEffectTask(5);
        if (pTask == NULL) {
            if (!EFCTDeleteOldBloodDropTask()) {
                return;
            }
            continue;
        }
        if (InitEffectObjectGunSmoke(pTask->pObj, i, Pos, wep_kind, light) == 0) {
            EFCTCutEffectTask(pTask);
            return;
        }
        pTask->pObj->LayerNum = LayerNum;
    }
    InitEffectTexEnv(5);
}

extern float data_angela_papa_tv_pos[4];
extern float data_angela_papa_tv_dir[4];
extern float data_angela_papa_chara_pos[2][4];
INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetDramaDemoAngelaPapa);

void EFCTSetBrokenGlass(float* parent_pos /* r20 */, float* parent_direction /* r19 */, float (* chara_pos)[4] /* r18 */) {   
    EFCTTask* pTask; // r21    
    int i; // r16
    u_short LayerNum; // r17

    LayerNum = GetEffectLayerNum(6);
    for (i = 0; i < LayerNum; i++) {
        pTask = EFCTEntryEffectTask(6);
        if (pTask == NULL) {
            return;
        }
        if (InitEffectObjectBrokenGlass(pTask->pObj, i, parent_pos, parent_direction, chara_pos) == 0) {
            EFCTCutEffectTask(pTask);
            return;
        }
        pTask->pObj->LayerNum = LayerNum;
    }
    InitEffectTexEnv(6);
}

void EFCTSetSmoke(float* pos /* r19 */, u_char kind /* r18 */) {
    EFCTTask* pTask; // r16
    int i; // r17
    u_short LayerNum = 1; // r2

    for (i = 0; i < LayerNum; i++) {
        pTask = EFCTEntryEffectTask(8);
        if (pTask == NULL) {
            return;
        }
        if (InitEffectObjectSmoke(pTask->pObj, i, pos, kind) == 0) {
            EFCTCutEffectTask(pTask);
            return;
        }
        pTask->pObj->LayerNum = LayerNum;
    }
    InitEffectTexEnv(8);
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", GetEffectLayerNum);

INCLUDE_RODATA("asm/nonmatchings/Effect/ef_common", @1103_0x0038DE90);

INCLUDE_RODATA("asm/nonmatchings/Effect/ef_common", @1104_0x0038DEB0);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", InitEffectTexEnv);

static EFCTTask* EFCTEntryEffectTask(short Kind /* r17 */) {
    EFCTObject* pObject; // r16
    shTskTASK* pTask; // r2    
    int i = 0; // r4

    pObject = EFCTLocalDataBuffer;
    while (pObject->Using == 1) {
        if (i >= 32) {
            return NULL;
        }
        i++;
        pObject++;
    }
    pTask = shTSKSetTask(EFCTControlFunc[Kind], 4);
    if (!pTask) {
        return NULL;
    }
    pObject->EffectKind = Kind;
    pObject->Using = 1;
    ((EFCTTask*) pTask)->pObj = pObject;
    ((EFCTTask*) pTask)->exe.atr = Kind;
    return pTask;
}
void EFCTCutEffectTask(EFCTTask* ptr) {
    if (ptr->pObj->Using == 1) {
        ptr->pObj->Using = 0;
        if (ptr->pObj->pVertex) {
            EfctFree(ptr->pObj->pVertex);
            ptr->pObj->pVertex = NULL;
        }
        if (ptr->pObj->pAnimData) {
            EfctFree(ptr->pObj->pAnimData);
            ptr->pObj->pAnimData = NULL;
        }
        shTSKDelTask((shTskTASK*) ptr);
    }
}

int InitEffectAnimData(u_short TotalFrame /* r17 */, float DrawFrameWait /* r20 */, short StartFrame /* r16 */, EFCTAnimationData** pAnim /* r18 */) {    
    EFCTAnimationData AnimData;
    
    if (*pAnim) {
        EfctFree(*pAnim);
        *pAnim = NULL;
    }
    *pAnim = (EFCTAnimationData*)EfctMalloc(sizeof(EFCTAnimationData));
    if (*pAnim == NULL) {
        return 0;
    }
    ASSERT_ON_LINE(StartFrame < TotalFrame, 1073);
    AnimData.Status = 0;
    AnimData.StartFrameNo = StartFrame;
    if (StartFrame <= 0) {
        AnimData.FinishFrameNo = TotalFrame - 1;
    } else {
        AnimData.FinishFrameNo = StartFrame - 1;
    }
    AnimData.TotalFrame = TotalFrame;
    AnimData.DrawFrameWait = DrawFrameWait;
    AnimData.CurrentFrameNo = AnimData.StartFrameNo;
    AnimData.DrawingTime = 0.0f;
    AnimData.SetAnimParam = NULL;
    **pAnim = AnimData;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", InitEffectVertexSprite);

void SetEffectVertexSpriteXY(float width /* r29 */, float height /* r29 */, EFCTVertexData* VertexData /* r2 */) {
    VertexData[0].LocalPos[0] = -width / 2.0f;
    VertexData[0].LocalPos[1] = -height / 2.0f;
    VertexData[0].LocalPos[2] = 0.0f;
    VertexData[0].LocalPos[3] = 1.0f;
    
    VertexData[1].LocalPos[0] = width / 2.0f;
    VertexData[1].LocalPos[1] = -height / 2.0f;
    VertexData[1].LocalPos[2] = 0.0f;
    VertexData[1].LocalPos[3] = 1.0f;
    
    VertexData[2].LocalPos[0] = -width / 2.0f;
    VertexData[2].LocalPos[1] = height / 2.0f;
    VertexData[2].LocalPos[2] = 0.0f;
    VertexData[2].LocalPos[3] = 1.0f;
    
    VertexData[3].LocalPos[0] = width / 2.0f;
    VertexData[3].LocalPos[1] = height / 2.0f;
    VertexData[3].LocalPos[2] = 0.0f;
    VertexData[3].LocalPos[3] = 1.0f;
}

void SetEffectVertexSpriteXZ(float width /* r29 */, float height /* r29 */, EFCTVertexData* VertexData /* r2 */) {
    VertexData[0].LocalPos[0] = -width / 2.0f;
    VertexData[0].LocalPos[1] = 0.0f;
    VertexData[0].LocalPos[2] = -height / 2.0f;
    VertexData[0].LocalPos[3] = 1.0f;
    
    VertexData[1].LocalPos[0] = width / 2.0f;
    VertexData[1].LocalPos[1] = 0.0f;
    VertexData[1].LocalPos[2] = -height / 2.0f;
    VertexData[1].LocalPos[3] = 1.0f;
    
    VertexData[2].LocalPos[0] = -width / 2.0f;
    VertexData[2].LocalPos[1] = 0.0f;
    VertexData[2].LocalPos[2] = height / 2.0f;
    VertexData[2].LocalPos[3] = 1.0f;
    
    VertexData[3].LocalPos[0] = width / 2.0f;
    VertexData[3].LocalPos[1] = 0.0f;
    VertexData[3].LocalPos[2] = height / 2.0f;
    VertexData[3].LocalPos[3] = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SpriteLocalRot);

int EFCTNextFrame(EFCTObject* pObj /* r2 */, int DoLoop /* r2 */) {
    pObj->pAnimData->DoLoop = DoLoop;
    return EFCTAutoNextFrame(pObj);
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTAutoNextFrame);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTThreeDWork);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTTinyThreeDWork);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", DrawPrimitive);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTMakePacket);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SetVertexPkData);

const char rodata_1193_0x0038DF30[] = "ef_common.c:1118> assert:(%s)\n";

INCLUDE_RODATA("asm/nonmatchings/Effect/ef_common", @1279_0x0038DF50);

INCLUDE_RODATA("asm/nonmatchings/Effect/ef_common", @1424_0x0038DF70);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTGetGiftag);

INCLUDE_RODATA("asm/nonmatchings/Effect/ef_common", @1455);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetAlphaEnvironment);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteTask);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteOldBloodDropTask);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteOldTask);

/* static */ void EFCTDoCtrlDummy(void* ptr /* r2 */) {
    EFCTCutEffectTask(ptr);
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", GetSpriteRotAngle);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", ClipEffectObject);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", ClipEffectObject2);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTClipVertex);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTResetRGBA);

void EFCTSetPassingTimePerFrame(float time /* r29 */) {
    passing_time = time;
}

float EFCTGetPassingTimePerFrame(void) {
    return passing_time;
}

void CalibrationZValue(u_int vertex_num /* r2 */, int z /* r2 */, EFCTVertexData* pVertex /* r2 */) {
    int i; // r8
    for (i = 0; i < vertex_num; i++) {
        pVertex[i].ScreenPos[2] += z;
    }
}
