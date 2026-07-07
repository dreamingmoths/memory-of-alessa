#ifndef SPACK_H
#define SPACK_H

#include "sh2_common.h"

// total size: 0x10
typedef struct SPACK_OT_DATA {
    // Members
    u_short DmaQwc;   // offset 0x0, size 0x2
    u_short DmaId;    // offset 0x2, size 0x2
    void* Addr;       // offset 0x4, size 0x4
    u_int W;          // offset 0x8, size 0x4
    u_short VifQwc;   // offset 0xC, size 0x2
    u_char EnvID;     // offset 0xE, size 0x1
    u_char VifDirect; // offset 0xF, size 0x1
} SPACK_OT_DATA;

// total size: 0x10
typedef struct SPACK_ENV_DATA {
    // Members
    u_short DmaQwc; // offset 0x0, size 0x2
    u_short DmaId; // offset 0x2, size 0x2
    void* Addr; // offset 0x4, size 0x4
    u_int pad1; // offset 0x8, size 0x4
    u_short VifQwc; // offset 0xC, size 0x2
    u_char pad2; // offset 0xE, size 0x1
    u_char VifDirect; // offset 0xF, size 0x1
} SPACK_ENV_DATA;

// total size: 0x10
struct SPACK_STATIC_DATA {
    // Members
    u_short GifNLOOP; // offset 0x0, size 0x2
    u_short DmaQwc; // offset 0x2, size 0x2
    u_int PRE_PRIM_FLG_NREG; // offset 0x4, size 0x4
    u_long REGS; // offset 0x8, size 0x4
};

// total size: 0x60
typedef struct SPACK_DATA {
    // Members
    struct SPACK_OT_DATA** ot_top; // offset 0x0, size 0x4
    struct SPACK_OT_DATA** ot_last; // offset 0x4, size 0x4
    u_int ot_size; // offset 0x8, size 0x4
    u_int ot_width; // offset 0xC, size 0x4
    u_int w_ofs; // offset 0x10, size 0x4
    u_int w_mini; // offset 0x14, size 0x4
    u_int w_max; // offset 0x18, size 0x4
    u_int envid; // offset 0x1C, size 0x4
    struct SPACK_OT_DATA* dma_top; // offset 0x20, size 0x4
    struct SPACK_OT_DATA* dmabuf_pos; // offset 0x24, size 0x4
    struct SPACK_ENV_DATA* env_top; // offset 0x28, size 0x4
    u_long* pk_last; // offset 0x2C, size 0x4
    u_long* pos; // offset 0x30, size 0x4
    short* ot_max; // offset 0x34, size 0x4
    u_long128* packet; // offset 0x38, size 0x4
    struct SPACK_STATIC_DATA* ps_top; // offset 0x3C, size 0x4
    u_long* pgiftag; // offset 0x40, size 0x4
    u_long giftag_b; // offset 0x48, size 0x4
    u_int flag; // offset 0x50, size 0x4
    void* kick_top; // offset 0x54, size 0x4
    void* old_lastpos; // offset 0x58, size 0x4
} SPACK_DATA;

SPACK_DATA* spkInit(void);

#endif // SPACK_H
