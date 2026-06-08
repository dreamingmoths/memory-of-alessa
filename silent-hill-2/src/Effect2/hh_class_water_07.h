#ifndef HH_CLASS_WATER_07_H
#define HH_CLASS_WATER_07_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_07_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_07_STEP_INIT    0
#define HH_WATER_07_STEP_DRAW    1
#define HH_WATER_07_STEP_OFF     2
#define HH_WATER_07_TABLE_MAX    7
#define HH_WATER_07_TEX_ID       4
#define HH_WATER_07_CLUT_ID      0

typedef struct HH_Object_Water_07 {
    // total size: 0x2310
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[40];     // offset 0x30, size 0xD20
    float Area00_Grid_Y_Value[400];        // offset 0xD50, size 0x640
    float Area01_Grid_Y_Value[192];        // offset 0x1390, size 0x300
    float Area02_Grid_Y_Value[84];         // offset 0x1690, size 0x150
    float Area03_Grid_Y_Value[224];        // offset 0x17E0, size 0x380
    float Area04_Grid_Y_Value[84];         // offset 0x1B60, size 0x150
    float Area05_Grid_Y_Value[266];        // offset 0x1CB0, size 0x428
    float Area06_Grid_Y_Value[120];        // offset 0x20D8, size 0x1E0
    float* pArea_Grid_Y_Value_Table[7];    // offset 0x22B8, size 0x1C
    float Area_WavePostTime[7];            // offset 0x22D4, size 0x1C
    u_int Area_Enable_Table[7];            // offset 0x22F0, size 0x1C
} HH_Object_Water_07;

u_int HH_Class_Prefix_Water_07(void);
u_int HH_Class_Suffix_Water_07(void);
u_int HH_Class_Water_07(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_07_H
