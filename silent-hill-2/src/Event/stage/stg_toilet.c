#include "sh2_common.h"

#include "Event/event.h"

#include "GFW/sh2_GsAllEnv.h"
#include "GFW/sh2gfw_2d_filters.h"

#include "SH2_common/sh2dt.h"

#include "view/camera_dat.h"

#include "data/daily.thu/data_movie.h"
#include "data/daily.thu/data_demo_first_toilet.h"

// data

static float stg_toilet_wvp[4] = { 0.0f, 0.0f, 450.0f, 1.0f };

// bss

static union Q_WORDDATA stg_toilet_qwd_01F02890[32];

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_EvProgPrologueInToilet);

/* static */ void stg_toilet_EvStageInit(void) {
    return;
}

/* static */ int stg_toilet_EvBgmControl(void) {
    if (GET_GAME_FLAG(GAME_FLAG_36)) {
        return 1;
    }
    return !GET_GAME_FLAG(GAME_FLAG_33) ? 4 : 0;
}

int stg_toilet_Kari_hisyakai(int KeyAlpha) {

    int ivt[4]; // r29+0x30
    float wsm[4][4]; // r29+0x40
    int id; // r2

    sceVu0CopyMatrix(wsm, cam0.view_screen);
    sceVu0RotTransPers(ivt, wsm, stg_toilet_wvp, 1);

    stg_toilet_qwd_01F02890[0].ui32[0] = 0x10000007;
    stg_toilet_qwd_01F02890[0].ui32[1] = 0;
    stg_toilet_qwd_01F02890[0].ui32[2] = 0;
    stg_toilet_qwd_01F02890[0].ui32[3] = 0x50000007;

    stg_toilet_qwd_01F02890[1].ui32[3] = 0;
    stg_toilet_qwd_01F02890[1].ui32[2] = 0xE;
    stg_toilet_qwd_01F02890[1].ui32[1] = 0x10000000;
    stg_toilet_qwd_01F02890[1].ui32[0] = 0x8006;

    stg_toilet_qwd_01F02890[2] = shGs_AllEnv.Now_DrawEnv.frame_normal;

    stg_toilet_qwd_01F02890[3].ul64[1] = 0x47;
    stg_toilet_qwd_01F02890[3].ul64[0] = 0x00058002;

    stg_toilet_qwd_01F02890[4].ul64[1] = 0x4E;
    stg_toilet_qwd_01F02890[4].ul64[0] = 0x3A0001c0;

    stg_toilet_qwd_01F02890[5].ul64[0] = 0x60;
    stg_toilet_qwd_01F02890[5].ul64[1] = 0x14;

    stg_toilet_qwd_01F02890[6].ul64[1] = 8;
    stg_toilet_qwd_01F02890[6].ul64[0] = 5;

    stg_toilet_qwd_01F02890[7].ul64[1] = 0x42;
    stg_toilet_qwd_01F02890[7].ul64[0] = 0xFF00000068ULL;

    stg_toilet_qwd_01F02890[8].ui32[0] = 0x10000005;
    stg_toilet_qwd_01F02890[8].ui32[1] = 0;
    stg_toilet_qwd_01F02890[8].ui32[2] = 0;
    stg_toilet_qwd_01F02890[8].ui32[3] = 0x50000005;

    stg_toilet_qwd_01F02890[9].ul64[0] = 0x4023400000008001ULL;
    stg_toilet_qwd_01F02890[9].ul64[1] = 0x5151;

    stg_toilet_qwd_01F02890[10].ui32[0] = 0;
    stg_toilet_qwd_01F02890[10].ui32[1] = 0;
    stg_toilet_qwd_01F02890[10].ui32[2] = 0;
    stg_toilet_qwd_01F02890[10].ui32[3] = KeyAlpha;

    stg_toilet_qwd_01F02890[11].ul64[0] = 0x0000700000007000ULL;
    stg_toilet_qwd_01F02890[11].ul64[1] = ivt[2];

    stg_toilet_qwd_01F02890[12].ui32[0] = 0;
    stg_toilet_qwd_01F02890[12].ui32[1] = 0;
    stg_toilet_qwd_01F02890[12].ui32[2] = 0;
    stg_toilet_qwd_01F02890[12].ui32[3] = KeyAlpha;

    stg_toilet_qwd_01F02890[13].ul64[0] = 0x0000900000009000ULL;
    stg_toilet_qwd_01F02890[13].ul64[1] = ivt[2];

    stg_toilet_qwd_01F02890[14].ul128 = 0;
    stg_toilet_qwd_01F02890[14].ui32[0] = 0x70000000;

    d1cSend(stg_toilet_qwd_01F02890);
    id = ivt[2] >> 4;
    return id;
}

/* static */ float stg_toilet_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_toilet", stg_toilet_Toilet_Dof_Filter); // https://decomp.me/scratch/dHOre
