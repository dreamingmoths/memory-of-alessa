#include "sh2_common.h"

#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/item.h"

#include "Enemy/en_common.h"

#include "sound/sh_sound.h"

#include "SH2_common/sh2dt.h"

extern /* static */ float stg_apart_e2f_cry_pos[4]; // @ 0x01F076E0

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

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgUseApart202Key);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvProgMonkeyKick206);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvCharaDataClear);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvSoundCallAfterLoad);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_EvAllTimeFunc);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_apart_e2f", stg_apart_e2f_Delete_RedPointLight);
