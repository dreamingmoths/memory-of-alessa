#ifndef HH_CLASS_WATER_00_H
#define HH_CLASS_WATER_00_H

#include "Effect2/hh_class_manager.h"
#include "Effect2/hh_class_water_common.h"

#define HH_WATER_00_GRID_INDEX_GET(_x, _z) (_z) * HH_WATER_00_GRID_SIZE + (_x)
#define HH_WATER_00_GRID_SIZE    0x30
#define HH_WATER_00_TEX_ID       0xCU
#define HH_WATER_00_CLUT_ID      0x0
#define HH_WATER_00_STEP_INIT    0
#define HH_WATER_00_STEP_MOTION  1
#define HH_WATER_00_STEP_DRAW    2
#define HH_WATER_00_STEP_OFF     3

typedef struct HH_Object_Water_00 {
    // total size: 0x4970
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step;                           // offset 0x10, size 0x1
    u_char Motion_Step;                    // offset 0x11, size 0x1
    float Timer;                           // offset 0x14, size 0x4
    u_int CurrentBuffer;                   // offset 0x18, size 0x4
    struct Wave_Element Wave_Info[4];      // offset 0x1C, size 0x150
    float Grid_Y_Value[2][2304];           // offset 0x16C, size 0x4800
} HH_Object_Water_00;

u_int HH_Class_Prefix_Water_00(void);
u_int HH_Class_Suffix_Water_00(void);
u_int HH_Class_Water_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_00_H
