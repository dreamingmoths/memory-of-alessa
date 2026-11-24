#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "gs.h"
#include "vec.h"
#include "candles.h"

#include "sce/libgraph.h"

#include "Fog/spack.h"

#include "GFW/sh2_DrawEnvData.h"

#include "taskman/shtskman.h"

#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_wrapper.h"

#include "Enemy/en_common.h"
#include "Enemy/en_effect.h"

#include "view/vb_main.h"

#define EN_POISON_FOG_EFCT_KIND 30
#define EN_SPRAY_EFCT_KIND      31
#define EN_BUG_2D_EFCT_KIND     32

#define POISON_FOG_RANGE_MIN    -100.0f
#define POISON_FOG_RANGE_MAX     10.0f
#define SPRAY_RANGE_MIN         -50.0f
#define SPRAY_RANGE_MAX          1.0f

static u_int enMultColor(u_int color, int rate);

struct EnEfctEnvData EnEfctEnvData; // size: 0x190, address: 0x5524C0
static int en_efct_kind_list[4] = {
    EN_POISON_FOG_EFCT_KIND,
    EN_SPRAY_EFCT_KIND,
    EN_BUG_2D_EFCT_KIND,
    -1
}; // size: 0x10, address: 0x2AA250

/**
 * sin(rad(x)) for x in range(0, 360, 22.5)
 */
static float sintable[16] = {
    /* sinf(TO_RAD(0.0000)) */ +0.0f,
    /* sinf(TO_RAD(22.500)) */ +0.3826834f,
    /* sinf(TO_RAD(45.000)) */ +0.7071068f,
    /* sinf(TO_RAD(67.500)) */ +0.9238795f,
    /* sinf(TO_RAD(90.000)) */ +1.0f,
    /* sinf(TO_RAD(112.50)) */ +0.9238795f,
    /* sinf(TO_RAD(135.00)) */ +0.7071068f,
    /* sinf(TO_RAD(157.50)) */ +0.3826834f,
    /* sinf(TO_RAD(180.00)) */ -0.0f,
    /* sinf(TO_RAD(202.50)) */ -0.3826834f,
    /* sinf(TO_RAD(225.00)) */ -0.7071068f,
    /* sinf(TO_RAD(247.50)) */ -0.9238795f,
    /* sinf(TO_RAD(270.00)) */ -1.0f,
    /* sinf(TO_RAD(292.50)) */ -0.9238795f,
    /* sinf(TO_RAD(315.00)) */ -0.7071068f,
    /* sinf(TO_RAD(337.50)) */ -0.3826834f,
};

#line 55
static u_int enMultColor(u_int color, int rate) {
    u_int r = ((color >> 0x00) & 0xFF) * rate / 128;
    u_int g = ((color >> 0x08) & 0xFF) * rate / 128;
    u_int b = ((color >> 0x10) & 0xFF) * rate / 128;
    u_int a = ((color >> 0x18) & 0xFF) * rate / 128;
    return COLOR_RGBA(r, g, b, a);
}

