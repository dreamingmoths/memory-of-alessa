#ifndef SH2_SHADOW_MAIN_H
#define SH2_SHADOW_MAIN_H

#include "sce/libvu0.h"
#include "view/camera_dat.h"

void sh2gfw_ShadowControl_Main(void);

void shadow_main(u_int paddata, CAMERA_DAT* cam /* r2 */, sceVu0FMATRIX m);

void drop_shadow_main(u_int paddata, CAMERA_DAT* cam /* r2 */, int arg2, int arg3);


#endif // SH2_SHADOW_MAIN_H
