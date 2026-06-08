#ifndef HH_CLASS_WATER_04_H
#define HH_CLASS_WATER_04_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_04_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_04_STEP_INIT    0
#define HH_WATER_04_STEP_DRAW    1
#define HH_WATER_04_STEP_OFF     2
#define HH_WATER_04_TABLE_MAX    7
#define HH_WATER_04_TEX_ID       4
#define HH_WATER_04_CLUT_ID      0

typedef struct HH_Object_Water_04 {
    // total size: 0x1AD0
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[40];     // offset 0x30, size 0xD20
    float Area00_Grid_Y_Value[152];        // offset 0xD50, size 0x260
    float Area01_Grid_Y_Value[84];         // offset 0xFB0, size 0x150
    float Area02_Grid_Y_Value[152];        // offset 0x1100, size 0x260
    float Area03_Grid_Y_Value[160];        // offset 0x1360, size 0x280
    float Area04_Grid_Y_Value[114];        // offset 0x15E0, size 0x1C8
    float Area05_Grid_Y_Value[120];        // offset 0x17A8, size 0x1E0
    float Area06_Grid_Y_Value[60];         // offset 0x1988, size 0xF0
    float* pArea_Grid_Y_Value_Table[7];    // offset 0x1A78, size 0x1C
    float Area_WavePostTime[7];            // offset 0x1A94, size 0x1C
    u_int Area_Enable_Table[7];            // offset 0x1AB0, size 0x1C
} HH_Object_Water_04;

u_int HH_Class_Prefix_Water_04(void);
u_int HH_Class_Suffix_Water_04(void);
u_int HH_Class_Water_04(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_04_H
