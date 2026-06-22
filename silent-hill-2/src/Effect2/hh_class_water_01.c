#include "sh2_common.h"
#include "Effect2/hh_class_water_01.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"
#include "libvifpk.h"

#pragma divbyzerocheck off

static void Grid_Work_Initialize(HH_Object_Water_01* pThis);
static u_int Object_Initialize(HH_Object_Water_01* pThis);
static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement, WaveArea_Infomeation* pInfo, u_int* pX_Index, u_int* pZ_Index);
static float Specular_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector);
static void SpecularRGBA_Calculator(int* iRGBA, float* RGBA_Base, float* RGBA_Specular_Base, float Specular_Ratio);
static u_int Object_Draw(HH_Object_Water_01* pThis, float* pGrid_Y_Value, float* WorldLocation, u_int Grid_X_Max, u_int Grid_Z_Max);

static u_int _area00_view_list_0x0036EE30[3] = {0, 1, 2};
static u_int _area01_view_list_0x0036EE40[4] = {0, 1, 2, 3};
static u_int _area02_view_list_0x0036EE50[4] = {1, 2, 3, 4};
static u_int _area03_view_list_0x0036EE60[3] = {2, 3, 4};
static u_int _area04_view_list_0x0036EE70[3] = {2, 3, 4};

static WaveArea_Infomeation _Area_Info_List_0x0036EE80[5] = {
    {/* .World_Location = */ {-142800.0f, -200.0f, 43400.0f, 1.0f},
     /* .Grid_WH = */ {6200.0f, 0.0f, 1400.0f, 200.0f},
     /* .Grid_Index = */ {31, 7},
     /* .pViewArea_List = */ &_area00_view_list_0x0036EE30,
     /* .ViewArea_List_Max = */ 3,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {-138000.0f, -200.0f, 44600.0f, 1.0f},
     /* .Grid_WH = */ {1400.0f, 0.0f, 5000.0f, 200.0f},
     /* .Grid_Index = */ {7, 25},
     /* .pViewArea_List = */ &_area01_view_list_0x0036EE40,
     /* .ViewArea_List_Max = */ 4,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {-140000.0f, -200.0f, 49400.0f, 1.0f},
     /* .Grid_WH = */ {3400.0f, 0.0f, 1400.0f, 200.0f},
     /* .Grid_Index = */ {17, 7},
     /* .pViewArea_List = */ &_area02_view_list_0x0036EE50,
     /* .ViewArea_List_Max = */ 4,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {-141200.0f, -200.0f, 49400.0f, 1.0f},
     /* .Grid_WH = */ {1400.0f, 0.0f, 2600.0f, 200.0f},
     /* .Grid_Index = */ {7, 13},
     /* .pViewArea_List = */ &_area03_view_list_0x0036EE60,
     /* .ViewArea_List_Max = */ 3,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {-142400.0f, -200.0f, 50600.0f, 1.0f},
     /* .Grid_WH = */ {1400.0f, 0.0f, 6200.0f, 200.0f},
     /* .Grid_Index = */ {7, 31},
     /* .pViewArea_List = */ &_area04_view_list_0x0036EE70,
     /* .ViewArea_List_Max = */ 3,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL}};

static WaveArea_GridLink_Infomeation _area00_01_grid_link_list_0x0036F150[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 1,
     /* .Length = */ 7,
     /* .X_Index_Max = */ {31, 7},
     /* .X_Index_Start = */ {24, 0},
     /* .Z_Index_Start = */ {6, 0}}};

static WaveArea_GridLink_Infomeation _area01_02_grid_link_list_0x0036F180[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 1,
     /* .Length = */ 7,
     /* .X_Index_Max = */ {7, 17},
     /* .X_Index_Start = */ {0, 10},
     /* .Z_Index_Start = */ {24, 0}}};

static WaveArea_GridLink_Infomeation _area02_03_grid_link_list_0x0036F1B0[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 7,
     /* .X_Index_Max = */ {17, 7},
     /* .X_Index_Start = */ {0, 6},
     /* .Z_Index_Start = */ {0, 0}}};

