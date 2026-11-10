#include "sh2_common.h"

#include "view/camera_dat.h"

#include "GFW/sh2gfw_structs.h"
#include "GFW/sh2gfw_blockman.h"
#include "GFW/sh2_GsAllEnv.h"
#include "sh2shd/sh2shd_stencil_shadow_main.h"
#include "GFW/sh2_shadow_main.h"

UNMIGRATED(u_int paddata2);

void sh2gfw_ShadowControl_Main(void) {
    int dense;
    CAMERA_DAT* cam_tmp;

    cam_tmp = &cam0;

    dense = Get_NowRoomShadowDense();

    if (sh2gfw_Get_NightOrDay()) {

        if (!sh2gfw_Check_JmsSpotOnOff() || !LightSpotOnOffCheck())

            if (check_bg_light_exist() == 9)
                sh2shd_bg_shadow_off();

        if (dense != 0) {

            if (dense == 2)
                if (check_bg_light_exist() == 9)
                    sh2shd_bg_shadow_off();

            shadow_main(paddata2, cam_tmp, b_man->Local_World);

            return;
        }
        drop_shadow_main(paddata2, cam_tmp, 1, 1);

    } else {
        Get_NowRoomShadowDense();

        drop_shadow_main(paddata2, cam_tmp, 1, 1);
    }
}

void shadow_main(u_int paddata, CAMERA_DAT* cam /* r2 */, sceVu0FMATRIX m) {
    Q_WORDDATA* call_addr;

    Q_WORDDATA* qkick = stencil_shadow_main(cam);

    if (!qkick)
        return;

    sh2gfw_Lock_AllTexSlot_For_Shadow();

    sh2gfw_ChangeClear_StencilBuf(&shGs_AllEnv, 128, 128, 128, 112);

    sh2gfw_StartShadowEnv(&shGs_AllEnv);

    d1cSend(sh2gfw_setEND_gsctl());

    d1cSend(qkick);

    sh2gfw_setREF_TEXFLUSH();

    shdw_shadow_filter_main(1);

    sh2gfw_UnLock_AllTexSlot_For_Shadow();
}

void drop_shadow_main(u_int paddata, CAMERA_DAT* cam /* r2 */, int arg2, int arg3) {
    Q_WORDDATA* call_addr = not_stencil_shadow_main(cam);
    if (!call_addr)
        return;

    d1cSend(call_addr);
}
