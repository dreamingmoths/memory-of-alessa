#include "common.h"
#include "Effect2/hh_class_water_00.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_dbg_wrapper.h"
#include "libgraph.h"

static Wave_Element* Free_WaveElement_Search(HH_Object_Water_00* pThis);
static Wave_Element* Oldest_WaveElement_Search(HH_Object_Water_00* pThis);
static u_int WaveElement_Addition(HH_Object_Water_00* pThis, Wave_Element* pElement);
static void Grid_Work_Initialize(HH_Object_Water_00* pThis);
static u_int Object_Initialize(HH_Object_Water_00* pThis);
static u_int Object_Motion_00(HH_Object_Water_00* pThis);
static float Specular_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector);
static void SpecularRGBA_Calculator(int* iRGBA, float* RGBA_Base, float* RGBA_Specular_Base, float Specular_Ratio);
static u_int Object_Draw(HH_Object_Water_00* pThis, ImpactQueue_Element* pElement);

static Wave_Element* Free_WaveElement_Search(HH_Object_Water_00* pThis) {
    Wave_Element* pElement; // r5
    u_int i = 0;
    Wave_Element* result = NULL; // r2

    for (i = 0; i < 4; i++) {
        pElement = &pThis->Wave_Info[i];

        if (!pElement->Enable) {
            result = pElement;
            break;
        }
    }

    return result;
}

static Wave_Element* Oldest_WaveElement_Search(HH_Object_Water_00* pThis) {
    Wave_Element* result = NULL; // r2
    u_int i;                     // r6
    float time = 0.0f;           // r29
    Wave_Element* pElement;      // r5
    for (i = 0; i < 4; i++) {
        pElement = &pThis->Wave_Info[i];

        if (pThis->Wave_Info[i].Enable) {
            if (time < pElement->Timer) {
                time = pElement->Timer;
                result = pElement;
            }
        }
    }
    return result;
}

static u_int WaveElement_Addition(HH_Object_Water_00* pThis, Wave_Element* pElement) {
    u_int result;                                                 // r2
    Wave_Element* pFree_Element = Free_WaveElement_Search(pThis); // r2

    if (pFree_Element == NULL) {
        pFree_Element = Oldest_WaveElement_Search(pThis);
    }
    word_struct_copy(pFree_Element, pElement, sizeof(Wave_Element));
    result = 1;
    return result;
}

void Grid_Work_Initialize(HH_Object_Water_00* pThis) {
    memset(pThis->Grid_Y_Value, 0, sizeof(pThis->Grid_Y_Value));
}

static u_int Object_Initialize(HH_Object_Water_00* pThis) {
    Wave_Element Element0;
    Wave_Element Element1;
    Wave_Element Element2;

    pThis->Timer = 0.0;

    pThis->Motion_Step = 0;

    Element0.Enable = 1;
    Element0.Impact_Grid_Index[0] = 24;
    Element0.Impact_Grid_Index[1] = 24;
    Element0.Max_Distance0 = 1800.0;
    Element0.Lost_Time = 15.0;
    Element0.Arrival = 50.0;
    Element0.Omega = 9.424778;
    Element0.Verocity = 400.0;

    WaveElement_Addition(pThis, &Element0);

    Element1.Enable = 1;
    Element1.Impact_Grid_Index[0] = 38;
    Element1.Impact_Grid_Index[1] = 38;
    Element1.Max_Distance0 = 1200.0;
    Element1.Lost_Time = 12.0;
    Element1.Arrival = 40.0;
    Element1.Omega = 10.681415;
    Element1.Verocity = 500.0;

    WaveElement_Addition(pThis, &Element1);

    Element2.Enable = 1;
    Element2.Impact_Grid_Index[0] = 10;
    Element2.Impact_Grid_Index[1] = 38;
    Element2.Max_Distance0 = 1500.0;
    Element2.Lost_Time = 12.0;
    Element2.Arrival = 50.0;
    Element2.Omega = 15.707963;
    Element2.Verocity = 300.0;

    WaveElement_Addition(pThis, &Element2);

    return 1;
}

