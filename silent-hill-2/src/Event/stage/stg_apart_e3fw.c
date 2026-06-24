#include "sh2_common.h"
#include "SH2_common/mem_share.h"
#include "Multi_thr/filesys/fcread.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/stg_name.h"
#include "Event/demoview.h"
#include "Event/chara_data_load.h"

#include "Chacter/chara_list.h"
#include "Chacter/sh2_character_manage.h"

#include "DS_Pad/dsr_data.h"
#include "data/daily.thu/data_demo_kagikeri.h"

/* static */ int stg_apart_e3fw_EvProgLauraKickKey(void);
/* static */ int stg_apart_e3fw_EvProgGetHandgun(void);
/* static */ void stg_apart_e3fw_EvRoomInit(void);
/* static */ void stg_apart_e3fw_EvProgSubScreamOn(void);

extern /* static */ float stg_apart_e3fw_yard_key_after_data[2][4]; // @ 0x01F02860
extern /* static */ DramaDemo_PlayInfo stg_apart_e3fw_kick; // @ 0x01F027E0
extern /* static */ CharaData_DemoList stg_apart_e3fw_kagikeri_data[4]; // @ 0x01F02810

/* static */ int stg_apart_e3fw_EvProgLauraKickKey(void) {   
    if (demo_frame > 405.5f && demo_frame <= 406.7f) {
        DSR_Entry0(__otn_kick_key_00, 0, 1.0f);
    }
    
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            FcRead(data_demo_kagikeri_kagikeri_dds, MemShare_gp_data_buf);
            CharaDataLoadDemo(stg_apart_e3fw_kagikeri_data, 1);
            EV_PROG_STEP(10);
            /* fallthrough */
    
        case 10:
            if (EvSubQuestion(3)) {
                if (!fontGetStatus()) {
                    EV_PROG_STEP(2);
                } else {
                    CharaDataLoadCancel(stg_apart_e3fw_kagikeri_data);
                    EV_PROG_STEP(13);
                }
            }
            break;
    
        case 2:
            if (fsSync(1, -1) >= 0) {
                CharaDataLoadDemo(stg_apart_e3fw_kagikeri_data, 0);
                CharaAdminPlayableDisplay(0);
                shCharacter_Manage_Delete(NULL, ITEM_X_KEYCOURT_CHARA_KIND, 0);
                SCNowDemoEventSwitch(sh2jms.player, 1);
                EV_PROG_STEP(22);
            case 22:
                if (DramaDemoMain(&stg_apart_e3fw_kick)) {
                    EV_PROG_STEP(6);
                }
            }
            break;
    
        case 6:
            CharaDataDeleteOne(HHH_JMS_CHARA_KIND);
            CharaDataDeleteOne(LAU_CHARA_KIND);
            CharaDataDeleteOne(ITEM_I_KEYCOU_CHARA_KIND);
            CharaWorkCreate(ITEM_X_KEYCOURT_CHARA_KIND, 0, stg_apart_e3fw_yard_key_after_data[0], stg_apart_e3fw_yard_key_after_data[1], 0);
            CharaAdminPlayableDisplay(1);
            SCNowDemoEventSwitch(sh2jms.player, false);
            vcReturnPreAutoCamWork(1);
            SET_GAME_FLAG(GAME_FLAG_67);
            EV_PROG_STEP(13);
            /* fallthrough */

        case 13:
            if (GET_GAME_FLAG(GAME_FLAG_66))
                stg_apart_e3fw_EvProgSubScreamOn();

            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }

    return 0;
}

/* static */ int stg_apart_e3fw_EvProgGetHandgun(void) {
    int ret = EvSubItemGetAndAnim(4, 0); // r16

    if (ret && GET_GAME_FLAG(GAME_FLAG_67)) {
        stg_apart_e3fw_EvProgSubScreamOn();
    }

    return ret;
}

/* static */ void stg_apart_e3fw_EvRoomInit(void) {
    /* empty */
}

/* static */ void stg_apart_e3fw_EvProgSubScreamOn(void) {
    SubCharacter* scp; // r16

    SET_GAME_FLAG(GAME_FLAG_68);
    scp = shCharacter_Manage_GetCharacterList();

    while (scp != NULL) {
        if (IS_SCP_ENEMY(scp) && RoomName(0, scp->pos.x, scp->pos.z) == 21 && scp->battle.hp <= 0.0f) {
            SET_FLAG(game_flag.enemy, scp->id);
            shCharacter_Manage_Delete(scp, 0, 0);
        }
        scp = scp->next;
    }
}

