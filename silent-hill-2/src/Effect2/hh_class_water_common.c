#include "sh2_common.h"
#include "Effect2/hh_class_water_common.h"
#include "Effect2/hh_math_wrapper.h"

static u_int WaveArea_CurrentArea_CollisionCheck(float* Position, WaveArea_Infomeation* pInfo);
static u_int Area_ViewFrustum_Judge(WaveArea_Infomeation* pInfo);
static float Wave_Calculator(Wave_Element* pElement, float Distance, float Amplitude_ratio);
static u_int WaveArea_Calculator(WaveArea_Infomeation* pInfo, Wave_Element* pElement_Table, u_int Element_Max, u_int Area_Index);
static u_int WaveArea_GridLink_Y_Value_Calculator(WaveArea_GridLink_Infomeation* pInfo);
static int WaveArea_CurrentArea_Search(float* Position, WaveArea_Infomeation* pInfo_Table, u_int Table_Max);
static Wave_Element* WaveElement_Free_Search(Wave_Element* pElement_Table, u_int Element_Max);
static Wave_Element* WaveElement_Oldest_Search(Wave_Element* pElement_Table, u_int Element_Max);
static u_int WaveElement_Addition(Wave_Element* pElement_Table, u_int Element_Max, Wave_Element* pAdd_Element);
static void Area_Enable_Table_Clear(u_int* pArea_Enable_Table, u_int Table_Max);
static void Area_Enable_Manager(u_int* pArea_Enable_Table, WaveArea_Infomeation* pInfo_Table, u_int Table_Max, int Current_Area);

static float Wave_Calculator(Wave_Element* pElement /* r16 */, float Distance /* r29+0x30 */, float Amplitude_ratio /* r20 */) {

    float result = pElement->Omega * (pElement->Timer + (Distance / pElement->Verocity)); // r29+0x30

    float theta = reflex_angle(result); // r29+0x30

    return Amplitude_ratio * pElement->Arrival * HH_MathWrapper_Sinf(theta);
}

static u_int WaveArea_Calculator(WaveArea_Infomeation* pInfo /* r2 */, Wave_Element* pElement_Table /* r29+0xBC */, u_int Element_Max /* r29+0xB8 */, u_int Area_Index /* r29+0xB4 */) {
    u_int result = 0;                            // r2
    u_int i;                                     // r30
    u_int Grid_X_Max = pInfo->Grid_Index[0];     // r16
    u_int Grid_Z_Max = pInfo->Grid_Index[1];     // r23
    float Grid_WH = pInfo->Grid_WH[3];           // r20
    float* pGrid_Y_Value = pInfo->pGrid_Y_Value; // r17

    for (i = 0; i < Element_Max; i++) {
        Wave_Element* pElement = &pElement_Table[i];

        if (!pElement->Enable)
            continue;

        if (pElement->Area == Area_Index) {

            float distance_max = pElement->Max_Distance0;
            u_int impact_x = pElement->Impact_Grid_Index[0];
            u_int impact_z = pElement->Impact_Grid_Index[1];
            u_int x_count, z_count;
            float arrival_ratio = 1.0f - (pElement->Timer / pElement->Lost_Time);
            float arrival_distance = pElement->Verocity * pElement->Timer;

            if (arrival_ratio < 0.0f) {
                arrival_ratio = 0.0f;
            }
            distance_max = distance_max * arrival_ratio;

            for (z_count = 0; z_count < Grid_Z_Max; z_count++) {
                float z_distance = (((impact_z - z_count) * (impact_z - z_count))) * Grid_WH * Grid_WH;

                for (x_count = 0; x_count < Grid_X_Max; x_count++) {
                    float x_distance = ((impact_x - x_count) * (impact_x - x_count)) * Grid_WH * Grid_WH;
                    float distance = HH_MathWrapper_Sqrtf(z_distance + x_distance);

                    if (distance > distance_max)
                        continue;
                    if (distance <= arrival_distance) {

                        float amplitude_ratio = 1.0f - distance / (distance_max < arrival_distance ? distance_max : arrival_distance);
                        float y = Wave_Calculator(pElement, distance, amplitude_ratio);

                        pGrid_Y_Value[x_count + (z_count * Grid_X_Max)] += y;
                    }
                }
            }
        }
    }

    return result;
}

