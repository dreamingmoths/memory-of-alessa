#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_common.h"
#include "Chacter/m3_play.h"
#include "shared/Chacter_Draw/clani.h"

/* static */ void event_jms_stand(void);

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

int PlayerEventJamesDeadly(void) {
    if ((sh2jms.player != NULL) && (sh2jms.dead != 0)) {
        return 1;
    }
    return 0;
}

int PlayerEventMariaDeadly(void) {
    if (sh2mar.mar_p && sh2mar.dead) {
        return 1;
    }
    return 0;
}

int PlayerEventAnimeSuccessFrame(void) { // https://decomp.me/scratch/NjmuL other version with line matched
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(sh2jms.player, 1); // r16
    short frame = shCharacterAnimeFrameGet_(sh2jms.player, 1); // r2 
    
    if (a_info->pad != 0 && frame >= a_info->pad) {
        return 1;
    } 
    return 0;
}

void PlayerEventAnimeSet(int anime /* r16 */) {
    player_flg_on((int*)&sh2jms.lower_st_flg, 0x80000000);
    player_flg_on((int*)&sh2jms.l_anime_st_flg, 0x40);
    player_flg_on((int*)&sh2jms.u_anime_st_flg, 0x40);
    sh2jms.event_anime = anime;
}

void PlayerEventAnimeSetDirect(int anime /* r16 */)  {
    player_flg_on((int*)&sh2jms.lower_st_flg, 0x80000000);
    player_flg_on((int*)&sh2jms.l_anime_st_flg, 0x40);
    player_flg_on((int*)&sh2jms.u_anime_st_flg, 0x40);
    sh2jms.event_anime = anime;
    SET_BIT(sh2jms.event_anime, 31);
}

/* static */ void event_jms_stand(void) {
    PlayerSpeedDownToStand(sh2jms.player);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", event_jms_walk); // https://decomp.me/scratch/1P1Qz 89%

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", event_jms_run); // https://decomp.me/scratch/DPU6a 92%

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", PlayerEventMove);

int PlayerEventMoveIsEnd(void) {
    if (((sh2jms.event_status_now == 0) && (l_anime_flg_on(2) == 0) && (l_anime_flg_on(0x40) == 0)) || (sh2jms.event_move_mode == 0)) {
        PlayerEventMoveCancel();
        return 1;
    }
    return 0;
}

int PlayerEventMoveCancel(void) {
    sh2jms.event_move_mode = 0;
    sh2jms.event_status_now = 0xFF;
    sh2jms.event_status_prev = 0xFF;
    sh2jms.tired = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", shCharacterHumanPJAMESAnimeSet); // https://decomp.me/scratch/8CNtW 99%

void JamesWeaponSet(int wep /* r2 */) {
    sh2jms.weapon = wep;
    switch (wep) {
        case 0:
        case 1:
        case 4:
            sh2jms.motion_no = 0;
            break;
        case 2:
        case 3:
            sh2jms.motion_no = 1;
            break;
        case 5:
        case 6:
            sh2jms.motion_no = 2;
            break;
        case 8:
            sh2jms.motion_no = 3;
            break;
        case 7:
            sh2jms.motion_no = 4;
            break;
    }
    sh2jms.hold_type = -1;
    actwithwep_flg_set(0, &sh2jms);
    PlayerCheckInit(sh2jms.player);
}

int PlayerGetJamesWeapon(void) {
    return (u_char)sh2jms.weapon;
}
