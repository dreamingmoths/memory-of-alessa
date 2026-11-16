#ifndef EF_SMOKE_H
#define EF_SMOKE_H

#include "common.h"
#include "Effect/ef_common.h"

typedef struct EFCTSmokePlane {
    sceVu0FVECTOR trans; // offset 0x0, size 0x10
    sceVu0FVECTOR speed; // offset 0x10, size 0x10
    float timer; // offset 0x20, size 0x4
    float cycle; // offset 0x24, size 0x4
    float width_cycle_param; // offset 0x28, size 0x4
    float height_cycle_param; // offset 0x2C, size 0x4
    sceVu0FVECTOR pos; // offset 0x30, size 0x10
    signed int valid; // offset 0x40, size 0x4
} EFCTSmokePlane ;

typedef struct EFCTSmokeObject {
    u_int index; // offset 0x0, size 0x4
    u_char use; // offset 0x4, size 0x1
    u_char kind; // offset 0x5, size 0x1
    EFCTObject* base_obj; // offset 0x8, size 0x4
    EFCTSmokePlane plane[16]; // offset 0x10, size 0x500
} EFCTSmokeObject;

int InitEffectObjectSmoke(EFCTObject* pObj /* r16 */, int nIndex /* r2 */, float* pos /* r2 */, u_char kind /* r2 */);

void InitSmokeTexEnv(EFCTTexEnvInfo* pTexInfo);

void DrawSmoke(void* task) ;

void SetFlameSmokeValid(u_int arg0, u_int arg1); // @note: signature different from DWARF

#endif // EF_SMOKE_H
