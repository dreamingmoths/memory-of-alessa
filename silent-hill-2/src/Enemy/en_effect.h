#ifndef EN_EFFECT_H
#define EN_EFFECT_H

#include "sh2_common.h"
#include "taskman/shtskman.h"

#define EN_POISON_FOG_EFCT_KIND 30
#define EN_SPRAY_EFCT_KIND      31
#define EN_BUG_2D_EFCT_KIND     32

#define POISON_FOG_RANGE_MIN    -100.0f
#define POISON_FOG_RANGE_MAX     10.0f
#define SPRAY_RANGE_MIN         -50.0f
#define SPRAY_RANGE_MAX          1.0f

typedef struct EnEFCT_PFOG_DATA {
    // total size: 0x40
    sceVu0FVECTOR pos; // offset 0x0, size 0x10
    sceVu0FVECTOR vec; // offset 0x10, size 0x10
    u_int color; // offset 0x20, size 0x4
    int alpha; // offset 0x24, size 0x4
    float scattar; // offset 0x28, size 0x4
    float size; // offset 0x2C, size 0x4
    float s; // offset 0x30, size 0x4
    float t; // offset 0x34, size 0x4
} EnEFCT_PFOG_DATA;

typedef struct EnEFCT_SPRAY_DATA {
    // total size: 0x50
    sceVu0FVECTOR pos; // offset 0x0, size 0x10
    sceVu0FVECTOR vec; // offset 0x10, size 0x10
    u_int color; // offset 0x20, size 0x4
    int timer; // offset 0x24, size 0x4
    int timer1; // offset 0x28, size 0x4
    int timer2; // offset 0x2C, size 0x4
    int alpha; // offset 0x30, size 0x4
    float scattar; // offset 0x34, size 0x4
    float size; // offset 0x38, size 0x4
    float s; // offset 0x3C, size 0x4
    float t; // offset 0x40, size 0x4
} EnEFCT_SPRAY_DATA;

typedef struct EnEFCT_TY2DU_DATA {
    // total size: 0x20
    sceVu0FVECTOR pos; // offset 0x0, size 0x10
    sceVu0FVECTOR rot; // offset 0x10, size 0x10
} EnEFCT_TY2DU_DATA;

typedef struct EnEFCT_TASK {
    // total size: 0x70
    struct _shTskEXECUTE exe; // offset 0x0, size 0x14
    int step; // offset 0x14, size 0x4
    int count; // offset 0x18, size 0x4
    union { // inferred
        struct EnEFCT_PFOG_DATA pfog; // offset 0x20, size 0x40
        struct EnEFCT_SPRAY_DATA spray; // offset 0x20, size 0x50
        struct EnEFCT_TY2DU_DATA tyu2d; // offset 0x20, size 0x20
    };
} EnEFCT_TASK;

struct EnEfctEnvData {
    // total size: 0x190
    u_long128 Poison[6]; // offset 0x0, size 0x60
    u_long128 Insect[6]; // offset 0x60, size 0x60
    u_long128 Spray[6]; // offset 0xC0, size 0x60
    u_long128 Tyu2D[6]; // offset 0x120, size 0x60
    s_char SetPoisonTex; // offset 0x180, size 0x1
    s_char SetInsectTex; // offset 0x181, size 0x1
    s_char SetInsectTex_bak; // offset 0x182, size 0x1
    s_char SetSprayTex; // offset 0x183, size 0x1
    s_char SetTYU2DTex; // offset 0x184, size 0x1
};

void enEfctInit(void);

void enEfctTexInit(void);

void enEfctClear(void);

void enEfctDraw(void);

void enEfctSetPoisonFog(sceVu0FVECTOR pos, sceVu0FVECTOR vec);

void enEfctMovePoisonFog(EnEFCT_TASK* pt);

void enEfctDrawPoisonFog(EnEFCT_TASK* pt);

void enEfctSetPoisonTex(void);

void enEfctDrawInsect(void* p);

void enEfctSetInsectTex(void);

void enEfctSetSpray(sceVu0FVECTOR pos, sceVu0FVECTOR vec, u_int color, int timer);

void enEfctMoveSpray(EnEFCT_TASK* pt);

void enEfctDrawSpray(EnEFCT_TASK* pt);

void enEfctSetSprayTex(void);

void enEfctSetTYU2D(sceVu0FVECTOR pos, sceVu0FVECTOR rot);

void enEfctMoveTYU2D(EnEFCT_TASK* pt);

void enEfctDrawTYU2D(EnEFCT_TASK* pt);

void enEfctSetTYU2DTex(void);

#endif // EN_EFFECT_H
