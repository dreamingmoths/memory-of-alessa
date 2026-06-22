#include "sh2_common.h"
#include "Effect2/hh_class_water_08.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"
#include "libvifpk.h"

static u_int _area00_view_list_0x00375128[3] = {0, 1, 5};
static u_int _area01_view_list_0x00375140[4] = {0, 1, 2, 5};
static u_int _area02_view_list_0x00375150[4] = {1, 2, 3, 4};
static u_int _area03_view_list_0x00375160[2] = {2, 3};
static u_int _area04_view_list_0x00375168[3] = {2, 4, 5};
static u_int _area05_view_list_0x00375180[5] = {0, 1, 4, 5, 6};
static u_int _area06_view_list_0x00375198[2] = {5, 6};

static WaveArea_Infomeation _Area_Info_List_0x003751A0[HH_WATER_08_TABLE_MAX] = {
    {/* .World_Location = */ {57700.0f, -180.0f, -24300.0f, 1.0f},
     /* .Grid_WH = */ {1600.0f, 0.0f, 1600.0f, 200.0f},
     /* .Grid_Index = */ {8, 8},
     /* .pViewArea_List = */ &_area00_view_list_0x00375128,
     /* .ViewArea_List_Max = */ 3,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {57700.0f, -180.0f, -25300.0f, 1.0f},
     /* .Grid_WH = */ {4800.0f, 0.0f, 1200.0f, 200.0f},
     /* .Grid_Index = */ {24, 6},
     /* .pViewArea_List = */ &_area01_view_list_0x00375140,
     /* .ViewArea_List_Max = */ 4,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {62300.0f, -180.0f, -25300.0f, 1.0f},
     /* .Grid_WH = */ {1200.0f, 0.0f, 8400.0f, 200.0f},
     /* .Grid_Index = */ {6, 42},
     /* .pViewArea_List = */ &_area02_view_list_0x00375150,
     /* .ViewArea_List_Max = */ 4,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {60300.0f, -180.0f, -22900.0f, 1.0f},
     /* .Grid_WH = */ {2200.0f, 0.0f, 1600.0f, 200.0f},
     /* .Grid_Index = */ {11, 8},
     /* .pViewArea_List = */ &_area03_view_list_0x00375160,
     /* .ViewArea_List_Max = */ 2,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {57700.0f, -180.0f, -18100.0f, 1.0f},
     /* .Grid_WH = */ {4800.0f, 0.0f, 1200.0f, 200.0f},
     /* .Grid_Index = */ {24, 6},
     /* .pViewArea_List = */ &_area04_view_list_0x00375168,
     /* .ViewArea_List_Max = */ 3,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {56700.0f, -180.0f, -24300.0f, 1.0f},
     /* .Grid_WH = */ {1200.0f, 0.0f, 7400.0f, 200.0f},
     /* .Grid_Index = */ {6, 37},
     /* .pViewArea_List = */ &_area05_view_list_0x00375180,
     /* .ViewArea_List_Max = */ 5,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL},
    {/* .World_Location = */ {57700.0f, -180.0f, -19300.0f, 1.0f},
     /* .Grid_WH = */ {3000.0f, 0.0f, 1400.0f, 200.0f},
     /* .Grid_Index = */ {15, 7},
     /* .pViewArea_List = */ &_area06_view_list_0x00375198,
     /* .ViewArea_List_Max = */ 2,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL}};

static WaveArea_GridLink_Infomeation _area00_01_grid_link_list_0x00375590[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 1,
     /* .Length = */ 8,
     /* .X_Index_Max = */ {8, 24},
     /* .X_Index_Start = */ {0, 0},
     /* .Z_Index_Start = */ {0, 5}}};

static WaveArea_GridLink_Infomeation _area00_05_grid_link_list[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 8,
     /* .X_Index_Max = */ {8, 6},
     /* .X_Index_Start = */ {0, 5},
     /* .Z_Index_Start = */ {0, 0}}};

