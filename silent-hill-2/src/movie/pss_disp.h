#ifndef PSS_DISP_H
#define PSS_DISP_H

#include "sce/eetypes.h"
#include "sce/libgraph.h"

// ////////////////////////////////////////////////////////////////
//
// Display
//
typedef struct _Display {
    sceGsDispEnv dispenv;
    int fbp0;
    int fbp1;
    int fb_w;
    int fb_h;
} Display;

// ////////////////////////////////////////////////////////////////
//
// Functions
//
void dispCreate(
    Display *d,
    int fb_w,
    int fb_h
);
void dispDelete(Display *d);
void dispSetTags(
    Display *d, u_int *tags, void *image, int index,
    int disp_x, int disp_y,
    int disp_w, int disp_h,
    int image_w, int image_h
);
void dispSwitch(Display *d, int id);
void dispClear(Display *d, u_int val);
void startDisplay(int waitEven);
void endDisplay();

#endif // PSS_DISP_H