static u_int WaveArea_GridLink_Y_Value_Calculator(WaveArea_GridLink_Infomeation* pInfo /* r2 */) {
    u_int result = 1;     // r2
    u_int i;              // r5
    u_int link_index0;    // r6
    u_int link_index1;    // r7
    u_int index0_add = 1, // r8
        index1_add = 1;   // r9

    switch (pInfo->Vertical_Horizontal_Flag) {
        case 0:
            index0_add = pInfo->X_Index_Max[0];
            index1_add = pInfo->X_Index_Max[1];
            break;

        case 1:
            break;
    }
    link_index0 = pInfo->X_Index_Start[0] + (pInfo->X_Index_Max[0] * pInfo->Z_Index_Start[0]);
    link_index1 = pInfo->X_Index_Start[1] + (pInfo->X_Index_Max[1] * pInfo->Z_Index_Start[1]);

    for (i = 0; i < pInfo->Length; i++, link_index0 += index0_add, link_index1 += index1_add) {
        pInfo->pGrid_Y_Value_Link[0][link_index0] = pInfo->pGrid_Y_Value_Link[1][link_index1] = pInfo->pGrid_Y_Value_Link[0][link_index0] + pInfo->pGrid_Y_Value_Link[1][link_index1];
    }

    return result;
}

static int WaveArea_CurrentArea_Search(float* Position /* r20 */, WaveArea_Infomeation* pInfo_Table /* r19 */, u_int Table_Max /* r18 */) {
    int result = -1; // r16
    u_int i;         // r17

    for (i = 0; i < Table_Max; i++) {
        WaveArea_Infomeation* pInfo = &pInfo_Table[i]; // r2;

        if (WaveArea_CurrentArea_CollisionCheck(Position, pInfo) != 0) {
            result = i;
            break;
        }
    }

    return result;
}

static u_int WaveArea_CurrentArea_CollisionCheck(float* Position /* r2 */, WaveArea_Infomeation* pInfo /* r17 */) {
    u_int result = 0;   // r16
    float check_pos[4]; // r29+0x30

    sceVu0SubVector(check_pos, Position, pInfo->World_Location);

    if (0.0f < check_pos[0] && check_pos[0] < pInfo->Grid_WH[0] && 0.0f < check_pos[2] && check_pos[2] < pInfo->Grid_WH[2]) {
        result = 1;
    }

    return result;
}

static Wave_Element* WaveElement_Free_Search(Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */) {
    Wave_Element* result = NULL; // r2
    u_int i;                     // r7

    for (i = 0; i < Element_Max; i++) {
        Wave_Element* pElement = &pElement_Table[i];

        if (!pElement->Enable) {
            result = pElement;
            break;
        }
    }

    return result;
}

static Wave_Element* WaveElement_Oldest_Search(Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */) {
    Wave_Element* result = NULL; // r2
    u_int i;                     // r7
    float time = 0.0f;           // r29

    for (i = 0; i < Element_Max; i++) {
        Wave_Element* pElement = &pElement_Table[i];

        if (pElement->Enable != 0) {
            if (time < pElement->Timer) {
                time = pElement->Timer;
                result = pElement;
            }
        }
    }
    return result;
}

static u_int WaveElement_Addition(Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */, Wave_Element* pAdd_Element /* r8 */) {
    u_int result = 1;                                                                   // r2
    Wave_Element* pFree_Element = WaveElement_Free_Search(pElement_Table, Element_Max); // r2

    if (pFree_Element == NULL) {
        pFree_Element = WaveElement_Oldest_Search(pElement_Table, Element_Max);
    }
    word_struct_copy(pFree_Element, pAdd_Element, sizeof(Wave_Element));

    return result;
}

static void Area_Enable_Table_Clear(u_int* pArea_Enable_Table /* r2 */, u_int Table_Max /* r2 */) {
    u_int i; // r6

    for (i = 0; i < Table_Max; i++) {
        pArea_Enable_Table[i] = 0;
    }
}

