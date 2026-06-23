#include "sh2_common.h"
#include "Effect2/hh_class_water_30.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_packet.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"
#include "Event/event.h"
#include "SH2_common/pad.h"
#include "libgraph.h"
#include "libvifpk.h"

#pragma divbyzerocheck off

static u_int _area00_view_list_0x00370388[1] = {0};
static WaveArea_Infomeation _Area_Info_List_0x00370390[1] = {
    {/* .World_Location = */ {98750.0f, -1450.0f, -100850.0f, 1.0f},
     /* .Grid_WH = */ {3000.0f, 0.0f, 2400.0f, 150.0f},
     /* .Grid_Index = */ {20, 16},
     /* .pViewArea_List = */ &_area00_view_list_0x00370388,
     /* .ViewArea_List_Max = */ 1,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL}};

static void Grid_Work_Initialize(HH_Object_Water_30* pThis);
static u_int Object_Initialize(HH_Object_Water_30* pThis, ImpactQueue_Element* pElement);
static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement, WaveArea_Infomeation* pInfo, u_int* pX_Index, u_int* pZ_Index);
static float Specular_Calculator(float* View_Direction, float* Light_Direction, float* Normal_Vector);
static void SpecularRGBA_Calculator(int* iRGBA, float* RGBA_Base, float* RGBA_Specular_Base, float Specular_Ratio);
static u_int Object_Draw(HH_Object_Water_30* pThis, float* pGrid_Y_Value, float* WorldLocation, u_int Grid_X_Max, u_int Grid_Z_Max);

static void Grid_Work_Initialize(HH_Object_Water_30* pThis /* r2 */) {
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));
}

static u_int Object_Initialize(HH_Object_Water_30* pThis /* r16 */, ImpactQueue_Element* pElement) {
    u_int result = 1;
    pThis->Timer = 0.0f;
    pThis->Motion_Step = 0;
    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0});
    sceVu0CopyVector(pThis->Location_Defference, (sceVu0FVECTOR){0});
    pThis->Area_WavePostTime[0] = 0.0f;
    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    _Area_Info_List_0x00370390->pGrid_Y_Value = pThis->Area00_Grid_Y_Value;
    return result;
}

static void CurrentPosition_AreaIndex_Calculator(ImpactQueue_Element* pElement /* r3 */, WaveArea_Infomeation* pInfo /* r2 */, u_int* pX_Index /* r17 */, u_int* pZ_Index /* r16 */) {
    float check_pos[4];
    sceVu0SubVector(check_pos, pElement->Option.Vector[0], pInfo->World_Location);
    *pX_Index = (u_int)(check_pos[0] / 150.0f);
    *pZ_Index = (u_int)(check_pos[2] / 150.0f);
}