static WaveArea_GridLink_Infomeation _area03_04_grid_link_list_0x0036F1E0[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 7,
     /* .X_Index_Max = */ {7, 7},
     /* .X_Index_Start = */ {0, 6},
     /* .Z_Index_Start = */ {6, 0}}};

static float cos_beta_min_72_0x0036F208 = 0.96592498f;

void Grid_Work_Initialize(HH_Object_Water_01* pThis) {
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));

    memset(pThis->Area01_Grid_Y_Value, 0, sizeof(pThis->Area01_Grid_Y_Value));
    memset(pThis->Area02_Grid_Y_Value, 0, sizeof(pThis->Area02_Grid_Y_Value));
    memset(pThis->Area03_Grid_Y_Value, 0, sizeof(pThis->Area03_Grid_Y_Value));
    memset(pThis->Area04_Grid_Y_Value, 0, sizeof(pThis->Area04_Grid_Y_Value));
}

static u_int Object_Initialize(HH_Object_Water_01* pThis /* r16 */) {
    u_int i;          // r5
    u_int result = 1; // r2

    pThis->Timer = 0.0f;

    pThis->Motion_Step = 0;

    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0.0f});

    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[1] = pThis->Area01_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[2] = pThis->Area02_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[3] = pThis->Area03_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[4] = pThis->Area04_Grid_Y_Value;

    for (i = 0; i < HH_WATER_01_TABLE_MAX; i++) {
        pThis->Area_WavePostTime[i] = 0.0f;
        _Area_Info_List_0x0036EE80[i].pGrid_Y_Value = pThis->pArea_Grid_Y_Value_Table[i];
    }

    _area00_01_grid_link_list_0x0036F150->pGrid_Y_Value_Link[0] = pThis->Area00_Grid_Y_Value;
    _area00_01_grid_link_list_0x0036F150->pGrid_Y_Value_Link[1] = _area01_02_grid_link_list_0x0036F180->pGrid_Y_Value_Link[0] = pThis->Area01_Grid_Y_Value;

    _area01_02_grid_link_list_0x0036F180->pGrid_Y_Value_Link[1] = _area02_03_grid_link_list_0x0036F1B0->pGrid_Y_Value_Link[0] = pThis->Area02_Grid_Y_Value;

    _area02_03_grid_link_list_0x0036F1B0->pGrid_Y_Value_Link[1] = _area03_04_grid_link_list_0x0036F1E0->pGrid_Y_Value_Link[0] = pThis->Area03_Grid_Y_Value;

    _area03_04_grid_link_list_0x0036F1E0->pGrid_Y_Value_Link[1] = pThis->Area04_Grid_Y_Value;

    return result;
}

static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement /* r3 */, WaveArea_Infomeation* pInfo /* r2 */, u_int* pX_Index /* r17 */, u_int* pZ_Index /* r16 */) {
    float check_pos[4]; // r29+0x30

    sceVu0SubVector(check_pos, pElement->Option.Vector[0], pInfo->World_Location);
    *pX_Index = (u_int)(check_pos[0] / 200.0f);
    *pZ_Index = (u_int)(check_pos[2] / 200.0f);
}

