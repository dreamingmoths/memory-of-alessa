#include "Effect2/hh_class_blood_footmark_00.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_class_wrapper.h"
#include "libvifpk.h"

extern int rand(void);

static u_int Object_Initialize(HH_Object_Blood_FootMark_00* pThis);
static u_int Object_Draw(HH_Object_Blood_FootMark_00* pThis, ImpactQueue_Element* pElement);

static sceVu0FMATRIX _square_00_vertex;
static sceVu0FMATRIX _square_00_stq;
static sceVu0FMATRIX _square_01_stq;
static sceVu0FMATRIX _square_10_stq;
static sceVu0FMATRIX _square_11_stq;
static float (* _square_0x_stq_list[2])[4];
static float (* _square_1x_stq_list[2])[4];
static sceVu0FMATRIX _square_00_rgba;
static Vertex_Infomeation_List _vertex_info_list[2];

static u_int Object_Initialize(HH_Object_Blood_FootMark_00* pThis) {
    u_int result = 1;

    pThis->Timer = 0.0f;
    pThis->Vertex_Kind = rand() % 2U;

    return result;
}

static u_int Object_Draw(HH_Object_Blood_FootMark_00* pThis, ImpactQueue_Element* pElement) {
    u_int result = 0;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    Vertex_Infomeation_List* pInfo = &_vertex_info_list[pElement->Option.Int_Value[0]];
    float (* pVertex)[4];
    float (* pRgba)[4];
    float (* pStq)[4];
    u_int vertex_num;
    u_int i;
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX clip_mat;
    sceVu0FVECTOR Rgba;
    sceVu0FVECTOR stq;
    sceVu0IVECTOR xyzf;
    sceVu0IVECTOR rgba;
    float ratio;

    pVertex = pInfo->pVertex_List;
    pRgba = pInfo->pRgba_List;
    pStq = pInfo->pStq_List[pThis->Vertex_Kind];
    vertex_num = pInfo->Vertex_Max;
    
    sceVu0CopyVector(Rgba, *pRgba);
    Rgba[3] *= pElement->Option.Float_Value[1];

    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);
    sceVu0UnitMatrix(lwm);
    sceVu0RotMatrixY(lwm, lwm, pElement->Option.Float_Value[0]);
    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0MulMatrix(lsm, lsm, lwm);
    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);

    HH_Vif1PacketBuffer_GifTag_Open();
    HH_Vif1Packet_GeneralGifTag_TriangleStrip_Open();

    for(i = 0; i < vertex_num; i++){
        sceVu0CopyVector(stq, pStq[i]);
        HH_ClassWrapper_Transform_PerspectiveProjection_Clip_forTriangleStrip(xyzf, stq, lsm, clip_mat, pVertex[i]);

        if(i == 0){
            ratio = HH_ClassWrapper_FogParameter_A_Get() + (stq[2] * HH_ClassWrapper_FogParameter_B_Get()) ;
            sceVu0ScaleVector(Rgba, Rgba, HH_ClassWrapper_Float_Clamp(ratio, 0.0f, 255.0f)/ 255.0f);
            sceVu0FTOI0Vector(rgba, Rgba);
        }
        xyzf[2] += 0xA0;
        
        ((u_long128 *)pPk->pCurrent)[0] = *(u_long128 *)(&stq);
        ((u_long128 *)pPk->pCurrent)[1] = *(u_long128 *)(&rgba);
        ((u_long128 *)pPk->pCurrent)[2] = *(u_long128 *)(&xyzf);
 
        pPk->pCurrent += 0xC;
    }

    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}

u_int HH_Class_Prefix_Blood_FootMark_00() {
    u_long tex0;
    sceVif1Packet* pPk;
    u_int result = 1;

    pPk = HH_Vif1Packet_Current_Get();
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(0,0);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(2, 16, 0, 0, 0x80));
    sceVif1PkCloseGifTag(pPk);
    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}

u_int HH_Class_Suffix_Blood_FootMark_00() {
    u_int result = 1;

    HH_Vif1Packet_GeneralGifTag_GS_AD_Open();
    return result;
}

u_int HH_Class_Blood_FootMark_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = 1;
    HH_Object_Blood_FootMark_00* pThis = pBlock;
    
    switch(pThis->Step){
        case 0:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;
        case 1:
            Object_Draw(pThis, pElement);
            pThis->Timer += 1.0/30.0;
            
            if(pThis->Timer > 10.0f){
                pElement->Option.Float_Value[1] -= 0.01f;

                if(pElement->Option.Float_Value[1] <= 0.0f){
                    pElement->Option.Float_Value[1] = 0.0f;
                    pThis->Step = 2;
                }
            }
            break;
        default:
        case 2:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    return result;
}
