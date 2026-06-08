#ifndef HH_CLASS_WATER_03_H
#define HH_CLASS_WATER_03_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_03_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_03_STEP_INIT    0
#define HH_WATER_03_STEP_DRAW    1
#define HH_WATER_03_STEP_OFF     2
#define HH_WATER_03_TABLE_MAX    4
#define HH_WATER_03_TEX_ID       4
#define HH_WATER_03_CLUT_ID      0

typedef struct HH_Object_Water_03 {
    // total size: 0x1920
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[40];     // offset 0x30, size 0xD20
    float Area00_Grid_Y_Value[104];        // offset 0xD50, size 0x1A0
    float Area01_Grid_Y_Value[168];        // offset 0xEF0, size 0x2A0
    float Area02_Grid_Y_Value[160];        // offset 0x1190, size 0x280
    float Area03_Grid_Y_Value[312];        // offset 0x1410, size 0x4E0
    float* pArea_Grid_Y_Value_Table[4];    // offset 0x18F0, size 0x10
    float Area_WavePostTime[4];            // offset 0x1900, size 0x10
    u_int Area_Enable_Table[4];            // offset 0x1910, size 0x10
} HH_Object_Water_03;

u_int HH_Class_Prefix_Water_03(void);
u_int HH_Class_Suffix_Water_03(void);
u_int HH_Class_Water_03(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_03_H
