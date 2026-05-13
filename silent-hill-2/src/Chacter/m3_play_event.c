#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_common.h"
#include "shared/Chacter_Draw/clani.h"

static void event_jms_stand(void);

int PlayerNowDemoEventMode(void) {
    return sh2jms.player->status & 0x2000 ? 1 : 0;
}

int PlayerEventButtonCheck(int button /* r2 */) {
    int pad; // r2
    
    switch (button) {
        case 0:
            pad = sh2jms.pad[0].action;
            break;
        case 1:
            pad = sh2jms.pad[0].menu;
            break;
        case 2:
            pad = sh2jms.pad[0].light;
            break;
        case 3:
            pad = sh2jms.pad[0].map;
            break;
        default:
            return 0;
    }
    if (pad != 0 && (u_char) sh2jms.upper_now < JMS_ST_U_WALL_F) {
        return 1;
    }
    return 0;
}

int PlayerEventDeadAnimeFinish(void) {
    return sh2jms.dead == 2;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventJamesDeadly); // https://decomp.me/scratch/8HQSd 93%

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventMariaDeadly); // https://decomp.me/scratch/o80q8 93%

int PlayerEventAnimeSuccessFrame(void) { // https://decomp.me/scratch/NjmuL other version with line matched
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(sh2jms.player, 1); // r16
    short frame = shCharacterAnimeFrameGet_(sh2jms.player, 1); // r2 
    
    if (a_info->pad != 0 && frame >= a_info->pad) {
        return 1;
    } 
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventAnimeSet); // https://decomp.me/scratch/hL9A1 alignment problem

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventAnimeSetDirect); // https://decomp.me/scratch/xpBEF alignment problem

static void event_jms_stand(void) {
    PlayerSpeedDownToStand(sh2jms.player);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", event_jms_walk);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", event_jms_run);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventMove);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventMoveIsEnd);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventMoveCancel);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", shCharacterHumanPJAMESAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", JamesWeaponSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerGetJamesWeapon);
