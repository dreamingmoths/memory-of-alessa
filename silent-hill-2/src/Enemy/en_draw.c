#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "gs.h"
#include "vec.h"
#include "sce/libgraph.h"
#include "Fog/spack.h"

#define EN_DRAW_ORIGIN_X ((int) X_COORD(-1568))
#define EN_DRAW_ORIGIN_Y ((int) Y_COORD(-1948))
#define EN_ASPECT_RATIO  (4.0f / 3.0f)
#define enDrawX(value)   (EN_DRAW_ORIGIN_X + vu0_ftoi((value) / view_rate + 2048.0f))
#define enDrawY(value)   (EN_DRAW_ORIGIN_Y + vu0_ftoi((value) / view_rate * EN_ASPECT_RATIO + 2048.0f))

extern float view_rate;

static inline u_long128 shFastPackXyz(sceVu0IVECTOR vector) {
    u_long128 xyz = *(u_long128*) vector;
    asm("\
        pexch        t7,  %0;\
        pextuw       %0,  zero, %0;\
        pextlw       %0,  %0, t7"
    : "+r"(xyz) :: "t7");
    return xyz;
}


INCLUDE_ASM("asm/nonmatchings/Enemy/en_draw", enDrawRadar);

#line 1201
static void enDrawWall(sceVu0FVECTOR wall_pos1, sceVu0FVECTOR wall_pos2, sceVu0FVECTOR ppos, float prot) {
    sceVu0FVECTOR vec, vec2;
    sceVu0IVECTOR scr;
    u_long xyz;
    if (wall_pos1[0] == wall_pos2[0] && wall_pos1[2] == wall_pos2[2]) return;
    shVectorZero(scr);
    shSubVector(vec, wall_pos1, ppos);
    shSubVector(vec2, wall_pos2, ppos);
    shRotVectorY(vec, vec, prot);
    scr[2] = 0xfffffe;
    scr[0] = enDrawX(vec[2]);
    scr[1] = enDrawY(vec[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz = shFastPackXyz(scr);
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_LINE, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    if ((vec[1] > 250.0f && vec2[1] > 250.0f) || (vec[1] < -250.0f && vec2[1] < -250.0f)) {
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 192, 64, 32, 0);            
    } else {
        (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 80, 255, 64, 0);
    }
    (*spack.pos++) = xyz;
    (*spack.pos++) = shFastPackXyz(scr);
}

#line 1233
static void enDrawColumn(sceVu0FVECTOR column_pos, float size, sceVu0FVECTOR ppos, float prot) {
    sceVu0FVECTOR vec, vec2;
    sceVu0IVECTOR scr;
    u_long xyz1, xyz2, xyz3;
    shVectorZero(scr);
    scr[2] = 0xfffffe;
    shSubVector(vec, column_pos, ppos);
    shVectorCopy(vec2, vec);
    vec2[0] -= size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz1 = shFastPackXyz(scr);
    shVectorCopy(vec2, vec);
    vec2[2] += size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz2 = shFastPackXyz(scr);
    shVectorCopy(vec2, vec);
    vec2[2] -= size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    xyz3 = shFastPackXyz(scr);
    shVectorCopy(vec2, vec);
    vec2[0] += size;
    shRotVectorY(vec2, vec2, prot);
    scr[0] = enDrawX(vec2[2]);
    scr[1] = enDrawY(vec2[0]);
    if (scr[0] < 0 || scr[1] < 0 || scr[0] > 65535 || scr[1] > 65535) return;
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(0, 80, 255, 64, 0);
    (*spack.pos++) = xyz1;
    (*spack.pos++) = xyz2;
    (*spack.pos++) = xyz3;
    (*spack.pos++) = shFastPackXyz(scr);
}

#line 1278
static void enDrawTriangle(sceVu0FVECTOR pos, float rot, u_int color, float size) {
    float x, y, dx, dy;
    x = pos[2];
    y = pos[0];
    dx = shCosF(rot) * size;
    dy = shSinF(rot) * size;
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 5), 
                   GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ3, SCE_GS_XYZ2), -4, 4);
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = color;
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx),
                                     enDrawY(y + dy), 
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x - dx + dy),
                                     enDrawY(y - dy - dx),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx - dy),
                                     enDrawY(y - dy + dx),
                                     0xffffff);
    spkCloseGiftag();
}


/*

let dx = cos θ, dy = sin θ

┌          ┐ ┌   ┐    ┌                  ┐
│  dx  dy  │ │ x │    │  dx * x + dy * y │
│          │ │   │ =  │                  │
│ -dy  dx  │ │ y │    │ -dy * x + dx * y │
└          ┘ └   ┘    └                  ┘

*/
#line 1303
static void enDrawBox(sceVu0FVECTOR pos, float rot, u_int color, float size1, float size2) {
    float x, y, dx, dy;
    x = pos[2];
    y = pos[0];
    dx = shCosF(rot);
    dy = shSinF(rot);
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 6), 
                   GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_XYZ3, SCE_GS_XYZ2, SCE_GS_XYZ2), 
                   -4, 4);
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 0, 0, SCE_GS_TRUE /* alpha blend */, 0, 0, 0, 0);
    (*spack.pos++) = color;
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx * size2 + dy * size1),
                                     enDrawY(y + dy * size2 - dx * size1), 
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ3(enDrawX(x + dx * size2 - dy * size1),
                                     enDrawY(y + dy * size2 + dx * size1),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx * size2 + dy * size1),
                                     enDrawY(y - dy * size2 - dx * size1),
                                     0xffffff);
    (*spack.pos++) = SCE_GS_SET_XYZ2(enDrawX(x - dx * size2 - dy * size1),
                                     enDrawY(y - dy * size2 + dx * size1),
                                     0xffffff);
    spkCloseGiftag();
}
