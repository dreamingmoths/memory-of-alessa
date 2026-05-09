#ifndef VB_MAIN_H
#define VB_MAIN_H

typedef struct _VbWVSMATRIX {
    // total size: 0xC0
    float wvm[4][4]; // offset 0x0, size 0x40
    float vsm[4][4]; // offset 0x40, size 0x40
    float wsm[4][4]; // offset 0x80, size 0x40
} VbWVSMATRIX;

extern struct /* @anon3 */ {
    // total size: 0x220
    float pos[4]; // offset 0x0, size 0x10
    float zdir[4]; // offset 0x10, size 0x10
    float ydir[4]; // offset 0x20, size 0x10
    float rot[4]; // offset 0x30, size 0x10
    float clip_volume[4]; // offset 0x40, size 0x10
    float world_view[4][4]; // offset 0x50, size 0x40
    float view_screen[4][4]; // offset 0x90, size 0x40
    float view_clip[4][4]; // offset 0xD0, size 0x40
    float world_screen[4][4]; // offset 0x110, size 0x40
    float world_clip[4][4]; // offset 0x150, size 0x40
    float clip_screen[4][4]; // offset 0x190, size 0x40
    float camera_pam[4]; // offset 0x1D0, size 0x10
    float screen_pam1[4]; // offset 0x1E0, size 0x10
    float screen_pam2[4]; // offset 0x1F0, size 0x10
    float rot_zdir[4]; // offset 0x200, size 0x10
    float rot_ydir[4]; // offset 0x210, size 0x10
} cam0; // size: 0x220, address: 0xE496D0

typedef struct _VbSCREENINFO {
    // total size: 0x24
    float scr_z; // offset 0x0, size 0x4
    float sx; // offset 0x4, size 0x4
    float sy; // offset 0x8, size 0x4
    float cx; // offset 0xC, size 0x4
    float cy; // offset 0x10, size 0x4
    float zmin; // offset 0x14, size 0x4
    float zmax; // offset 0x18, size 0x4
    float nearz; // offset 0x1C, size 0x4
    float farz; // offset 0x20, size 0x4
} VbSCREENINFO;

extern VbSCREENINFO VbScreenInfo; // size: 0x24, address: 0x10E5910
extern VbWVSMATRIX VbWvsMatrix; // size: 0xC0, address: 0x10E59D0

#endif // VB_MAIN_H
