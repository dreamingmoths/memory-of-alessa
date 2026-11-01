#include "sh2_common.h"

#include "sce/libvifpk.h"
#include "sce/libgraph.h"

#include "Effect2/hh_class_flame_02.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"

#pragma divbyzerocheck off

typedef struct Flame_Initialize_Parameter {
    // total size: 0x60
    u_int ParticleDraw_Num; // offset 0x0, size 0x4
    u_int Flag[3]; // offset 0x4, size 0xC
    float Convergence_Coff; // offset 0x10, size 0x4
    float Convergence_Coff_Sub; // offset 0x14, size 0x4
    float Gravity_Suppress_Coff; // offset 0x18, size 0x4
    float Base_Alpha; // offset 0x1C, size 0x4
    float Base_Scale; // offset 0x20, size 0x4
    float Base_Time; // offset 0x24, size 0x4
    float Rand_Time_Width; // offset 0x28, size 0x4
    sceVu0IVECTOR Verocity_0; // offset 0x30, size 0x10
    sceVu0IVECTOR Length_Max; // offset 0x40, size 0x10
    sceVu0FVECTOR RGBA; // offset 0x50, size 0x10
} Flame_Initialize_Parameter;

static void Particle_Initialize(HH_Object_Flame_02_Particle* pParticle, Flame_Initialize_Parameter* pParameter);
static void Particle_Calculator(HH_Object_Flame_02_Particle* pParticle, float* Position);
static u_int Object_Initialize(HH_Object_Flame_02* pThis, ImpactQueue_Element* pElement);
static void Particle_Motion(HH_Object_Flame_02_Particle* pParticle, Flame_Initialize_Parameter* pParameter, float* Position);
static u_int Object_Draw(HH_Object_Flame_02* pThis, ImpactQueue_Element* pElement);

/**
 * flame_02 is more akin to flame_00, except it has alpha & depth tests set to "always".
 */
UNMIGRATED(/* static */ sceVu0FVECTOR* _square_stq_list_0x0037B030[64]); // size: 0x100, address: 0x377A50
UNMIGRATED(/* static */ Flame_Initialize_Parameter _flame_init_parm_table_0x0037B130[8]); // size: 0x300, address: 0x377B50
UNMIGRATED(/* static */ sceVu0FMATRIX _square_00_vertex_0x00379FF0); // size: 0x40, address: 0x376A10
#define HH_FLAME_02_PARTICLE_MAX 100

#line 795
static u_int Object_Initialize(HH_Object_Flame_02* pThis, ImpactQueue_Element* pElement) {
    u_int result; // r2
    u_int i; // r16
    Flame_Initialize_Parameter* pParameter; // r2
    HH_Object_Flame_02_Particle* pParticle; // r19
    float ratio; // r1
    pThis->Timer = 0.0f;
    
    
    
    
    
    pElement->Option.Int_Value[0] %= 8;
    
    
    
    
    pParameter = &_flame_init_parm_table_0x0037B130[pElement->Option.Int_Value[0]];
    
    for (i = 0; i < pParameter->ParticleDraw_Num; i++) {
        pParticle = &pThis->Particle[i];
    
        Particle_Initialize(pParticle, pParameter);



        
        ratio = 0.01f * (rand() % 100);
        
        pParticle->Time = pParticle->Life_Time * ratio;
    
    }
    
    
    pThis->Particle_DrawNum = HH_FLAME_02_PARTICLE_MAX;
    
    result = true;
    return result;
}