u_int Object_Motion_00(HH_Object_Water_00* pThis) {
    u_int result = 0;                                                    // r2
    float* pCurr_Grid_Y = pThis->Grid_Y_Value[pThis->CurrentBuffer];     // r2
    float* pPrev_Grid_Y = pThis->Grid_Y_Value[pThis->CurrentBuffer ^ 1]; // r5
    u_int x_index;                                                       // r6
    u_int z_index;                                                       // r7
    float* pCurr_Grid_Y_C;                                               // r2 @unused-dwarf-symbol
    float* pPrev_Grid_Y_C;                                               // r2 @unused-dwarf-symbol
    u_int table_index;                                                   // r3
    float depth;                                                         // r1
    static float dev_0_105 = 2.0f;
    static float dev_1_106 = 16.0f;

    for (z_index = 1; z_index < HH_WATER_00_GRID_SIZE - 1; z_index++) {
        for (x_index = 1; x_index < HH_WATER_00_GRID_SIZE - 1; x_index++) {
            table_index = HH_WATER_00_GRID_INDEX_GET(x_index, z_index);
            depth = pCurr_Grid_Y[table_index - 1];

            depth += pCurr_Grid_Y[table_index + 1];
            depth += pCurr_Grid_Y[HH_WATER_00_GRID_INDEX_GET(x_index, z_index - 1)];
            depth += pCurr_Grid_Y[HH_WATER_00_GRID_INDEX_GET(x_index, z_index + 1)];

            depth /= dev_0_105;
            depth -= pPrev_Grid_Y[table_index];

            depth -= depth / dev_1_106;
            pPrev_Grid_Y[table_index] = depth;
        }
    }

    return result;
}

float Specular_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector) {
    float result;                      // r29+0x60
    float specular_coefficient = 1.0f; // r29+0x60
    float input_light_power;           // r29+0x60
    float reverse_light_dir[4];        // r29+0x40
    float cos_theta;                   // r29+0x60
    float cos_beta;                    // r29+0x60
    float cos_beta_min = 0.939692f;    // r29+0x60
    float tmp_vec[4];                  // r29+0x50;

    /* phong model specular reflection model */
    /* R = 2n(dot(n, L)) - L */
    cos_theta = sceVu0InnerProduct(Light_Direction, Normal_Vector);
    if (cos_theta < 0.0f) {
        cos_theta = -cos_theta;
    }
    sceVu0ScaleVectorXYZ(tmp_vec, Normal_Vector, 2.0f * cos_theta);
    sceVu0SubVector(reverse_light_dir, tmp_vec, Light_Direction);
    sceVu0Normalize(reverse_light_dir, reverse_light_dir);

    cos_beta = sceVu0InnerProduct(reverse_light_dir, View_Direction);
    if (cos_beta < 0.0f) {
        cos_beta = -cos_beta;
    }
    if (cos_beta < cos_beta_min) {
        result = 0.0f;
    } else {
        result = 1.0f - ((1.0f - cos_beta) / (1 - cos_beta_min));
    }
    return result * specular_coefficient;
}

void SpecularRGBA_Calculator(int* iRGBA, float* RGBA_Base, float* RGBA_Specular_Base, float Specular_Ratio) {
    float brightness = 255.0f;

    asm("lqc2 vf30, 0(a1);\
         lqc2 vf31, 0(a2);\
         mfc1 t0, f12;\
         mfc1 t1, %0;\
         qmtc2.ni t0, vf29;\
         ctc2.ni t1, vi21;\
         vmulx.xyzw vf31, vf31, vf29x;\
         vadd.xyzw vf31, vf30, vf31;\
         vmaxx.xyzw vf31, vf31, vf0x;\
         vminii.xyzw vf31, vf31, I;\
         vftoi0.xyzw vf31, vf31;\
         sqc2 vf31, 0(a0);\
    " ::"f"(brightness) : "t0", "t1", "memory");
}

