#include "sh2_common.h"
#include "math.h"
#include "sce/libgraph.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_smoke_00.h"

static sceVu0FMATRIX _square_00_vertex = {
    { -1.0f, -1.0f, 0.0f, 1.0f },
    { -1.0f,  1.0f, 0.0f, 1.0f },
    {  1.0f, -1.0f, 0.0f, 1.0f },
    {  1.0f,  1.0f, 0.0f, 1.0f }
};

static sceVu0FMATRIX _square_stq_00 = {
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.74804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.5f, 1.0f, 0.0f },
    { 0.74804687f, 0.74804687f, 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_01 = {
    { 0.5f, 0.75f, 1.0f, 0.0f },
    { 0.5f, 0.99804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.75f, 1.0f, 0.0f },
    { 0.74804687f, 0.99804687f, 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_02 = {
    { 0.75f, 0.5f, 1.0f, 0.0f },
    { 0.75f, 0.74804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.5f, 1.0f, 0.0f },
    { 0.99804687f, 0.74804687f, 1.0f, 0.0f },
};
static sceVu0FMATRIX _square_stq_03 = {
    { 0.75f, 0.75f, 1.0f, 0.0f },
    { 0.75f, 0.99804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.75f, 1.0f, 0.0f },
    { 0.99804687f, 0.99804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_10 = {
    { 0.5f, 0.74804687f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.74804687f, 0.74804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.5f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_11 = {
    { 0.5f, 0.99804687f, 1.0f, 0.0f },
    { 0.5f, 0.75f, 1.0f, 0.0f },
    { 0.74804687f, 0.99804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.75f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_12 = {
    { 0.75f, 0.74804687f, 1.0f, 0.0f },
    { 0.75f, 0.5f, 1.0f, 0.0f },
    { 0.99804687f, 0.74804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.5f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_13 = {
    { 0.75f, 0.99804687f, 1.0f, 0.0f },
    { 0.75f, 0.75f, 1.0f, 0.0f },
    { 0.99804687f, 0.99804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.75f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_20 = {
    { 0.74804687f, 0.74804687f, 1.0f, 0.0f },
    { 0.5f, 0.74804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.5f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_21 = {
    { 0.74804687f, 0.99804687f, 1.0f, 0.0f },
    { 0.5f, 0.99804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.75f, 1.0f, 0.0f },
    { 0.5f, 0.75f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_22 = {
    { 0.99804687f, 0.74804687f, 1.0f, 0.0f },
    { 0.75f, 0.74804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.5f, 1.0f, 0.0f },
    { 0.75f, 0.5f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_23 = {
    { 0.99804687f, 0.99804687f, 1.0f, 0.0f },
    { 0.75f, 0.99804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.75f, 1.0f, 0.0f },
    { 0.75f, 0.75f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_30 = {
    { 0.5f, 0.5f, 1.0f, 0.0f },
    { 0.74804687f, 0.5f, 1.0f, 0.0f },
    { 0.5f, 0.74804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.74804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_31 = {
    { 0.5f, 0.75f, 1.0f, 0.0f },
    { 0.74804687f, 0.75f, 1.0f, 0.0f },
    { 0.5f, 0.99804687f, 1.0f, 0.0f },
    { 0.74804687f, 0.99804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_32 = {
    { 0.75f, 0.5f, 1.0f, 0.0f },
    { 0.99804687f, 0.5f, 1.0f, 0.0f },
    { 0.75f, 0.74804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.74804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_33 = {
    { 0.75f, 0.75f, 1.0f, 0.0f },
    { 0.99804687f, 0.75f, 1.0f, 0.0f },
    { 0.75f, 0.99804687f, 1.0f, 0.0f },
    { 0.99804687f, 0.99804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_90 = {
    { 0.25f, 0.875f, 1.0f, 0.0f },
    { 0.25f, 0.99804687f, 1.0f, 0.0f },
    { 0.37304687f, 0.875f, 1.0f, 0.0f },
    { 0.37304687f, 0.99804687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_91 = {
    { 0.375f, 0.75f, 1.0f, 0.0f },
    { 0.375f, 0.87304687f, 1.0f, 0.0f },
    { 0.49804687f, 0.75f, 1.0f, 0.0f },
    { 0.49804687f, 0.87304687f, 1.0f, 0.0f },    
};
static sceVu0FMATRIX _square_stq_92 = {
    { 0.375f, 0.875f, 1.0f, 0.0f },
    { 0.375f, 0.99804687f, 1.0f, 0.0f },
    { 0.49804687f, 0.875f, 1.0f, 0.0f },
    { 0.49804687f, 0.99804687f, 1.0f, 0.0f },    
};

static sceVu0FVECTOR* _square_stq_list[19] = {
    _square_stq_00, _square_stq_01, _square_stq_02, 
    _square_stq_03, _square_stq_10, _square_stq_11, 
    _square_stq_12, _square_stq_13, _square_stq_20,
    _square_stq_21, _square_stq_22, _square_stq_23, 
    _square_stq_30, _square_stq_31, _square_stq_32, 
    _square_stq_33, _square_stq_90, _square_stq_91, 
    _square_stq_92
};

static Smoke_Initialize_Parameter _flame_init_parm_table[4] = {
    {
        /* .particleDrawNum = */ 12,
        /* .flag = */ {0, 0, 1},
        /* .convergenceCoff = */ 1.0f,
        /* .convergenceCoffSub = */ -0.0099999997f,
        /* .gravitySuppressCoff = */ 0.09f,
        /* .baseAlpha = */ 50.0f,
        /* .baseScale = */ 600.0f,
        /* .baseTime = */ 1.5f,
        /* .randTimeWidth = */ 1.7999999f,
        /* .verocity0 = */ {100, 100, 800, 0},
        /* .lengthMax = */ {10, 250, 500, 0},
        /* .rgba = */ {30.0f, 30.0f, 30.0f, 0.0f},
    },
    {
        /* .particleDrawNum = */ 12,
        /* .flag = */ {1, 0, 0},
        /* .convergenceCoff = */ 1.0f,
        /* .convergenceCoffSub = */ -0.0099999997f,
        /* .gravitySuppressCoff = */ 0.09f,
        /* .baseAlpha = */ 50.0f,
        /* .baseScale = */ 600.0f,
        /* .baseTime = */ 1.5f,
        /* .randTimeWidth = */ 1.7999999f,
        /* .verocity0 = */ {800, 100, 100, 0},
        /* .lengthMax = */ {500, 250, 10, 0},
        /* .rgba = */ {30.0f, 30.0f, 30.0f, 0.0f},
    },
    {
        /* .particleDrawNum = */ 8,
        /* .flag = */ {0, 1, 0},
        /* .convergenceCoff = */ 1.0f,
        /* .convergenceCoffSub = */ -0.029999999f,
        /* .gravitySuppressCoff = */ 0.1f,
        /* .baseAlpha = */ 40.0f,
        /* .baseScale = */ 600.0f,
        /* .baseTime = */ 0.4f,
        /* .randTimeWidth = */ 1.7999999f,
        /* .verocity0 = */ {1000, 100, 1000, 0},
        /* .lengthMax = */ {100, 150, 100, 0},
        /* .rgba = */ {40.0f, 40.0f, 40.0f, 0.0f},
    },
    {
        /* .particleDrawNum = */ 12,
        /* .flag = */ {0, 1, 0},
        /* .convergenceCoff = */ 1.2f,
        /* .convergenceCoffSub = */ -0.0049999998f,
        /* .gravitySuppressCoff = */ 0.05f,
        /* .baseAlpha = */ 40.0f,
        /* .baseScale = */ 900.0f,
        /* .baseTime = */ 2.5f,
        /* .randTimeWidth = */ 1.5f,
        /* .verocity0 = */ {500, 100, 500, 0},
        /* .lengthMax = */ {100, 250, 100, 0},
        /* .rgba = */ {40.0f, 40.0f, 40.0f, 0.0f},
    }
};

static u_int Object_Initialize(HH_Object_Smoke_00* pThis, ImpactQueue_Element* pElement);

static void Particle_Initialize(HH_Object_Smoke_00_Particle* pParticle, Smoke_Initialize_Parameter* pParameter);

static void Particle_Motion(HH_Object_Smoke_00_Particle* pParticle, Smoke_Initialize_Parameter* pParameter, float* Position);

static void Particle_Calculator(HH_Object_Smoke_00_Particle* pParticle, float* Position);

static u_int Object_Draw(HH_Object_Smoke_00* pThis, ImpactQueue_Element* pElement);


#line 404
static u_int Object_Initialize(HH_Object_Smoke_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = true;
    u_int i;
    Smoke_Initialize_Parameter* pParameter;
    float ratio;
    
    pThis->Timer = 0.0f;
    
    
    pElement->Option.Int_Value[0] %= 4;
    
    
    
    pParameter = &_flame_init_parm_table[pElement->Option.Int_Value[0]];
    
    for (i = 0; i < pParameter->ParticleDraw_Num; i++) {
        HH_Object_Smoke_00_Particle* pParticle = &pThis->Particle[i];
    
        Particle_Initialize(pParticle, pParameter);
        
        
        
        
        ratio = (0.01f * (rand() % 100));
        
        pParticle->Time = pParticle->Life_Time * ratio;
        
    }
    
    
    pThis->Particle_DrawNum = 50;
    
    
    return result;
}

#pragma divbyzerocheck off

#line 449
static void Particle_Initialize(HH_Object_Smoke_00_Particle* pParticle, Smoke_Initialize_Parameter* pParameter) {
    float ratio;
    float length_max_pow_f = 0.5f * (pParameter->Length_Max[0] + pParameter->Length_Max[2]);

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
    pParticle->Texture_Kind = rand() % 19U;
    
    ratio = sceVu0InnerProduct(pParticle->Location, pParticle->Location) / length_max_pow_f;
    
    if (ratio > 1.0f)
        ratio = 1.0f;

    pParticle->Life_Time = pParameter->Base_Time + (pParameter->Rand_Time_Width * (1.0f - ratio));
}

#pragma divbyzerocheck on

#line 499
static void Particle_Motion(HH_Object_Smoke_00_Particle* pParticle, Smoke_Initialize_Parameter* pParameter, float* Position) {
    if (pParticle->Time > pParticle->Life_Time)
        Particle_Initialize(pParticle, pParameter);
    {
        float ratio;
        ratio = pParticle->Time / pParticle->Life_Time;
        
        
        Particle_Calculator(pParticle, Position);
        if (pParticle->Convergence_Coff > 0.0f)
            pParticle->Convergence_Coff = pParticle->Convergence_Coff + pParameter->Convergence_Coff_Sub;
        
        pParticle->Time += TIME_STEP_30FPS;
        pParticle->RGBA[3] = ratio * pParameter->Base_Alpha;
        pParticle->Scale = ratio * pParameter->Base_Scale;
    }
}

#line 527
static void Particle_Calculator(HH_Object_Smoke_00_Particle* pParticle, float* Position) {
    sceVu0FMATRIX time_mat;

    
    sceVu0UnitMatrix(time_mat);
    time_mat[0][0] = time_mat[2][2] =  pParticle->Time * pParticle->Convergence_Coff;
    
    time_mat[1][1] = pParticle->Time;
    time_mat[3][1]  = pParticle->Time * pParticle->Time;
    time_mat[3][3]  = 0;
    sceVu0ApplyMatrix(Position, time_mat, pParticle->Verocity_0);
}

#line 552
static u_int Object_Draw(HH_Object_Smoke_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = false;
    Smoke_Initialize_Parameter* pParameter = &_flame_init_parm_table[pElement->Option.Int_Value[0]];
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    sceVu0FVECTOR* pVertex = _square_00_vertex;
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX _lsm;
    sceVu0FMATRIX clip_mat;
    sceVu0FMATRIX _clip_mat;
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba;
    sceVu0FVECTOR* pStq;
    sceVu0IVECTOR position;
    sceVu0FVECTOR stq_dummy;
    u_int i;

    HH_ClassWrapper_WorldScreenMatrix_Get(_lsm);
    
    
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(_clip_mat);
    
    HH_Vif1PacketBuffer_GifTag_Open();

    for (i = 0; i < pParameter->ParticleDraw_Num; i++) {
        HH_Object_Smoke_00_Particle* pParticle = &pThis->Particle[i];
        Smoke_Initialize_Parameter * pParameter1 = pParameter; // ???
        
        Particle_Motion(pParticle, pParameter, position);
        
        
        HH_ClassWrapper_AlwaysFront_WorldView_Matrix_Get(lwm);
        
        
        sceVu0ScaleVector(lwm, lwm, pParticle->Scale);
        sceVu0ScaleVector(lwm[1], lwm[1], pParticle->Scale);
        sceVu0ScaleVector(lwm[2], lwm[2], pParticle->Scale);
        
        
        sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
        sceVu0TransMatrix(lwm, lwm, pParticle->Location);
        sceVu0TransMatrix(lwm, lwm, position);
        sceVu0MulMatrix(lsm, _lsm, lwm);
        
        
        sceVu0MulMatrix(clip_mat, _clip_mat, lwm);
        
        
        pStq = _square_stq_list[pParticle->Texture_Kind];
        sceVu0FTOI0Vector(rgba, pParticle->RGBA);
        
        HH_Vif1Packet_GeneralGifTag_Sprite_Open();
        ((u_long128*) pPk->pCurrent)[0] = *(u_long128*) rgba;
        
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[0], 0x3F);
        ((u_long128*) pPk->pCurrent)[1] = ((u_long128*) pStq)[0];
        ((u_long128*) pPk->pCurrent)[2] = *(u_long128*) xyzf;
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq_dummy, lsm, clip_mat, pVertex[3], 0x3F);
        ((u_long128*) pPk->pCurrent)[3] = ((u_long128*) pStq)[3];
        ((u_long128*) pPk->pCurrent)[4] = *(u_long128*) xyzf;
        ((u_long128*) pPk->pCurrent) += 5;
        sceVif1PkCloseGifTag(pPk);
    }
    HH_Vif1PacketBuffer_GifTag_Close();
   
    return result;
}

#line 638
u_int HH_Class_Prefix_Smoke_00(void) {
    u_int result = true;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;
        
    HH_Vif1PacketBuffer_GifTag_Open();
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(0, 0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP_1(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, 511, 0, 511, 0));
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 1, 0, 1, 128));
    #line 679
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 696
u_int HH_Class_Suffix_Smoke_00(void) {
    u_int result = true;

    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    
    return result;
}

#line 715
u_int HH_Class_Smoke_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Smoke_00* pThis;
    sceVu0FMATRIX clip_mat;


    
    
    result = true;
    pThis = pBlock;
    
    
    switch (pThis->Step) {
        case 0:
            
            Object_Initialize(pThis, pElement);
            
            
            if (pElement->Option.Float_Value[0] == 0.0f) {
            
                pThis->Step = 2;
            }
            
            else
                pThis->Step = 1;
            
            break;
        
        case 1:   
            if (pThis->Timer > pElement->Option.Float_Value[0]) 
                pThis->Step = 3;
            /* fallthrough */
        case 2:
            HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
        
            if (!(HH_ClassWrapper_Point_Clip_Judge(clip_mat, pElement->Option.Vector[0], 1))) {
            
                Object_Draw(pThis, pElement);
            }
            
            pThis->Timer += TIME_STEP_30FPS;
            break;
        default:
        case 3:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}
