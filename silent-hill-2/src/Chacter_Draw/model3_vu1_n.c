#include "sh2_common.h"

#include "sce/libdma.h"
#include "sce/libvu0.h"
#include "sce/libvifpk.h"

#include "ee.h"
#include "gs.h"

#include "GFW/sh2gfw_Init_ModelDrawData.h"
#include "GFW/sh2_GsAllEnv.h"

#include "Chacter/character.h"

#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_n.h"
#include "Chacter_Draw/model3_sub_n.h"
#include "Chacter_Draw/model_common.h"
#include "Chacter_Draw/model3_vu1_n.h"
#include "Chacter_Draw/light_n.h"
#include "Chacter_Draw/model3_structs.h"
#include "Chacter_Draw/vifot/sh_kt_vif1pkbuf.h"

extern SprData spr_data_mem; // size: 0x200, address: 0x41ACC0
extern AllData all_data_db[2]; // size: 0x1000, address: 0x41AF00
extern SprData* spr_data;
extern u_int xitop_0x0041BF08;
extern u_int prev_xtop;
extern u_int muga;

#define xitop xitop_0x0041BF08

#define SHADING_TYPE_1            1
#define SHADING_TYPE_LAMBERTIAN_2 2
#define SHADING_TYPE_LAMBERTIAN_3 3
#define SHADING_TYPE_LAMBERTIAN_4 4

static void InitAllDataOne(AllData* p);
static void InitSprData(SprData* p);
static void InitData1(void);
static void MakeData1(void);
static void InitEnv1(sceVif1Packet* pk, int unused);
static void TiniEnv(sceVif1Packet* pk);
static void MakeVu1PartTransferPacket(Part* part, sceVif1Packet* pk);
static void MakeLambertShadingPacket_VU1(Part* part, sceVif1Packet* pk);
static void MakeNormalPacket(Part* part, sceVif1Packet* pk);
static void MakeEnvironPacket(Part* part, sceVif1Packet* pk);
static void MakeSpecularPacket(Part* part, sceVif1Packet* pk);
static void MakeBaseSpecularPacket(Part* part, sceVif1Packet* pk);
static void MakeOverPacket(Part* part, sceVif1Packet* pk);
static void MakeDrawPacket(Part* part, sceVif1Packet* pk);
static void DrawPart1(Part* part, sceVif1Packet* pk);
static void DrawParts1(sh_Model* model, ModelWork* work);