#line 66
void enEfctInit(void) {
    SyncDCache((void*) EnEfctEnvData.Poison, (void*) ((s_char*) &EnEfctEnvData + sizeof(EnEfctEnvData)));
    
    InvalidDCache((void*) EnEfctEnvData.Poison, (void*) ((s_char*) &EnEfctEnvData + sizeof(EnEfctEnvData)));
    
    
    spkStartPacketS(EnEfctEnvData.Poison);
    spkOpenDGiftagS(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    spkAddressData(0, SCE_GS_TEX0_1);
    spkAddressData(0, SCE_GS_CLAMP_1);
    spkAddressData(SCE_GS_SET_ALPHA(0, 1, 0, 1, 0), SCE_GS_ALPHA_1);
    spkAddressData(SCE_GS_SET_TEX1(1, 0, 1, 1, 0, 0, -1), SCE_GS_TEX1_1);
    spkAddressData(SCE_GS_SET_ZBUF(917504 / 2048, SCE_GS_PSMZ16S, SCE_GS_TRUE), SCE_GS_ZBUF_1);
    spkCloseGiftagS();
    spkEndPacketS();
    spkSetEnvPacket(EnEfctEnvData.Poison, 2);
    spkStartPacketS(EnEfctEnvData.Insect);
    
    spkOpenDGiftagS(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    spkAddressData(0, SCE_GS_TEX0_1);
    spkAddressData(0, SCE_GS_CLAMP_1);
    spkAddressData(SCE_GS_SET_ALPHA(0, 1, 0, 1, 0), SCE_GS_ALPHA_1);
    spkAddressData(SCE_GS_SET_TEX1(1, 0, 1, 1, 0, 0, -1), SCE_GS_TEX1_1);
    spkAddressData(SCE_GS_SET_ZBUF(917504 / 2048, SCE_GS_PSMZ16S, SCE_GS_TRUE), SCE_GS_ZBUF_1);
    spkCloseGiftagS();
    spkEndPacketS();
    spkSetEnvPacket(EnEfctEnvData.Insect, 6);
    spkStartPacketS(EnEfctEnvData.Spray);

    spkOpenDGiftagS(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    spkAddressData(0, SCE_GS_TEX0_1);
    spkAddressData(0, SCE_GS_CLAMP_1);
    spkAddressData(SCE_GS_SET_ALPHA(0, 1, 0, 1, 0), SCE_GS_ALPHA_1);
    spkAddressData(SCE_GS_SET_TEX1(1, 0, 1, 1, 0, 0, -1), SCE_GS_TEX1_1);
    spkAddressData(SCE_GS_SET_ZBUF(917504 / 2048, SCE_GS_PSMZ16S, SCE_GS_TRUE), SCE_GS_ZBUF_1);
    spkCloseGiftagS();
    spkEndPacketS();
    spkSetEnvPacket(EnEfctEnvData.Spray, 7);
    spkStartPacketS(EnEfctEnvData.Tyu2D);

    spkOpenDGiftagS(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD);
    spkAddressData(0, SCE_GS_TEX0_1);
    spkAddressData(0, SCE_GS_CLAMP_1);
    spkAddressData(SCE_GS_SET_ALPHA(0, 1, 0, 1, 0), SCE_GS_ALPHA_1);
    spkAddressData(SCE_GS_SET_TEX1(1, 0, 1, 1, 0, 0, -1), SCE_GS_TEX1_1);
    spkAddressData(SCE_GS_SET_ZBUF(917504 / 2048, SCE_GS_PSMZ16S, SCE_GS_TRUE), SCE_GS_ZBUF_1);
    spkCloseGiftagS();
    spkEndPacketS();
    spkSetEnvPacket(EnEfctEnvData.Tyu2D, 8);
}

#line 133
void enEfctTexInit(void) { /* empty */ }

#line 137
void enEfctClear(void) {
    int kind, n;

    n = 0;
    while ((kind = en_efct_kind_list[n++]) != -1) {
        shTskTASK* pt = shTSKSearchTaskWithAtr(kind, (shTskTASK*) shTskTaskListTop[EN_EFFECT_TASK_ID]->exe.next, EN_EFFECT_TASK_ID);
        while (pt) {
            shTskTASK* pnext = shTSKSearchTaskWithAtr(kind, (shTskTASK*) pt->exe.next, EN_EFFECT_TASK_ID);
            shTSKCutTask(pt);
            pt = pnext;
        }       
    }
}

#line 153
void enEfctDraw(void) {
    int kind, n;

    n = 0;
    EnEfctEnvData.SetPoisonTex = 0;
    EnEfctEnvData.SetSprayTex = 0;
    EnEfctEnvData.SetTYU2DTex = 0;
    while ((kind = en_efct_kind_list[n++]) != -1) {
        shTskTASK* pt = shTSKSearchTaskWithAtr(kind, (shTskTASK*) shTskTaskListTop[EN_EFFECT_TASK_ID]->exe.next, EN_EFFECT_TASK_ID);
        while (pt) {
            switch (kind) {                      /* irregular */
                case EN_POISON_FOG_EFCT_KIND:
                    enEfctDrawPoisonFog((EnEFCT_TASK*) pt);
                    break;
                case EN_SPRAY_EFCT_KIND:
                    enEfctDrawSpray((EnEFCT_TASK*) pt);
                    break;
                case EN_BUG_2D_EFCT_KIND:
                    enEfctDrawTYU2D((EnEFCT_TASK*) pt);
                    break;
            }
            pt = shTSKSearchTaskWithAtr(kind, (shTskTASK*) pt->exe.next, EN_EFFECT_TASK_ID);
        }
    }
    n = 0;
    if (EnEfctEnvData.SetPoisonTex) {
        enEfctSetPoisonTex();
        n = 1;
    }
    if (EnEfctEnvData.SetInsectTex) {
        enEfctSetInsectTex();
        n = 1;
    }
    if (EnEfctEnvData.SetSprayTex) {
        enEfctSetSprayTex();
        n = 1;
    }
    if (EnEfctEnvData.SetTYU2DTex) {
        enEfctSetTYU2DTex();
        n = 1;
    }
    if (n) {
        //  waits for completion of drawing, then disables the texture data read to the texture page buffer.
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, -MAX_INT - 1, 0);
        spkAddressData(0, SCE_GS_TEXFLUSH);
        spkCloseGiftag();
    }
    
    EnEfctEnvData.SetInsectTex_bak = EnEfctEnvData.SetInsectTex;
    EnEfctEnvData.SetInsectTex = 0;
}

#line 209
void enEfctSetPoisonFog(sceVu0FVECTOR pos, sceVu0FVECTOR vec) {
    EnEFCT_TASK* pt; // r16
    pt = shTSKSetTask(enEfctMovePoisonFog, EN_EFFECT_TASK_ID);
    
    if (pt != NULL) {
        pt->exe.atr = EN_POISON_FOG_EFCT_KIND;
        shVectorCopyVu0(pt->pfog.pos, pos);
        pt->step = 0;
        pt->count = 0;
        pt->pfog.alpha = 0;
        shVectorCopy(pt->pfog.vec, vec);
        pt->pfog.vec[0] += shSway1f(POISON_FOG_RANGE_MIN, POISON_FOG_RANGE_MAX);
        pt->pfog.vec[1] += shSway1f(POISON_FOG_RANGE_MIN, POISON_FOG_RANGE_MAX);
        pt->pfog.vec[2] += shSway1f(POISON_FOG_RANGE_MIN, POISON_FOG_RANGE_MAX);
        pt->pfog.size = shVectorLengthXyz(pt->pfog.vec);
        shNormalizeVector(pt->pfog.vec, pt->pfog.vec);
        pt->pfog.s = shRandF();
        pt->pfog.t = shRandF();
        switch (enGetWorldCondition()) {
            case WORLD_NIGHT_LIGHT_OFF:
                if (enLocalWork.This && enCheckDarkOrBright(enLocalWork.This->scp)) {
                    pt->pfog.color = COLOR_RGB(48, 48, 48);
                    return;
                }
                pt->pfog.color = COLOR_RGB(24, 24, 24);
                return;
            default:
                pt->pfog.color = COLOR_RGB(128, 128, 128);
        }
    }
}

#line 247
void enEfctMovePoisonFog(EnEFCT_TASK* pt) {
    sceVu0FVECTOR vec; // r29+0x50
    float d; // r20
    switch (pt->step) {
        case 0:
            d = (float) pt->count / (float) enCalcTimer(6);
            shScaleVector(vec, pt->pfog.vec, 0.2f * pt->pfog.size / enCalcTimer(6));
            shAddVectorXyz(pt->pfog.pos, vec, pt->pfog.pos);
            pt->pfog.alpha = 32.0f * d;
            pt->pfog.scattar = 0.5f * d;
            if ((pt->count += shGetDF()) >= enCalcTimer(6)) {
                pt->step++;
            }
            break;
        case 1:
            d = pt->count - enCalcTimer(6); d /= enCalcTimer(6);
            shScaleVector(vec, pt->pfog.vec, 0.25f * pt->pfog.size / enCalcTimer(6));
            vec[1] += 100.0f * shGetDT();
            shAddVectorXyz(pt->pfog.pos, vec, pt->pfog.pos);
            pt->pfog.alpha = 32;
            pt->pfog.scattar = 0.5f + 0.5f * d;
            if ((pt->count += shGetDF()) >= enCalcTimer(6) + enCalcTimer(6)) {
                pt->step++;
            }
            break;
        case 2:
            d = pt->count - enCalcTimer(6) - enCalcTimer(6); d /= enCalcTimer(10);
            shScaleVector(vec, pt->pfog.vec, 0.3f * pt->pfog.size / enCalcTimer(10));
            vec[1] += 100.0f * shGetDT();
            shAddVectorXyz(pt->pfog.pos, vec, pt->pfog.pos);
            pt->pfog.alpha = 32.0f * (1.0f - d);
            pt->pfog.scattar = 1.0f + (0.2f * d);
            if ((pt->count += shGetDF()) >= enCalcTimer(6) + 
                                            enCalcTimer(6) + enCalcTimer(10)) {
                shTSKDelTask(pt);
            }
            break;
    }
}

#line 297
void enEfctDrawPoisonFog(EnEFCT_TASK* pt) {
    sceVu0FVECTOR v0; // r29+0x30
    sceVu0FVECTOR vec; // r29+0x40
    float q, s, dx, dy, ds, dt; // r29+0x50, r29+0x50, r20, r21, r29+0x50, r22, r2
    int i;
    q = shTransformVectorPerspective(v0, VbWvsMatrix.wsm, pt->pfog.pos); // r29+0x50
    dx = (0.25f * pt->pfog.size * pt->pfog.scattar * q) * VbScreenInfo.scr_z;
    
    dy = SCREEN_ASPECT_RATIO * dx;
    dt = 0.25f;
    
    if (v0[0] + dx < 1792.0f ||  v0[0] - dx > 2304.0f || 
        v0[1] + dy < 1792.0f ||  v0[1] - dy > 2304.0f || 
        v0[2] < 0.0f         ||
        v0[3] < 128.0f       || 
        v0[3] > 32767.0f) {
        return;
    }
    
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRIFAN, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, shVu0FloatToInt(v0[3]), 2U);
    
    
    
    spkAddressData(SH_GIF_SET_AQ(pt->pfog.color, pt->pfog.alpha, FLOAT_ONE), SCE_GS_RGBAQ);
    
    spkAddressData(shFastSetSt(pt->pfog.s, pt->pfog.t), SCE_GS_ST);
    spkAddressData(shFastPackXyz(shFloatToIntXyz3(v0)), SCE_GS_XYZ3);
    shVectorCopy(vec, v0);
    spkAddressData(SH_GIF_SET_AQ(pt->pfog.color, 0, FLOAT_ONE), SCE_GS_RGBAQ);
    for (i = 0; i < 17; i++) {
        vec[0] = v0[0] + (dx * sintable[(i + 4) & 0xF]);
        vec[1] = v0[1] + (dy * sintable[i & 0xF]);
        spkAddressData(shFastSetSt(pt->pfog.s + sintable[(i + 4) & 0xF] * dt, pt->pfog.t + sintable[i & 0xF] * dt), SCE_GS_ST);
        
        spkAddressData(shFastPackXyz(shFloatToIntXyz3(vec)), SCE_GS_XYZ2);
    }
    spkCloseGiftag();
    EnEfctEnvData.SetPoisonTex = TRUE;
}

#line 339
void enEfctSetPoisonTex(void) {
    
    
    
    
    
    #line 346
    *(u_long*) &EnEfctEnvData.Poison[1] = HH_Effect_Object_Texture_GS_Register_Tex0_Get(2, 0);

    #line 349
}

#line 359
void enEfctDrawInsect(void* p) {
    EnLOCAL_DATA* dp = (EnLOCAL_DATA*) p;
    sceVu0FVECTOR v0, v1;
    sceVu0FMATRIX m0;
    float q, s, dx, dy;
    u_short u, v;
    
    shVectorCopyVu0(v0, &dp->scp->pos);
    q = shTransformVectorPerspective(v0, VbWvsMatrix.wsm, v0);
    dx = VbScreenInfo.scr_z * (dp->size * q);
    
    dy = (32.0f * (SCREEN_ASPECT_RATIO * dx)) / 32.0f;
    if (v0[0] + dx < 1792.0f ||  v0[0] - dx > 2304.0f || 
        v0[1] + dy < 1792.0f ||  v0[1] - dy > 2304.0f || 
        v0[2] < 0.0f         ||
        v0[3] < 128.0f       || 
        v0[3] > 32767.0f) {
        return;
    }
    u = (dp->anim % 2) << 5;
    v = (dp->anim / 2) << 5;
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 10), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_RGBAQ, SCE_GS_UV, SCE_GS_XYZ3, SCE_GS_UV, SCE_GS_XYZ2, SCE_GS_UV, SCE_GS_XYZ3, SCE_GS_UV, SCE_GS_XYZ2), shVu0FloatToInt(v0[3]), 6);
    
    (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 1, 0, 1, 0, 0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(128, 128, 128, 128, FLOAT_ONE);
    (*spack.pos++) = SH_GIF_SET_UV(u, v);
    shVectorCopy(v1, v0);
    v1[0] -= dx;
    v1[1] -= dy;
    (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(v1));
    (*spack.pos++) = SH_GIF_SET_UV(u + 32, v + 32);
    v1[0] += dx;
    v1[1] += dy;
    (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(v1));
    shVectorCopyVu0(v0, &dp->scp->pos);
    shUnitMatrix(m0);
    shRotMatrixZ(m0, m0, dp->ins.view_rot[2]);
    shRotMatrixY(m0, m0, dp->ins.view_rot[1]);
    shRotMatrixX(m0, m0, dp->ins.view_rot[0]);
    v1[0] = v1[1] = v1[2] = dp->ins.twin_dist;
    sHVectorTransform3d(v1, m0);
    shAddVectorXyz(v0, v1, v0);
    q = shTransformVectorPerspective(v0, VbWvsMatrix.wsm, v0);
    dx = VbScreenInfo.scr_z * (dp->size * q);
    dy = (32.0f * (SCREEN_ASPECT_RATIO * dx)) / 32.0f;
    (*spack.pos++) = SH_GIF_SET_UV(u, v);
    shVectorCopy(v1, v0);
    v1[0] -= dx;
    v1[1] -= dy;
    (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(v1));
    (*spack.pos++) = SH_GIF_SET_UV(u + 32, v + 32);
    v1[0] += dx;
    v1[1] += dy;
    (*spack.pos++) =  shFastPackXyz(shFloatToIntXyz3(v1));
    spkCloseGiftag();
    EnEfctEnvData.SetInsectTex = 1;
}

