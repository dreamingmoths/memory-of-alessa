#include "sh2_common.h"

#include "sce/libvifpk.h"
#include "sce/libgraph.h"

#include "Effect2/hh_class_flame_00.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"

#pragma divbyzerocheck off

static u_int Object_Initialize(HH_Object_Flame_00* pThis, ImpactQueue_Element* pElement);
static void Particle_Initialize(HH_Object_Flame_00_Particle* pParticle, Flame_Initialize_Parameter* pParameter);
static void Particle_Motion(HH_Object_Flame_00_Particle* pParticle, Flame_Initialize_Parameter* pParameter, float* Position);
static void Particle_Calculator(HH_Object_Flame_00_Particle* pParticle, float* Position);
static u_int Object_Draw(HH_Object_Flame_00* pThis, ImpactQueue_Element* pElement);

UNMIGRATED(/* static */ sceVu0FVECTOR* _square_stq_list_0x00377A50[64]); // size: 0x100, address: 0x377A50
UNMIGRATED(/* static */ Flame_Initialize_Parameter _flame_init_parm_table_0x00377B50[8]); // size: 0x300, address: 0x377B50
UNMIGRATED(/* static */ sceVu0FMATRIX _square_00_vertex_0x00376A10); // size: 0x40, address: 0x376A10

#line 799
static u_int Object_Initialize(HH_Object_Flame_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false; // r2
    u_int i; // r16
    Flame_Initialize_Parameter* pParameter; // r2
    HH_Object_Flame_00_Particle* pParticle; // r19
    float ratio; // r1
    pThis->Timer = 0.0f;
    
    
    
    
    
    pElement->Option.Int_Value[0] %= 8;
    
    
    
    
    pParameter = &_flame_init_parm_table_0x00377B50[pElement->Option.Int_Value[0]];
    
    for (i = 0; i < pParameter->ParticleDraw_Num; i++) {
        pParticle = &pThis->Particle[i];
    
        Particle_Initialize(pParticle, pParameter);



        
        ratio = 0.01f * (rand() % 100);
        
        pParticle->Time = pParticle->Life_Time * ratio;
    
    }
    
    
    pThis->Particle_DrawNum = HH_FLAME_00_PARTICLE_MAX;
    
    result = true;
    return result;
}

#line 848
static void Particle_Initialize(HH_Object_Flame_00_Particle* pParticle, Flame_Initialize_Parameter* pParameter) {
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

#line 898
static void Particle_Motion(HH_Object_Flame_00_Particle* pParticle, Flame_Initialize_Parameter* pParameter, float* Position) {
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

#line 939
static void Particle_Calculator(HH_Object_Flame_00_Particle* pParticle, float* Position) {
    sceVu0FMATRIX time_mat; // r29+0x30

    // X & Z are scaled by the convergence coefficient; the Y translation is quadratic with time
    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = time_mat[2][2] = pParticle->Time * pParticle->Convergence_Coff;
    
    time_mat[1][1] = pParticle->Time;
    time_mat[3][1] = SQUARE(pParticle->Time);
    time_mat[3][3] = 0;
    sceVu0ApplyMatrix(Position, time_mat, pParticle->Verocity_0);
}

#line 964
static u_int Object_Draw(HH_Object_Flame_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false; // r2
    Flame_Initialize_Parameter* pParmTable = &_flame_init_parm_table_0x00377B50[pElement->Option.Int_Value[0]]; // @note not in dwarf!
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r17
    sceVu0FVECTOR* pVertex = _square_00_vertex_0x00376A10[0]; // r18
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
        HH_Object_Flame_00_Particle* pParticle = &pThis->Particle[i]; // r21
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
        
        
        pStq = _square_stq_list_0x00377A50[pParticle->Texture_Kind];
        sceVu0FTOI0Vector(rgba, pParticle->RGBA);
        
        HH_Vif1Packet_GeneralGifTag_Sprite_Open();
        ((u_long128*) pPk->pCurrent)[0] = *(u_long128*) rgba;
        
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
        ((u_long128*) pPk->pCurrent)[1] = ((u_long128*) pStq)[0];
        xyzf[2] += 800;
        ((u_long128*) pPk->pCurrent)[2] = *(u_long128*) xyzf;
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
        ((u_long128*) pPk->pCurrent)[3] = ((u_long128*) pStq)[3];
        xyzf[2] += 800;
        ((u_long128*) pPk->pCurrent)[4] = *(u_long128*) xyzf;
        pPk->pCurrent += 20;
        sceVif1PkCloseGifTag(pPk);
    }
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 1054
u_int HH_Class_Prefix_Flame_00(void) {
    u_long tex0;                                      // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_int result = true;                              // r2

    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_FLAME_00_TEX_ID, HH_FLAME_00_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, 0x1ff, 0, 0x1ff, 0)); // 0x1ff001fff
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));

    #line 1095
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 1112
u_int HH_Class_Suffix_Flame_00(void) {
    u_int result = true; // r2
    
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    
    return result;
}

#line 1131
u_int HH_Class_Flame_00(void* pBlock, ImpactQueue_Element* pElement) {
    #line 1139
    u_int result = true; // r16
    HH_Object_Flame_00* pThis = pBlock; // r17
    sceVu0FMATRIX clip_mat; // r29+0x40

    switch (pThis->Step) {
        case HH_FLAME_00_STEP_INIT:
            
            Object_Initialize(pThis, pElement);
            
            
            if (pElement->Option.Float_Value[0] == 0.0f) {
            
                pThis->Step = HH_FLAME_00_STEP_DRAW;
            } else {
             
                
                pThis->Step = HH_FLAME_00_STEP_TIMER;
            }
            break;

        case HH_FLAME_00_STEP_TIMER:
            if (pThis->Timer > pElement->Option.Float_Value[0])
                pThis->Step = HH_FLAME_00_STEP_OFF;
            /* fallthrough */
        case HH_FLAME_00_STEP_DRAW:
            HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
            
            if (!HH_ClassWrapper_Point_Clip_Judge(clip_mat, pElement->Option.Vector[0], 1)) {
            
                Object_Draw(pThis, pElement);
            }
            
            #line 1200
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case HH_FLAME_00_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}