#ifdef NON_MATCHING
extern u_long128 model3_mpg1_view_load[];
extern void* __model3_mpg1_view_end;
void Model3LoadMpg1(void) {
    extern /* static */ int initialized_867; // @ 0x0041AC70
    extern /* static */ u_long128 packet_buffer_866[4]; // @ 0x0041AC80
    Q_WORDDATA* qwd; // r2

    if (initialized_867 == 0) {
        qwd = UNCACHED_POINTER(packet_buffer_866);
        qwd->ui32[0] = DMAcall;
        qwd->ui32[1] = (u_int) model3_mpg1_view_load;
        qwd->ui32[2] = SCE_VIF1_SET_FLUSH(0);
        qwd->ui32[3] = 0;
        printf("Model3:MPG1: %x\n", __model3_mpg1_view_end);
        qwd->ui32[4] = DMAend;
        qwd->ui32[5] = 0;
        qwd->ul64[3] = 0;
        initialized_867 = 1;
    }
    d1cSend(packet_buffer_866);
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", Model3LoadMpg1);
#endif

#ifdef NON_MATCHING
static void InitAllDataOne(AllData* p /* r16 */) {
    
    {
        LambertData* data = UNCACHED_POINTER(&p->lambert);
        sceVu0CopyVector(data->rgba_max, model3_junk.rgba_max);
    }

    
    {
        DSetupData* data = UNCACHED_POINTER(&p->dsetup);
        sceVu0CopyVector(data->rgba_max.fv, model3_junk.rgba_max);
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
    }
    
    
    
    {
        EDrawData* data = UNCACHED_POINTER(&p->edraw);
        data->giftag.u64[0] = SCE_GIF_SET_TAG(4, 1, 0, 0, SCE_GIF_PACKED, 3);
        data->giftag.u64[1] = GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM);
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
        data->envtag.u64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 1, 1, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 5);
    
        
        data->envtag.u64[1] = GIF_REGLIST(SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
        data->tex0.u64[0] = 0;
        data->tex0.u64[1] = SCE_GS_TEX0_1;
        data->tex1.u64[0] = SCE_GS_SET_TEX1(/* lcm */ 1, /* mxl */ 0, /* mmag */ 1, /* mmin */ 1, /* mtba */ 0, /* l */ 0, /* k */ 0);
        data->tex1.u64[1] = SCE_GS_TEX1_1;
        data->clamp.u64[0] = SCE_GS_SET_CLAMP(0, /* wmt */ 1, 0, 0, 0, 0);
        data->clamp.u64[1] = SCE_GS_CLAMP_1;
        data->alpha.u64[0] = SCE_GS_SET_ALPHA(0, /* b */ 1, 0, /* d */ 1, 0);
        data->alpha.u64[1] = SCE_GS_ALPHA_1;
        data->fogcol.u64[0] = 0;
        data->fogcol.u64[1] = SCE_GS_FOGCOL;
    }





    
    
    {
        SDrawData* data = UNCACHED_POINTER(&p->sdraw);
        data->giftag.u64[0] = SCE_GIF_SET_TAG(4, 1, 0, 0, SCE_GIF_PACKED, 3);
        data->giftag.u64[1] = GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM);
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
        data->envtag.u64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 1, 1, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 5);
    
        
        data->envtag.u64[1] = GIF_REGLIST(SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
        data->tex0.u64[0] = 0;
        data->tex0.u64[1] = SCE_GS_TEX0_1;
        data->tex1.u64[0] = SCE_GS_SET_TEX1(/* lcm */ 1, /* mxl */ 0, /* mmag */ 1, /* mmin */ 1, /* mtba */ 0, /* l */ 0, /* k */ 0);
        data->tex1.u64[1] = SCE_GS_TEX1_1;
        data->clamp.u64[0] = SCE_GS_SET_CLAMP(/* wms */ 1, /* wmt */ 1, 0, 0, 0, 0);
        data->clamp.u64[1] = SCE_GS_CLAMP_1;
        
        
        
        
        data->alpha.u64[0] = SCE_GS_SET_ALPHA(0, /* b */ 2, 1 /* c */, /* d */ 1, 0);
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        data->alpha.u64[1] = SCE_GS_ALPHA_1;
        data->fogcol.u64[0] = 0;
        data->fogcol.u64[1] = SCE_GS_FOGCOL;
    }

    
    {
        SDrawData* data = UNCACHED_POINTER(&p->bdraw);
        data->giftag.u64[0] = SCE_GIF_SET_TAG(4, 1, 0, 0, SCE_GIF_PACKED, 3);
        data->giftag.u64[1] = GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM);
        data->envtag.u64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 0, 1, 1, 0, 0, 0, 0, 0), SCE_GIF_PACKED, 5);
    
        
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
        data->envtag.u64[1] = GIF_REGLIST(SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
        data->tex0.u64[0] = 0;
        data->tex0.u64[1] = SCE_GS_TEX0_1;
        data->tex1.u64[0] = SCE_GS_SET_TEX1(/* lcm */ 1, /* mxl */ 0, /* mmag */ 1, /* mmin */ 1, /* mtba */ 0, /* l */ 0, /* k */ 0);
        data->tex1.u64[1] = SCE_GS_TEX1_1;
        data->clamp.u64[0] = SCE_GS_SET_CLAMP(/* wms */ 1, /* wmt */ 1, 0, 0, 0, 0);
        data->clamp.u64[1] = SCE_GS_CLAMP_1;
        data->alpha.u64[0] = SCE_GS_SET_ALPHA(0, /* b */ 1, 0, /* d */ 1, 0);
        data->alpha.u64[1] = SCE_GS_ALPHA_1;
        data->fogcol.u64[0] = 0;
        data->fogcol.u64[1] = SCE_GS_FOGCOL;
    } 
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", InitAllDataOne);
#endif

