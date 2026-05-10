#ifndef PICTURE_H
#define PICTURE_H

#include "common.h"

typedef struct sh2gfw_AREA_HEAD {
    // total size: 0x10
    u_int area_id; // offset 0x0, size 0x4
    u_int toGlobalTexHead; // offset 0x4, size 0x4
    u_int toGlobalClutsHead; // offset 0x8, size 0x4
    u_int date; // offset 0xC, size 0x4
} sh2gfw_AREA_HEAD;

typedef struct SPACK_OT_DATA {
    // total size: 0x10
    u_short DmaQwc; // offset 0x0, size 0x2
    u_short DmaId; // offset 0x2, size 0x2
    void* Addr; // offset 0x4, size 0x4
    u_int W; // offset 0x8, size 0x4
    u_short VifQwc; // offset 0xC, size 0x2
    u_char EnvID; // offset 0xE, size 0x1
    u_char VifDirect; // offset 0xF, size 0x1
} SPACK_OT_DATA;

typedef struct PicDraw_Data {
    // total size: 0x44
    struct sh2gfw_AREA_HEAD* ap; // offset 0x0, size 0x4
    int tex; // offset 0x4, size 0x4
    int clut; // offset 0x8, size 0x4
    short x0; // offset 0xC, size 0x2
    short y0; // offset 0xE, size 0x2
    short x1; // offset 0x10, size 0x2
    short y1; // offset 0x12, size 0x2
    short x2; // offset 0x14, size 0x2
    short y2; // offset 0x16, size 0x2
    short x3; // offset 0x18, size 0x2
    short y3; // offset 0x1A, size 0x2
    int us0; // offset 0x1C, size 0x4
    int vt0; // offset 0x20, size 0x4
    int us1; // offset 0x24, size 0x4
    int vt1; // offset 0x28, size 0x4
    u_char r; // offset 0x2C, size 0x1
    u_char g; // offset 0x2D, size 0x1
    u_char b; // offset 0x2E, size 0x1
    u_char a; // offset 0x2F, size 0x1
    u_char alpha_a; // offset 0x30, size 0x1
    u_char alpha_b; // offset 0x31, size 0x1
    u_char alpha_c; // offset 0x32, size 0x1
    u_char alpha_d; // offset 0x33, size 0x1
    u_char alpha_fix; // offset 0x34, size 0x1
    u_char test_ate; // offset 0x35, size 0x1
    u_char test_atst; // offset 0x36, size 0x1
    u_char test_aref; // offset 0x37, size 0x1
    u_char test_afail; // offset 0x38, size 0x1
    u_char test_date; // offset 0x39, size 0x1
    u_char test_datm; // offset 0x3A, size 0x1
    u_char test_zte; // offset 0x3B, size 0x1
    u_char test_ztst; // offset 0x3C, size 0x1
    u_char pad[3]; // offset 0x3D, size 0x3
    short otp; // offset 0x40, size 0x2
    short status; // offset 0x42, size 0x2
} PicDraw_Data;

inline void picture_set_ap(PicDraw_Data* pic, void* adr) {
    pic->ap      = (sh2gfw_AREA_HEAD* ) adr;
    pic->tex     = -1;
    pic->clut    = -1;
    pic->status |= 1;
}

inline void picture_set_alpha(PicDraw_Data* pic, u_char alpha) {
    pic->a = alpha;

    // sets alpha blend equation to 1 - B
    pic->alpha_a    = 0;
    pic->alpha_b    = 1;
    pic->alpha_c    = 0;
    pic->alpha_d    = 1;
    pic->alpha_fix  = 0x80;
    pic->status    |= 0x20;
}

inline void picture_set_bounds(PicDraw_Data* pic, short pos[2], short tex[2]) {
    pic->x0      = pos[0];
    pic->y0      = pos[1];
    pic->x1      = pos[0] + (tex[2] - tex[0]) * 16;
    pic->y1      = pos[1] + (tex[3] - tex[1]) * 16;
    pic->status |= 2;
}

inline void picture_set_tex_coords(PicDraw_Data* pic, short uvst[4]) {
    pic->us0     = uvst[0] * 16;
    pic->vt0     = uvst[1] * 16;
    pic->us1     = (uvst[2] - 1) * 16;
    pic->vt1     = (uvst[3] - 1) * 16;
    pic->status |= 4;
}

void PictureDraw(PicDraw_Data* pic /* r21 */);
void PictureLoadImage(sh2gfw_AREA_HEAD* ap /* r2 */, int otp /* r23 */, int tex_adr /* r22 */, int clut_adr /* r21 */);

#endif // PICTURE_H
