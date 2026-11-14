#ifndef HH_CLASS_SMOKE_00_H
#define HH_CLASS_SMOKE_00_H

#include "Effect2/hh_class_manager.h"

typedef struct Smoke_Initialize_Parameter {
    u_int ParticleDraw_Num; // offset 0x0, size 0x4
    u_int Flag[3]; // offset 0x4, size 0xC
    float Convergence_Coff; // offset 0x10, size 0x4
    float Convergence_Coff_Sub; // offset 0x14, size 0x4
    float Gravity_Suppress_Coff; // offset 0x18, size 0x4
    float Base_Alpha; // offset 0x1C, size 0x4
    float Base_Scale; // offset 0x20, size 0x4
    float Base_Time; // offset 0x24, size 0x4
    float Rand_Time_Width; // offset 0x28, size 0x4
    sceVu0IVECTOR Verocity_0; // offset 0x30, size 0x10
    sceVu0IVECTOR Length_Max; // offset 0x40, size 0x10
    sceVu0FVECTOR RGBA; // offset 0x50, size 0x10
} Smoke_Initialize_Parameter;

typedef struct HH_Object_Smoke_00_Particle {
    sceVu0FVECTOR Location; // offset 0x0, size 0x10
    sceVu0FVECTOR Verocity_0; // offset 0x10, size 0x10
    sceVu0FVECTOR RGBA; // offset 0x20, size 0x10
    float Time; // offset 0x30, size 0x4
    float Scale; // offset 0x34, size 0x4
    float Convergence_Coff; // offset 0x38, size 0x4
    float Life_Time; // offset 0x3C, size 0x4
    u_int Texture_Kind; // offset 0x40, size 0x4
} HH_Object_Smoke_00_Particle;

typedef struct HH_Object_Smoke_00 {
    Object_DataBlock_Header Header; // offset 0x0, size 0x10
    u_char Step; // offset 0x10, size 0x1
    float Timer; // offset 0x14, size 0x4
    u_int Particle_DrawNum; // offset 0x18, size 0x4
    HH_Object_Smoke_00_Particle Particle[20]; // offset 0x20, size 0x640
} HH_Object_Smoke_00;

u_int HH_Class_Prefix_Smoke_00(void);

u_int HH_Class_Suffix_Smoke_00(void);

u_int HH_Class_Smoke_00(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_SMOKE_00_H
