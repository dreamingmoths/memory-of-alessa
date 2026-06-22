#include "sh2_common.h"
#include "Effect2/hh_class_water_02.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"
#include "SH2_common/pad.h"
#include "libvifpk.h"

#pragma divbyzerocheck off

static u_int _area00_view_list_0x0036F330[1] = {0};
static WaveArea_Infomeation _Area_Info_List_0x0036F340[1] = {
    {/* .World_Location = */ {-51100.0f, -200.0f, -30900.0f, 1.0f},
     /* .Grid_WH = */ {2200.0f, 0.0f, 2400.0f, 100.0f},
     /* .Grid_Index = */ {22, 24},
     /* .pViewArea_List = */ &_area00_view_list_0x0036F330,
     /* .ViewArea_List_Max = */ 1,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL}};

static float cos_beta_min_66_0x0036F3D0 = 0.99144399f;

static void Grid_Work_Initialize(HH_Object_Water_02* pThis /* r2 */) {
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));
}

static unsigned int Object_Initialize(HH_Object_Water_02* pThis /* r16 */) {
    u_int result = 1; // r2
    pThis->Timer = 0.0f;
    pThis->Motion_Step = 0;
    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0});
    pThis->Area_WavePostTime[0] = 0.0f;
    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    _Area_Info_List_0x0036F340->pGrid_Y_Value = pThis->Area00_Grid_Y_Value;
    return result;
}

static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement /* r3 */, WaveArea_Infomeation* pInfo /* r2 */, unsigned int* pX_Index /* r17 */, unsigned int* pZ_Index /* r16 */) {
    float check_pos[4]; // r29+0x30
    sceVu0SubVector(check_pos, pElement->Option.Vector[0], pInfo->World_Location);
    *pX_Index = (u_int)(check_pos[0] / 100.0f);
    *pZ_Index = (u_int)(check_pos[2] / 100.0f);
}

static float Specular_Calculator(float* View_Direction /* r18 */, float* Light_Direction /* r17 */, float* Normal_Vector /* r16 */) {
    float result;                      // r29+0x60
    float specular_coefficient = 1.0f; // r29+0x60
    float input_light_power;           // r29+0x60
    float reverse_light_dir[4];        // r29+0x40
    float tmp_vec[4];                  // r29+0x50
    float cos_theta;                   // r29+0x60
    float cos_beta;                    // r29+0x60
    // float cos_beta_min; // @ 0x0036F3D0

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
    if (cos_beta < cos_beta_min_66_0x0036F3D0) {
        result = 0.0f;
    } else {

        result = 1.0f - ((1.0f - cos_beta) / (1 - cos_beta_min_66_0x0036F3D0));
    }
    return result * specular_coefficient;
}

