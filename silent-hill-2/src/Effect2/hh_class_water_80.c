#include "sh2_common.h"
#include "SH2_common/sh2sys.h"

#include "sce/libvifpk.h"
#include "sce/libgraph.h"

#include "Effect2/hh_class_water_80.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_wrapper.h"
#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_object_vertex_info.h"
#include "Effect2/hh_math_wrapper.h"
#include "Effect2/hh_packet.h"

#pragma divbyzerocheck off

static void Grid_Work_Initialize(HH_Object_Water_80* pThis);
static u_int Object_Initialize(HH_Object_Water_80* pThis);
static u_int Object_Draw(HH_Object_Water_80* pThis, float* pGrid_Y_Value, float* WorldLocation, u_int Grid_X_Max, u_int Grid_Z_Max);

static u_int _area00_view_list[1] = {0};
static WaveArea_Infomeation _Area_Info_List[1] = {{
     /* .World_Location = */ {0.0f, 0.0f, 0.0f, 1.0f},
     /* .Grid_WH = */ {13500.0f, 0.0f, 13500.0f, 300.0f},
     /* .Grid_Index = */ {20, 1},
     /* .pViewArea_List = */ &_area00_view_list,
     /* .ViewArea_List_Max = */ 1,
     /* .pGrid_Y_Value = */ NULL,
     /* .Specular_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient0_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Ambient1_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .Light_BaseRGBA = */ {0.0f, 0.0f, 0.0f, 0.0f},
     /* .pST_Defference = */ NULL
}};

Wave_Element _wave_element_list[3] = {
    {
        /* .enable = */ true,
        /* .area = */ 0,
        /* .attribute = */ 0,
        /* .waveOrigin = */ 0,
        /* .postHistory = */ {},
        /* .power = */ 0.0f,
        /* .impactGridIndex = */ {},
        /* .maxDistance0 = */ 28800.0f,
        /* .lostTime = */ 60.0f,
        /* .timer = */ 0.0f,
        /* .arrival = */ 80.0f,
        /* .omega = */ 100.0f,
        /* .verocity = */ 400.0f,
    },
    {
        /* .enable = */ true,
        /* .area = */ 0,
        /* .attribute = */ 0,
        /* .waveOrigin = */ 0,
        /* .postHistory = */ {},
        /* .power = */ 0.0f,
        /* .impactGridIndex = */ {},
        /* .maxDistance0 = */ 28800.0f,
        /* .lostTime = */ 60.0f,
        /* .timer = */ 0.0f,
        /* .arrival = */ 50.0f,
        /* .omega = */ 200.0f,
        /* .verocity = */ 900.0f,
    },
    {
        /* .enable = */ true,
        /* .area = */ 0,
        /* .attribute = */ 0,
        /* .waveOrigin = */ 0,
        /* .postHistory = */ {},
        /* .power = */ 0.0f,
        /* .impactGridIndex = */ {},
        /* .maxDistance0 = */ 28800.0f,
        /* .lostTime = */ 60.0f,
        /* .timer = */ 0.0f,
        /* .arrival = */ 90.0f,
        /* .omega = */ 150.0f,
        /* .verocity = */ 500.0f,
    }
};


#line 208
static void Grid_Work_Initialize(HH_Object_Water_80* pThis) {
    #line 210
    memset(pThis->Area00_Grid_Y_Value, 0, sizeof(pThis->Area00_Grid_Y_Value));
}

#line 224
static u_int Object_Initialize(HH_Object_Water_80* pThis) {
    #line 231
    u_int result = true;
    pThis->Timer = 0.0f;
    
    pThis->Motion_Step = 0;
    
    sceVu0CopyVector(pThis->ST_Defference, (sceVu0FVECTOR){0});
    sceVu0CopyVector(pThis->Location_Defference, (sceVu0FVECTOR){0});
    
    pThis->Area_WavePostTime[0] = 0.0f;
    
    pThis->pArea_Grid_Y_Value_Table[0] = pThis->Area00_Grid_Y_Value;
    
    _Area_Info_List->pGrid_Y_Value = pThis->Area00_Grid_Y_Value;
 
    #line 295
    return result;
}

