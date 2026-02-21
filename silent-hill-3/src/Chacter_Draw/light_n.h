#ifndef LIGHT_N_H
#define LIGHT_N_H

typedef struct Light
{
    // total size: 0xA0
    signed int kind;         // offset 0x0, size 0x4
    float intensity;         // offset 0x4, size 0x4
    float influence;         // offset 0x8, size 0x4
    float intensity2;        // offset 0xC, size 0x4
    float influence2;        // offset 0x10, size 0x4
    signed short cid;        // offset 0x14, size 0x2
    signed short fakekind;   // offset 0x16, size 0x2
    float inf_fac;           // offset 0x18, size 0x4
    void *DrawEnv_LightData; // offset 0x1C, size 0x4
    float pos[4];            // offset 0x20, size 0x10
    float vpos[4];           // offset 0x30, size 0x10
    float dir[4];            // offset 0x40, size 0x10
    float vdir[4];           // offset 0x50, size 0x10
    float color[4];          // offset 0x60, size 0x10
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

int LightNValidParallelMatrices();
void LightGetNthViewNLM(float (*nlm)[4] /* r2 */, int n /* r2 */);
void LightGetNthLCM(float (*lcm)[4] /* r2 */, int n /* r2 */);
static void LightGetNthViewNHM(float (*nhm)[4] /* r2 */, int unknown);
int LightNValidExtras();
struct Light *LightNthValidExtra(int n /* r2 */);
float LightReflectionBrightness();

#endif
