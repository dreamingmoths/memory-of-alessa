#ifndef SKELTON_H
#define SKELTON_H

#include "sh2_common.h"

// total size: 0xF0
typedef struct shSkelton {    
    struct shSkelton* next;   // offset 0x0, size 0x4
    struct shSkelton* parent; // offset 0x4, size 0x4
    sceVu0FMATRIX src_m;      // offset 0x10, size 0x40
    Vector4 src_t;            // offset 0x50, size 0x10
    sceVu0FMATRIX des_m;      // offset 0x60, size 0x40
    Vector4 des_t;            // offset 0xA0, size 0x10
    Vector4 axis;             // offset 0xB0, size 0x10
    float theta;              // offset 0xC0, size 0x4
    float xx;                 // offset 0xC4, size 0x4
    float yy;                 // offset 0xC8, size 0x4
    float zz;                 // offset 0xCC, size 0x4
    float xy;                 // offset 0xD0, size 0x4
    float yz;                 // offset 0xD4, size 0x4
    float zx;                 // offset 0xD8, size 0x4
    u_short c_count;          // offset 0xDC, size 0x2
    u_short c_speed;          // offset 0xDE, size 0x2
    s_char change;            // offset 0xE0, size 0x1
    char reserved;            // offset 0xE1, size 0x1
    char is_key;              // offset 0xE2, size 0x1
    char pad;                 // offset 0xE3, size 0x1
    void* untouchable;        // offset 0xE4, size 0x4
} shSkelton;

void shCharacterInitSkeltons(void);
void shCharacterFreeSkeltons(shSkelton* top /* r2 */);
shSkelton* shCharacterGetSkeletons(int n /* r7 */, u_char* hrc /* r2 */);

#endif // SKELTON_H
