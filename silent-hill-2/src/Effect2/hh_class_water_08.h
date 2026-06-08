#ifndef HH_CLASS_WATER_08_H
#define HH_CLASS_WATER_08_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#pragma divbyzerocheck off

#define HH_WATER_08_GRID_INDEX_GET(_x, _z) x_grid_max* (_z) + (_x)

#define HH_WATER_08_STEP_INIT    0
#define HH_WATER_08_STEP_DRAW    1
#define HH_WATER_08_STEP_OFF     2
#define HH_WATER_08_TABLE_MAX    7
#define HH_WATER_08_TEX_ID       4
#define HH_WATER_08_CLUT_ID      0

typedef struct HH_Object_Water_08 {
    // total size: 0x1700
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    sceVu0FVECTOR ST_Defference;           // offset 0x20, size 0x10
    struct Wave_Element Wave_Info[20];     // offset 0x30, size 0x690
    float Area00_Grid_Y_Value[64];         // offset 0x6C0, size 0x100
    float Area01_Grid_Y_Value[144];        // offset 0x7C0, size 0x240
    float Area02_Grid_Y_Value[252];        // offset 0xA00, size 0x3F0
    float Area03_Grid_Y_Value[88];         // offset 0xDF0, size 0x160
    float Area04_Grid_Y_Value[144];        // offset 0xF50, size 0x240
    float Area05_Grid_Y_Value[222];        // offset 0x1190, size 0x378
    float Area06_Grid_Y_Value[105];        // offset 0x1508, size 0x1A4
    float* pArea_Grid_Y_Value_Table[7];    // offset 0x16AC, size 0x1C
    float Area_WavePostTime[7];            // offset 0x16C8, size 0x1C
    u_int Area_Enable_Table[7];            // offset 0x16E4, size 0x1C
} HH_Object_Water_08;

u_int HH_Class_Prefix_Water_08(void);
u_int HH_Class_Suffix_Water_08(void);
u_int HH_Class_Water_08(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_08_H
