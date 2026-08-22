#ifndef LIGHT_N_H
#define LIGHT_N_H
#include "sce/libvu0.h"

typedef struct Light {
    // total size: 0xA0
    int kind;                // offset 0x0, size 0x4
    float intensity;         // offset 0x4, size 0x4
    float influence;         // offset 0x8, size 0x4
    float intensity2;        // offset 0xC, size 0x4
    float influence2;        // offset 0x10, size 0x4
    signed short cid;        // offset 0x14, size 0x2
    signed short fakekind;   // offset 0x16, size 0x2
    float inf_fac;           // offset 0x18, size 0x4
    void* DrawEnv_LightData; // offset 0x1C, size 0x4
    sceVu0FVECTOR pos;       // offset 0x20, size 0x10
    sceVu0FVECTOR vpos;      // offset 0x30, size 0x10
    sceVu0FVECTOR dir;       // offset 0x40, size 0x10
    sceVu0FVECTOR vdir;      // offset 0x50, size 0x10
    sceVu0FVECTOR color;     // offset 0x60, size 0x10
    float f_start;           // offset 0x70, size 0x4
    float f_end;             // offset 0x74, size 0x4
    float s_start;           // offset 0x78, size 0x4
    float s_end;             // offset 0x7C, size 0x4
    float f_a;               // offset 0x80, size 0x4
    float f_b;               // offset 0x84, size 0x4
    float s_a;               // offset 0x88, size 0x4
    float s_b;               // offset 0x8C, size 0x4
    float f_ra;              // offset 0x90, size 0x4
    float f_rb;              // offset 0x94, size 0x4
} Light;

typedef struct LightWork {
    // total size: 0x9E0
    struct Light lights[12]; // offset 0x0, size 0x780
    int n_valid_parallels; // offset 0x780, size 0x4
    int n_valid_parallel_matrices; // offset 0x784, size 0x4
    int n_valid_extras; // offset 0x788, size 0x4
    int n_valid_shadows; // offset 0x78C, size 0x4
    sceVu0FMATRIX nlms[2]; // offset 0x790, size 0x80
    sceVu0FMATRIX vnlms[2]; // offset 0x810, size 0x80
    sceVu0FMATRIX lcms[2]; // offset 0x890, size 0x80
    struct Light* valid_extras[6]; // offset 0x910, size 0x18
    struct Light* valid_shadows[8]; // offset 0x928, size 0x20
    float reflection_brightness; // offset 0x948, size 0x4
    sceVu0FVECTOR reflection_color; // offset 0x950, size 0x10
    float nhm[4][4]; // offset 0x960, size 0x40
    float vnhm[4][4]; // offset 0x9A0, size 0x40
} LightWork;

float ktClampFloat(float x, float l, float h);

Light* LightPointer(int n);

void LightDelete(int n);

void LightDeleteAll(void);

void LightSetParallel(int n, float* dir, float* color);

void LightSetPoint(int n, float* pos, float* color, float f_start, float f_end);

void LightSetFakePoint(int n, float* pos, float* color, float f_start, float f_end);

void LightSetFakeSpot(int n, float* pos, int unused /* @note: not in dwarf */, float* color, float f_start, float f_end, float s_start, float s_end);

void sh_Set_DrawEnvLightData(int n, void* ded);

void sh_Kari_LightSetSpot(int n, float* pos, float* dir, float* color, float* sv);

void LightSetReflection(int n, float* dir, float* color);

void LightSetPos(int n, float* pos);

void LightSetDir(int n, float* dir);

void LightSetColor(int n, float* color);

void LightSetFalloff(int n, float f_start, float f_end);

void LightSetSpread(int n, float s_start, float s_end);

void UpdateViewParams(void);

void UpdateParallels(void);

void UpdateReflections(void);

void LightUpdateInfoByScene(void);

void LightUpdateInfoByPos(float* center, float radius);

int LightNValidParallelMatrices(void);

void LightGetNthViewNLM(float (* nlm)[4], int n);

void LightGetNthLCM(float (* lcm)[4], int n);

float LightReflectionBrightness(void);

void LightGetReflectionColor(float* color);

float* LightReflectionColor(void);

void LightGetNthViewNHM(float (* nhm)[4], int unused /* @note: not in dwarf */);

int LightNValidExtras(void);

Light* LightNthValidExtra(int n);


#endif