#line 841
static void Particle_Initialize(HH_Object_Flame_02_Particle* pParticle, Flame_Initialize_Parameter* pParameter) {
    float ratio; // r1
    float length_max_pow_f = 0.5f * (pParameter->Length_Max[0] + pParameter->Length_Max[2]); // r20

    if (pParameter->Flag[0])
        length_max_pow_f = pParameter->Length_Max[0];

    if (pParameter->Flag[1])
        length_max_pow_f = pParameter->Length_Max[1];

    if (pParameter->Flag[2])
        length_max_pow_f = pParameter->Length_Max[2];

    length_max_pow_f *= length_max_pow_f;

    #define DEVIATE(x) ((rand() % (x)) - ((x) >> 1))
    pParticle->Location[0]   = DEVIATE(pParameter->Length_Max[0]);
    pParticle->Location[1]   = DEVIATE(pParameter->Length_Max[1]);
    pParticle->Location[2]   = DEVIATE(pParameter->Length_Max[2]);
    
    pParticle->Verocity_0[0] = DEVIATE(pParameter->Verocity_0[0]);
    pParticle->Verocity_0[1] = DEVIATE(pParameter->Verocity_0[1]);
    pParticle->Verocity_0[2] = DEVIATE(pParameter->Verocity_0[2]);
    pParticle->Verocity_0[3] = -2450.0f * pParameter->Gravity_Suppress_Coff;
    sceVu0CopyVector(pParticle->RGBA, pParameter->RGBA);
    
    pParticle->Time = 0.0f;
    pParticle->Scale = pParameter->Base_Scale;
    pParticle->Convergence_Coff = pParameter->Convergence_Coff;
    pParticle->Texture_Kind = rand() & 63; // @note mod doesn't match. we care about speed here
    
    ratio = sceVu0InnerProduct(pParticle->Location, pParticle->Location) / length_max_pow_f;
    
    if (ratio > 1.0f)
        ratio = 1.0f;

    pParticle->Life_Time = pParameter->Base_Time + (pParameter->Rand_Time_Width * (1.0f - ratio));
}











#line 891
static void Particle_Motion(HH_Object_Flame_02_Particle* pParticle, Flame_Initialize_Parameter* pParameter, float* Position) {
    if (pParticle->Time > pParticle->Life_Time) {
        Particle_Initialize(pParticle, pParameter);
    }
    {
        float pre_time; // r1
        float life_time_rev; // r2
        float scale_ratio; // r20
        float alpha_ratio; // r29+0x50
        pre_time = 0.25f * pParticle->Life_Time;
        life_time_rev = 1.0f / pParticle->Life_Time;
        scale_ratio = 1.0f - (pParticle->Time * life_time_rev);
        
        
        
        
        if (pParticle->Time < pre_time) {
            alpha_ratio = pParticle->Time / pre_time;
        } else {
            alpha_ratio = 1.0f - ((4.0f / 3.0f) * (life_time_rev * (pParticle->Time - pre_time)));
        }
        
        Particle_Calculator(pParticle, Position);
        if (pParticle->Convergence_Coff > 0.0f) {
            pParticle->Convergence_Coff = pParticle->Convergence_Coff + pParameter->Convergence_Coff_Sub;
        }
        pParticle->Time += TIME_STEP_30FPS;
        pParticle->RGBA[3] = pParameter->Base_Alpha * alpha_ratio;
        pParticle->Scale = pParameter->Base_Scale * scale_ratio;
    }
}









#line 932
static void Particle_Calculator(HH_Object_Flame_02_Particle* pParticle, float* Position) {
    sceVu0FMATRIX time_mat; // r29+0x30

    // X & Z are scaled by the convergence coefficient; the Y translation is quadratic with time
    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = time_mat[2][2] = pParticle->Time * pParticle->Convergence_Coff;
    
    time_mat[1][1] = pParticle->Time;
    time_mat[3][1] = SQUARE(pParticle->Time);
    time_mat[3][3] = 0;
    sceVu0ApplyMatrix(Position, time_mat, pParticle->Verocity_0);
}












