#ifndef HH_CLASS_WATER_06_H
#define HH_CLASS_WATER_06_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_06_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_06_STEP_INIT    0
#define HH_WATER_06_STEP_DRAW    1
#define HH_WATER_06_STEP_OFF     2
#define HH_WATER_06_TABLE_MAX    8
#define HH_WATER_06_TEX_ID       4
#define HH_WATER_06_CLUT_ID      0

typedef struct HH_Object_Water_06 {
    // total size: 0x2060
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[256];        // offset 0x6C0, size 0x400
    float Area01_Grid_Y_Value[288];        // offset 0xAC0, size 0x480
    float Area02_Grid_Y_Value[192];        // offset 0xF40, size 0x300
    float Area03_Grid_Y_Value[168];        // offset 0x1240, size 0x2A0
    float Area04_Grid_Y_Value[176];        // offset 0x14E0, size 0x2C0
    float Area05_Grid_Y_Value[216];        // offset 0x17A0, size 0x360
    float Area06_Grid_Y_Value[168];        // offset 0x1B00, size 0x2A0
    float Area07_Grid_Y_Value[152];        // offset 0x1DA0, size 0x260
    float* pArea_Grid_Y_Value_Table[8];    // offset 0x2000, size 0x20
    float Area_WavePostTime[8];            // offset 0x2020, size 0x20
    u_int Area_Enable_Table[8];            // offset 0x2040, size 0x20
} HH_Object_Water_06;

u_int HH_Class_Prefix_Water_06(void);
u_int HH_Class_Suffix_Water_06(void);
u_int HH_Class_Water_06(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_06_H
