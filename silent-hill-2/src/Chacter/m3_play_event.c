#include "Chacter/m3_play_event.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play_common.h"
#include "Chacter/m3_play.h"
#include "shared/Chacter_Draw/clani.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/playing_info.h"

// @todo: clean-up and migrate data

static void event_jms_stand(void);
static void event_jms_walk(float* target);
static void event_jms_run(float* target);

static void (*func_list_event[3])(float *) = { event_jms_stand, event_jms_walk, event_jms_run };

static int pjames_anime_adr_list[30] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x11CD0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
}; // size: 0x78, address: 0x379EB0

static float distance_990 = 0.0f;

extern /* static */ AnimeInfo pjames_demo_anim[30]; // size: 0x168, address: 0x0

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

static void event_jms_stand(void) {
    PlayerSpeedDownToStand(sh2jms.player);
}

static void event_jms_walk(float* target) {
    SubCharacter* p;
    float to_target; 
    p = sh2jms.player;
    
    
    
    
    if (p->spd > 1.5f) {
        
        p->spd -= 5.0f * shGetDT();
        p->spd = (p->spd > 1.5f) ? p->spd : 1.5f;
    } else {
        
        p->spd += 2.5f * shGetDT();
        p->spd = (p->spd > 1.5f) ? 1.5f : p->spd;
    }
    p->spd_org = p->spd;
    
    
    to_target = shAtan2(target[2] - p->pos.z, target[0] - p->pos.x);
    
    
    
    close_to_angle_target(&p->rot.y, to_target, -PI, PI, 12.0f);
    
    
    
    
    
    
    
    
    switch (playing.control_type) {
        case 0:
            p->spd_roty = 0.0f;
            break;
        case 1:
            p->spd_roty = to_target;
            break;
    }

}

#ifdef HOLY_CANDLE
static void event_jms_run(float* target) {
    SubCharacter* p;
    float to_target;   
    p = sh2jms.player;
    
    
    
    
    p->spd += 3.0f * shGetDT();
    p->spd = (p->spd > 4.0f) ? 4.0f : p->spd;
    p->spd_org = p->spd;

    
    to_target = shAtan2(target[2] - p->pos.z, target[0] - p->pos.x);
    

    close_to_angle_target(&p->rot.y, to_target, -PI, PI, 8.0f);

    
    
    
    
    
    switch (playing.control_type) {
        case 0:
            p->spd_roty = 0.0f;
            break;
        case 1:
            p->spd_roty = to_target;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_event", event_jms_run);
#endif

float PlayerEventMove(float* target /* r16 */) {
    void (* event_jms_func)(float *); // r2
    
    
    
    
    
    
    

    
    sh2jms.event_move_mode = 1;
    distance_990 = vec3_dist_xz_reverse(target, &sh2jms.player->pos);
    
    
    
    
    if (sh2jms.event_status_now != 0) {
        if (distance_990 > 3500.0f) {
            if (sh2jms.event_status_now != 2) {
                sh2jms.event_status_prev = sh2jms.event_status_now;
                sh2jms.event_status_now = 2;
            }
        } else 
            if (distance_990 > 87.49999850988388) {
                if (sh2jms.event_status_now != 1) {
                    sh2jms.event_status_prev = sh2jms.event_status_now;
                    sh2jms.event_status_now = 1;
                }
        } else {            
            
            if (sh2jms.event_status_now != 0) {
                sh2jms.event_status_prev = sh2jms.event_status_now;
                sh2jms.event_status_now = 0;
            }
        }
    }    
    if (sh2jms.event_status_prev != sh2jms.event_status_now) {
        player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
        player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_U_LROUND);
        sh2jms.event_status_prev = sh2jms.event_status_now;
    }
    
    
    
    
    event_jms_func = func_list_event[sh2jms.event_status_now];
    event_jms_func(target);
    
    
    return distance_990;
}

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

int shCharacterHumanPJAMESAnimeSet(SubCharacter* scp, int anime_id) {
    short id;
    struct _AnimeInfo* aip;

    id = shCharacterGetModelID(scp);
    
    if ((id == LLL_JMS_CHARA_KIND) || (id == HLL_JMS_CHARA_KIND)) {
        
        
        aip = &pjames_demo_anim[(anime_id - PJAMES_DRAMA_ANIME_ID_START)];
                shCharacterAnimeSet(scp,
                                    0,
                                    2,
                                    aip,
                                    pjames_anime_adr_list[anime_id - PJAMES_DRAMA_ANIME_ID_START] + (int)shCharacterGetAnimeAdrForDrama(scp, anime_id - PJAMES_DRAMA_ANIME_ID_START));
        
        
        
        return 0;
    }
    return -1;

}

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
