#include "sh2_common.h"

#include "gs.h"

#include "sce/libgraph.h"

#include "Fog/spack.h"

#include "taskman/shtskman.h"

#include "Enemy/en_common.h"
#include "Enemy/en_effect.h"

#define EN_POISON_FOG_EFCT_KIND 30
#define EN_SPRAY_EFCT_KIND      31
#define EN_BUG_2D_EFCT_KIND     32

#define POISON_FOG_RANGE_MIN -100.0f
#define POISON_FOG_RANGE_MAX 10.0f

static u_int enMultColor(u_int color, int rate);

extern struct EnEfctEnvData EnEfctEnvData; // size: 0x190, address: 0x5524C0
static int en_efct_kind_list[4] = {
    EN_POISON_FOG_EFCT_KIND,
    EN_SPRAY_EFCT_KIND,
    EN_BUG_2D_EFCT_KIND,
}; // size: 0x10, address: 0x2AA250

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
        pt->pfog.size = shVector3Length(pt->pfog.vec);
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

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctMovePoisonFog);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctDrawPoisonFog);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetPoisonTex);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctDrawInsect);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetInsectTex);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetSpray);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctMoveSpray);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctDrawSpray);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetSprayTex);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetTYU2D);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctMoveTYU2D);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctDrawTYU2D);

INCLUDE_ASM("asm/nonmatchings/Enemy/en_effect", enEfctSetTYU2DTex);
