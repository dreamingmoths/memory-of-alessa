#ifndef EF_COMMON_H
#define EF_COMMON_H

// total size: 0x18
typedef struct EFCTAnimationData {
    // Members
    unsigned short TotalFrame; // offset 0x0, size 0x2
    signed short CurrentFrameNo; // offset 0x2, size 0x2
    float DrawFrameWait; // offset 0x4, size 0x4
    float DrawingTime; // offset 0x8, size 0x4
    signed short StartFrameNo; // offset 0xC, size 0x2
    signed short FinishFrameNo; // offset 0xE, size 0x2
    unsigned char DoLoop; // offset 0x10, size 0x1
    unsigned char Status; // offset 0x11, size 0x1
    void (* SetAnimParam)(void *); // offset 0x14, size 0x4
} EFCTAnimationData;
 
// total size: 0x60
typedef struct EFCTVertexData {
    // Members
    float LocalPos[4]; // offset 0x0, size 0x10
    float WorldPos[4]; // offset 0x10, size 0x10
    signed int ScreenPos[4]; // offset 0x20, size 0x10
    unsigned char rgba[4]; // offset 0x30, size 0x4
    float stq[4]; // offset 0x40, size 0x10
    signed short is_valid; // offset 0x50, size 0x2
} EFCTVertexData;

// total size: 0x60
typedef struct EFCTObject {
    // Members
    unsigned short Index; // offset 0x0, size 0x2
    signed short Using; // offset 0x2, size 0x2
    signed short EffectKind; // offset 0x4, size 0x2
    signed short AutoDisappear; // offset 0x6, size 0x2
    float width; // offset 0x8, size 0x4
    float height; // offset 0xC, size 0x4
    unsigned short VertexNum; // offset 0x10, size 0x2
    unsigned short LayerNum; // offset 0x12, size 0x2
    float trans[4]; // offset 0x20, size 0x10
    float rot[4]; // offset 0x30, size 0x10
    float Pos[4]; // offset 0x40, size 0x10
    signed short chara_kind; // offset 0x50, size 0x2
    signed short chara_id; // offset 0x52, size 0x2
    struct EFCTVertexData * pVertex; // offset 0x54, size 0x4
    struct EFCTAnimationData * pAnimData; // offset 0x58, size 0x4
};

void EFCTSetGunFire(float * pos /* r19 */, float * vec /* r18 */);
void EFCTSetGunSmoke(float * pos);
void EFCTResetRGBA(int * rgba /* r2 */, struct EFCTVertexData * pVertex /* r2 */);
float EFCTGetPassingTimePerFrame();
void ClipEffectObject2(struct EFCTObject * pObj /* r18 */);
void DrawPrimitive(struct EFCTObject * pObj /* r17 */);
void EFCTThreeDWork(struct EFCTObject * pObj /* r17 */);

#endif // EF_COMMON_H
