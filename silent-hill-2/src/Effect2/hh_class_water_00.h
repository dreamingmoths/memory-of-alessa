#ifndef HH_CLASS_WATER_00_H
#define HH_CLASS_WATER_00_H

#include "Effect2/hh_class_manager.h"

#define HH_WATER_00_GRID_INDEX_GET(_x, _z) (_z) * HH_WATER_00_GRID_SIZE + (_x)
#define HH_WATER_00_GRID_SIZE 0x30
#define HH_WATER_00_TEX_ID  0xCU
#define HH_WATER_00_CLUT_ID 0x0

typedef struct Wave_Element {
    // total size: 0x54
    u_int Enable; // offset 0x0, size 0x4
    u_int Area; // offset 0x4, size 0x4
    u_int Attribute; // offset 0x8, size 0x4
    u_int Wave_Origin; // offset 0xC, size 0x4
    u_int Post_History[4][2]; // offset 0x10, size 0x20
    float Power; // offset 0x30, size 0x4
    u_int Impact_Grid_Index[2]; // offset 0x34, size 0x8
    float Max_Distance0; // offset 0x3C, size 0x4
    float Lost_Time; // offset 0x40, size 0x4
    float Timer; // offset 0x44, size 0x4
    float Arrival; // offset 0x48, size 0x4
    float Omega; // offset 0x4C, size 0x4
    float Verocity; // offset 0x50, size 0x4
} Wave_Element;

typedef struct HH_Object_Water_00 {
    // total size: 0x4970
    struct Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step; // offset 0x10, size 0x1
    u_char Motion_Step; // offset 0x11, size 0x1
    float Timer; // offset 0x14, size 0x4
    u_int CurrentBuffer; // offset 0x18, size 0x4
    struct Wave_Element Wave_Info[4]; // offset 0x1C, size 0x150
    float Grid_Y_Value[2][2304]; // offset 0x16C, size 0x4800
} HH_Object_Water_00;

u_int HH_Class_Prefix_Water_00(void);
u_int HH_Class_Suffix_Water_00(void);
u_int HH_Class_Water_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_WATER_00_H