void enEfctSetInsectTex(void) {
    *(u_long*) &EnEfctEnvData.Insect[1] = HH_Effect_Object_Texture_GS_Register_Tex0_Get(18, 0);

}

#line 429
void enEfctSetSpray(sceVu0FVECTOR pos, sceVu0FVECTOR vec, u_int color, int timer) {
    EnEFCT_TASK* pt; // r16
    pt = shTSKSetTask(enEfctMoveSpray, EN_EFFECT_TASK_ID);
    
    if (pt != NULL) {
        pt->exe.atr = EN_SPRAY_EFCT_KIND;
        shVectorCopyVu0(pt->spray.pos, pos);
        pt->step = 0;
        pt->count = 0;
        pt->spray.alpha = 0;
        shVectorCopy(pt->spray.vec, vec);
        pt->spray.vec[0] += shSway1f(SPRAY_RANGE_MIN, SPRAY_RANGE_MAX);
        pt->spray.vec[1] += shSway1f(SPRAY_RANGE_MIN, SPRAY_RANGE_MAX);
        pt->spray.vec[2] += shSway1f(SPRAY_RANGE_MIN, SPRAY_RANGE_MAX);
        pt->spray.size = shVectorLengthXyz(pt->spray.vec);
        shNormalizeVector(pt->spray.vec, pt->spray.vec);
        pt->spray.s = shRandF();
        pt->spray.t = shRandF();
        pt->spray.timer  = (int) (0.6f * timer);
        pt->spray.timer1 = (int) (0.3f * timer);
        pt->spray.timer2 = (int) (0.3f * timer);
        switch (enGetWorldCondition()) {
            case WORLD_NIGHT_LIGHT_OFF:
                if (enCheckDarkOrBrightPlayer())
                    color = enMultColor(color, 48);
                else 
                    color = enMultColor(color, 24);
                break;
        }
        pt->spray.color = color;
    }
}

