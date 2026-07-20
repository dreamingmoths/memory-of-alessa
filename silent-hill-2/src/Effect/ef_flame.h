#ifndef EF_FLAME_H
#define EF_FLAME_H

#include "sh2_common.h"
#include "Effect/ef_common.h"
#include "Effect/ef_sparks.h"

typedef struct EFCTFlamePlane {
    // total size: 0x80
    float timer; // offset 0x0, size 0x4
    float cycle; // offset 0x4, size 0x4
    float width_cycle_param; // offset 0x8, size 0x4
    float height_cycle_param; // offset 0xC, size 0x4
    short current_frame; // offset 0x10, size 0x2
    float draw_wait; // offset 0x14, size 0x4
    float drawing_time; // offset 0x18, size 0x4
    sceVu0FVECTOR rot; // offset 0x20, size 0x10
    sceVu0FVECTOR trans; // offset 0x30, size 0x10
    float s_index; // offset 0x40, size 0x4
    sceVu0FVECTOR start_pos; // offset 0x50, size 0x10
    float w_right_ratio; // offset 0x60, size 0x4
    float w_enlarge_speed; // offset 0x64, size 0x4
    float h_enlarge_speed; // offset 0x68, size 0x4
    float w_enlarge_time; // offset 0x6C, size 0x4
    float h_enlarge_time; // offset 0x70, size 0x4
} EFCTFlamePlane;
STATIC_ASSERT_SIZEOF(EFCTFlamePlane, 0x80);

typedef struct EFCTFlameObject {
    // total size: 0x940
    u_char use; // offset 0x0, size 0x1
    u_char kind; // offset 0x1, size 0x1
    u_int plane_num; // offset 0x4, size 0x4
    u_int index; // offset 0x8, size 0x4
    float life_timer; // offset 0xC, size 0x4
    EFCTObject* base_obj; // offset 0x10, size 0x4
    EFCTFlamePlane plane[16]; // offset 0x20, size 0x800
    EFCTSparksObject sparks; // offset 0x820, size 0x120
} EFCTFlameObject;
STATIC_ASSERT_SIZEOF(EFCTFlameObject, 0x940);

void EFCTFlameChangeCamera(void);
void DrawFlame(void* task);
void InitFlameTexEnv(EFCTTexEnvInfo* pTexInfo);
u_short GetFlameEffectLayerNum(void);

#endif // EF_FLAME_H
