#include "sh2_common.h"
#include "Effect2/hh_class_water_10.h"
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

static void Grid_Work_Initialize(struct HH_Object_Water_10* pThis);
static u_int Object_Initialize(struct HH_Object_Water_10* pThis);
static u_int Object_Draw(struct HH_Object_Water_10* pThis, float* pGrid_Y_Value, float* WorldLocation, u_int Grid_X_Max, u_int Grid_Z_Max);

static u_int _area00_view_list_0x0036F500[1] = {0};
static WaveArea_Infomeation _Area_Info_List_0x0036F510[1] = {
    {/* .World_Location = */ {58000.0f, 160.0f, 56000.0f, 1.0f},
     /* .Grid_WH = */ {4200.0f, 0.0f, 8200.0f, 200.0f},
     /* .Grid_Index = */ {21, 41},
     /* .pViewArea_List = */ &_area00_view_list_0x0036F500,
     /* .ViewArea_List_Max = */ 1,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {255.0f, 255.0f, 255.0f, 64.0f},
     /* .Ambient0_BaseRGBA = */ {64.0f, 64.0f, 64.0f, 32.0f},
     /* .Ambient1_BaseRGBA = */ {19.0f, 19.0f, 19.0f, 255.0f},
     /* .Light_BaseRGBA = */ {16.0f, 16.0f, 16.0f, 128.0f},
     /* .pST_Defference = */ NULL}};

static void Grid_Work_Initialize(HH_Object_Water_10* pThis /* r2 */) {
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));
}

static u_int Object_Initialize(HH_Object_Water_10* pThis /* r16 */) {
    u_int result = 1; // r2
    pThis->Timer = 0.0f;
    pThis->Motion_Step = 0;
    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0});
    pThis->Area_WavePostTime[0] = 0.0f;
    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    _Area_Info_List_0x0036F510->pGrid_Y_Value = pThis->Area00_Grid_Y_Value;
    _Area_Info_List_0x0036F510->pST_Defference = pThis->ST_Defference;
    return result;
}

static u_int Object_Draw(HH_Object_Water_10* pThis /* r22 */, float* pGrid_Y_Value /* r21 */, float* WorldLocation /* r17 */, u_int Grid_X_Max /* r20 */, u_int Grid_Z_Max /* r18 */) {
    // Range: 0x25EFB0 -> 0x25F820
    static u_long _GifTag[2] = {
        SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
        GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F5A0
    static u_long _GifTag_Tri[2] = {
        SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 0, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
        GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)}; // @ 0x0036F5B0
    static float Light_Base[4] = {16.0f, 16.0f, 16.0f, 0.0f};                                                   // @ 0x0036F5C0
    static float Amb_Base[4] = {64.0f, 64.0f, 64.0f, 0.0f};                                                     // @ 0x0036F5D0
    static float Ambient_Color2[4] = {19.0f, 19.0f, 19.0f, 255.0f};                                             // @ 0x0036F5E0
    static float SpecularRgba[4] = {255.0f, 255.0f, 255.0f, 64.0f};                                             // @ 0x0036F5F0
    static float amb_alpha_72 = 32.0f;                                                                          // @ 0x0036F600
    static float light_alpha_73 = 128.0f;                                                                       // @ 0x0036F608                                                                               // @ 0x0036F640

    u_int result = 0;               // r2
    sceVif1Packet* pPk;             // r16
    u_int vertex_num;               // r2
    u_int x_grid_max;               // r2
    u_int z_grid_max;               // r29+0xB0
    u_int x_index;                  // r17
    u_int z_index;                  // r18
    u_int prim_type;                // r2
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

    pPk = HH_Vif1Packet_Current_Get();
    x_grid_max = Grid_X_Max;
    z_grid_max = Grid_Z_Max - 1;
    pPk_Current = NULL;

    HH_ClassWrapper_ViewDirection_Get(view_dir);
    HH_ClassWrapper_AmbientColor_Get(Ambient_Color);
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, Light_Color, Parameter);
    sceVu0MulVector(Light_Color, Light_Color, Light_Base);

    sceVu0MulVector(Ambient_Color, Ambient_Color, Amb_Base);

    Ambient_Color[3] = amb_alpha_72;
    Light_Color[3] = light_alpha_73;

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
        sceVu0FVECTOR Grid_Vertex0 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};       // r29+0x1E0
        sceVu0FVECTOR Grid_Vertex1 = {200.0f, 0.0f, 200.0f * (z_index + 1), 1.0f}; // r29+0x1F0
        sceVu0FVECTOR Grid_Vertex2 = {200.0f, 0.0f, 200.0f * z_index, 1.0f};       // r29+0x200

        sceVif1PkOpenGifTag(pPk, *(u_long128*)_GifTag_Tri);

        if (pPk_Current) {

            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, Grid_X_Max, 3, 3);
        }

        for (x_index = 0; x_index < Grid_X_Max; x_index++) {
            float Rgba[4];             // r29+0x210
            int xyzf[4];               // r29+0x220
            int rgba[4];               // r29+0x230
            u_int addr;                // r2
            float vec0[4];             // r29+0x240
            float vec1[4];             // r29+0x250
            float n0[4];               // r29+0x260
            float specular_ratio;      // r22
            float stq0[4];             // r29+0x270
            float stq1[4];             // r29+0x280
            float base;                // r2
            float color_scale;         // r29+0x290
            static float sx_87 = 7.0f; // @ 0x0036F480
            static float ty_88 = 7.0f; // @ 0x0036F488

            Grid_Vertex0[0] = Grid_Vertex1[0] = 200.0f * x_index;

            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 200.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_10_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_10_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_10_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

            base = 0.25f * (1.0f / (200.0f * ty_88));
            stq0[0] = stq1[0] = 0.25f * (Grid_Vertex0[0] / (200.0f * sx_87));
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

            specular_ratio = HH_ClassWrapper_SpecularRatio0_Calculator(view_dir, dir, n0, 0.991444f);

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
                        HH_ClassWrapper_SpecularRGBA_Add_BaseRGBA(rgba, Rgba, SpecularRgba, specular_ratio);
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
                    HH_ClassWrapper_SpecularRGBA_Add_BaseRGBA(rgba, Rgba, SpecularRgba, specular_ratio);
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

u_int HH_Class_Prefix_Water_10(void) {
    static u_int interval_133 = 1;
    static int i_131 = 0;                             // @ 0x011EB600
    static int j_132 = 0;                             // @ 0x011EB608
    u_int result = 1;                                 // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_long tex0;                                      // r2
    HH_Vif1PacketBuffer_GifTag_Open();
    tex0 = HH_Effect_Object_Texture_GS_Register_Tex0_Get(HH_WATER_10_TEX_ID, HH_WATER_10_CLUT_ID);
    sceVif1PkAddGsAD(pPk, SCE_GS_TEX0_1, tex0);
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, hh_class_water_clamp(i_131));
    if ((HH_DBG_Wrapper_Controller_KeyAssign_Check(1, 0, PAD_KEY_CIRCLE) != 0) && j_132 % interval_133 == 0) {
        i_131++;
        i_131 = clamp_n(i_131, 4);
    }
    j_132++;
    sceVif1PkAddGsAD(pPk, SCE_GS_ALPHA_1, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0x80));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