#line 449           
static u_int Object_Draw(HH_Object_Water_80* pThis, float* pGrid_Y_Value, float* WorldLocation, u_int Grid_X_Max, u_int Grid_Z_Max) {
    static u_long _GifTag[2] = {
        SCE_GIF_SET_TAG(0, 0, 0, 0, SCE_GIF_PACKED, 1),
        GIF_REG(SCE_GIF_PACKED_AD, 0) | GIF_REG(SCE_GS_PRIM, 1) | GIF_REG(SCE_GS_PRIM, 2) | GIF_REG(SCE_GS_PRIM, 3)};
    static u_long _GifTag_Tri[2] = {
        SCE_GIF_SET_TAG(0, 0, 1, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 1, 0, 0, 0, 0), SCE_GIF_PACKED, 3),
        GIF_REG(SCE_GS_ST, 0) | GIF_REG(SCE_GS_RGBAQ, 1) | GIF_REG(SCE_GS_XYZF2, 2) | GIF_REG(SCE_GS_PRIM, 3)};
    static sceVu0FVECTOR Light_Base = {80.0f, 80.0f, 80.0f, 80.0f}; // @ 0x0037D700
    static sceVu0FVECTOR Ambient_Color = {16.0f, 16.0f, 16.0f, 70.0f}; // @ 0x0037D710
    static float fog_ratio_f = 1.0f; // @ 0x0037D720
    static sceVu0FVECTOR _n = {0.0f, -1.0f, 0.0f, 0.0f}; // @ 0x0037D730
    static u_int flag = 0; // @ 0x01F01BE0


    
    u_int result = false; // r2
    sceVif1Packet* pPk; // r16
    u_int vertex_num; // r2
    u_int x_grid_max; // r2
    u_int z_grid_max; // r23
    u_int x_index; // r17
    u_int z_index; // r18
    u_int prim_type; // r2
    sceVu0FMATRIX lwm; // r29+0xA0
    sceVu0FMATRIX lsm; // r29+0xE0
    sceVu0FMATRIX clip_mat; // r29+0x120
    float* pGrid_Y = pGrid_Y_Value; // r2
    sceVu0FVECTOR view_dir; // r29+0x160
    sceVu0FVECTOR pos; // r29+0x170
    sceVu0FVECTOR dir; // r29+0x180
    sceVu0FVECTOR Light_Color; // r29+0x190
    sceVu0FVECTOR Parameter; // r29+0x1A0
    float far_z; // r29+0x270
    float cos_theta; // r29+0x270
    u_int* pPk_Current; // r19
    u_int* pPk_End; // r2
    sceVu0FVECTOR rev; // r29+0x1B0
    pPk = HH_Vif1Packet_Current_Get();
    
    
    z_grid_max = Grid_Z_Max - 1;
    x_grid_max = Grid_X_Max;
    pPk_Current = NULL;

    #line 509       
    HH_ClassWrapper_ViewDirection_Get(view_dir);
    
    HH_ClassWrapper_SpotLight_EnvironmentParameter_Get(pos, dir, Light_Color, Parameter);
    sceVu0MulVector(Light_Color, Light_Color, Light_Base);

    #line 526  
    sceVu0Normalize(dir, dir);
    
           
           
    if (flag) {
        float cos_theta;
           
        cos_theta = 2.0f * sceVu0InnerProduct(&_n, dir);
        
        sceVu0ScaleVectorXYZ(rev, &_n, cos_theta);
        sceVu0SubVector(dir, dir, rev);
    } else {
        
        dir[0] = 0.7768225f;
        dir[1] = 0.2888876f;
        dir[2] = 0.559206f;
    }
    sceVu0ScaleVectorXYZ(dir, dir, -1.0f);

    
           
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
        sceVu0FVECTOR Grid_Vertex0 = {300.0f, 0.0f, 300.0f * z_index, 1.0f};       // r29+0x1C0
        sceVu0FVECTOR Grid_Vertex1 = {300.0f, 0.0f, 300.0f * (z_index + 1), 1.0f}; // r29+0x1D0
        sceVu0FVECTOR Grid_Vertex2 = {300.0f, 0.0f, 300.0f * z_index, 1.0f};       // r29+0x2E0
        sceVu0FVECTOR Rgba;
        sceVif1PkOpenGifTag(pPk, *(u_long128*) _GifTag_Tri);

        if (pPk_Current) {

            
            
            
            
            
            
            HH_ClassWrapper_MemoryCopy128Align_DesignateCycle(pPk->pCurrent, pPk_Current, Grid_X_Max, 3, 3);
        }

        for (x_index = 0; x_index < Grid_X_Max; x_index++) {
            sceVu0IVECTOR xyzf; // r29+0x200
            sceVu0IVECTOR rgba; // r29+0x210
            u_int addr; // r2
            sceVu0FVECTOR vec0; // r29+0x220
            sceVu0FVECTOR vec1; // r29+0x230
            sceVu0FVECTOR n0; // r29+0x240
            float specular_ratio; // r29+0x270
            sceVu0FVECTOR stq0; // r29+0x250
            sceVu0FVECTOR stq1; // r29+0x260
            float base; // r2
            float color_scale; // r29+0x270
            
            Grid_Vertex0[0] = Grid_Vertex1[0] = 300.0f * x_index;

            Grid_Vertex2[0] = ((x_index + 1) % x_grid_max) * 300.0f;
            Grid_Vertex0[1] = pGrid_Y[HH_WATER_80_GRID_INDEX_GET(x_index, z_index)];
            Grid_Vertex1[1] = pGrid_Y[HH_WATER_80_GRID_INDEX_GET(x_index, z_index + 1)];
            Grid_Vertex2[1] = pGrid_Y[HH_WATER_80_GRID_INDEX_GET((x_index + 1) % x_grid_max, z_index)];

            
            {
                static float sx = 7.0f; // @ 0x0037D770
                static float ty = 7.0f; // @ 0x0037D778

                #line 616
                base = 0.25f * (1.0f / (300.0f * ty));
                
                stq0[0] = stq1[0] = 0.25f * (Grid_Vertex0[0] / (300.0f * sx));
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
            }



            
            if (z_index == 0) {
                float color_scale;
            
                HH_ClassWrapper_Transform_PerspectiveProjection_Clip_N(xyzf, stq0, lsm, clip_mat, Grid_Vertex0, 0x3f);


                
                color_scale = sceVu0InnerProduct(dir, n0);
                
                color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

                if (color_scale == 0.0f) {
                    sceVu0FTOI0Vector(rgba, Ambient_Color);
                } else {

                    sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);
                    sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                    sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);
                    
                    sceVu0FTOI0Vector(rgba, Rgba);
                }
                {   
                    float fog_col_f; // r1
                    u_int fog_col_i; // r2

                    
                    fog_col_f = HH_ClassWrapper_FogParameter_A_Get() + stq0[2] * HH_ClassWrapper_FogParameter_B_Get();
                    fog_col_i = HH_ClassWrapper_Float_Clamp(fog_col_f * fog_ratio_f, 0.0f, 255.0f);
                    
                    xyzf[3] &= ~0xFF0; // @note what's happening here?
                    xyzf[3] |= fog_col_i * 16;
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


                 
            color_scale = sceVu0InnerProduct(dir, n0);

            color_scale = HH_ClassWrapper_Float_Clamp(color_scale, 0.0f, 1.0f);

            if (color_scale == 0.0f) {
                sceVu0FTOI0Vector(rgba, Ambient_Color);
            } else {
                
                sceVu0ScaleVectorXYZ(Rgba, Light_Color, color_scale);
                sceVu0AddVector(Rgba, Rgba, Ambient_Color);
                sceVu0ClampVector(Rgba, Rgba, 0.0f, 255.0f);
                
                sceVu0FTOI0Vector(rgba, Rgba);
            }
            {   
                float fog_col_f; // r1
                u_int fog_col_i; // r2

                
                fog_col_f = HH_ClassWrapper_FogParameter_A_Get() + stq1[2] * HH_ClassWrapper_FogParameter_B_Get();
                fog_col_i = HH_ClassWrapper_Float_Clamp(fog_col_f * fog_ratio_f, 0.0f, 255.0f);
                
                xyzf[3] &= ~0xFF0; // @note what's happening here?
                xyzf[3] |= fog_col_i * 16;
            }

            if (x_index == 0) {
                pPk_Current = pPk->pCurrent;
            }
            *(u_long128*)pPk->pCurrent = *(u_long128*) stq1;
            ((u_long128*)pPk->pCurrent)++;
            *(u_long128*)pPk->pCurrent = *(u_long128*) rgba;
            ((u_long128*)pPk->pCurrent)++;
            *(u_long128*)pPk->pCurrent = *(u_long128*) xyzf;
            ((u_long128*)pPk->pCurrent)++;
        }
        sceVif1PkCloseGifTag(pPk);
    }
    pPk_End = pPk->pCurrent;

    HH_ClassWrapper_Packet_ADC_Flag_OnceMore_Set(pPk_End, x_grid_max, z_grid_max);

    sceVif1PkOpenGifTag(pPk, *(u_long128*) _GifTag);

    HH_Vif1PacketBuffer_GifTag_Close();

    return result;
}