float Specular_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector) {
    float result;                      // r29+0x60
    float specular_coefficient = 1.0f; // r29+0x60
    float input_light_power;           // r29+0x60
    float reverse_light_dir[4];        // r29+0x40
    float cos_theta;                   // r29+0x60
    float cos_beta;                    // r29+0x60
    float tmp_vec[4];                  // r29+0x50;
    /* static cos_beta_min_72_0x0036F208 */

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
    if (cos_beta < cos_beta_min_72_0x0036F208) {
        result = 0.0f;
    } else {

        result = 1.0f - ((1.0f - cos_beta) / (1 - cos_beta_min_72_0x0036F208));
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
#define HH_WATER_01_GRID_INDEX_GET(_x, _z) x_grid_max * (_z) + (_x)

/* @note: the function does not match when these statics are inside of `Object_Draw` */
static u_long _GifTag[2] = {
    SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
    GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F210
static u_long _GifTag_Tri[2] = {
    SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
    GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F220
static sceVu0FVECTOR Light_Base = {30.0f, 30.0f, 30.0f, 0.0f};                                              // @ 0x0036F230
static sceVu0FVECTOR Amb_Base = {64.0f, 64.0f, 64.0f, 0.0f};                                                // @ 0x0036F240
static float Ambient_Color2[4] = {19.0f, 19.0f, 19.0f, 255.0f};                                             // @ 0x0036F250
static float SpecularRgba[4] = {96.0f, 96.0f, 96.0f, 96.0f};                                                // @ 0x0036F260
static float amb_alpha_0x0036F270 = 60.0f;                                                                  // @ 0x0036F270
static float light_alpha_0x0036F278 = 120.0f;                                                               // @ 0x0036F278

static u_int Object_Draw(HH_Object_Water_01* pThis /* r22 */, float* pGrid_Y_Value /* r21 */, float* WorldLocation /* r17 */, u_int Grid_X_Max /* r20 */, u_int Grid_Z_Max /* r18 */) {
    // Range: 0x25CB00 -> 0x25D360
    u_int result = 0;               // r2
    sceVif1Packet* pPk;             // r16
    u_int vertex_num;               // r2
    u_int x_grid_max;               // r2
    u_int z_grid_max;               // r29+0xB0
    u_int x_index;                  // r17
    u_int z_index;                  // r18
    sceVu0FMATRIX lwm;              // r29+0xC0
    sceVu0FMATRIX lsm;              // r29+0x100
    sceVu0FMATRIX clip_mat;         // r29+0x140
    float* pGrid_Y = pGrid_Y_Value; // r2
    float Ambient_Color[4];         // r29+0x180
    float view_dir[4];              // r29+0x190
    float pos[4];                   // r29+0x1A0
    float dir[4];                   // r29+0x1B0
    float Light_Color[4];           // r29+0x1C0
    float Parameter[4];             // r29+0x1D0
    float far_z;                    // r20
    float cos_theta;                // r21
    u_int* pPk_Current;             // r19
    u_int* pPk_End;                 // r2
    float Grid_Vertex0[4];          // r29+0x1E0
    float Grid_Vertex1[4];          // r29+0x1F0
    float Grid_Vertex2[4];          // r29+0x200

    pPk = HH_Vif1Packet_Current_Get();
    x_grid_max = Grid_X_Max;
    z_grid_max = Grid_Z_Max - 1;
    pPk_Current = NULL;

    HH_ClassWrapper_ViewDirection_Get(view_dir);
    HH_ClassWrapper_AmbientColor_Get(Ambient_Color);
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, Light_Color, Parameter);
    sceVu0MulVector(Light_Color, Light_Color, Light_Base);

    sceVu0MulVector(Ambient_Color, Ambient_Color, Amb_Base);

    Ambient_Color[3] = amb_alpha_0x0036F270;
    Light_Color[3] = light_alpha_0x0036F278;

    cos_theta = Parameter[0]; // r21
    far_z = Parameter[2];     // r20

    sceVu0Normalize(dir, dir);

    sceVu0SubVector(pos, pos, WorldLocation);

    HH_ClassWrapper_WorldScreenMatrix_Get(lsm);

    sceVu0UnitMatrix(lwm);

    sceVu0TransMatrix(lwm, lwm, WorldLocation);
    sceVu0MulMatrix(lsm, lsm, lwm);

    HH_ClassWrapper_ViewFrustum_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);

    HH_Vif1PacketBuffer_GifTag_Open();

    sceVif1PkCloseGifTag(pPk);

    for (z_index = 0; z_index < z_grid_max; z_index++) {
        sceVu0FVECTOR Grid_Vertex0 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};       // r29+0x1B0
        sceVu0FVECTOR Grid_Vertex1 = {200.0f, 0.0f, 200.0f * (z_index + 1), 1.0f}; // r29+0x1C0
        sceVu0FVECTOR Grid_Vertex2 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};       // r29+0x1D0

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, Grid_X_Max, 3, 3);
        }

        for (x_index = 0; x_index < Grid_X_Max; x_index++) {
            float Rgba[4];        // r29+0x210
            int xyzf[4];          // r29+0x220
            int rgba[4];          // r29+0x230
            u_int addr;           // r2
            float vec0[4];        // r29+0x240
            float vec1[4];        // r29+0x250
            float n0[4];          // r29+0x260
            float specular_ratio; // r22
            float stq0[4];        // r29+0x270
            float stq1[4];        // r29+0x280
            float base;           // r2
            float color_scale;    // r29+0x290
            static float sx_0x0036F2B0 = 2.5f;                                                                                     // @ 0x0036F2B0
            static float ty_0x0036F2B8 = 2.5f;                                                                                     // @ 0x0036F2B8


            Grid_Vertex0[0] = Grid_Vertex1[0] = 200.0f * x_index;

            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 200.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_01_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_01_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_01_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

            base = 0.25f * (1.0f / (200.0f * ty_0x0036F2B8));
            stq0[0] = stq1[0] = 0.25f * (Grid_Vertex0[0] / (200.0f * sx_0x0036F2B0));
            stq0[1] = Grid_Vertex0[2] * base;
            stq1[1] = Grid_Vertex1[2] * base;
            sceVu0AddVector(stq0, stq0, pThis->ST_Defference);
            sceVu0AddVector(stq1, stq1, pThis->ST_Defference);
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
                HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq0, lsm, clip_mat, Grid_Vertex0, 0x3f);

                color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, Grid_Vertex0, cos_theta, far_z);

                color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

                if (color_scale == 0.0f) {
                    sceVu0FTOI0Vector(rgba, Ambient_Color2);
                } else {

                    sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

                    sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                    sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

                    if (Grid_Vertex0[1] != 0.0f) {
                        SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba, specular_ratio);
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

            HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq1, lsm, clip_mat, Grid_Vertex1, 0x3f);

            color_scale = HH_ClassWrapper_SpotLight_ColorRatio_Calculator(pos, dir, Grid_Vertex1, cos_theta, far_z);

            color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

            if (color_scale == 0.0f) {
                sceVu0FTOI0Vector(rgba, Ambient_Color2);
            } else {

                sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

                sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

                if (Grid_Vertex1[1] != 0.0f) {
                    SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba, specular_ratio);
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

    sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag);

    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}