static void SpecularRGBA_Calculator(signed int* iRGBA /* r2 */, float* RGBA_Base /* r2 */, float* RGBA_Specular_Base /* r2 */, float Specular_Ratio /* r29 */) {
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

// @todo: data partially moved out of function, required for match
static u_long _GifTag[2] = {
    SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
    GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F3E0
static u_long _GifTag_Tri[2] = {
    SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
    GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F3F0
static float Light_Base[4] = {16.0f, 16.0f, 16.0f, 0.0f};                                                   // @ 0x0036F400
static float Amb_Base[4] = {64.0f, 64.0f, 64.0f, 0.0f};                                                     // @ 0x0036F410
static float Ambient_Color2[4] = {19.0f, 19.0f, 19.0f, 255.0f};                                             // @ 0x0036F420
static float SpecularRgba[4] = {255.0f, 255.0f, 255.0f, 64.0f};                                             // @ 0x0036F430

static u_int Object_Draw(HH_Object_Water_02* pThis /* r22 */, float* pGrid_Y_Value /* r21 */, float* WorldLocation /* r17 */, u_int Grid_X_Max /* r20 */, u_int Grid_Z_Max /* r18 */) {
    static float amb_alpha = 32.0f;    // @ 0x0036F440
    static float light_alpha = 128.0f; // @ 0x0036F448
    u_int result = 0;                  // r2
    sceVif1Packet* pPk;                // r16
    u_int vertex_num;                  // r2
    u_int x_grid_max;                  // r2
    u_int z_grid_max;                  // r29+0xB0
    u_int x_index;                     // r17
    u_int z_index;                     // r18
    u_int prim_type;                   // r2
    float lwm[4][4];                   // r29+0xC0
    float lsm[4][4];                   // r29+0x100
    float clip_mat[4][4];              // r29+0x140
    float* pGrid_Y = pGrid_Y_Value;    // r2
    float Ambient_Color[4];            // r29+0x180
    float view_dir[4];                 // r29+0x190
    float pos[4];                      // r29+0x1A0
    float dir[4];                      // r29+0x1B0
    float Light_Color[4];              // r29+0x1C0
    float Parameter[4];                // r29+0x1D0
    float far_z;                       // r20
    float cos_theta;                   // r21
    u_int* pPk_Current;                // r19
    u_int* pPk_End;                    // r2
    float Grid_Vertex0[4];             // r29+0x1E0
    float Grid_Vertex1[4];             // r29+0x1F0
    float Grid_Vertex2[4];             // r29+0x200
    float Rgba[4];                     // r29+0x210
    int xyzf[4];                       // r29+0x220
    int rgba[4];                       // r29+0x230
    u_int addr;                        // r2
    float vec0[4];                     // r29+0x240
    float vec1[4];                     // r29+0x250
    float n0[4];                       // r29+0x260
    float specular_ratio;              // r22
    float stq0[4];                     // r29+0x270
    float stq1[4];                     // r29+0x280
    float base;                        // r2
    float color_scale;                 // r29+0x290

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
        sceVu0FVECTOR Grid_Vertex0 = {100.0f, 0.0f, 100.0f * z_index, 1.0f};       // r29+0x1B0
        sceVu0FVECTOR Grid_Vertex1 = {100.0f, 0.0f, 100.0f * (z_index + 1), 1.0f}; // r29+0x1C0
        sceVu0FVECTOR Grid_Vertex2 = {100.0f, 0.0f, 100.0f * z_index, 1.0f};       // r29+0x1D0

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, Grid_X_Max, 3, 3);
        }

        for (x_index = 0; x_index < Grid_X_Max; x_index++) {
            float Rgba[4];                     // r29+0x210
            int xyzf[4];                       // r29+0x220
            int rgba[4];                       // r29+0x230
            u_int addr;                        // r2
            float vec0[4];                     // r29+0x240
            float vec1[4];                     // r29+0x250
            float n0[4];                       // r29+0x260
            float specular_ratio;              // r22
            float stq0[4];                     // r29+0x270
            float stq1[4];                     // r29+0x280
            float base;                        // r2
            float color_scale;                 // r29+0x290
            static float sx_0x0036F480 = 7.0f; // @ 0x0036F480
            static float ty_0x0036F488 = 7.0f; // @ 0x0036F488

            Grid_Vertex0[0] = Grid_Vertex1[0] = 100.0f * x_index;

            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 100.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_02_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_02_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_02_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

            base = 0.25f * (1.0f / (100.0f * ty_0x0036F488));
            stq0[0] = stq1[0] = 0.25f * (Grid_Vertex0[0] / (100.0f * sx_0x0036F480));
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

unsigned int HH_Class_Prefix_Water_02() {
    static u_int _interval_194_0x0036F4D0 = 1;        // @ 0x0036F490
    static int i = 0;                                 // @ 0x011EB580
    static u_int j = 0;                               // @ 0x011EB588
    u_int result = 1;                                 // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_long tex0;                                      // r2
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_02_TEX_ID, HH_WATER_02_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, hh_class_water_clamp(i));
    if ((HH_DBG_Wrapper_Controller_KeyAssign_Check(1, 0, PAD_KEY_CIRCLE) != 0) && j % _interval_194_0x0036F4D0 == 0) {
        i++;
        i = clamp_n(i, 4);
    }
    j++;
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

unsigned int HH_Class_Suffix_Water_02() {
    u_int result = 1;                                 // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

static float degree_180 = 10.0f;
static float base_move_181 = 128.0f;
static float _distance_189_0x0036F4A8 = 1200.0f;
static float _lost_time_190_0x0036F4B0 = 12.0f;
static float _arri_191_0x0036F4B8 = 40.0f;
static float _omega_192_0x0036F4C0 = 540.0f;
static float _v_193_0x0036F4C8 = 500.0f;
static float __interval_194_0x0036F4D0_194_0x0036F4D0 = 4.0f;
static float __distance_201_0x0036F4D8 = 3200.0f;
static float __lost_time_202_0x0036F4E0 = 10.0f;
static float __arri_203_0x0036F4E8 = 40.0f;
static float __omega_204_0x0036F4F0 = 612.0f;
static float __v_205_0x0036F4F8 = 1200.0f;

unsigned int HH_Class_Water_02(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r19 */) {
    static char tmp[80];                // @ 0x011EB5A0
    static u_int i;                     // @ 0x011EB590
    u_int result = 1;                   // r16
    HH_Object_Water_02* pThis = pBlock; // r17

    switch (pThis->Step) { /* irregular */
        case HH_WATER_02_STEP_INIT:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;

        case HH_WATER_02_STEP_DRAW: {
            float rad_omega;   // r29+0x150
            float rad;         // r29+0x150
            sceVu0FVECTOR pos; // r29+0x80
            int area;          // r18
            Grid_Work_Initialize(pThis);
            rad_omega = TO_RAD(degree_180) * pThis->Timer;
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
            pThis->ST_Defference[0] = ((base_move_181 + (base_move_181 * HH_MathWrapper_Cosf(rad))) / 512.0f);
            pThis->ST_Defference[1] = ((base_move_181 + (base_move_181 * HH_MathWrapper_Sinf(rad))) / 512.0f);
            HH_ClassWrapper_JMS_WorldPosition_Get(pos);
            area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pos, _Area_Info_List_0x0036F340, HH_WATER_02_TABLE_MAX);
            HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, HH_WATER_02_TABLE_MAX);
            if (area != -1) {
                HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List_0x0036F340, HH_WATER_02_TABLE_MAX, area);
            } else {
                pThis->Area_Enable_Table[0] = 1;
            }
            if (pElement->Option.Int_Value[0] != 0) {
                int area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x0036F340, HH_WATER_02_TABLE_MAX);
                if (area != -1) {
                    Wave_Element wave_element; // r29+0x90
                    u_int x;
                    u_int z;
                    CurrentPosition_AreaIndex_Calculator(pElement, &_Area_Info_List_0x0036F340[area], &x, &z);
                    wave_element.Enable = 1;
                    wave_element.Area = area;
                    wave_element.Impact_Grid_Index[0] = x;
                    wave_element.Impact_Grid_Index[1] = z;
                    wave_element.Max_Distance0 = _distance_189_0x0036F4A8;
                    wave_element.Lost_Time = _lost_time_190_0x0036F4B0;
                    wave_element.Arrival = _arri_191_0x0036F4B8;
                    wave_element.Omega = TO_RAD(_omega_192_0x0036F4C0);
                    wave_element.Verocity = _v_193_0x0036F4C8;
                    wave_element.Timer = 0;
                    HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                }
                pElement->Option.Int_Value[0] = 0;
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_02_TABLE_MAX; i++) {
                    if (pThis->Timer - pThis->Area_WavePostTime[i] > __interval_194_0x0036F4D0_194_0x0036F4D0) {
                        WaveArea_Infomeation* pInfo = &_Area_Info_List_0x0036F340[i];
                        Wave_Element wave_element; // r29+0xF0
                        int x = rand() % pInfo->Grid_Index[0];
                        int z = rand() % pInfo->Grid_Index[1];
                        wave_element.Enable = 1;
                        wave_element.Area = i;
                        wave_element.Impact_Grid_Index[0] = x;
                        wave_element.Impact_Grid_Index[1] = z;
                        wave_element.Max_Distance0 = __distance_201_0x0036F4D8;
                        wave_element.Lost_Time = __lost_time_202_0x0036F4E0;
                        wave_element.Arrival = __arri_203_0x0036F4E8;
                        wave_element.Omega = TO_RAD(__omega_204_0x0036F4F0);
                        wave_element.Verocity = __v_205_0x0036F4F8;
                        wave_element.Timer = 0.0f;
                        HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                        pThis->Area_WavePostTime[i] = pThis->Timer;
                    }
                }
                for (i = 0; i < HH_WATER_02_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        HH_Class_WaterCommon_WaveArea_Calculator(&_Area_Info_List_0x0036F340[i], pThis->Wave_Info, 0x14u, i);
                    }
                }
                for (i = 0; i < HH_WATER_02_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        WaveArea_Infomeation* pInfo = _Area_Info_List_0x0036F340; // r21
                        WaveArea_Infomeation* pArea_Info = &pInfo[i];             // r2
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], pArea_Info, pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
            }
            {
                WaveArea_Infomeation* pInfo; // r18
                HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14);
                HH_DBG_Wrapper_T0_COUNT_Delta();
                pInfo = &(&_Area_Info_List_0x0036F340)[i];
                sprintf(tmp, "x = %f\n", (double)(pInfo->World_Location[0]));
                /* @note: casts needed for match */
                HH_DBG_Wrapper_Printf(0x100, 0xE8, (char*)tmp);
                sprintf(tmp, "y = %f\n", (double)(pInfo->World_Location[1]));
                HH_DBG_Wrapper_Printf(0x100, 0xF0, (char*)tmp);
                sprintf(tmp, "z = %f\n", (double)(pInfo->World_Location[2]));
                HH_DBG_Wrapper_Printf(0x100, 0xF8, (char*)tmp);
                sprintf(tmp, "i = %d\n", i);
                HH_DBG_Wrapper_Printf(0x100, 0x100, (char*)tmp);
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 0u, 0x1000u) != 0) {
                    i = 0;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_DPAD_RIGHT) != 0) {
                    pInfo->World_Location[0] += 10.0f;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_DPAD_LEFT) != 0) {
                    pInfo->World_Location[0] -= 10.0f;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_DPAD_UP) != 0) {
                    pInfo->World_Location[1] -= 10.0f;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_DPAD_DOWN) != 0) {
                    pInfo->World_Location[1] += 10.0f;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_R1) != 0) {
                    pInfo->World_Location[2] -= 10.0f;
                }
                if (HH_DBG_Wrapper_Controller_KeyAssign_Check(1u, 1u, PAD_KEY_R2) != 0) {
                    pInfo->World_Location[2] += 10.0f;
                }
                pThis->Timer += 1.0f / 30.0f;
            }
            break;
        }

        default:
        case HH_WATER_02_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }
    return result;
}
