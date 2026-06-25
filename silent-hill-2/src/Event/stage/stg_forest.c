#include "sh2_common.h"
#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh2sys.h"

#include "Event/event.h"
#include "Event/event_sub.h"

#include "sound/sh_sound.h"
#include "Effect/screen_effect.h"
#include "Chacter/character.h"
#include "data/daily.thu/data_pic_out.h"

#line 131
int stg_forest_EvProgFirstSaveWell(void) {
    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, true);
            PlayerEventAnimeSet(101);
            EV_PROG_STEP(2);
            /* fallthrough */
        case 2:
            if (!EvSubFileLoadAndFadeOut(NULL, &data_pic_out_p_redpaper_tex, 0))
                break;
            ScreenEffectFadeStart(4, 0.0f);
            EV_PROG_STEP(3);

                
        case 3:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) EV_PROG_STEP(8);
            break;

        case 8:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel)))
                EV_PROG_STEP(10);
            break;
        
        case 10:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (!EvSubMessage(0)) break;
            ScreenEffectFadeStart(11, 0.0f);
            EV_PROG_STEP(4);
            break;
        
        case 4:
            if (!ScreenEffectFadeCheck()) break;
            EV_PROG_STEP(13);

        case 13:
            SET_GAME_FLAG(5);
            SetSavePointName(2);
            SeCall(10051, 1.0f, 0);
            sh2sys_set_2(9);
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return 1;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgAngelaInGrave);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgGraveSureQuiet);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgGraveLookingFor);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgLastScene);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvProgGetChainsaw);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvStageInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvSoundCallAfterLoad);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_EvAllTimeFunc);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_LinearTrim);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_forest", stg_forest_Ca10_Hakaba_Angela_SetDrawEnv);
