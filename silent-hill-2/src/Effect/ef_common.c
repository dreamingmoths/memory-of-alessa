#include "Effect/ef_common.h"
#include "Effect/ef_packet.h"
#include "Effect/ef_malloc.h"
#include "SH2_common/sh2dt.h"
#include "Event/item.h"
#include "Chacter/m3_play_event.h"
#include "Multi_thr/dma/dma1cmd.h"

static void EFCTInitEffectTask(void);
static void SetGunFire(float* Pos /* r21 */, float* vec /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */);
static void SetGunSmoke(float* Pos /* r20 */, int wep_kind /* r19 */, u_char light /* r18 */);
static EFCTTask* EFCTEntryEffectTask(short Kind /* r17 */);
static u_short GetEffectLayerNum(short EffectKind /* r2 */);
static int EFCTDeleteOldBloodDropTask(void);
static void InitEffectTexEnv(int EffectKind /* r2 */);

void EFCTInit(void) {
    shTSKInitTaskList(EFCTTaskBuf, sizeof(EFCTTaskBuf));

    if (&efctheap != NULL)         
        EfctInitHeap(&efctheap, sizeof(efctheap));
    
    if (&efctPacket != NULL)
        shEfctPkInit(&efctPacket);
    
    EFCTInitEffectTask();
}

static void EFCTInitEffectTask(void) {   
    int i; // r16
    
    for (i = 0; i < 32; i++) {
        EFCTLocalDataBuffer[i].Using = 0;
        if (EFCTLocalDataBuffer[i].pAnimData != NULL) {
            EfctFree(EFCTLocalDataBuffer[i].pAnimData);
            EFCTLocalDataBuffer[i].pAnimData = NULL;
        }
        if (EFCTLocalDataBuffer[i].pVertex != NULL) {
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
            if (EFCTDeleteOldBloodDropTask() == 0) {
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

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetGunSmoke); //

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SetGunSmoke); //

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetDramaDemoAngelaPapa); // yes but unsure

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetBrokenGlass); //

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetSmoke); //

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", GetEffectLayerNum);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", InitEffectTexEnv);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTEntryEffectTask);

void EFCTCutEffectTask(EFCTTask* ptr) {
    if (ptr->pObj->Using == 1) {
        ptr->pObj->Using = 0;
        if (ptr->pObj->pVertex != NULL) {
            EfctFree(ptr->pObj->pVertex);
            ptr->pObj->pVertex = NULL;
        }
        if (ptr->pObj->pAnimData != NULL) {
            EfctFree(ptr->pObj->pAnimData);
            ptr->pObj->pAnimData = NULL;
        }
        shTSKDelTask((shTskTASK *)ptr);
    }
}

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", InitEffectAnimData);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", InitEffectVertexSprite);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SetEffectVertexSpriteXY);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SetEffectVertexSpriteXZ);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SpriteLocalRot);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTNextFrame);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTAutoNextFrame);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTThreeDWork);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTTinyThreeDWork);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", DrawPrimitive);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTMakePacket);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", SetVertexPkData);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTGetGiftag);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetAlphaEnvironment);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteTask);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteOldBloodDropTask);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDeleteOldTask);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTDoCtrlDummy);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", GetSpriteRotAngle);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", ClipEffectObject);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", ClipEffectObject2);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTClipVertex);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTResetRGBA);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTSetPassingTimePerFrame);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", EFCTGetPassingTimePerFrame);

INCLUDE_ASM("asm/nonmatchings/Effect/ef_common", CalibrationZValue);