CANDLE(enEfctMoveSpray, CANDLE_TYPE_GPR, *);

#line 464
void enEfctMoveSpray(EnEFCT_TASK* pt) {
    sceVu0FVECTOR vec; // r29+0x30
    float d, rt; // r20
    switch (pt->step) {
        case 0:
            rt = (1.0f / shIntToFloat(pt->spray.timer1));
            d = rt * pt->count;
            shScaleVector(vec, pt->spray.vec, 0.3f * pt->spray.size * rt);
            shAddVectorXyz(pt->spray.pos, vec, pt->spray.pos);
            pt->spray.alpha = 32.0f * d;
            pt->spray.scattar = 0.2f * d;
            if ((pt->count += shGetDF()) >= pt->spray.timer1) {
                pt->step++;
            }
            break;
        case 1:
            rt = (1.0f / shIntToFloat(pt->spray.timer2));
            d = rt * (pt->count - pt->spray.timer1);
            shScaleVector(vec, pt->spray.vec, 0.3f * pt->spray.size * rt);
            vec[1] += 100.0f * shGetDT();
            shAddVectorXyz(pt->spray.pos, vec, pt->spray.pos);
            pt->spray.alpha = 32;
            pt->spray.scattar = 0.2f + 0.2f * d;
            if ((pt->count += shGetDF()) >= pt->spray.timer) {
                pt->step++;
            }
            break;
        case 2:
            rt = (1.0f / shIntToFloat(pt->spray.timer));
            d = rt * (pt->count - pt->spray.timer);
            shScaleVector(vec, pt->spray.vec, 0.5f * pt->spray.size * rt);
            vec[1] += 100.0f * shGetDT();
            shAddVectorXyz(pt->spray.pos, vec, pt->spray.pos);
            pt->spray.alpha = 32.0f * (1.0f - d);
            pt->spray.scattar = 0.4f + (0.4f * d);
            if ((pt->count += shGetDF()) < pt->spray.timer * 2)
                break;
            shTSKDelTask(pt);
            break;
    }
}


