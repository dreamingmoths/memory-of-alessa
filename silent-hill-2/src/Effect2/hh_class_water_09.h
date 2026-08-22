#ifndef HH_CLASS_WATER_09_H
#define HH_CLASS_WATER_09_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"
#include "sce/libvu0.h"

#define HH_WATER_09_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_09_STEP_INIT    0
#define HH_WATER_09_STEP_DRAW    1
#define HH_WATER_09_STEP_OFF     2
#define HH_WATER_09_TABLE_MAX    3
#define HH_WATER_09_TEX_ID       4
#define HH_WATER_09_CLUT_ID      0

typedef struct HH_Object_Water_09 {
    // total size: 0xE70
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[200];        // offset 0x6C0, size 0x320
    float Area01_Grid_Y_Value[160];        // offset 0x9E0, size 0x280
    float Area02_Grid_Y_Value[120];        // offset 0xC60, size 0x1E0
    float* pArea_Grid_Y_Value_Table[3];    // offset 0xE40, size 0xC
    float Area_WavePostTime[3];            // offset 0xE4C, size 0xC
    u_int Area_Enable_Table[3];            // offset 0xE58, size 0xC
} HH_Object_Water_09;

u_int HH_Class_Prefix_Water_09(void);
u_int HH_Class_Suffix_Water_09(void);
u_int HH_Class_Water_09(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_09_H
