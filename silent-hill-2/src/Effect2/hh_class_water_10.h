#ifndef HH_CLASS_WATER_10_H
#define HH_CLASS_WATER_10_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_10_STEP_INIT    0
#define HH_WATER_10_STEP_DRAW    1
#define HH_WATER_10_STEP_OFF     2
#define HH_WATER_10_TABLE_MAX    1
#define HH_WATER_10_TEX_ID       0xEU
#define HH_WATER_10_CLUT_ID      0
#define HH_WATER_10_GRID_INDEX_GET(_x, _z) x_grid_max * (_z) + (_x)

typedef struct HH_Object_Water_10 {
    // total size: 0x1440
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[861];        // offset 0x6C0, size 0xD74
    float* pArea_Grid_Y_Value_Table[1];    // offset 0x1434, size 0x4
    float Area_WavePostTime[1];            // offset 0x1438, size 0x4
    u_int Area_Enable_Table[1];            // offset 0x143C, size 0x4
} HH_Object_Water_10;

#endif // HH_CLASS_WATER_10_H
