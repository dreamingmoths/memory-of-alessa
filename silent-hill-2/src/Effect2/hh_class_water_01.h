#ifndef HH_CLASS_WATER_01_H
#define HH_CLASS_WATER_01_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"
#define HH_WATER_01_STEP_INIT    0
#define HH_WATER_01_STEP_DRAW    1
#define HH_WATER_01_STEP_OFF     2
#define HH_WATER_01_TABLE_MAX    5
#define HH_WATER_01_TEX_ID       5
#define HH_WATER_01_CLUT_ID      0

typedef struct HH_Object_Water_01 {
    // total size: 0x13D0
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[217];        // offset 0x6C0, size 0x364
    float Area01_Grid_Y_Value[175];        // offset 0xA24, size 0x2BC
    float Area02_Grid_Y_Value[119];        // offset 0xCE0, size 0x1DC
    float Area03_Grid_Y_Value[91];         // offset 0xEBC, size 0x16C
    float Area04_Grid_Y_Value[217];        // offset 0x1028, size 0x364
    float* pArea_Grid_Y_Value_Table[5];    // offset 0x138C, size 0x14
    float Area_WavePostTime[5];            // offset 0x13A0, size 0x14
    u_int Area_Enable_Table[5];            // offset 0x13B4, size 0x14
} HH_Object_Water_01;

typedef struct WaveArea_Infomeation {
    // total size: 0x90
    float World_Location[4];         // offset 0x0, size 0x10
    float Grid_WH[4];                // offset 0x10, size 0x10
    u_int Grid_Index[2];             // offset 0x20, size 0x8
    u_int* pViewArea_List;           // offset 0x28, size 0x4
    u_int ViewArea_List_Max;         // offset 0x2C, size 0x4
    float* pGrid_Y_Value;            // offset 0x30, size 0x4
    sceVu0FVECTOR Specular_BaseRGBA; // offset 0x40, size 0x10
    sceVu0FVECTOR Ambient0_BaseRGBA; // offset 0x50, size 0x10
    sceVu0FVECTOR Ambient1_BaseRGBA; // offset 0x60, size 0x10
    sceVu0FVECTOR Light_BaseRGBA;    // offset 0x70, size 0x10
    float* pST_Defference;           // offset 0x80, size 0x4
} WaveArea_Infomeation;

typedef struct WaveArea_GridLink_Infomeation {
    // total size: 0x28
    float* pGrid_Y_Value_Link[2];   // offset 0x0, size 0x8
    u_int Vertical_Horizontal_Flag; // offset 0x8, size 0x4
    u_int Length;                   // offset 0xC, size 0x4
    u_int X_Index_Max[2];           // offset 0x10, size 0x8
    u_int X_Index_Start[2];         // offset 0x18, size 0x8
    u_int Z_Index_Start[2];         // offset 0x20, size 0x8
} WaveArea_GridLink_Infomeation;

u_int HH_Class_Prefix_Water_01(void);
u_int HH_Class_Suffix_Water_01(void);

#endif // HH_CLASS_WATER_01_H
