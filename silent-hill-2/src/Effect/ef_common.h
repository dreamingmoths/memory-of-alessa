#ifndef EF_COMMON_H
#define EF_COMMON_H

#include "common.h"
#include "libvifpk.h"
#include "taskman/shtskman.h"

// total size: 0x18
typedef struct EFCTAnimationData {
    // Members
    u_short TotalFrame; // offset 0x0, size 0x2
    short CurrentFrameNo; // offset 0x2, size 0x2
    float DrawFrameWait; // offset 0x4, size 0x4
    float DrawingTime; // offset 0x8, size 0x4
    short StartFrameNo; // offset 0xC, size 0x2
    short FinishFrameNo; // offset 0xE, size 0x2
    u_char DoLoop; // offset 0x10, size 0x1
    u_char Status; // offset 0x11, size 0x1
    void (* SetAnimParam)(void *); // offset 0x14, size 0x4
} EFCTAnimationData;
 
// total size: 0x60
typedef struct EFCTVertexData {
    // Members
    float LocalPos[4]__attribute__((aligned(16))); // offset 0x0, size 0x10
    float WorldPos[4]__attribute__((aligned(16))); // offset 0x10, size 0x10
    int ScreenPos[4]__attribute__((aligned(16))); // offset 0x20, size 0x10
    u_char rgba[4]; // offset 0x30, size 0x4
    float stq[4]__attribute__((aligned(16))); // offset 0x40, size 0x10
    signed short is_valid; // offset 0x50, size 0x2
} EFCTVertexData;

// total size: 0x60
typedef struct EFCTObject {
    // Members
    u_short Index; // offset 0x0, size 0x2
    short Using; // offset 0x2, size 0x2
    short EffectKind; // offset 0x4, size 0x2
    short AutoDisappear; // offset 0x6, size 0x2
    float width; // offset 0x8, size 0x4
    float height; // offset 0xC, size 0x4
    u_short VertexNum; // offset 0x10, size 0x2
    u_short LayerNum; // offset 0x12, size 0x2
    float trans[4]__attribute__((aligned(16))); // offset 0x20, size 0x10
    float rot[4]__attribute__((aligned(16))); // offset 0x30, size 0x10
    float Pos[4]__attribute__((aligned(16))); // offset 0x40, size 0x10
    short chara_kind; // offset 0x50, size 0x2
    short chara_id; // offset 0x52, size 0x2
    EFCTVertexData * pVertex; // offset 0x54, size 0x4
    EFCTAnimationData * pAnimData; // offset 0x58, size 0x4
} EFCTObject;

void EFCTInit(void);
void EFCTDoTask(void);
void EFCTSetPassingTimePerFrame(float time /* r29 */);
void EFCTKickPacket(void);

void EFCTSetGunFire(float * pos /* r19 */, float * vec /* r18 */);

void EFCTSetGunFireEddie(float * Pos /* r16 */, float * vec /* r2 */);

void EFCTSetGunSmoke(float * pos);
void EFCTResetRGBA(int * rgba /* r2 */, EFCTVertexData * pVertex /* r2 */);
float EFCTGetPassingTimePerFrame();
void ClipEffectObject2(EFCTObject * pObj /* r18 */);
void DrawPrimitive(EFCTObject * pObj /* r17 */);
void EFCTThreeDWork(EFCTObject * pObj /* r17 */);

extern u_char EFCTTaskBuf[131072];
extern u_long128 efctPacket[4096];
extern u_long128 efctheap[32768];
extern EFCTObject EFCTLocalDataBuffer[32];

#endif // EF_COMMON_H