#line 509
void enEfctDrawSpray(EnEFCT_TASK* pt) {
    sceVu0FVECTOR v0, vec;
    float q, s, dx, dy, ds, dt;
    int i, r, g, b, a;
    
    q = shTransformVectorPerspective(v0, VbWvsMatrix.wsm, pt->spray.pos);
    dx = VbScreenInfo.scr_z * ((0.25f * pt->spray.size * pt->spray.scattar) * q);
    
    dy = SCREEN_ASPECT_RATIO * dx;
    dt = 0.125f;
    
    if (v0[0] + dx < 1792.0f ||  v0[0] - dx > 2304.0f || 
        v0[1] + dy < 1792.0f ||  v0[1] - dy > 2304.0f || 
        v0[2] < 0.0f         ||
        v0[3] < 128.0f       || 
        v0[3] > 32767.0f) {
        return;
    }
    
    r = shClamp((((pt->spray.color >> 0x00) & 0xFF)),                         0, 204);
    g = shClamp((((pt->spray.color >> 0x08) & 0xFF) * 144) / 128,             0, 226);
    b = shClamp((((pt->spray.color >> 0x10) & 0xFF) * 160) / 128,             0, 255);
    a = shClamp(pt->spray.alpha * (((pt->spray.color >> 0x18) & 0xFF)) / 128, 0, 255);
    spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRIFAN, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 1), SCE_GIF_PACKED_AD, shVu0FloatToInt(v0[3]), 7);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(r, g, b, a, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_RGBAQ;
    (*spack.pos++) = shFastSetSt(pt->spray.s, pt->spray.t);
    (*spack.pos++) = SCE_GS_ST;
    (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(v0));
    (*spack.pos++) = SCE_GS_XYZ3;
    shVectorCopy(vec, v0);
    (*spack.pos++) = SCE_GS_SET_RGBAQ(r, g, b, 0, FLOAT_ONE);
    (*spack.pos++) = SCE_GS_RGBAQ;
    for (i = 0; i < 17; i++) {
        vec[0] = v0[0] + (dx * sintable[(i + 4) & 0xF]);
        vec[1] = v0[1] + (dy * sintable[i & 0xF]);
        (*spack.pos++) = shFastSetSt(pt->spray.s + sintable[(i + 4) & 0xF] * dt, pt->spray.t + sintable[i & 0xF] * dt);
        (*spack.pos++) = SCE_GS_ST;
        (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(vec));
        (*spack.pos++) = SCE_GS_XYZ2;
    }
    spkCloseGiftag();
    EnEfctEnvData.SetSprayTex = TRUE;
}