static float Specular_Calculator(float* View_Direction /* r18 */, float* Light_Direction /* r17 */, float* Normal_Vector /* r16 */) {
    static float cos_beta_min = 0.819152f; // @ 0x00370420
    float result;
    float specular_coefficient = 1.0f;
    float input_light_power;
    float reverse_light_dir[4];
    float tmp_vec[4];
    float cos_theta;
    float cos_beta;

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

// @todo: data partially moved out, required for match due to float args

static u_long _GifTag[2] = {
    SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
    GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x00370430
static u_long _GifTag_Tri[2] = {
    SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
    GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x00370440

static u_int Object_Draw(HH_Object_Water_30* pThis, float* pGrid_Y_Value /* r16 */, float* WorldLocation /* r19 */, u_int Grid_X_Max /* r22 */, u_int Grid_Z_Max /* r18 */) {
    static float Light_Base[4] = {48.0f, 48.0f, 48.0f, 0.0f};       // @ 0x00370450
    static float Amb_Base[4] = {64.0f, 64.0f, 64.0f, 0.0f};         // @ 0x00370460
    static float SpecularRgba[4] = {128.0f, 128.0f, 128.0f, 64.0f}; // @ 0x00370470
    static float amb_alpha = 64.0f;                                 // @ 0x00370480
    static float light_alpha = 32.0f;                               // @ 0x00370488
    u_int result = 0;
    sceVif1Packet* pPk;
    u_int vertex_num;
    u_int x_grid_max;
    u_int z_grid_max;
    u_int x_index;
    u_int z_index;
    u_int prim_type;
    sceVu0FMATRIX lwm;
    sceVu0FMATRIX lsm;
    sceVu0FMATRIX clip_mat;
    float* pGrid_Y = pGrid_Y_Value;
    float Ambient_Color[4];
    float view_dir[4];
    float pos[4];
    float dir[4];
    float Light_Color[4];
    float Parameter[4];
    float far_z;
    float cos_theta;
    float tex_s_w;
    float tex_t_w;
    u_int* pPk_Current;
    u_int* pPk_End;

    pPk = HH_Vif1Packet_Current_Get();
    z_grid_max = Grid_Z_Max - 1;
    x_grid_max = Grid_X_Max;

    tex_s_w = 512.0f / (Grid_X_Max - 1);
    tex_t_w = 512.0f / z_grid_max;

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

    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);
    sceVu0MulMatrix(clip_mat, clip_mat, lwm);

    HH_Vif1PacketBuffer_GifTag_Open();

    sceVif1PkCloseGifTag(pPk);

    for (z_index = 0; z_index < z_grid_max; z_index++) {
        sceVu0FVECTOR Grid_Vertex0 = {150.0f, 0.0f, 150.0f * z_index, 1.0f};
        sceVu0FVECTOR Grid_Vertex1 = {150.0f, 0.0f, 150.0f * (z_index + 1), 1.0f};
        sceVu0FVECTOR Grid_Vertex2 = {150.0f, 0.0f, 150.0f * z_index, 1.0f};

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, x_grid_max, 3, 3);
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
            float now_s = (tex_s_w * x_index) / 512.0f;
            float stq0[4] = {
                now_s,
                (tex_t_w * z_index) / 512.0f, 0.0f, 0.0f};
            float stq1[4] = {
                now_s,
                (tex_t_w * (z_index + 1)) / 512.0f, 0.0f, 0.0f};
            float color_scale;

            Grid_Vertex0[0] = Grid_Vertex1[0] = 150.0f * x_index;
            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 150.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_30_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_30_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_30_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

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

                sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

                sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

                SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba, specular_ratio);

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

            sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);

            sceVu0AddVector(Rgba, Rgba, Ambient_Color);
            sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);

            SpecularRGBA_Calculator(rgba, Rgba, SpecularRgba, specular_ratio);

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

