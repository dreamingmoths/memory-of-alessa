#include "sh2_common.h"

#include "GFW/sh2_DrawEnvData.h"

#include "view/vw_calc.h"
#include "view/vb_main.h"

#define VB_SET_ASPECT(X, Y)                         \
    VbScreenInfo.sx = X * Env_ctl.camera_parms2[0]; \
    VbScreenInfo.sy = Y * Env_ctl.camera_parms2[1]; \

#define VB_SET_OFFSET(X, Y)                         \
    VbScreenInfo.cx = X + 2048.0f;                  \
    VbScreenInfo.cy = Y + 2048.0f;                  \

#define VB_SET_BOUNDS()                             \
    VbScreenInfo.nearz = Env_ctl.camera_parms[3];   \
    VbScreenInfo.farz = Env_ctl.camera_parms2[2];   \

#define VB_SET_ZBOUNDS()                            \
    VbScreenInfo.zmin = 2.0f;                       \
    VbScreenInfo.zmax = Env_ctl.camera_parms2[3];   \

#define VW_GET_VIEW_POSITION()                      \
    vwGetViewPosition(Env_ctl.camera_p);            \
    Env_ctl.camera_p[3] = 0.0f;

#line 48
void sh2gfw_set_ViewScreenM(void) {
    // see also: `vbCalcViewScreenMatrix
    VB_SET_ASPECT(512.0f, 448.0f);
    VB_SET_OFFSET(0.0f, 0.0f); // center of screen
    VB_SET_ZBOUNDS();
    VB_SET_BOUNDS();
    VbScreenInfo.scr_z = Env_ctl.camera_parms[2];
    
    vbCalcViewScreenMatrix();
}

#line 65
void sh2gfw_init_shcamera(void) {
    #line 67
    sh2gfw_set_ViewScreenM();

    #line 70
}

#line 81
void sh2gfw_test_shcamera_main(void) {
    #line 98
    if (BgIsOut(0)) {


        
        VB_SET_ZBOUNDS();
        VB_SET_BOUNDS();
    } else {
        
        
        VB_SET_ZBOUNDS();
        VB_SET_BOUNDS();
    }
    
    
    vbCalcViewScreenMatrix();
    
    

    vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
    
    
    VW_GET_VIEW_POSITION();
    
    vwGetViewAngle(Env_ctl.camera_rot);
    
    sceVu0UnitMatrix(Env_ctl.camera_mat);
    vwRotMatrixYXZ(Env_ctl.camera_rot, Env_ctl.camera_mat);
}
