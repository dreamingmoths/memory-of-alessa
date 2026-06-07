#ifndef HH_CLASS_WATER_COMMON_H
#define HH_CLASS_WATER_COMMON_H

#include "eetypes.h"

typedef struct Wave_Element {
    // total size: 0x54
    u_int Enable;               // offset 0x0, size 0x4
    u_int Area;                 // offset 0x4, size 0x4
    u_int Attribute;            // offset 0x8, size 0x4
    u_int Wave_Origin;          // offset 0xC, size 0x4
    u_int Post_History[4][2];   // offset 0x10, size 0x20
    float Power;                // offset 0x30, size 0x4
    u_int Impact_Grid_Index[2]; // offset 0x34, size 0x8
    float Max_Distance0;        // offset 0x3C, size 0x4
    float Lost_Time;            // offset 0x40, size 0x4
    float Timer;                // offset 0x44, size 0x4
    float Arrival;              // offset 0x48, size 0x4
    float Omega;                // offset 0x4C, size 0x4
    float Verocity;             // offset 0x50, size 0x4
} Wave_Element;

#endif // HH_CLASS_WATER_COMMON_H