static void InitSprData(SprData* p /* r2 */) {
    int i; // r3

    for (i = 0; i < 2; i++) {
        NDrawData* data = UNCACHED_POINTER(&p->ndraw[i]); // r2
        data->giftag.u64[0] = SCE_GIF_SET_TAG(4, 1, 0, 0, SCE_GIF_PACKED, 3);
        data->giftag.u64[1] = GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM);
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
        data->envtag.u64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 0, 0, 0, 0, 0), SCE_GIF_PACKED, 5);
        data->envtag.u64[1] = GIF_REGLIST(SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
        data->tex0.u64[0] = 0;
        data->tex0.u64[1] = SCE_GS_TEX0_1;
        data->tex1.u64[0] = 0;
        data->tex1.u64[1] = SCE_GS_TEX1_1;
        data->clamp.u64[0] = 0;
        data->clamp.u64[1] = SCE_GS_CLAMP_1;
        data->alpha.u64[0] = SCE_GS_SET_ALPHA(0, /* b */ 1, 0, /* d */ 1, 0);
        data->alpha.u64[1] = SCE_GS_ALPHA_1;
        data->fogcol.u64[0] = 0;
        data->fogcol.u64[1] = SCE_GS_FOGCOL;
    }

    for (i = 0; i < 2; i++) {
        NDrawData* data = UNCACHED_POINTER(&p->odraw[i]); // r2
        data->giftag.u64[0] = SCE_GIF_SET_TAG(4, 1, 0, 0, SCE_GIF_PACKED, 3);
        data->giftag.u64[1] = GIF_REGLIST(SCE_GS_ST, SCE_GS_RGBAQ, SCE_GS_XYZF2, SCE_GS_PRIM);
        data->waittag.u64[0] = 0x8000;
        data->waittag.u64[1] = 0;
        data->envtag.u64[0] = SCE_GIF_SET_TAG(1, 1, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 1, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 5);
        data->envtag.u64[1] = GIF_REGLIST(SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD, SCE_GIF_PACKED_AD);
        data->tex0.u64[0] = 0;
        data->tex0.u64[1] = SCE_GS_TEX0_1;
        data->tex1.u64[0] = 0;
        data->tex1.u64[1] = SCE_GS_TEX1_1;
        data->clamp.u64[0] = 0;
        data->clamp.u64[1] = SCE_GS_CLAMP_1;
        data->alpha.u64[0] = SCE_GS_SET_ALPHA(0, /* b */ 1, 0, /* d */ 1, 0);
        data->alpha.u64[1] = SCE_GS_ALPHA_1;
        data->fogcol.u64[0] = 0;
        data->fogcol.u64[1] = SCE_GS_FOGCOL;
    }
}

static void InitData1(void) {
    extern /* static */ int initialized_928; // @ 0x0041AC78
    sceDmaChan* toSPR; // r2

    if (initialized_928 == 0) {
        InitAllDataOne(all_data_db);
        InitAllDataOne(&all_data_db[1]);
        InitSprData(&spr_data_mem);
        initialized_928 = 1;
    }
    do {

    } while (*D9_CHCR & 0x100);
    toSPR = sceDmaGetChan(SCE_DMA_toSPR);
    toSPR->sadr = (void*) ((u_int) spr_data & 0x3FFF);
    sceDmaSendN(toSPR, &spr_data_mem, 32);
    do {

    } while (*D9_CHCR & 0x100);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeData1);

#define packet4main packet4main_1018
extern /* static */ Init_Gs_Packet packet4main; // @ 0x002A9780
static void InitEnv1(sceVif1Packet* pk /* r16 */, int unused) {
    sceVif1PkCnt(pk, 0);
    sceVif1PkAddCode(pk, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkRef(pk, (u_long128*) &packet4main, sizeof(packet4main) / sizeof(Q), 0, SCE_VIF1_SET_DIRECT(4, 0), 0);
}

#define packet packet_1024
extern /* static */ Packet packet; // @ 0x002A97C0
static void TiniEnv(sceVif1Packet* pk /* r2 */) {
    sceVif1PkRef(pk, (u_long128*) &packet, sizeof(Packet) / sizeof(Q), 0, SCE_VIF1_SET_DIRECT(3, 0), 0);
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeVu1PartTransferPacket);

#ifdef NON_MATCHING
static void MakeLambertShadingPacket(Part* part /* r20 */, sceVif1Packet* pk /* r19 */) {
    int n_parallels = LightNValidParallelMatrices(); // r16
    int n_extras = LightNValidExtras(); // r17
    int i; // r18
    Light* light; // r16
    float brightness; // r20
    Data* lf_data; // r16

    for (i = 1; i < n_parallels; i++) {
        sceVif1PkRef(pk, (u_long128* ) &all_data->plight[i], 8, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 8, SCE_VIF_UPK_V4_32, 0), 0);
        sceVif1PkCnt(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));
        sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(8, 0));
        xitop_0x0041BF08 ^= (1 << 9);
    }

    for (i = 0; i < n_extras; i++) {
        light = LightNthValidExtra(i);
        sceVif1PkRef(pk, (u_long128* ) &all_data->elight[i], 4, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 4, SCE_VIF_UPK_V4_32, 0), 0);
        sceVif1PkCnt(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));

        switch (light->kind) {
            case 2:
                sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(10, 0));
                break;

            case 3:
                sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(12, 0));
                break;

            default:
                ASSERT_ON_LINE(0, 830);
        }
        
        xitop ^= (1 << 9);
    }

    brightness = LightReflectionBrightness();
    sceVif1PkRef(pk, (u_long128* ) all_data, 10, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 10, SCE_VIF_UPK_V4_32, 0), 0);
    sceVif1PkCnt(pk, 0);
    sceVif1PkAddCode(pk, SCE_VIF1_SET_STCYCL(1, 1, 0));
    sceVif1PkAddCode(pk, SCE_VIF1_SET_UNPACK(xitop + 10, 3, SCE_VIF_UPK_V4_32, 0));
    lf_data = sceVif1PkReserve(pk, 12);

    ASSERT_ON_LINE(((u_int)lf_data & 0x03) == 0, 885);

    sceVu0CopyVector(lf_data->diffuse, part->diffuse);
    lf_data->diffuse[3] = 1.0f;

    sceVu0CopyVector(lf_data->ambient, part->ambient);
    lf_data->ambient[3] = 1.0f;

    lf_data->param[2] = part->phong_param_a * brightness;
    lf_data->param[3] = part->phong_param_b * brightness;

    sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));
    sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(14, 0));

    xitop ^= (1 << 9);
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeLambertShadingPacket_VU1);
#endif

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeNormalPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeEnvironPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeSpecularPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeBaseSpecularPacket);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", MakeOverPacket);

