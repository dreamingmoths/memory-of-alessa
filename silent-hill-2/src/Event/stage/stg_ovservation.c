#include "sh2_common.h"

#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_event.h"
#include "Chacter/chara_list.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/chara_data_load.h"
#include "Event/chara_admin.h"
#include "Event/demoview.h"

#include "SH2_common/mem_share.h"

#include "GFW/sh2gfw_2d_filters.h"

#include "Multi_thr/filesys/fcread.h"
#include "Multi_thr/filesys/fileserv.h"

#include "data/daily.thu/data_demo_mar_isho_i.h"
#include "data/daily.thu/data_pic_out.h"

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgLetterFromMary);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgItemInCar);

/* static */ int stg_ovservation_EvProgNothingTakeInCar(void) {
    return EvSubPictureDisplay(&data_pic_out_p_incar_tex, 3);
}

/* static */ int stg_ovservation_EvProgHadBetterGetMap(void) {

    static float stg_ovservation_pos_01F02EA0[4];

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubMessage(2)) {
                EV_PROG_STEP(27);
            }
            break;
            
        case 27:
            stg_ovservation_pos_01F02EA0[0] = sh2jms.player->pos.x;
            stg_ovservation_pos_01F02EA0[1] = sh2jms.player->pos.y;
            stg_ovservation_pos_01F02EA0[2] = sh2jms.player->pos.z - 500.0f;
            stg_ovservation_pos_01F02EA0[3] = 0.0f;
            EV_PROG_STEP(28);
            /* fallthrough */
        case 28:
            PlayerEventMove(stg_ovservation_pos_01F02EA0);
            if (PlayerEventMoveIsEnd()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

/* static */ int stg_ovservation_EvProgCantGoBack(void) {

    static float stg_ovservation_pos_01F02E90[4];

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(10);
            /* fallthrough */
        case 10:
            if (EvSubMessage(0)) {
                EV_PROG_STEP(27);
            }
            break;
        case 27:
            stg_ovservation_pos_01F02E90[0] = sh2jms.player->pos.x - 500.0f;
            stg_ovservation_pos_01F02E90[1] = sh2jms.player->pos.y;
            stg_ovservation_pos_01F02E90[2] = sh2jms.player->pos.z;
            stg_ovservation_pos_01F02E90[3] = 0.0f;
            EV_PROG_STEP(28);
            /* fallthrough */
        case 28:
            PlayerEventMove(stg_ovservation_pos_01F02E90);
            if (PlayerEventMoveIsEnd()) {
                EV_PROG_STEP(13);
            }
            break;
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_ovservation", stg_ovservation_EvProgLastScene);

/* static */ void stg_ovservation_EvAllTimeFunc(void) {
    int disp_ctrl_list[3]; // r29+0x10

    disp_ctrl_list[0] = 0;
    EvDispControlModelEntry(disp_ctrl_list, 3, !GET_GAME_FLAG(GAME_FLAG_24) ? 0 : -1); // @todo: add room id
    EvDispControlModelExec(disp_ctrl_list);
}

/* static */ int stg_ovservation_EvBgmControl(void) {
    if (GET_BIT(Sh2sys.main_status, 6)) {
        return !GET_GAME_FLAG(GAME_FLAG_517) ? 4 : 14;
    }
    return GET_GAME_FLAG(GAME_FLAG_36) != 0;
}

/* static */ float stg_ovservation_LinearTrim(float Yen, float Yst, float Xen, float Xst, float Parm) {
    return Yst + (((Yen - Yst) * (Parm - Xst)) / (Xen - Xst));
}

/* static */ void stg_ovservation_OB_DemoBlur(void) {
    float blt; // r29+0x10
    float tm; // r29+0x10
    
    if (DramaDemoNumber()) {
        tm = demo_frame;
        if (tm > 1500.0f) {
            sh2gfw_Reset_FilterCommand();
            return;
        }
        if (tm < 0.0f) {
            tm = 0.0f;
        }
        blt = stg_ovservation_LinearTrim(0.0f, 1.0f, 1500.0f, 0.0f, tm);
        sh2gfw_Set_FilterBlur(blt);
    }
}
