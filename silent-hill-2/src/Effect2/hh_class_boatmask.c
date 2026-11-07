#include "sh2_common.h"
#include "sce/libvifpk.h"
#include "Chacter/m3_sc.h"
#include "Chacter/character.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_boatmask.h"

static u_int Object_Initialize(HH_Object_Boat_Mask* pThis, ImpactQueue_Element* pElement);
static u_int Object_Draw(HH_Object_Boat_Mask* pThis, ImpactQueue_Element* pElement);

static sceVu0FMATRIX _square_stq;
static sceVu0FMATRIX _square_00_vertex;


#line 203
static u_int Object_Initialize(HH_Object_Boat_Mask* pThis, ImpactQueue_Element* pElement) {
    u_int result = 1;
    
    pThis->Timer = 0.0f;
    
    return result;
}

#line 223
static u_int Object_Draw(HH_Object_Boat_Mask* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0;
    sceVif1Packet *pPk = HH_Vif1Packet_Current_Get();
    sceVu0FVECTOR *pVertex = _square_00_vertex;
    sceVu0FVECTOR Rgba = { 128.0f, 128.0f, 128.0f, 255.0f };
    static u_int div_i = 4, div_j = 8;
    sceVu0FVECTOR *pStq = _square_stq;
    u_int vertex_num, v, i, j;
    sceVu0FMATRIX lwm, lsm, clip_mat;
    sceVu0FVECTOR stq;
    sceVu0IVECTOR xyzf, rgba;
    float x_w, z_w, s_w, t_w;
    SubCharacter *pSub_Char; 
    sceVu0FMATRIX _lwm;

    x_w = (pVertex[3][1] - pVertex[0][1]) / div_i;
    z_w = (pVertex[0][2] - pVertex[3][2]) / div_j;
    s_w = (pStq[2][0] - pStq[1][0]) / div_i;
    t_w = (pStq[2][1] - pStq[1][1]) / div_j;
    pSub_Char = shCharacterGetSubCharacter(267, -1);
    
    if (pSub_Char == NULL) {
        return result;
    }
    
    
    
    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);
    
    sceVu0UnitMatrix(lwm);
    
    
    
    
    
    shCharacterGetPartsMatrixForShadow(_lwm, 267, 0, 0);
    sceVu0MulMatrix(lwm, lwm, _lwm);
    
    sceVu0MulMatrix(lsm, lsm, lwm);
    
    
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);
    
    
    HH_Vif1PacketBuffer_GifTag_Open();
    
    sceVu0FTOI0Vector(rgba, Rgba);

    for (j = 0; j < div_j; j++) {
        sceVu0FVECTOR vec[2] = {
            { 0, 0, z_w * (float)(j + 0), 1 },
            { 0, 0, z_w * (float)(j + 1), 1 }
        };
        
        
        sceVu0FVECTOR stq_list[2] = { 
            { pStq[1][0], t_w * (float)(j + 0), 1, 0 },
            { pStq[1][0], t_w * (float)(j + 1), 1, 0 }
        };
        
        
        
        sceVu0AddVector(&vec[0][0], &vec[0][0], pVertex[1]);
        sceVu0AddVector(&vec[1][0], &vec[1][0], pVertex[1]);
        
        HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open();
        for (i = 0; i <= div_i; i++) {
            float now_x = x_w * i;
            float now_s = s_w * i;
            
            
            
            
            
            
            
            vec[0][1] += now_x;
            vec[1][1] += now_x;
            stq_list[0][0] += now_s;
            stq_list[1][0] += now_s;

            
            vertex_num = 2;
            for (v = 0; v < vertex_num; v++) {
                sceVu0CopyVector(stq, stq_list[v]);
                
                HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip(xyzf, stq, lsm, clip_mat, vec[v]);
               
                ((u_long128*)pPk->pCurrent)[0] = ((u_long128*)stq)[0];
                ((u_long128*)pPk->pCurrent)[1] = ((u_long128*)rgba)[0];
                ((u_long128*)pPk->pCurrent)[2] = ((u_long128*)xyzf)[0];
                ((u_long128*)pPk->pCurrent) += 3;
            }
        }
        sceVif1PkCloseGifTag(pPk);
    }    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 342
u_int HH_Class_Prefix_Boat_Mask(void) {
    u_int result = 1;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;

    HH_Vif1PacketBuffer_GifTag_Open();
    *(u_long128*)pPk->pCurrent = *HH_ClassWrapper_GS_EnvironmentRegister_Frame_AlphaMask_Get();

    pPk->pCurrent[1] = 0;
    ((u_long128*)pPk->pCurrent)++;
    
    
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(20, 0);
    
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0 & ~SCE_GS_SET_TEX0(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    
        
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA_1(0, 2, 0, 1, 128));
    
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST_1(0, 1, 0, 0, 0, 0, 1, 1));
    
        
        
        






        
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}

#line 390
u_int HH_Class_Suffix_Boat_Mask(void) {
    u_int result = 1;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();

    HH_Vif1PacketBuffer_GifTag_Open();
    
    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    *(u_long128*)pPk->pCurrent = *HH_ClassWrapper_GS_EnvironmentRegister_Frame_AlphaMask_Get();
    ((u_long128*)pPk->pCurrent)++;
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST_1(0, 1, 0, 0, 0, 0, 1, 2));
    
    
    
    
    
    
    
    
    
    
    
    
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return 1;
}

#line 428
u_int HH_Class_Boat_Mask(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result;
    HH_Object_Boat_Mask* pThis = pBlock;

    
    
    
    result = 1;
    
    
    switch (pThis->Step) {
        
        case 0:
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;
        
        case 1:
            Object_Draw(pThis, pElement);
            
            break;
        
        case 2: default:
            pThis->Header.Enable = NULL;
            result = 0;
            break;
    }
    return result;
}