#line 957
static u_int Object_Draw(HH_Object_Flame_02* pThis, ImpactQueue_Element* pElement) {
    u_int result = false; // r2
    Flame_Initialize_Parameter* pParmTable = &_flame_init_parm_table_0x0037B130[pElement->Option.Int_Value[0]]; // @note not in dwarf!
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r17
    sceVu0FVECTOR* pVertex = _square_00_vertex_0x00379FF0[0]; // r18
    sceVu0FMATRIX lwm; // r29+0x90
    sceVu0FMATRIX lsm; // r29+0xD0
    sceVu0FMATRIX _lsm; // r29+0x110
    sceVu0FMATRIX clip_mat; // r29+0x150
    sceVu0FMATRIX _clip_mat; // r29+0x190
    sceVu0IVECTOR xyzf; // r29+0x1D0
    sceVu0IVECTOR rgba; // r29+0x1E0
    sceVu0FVECTOR* pStq; // r19
    sceVu0IVECTOR position; // r29+0x1F0
    sceVu0FVECTOR stq_dummy; // r29+0x200
    u_int i; // r20
    
    HH_ClassWrapper_WorldScreenMatrix_Get(_lsm);
    
    
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(_clip_mat);
    
    HH_Vif1PacketBuffer_GifTag_Open();

    for (i = 0; i < pParmTable->ParticleDraw_Num; i++) {
        HH_Object_Flame_02_Particle* pParticle = &pThis->Particle[i]; // r21
        Flame_Initialize_Parameter* pParameter = pParmTable;
        
        Particle_Motion(pParticle, pParameter, position);
        
        
        
        
        HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(lwm);
        
        
        sceVu0ScaleVector(lwm[0], lwm[0], pParticle->Scale);
        sceVu0ScaleVector(lwm[1], lwm[1], pParticle->Scale);
        sceVu0ScaleVector(lwm[2], lwm[2], pParticle->Scale);
        
        
        sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
        sceVu0TransMatrix(lwm, lwm, pParticle->Location);
        sceVu0TransMatrix(lwm, lwm, position);
        sceVu0MulMatrix(lsm, _lsm, lwm);
        
        
        sceVu0MulMatrix(clip_mat, _clip_mat, lwm);
        
        
        pStq = _square_stq_list_0x0037B030[pParticle->Texture_Kind];
        sceVu0FTOI0Vector(rgba, pParticle->RGBA);
        
        HH_Vif1Packet_GeneralGifTag_Sprite_Open();
        ((u_long128*) pPk->pCurrent)[0] = *(u_long128*) rgba;
        
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
        ((u_long128*) pPk->pCurrent)[1] = ((u_long128*) pStq)[0];
        xyzf[2] += sizeof(u_long128) * 50;
        ((u_long128*) pPk->pCurrent)[2] = *(u_long128*) xyzf;
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
        ((u_long128*) pPk->pCurrent)[3] = ((u_long128*) pStq)[3];
        xyzf[2] += sizeof(u_long128) * 50;
        ((u_long128*) pPk->pCurrent)[4] = *(u_long128*) xyzf;
        pPk->pCurrent += 20;
        sceVif1PkCloseGifTag(pPk);
    }
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}












#define HH_FLAME_02_TEX_ID 3
#define HH_FLAME_02_CLUT_ID 0

#line 1044
u_int HH_Class_Prefix_Flame_02(void) {
    u_long tex0;                                      // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_int result = true;                              // r2

    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 0, SCE_GS_TRUE, SCE_GS_DEPTH_ALWAYS));











    #line 1063
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_FLAME_02_TEX_ID, HH_FLAME_02_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, 0x1ff, 0, 0x1ff, 0)); // 0x1ff001fff
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}











#line 1085
u_int HH_Class_Suffix_Flame_02(void) {
    u_int result = true; // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16

    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 0, SCE_GS_TRUE, SCE_GS_DEPTH_GEQUAL));
    
    
    
    
    
    
    
    
    
    
    
    #line 1106
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}



#define HH_FLAME_02_STEP_INIT    0
#define HH_FLAME_02_STEP_TIMER   1
#define HH_FLAME_02_STEP_DRAW    2
#define HH_FLAME_02_STEP_OFF     3




#line 1122
u_int HH_Class_Flame_02(void* pBlock, ImpactQueue_Element* pElement) {
    
    
    
    
    
    
    
    u_int result = true; // r16
    HH_Object_Flame_02* pThis = pBlock; // r17
    sceVu0FMATRIX clip_mat; // r29+0x40

    switch (pThis->Step) {
        case HH_FLAME_02_STEP_INIT:
            
            Object_Initialize(pThis, pElement);
            
            
            if (pElement->Option.Float_Value[0] == 0.0f) {
            
                pThis->Step = HH_FLAME_02_STEP_DRAW;
            } else {
             
                
                pThis->Step = HH_FLAME_02_STEP_TIMER;
            }
            break;

        case HH_FLAME_02_STEP_TIMER:
            if (pThis->Timer > pElement->Option.Float_Value[0])
                pThis->Step = HH_FLAME_02_STEP_OFF;
            /* fallthrough */
        case HH_FLAME_02_STEP_DRAW:
            HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
            
            if (!HH_ClassWrapper_Point_Clip_Judge(clip_mat, pElement->Option.Vector[0], 1)) {
            
                Object_Draw(pThis, pElement);
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case HH_FLAME_02_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}