u_int HH_Class_Prefix_Water_01() {
    u_long tex0;                                      // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_int result = 1;                                 // r2
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_01_TEX_ID, HH_WATER_01_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(3, 3, 0x1ff, 0, 0x1ff, 0)); // 0x1ff001fff
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Suffix_Water_01() {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_int result = 1;                                 // r2
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

static float degree_178_0x0036F2C0 = 40.0f;
static float base_move_179_0x0036F2C8 = 24.0f;
static float add_move_180_0x0036F2D0 = -1.0f;
static float _distance_189_0x0036F2D8 = 1200.0f;
static float _lost_time_190_0x0036F2E0 = 12.0f;
static float _arri_191_0x0036F2E8 = 40.0f;
static float _omega_192_0x0036F2F0 = 540.0f;
static float _v_193_0x0036F2F8 = 500.0f;
static float _interval_194_0x0036F300 = 4.0f;
static float __distance_201_0x0036F308 = 3200.0f;
static float __lost_time_202_0x0036F310 = 10.0f;
static float __arri_203_0x0036F318 = 40.0f;
static float __omega_204_0x0036F320 = 612.0f;
static float __v_205_0x0036F328 = 1200.0f;
static float center_181_0x011EB560 = 0.0f;

u_int HH_Class_Water_01(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r19 */) {
    u_int result = 1;                   // r16
    HH_Object_Water_01* pThis = pBlock; // r17

    switch (pThis->Step) { /* irregular */
        case HH_WATER_01_STEP_INIT:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;

        case HH_WATER_01_STEP_DRAW: {
            float rad_omega;   // r29+0x150
            float rad;         // r29+0x150
            sceVu0FVECTOR pos; // r29+0x80
            int area;          // r18
            Grid_Work_Initialize(pThis);
            rad_omega = TO_RAD(degree_178_0x0036F2C0) * pThis->Timer;
            if (rad_omega > 0.0f) {
                rad = fmodf(rad_omega, TAU);
                if (rad > PI) {
                    rad -= TAU;
                }
            } else {
                rad = fmodf(rad_omega, -TAU);
                if (rad < -PI) {
                    rad += TAU;
                }
            }
            pThis->ST_Defference[0] = add_move_180_0x0036F2D0 + ((center_181_0x011EB560 + (base_move_179_0x0036F2C8 * HH_MathWrapper_Cosf(rad))) / 512.0f);
            pThis->ST_Defference[1] = add_move_180_0x0036F2D0 + ((center_181_0x011EB560 + (base_move_179_0x0036F2C8 * HH_MathWrapper_Sinf(rad))) / 512.0f);
            HH_ClassWrapper_JMS_WorldPosition_Get(pos);
            area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pos, _Area_Info_List_0x0036EE80, HH_WATER_01_TABLE_MAX);
            HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, HH_WATER_01_TABLE_MAX);
            if (area != -1) {
                HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List_0x0036EE80, HH_WATER_01_TABLE_MAX, area);
            } else {
                pThis->Area_Enable_Table[0] = 0;
                pThis->Area_Enable_Table[1] = 1;
                pThis->Area_Enable_Table[2] = 1;
                pThis->Area_Enable_Table[3] = 1;
            }
            if (pElement->Option.Int_Value[0] != 0) {
                int area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x0036EE80, HH_WATER_01_TABLE_MAX);
                if (area != -1) {
                    Wave_Element wave_element; // r29+0x90
                    u_int x;
                    u_int z;
                    CurrentPosition_AreaIndex_Calculator(pElement, &_Area_Info_List_0x0036EE80[area], &x, &z);
                    wave_element.Enable = 1;
                    wave_element.Area = area;
                    wave_element.Impact_Grid_Index[0] = x;
                    wave_element.Impact_Grid_Index[1] = z;
                    wave_element.Max_Distance0 = _distance_189_0x0036F2D8;
                    wave_element.Lost_Time = _lost_time_190_0x0036F2E0;
                    wave_element.Arrival = _arri_191_0x0036F2E8;
                    wave_element.Omega = TO_RAD(_omega_192_0x0036F2F0);
                    wave_element.Verocity = _v_193_0x0036F2F8;
                    wave_element.Timer = 0;
                    HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                }
                pElement->Option.Int_Value[0] = 0;
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_01_TABLE_MAX; i++) {
                    if (!((pThis->Timer - pThis->Area_WavePostTime[i]) <= _interval_194_0x0036F300)) {
                        WaveArea_Infomeation* pInfo = &_Area_Info_List_0x0036EE80[i];
                        Wave_Element wave_element; // r29+0xF0
                        int x = rand() % pInfo->Grid_Index[0];
                        int z = rand() % pInfo->Grid_Index[1];
                        wave_element.Enable = 1;
                        wave_element.Area = i;
                        wave_element.Impact_Grid_Index[0] = x;
                        wave_element.Impact_Grid_Index[1] = z;
                        wave_element.Max_Distance0 = __distance_201_0x0036F308;
                        wave_element.Lost_Time = __lost_time_202_0x0036F310;
                        wave_element.Arrival = __arri_203_0x0036F318;
                        wave_element.Omega = TO_RAD(__omega_204_0x0036F320);
                        wave_element.Verocity = __v_205_0x0036F328;
                        wave_element.Timer = 0.0f;
                        HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                        pThis->Area_WavePostTime[i] = pThis->Timer;
                    }
                }
                for (i = 0; i < HH_WATER_01_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        HH_Class_WaterCommon_WaveArea_Calculator(&_Area_Info_List_0x0036EE80[i], pThis->Wave_Info, 0x14U, i);
                    }
                }
            }
            HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area00_01_grid_link_list_0x0036F150);
            HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area01_02_grid_link_list_0x0036F180);
            HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area02_03_grid_link_list_0x0036F1B0);
            HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area03_04_grid_link_list_0x0036F1E0);
            {
                u_int i;
                for (i = 0; i < HH_WATER_01_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        WaveArea_Infomeation* pInfo = _Area_Info_List_0x0036EE80; // r21
                        WaveArea_Infomeation* pArea_Info = &pInfo[i];             // r2
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], pArea_Info, pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
            }
            HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14);
            pThis->Timer += 1.0f / 30.0f;
            break;
        }

        default:
        case HH_WATER_01_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}