static u_long _GifTag_152[2] = {
    SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
    GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036ED90
    static u_long _GifTag_Tri_153[2] = {
        SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_LINESTRIP, 1, 0, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
        GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036EDA0
static float Light_Base_154[4] = {16.0f, 16.0f, 16.0f, 0.0f}; // @ 0x0036EDB0
static float Amb_Base_155[4] = {64.0f, 64.0f, 64.0f, 0.0f};   // @ 0x0036EDC0
static float Ambient_Color2_156[4] = {19.0f, 19.0f, 19.0f, 255.0f};                                         // @ 0x0036EDD0
static float SpecularRgba_157[4] = {255.0f, 255.0f, 255.0f, 64.0f};                                         // @ 0x0036EDE0
static float amb_alpha_158 = 32.0f;                           // @ 0x0036EDF0
static float light_alpha_159 = 128.0f;                        // @ 0x0036EDF8
#ifdef NON_MATCHING
u_int Object_Draw(HH_Object_Water_00* pThis, ImpactQueue_Element* pElement) {

    u_int result = 0;                             // r2
    sceVif1Packet* pPk;                           // r16
    u_int vertex_num;                             // r2 @unused-dwarf-symbol
    u_int x_grid_max = HH_WATER_00_GRID_SIZE;     // r2
    u_int z_grid_max = HH_WATER_00_GRID_SIZE - 1; // r2
    u_int x_index;                                // r17
    u_int z_index;                                // r18
    u_int prim_type;                              // r2
    sceVu0FMATRIX lwm;                            // r29+0x90
    sceVu0FMATRIX lsm;                            // r29+0xD0
    sceVu0FMATRIX clip_mat;                       // r29+0x110
    float* pGrid_Y;                               // r19
    sceVu0FVECTOR Ambient_Color;                  // r29+0x150
    sceVu0FVECTOR view_dir;                       // r29+0x160
    sceVu0FVECTOR pos;                            // r29+0x170
    sceVu0FVECTOR dir;                            // r29+0x180
    sceVu0FVECTOR Light_Color;                    // r29+0x190
    sceVu0FVECTOR Parameter;                      // r29+0x1A0
    float far_z;                                  // r20
    float cos_theta;                              // r21
    u_int* pPk_Current;                           // r20
    u_int* pPk_End;                               // r2
    u_int Clip_Mask = 0x3f;                       // r2

    pPk = HH_Vif1Packet_Current_Get();

    pGrid_Y = pThis->Grid_Y_Value[pThis->CurrentBuffer ^ 1];

    pPk_Current = NULL;

    HH_ClassWrapper_ViewDirection_Get(view_dir);
    HH_ClassWrapper_AmbientColor_Get(Ambient_Color);
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, Light_Color, Parameter);
    sceVu0MulVector(Light_Color, Light_Color, Light_Base_154);

    sceVu0MulVector(Ambient_Color, Ambient_Color, Amb_Base_155);

    Ambient_Color[3] = amb_alpha_158;
    Light_Color[3] = light_alpha_159;

    cos_theta = Parameter[0]; // r21
    far_z = Parameter[2];     // r20

    sceVu0Normalize(dir, dir);

    sceVu0SubVector(pos, pos, pElement->Option.Vector[0]);

    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);

    sceVu0UnitMatrix(lwm);

    sceVu0TransMatrix(lwm, lwm, pElement->Option.Vector[0]);
    sceVu0MulMatrix(lsm, lsm, lwm);

    HH_ClassWrapper_ViewFrustum_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);

    HH_Vif1PacketBuffer_GifTag_Open();

    sceVif1PkCloseGifTag(pPk);

    for (z_index = 0; z_index < z_grid_max; z_index++) {
        sceVu0FVECTOR Grid_Vertex0 = {500.0f, 0.0f, 500.0f * z_index, 1.0f};       // r29+0x1B0
        sceVu0FVECTOR Grid_Vertex1 = {500.0f, 0.0f, 500.0f * (z_index + 1), 1.0f}; // r29+0x1C0
        sceVu0FVECTOR Grid_Vertex2 = {500.0f, 0.0f, 500.0f * z_index, 1.0f};       // r29+0x1D0

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri_153);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, 0x30, 3, 3);
        }

        for (x_index = 0; x_index < x_grid_max; x_index++) {
            sceVu0FVECTOR Rgba;   // r29+0x1E0
            sceVu0IVECTOR xyzf;   // r29+0x1F0
            sceVu0IVECTOR rgba;   // r29+0x200
            u_int addr;           // r2
            sceVu0FVECTOR vec0;   // r29+0x210
            sceVu0FVECTOR vec1;   // r29+0x220
            sceVu0FVECTOR n0;     // r29+0x230
            float specular_ratio; // r22
            sceVu0FVECTOR stq0;   // r29+0x240
            sceVu0FVECTOR stq1;   // r29+0x250
            float color_scale;    // r29+0x260

            Grid_Vertex0[0] = Grid_Vertex1[0] = 500.0f * x_index;

            Grid_Vertex2[0] = (x_index + 1) % 48 * 500.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_00_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_00_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_00_GRID_INDEX_GET((x_index + 1) % 48, z_index)];

            stq0[0] = stq1[0] = Grid_Vertex0[0] / 12000.0f;
            stq0[1] = Grid_Vertex0[2] / 11750.0f;
            stq1[1] = Grid_Vertex1[2] / 11750.0f;

            sceVu0SubVector(vec0, Grid_Vertex2, Grid_Vertex0);
            sceVu0SubVector(vec1, Grid_Vertex1, Grid_Vertex0);

            sceVu0Normalize(vec0, vec0);
            sceVu0Normalize(vec1, vec1);
            vec0[3] = 1.0f;
            vec1[3] = 1.0f;

            sceVu0OuterProduct(n0, vec0, vec1);

            specular_ratio = Specular_Calculator(view_dir, dir, n0);

            if (z_index == 0) {
                float color_scale;
                HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq0, lsm, clip_mat, Grid_Vertex0, Clip_Mask);

                color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, Grid_Vertex0, cos_theta, far_z);

                color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

                if (color_scale == 0.0f) {
                    sceVu0FTOI0Vector(rgba, Ambient_Color2_156);
                } else {

                    sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

                    sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                    sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

                    if (Grid_Vertex0[1] != 0.0f) {
                        SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba_157, specular_ratio);
                    } else {
                        sceVu0FTOI0Vector(rgba, Rgba);
                    }
                }

                *(u_long128*)pPk->pCurrent = *(u_long128*)stq0;
                ((u_long128*)pPk->pCurrent)++;
                *(u_long128*)pPk->pCurrent = *(u_long128*)rgba;
                ((u_long128*)pPk->pCurrent)++;
                *(u_long128*)pPk->pCurrent = *(u_long128*)xyzf;
                ((u_long128*)pPk->pCurrent)++;
            } else {

                (u_long128*)pPk->pCurrent += 3;
            }

            HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq1, lsm, clip_mat, Grid_Vertex1, Clip_Mask);

            color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, Grid_Vertex1, cos_theta, far_z);

            color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

            if (color_scale == 0.0f) {
                sceVu0FTOI0Vector(rgba, Ambient_Color2_156);
            } else {

                sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

                sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

                if (Grid_Vertex1[1] != 0.0f) {
                    SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba_157, specular_ratio);
                } else

                    sceVu0FTOI0Vector(rgba, Rgba);
            }

            if (x_index == 0) {
                pPk_Current = pPk->pCurrent;
            }

            *(u_long128*)pPk->pCurrent = *(u_long128*)stq1;
            ((u_long128*)pPk->pCurrent)++;
            *(u_long128*)pPk->pCurrent = *(u_long128*)rgba;
            ((u_long128*)pPk->pCurrent)++;
            *(u_long128*)pPk->pCurrent = *(u_long128*)xyzf;
            ((u_long128*)pPk->pCurrent)++;
        }
        sceVif1PkCloseGifTag(pPk);
    }
    pPk_End = pPk->pCurrent;

    HH_ClassWrapper_Packet_ADC_Flag_OnceMore_Set(pPk_End, x_grid_max, z_grid_max);

    sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_152);

    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}