u_int HH_Class_Suffix_Water_10(void) {
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    u_int result = 1;                                 // r2
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_CLAMP_1, SCE_GS_SET_CLAMP(1 /* CLAMP (horizontal) */, 1 /* CLAMP (vertical) */, 0, 0, 0, 0));
    HH_Vif1PacketBuffer_GifTag_Close();
    return result;
}

static float degree_155 = 10.0f;
static float base_move_156 = 128.0f;
static float _interval_162 = 4.0f; // @ 0x0036F650
static float __distance_171 = 3200.0f;
static float __lost_time_172 = 10.0f;
static float __arri_173 = 40.0f;
static float __omega_174 = 612.0f;
static float __v_175 = 1200.0f;

u_int HH_Class_Water_10(void* pBlock /* r2 */, ImpactQueue_Element* pElement /* r18 */) {
    u_int result = 1;                   // r16
    HH_Object_Water_10* pThis = pBlock; // r17

    switch (pThis->Step) { /* irregular */
        case HH_WATER_10_STEP_INIT:
            Object_Initialize(pThis);
            pThis->Step = 1;
            break;

        case HH_WATER_10_STEP_DRAW: {
            float rad_omega;   // r29+0x100
            float rad;         // r29+0x100
            int area;          // r18
            sceVu0FVECTOR pos; // r29+0x90
            Grid_Work_Initialize(pThis);
            rad_omega = TO_RAD(degree_155) * pThis->Timer;
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
            pThis->ST_Defference[0] = ((base_move_156 + (base_move_156 * HH_MathWrapper_Cosf(rad))) / 512.0f);
            pThis->ST_Defference[1] = ((base_move_156 + (base_move_156 * HH_MathWrapper_Sinf(rad))) / 512.0f);

            area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List_0x0036F510, HH_WATER_10_TABLE_MAX);
            HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, HH_WATER_10_TABLE_MAX);
            if (area != -1) {
                HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List_0x0036F510, HH_WATER_10_TABLE_MAX, area);
            } else {
                pThis->Area_Enable_Table[0] = 1;
            }
            HH_ClassWrapper_JMS_WorldPosition_Get(pos);
            if (pos[1] < -6000.0f) {
                pThis->Area_Enable_Table[0] = 0;
            }
            {
                u_int i;
                for (i = 0; i < HH_WATER_10_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i])
                        if ((pThis->Timer - pThis->Area_WavePostTime[i] > _interval_162)) {
                            WaveArea_Infomeation* pInfo = &_Area_Info_List_0x0036F510[i];
                            Wave_Element wave_element; // r29+0x90
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
                            wave_element.Max_Distance0 = __distance_171;
                            wave_element.Lost_Time = __lost_time_172;
                            wave_element.Arrival = __arri_173;
                            wave_element.Omega = TO_RAD(__omega_174);
                            wave_element.Verocity = __v_175;
                            wave_element.Timer = 0;
                            HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 0x14, &wave_element);
                            pThis->Area_WavePostTime[i] = pThis->Timer;
                        }
                }
            }
            HH_DBG_Wrapper_T0_COUNT_Get();
            {
                u_int i;
                for (i = 0; i < HH_WATER_10_TABLE_MAX; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        WaveArea_Infomeation* pInfo = _Area_Info_List_0x0036F510; // r21
                        WaveArea_Infomeation* pArea_Info = &pInfo[i];             // r2
                        HH_Class_WaterCommon_WaveArea_Calculator(pArea_Info, pThis->Wave_Info, 0x14, i);
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], pArea_Info, pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
            }
            HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14);
            HH_DBG_Wrapper_T0_COUNT_Delta();
            if (GET_GAME_FLAG(15, 23)) {
                pThis->Step = 2;
            }
            pThis->Timer += 1.0f / 30.0f;
            break;
        }

        default:
        case HH_WATER_10_STEP_OFF:
            pThis->Header.Enable = 0;
            result = 0;
            break;
    }

    return result;
}
