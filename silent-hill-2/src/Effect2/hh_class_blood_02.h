#ifndef HH_CLASS_BLOOD_02_H
#define HH_CLASS_BLOOD_02_H

#include "common.h"
#include "hh_class_manager.h"

typedef struct HH_Object_Blood_02 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_short Step; // offset 0x10, size 0x2
    u_char Vertex_Kind; // offset 0x12, size 0x1
    u_char Scale_Kind; // offset 0x13, size 0x1
    u_char Rgba_Kind; // offset 0x14, size 0x1
    u_char Motion_Step; // offset 0x15, size 0x1
    float Timer; // offset 0x18, size 0x4
    float Rotate_Y; // offset 0x1C, size 0x4
    float Rgba[4]; // offset 0x20, size 0x10
    float Scale[4]; // offset 0x30, size 0x10
}HH_Object_Blood_02;

typedef struct Motion_Table_Infomeation {
    float diff_time; // offset 0x0, size 0x4
    float diff_scale_ratio; // offset 0x4, size 0x4
    float diff_rgba_ratio; // offset 0x8, size 0x4
}Motion_Table_Infomeation;

typedef struct Vertex_Infomeation_List {
    float (* pVertex_List)[4]; // offset 0x0, size 0x4
    float (* pStq_List)[4]; // offset 0x4, size 0x4
    u_int Vertex_Max; // offset 0x8, size 0x4
    u_int Primitive_Type; // offset 0xC, size 0x4
}Vertex_Infomeation_List;

typedef struct shBattleShot {
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
}shBattleShot;

typedef struct shBattleFight {
    float test_a; // offset 0x0, size 0x4
    float test_b; // offset 0x4, size 0x4
    float test_c; // offset 0x8, size 0x4
}shBattleFight;

typedef struct shAttackInfo {
    u_short id; // offset 0x0, size 0x2
    u_short kind; // offset 0x2, size 0x2
    float ap; // offset 0x4, size 0x4
    float sp; // offset 0x8, size 0x4
    float min_range; // offset 0xC, size 0x4
    float max_range; // offset 0x10, size 0x4
    union {
        shBattleFight fight; // offset 0x0, size 0xC
        shBattleShot shot; // offset 0x0, size 0xC
    } hit_check; // offset 0x14, size 0xC
    u_char atk_start; // offset 0x20, size 0x1
    u_char atk_end; // offset 0x21, size 0x1
    u_char sd; // offset 0x22, size 0x1
    u_char eff; // offset 0x23, size 0x1
}shAttackInfo;;

u_int HH_Class_Prefix_Blood_02(void);
u_int HH_Class_Suffix_Blood_02(void);
u_int HH_Class_Blood_02(void* pBlock, ImpactQueue_Element* pElement);
u_int HH_Class_Blood_02_DesignateLocation_CollisionCheck(void* pBlock, ImpactQueue_Element* pElement, float* Target_Location);

#endif
