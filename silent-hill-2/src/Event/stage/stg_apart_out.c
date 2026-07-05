#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/item.h"
#include "Event/stg_name.h"
#include "Event/chara_data_load.h"
#include "Event/chara_admin.h"
#include "Event/demoview.h"

#include "Chacter/chara_list.h"
#include "Chacter/m3_sc.h"

#include "Effect/screen_effect.h"

#include "SH2_common/mem_share.h"
#include "SH2_common/pad.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "view/vc_main.h"

#include "data/daily.thu/data_demo_tobira.h"
#include "data/daily.thu/data_demo_tobira_c.h"
#include "data/daily.thu/data_pic_apt.h"

// extern /* static */ int stg_apart_out_px; // @ 0x01F02C48

// extern /* static */ int stg_apart_out_py; // @ 0x01F02C50

extern /* static */ DramaDemo_PlayInfo stg_apart_out_info_door_a; // @ 0x01F02C70

extern /* static */ DramaDemo_PlayInfo stg_apart_out_info_door_b; // @ 0x01F02CA0

extern /* static */ CharaData_DemoList stg_apart_out_chara_data_01F02CD0[2]; // @ 0x01F02CD0

extern /* static */ DramaDemo_PlayInfo stg_apart_out_info_door_c; // @ 0x01F02D00

extern /* static */ CharaData_DemoList stg_apart_out_chara_data_01F02D30[2]; // @ 0x01F02D30

/* static */ int stg_apart_out_EvProgGetCoinOfSnake(void) {
    return EvSubItemGetAndAnim(COIN_OF_SNAKE, 5);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_out", stg_apart_out_EvProgGetCoinOfOldman);

/* static */ int stg_apart_out_EvProgMurderNewsRead(void) {
    return EvSubPictureDisplay(data_pic_apt_p_dust_out_tex, 1);
}

/* static */ int stg_apart_out_EvProgApartEastToWest(void) {
    int ret; // r16

    switch (ev_p_step) {
        case 0:
            FcRead(&data_demo_tobira_tobira_a_dds, MemShare_gp_data_buf);
            FcRead(&data_demo_tobira_tobira_b_dds, MemShare_gp_data_buf + 0x8000);
            fsSync(0, -1);
            CharaDataLoadDemo(stg_apart_out_chara_data_01F02CD0, 0);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            if (GET_GAME_FLAG(GAME_FLAG_97)) {
                EV_PROG_STEP(24);
            } else {
                EV_PROG_STEP(23);
            }
            return stg_apart_out_EvProgApartEastToWest();
        case 23:
            if (DramaDemoMain(&stg_apart_out_info_door_a)) {
                if (shPadTrigger(0, key_config.skip)) {
                    EV_PROG_STEP(13);
                } else {
                    EV_PROG_STEP(10);
                }
            }
            break;
            
        case 10:
            if (EvSubMessage(4)) {
                EV_PROG_STEP(24);
            }
            break;
        case 24:
            ret = DramaDemoMain(&stg_apart_out_info_door_b);
            if (demo_frame > (total_demo_frame - 15.0f)) {
                ScreenEffectFadeStart(1, 0.5f);
            }
            if (ret) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            ScreenEffectFadeStart(3, 0.0f);
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            return 1;
    }
    return 0;
}

/* static */ int stg_apart_out_EvProgApartWestToEast(void) {
    int ret; // r16

    switch (ev_p_step) {
        case 0:
            FcRead(&data_demo_tobira_c_tobira_c_dds, MemShare_gp_data_buf);
            fsSync(0, -1);
            CharaDataLoadDemo(stg_apart_out_chara_data_01F02D30, 0);
            CharaAdminPlayableDisplay(0);
            SCNowDemoEventSwitch(sh2jms.player, true);
            EV_PROG_STEP(24);
            /* fallthrough */
        case 24:
            ret = DramaDemoMain(&stg_apart_out_info_door_c);
            if (demo_frame > (total_demo_frame - 15.0f)) {
                ScreenEffectFadeStart(1, 0.5f);
            }
            if (ret) {
                EV_PROG_STEP(13);
            }
            break;
            
        case 13:
            ScreenEffectFadeStart(3, 0.0f);
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaAdminPlayableDisplay(1);
            vcReturnPreAutoCamWork(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            shCharacterPlayerModelToPlayable();
            return 1;
    }
    return 0;
}

/* static */ void stg_apart_out_EvStageInit(void) {
    UNSET_GAME_FLAG(GAME_FLAG_87);
}

/* static */ void stg_apart_out_EvAllTimeFunc(void) {
    int disp_ctrl_list[3]; // r29+0x10

    disp_ctrl_list[0] = 0;
    
    if (RoomNameJms() != 7) {
        
        if (GET_GAME_FLAG(GAME_FLAG_95)) {
            EvDispControlModelEntry(disp_ctrl_list, 0x2E, 2); // @todo: add room id
        }
        EvDispControlModelEntry(disp_ctrl_list, 0x2E, 1);
    }
    EvDispControlModelExec(disp_ctrl_list);
}