static void MakeDrawPacket(Part* part /* r17 */, sceVif1Packet* pk /* r16 */) {
    u_long128* gifad; // r2

    sceVif1PkRef(pk, (u_long128*) &all_data->dsetup, 8, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 8, SCE_VIF_UPK_V4_32, 0), 0);
    sceVif1PkCnt(pk, 0);
    sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));
    sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(20, 0));

    xitop ^= (1 << 9);

    if (!part->specular_pos) {
        MakeNormalPacket(part, pk);
        if (part->envmap_param) {
            MakeEnvironPacket(part, pk);
        }
        if (part->shading_type == SHADING_TYPE_LAMBERTIAN_4) {
            gifad = (u_long128*) (&shGs_AllEnv.Now_DrawEnv.frame_mskalpha) - 1;
            sceVif1PkRef(pk, gifad, 2, SCE_VIF1_SET_FLUSH(0), SCE_VIF1_SET_DIRECT(2, 0), 0);
            MakeSpecularPacket(part, pk);

            gifad = (u_long128*) (&shGs_AllEnv.Now_DrawEnv.frame_normal) - 1;
            sceVif1PkRef(pk, (u_long128*) (&shGs_AllEnv.Now_DrawEnv.frame_normal) - 1, 2, SCE_VIF1_SET_FLUSH(0), SCE_VIF1_SET_DIRECT(2, 0), 0);
        }
    } else {
        if (part->shading_type == SHADING_TYPE_LAMBERTIAN_4) {
            MakeBaseSpecularPacket(part, pk);
        }
        MakeOverPacket(part, pk);
    }
}