#line 775
u_int HH_Class_Prefix_Water_80(void) {
    u_int result = true; // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16

    #line 783
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 1, 0, SCE_GS_TRUE, SCE_GS_DEPTH_GEQUAL));
    
           
           
           
           
           
           
           
           
           
           
    sceVif1PkAddGsAD(pPk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMCT16S, SCE_GS_FALSE)); // 0x0a0001c0
    HH_Vif1PacketBuffer_GifTag_Close();

   return result;
}

#line 813
u_int HH_Class_Suffix_Water_80(void) {
    u_int result = true; // r2
    sceVif1Packet* pPk = HH_Vif1Packet_Current_Get(); // r16
    
    HH_Vif1PacketBuffer_GifTag_Open();
    sceVif1PkAddGsAD(pPk, SCE_GS_ZBUF_1, SCE_GS_SET_ZBUF(448, SCE_GS_PSMCT16S, SCE_GS_TRUE)); // 0x0a0001c0
    sceVif1PkAddGsAD(pPk, SCE_GS_TEST_1, SCE_GS_SET_TEST(SCE_GS_FALSE, SCE_GS_ALPHA_ALWAYS, 0, 0, 0, 0, SCE_GS_TRUE, SCE_GS_DEPTH_GEQUAL));

    #line 831 
    HH_Vif1PacketBuffer_GifTag_Close();
    
    return result;
}


