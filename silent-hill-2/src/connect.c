#include "connect.h"

#include "gamemain.h"

#include "sh2gfw_all_sysinit.h"

#include "Chacter/m3_sc.h"

#include "Event/event.h"
#include "Event/chara_admin.h"
#include "Event/chara_data_load.h"
#include "Event/title.h"
#include "Event/stg_name.h"

#include "Enemy/en_effect.h"

#include "Effect2/hh_effect_object_texture.h"
#include "Effect2/hh_class_object_execute.h"

#include "LoadBg/loadbg_cam.h"
#include "LoadBg/loadbg_chara.h"
#include "LoadBg/loadbg_event.h"

#include "SH2_common/data_load.h"
#include "SH2_common/sh2sys.h"

#include "Multi_thr/loadinit/loadinit.h"
#include "Multi_thr/filesys/fileserv.h"

#include "view/vc_util.h"
#include "view/vc_play.h" // @note: does sys really belong there?

typedef int (func2_t)(void); // @todo: find a home for these
typedef int (func_t)(func2_t*);

/* static */ int connectStageInit(void) {
    step_init_STAGE();
    CharaDataLoadStage();
    if ((Sh2sys.main_status >> 3) & 1) {
        ConnectCharaWorkReset();
        Sh2sys.main_status &= ~8;
    }
    ConnectCharaWorkJamesSet();
    CheckModeJumpDataSet();


    
    titleSetDataStartPoint();

    
    if (stage->stage_init) stage->stage_init();
    LoadBgCharaInit();
    LoadBgEventInit(NULL, 0);
    
    return 0;
}

/* static */ int connectRoomInit(void) {
    CharaDataLoadRoom(RoomName(0, connect_pos[0], connect_pos[2]));

    
    map_DATA_LOAD(0);



    HH_Effect_Object_Texture_DesignateEntryLevel_Initialize(3);
    HH_Class_Object_Initialize();
    
    
    
    ConnectCharaWorkAdminClear();
    if (BgIsOut(stage->glb_crd) == 0) ConnectCharaWorkAdminIn();         
    else ConnectCharaWorkAdminOut(0);
    PlayerInitOnConnect();    
    if (GET_GAME_FLAG(GAME_FLAG_15)) MariaInitOnConnect();

    volatile_vec_copy(&sys.hero.pos[0], &connect_pos[0]);
    
    
    
    
    enEfctClear();
    
    vcInitCamera(NULL);
    loadBgCAM_vcReset();
    
    if (stage->room_init) stage->room_init();

    return 1;
}

/* static */ int connectPlayableInit(void) {
    ConnectCharaWorkWeapon();
    LightSpotOnOffSet();
    DataLoadMessage(0);
    DataLoadMessage(6);
    return 1;
}

int connectMain(void) {
    switch (Sh2sys.step[3]) {
        case 0:
            StgOverlay();
            sh2sys_step_3();
            break;       
        case 1:
            (((func_t*)&lisPutCmd0))(connectStageInit);
            sh2sys_step_3();
            break;
        case 2:
            if (lisSync(1, -1) >= 0) {
                sh2sys_step_3();
            }
            break;
        case 3:
            shCharacterSetPosAfterDemo(sh2jms.player, connect_pos, connect_pos[3]);
            sh2sys_step_3();
            break;
        case 4:
            (((func_t*)&lisPutCmd0))(connectRoomInit);
            sh2sys_step_3();
            break;
        case 5:
            if (lisSync(1, -1) >= 0) {
                sh2sys_step_3();
            }
            break;
        case 6:
            (((func_t*)&lisPutCmd0))(connectPlayableInit);
            sh2sys_step_3();
            break;
        case 7:
            if ((lisSync(1, -1) >= 0) && (fsSync(1, -1) >= 0)) {
                return 1;
            }
            break;
    }
    return 0;
}
