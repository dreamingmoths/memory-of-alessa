#ifndef CAMERA_DAT_H
#define CAMERA_DAT_H

// @todo: header file not found in symbols, this is just here to hold `CAMERA_DAT`

typedef struct /* @anon6 */ {
    // total size: 0x220
    float pos[4];             // offset 0x0, size 0x10
    float zdir[4];            // offset 0x10, size 0x10
    float ydir[4];            // offset 0x20, size 0x10
    float rot[4];             // offset 0x30, size 0x10
    float clip_volume[4];     // offset 0x40, size 0x10
    float world_view[4][4];   // offset 0x50, size 0x40
    float view_screen[4][4];  // offset 0x90, size 0x40
    float view_clip[4][4];    // offset 0xD0, size 0x40
    float world_screen[4][4]; // offset 0x110, size 0x40
    float world_clip[4][4];   // offset 0x150, size 0x40
    float clip_screen[4][4];  // offset 0x190, size 0x40
    float camera_pam[4];      // offset 0x1D0, size 0x10
    float screen_pam1[4];     // offset 0x1E0, size 0x10
    float screen_pam2[4];     // offset 0x1F0, size 0x10
    float rot_zdir[4];        // offset 0x200, size 0x10
    float rot_ydir[4];        // offset 0x210, size 0x10
} CAMERA_DAT;

extern CAMERA_DAT cam0; // size: 0x220, address: 0xE496D0

#endif // CAMERA_DAT_H
