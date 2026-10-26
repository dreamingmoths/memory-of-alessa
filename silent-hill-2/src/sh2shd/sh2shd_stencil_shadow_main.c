#include "sh2_common.h"

#include "Chacter_Draw/light_n.h"
#include "view/camera_dat.h"
#include "LoadBg/loadbg_kg2.h"
#include "sh2shd/sh2shd_structs.h"
#include "sh2shd/sh2shd_shadow_model.h"
#include "GFW/sh2_get_drawenv.h"

Q_WORDDATA* stencil_shadow_main(CAMERA_DAT* cam /* r19 */) {
    Q_WORDDATA* ret_addr;
    void** list;
    void* addr;
    int i;
    SPOT_LIGHT spot;
    int glb_coord;
    int map_id;
    int light_kind;

    sh2gde_getspotParams_for_Shadow(spot.c, spot.zdir, spot.range);
    
    light_kind = 0;
    
    get_map_id(&glb_coord, &map_id);
    
    if (glb_coord == 12 && map_id == 91) {
        light_kind = LIGHT_KIND_REFLECTION;

        spot.zdir[0] = 0.07311368f;
        spot.zdir[1] = 0.683614f;
        spot.zdir[2] = 0.7261726f;
    } else if (glb_coord == 9 && map_id == 42 && !sh2gfw_Check_JmsSpotOnOff()) {
        light_kind = LIGHT_KIND_NONE;

        spot.c[0] = -58350.0f;
        spot.c[1] = -700.0f;
        spot.c[2] = 19275.0f;
        spot.c[3] = 1.0f;

        spot.zdir[0] = -0.362f;
        spot.zdir[1] = 0.769f;
        spot.zdir[2] = 0.326f;
        spot.zdir[3] = 0.0f;
    }

    list = loadBgKG2_GetLoadedDataAddrList();

    for (i = 0; (addr = *list) != NULL; i++, list++) {
        sh2shd_add_map(i, addr, light_kind, spot.c, spot.zdir, spot.range);
    }
    
    ret_addr = sh2shd_exe_shadow(cam);

    return ret_addr;
}

Q_WORDDATA* not_stencil_shadow_main(CAMERA_DAT* cam /* r2 */) {
    Q_WORDDATA* ret_addr;

    ret_addr = sh2shd_exe_drop_shadow(cam);

    return ret_addr;
}