static void Area_Enable_Manager(u_int* pArea_Enable_Table /* r20 */, WaveArea_Infomeation* pInfo_Table /* r19 */, u_int Table_Max /* r18 */, int Current_Area /* r17 */) {
    WaveArea_Infomeation* pInfo_Cur = &pInfo_Table[Current_Area]; // r5
    u_int i;                                                      // r16
    u_int area;                                                   // r2

    for (i = 0; i < pInfo_Cur->ViewArea_List_Max; i++) {
        area = pInfo_Cur->pViewArea_List[i];
        pArea_Enable_Table[area] = 1;
    }

    for (i = 0; i < Table_Max; i++) {
        WaveArea_Infomeation* pInfo = &pInfo_Table[i];

        if (!pArea_Enable_Table[i] || i == Current_Area)
            continue;
        if (!Area_ViewFrustum_Judge(pInfo))
            pArea_Enable_Table[i] = 0;
    }
}

static u_int Area_ViewFrustum_Judge(WaveArea_Infomeation* pInfo /* r18 */) {
    u_int result = 0;        // r16
    sceVu0FMATRIX clip_mat;  // r29+0x40
    sceVu0FMATRIX vec_array; // r29+0x80
    u_int j;                 // r17

    for (j = 0; j < 4; j++) {
        sceVu0CopyVector(vec_array[j], pInfo->World_Location);
    }
    vec_array[1][2] += pInfo->Grid_WH[2];
    vec_array[2][0] += pInfo->Grid_WH[0];
    vec_array[3][0] += pInfo->Grid_WH[0];
    vec_array[3][2] += pInfo->Grid_WH[2];

    HH_ClassWrapper_ViewFrustum_Primitive_ClipMatrix_Get(clip_mat);

    if (HH_ClassWrapper_Point_Clip_Judge(clip_mat, vec_array, 4) != 4) {
        result = 1;
    }

    return result;
}

u_int HH_Class_WaterCommon_WaveArea_Calculator(WaveArea_Infomeation* pInfo /* r2 */, Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */, u_int Area_Index /* r2 */) {
    return WaveArea_Calculator(pInfo, pElement_Table, Element_Max, Area_Index);
}

u_int HH_Class_WaterCommon_WaveArea_GridLink_Y_Value_Calculator(WaveArea_GridLink_Infomeation* pInfo /* r2 */) {
    return WaveArea_GridLink_Y_Value_Calculator(pInfo);
}

int HH_Class_WaterCommon_WaveArea_CurrentArea_Search(float* Position /* r2 */, WaveArea_Infomeation* pInfo_Table /* r2 */, u_int Table_Max /* r2 */) {
    return WaveArea_CurrentArea_Search(Position, pInfo_Table, Table_Max);
}

u_int HH_Class_WaterCommon_WaveElement_Addition(Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */, Wave_Element* pAdd_Element /* r2 */) {
    return WaveElement_Addition(pElement_Table, Element_Max, pAdd_Element);
}

void HH_Class_WaterCommon_WaveElement_Time_Count(Wave_Element* pElement_Table /* r2 */, u_int Element_Max /* r2 */) {
    Wave_Element* pElement; // r6
    u_int i;                // r7

    for (i = 0; i < Element_Max; i++) {
        pElement = &pElement_Table[i];
        if (pElement->Enable != 0) {
            pElement->Timer += 1.0f / 30.0f;
            if (pElement->Timer > pElement->Lost_Time) {
                pElement->Enable = 0;
            }
        }
    }
}

void HH_Class_WaterCommon_Area_Enable_Table_Clear(u_int* pArea_Enable_Table /* r2 */, u_int Table_Max /* r2 */) {
    Area_Enable_Table_Clear(pArea_Enable_Table, Table_Max);
}

void HH_Class_WaterCommon_Area_Enable_Manager(u_int* pArea_Enable_Table /* r2 */, WaveArea_Infomeation* pInfo_Table /* r2 */, u_int Table_Max /* r2 */, int Current_Area /* r2 */) {
    Area_Enable_Manager(pArea_Enable_Table, pInfo_Table, Table_Max, Current_Area);
}
