#ifndef HH_CLASS_WATER_14_H
#define HH_CLASS_WATER_14_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_14_GRID_INDEX_GET(_x, _z) x_grid_max * (_z) + (_x)

#define HH_WATER_14_STEP_INIT    0
#define HH_WATER_14_STEP_DRAW    1
#define HH_WATER_14_STEP_OFF     2
#define HH_WATER_14_TABLE_MAX    1
#define HH_WATER_14_TEX_ID       8
#define HH_WATER_14_CLUT_ID      0

typedef struct HH_Object_Water_14 {
    // total size: 0x10C0
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    sceVu0FVECTOR Location_Defference;     // offset 0x30, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x40, size 0x690
    float Area00_Grid_Y_Value[630];        // offset 0x6D0, size 0x9D8
    float* pArea_Grid_Y_Value_Table[1];    // offset 0x10A8, size 0x4
    float Area_WavePostTime[1];            // offset 0x10AC, size 0x4
    u_int Area_Enable_Table[1];            // offset 0x10B0, size 0x4
} HH_Object_Water_14;

u_int HH_Class_Prefix_Water_14(void);
u_int HH_Class_Suffix_Water_14(void);
u_int HH_Class_Water_14(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_14_H
