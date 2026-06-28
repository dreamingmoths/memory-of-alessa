#ifndef LENS_FLARE_H
#define LENS_FLARE_H

#include "sh2_common.h"
#include "GFW/sh2gfw_structs.h"

typedef struct /* @anon6 */ {
    // total size: 0x40
    u_char flare_inhibit_f; // offset 0x0, size 0x1
    u_char water_inhibit_f; // offset 0x1, size 0x1
    u_char lfl_sync_draw_func_exec_f; // offset 0x2, size 0x1
    u_char draw_center_f; // offset 0x3, size 0x1
    float tgt_l_eff_rate; // offset 0x4, size 0x4
    float now_l_eff_rate; // offset 0x8, size 0x4
    Vector4 scr_l_pos;
    float scr_l_ang_xy; // offset 0x20, size 0x4
    float scr_l_ang_z; // offset 0x24, size 0x4
    IVector4 l_screen_pos; // offset 0x30, size 0x10
} LensFlareWork;
typedef struct /* @anon12 */ {
    // total size: 0x30
    float light_pow; // offset 0x0, size 0x4
    Vector4 world_light_vector; // offset 0x10, size 0x10
    Vector4 world_light_pos; // offset 0x20, size 0x10
} LightInfo;

typedef struct /* @anon7 */ {
    // total size: 0x10
    float center_x; // offset 0x0, size 0x4
    float center_y; // offset 0x4, size 0x4
    float width; // offset 0x8, size 0x4
    float height; // offset 0xC, size 0x4
} ScreenInfo;

extern ScreenInfo screen_info; // size: 0x10, address: 0x1013760
extern float reverse_light_rate;
extern int Lens_Fl_Head;
extern LensFlareWork light_flare_work;
extern LightInfo light_info[2]; // size: 0x60, address: 0x1013770

extern struct sh2gfw_Effect_Man LF_Tex_Work; // size: 0x40, address: 0x1013850

int shLensFlareCameraIsSmooth(void);

int shLensFlareLightCenterIsVisible(LensFlareWork* lf_info);

void shLensFlareInit(void);

void shLensFlareExec(struct SubCharacter* scp, float light_intensity, int type);

// @hack float memes in `shLensFlareMakeEffectTargetRate`
#define UNCURSE_LENS_FLARE_BLOOD()                      \
static void blood_lens_flare_blood(float a0, float a1) {\
    sceVu0FVECTOR sp10;                                 \
    do {                                                \
        do {                                            \
            SeCall(a0, 0.0f, 666);                      \
            SeCall(a1, 0.0f, 666);                      \
            SeCall(a1, 0.0f, 666);                      \
        } while(1);                                     \
    } while (0);                                        \
}

#endif // LENS_FLARE_H
