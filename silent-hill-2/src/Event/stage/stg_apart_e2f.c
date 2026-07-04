#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/item.h"
#include "Event/stg_name.h"
#include "Event/chara_data_load.h"

#include "Chacter/chara_list.h"

#include "GFW/sh2_DrawEnvData.h"

#include "Enemy/en_common.h"
#include "Enemy/en_insect.h"

#include "sound/sh_sound.h"

#include "Chacter_Draw/sh2gfw_Draw_Character.h"

#include "SH2_common/sh2dt.h"

#include "data/daily.thu/data_demo_kao.h"
#include "data/daily.thu/data_chr_jms.h"

// @todo: migrate data

extern /* static */ float stg_apart_e2f_tv_pos[4]; // = { -58082.375f, -356.5f , 19011.39062, 0.0f}; // @ 0x01F07240

extern /* static */ float stg_apart_e2f_cry_pos[4]; // = { -99400.0f, -500.0f, -10785.03027f, 0.0f }; @ 0x01F076E0

extern /* static */ float stg_apart_e2f_pos_01F076F0[4]; // = { -100447.5f, -500.0f, -10785.03027f, 0.0f };

extern /* static */ float stg_apart_e2f_pos_01F07700[4]; // = { -99000.0f, -1500.0f, 13600.0f, 0.0f };

extern /* static */ CharaData_DemoList stg_apart_e2f_chara_data_01F07710[2];
/*
static CharaData_DemoList stg_apart_e2f_chara_data_01F07710[2] = {
    {
        .kind = HHL_JMS_CHARA_KIND,
        .model = data_chr_jms_hhl_jms_notex_mdl,
        .animation = data_demo_kao_hhl_jms_anm,
        .shadow = data_chr_jms_hhh_jms_kg1,
        .cluster = data_demo_kao_hhl_jms_cls
    },
    0
};
*/
extern /* static */ float stg_apart_e2f_pos_01F07740[4]; // = { -22800.0f, -700.0f, 59200.0f, 1.0f };

// @todo: migrate bss

extern /* static */ u_long128* stg_apart_e2f_kao_dds; // @ 0x01F077A0

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgThreeNameOnWall);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgHintOfClockSet);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgClockTime);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgClockNeedleMove);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgSubClockNeedleDraw);

/* static */ int stg_apart_e2f_EvProgUseClockKey(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgTryMoveClock);

/* static */ int stg_apart_e2f_EvProgUseEmergencyKey(void) {
    return EvSubItemUse0(27, 24, 0, 0, 0, 1);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgAnyoneInHole);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgNooneInHole);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgLookDustChute);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgUseCannedJuice);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgNoFaceCorpse);

/* static */ int stg_apart_e2f_EvProgAnyoneCry(void) {
    int anm; // r2

    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(20002);
            ev_timer = 0.0f;
            SeCallPos(40009, 1.0f, stg_apart_e2f_cry_pos, 6);
            EV_PROG_STEP(27);
    
        case 27:
            Se3dControl(40009, 1.0f, stg_apart_e2f_cry_pos);
            ev_timer += shGetDT();
            if (shCharacterAnimeIsEnd(sh2jms.player)) {
                if (ev_timer < 2.0f)
                    anm = 0;
                else
                    anm = EvSubMessage(0);

                if (anm) {
                    EV_PROG_STEP(13);                    
                }
            }
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, false);
            return 1;
    }

    return 0;
}

/* static */ int stg_apart_e2f_EvProgGetLight(void) {
    int ret;

    ret = EvSubItemGetAndAnim(15, 20); // @todo: add define in item.h
    
    if (ret != 0) {
        item.light_switch = 1;
        LightSpotOnOffSet();
        if (GET_GAME_FLAG(GAME_FLAG_66) && GET_GAME_FLAG(GAME_FLAG_67)) {
            SET_GAME_FLAG(GAME_FLAG_68);
        }
        enEventDriven(2, 0);
    }
    return ret;
}

/* static */ int stg_apart_e2f_EvProgGetApart202Key(void) {
    return EvSubItemGetAndAnim(APART_202_KEY, 21);
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintRecoveryRead);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintMariaRead);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgEndHintSuicideRead);

/* static */ int stg_apart_e2f_EvProgUseApart202Key(void) {
    float pos[4];
    pos = stg_apart_e2f_pos_01F076F0;
    return EvSubItemUse0(APART_202_KEY, 23, 19003, 0, pos, 1);
}

/* static */ int stg_apart_e2f_EvProgMonkeyKick206(void) {
    float pos[4]; // not present in DWARF
    if (!GET_GAME_FLAG(GAME_FLAG_69)) {
        pos = stg_apart_e2f_pos_01F07700;
        SeCallPos(40007, 1.0f, pos, 2); // @note: not line matched these 2 should be only one line
    }
    return 1;
}

/* static */ int stg_apart_e2f_EvCharaDataClear(int room) {
    if ((room == 0x18) && (GET_GAME_FLAG(GAME_FLAG_69) && !GET_GAME_FLAG(GAME_FLAG_71))) { // @todo: add room id
        return 1;
    } 
    return 0;       
}

/* static */ void stg_apart_e2f_EvRoomInit(void) {
    int room; // r16    
    float pos[4]; // not present in DWARF

    room = RoomNameJms();
    if ((room == 0x18) && (GET_GAME_FLAG(GAME_FLAG_69) && !GET_GAME_FLAG(GAME_FLAG_71))) {
        CharaDataLoadDemo(stg_apart_e2f_chara_data_01F07710, 0);
        stg_apart_e2f_kao_dds = CharaDataLoadExtra(data_demo_kao_kao_dds, EN_SCU_CHARA_KIND);
        fsSync(0, -1);
    }
    if (room == 0x16) {
        pos = stg_apart_e2f_pos_01F07740;
        enSetInsect(pos, 5);
        return;
    }
    enKillAllInsect();
}

/* static */ void stg_apart_e2f_EvSoundCallAfterLoad(void) {
    if (RoomNameJms() == 0x18) {
        if (GET_GAME_FLAG(GAME_FLAG_69)) {
            SeCallPos(16000, 0.3f, stg_apart_e2f_tv_pos, 12);
            sh2gfw_SetNoise_CharaTexture(ITEM_NOA_CHARA_KIND); // https://silenthillmuseum.org/?game=sh2&model=chr-item-noa
            SET_GAME_FLAG(GAME_FLAG_70);
            return;
        }
        sh2gfw_RemoveNoise_CharaTexture(ITEM_NOA_CHARA_KIND);
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvAllTimeFunc);

/* static */ void stg_apart_e2f_Delete_RedPointLight(void) {
    int* mp; // r17
    DrawEnvData* ded; // r16

    mp = Get_NowMapId();
    ded = Get_NowDrawEnvData();
    if (*mp == 0x90032) {
        if (EventProgressCheck() == 4) {            
            if (ded->pointLNum < 5) {
                ded->pointLNum = 5;
            }
        } else if (ded->pointLNum > 4) {
            ded->pointLNum = 4;
        }
    }
}