#else
sceVu0FVECTOR GridVertex0 = {500.0f, 0.0f, 0.0f, 1.0f};
sceVu0FVECTOR GridVertex1 = {500.0f, 0.0f, 0.0f, 1.0f};
sceVu0FVECTOR GridVertex2 = {500.0f, 0.0f, 0.0f, 1.0f};
INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_water_00", Object_Draw);
#endif

u_int HH_Class_Prefix_Water_00(void) {
    u_int result = 1;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_00_TEX_ID, HH_WATER_00_CLUT_ID));
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_FALSE);
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Suffix_Water_00(void) {
    u_int result = 1;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Water_00(void* pBlock, ImpactQueue_Element* pElement) {
    u_int result = true;
    HH_Object_Water_00* pThis = pBlock;

    switch (pThis->Step) { /* irregular */
        case HH_WATER_00_STEP_INIT:
            Object_Initialize(pThis);
            Grid_Work_Initialize(pThis);
            pThis->Step = 1;
            break;

        case HH_WATER_00_STEP_MOTION:
            pThis->CurrentBuffer ^= 1;
            Object_Motion_00(pThis);
            HH_DBG_Wrapper_T0_COUNT_Get();
            Object_Draw(pThis, pElement);
            HH_DBG_Wrapper_T0_COUNT_Delta();
            pThis->Timer += 1.0f / 30.f;
            break;

        case HH_WATER_00_STEP_DRAW:
            Object_Draw(pThis, pElement);
            break;

        default:
        case HH_WATER_00_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }

    return result;
}
