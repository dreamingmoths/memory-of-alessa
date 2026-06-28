#ifndef VB_MAIN_H
#define VB_MAIN_H

typedef struct _VbCOORDINATE {
    // total size: 0x140
    u_int flg;                   // offset 0x0, size 0x4
    sceVu0FMATRIX coord;         // offset 0x10, size 0x40
    sceVu0FMATRIX work;          // offset 0x50, size 0x40
    u_int* param;                // offset 0x90, size 0x4
    struct _VbCOORDINATE* super; // offset 0x94, size 0x4
    struct _VbCOORDINATE* sub;   // offset 0x98, size 0x4
    struct /* @anon0 */ {
        // total size: 0x8
        short vx;      // offset 0x0, size 0x2
        short vy;      // offset 0x2, size 0x2
        short vz;      // offset 0x4, size 0x2
        short pad;     // offset 0x6, size 0x2
    } r;               // offset 0x9C, size 0x8
    sceVu0FMATRIX lw;  // offset 0xB0, size 0x40
    sceVu0FMATRIX ls;  // offset 0xF0, size 0x40
    sceVu0FVECTOR rot; // offset 0x130, size 0x10
} VbCOORDINATE;

typedef struct _VbRVIEW {
    /* 0x00 */ sceVu0FVECTOR vp;
    /* 0x10 */ sceVu0FVECTOR vr;
    /* 0x20 */ float rz;
    /* 0x24 */ VbCOORDINATE* super;
} VbRVIEW;

typedef struct _VbWVSMATRIX {
    // total size: 0xC0
    float wvm[4][4]; // offset 0x0, size 0x40
    float vsm[4][4]; // offset 0x40, size 0x40
    float wsm[4][4]; // offset 0x80, size 0x40
} VbWVSMATRIX;

extern struct /* @anon3 */ {
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
} cam0;                       // size: 0x220, address: 0xE496D0

typedef struct _VbSCREENINFO {
    // total size: 0x24
    float scr_z; // offset 0x0, size 0x4
    float sx;    // offset 0x4, size 0x4
    float sy;    // offset 0x8, size 0x4
    float cx;    // offset 0xC, size 0x4
    float cy;    // offset 0x10, size 0x4
    float zmin;  // offset 0x14, size 0x4
    float zmax;  // offset 0x18, size 0x4
    float nearz; // offset 0x1C, size 0x4
    float farz;  // offset 0x20, size 0x4
} VbSCREENINFO;

extern VbSCREENINFO VbScreenInfo; // size: 0x24, address: 0x10E5910
extern VbWVSMATRIX VbWvsMatrix;   // size: 0xC0, address: 0x10E59D0

void vbCalcViewScreenMatrix(void);
void vbInitCoordinate(VbCOORDINATE* super, VbCOORDINATE* coord);
void vbSetWorldScreenMatrix(void);
void vbGetLw(VbCOORDINATE* coord, int fflip);
int vbSetRefView(VbRVIEW* rview);
float vbNormalizeRadianAngle(float ang);
void vbTransposeMatrixWithoutTr(float m0[4], float m1[4]); // @todo: check types
void vbApplyMatrixWithoutTr(sceVu0FVECTOR v0, sceVu0FMATRIX m0, sceVu0FVECTOR v1);

#endif // VB_MAIN_H
