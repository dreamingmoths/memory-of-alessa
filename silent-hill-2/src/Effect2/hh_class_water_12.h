#ifndef HH_CLASS_WATER_12_H
#define HH_CLASS_WATER_12_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_12_GRID_INDEX_GET(_x, _z) x_grid_max * (_z) + (_x)
#define HH_WATER_12_STEP_INIT    0
#define HH_WATER_12_STEP_DRAW    1
#define HH_WATER_12_STEP_OFF     2
#define HH_WATER_12_TABLE_MAX    1
#define HH_WATER_12_TEX_ID       7
#define HH_WATER_12_CLUT_ID      0

typedef struct HH_Object_Water_12 {
    // total size: 0xE80
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[493];        // offset 0x6C0, size 0x7B4
    float* pArea_Grid_Y_Value_Table[1];    // offset 0xE74, size 0x4
    float Area_WavePostTime[1];            // offset 0xE78, size 0x4
    u_int Area_Enable_Table[1];            // offset 0xE7C, size 0x4
} HH_Object_Water_12;

u_int HH_Class_Prefix_Water_12(void);
u_int HH_Class_Suffix_Water_12(void);
u_int HH_Class_Water_12(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_12_H
