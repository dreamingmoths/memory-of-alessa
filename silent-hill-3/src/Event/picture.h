#ifndef PICTURE_H
#define PICTURE_H

#include "common.h"

typedef struct sh3gfw_AREA_HEAD
{
    // total size: 0x10
    u_int unk0;            // offset 0x0, size 0x4
    u_int unk4;            // offset 0x4, size 0x4
    u_int toGlobalTexHead; // offset 0x8, size 0x4
    u_int totalsize;       // offset 0xC, size 0x4
} sh3gfw_AREA_HEAD;

typedef struct PicLoadImage_Data
{
    // total size: 0x10
    struct sh3gfw_AREA_HEAD* ap;       // offset 0x0, size 0x4
    int                      tex_adr;  // offset 0x4, size 0x4
    int                      clut_adr; // offset 0x8, size 0x4
    short                    otp;      // offset 0xC, size 0x2
    short                    pad;      // offset 0xE, size 0x2
} PicLoadImage_Data;

typedef struct PicDraw_Data
{
    // total size: 0x44
    struct sh3gfw_AREA_HEAD* ap;         // offset 0x0, size 0x4
    int                      tex;        // offset 0x4, size 0x4
    int                      clut;       // offset 0x8, size 0x4
    short                    x0;         // offset 0xC, size 0x2
    short                    y0;         // offset 0xE, size 0x2
    short                    x1;         // offset 0x10, size 0x2
    short                    y1;         // offset 0x12, size 0x2
    short                    x2;         // offset 0x14, size 0x2
    short                    y2;         // offset 0x16, size 0x2
    short                    x3;         // offset 0x18, size 0x2
    short                    y3;         // offset 0x1A, size 0x2
    int                      us0;        // offset 0x1C, size 0x4
    int                      vt0;        // offset 0x20, size 0x4
    int                      us1;        // offset 0x24, size 0x4
    int                      vt1;        // offset 0x28, size 0x4
    u_char                   r;          // offset 0x2C, size 0x1
    u_char                   g;          // offset 0x2D, size 0x1
    u_char                   b;          // offset 0x2E, size 0x1
    u_char                   a;          // offset 0x2F, size 0x1
    u_char                   alpha_a;    // offset 0x30, size 0x1
    u_char                   alpha_b;    // offset 0x31, size 0x1
    u_char                   alpha_c;    // offset 0x32, size 0x1
    u_char                   alpha_d;    // offset 0x33, size 0x1
    u_char                   alpha_fix;  // offset 0x34, size 0x1
    u_char                   test_ate;   // offset 0x35, size 0x1
    u_char                   test_atst;  // offset 0x36, size 0x1
    u_char                   test_aref;  // offset 0x37, size 0x1
    u_char                   test_afail; // offset 0x38, size 0x1
    u_char                   test_date;  // offset 0x39, size 0x1
    u_char                   test_datm;  // offset 0x3A, size 0x1
    u_char                   test_zte;   // offset 0x3B, size 0x1
    u_char                   test_ztst;  // offset 0x3C, size 0x1
    u_char                   unk3D;      // offset 0x3D, size 0x1
    u_char                   pad[2];     // offset 0x3E, size 0x2
    short                    otp;        // offset 0x40, size 0x2
    short                    status;     // offset 0x42, size 0x2
} PicDraw_Data;

void PictureDraw(PicDraw_Data* pic /* r16 */);
void PictureLoadImage(PicLoadImage_Data* pic_load /* r22 */);

#endif