static WaveArea_GridLink_Infomeation _area01_02_grid_link_list_0x003755F0[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 6,
     /* .X_Index_Max = */ {24, 6},
     /* .X_Index_Start = */ {23, 0},
     /* .Z_Index_Start = */ {0, 0}}};

static WaveArea_GridLink_Infomeation _area02_03_grid_link_list_0x00375620[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 8,
     /* .X_Index_Max = */ {6, 11},
     /* .X_Index_Start = */ {0, 10},
     /* .Z_Index_Start = */ {12, 0}}};

static WaveArea_GridLink_Infomeation _area02_04_grid_link_list_0x00375650[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 6,
     /* .X_Index_Max = */ {6, 24},
     /* .X_Index_Start = */ {0, 23},
     /* .Z_Index_Start = */ {36, 0}}};

static WaveArea_GridLink_Infomeation _area04_05_grid_link_list_0x00375680[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 6,
     /* .X_Index_Max = */ {24, 6},
     /* .X_Index_Start = */ {0, 5},
     /* .Z_Index_Start = */ {0, 31}}};

static WaveArea_GridLink_Infomeation _area05_06_grid_link_list_0x003756B0[1] = {
    {/* .pGrid_Y_Value_Link = */ {NULL, NULL},
     /* .Vertical_Horizontal_Flag = */ 0,
     /* .Length = */ 7,
     /* .X_Index_Max = */ {6, 15},
     /* .X_Index_Start = */ {5, 0},
     /* .Z_Index_Start = */ {25, 0}}};

static void Grid_Work_Initialize(HH_Object_Water_08* pThis /* r16 */) {
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));
    memset(pThis->Area01_Grid_Y_Value, 0, sizeof(pThis->Area01_Grid_Y_Value));
    memset(pThis->Area02_Grid_Y_Value, 0, sizeof(pThis->Area02_Grid_Y_Value));
    memset(pThis->Area03_Grid_Y_Value, 0, sizeof(pThis->Area03_Grid_Y_Value));
    memset(pThis->Area04_Grid_Y_Value, 0, sizeof(pThis->Area04_Grid_Y_Value));
    memset(pThis->Area05_Grid_Y_Value, 0, sizeof(pThis->Area05_Grid_Y_Value));
    memset(pThis->Area06_Grid_Y_Value, 0, sizeof(pThis->Area06_Grid_Y_Value));
}

static u_int Object_Initialize(HH_Object_Water_08* pThis /* r16 */) {
    u_int result = 1;
    u_int i;

    pThis->Timer = 0.0f;

    pThis->Motion_Step = 0;

    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0.0f});

    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[1] = pThis->Area01_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[2] = pThis->Area02_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[3] = pThis->Area03_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[4] = pThis->Area04_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[5] = pThis->Area05_Grid_Y_Value;
    pThis->pArea_Grid_Y_Value_Table[6] = pThis->Area06_Grid_Y_Value;

    for (i = 0; i < HH_WATER_08_TABLE_MAX; i++) {
        pThis->Area_WavePostTime[i] = 0.0f;
        _Area_Info_List_0x003751A0[i].pGrid_Y_Value = pThis->pArea_Grid_Y_Value_Table[i];
    }

    _area00_01_grid_link_list_0x00375590->pGrid_Y_Value_Link[0] = pThis->Area00_Grid_Y_Value;
    _area00_01_grid_link_list_0x00375590->pGrid_Y_Value_Link[1] = pThis->Area01_Grid_Y_Value;
    _area00_05_grid_link_list->pGrid_Y_Value_Link[0] = pThis->Area00_Grid_Y_Value;
    _area00_05_grid_link_list->pGrid_Y_Value_Link[1] = pThis->Area05_Grid_Y_Value;
    _area01_02_grid_link_list_0x003755F0->pGrid_Y_Value_Link[0] = pThis->Area01_Grid_Y_Value;
    _area01_02_grid_link_list_0x003755F0->pGrid_Y_Value_Link[1] = _area02_03_grid_link_list_0x00375620->pGrid_Y_Value_Link[0] = pThis->Area02_Grid_Y_Value;
    _area02_03_grid_link_list_0x00375620->pGrid_Y_Value_Link[1] = pThis->Area03_Grid_Y_Value;
    _area02_04_grid_link_list_0x00375650->pGrid_Y_Value_Link[0] = pThis->Area02_Grid_Y_Value;
    _area02_04_grid_link_list_0x00375650->pGrid_Y_Value_Link[1] = _area04_05_grid_link_list_0x00375680->pGrid_Y_Value_Link[0] = pThis->Area04_Grid_Y_Value;
    _area04_05_grid_link_list_0x00375680->pGrid_Y_Value_Link[1] = _area05_06_grid_link_list_0x003756B0->pGrid_Y_Value_Link[0] = pThis->Area05_Grid_Y_Value;
    _area05_06_grid_link_list_0x003756B0->pGrid_Y_Value_Link[1] = pThis->Area06_Grid_Y_Value;

    return result;
}

