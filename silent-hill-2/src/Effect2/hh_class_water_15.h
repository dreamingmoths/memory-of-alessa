#ifndef HH_CLASS_WATER_15_H
#define HH_CLASS_WATER_15_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_15_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_15_STEP_INIT    0
#define HH_WATER_15_STEP_DRAW    1
#define HH_WATER_15_STEP_OFF     2
#define HH_WATER_15_TABLE_MAX    4
#define HH_WATER_15_TEX_ID       9
#define HH_WATER_15_CLUT_ID      0

typedef struct HH_Object_Water_15 {
    // total size: 0x18E0
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[261];        // offset 0x6C0, size 0x414
    float Area01_Grid_Y_Value[477];        // offset 0xAD4, size 0x774
    float Area02_Grid_Y_Value[273];        // offset 0x1248, size 0x444
    float Area03_Grid_Y_Value[136];        // offset 0x168C, size 0x220
    float* pArea_Grid_Y_Value_Table[4];    // offset 0x18AC, size 0x10
    float Area_WavePostTime[4];            // offset 0x18BC, size 0x10
    u_int Area_Enable_Table[4];            // offset 0x18CC, size 0x10
} HH_Object_Water_15;

u_int HH_Class_Prefix_Water_15(void);
u_int HH_Class_Suffix_Water_15(void);
u_int HH_Class_Water_15(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_15_H