#line 848
u_int HH_Class_Water_80(void* pBlock, ImpactQueue_Element* pElement) {
    static float degree = 10.0f; // @ 0x0037D780
    static float base_move = 128.0f; // @ 0x0037D788
    static float _interval = 30.0f; // @ 0x0037D790
    static float delta_y_demo = 100.0f; // @ 0x0037D798
    static float delta_y = 50.0f; // @ 0x0037D7A0
    
    u_int result = true; // r16
    HH_Object_Water_80* pThis = pBlock; // r17

    switch (pThis->Step) {
        case HH_EFFECT_STEP_INIT:
            
            Object_Initialize(pThis);
            
            pThis->Step = HH_EFFECT_STEP_DRAW;
            pThis->Timer = 8.0f;
            break;

        case HH_EFFECT_STEP_DRAW: {
            float rad_omega, rad;
            Grid_Work_Initialize(pThis);
            
             
             
             
             
            rad = TO_RAD(degree); // r29+0x130
            rad_omega = shReflexAngle(rad * pThis->Timer); // r29+0x130
            
            pThis->ST_Defference[0] = (base_move + (base_move * HH_MathWrapper_Cosf(rad_omega))) / 512.0f;
            pThis->ST_Defference[1] = (base_move + (base_move * HH_MathWrapper_Sinf(rad_omega))) / 512.0f;


             
             {
                int area = HH_Class_WaterCommon_WaveArea_CurrentArea_Search(pElement->Option.Vector[0], _Area_Info_List, 1U);
                sceVu0FVECTOR temp; // r29+0x80

                HH_ClassWrapper_JMS_WorldPosition_Get(temp);

                HH_Class_WaterCommon_Area_Enable_Table_Clear(pThis->Area_Enable_Table, 1);
                if (area != -1) {
                    HH_Class_WaterCommon_Area_Enable_Manager(pThis->Area_Enable_Table, _Area_Info_List, 1U, area);
                } else {
                
                    pThis->Area_Enable_Table[0] = 1;
                }
                if (temp[2] > -7500.0f) {
                    pThis->Area_Enable_Table[0] = 0;
                }
                
             
             
             
             
             
             
             
             
             
             
             
             if (pThis->Area_Enable_Table[0] != 0)
                 if (pThis->Timer - pThis->Area_WavePostTime[0] > _interval) {
                        u_int i; // r18
                        float delta; // r29+0x130
                        WaveArea_Infomeation* pInfo; // r2
                        Wave_Element wave_element; // r29+0x90
                        u_int post_grid[4][2]; // r29+0xF0
                        u_int disable_num; // r19
                        
                        disable_num = rand() & 3; // @note % doesn't match
                        
             
                        post_grid[0][0] = rand() % _Area_Info_List->Grid_Index[0];
                        post_grid[0][1] = _Area_Info_List->Grid_Index[1] - 1;
                        
                        post_grid[1][0] = _Area_Info_List->Grid_Index[0] - 1;
                        post_grid[1][1] = rand() % _Area_Info_List->Grid_Index[1];
                        
                        post_grid[2][0] = rand() % _Area_Info_List->Grid_Index[0];
                        post_grid[2][1] = 0;
                        
                        post_grid[3][0] = 0;
                        post_grid[3][1] = rand() % _Area_Info_List->Grid_Index[1];
                        
             
                         for (i = 0; i < 4; i++) {
                            u_int x = post_grid[i][0]; // r20
                            u_int z = post_grid[i][1]; // r21
                            u_int wave_type_index = rand() % 3u; // r3
                            
                             if (disable_num != i) {
                                float omega; // @note not in dwarf
                                 
             
                                wave_element = _wave_element_list[wave_type_index];
                                wave_element.Impact_Grid_Index[0] = x;
                                wave_element.Impact_Grid_Index[1] = z;
                                omega = wave_element.Omega; // @note this is likely wrong
                                wave_element.Omega = TO_RAD(wave_element.Omega);
                                
                                HH_Class_WaterCommon_WaveElement_Addition(pThis->Wave_Info, 20, &wave_element);
                                pThis->Area_WavePostTime[0] = pThis->Timer;
                            }
                        }
                    }
                }
            {
                sceVu0FVECTOR temp; // r29+0x110
                u_int i; // r18
                WaveArea_Infomeation* pArea_Info; // r20
                sceVu0FVECTOR world_location; // r29+0x120
                HH_ClassWrapper_JMS_WorldPosition_Get(temp);
                temp[0] -= 6750.0f;
                if (GET_BIT(Sh2sys.main_status, 6)) {
                    temp[1] = 3500.0f + delta_y_demo;
                } else {
                    temp[1] = 3500.0f + delta_y;
                }
                temp[2] -= 6750.0f;
                sceVu0CopyVector(pThis->Location_Defference, temp);
                for (i = 0; i < 1; i++) {
                    if (pThis->Area_Enable_Table[i] != 0) {
                        pArea_Info = &_Area_Info_List[i];
                        sceVu0AddVector(&world_location[0], pArea_Info->World_Location, pThis->Location_Defference);
                        HH_Class_WaterCommon_WaveArea_Calculator(pArea_Info, pThis->Wave_Info, 20, i);
                        Object_Draw(pThis, pThis->pArea_Grid_Y_Value_Table[i], &world_location[0], pArea_Info->Grid_Index[0], pArea_Info->Grid_Index[1]);
                    }
                }
                HH_Class_WaterCommon_WaveElement_Time_Count(pThis->Wave_Info, 0x14U);
                pThis->Timer += TIME_STEP_30FPS;
            }
            break;
       }

        default:
        case HH_EFFECT_STEP_OFF:
            pThis->Header.Enable = false;
            result = false;
            break;
    }
    return result;
}