u_int HH_Class_Prefix_Water_30() {
    u_long tex0;
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_int result = 1;
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_30_TEX_ID, HH_WATER_30_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(3, 3, 0x1ff, 0, 0x1ff, 0));         // 0x1ff001fff
    sceVif1PkAddGsAD(pPk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMCT16S, SCE_GS_FALSE)); // 0x0a0001c0
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Suffix_Water_30() {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get();
    u_int result = 1;
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    sceVif1PkAddGsAD(pPk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMCT16S, SCE_GS_TRUE));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Water_30(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r19 */) {
    u_int result = 1;
    HH_Object_Water_30* pThis = pBlock;

    switch (pThis->Step) { /* irregular */
        case HH_WATER_30_STEP_INIT:
            if (GET_GAME_FLAG(4, 20)) {
                // @bug this is overwritten to 1 below
                pThis->Step = 2;
            }
            Object_Initialize(pThis, pElement);
            pThis->Step = 1;
            break;

        case HH_WATER_30_STEP_DRAW: {
            float rad_omega;
            float rad;
            int area;
            sceVu0FVECTOR pos;
            static float degree_185 = 40.0f;
            static float base_move_186 = 8.0f;
            static float add_move_187 = 0.0f;
            static float center_188 = 0.0f;
            static float _distance_196 = 1200.0f;
            static float _lost_time_197 = 12.0f;
            static float _arri_198 = 40.0f;
            static float _omega_199 = 540.0f;
            static float _v_200 = 500.0f;
            static float _interval_201 = 4.0f;
            static float __distance_210 = 3200.0f;
            static float __lost_time_211 = 10.0f;
            static float __arri_212 = 40.0f;
            static float __omega_213 = 612.0f;
            static float __v_214 = 1200.0f;
            static float time_234 = 10.0f;

            Grid_Work_Initialize(pThis);
            rad_omega = TO_RAD(degree_185) * pThis->Timer;
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
            pThis->ST_Defference[0] = add_move_187 + ((center_188 + (base_move_186 * HH_MathWrapper_Cosf(rad))) / 512.0f);
            pThis->ST_Defference[1] = add_move_187 + ((center_188 + (base_move_186 * HH_MathWrapper_Sinf(rad))) / 512.0f);

            area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x00370390, HH_WATER_30_TABLE_MAX);
            HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, HH_WATER_30_TABLE_MAX);
            if (area != -1) {
                HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List_0x00370390, HH_WATER_30_TABLE_MAX, area);
            } else {
                pThis->Area_Enable_Table[0] = 1;
            }
            if (pElement->Option.Int_Value[0] != 0) {
                int area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x00370390, HH_WATER_30_TABLE_MAX);
                if (area != -1) {
                    Wave_Element wave_element;
                    u_int x;
                    u_int z;
                    CurrentPosition_AreaIndex_Calculator(pElement, &_Area_Info_List_0x00370390[area], &x, &z);
                    wave_element.Enable = 1;
                    wave_element.Area = area;
                    wave_element.Impact_Grid_Index[0] = x;
                    wave_element.Impact_Grid_Index[1] = z;
                    wave_element.Max_Distance0 = _distance_196;
                    wave_element.Lost_Time = _lost_time_197;
                    wave_element.Arrival = _arri_198;
                    wave_element.Omega = TO_RAD(_omega_199);
                    wave_element.Verocity = _v_200;
                    wave_element.Timer = 0;
                    HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                }
                pElement->Option.Int_Value[0] = 0;
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_30_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i])
                        if ((pThis->Timer - pThis->Area_WavePostTime[i] > _interval_201)) {
                            WaveArea_Infomeation* pInfo = &_Area_Info_List_0x00370390[i];
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
                            wave_element.Max_Distance0 = __distance_210;
                            wave_element.Lost_Time = __lost_time_211;
                            wave_element.Arrival = __arri_212;
                            wave_element.Omega = TO_RAD(__omega_213);
                            wave_element.Verocity = __v_214;
                            wave_element.Timer = 0;
                            HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                            pThis->Area_WavePostTime[i] = pThis->Timer;
                        }
                }
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_30_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        WaveArea_Infomeation* pInfo = _Area_Info_List_0x00370390;
                        WaveArea_Infomeation* pArea_Info = &pInfo[i];
                        float world_location[4];
                        sceVu0AddVector(world_location, pArea_Info->World_Location, pThis->Location_Defference);
                        HH_Class_WaterCommon_WaveArea_Calculator(pArea_Info, pThis->Wave_Info, 0x14, i);
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], world_location, pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
            }
            HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14);
            if (GET_GAME_FLAG(4, 19)) {
                // @todo: is there a cleaner way to write this float?
                float add_vec[4] = {0.0f, 50.000004f / time_234, 0.0f, 0.0f};
                sceVu0AddVector(pThis->Location_Defference, pThis->Location_Defference, add_vec);
                if (pThis->Location_Defference[1] > 1700.0f) {
                    SET_GAME_FLAG(4, 20);
                }
            }
            if (GET_GAME_FLAG(4, 20)) {
                pThis->Step = HH_WATER_30_STEP_OFF;
            } else {
                pThis->Timer += 1.0f / 30.0f;
            }
            break;
        }

        default:
        case HH_WATER_30_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    return result;
}
