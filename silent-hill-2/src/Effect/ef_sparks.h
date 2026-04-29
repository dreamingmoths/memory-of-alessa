#ifndef EF_SPARKS_H
#define EF_SPARKS_H

#include "common.h"
#include "Effect/ef_common.h"

// total size: 0x60
typedef struct EFCTSparksPlane {
    // Members
    float width; // offset 0x0, size 0x4
    float height; // offset 0x4, size 0x4
    int kind; // offset 0x8, size 0x4
    float trans[4]__attribute__((aligned(16))); // offset 0x10, size 0x10
    float speed[4]__attribute__((aligned(16))); // offset 0x20, size 0x10
    float timer; // offset 0x30, size 0x4
    float life_span; // offset 0x34, size 0x4
    float pos[4]__attribute__((aligned(16))); // offset 0x40, size 0x10
    int rgba[4]; // offset 0x50, size 0x10
} EFCTSparksPlane;

// total size: 0x120
typedef struct EFCTSparksObject {
    // Members
    EFCTObject base_obj; // offset 0x0, size 0x60
    EFCTSparksPlane plane[2]; // offset 0x60, size 0xC0
} EFCTSparksObject;

void DrawSparks(EFCTSparksObject* sparks /* r16 */);

#endif // EF_SPARKS_H