static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement /* r3 */, WaveArea_Infomeation* pInfo /* r2 */, u_int* pX_Index /* r17 */, u_int* pZ_Index /* r16 */) {
    float check_pos[4];

    sceVu0SubVector(check_pos, pElement->Option.Vector[0], pInfo->World_Location);
    *pX_Index = (u_int)(check_pos[0] / 200.0f);
    *pZ_Index = (u_int)(check_pos[2] / 200.0f);
}

static float Specular_Calculator(float* View_Direction /* r18 */, float* Light_Direction /* r17 */, float* Normal_Vector /* r16 */) {
    static float cos_beta_min = 0.99144399f; // @ 0x003756D8
    float result = 1;
    float specular_coefficient = 1.0f;
    float input_light_power;
    float reverse_light_dir[4];
    float cos_theta;
    float cos_beta;
    float tmp_vec[4];

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

static void SpecularRGBA_Calculator(int* iRGBA /* r2 */, float* RGBA_Base /* r2 */, float* RGBA_Specular_Base /* r2 */, float Specular_Ratio /* r29 */) {
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

// @note: data partially moved out, required for match
static u_long _GifTag[2] = {
    SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
    GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x003756E0

static u_int Object_Draw(HH_Object_Water_08* pThis /* r22 */, float* pGrid_Y_Value /* r21 */, float* WorldLocation /* r17 */, u_int Grid_X_Max /* r20 */, u_int Grid_Z_Max /* r18 */) {
    static u_long _GifTag_Tri[2] = {
        SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
        GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x003756F0
    static float Light_Base[4] = {20.0f, 20.0f, 20.0f, 0.0f};                                                   // @ 0x00375700
    static float Amb_Base[4] = {64.0f, 64.0f, 64.0f, 0.0f};                                                     // @ 0x00375710
    static float Ambient_Color2[4] = {19.0f, 19.0f, 19.0f, 255.0f};                                             // @ 0x00375720
    static float SpecularRgba[4] = {48.0f, 48.0f, 48.0f, 64.0f};                                                // @ 0x00375730
    static float amb_alpha = 40.0f;                                                                             // @ 0x00375740
    static float light_alpha = 80.0f;                                                                           // @ 0x00375748

    u_int result = 0;
    sceVif1Packet* pPk;
    u_int vertex_num;
    u_int x_grid_max;
    u_int z_grid_max;
    u_int x_index;
    u_int z_index;
    float lwm[4][4];
    float lsm[4][4];
    float clip_mat[4][4];
    float* pGrid_Y = pGrid_Y_Value;
    float Ambient_Color[4];
    float view_dir[4];
    float pos[4];
    float dir[4];
    float Light_Color[4];
    float Parameter[4];
    float far_z;
    float cos_theta;
    u_int* pPk_Current;
    u_int* pPk_End;

    pPk = HH_Vif1Packet_Current_Get();
    x_grid_max = Grid_X_Max;
    z_grid_max = Grid_Z_Max - 1;
    pPk_Current = NULL;

    HH_ClassWrapper_ViewDirection_Get(view_dir);
    HH_ClassWrapper_AmbientColor_Get(Ambient_Color);
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, Light_Color, Parameter);
    sceVu0MulVector(Light_Color, Light_Color, Light_Base);

    sceVu0MulVector(Ambient_Color, Ambient_Color, Amb_Base);

    Ambient_Color[3] = amb_alpha;
    Light_Color[3] = light_alpha;

    cos_theta = Parameter[0];
    far_z = Parameter[2];

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
        sceVu0FVECTOR Grid_Vertex0 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};
        sceVu0FVECTOR Grid_Vertex1 = {200.0f, 0.0f, 200.0f * (z_index + 1), 1.0f};
        sceVu0FVECTOR Grid_Vertex2 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, Grid_X_Max, 3, 3);
        }

        for (x_index = 0; x_index < Grid_X_Max; x_index++) {
            float Rgba[4];
            int xyzf[4];
            int rgba[4];
            u_int addr;
            float vec0[4];
            float vec1[4];
            float n0[4];
            float specular_ratio;
            float stq0[4];
            float stq1[4];
            float base;
            float color_scale;
            static float sx_118_0x00375780 = 2.5f; // @ 0x00375780
            static float ty_119_0x00375788 = 2.5f; // @ 0x00375788

            Grid_Vertex0[0] = Grid_Vertex1[0] = 200.0f * x_index;

            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 200.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_08_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_08_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_08_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

            base = 0.25f * (1.0f / (200.0f * ty_119_0x00375788));
            stq0[0] = stq1[0] = 0.25f * (Grid_Vertex0[0] / (200.0f * sx_118_0x00375780));
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

u_int HH_Class_Prefix_Water_08() {
    u_int result = 1;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_long tex0;
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_08_TEX_ID, HH_WATER_08_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(3, 3, 0x1ff, 0, 0x1ff, 0)); // 0x1ff001fff
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Suffix_Water_08() {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_int result = 1;
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

static float degree_178_0x00375790 = 40.0f;
static float base_move_179_0x00375798 = 8.0f;
static float add_move_180_0x003757A0 = -1.0f;
static float center_181_0x01202F60 = 0.0f;
static float _distance_189_0x003757A8 = 1200.0f;
static float _lost_time_190_0x003757B0 = 12.0f;
static float _arri_191_0x003757B8 = 40.0f;
static float _omega_192_0x003757C0 = 540.0f;
static float _v_193_0x003757C8 = 500.0f;
static float _interval_194_0x003757D0 = 4.0f;
static float __distance_203 = 3200.0f;
static float __lost_time_204 = 10.0f;
static float __arri_205 = 40.0f;
static float __omega_206 = 612.0f;
static float __v_207 = 1200.0f;

u_int HH_Class_Water_08(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r19 */) {
    u_int result = 1;
    HH_Object_Water_08* pThis = pBlock;

    switch (pThis->Step) { /* irregular */
        case HH_WATER_08_STEP_INIT:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;

        case HH_WATER_08_STEP_DRAW: {
            float rad_omega;
            float rad;
            int area;
            sceVu0FVECTOR pos;

            Grid_Work_Initialize(pThis);
            rad_omega = TO_RAD(degree_178_0x00375790) * pThis->Timer;
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
            pThis->ST_Defference[0] = ((add_move_180_0x003757A0 + (center_181_0x01202F60 + (base_move_179_0x00375798 * HH_MathWrapper_Cosf(rad))) / 512.0f));
            pThis->ST_Defference[1] = ((add_move_180_0x003757A0 + (center_181_0x01202F60 + (base_move_179_0x00375798 * HH_MathWrapper_Sinf(rad))) / 512.0f));
            HH_ClassWrapper_JMS_WorldPosition_Get(pos);
            area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pos, _Area_Info_List_0x003751A0, HH_WATER_08_TABLE_MAX);
            HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, HH_WATER_08_TABLE_MAX);
            if (area != -1) {
                HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List_0x003751A0, HH_WATER_08_TABLE_MAX, area);
            }
            if (pElement->Option.Int_Value[0] != 0) {
                area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x003751A0, HH_WATER_08_TABLE_MAX);
                if (area != -1) {
                    Wave_Element wave_element;
                    u_int x;
                    u_int z;
                    CurrentPosition_AreaIndex_Calculator(pElement, &_Area_Info_List_0x003751A0[area], &x, &z);
                    wave_element.Enable = 1;
                    wave_element.Area = area;
                    wave_element.Impact_Grid_Index[0] = x;
                    wave_element.Impact_Grid_Index[1] = z;
                    wave_element.Max_Distance0 = _distance_189_0x003757A8;
                    wave_element.Lost_Time = _lost_time_190_0x003757B0;
                    wave_element.Arrival = _arri_191_0x003757B8;
                    wave_element.Omega = TO_RAD(_omega_192_0x003757C0);
                    wave_element.Verocity = _v_193_0x003757C8;
                    wave_element.Timer = 0;
                    HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                }
                pElement->Option.Int_Value[0] = 0;
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_08_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i])
                        if ((pThis->Timer - pThis->Area_WavePostTime[i] > _interval_194_0x003757D0)) {
                            WaveArea_Infomeation* pInfo = &_Area_Info_List_0x003751A0[i];
                            Wave_Element wave_element;
                            u_int x = rand() % pInfo->Grid_Index[0];
                            u_int z = rand() % pInfo->Grid_Index[1];
                            if ((rand() % 3) != 0) {
                                if ((rand() % 3) != 0) {
                                    z = 0;
                                } else {
                                    z = pInfo->Grid_Index[1] - 1;
                                }
                            } else if ((rand() % 3) != 0) {
                                x = 0;
                            } else {
                                x = pInfo->Grid_Index[0] - 1;
                            }
                            wave_element.Enable = 1;
                            wave_element.Area = i;
                            wave_element.Impact_Grid_Index[0] = x;
                            wave_element.Impact_Grid_Index[1] = z;
                            wave_element.Max_Distance0 = __distance_203;
                            wave_element.Lost_Time = __lost_time_204;
                            wave_element.Arrival = __arri_205;
                            wave_element.Omega = TO_RAD(__omega_206);
                            wave_element.Verocity = __v_207;
                            wave_element.Timer = 0;
                            HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                            pThis->Area_WavePostTime[i] = pThis->Timer;
                        }
                }
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_08_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        HH_Class_WaterCommon_WaveArea_Calculator(&_Area_Info_List_0x003751A0[i], pThis->Wave_Info, 0x14, i);
                    }
                }
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area00_01_grid_link_list_0x00375590);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area00_05_grid_link_list);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area01_02_grid_link_list_0x003755F0);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area02_03_grid_link_list_0x00375620);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area02_04_grid_link_list_0x00375650);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area04_05_grid_link_list_0x00375680);
                HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(_area05_06_grid_link_list_0x003756B0);
                for (i = 0; i < HH_WATER_08_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        WaveArea_Infomeation* pInfo = _Area_Info_List_0x003751A0;
                        WaveArea_Infomeation* pArea_Info = &pInfo[i];
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], pArea_Info->World_Location, pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
            }
            HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14);
            pThis->Timer += 1.0f / 30.0f;
            break;
        }

        default:
        case HH_WATER_08_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    return result;
}
