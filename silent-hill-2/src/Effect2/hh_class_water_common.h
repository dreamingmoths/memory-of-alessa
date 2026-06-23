#ifndef HH_CLASS_WATER_COMMON_H
#define HH_CLASS_WATER_COMMON_H

#include "eestruct.h"

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

typedef struct WaveArea_Infomeation {
    // total size: 0x90
    sceVu0FVECTOR World_Location;    // offset 0x0, size 0x10
    sceVu0FVECTOR Grid_WH;           // offset 0x10, size 0x10
    u_int Grid_Index[2];             // offset 0x20, size 0x8
    u_int* pViewArea_List;           // offset 0x28, size 0x4
    u_int ViewArea_List_Max;         // offset 0x2C, size 0x4
    float* pGrid_Y_Value;            // offset 0x30, size 0x4
    sceVu0FVECTOR Specular_BaseRGBA; // offset 0x40, size 0x10
    sceVu0FVECTOR Ambient0_BaseRGBA; // offset 0x50, size 0x10
    sceVu0FVECTOR Ambient1_BaseRGBA; // offset 0x60, size 0x10
    sceVu0FVECTOR Light_BaseRGBA;    // offset 0x70, size 0x10
    float* pST_Defference;           // offset 0x80, size 0x4
} WaveArea_Infomeation;

typedef struct WaveArea_GridLink_Infomeation {
    // total size: 0x28
    float* pGrid_Y_Value_Link[2];   // offset 0x0, size 0x8
    u_int Vertical_Horizontal_Flag; // offset 0x8, size 0x4
    u_int Length;                   // offset 0xC, size 0x4
    u_int X_Index_Max[2];           // offset 0x10, size 0x8
    u_int X_Index_Start[2];         // offset 0x18, size 0x8
    u_int Z_Index_Start[2];         // offset 0x20, size 0x8
} WaveArea_GridLink_Infomeation;

static inline u_long hh_class_water_clamp(int i) {
    u_long umax = clamp_n_reverse(i, 2) << 7;
    u_long c = SCE_GS_SET_CLAMP(3, 3, 127, umax, 127, 0);
    u_long vmax = clamp_n(i, 2) << 7;
    return c | (vmax << 0x22);
}

static inline void word_struct_copy(u_int* dst, u_int* src, u_int size) {
    int i = size / 4;
    do {
        int w0 = src[0];
        src++, i--;
        dst[0] = w0;
        dst++;
    } while (i > 0);
}

u_int HH_Class_WaterCommon_WaveArea_Calculator(WaveArea_Infomeation* pInfo, Wave_Element* pElement_Table, u_int Element_Max, u_int Area_Index);
u_int HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(WaveArea_GridLink_Infomeation* pInfo);
int HH_Class_WaterCommon_WaveArea_CurrentArea_Search(float* Position, WaveArea_Infomeation* pInfo_Table, u_int Table_Max);
u_int HH_Class_WaterCommon_WaveElement_Addition(Wave_Element* pElement_Table, u_int Element_Max, Wave_Element* pAdd_Element);
void HH_Class_WaterCommon_WaveElement_Time_Count(Wave_Element* pElement_Table, u_int Element_Max);
void HH_Class_WaterCommon_Area_Enable_Table_Clear(u_int* pArea_Enable_Table, u_int Table_Max);
void HH_Class_WaterCommon_Area_Enable_Manager(u_int* pArea_Enable_Table, WaveArea_Infomeation* pInfo_Table, u_int Table_Max, int Current_Area);

#endif // HH_CLASS_WATER_COMMON_H