#ifdef NON_MATCHING
static void DrawPart1(Part* part /* r17 */, sceVif1Packet* pk /* r16 */) {
    Data* data; // r2

    xitop = 496;

    if (part->xtop == prev_xtop) {
        sceVif1PkCnt(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_FLUSH(0));
    }

    prev_xtop = part->xtop;

    MakeVu1PartTransferPacket(part, pk);
    sceVif1PkCnt(pk, 0);
    sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(part->xtop, 0));
    sceVif1PkAddCode(pk, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkAddCode(pk, SCE_VIF1_SET_UNPACK(xitop, 1, SCE_VIF_UPK_V4_32, 0));

    if (part->shading_type == SHADING_TYPE_1) {
        sceVif1PkAddData(pk, reinterpret_as_u_int(part->diffuse[0]));
        sceVif1PkAddData(pk, reinterpret_as_u_int(part->diffuse[1]));
        sceVif1PkAddData(pk, reinterpret_as_u_int(part->diffuse[2]));
        sceVif1PkAddData(pk, reinterpret_as_u_int(128.0f));
    } else {
        sceVif1PkAddData(pk, 0);
        sceVif1PkAddData(pk, 0);
        sceVif1PkAddData(pk, 0);
        sceVif1PkAddData(pk, 0);
    }

    sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(6, 0));
    xitop ^= (1 << 9);

    switch (part->shading_type) {
        case SHADING_TYPE_1:
            break;

        case SHADING_TYPE_LAMBERTIAN_2:
        case SHADING_TYPE_LAMBERTIAN_3:
        case SHADING_TYPE_LAMBERTIAN_4:
            MakeLambertShadingPacket_VU1(part, pk);
            break;

        default:
            ASSERT_ON_LINE(0, 1208);
            return;
    }

    if (part->envmap_param) {
        sceVif1PkRef(pk, (u_long128*) &all_data->emap, 6, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 6, SCE_VIF_UPK_V4_32, 0), 0);
        sceVif1PkCnt(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));
        sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(16, 0));
        xitop ^= (1 << 9);
    }

    if (part->shading_type == SHADING_TYPE_LAMBERTIAN_4) {
        sceVif1PkRef(pk, (u_long128*) &all_data->smap, 4, SCE_VIF1_SET_STCYCL(1, 1, 0), SCE_VIF1_SET_UNPACK(xitop, 4, SCE_VIF_UPK_V4_32, 0), 0);
        sceVif1PkCnt(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_STCYCL(1, 1, 0));
        sceVif1PkAddCode(pk, SCE_VIF1_SET_UNPACK(xitop + 4, 1, SCE_VIF_UPK_V4_32, 0));

        data = sceVif1PkReserve(pk, 4);
        ASSERT_ON_LINE(((u_int)data & 0x03) == 0, 1238);

        data->diffuse[3] = part->blinn_param;
        sceVif1PkAddCode(pk, SCE_VIF1_SET_ITOP(xitop, 0));
        sceVif1PkAddCode(pk, SCE_VIF1_SET_MSCAL(18, 0));
        xitop ^= (1 << 9);
    }

    MakeDrawPacket(part, pk);
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", DrawPart1);
#endif

#ifdef NON_MATCHING
static void DrawParts1(sh_Model* model /* r19 */, ModelWork* work /* r16 */) {
    
    u_long128* packet_buffer = ktVif1PkBufNext(); // r17
    sceVif1Packet packet; // r29+0x80
    sceVif1Packet* pk = &packet; // r18
    int n_parts = model->n_vu1_parts; // r2
    Part* parts_top; // r2 @note `parts_top` is unused here, but present in dwarf.
    Part* part = (u_char*) model + model->vu1_parts_offset; // r19
    int i, itex; // r2, r17 @note `itex` is unused here, but present in dwarf.
    void* pktop; // r20
    prev_xtop = 1;
    
    xitop_0x0041BF08 = 496;
    MakeData1();
    sceVif1PkInit(pk, UNCACHED_POINTER(packet_buffer));
    
    pktop = pk->pBase;
    

    InitEnv1(pk, sh2gfw_get_Charaid());
    
    for (i = 0; i < sh2gfw_get_TBChangeVU1num(); i++) {
        int st, en; // r21, r22
        st = sh2gfw_get_ModelChangeTB(i);
        en = sh2gfw_get_ModelChangeTB(i + 1);
    
        for (; st < en; st++, (u_char*) part += part->size) {
        
            
            
            
            
            if (!Model3WorkEquipmentFlag(work, part->equipment_id)) continue;
            
                
            DrawPart1(part, pk);
        }

        
        sceVif1PkEnd(pk, 0);
        sceVif1PkAddCode(pk, SCE_VIF1_SET_FLUSH(0));
        sceVif1PkAddCode(pk, 0);
        
        sh2gfw_Thr_Chracter_d1d2SyncKick(pktop, sh2gfw_get_ModelIndexTB(i));
        
        pktop = (u_long128* ) pk->pCurrent;
    
    }
    
    
    TiniEnv(pk);
    sceVif1PkEnd(pk, 0);
    sceVif1PkAddCode(pk, SCE_VIF1_SET_FLUSH(0));
    sceVif1PkAddCode(pk, 0);
    sceVif1PkTerminate(pk);
    
    
    
    
    
    sh2gfw_set_CharaD1CID(d1cSend(MAIN_RAM_POINTER(pktop)));



}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu1_n", DrawParts1);
#endif

void Model3DrawVu1Parts(Model* model /* r2 */, ModelWork* work /* r2 */) {
    muga ^= 1;
    DrawParts1((sh_Model*) model, work);
}


INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @873_0x0038D9B0);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1102_0x0038D9D0);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1103_0x0038D9F8);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1104_0x0038DA00);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1105_0x0038DA30);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @22);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @23);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @39);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1171_0x0038DAD0);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1190);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1216_0x0038DB30);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1290);

INCLUDE_RODATA("asm/nonmatchings/Chacter_Draw/model3_vu1_n", @1291);

