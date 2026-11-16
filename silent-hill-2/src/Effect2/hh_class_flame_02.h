#ifndef HH_CLASS_FLAME_02_H
#define HH_CLASS_FLAME_02_H

#include "Effect2/hh_class_manager.h"

#define HH_FLAME_02_STEP_INIT    0
#define HH_FLAME_02_STEP_TIMER   1
#define HH_FLAME_02_STEP_DRAW    2
#define HH_FLAME_02_STEP_OFF     3
#define HH_FLAME_02_TEX_ID       3
#define HH_FLAME_02_CLUT_ID      0
#define HH_FLAME_02_PARTICLE_MAX 100

typedef struct HH_Object_Flame_02_Particle {
    // total size: 0x50
    sceVu0FVECTOR Location;   // offset 0x0, size 0x10
    sceVu0FVECTOR Verocity_0; // offset 0x10, size 0x10
    sceVu0FVECTOR RGBA;       // offset 0x20, size 0x10
    float Time;               // offset 0x30, size 0x4
    float Scale;              // offset 0x34, size 0x4
    float Convergence_Coff;   // offset 0x38, size 0x4
    float Life_Time;          // offset 0x3C, size 0x4
    u_int Texture_Kind;       // offset 0x40, size 0x4
} HH_Object_Flame_02_Particle;

typedef struct HH_Object_Flame_02 {
    // total size: 0x1F70
    Object_DataBlock_Header Header;                                 // offset 0x0, size 0x10
    u_char Step;                                                    // offset 0x10, size 0x1
    float Timer;                                                    // offset 0x14, size 0x4
    u_int Particle_DrawNum;                                         // offset 0x18, size 0x4
    sceVu0FVECTOR Wind;                                             // offset 0x20, size 0x10
    HH_Object_Flame_02_Particle Particle[HH_FLAME_02_PARTICLE_MAX]; // offset 0x30, size 0x1F40
} HH_Object_Flame_02;

u_int HH_Class_Prefix_Flame_02(void);

u_int HH_Class_Suffix_Flame_02(void);

u_int HH_Class_Flame_02(void* pBlock, ImpactQueue_Element* pElement);

#endif // HH_CLASS_FLAME_02_H