#line 556
void enEfctSetSprayTex(void) {
    
    *(u_long*) &EnEfctEnvData.Spray[1] = HH_Effect_Object_Texture_GS_Register_Tex0_Get(2, 0);

}

#line 565
void enEfctSetTYU2D(sceVu0FVECTOR pos, sceVu0FVECTOR rot) {
    EnEFCT_TASK* pt;

    pt = shTSKSetTask(enEfctMoveTYU2D, EN_EFFECT_TASK_ID);
    if (pt != NULL) {
        pt->exe.atr = EN_BUG_2D_EFCT_KIND;
        shVectorCopyVu0(pt->tyu2d.pos, pos);
        pt->spray.pos[1] -= 10.0f;
        shVectorCopy(pt->tyu2d.rot, rot);
    }
}


void enEfctMoveTYU2D(EnEFCT_TASK* pt) {
    void* tmp = (void*) pt;
    /* empty */
    #line 581
}

#pragma fast_fptosi on
#line 588
void enEfctDrawTYU2D(EnEFCT_TASK* pt) {
    sceVu0FMATRIX pos; sceVu0FVECTOR vec, vec2;
    sceVu0FMATRIX mat, rot; sceVu0FVECTOR q;

    float w; // r29+0x190
    float* ppos = pt->tyu2d.pos; // r2
    int i;
    shUnitMatrix(rot);
    shVectorZero(vec);
    shRotMatrixZ(rot, rot, pt->tyu2d.rot[2]); shRotMatrixX(rot, rot, pt->tyu2d.rot[0]); shRotMatrixY(rot, rot, pt->tyu2d.rot[1]);
    vec[0] = -75.0f;
    vec[2] = 75.0f;
    shMatrixCopy(mat, VbWvsMatrix.wsm);
    w = 0;
    for (i = 0; i < 4; i++) {
        shVectorTransformTo(vec2, rot, vec);
        shAddVector(pos[i], ppos, vec2);
        pos[i][3] = 1.0f;
        q[i] = shTransformVectorPerspective(pos[i], mat, pos[i]);
        if (pos[i][0] < 0.0f || pos[i][0] >= 4096.0f || 
            pos[i][1] < 0.0f || pos[i][1] >= 4096.0f || pos[i][2] < 0.0f) {
            return;
        }
        if (pos[i][3] > w)  w = pos[i][3];
        vec[0] = -vec[0];
        if (i == 1) vec[2] = -vec[2];
    }
    {
        int r, g, b; /* r3, r2, r2, r2 */ 
        sceVu0FVECTOR amb, lpos, ldir, lcolor, para; float rate; // r29+0x190
        sceVu0ScaleVector(amb, Env_ctl.ambient, 2.0f);
        HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(lpos, ldir, lcolor, para);
        
        rate = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(lpos, ldir, pt->tyu2d.pos, para[0], para[2]);
        
        shScaleVector(lcolor, lcolor, rate);
        shAddVector(lcolor, lcolor, amb);
        shScaleVector(lcolor, lcolor, 64.0f);
        shClampVector(lcolor, lcolor, 0.0f, 255.0f);
        r = lcolor[0];
        g = lcolor[1];
        b = lcolor[2];
        
        spkOpenDGiftag(SCE_GIF_SET_TAG(0, 1, 0, 0, SCE_GIF_REGLIST, 13), GIF_REGLIST(SCE_GS_PRIM, SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZ3, SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZ2, SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZ2), shVu0FloatToInt(w), 8U);
        
        (*spack.pos++) = SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, SCE_GS_TRUE /* texture mapping */, 0, SCE_GS_TRUE /* alpha blending */, 0, 0, 0, 0);
        for (i = 0; i < 4; i++) {
            (*spack.pos++) = shFastSetSt(((i & 1) ? 1.0f : 0.0f) * q[i], ((i & 2) ? 1.0f : 0.0f) * q[i]);

            (*spack.pos++) = shFastSetRgbaq(r, g, b, 128, q[i]);
            (*spack.pos++) = shFastPackXyz(shFloatToIntXyz3(pos[i]));
        }
        spkCloseGiftag();
        EnEfctEnvData.SetTYU2DTex = TRUE;
    }
}

#line 646
void enEfctSetTYU2DTex(void) {
    *(u_long*) &EnEfctEnvData.Tyu2D[1] = HH_Effect_Object_Texture_GS_Register_Tex0_Get(19, 0);
}
