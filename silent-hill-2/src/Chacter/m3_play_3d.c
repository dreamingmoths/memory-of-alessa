#include "Chacter/m3_play_3d.h"
#include "Chacter/m3_sc.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/pad.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_play_common.h"

static int PlayerCheckLturn180(void);
static int PlayerCheckRturn180(void);
static int PlayerCheckTurn180(void);
static void lower_lround_3d_nata(SubCharacter* p, float* spd);
static void lower_rround_3d_nata(SubCharacter* p, float* spd);

/* static */ void lower_stand_3d(SubCharacter* p);
/* static */ void upper_stand_3d(SubCharacter* p);
/* static */ void lower_relax_3d(SubCharacter* p);
/* static */ void upper_relax_3d(SubCharacter* p);
/* static */ void lower_alert_3d(SubCharacter* p);
/* static */ void upper_alert_3d(SubCharacter* p);
/* static */ void lower_tired_3d(SubCharacter* p);
/* static */ void upper_tired_3d(SubCharacter* p);
/* static */ void lower_ready_3d(SubCharacter* p);
/* static */ void upper_ready_3d(SubCharacter* p);
/* static */ void lower_readyoff_3d(SubCharacter* p);
/* static */ void upper_readyoff_3d(SubCharacter* p);

static void PlayerUpdateStatusLower2nd3D(SubCharacter* this);
static void PlayerCheckAttack3D(SubCharacter* this);

static int PlayerCheckLturn180(void) {
    PAD_INFO* pad = &sh2jms.pad[0]; // r2
    PAD_3D* p3d = &pad->pad3d; // r4
    
    if (p3d->lslide != 0) {
        if ((p3d->lturn180 > 0) && (p3d->rturn180 == 2)) {
            return 1;
        }
    } else if ((p3d->lturn180 == 2) && (p3d->rturn180 == 2)) {
        return 2;
    }
    return 0;
}

static int PlayerCheckRturn180(void) {
    PAD_INFO* pad = &sh2jms.pad[0]; // r2
    PAD_3D* p3d = &pad->pad3d; // r4
   
    if (p3d->rslide != 0) {
        if ((p3d->rturn180 > 0) && (p3d->lturn180 == 2)) {
            return 1;
        }
    } else if ((p3d->rturn180 == 2) && (p3d->lturn180 == 2)) {
        return 2;
    }
    return 0;
}

static int PlayerCheckTurn180(void) { // not line matched
    PAD_3D* p3d = &sh2jms.pad[0].pad3d; // r5

    
    int l = PlayerCheckLturn180(); // r6
    int r = PlayerCheckRturn180(); // r2

    if (l == 0 && r == 0) return 0;
    
    switch (p3d->round_way) {
        case -1:
            return -1;
        case 1:
            return 1;
        default:
            if (l < r) {
                break;
            }
        return -1;
    }
    return 1;

}

static void lower_lround_3d_nata(SubCharacter* p, float* spd) {
    
    switch (sh2jms.ctrl_unit) {
        
        case 1:
            *spd = sh2jms.lstick_x;


            
            break;
        case 0:
            *spd = -1.0f;
            break;
    }
    shCharacterAnimeSpeedAdd_(p, 2, -384); 
    shCharacterAnimeSpeedAdd_(p, 1, -384);
}

static void lower_rround_3d_nata(SubCharacter* p, float* spd) {
    
    switch (sh2jms.ctrl_unit) {
        
        case 1:
            *spd = sh2jms.lstick_x;


            
            break;
        case 0:
            *spd = 1.0f;
            break;
    }
    shCharacterAnimeSpeedAdd_(p, 2, -384);
    shCharacterAnimeSpeedAdd_(p, 1, -384);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_walk_3d_nata);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_back_3d_nata);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lswalk_3d_nata);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rswalk_3d_nata);

/* static */ void lower_stand_3d(SubCharacter* p) {
    lower_stand(p);
}

/* static */ void upper_stand_3d(SubCharacter* p) {
    upper_stand(p);
}

/* static */ void lower_relax_3d(SubCharacter* p) {
    lower_relax(p);
}

/* static */ void upper_relax_3d(SubCharacter* p) {
    upper_relax(p);
}

/* static */ void lower_alert_3d(SubCharacter* p) {
    lower_alert(p);
}

/* static */ void upper_alert_3d(SubCharacter* p) {
    upper_alert(p);
}

/* static */ void lower_tired_3d(SubCharacter* p) {
    lower_tired(p);
}

/* static */ void upper_tired_3d(SubCharacter* p) {
    upper_tired(p);
}

/* static */ void lower_ready_3d(SubCharacter* p) {
    lower_ready(p);
}

/* static */ void upper_ready_3d(SubCharacter* p) {
    upper_ready(p);
}

/* static */ void lower_readyoff_3d(SubCharacter* p) {
    lower_readyoff(p);
}

/* static */ void upper_readyoff_3d(SubCharacter* p) {
    upper_readyoff(p);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lround_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_lround_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rround_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_rround_3d);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @947_0x0038C3B0);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @948_0x0038C3D0);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @968_0x0038C3F0);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @988_0x0038C410);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @1008_0x0038C430);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_walk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_walk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_back_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_back_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lswalk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_lswalk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rswalk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_rswalk_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_run1_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_run1_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_run2_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_run2_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_run3_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_run3_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lsrun_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_lsrun_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rsrun_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_rsrun_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lturn180_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_lturn180_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rturn180_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_rturn180_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_jump_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_jump_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_guard_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_guard_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_lstep_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_lstep_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_rstep_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_rstep_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_hold_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_hold_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_release_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_release_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_attack_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_attack_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_kick_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_kick_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_fall_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_fall_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_damage_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_damage_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_to_stand_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_to_stand_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_wall_f_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_wall_f_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", lower_event_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", upper_event_3d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", PlayerUpdateStatus3D);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", PlayerUpdateStatusStand3D);

extern float dtf_0x003C8488;
void PlayerUpdateStatusLower3D(SubCharacter* this) {
    
    shPlayerWork* w = &sh2jms;                // r16
    PAD_INFO* p = &sh2jms.pad;                // r17
    PAD_3D* p3d = &sh2jms.pad[0].pad3d;       // r18
    SubCharacterDisp* scp_d = &sh2jms.player; // r2

    
    
    
    
    
    
    
    
    
    
    
    if (lower_flg_on(1 << JMS_ST_L_FALL)) {
        if (w->lower_now != JMS_ST_L_FALL) {
            lower_st_set(JMS_ST_L_FALL, w);
            lower_flg_set(JMS_ST_L_FALL, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    
    
    
    
    
    if (lower_flg_on(1 << JMS_ST_L_GUARD)) {
        if (w->lower_now != JMS_ST_L_GUARD) {
            lower_st_set(21, w);
            lower_flg_set(21, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    
    
    
    
    if (lower_flg_on(1 << JMS_ST_L_DAMAGE)) {
        if (w->lower_now != JMS_ST_L_DAMAGE) {
            lower_st_set(JMS_ST_L_DAMAGE, w);
            lower_flg_set(JMS_ST_L_DAMAGE, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    
    
    
    
    
    
    if (lower_flg_on(1 << JMS_ST_L_EVENT)) {
        if (w->lower_now != JMS_ST_L_EVENT) {
            lower_st_set(JMS_ST_L_EVENT, w);
            lower_flg_set(JMS_ST_L_EVENT, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    
    
    
    
    
    
    if (w->upper_now == 0x1C) {
        switch (w->lower_now) { /* switch 1; irregular */
            case JMS_ST_L_WALK:
            case JMS_ST_L_BACK:
            case JMS_ST_L_LSWALK:
            case JMS_ST_L_RSWALK:
    
                
                
                
                
                
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if ((actwithwep_flg_on(1 << JMS_ST_L_LROUND)) && (u_anime_flg_on(1 << JMS_ST_L_LROUND) == 0)) {
                
                        return;
                    }
                    break;
                }
                
                
                
                
                
                
                if ((actwithwep_flg_on(1 << JMS_ST_L_LROUND)) && ((u_anime_flg_on(1 << JMS_ST_L_LROUND) == 0) || (sh2jms.strike_splash_flg))) {
                
                    return;
                }
                break;
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            case JMS_ST_L_RUN1:
            case JMS_ST_L_RUN2:
            case JMS_ST_L_RUN3:
            case JMS_ST_L_LSRUN:
            case JMS_ST_L_RSRUN:
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if ((actwithwep_flg_on(0x80)) && (u_anime_flg_on(1 << JMS_ST_L_LROUND) == 0)) {
                
                        return;
                    }
                }
                else if (sh2jms.map_mode == 0) {
                    
                    
                    
                    
                    
                    
                    
                    if ((actwithwep_flg_on(0x80)) && ((u_anime_flg_on(1 << JMS_ST_L_LROUND) == 0) || (sh2jms.strike_splash_flg))) {
                        
                        return;
                    }
                }
                break;
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            case JMS_ST_L_HOLD:
            case JMS_ST_L_ATTACK:
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if (l_anime_flg_on(1 << JMS_ST_L_LROUND) == 0) {
            
                        return;
                    }
                    break;
                }
                
                
                
                
                if ((l_anime_flg_on(1 << JMS_ST_L_LROUND) == 0) || (sh2jms.strike_splash_flg)) {
                
                    return;
                }
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if ((this->eye.kind == 1) && (sh2jms.inner_to_wall <= -0.85f) && !(sh2jms.running_time < 3.0f)) {
        
        if (lower_flg_on(1 << JMS_ST_L_WALL_F)) {
            lower_st_set(17, w);
            lower_flg_set(17, w);
        }
    }
    
    
    
    
    switch (PlayerCheckTurn180()) { /* switch 2; irregular */
        case -1:
            if ((lower_flg_on(1 << JMS_ST_L_LTURN)) && (w->hold_type == -1)) {
                if (w->lower_now != JMS_ST_L_LTURN) {
                    lower_st_set(JMS_ST_L_LTURN, w);
                    lower_flg_set(JMS_ST_L_LTURN, w);
                    player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                }
                ;
                REFLEX_ANGLE(w->dist_rot.y, this->rot.y - PI);
                
                w->dist_rot.w = 0.0f;
                return;
            }
            break;
        case 1:
            if ((lower_flg_on(1 << JMS_ST_L_RTURN)) && (w->hold_type == -1)) {
                if (w->lower_now != JMS_ST_L_RTURN) {
                    lower_st_set(19, w);
                    lower_flg_set(19, w);
                    player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                }
                
                REFLEX_ANGLE(w->dist_rot.y, this->rot.y - PI);
                
                w->dist_rot.w = 0.0f;
                return;
            }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if ((p->forward) || (p->lstickY < 0)) {
    
        
        
        
        PlayerCheckStraightLine(this, this->spd_roty);
        
        
        
        
        
        if ((p->dash) && (sh2jms.cannot_run == 0)) {
        
            
            
            
            
            
            if ((lower_flg_on(1 << JMS_ST_L_RUN3)) && (sh2jms.map_mode == 0) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
            
                
                
                
                
                
                
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND)))) {
                        
                    if (w->lower_now != JMS_ST_L_RUN3) {
                        lower_st_set(JMS_ST_L_RUN3, w);
                        lower_flg_set(JMS_ST_L_RUN3, w);
                        
                        if (this->spd < 3.0f)
                            this->spd = 3.0f;
                    }
                }
                return;
            }
            if ((lower_flg_on(1 << JMS_ST_L_RUN2)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
                
                
                
                
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND)))) {

                    if (w->lower_now != JMS_ST_L_RUN2) {
                        lower_st_set(JMS_ST_L_RUN2, w);
                        lower_flg_set(JMS_ST_L_RUN2, w);
                        
                        if (this->spd < 2.5f)
                            this->spd = 2.5f;
                    }
                }
                return;
            }
            if ((lower_flg_on(1 << JMS_ST_L_RUN1)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_RUN1)) {
                    lower_st_set(JMS_ST_L_RUN1, w);
                    lower_flg_set(JMS_ST_L_RUN1, w);
                    if (this->spd < 1.5f) {
                        this->spd = 1.5f;
                    }
                }
                return;
            }
        }
        if (((p->dash == 0) || (w->hold_type != -1) || (sh2jms.cannot_run)) && (lower_flg_on(1 << JMS_ST_L_WALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(1 << JMS_ST_L_LROUND))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_WALK)) {
                lower_st_set(9, w);
                lower_flg_set(9, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if (((p->backward) || (p->lstickY > 0)) && (lower_flg_on(1 << JMS_ST_L_BACK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(1 << JMS_ST_L_LROUND))))) {
        if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_BACK)) {
            lower_st_set(8, w);
            lower_flg_set(8, w);
            this->spd = 0.6f;
        }
        return;
    }
    if ((p3d->lslide) && ((p3d->rslide == 0) || (w->lower_now == JMS_ST_L_LSRUN))) {
        float roty;
        switch (w->lower_prev) {
            case 9:
            case 0xC:
            case 0xD:
            case 0xE:
                roty = this->spd_roty;
                break;
            default:
                roty = -QUARTER_TURN;
                break;
        }
        PlayerCheckStraightLine(this, roty);
        if ((p->dash) && (sh2jms.cannot_run == 0) && (lower_flg_on(1 << JMS_ST_L_LSRUN)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_LSRUN)) {
                lower_st_set(JMS_ST_L_LSRUN, w);
                lower_flg_set(JMS_ST_L_LSRUN, w);
                this->spd = 2.0f;
            }
            return;
        }
        if (((p->dash == 0) || (w->hold_type != -1) || (sh2jms.cannot_run)) && (lower_flg_on(1 << JMS_ST_L_LSWALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(1 << JMS_ST_L_LROUND))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_LSWALK)) {
                lower_st_set(JMS_ST_L_LSWALK, w);
                lower_flg_set(JMS_ST_L_LSWALK, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if ((p3d->rslide) && ((p3d->lslide == 0) || (w->lower_now == JMS_ST_L_RSRUN))) {
        float roty;
        switch (w->lower_prev) {
            case 9:
            case 0xC:
            case 0xD:
            case 0xE:
                roty = this->spd_roty;
                break;
            default:
                roty = QUARTER_TURN;
                break;
        }
        PlayerCheckStraightLine(this, roty);
        if ((p->dash) && (sh2jms.cannot_run == 0) && (lower_flg_on(1 << JMS_ST_L_RSRUN)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_RSRUN)) {
                lower_st_set(16, w);
                lower_flg_set(16, w);
                this->spd = 2.0f;
            }
            return;
        }
        if (((p->dash == 0) || (w->hold_type != -1) || (sh2jms.cannot_run)) && (lower_flg_on(1 << JMS_ST_L_RSWALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(1 << JMS_ST_L_LROUND))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(1 << JMS_ST_L_LROUND))) && (w->lower_now != JMS_ST_L_RSWALK)) {
                lower_st_set(11, w);
                lower_flg_set(11, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if (((p->lround) || (p->lstickX < 0)) && (lower_flg_on(1 << JMS_ST_L_LROUND))) {
        if (w->lower_now != JMS_ST_L_LROUND) {
            lower_st_set(6, w);
            lower_flg_set(6, w);
        }
        return;
    }
    if (((p->rround) || (p->lstickX > 0)) && (lower_flg_on(1 << JMS_ST_L_RROUND))) {
        if (w->lower_now != JMS_ST_L_RROUND) {
            lower_st_set(7, w);
            lower_flg_set(7, w);
        }
        return;
    }
    if ((w->l_anime_st_flg == 0) && (shPadPress(0, key_config.dash)) && (sh2jms.weapon != 8) && (lower_flg_on(16))) {
        if (w->lower_now != JMS_ST_L_READY) {
            lower_st_set(4, w);
            lower_flg_set(4, w);
        }
        return;
    }
    if (lower_flg_on(1 << JMS_ST_L_READYOFF)) {
        if (w->lower_now != JMS_ST_L_READYOFF) {
            lower_st_set(5, w);
            lower_flg_set(5, w);
        }
        return;
    }
    if ((lower_flg_on(1 << JMS_ST_L_TIRED)) && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->lower_now != JMS_ST_L_TIRED) {
            lower_st_set(3, w);
            lower_flg_set(3, w);
        }
        return;
    }
    if (lower_flg_on(1)) {
        if (w->lower_now != JMS_ST_L_STAND) {
            lower_st_set(0, w);
            lower_flg_set(0, w);
            sh2jms.no_damage = 0;
            sh2jms.player->battle.id = 0;
            if (sh2jms.lower_prev == 0x19) {
                sh2jms.muteki_time = 2.0f;
            }
        }
        return;
    }
    if (shPadPress(0, key_config.ready) == 0) {
        w->non_input += dtf_0x003C8488;
    }
    if (!(w->non_input < 10.0f) && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->enemy_around) {
            if (lower_flg_on(4)) {
                if (w->lower_now != JMS_ST_L_ALERT) {
                    lower_st_set(2, w);
                    lower_flg_set(2, w);
                }
                return;
            }
        } else if ((lower_flg_on(2)) && (w->lower_now != JMS_ST_L_RELAX)) {
            lower_st_set(1, w);
            lower_flg_set(1, w);
        }
    }
}

void PlayerUpdateStatusUpper3D(SubCharacter* this) {
    shPlayerWork* w = &sh2jms;      // r16
    PAD_INFO* p = &w->pad;          // r17
    PAD_INFO* p_pre = &w->pad[1];   // r18
    PAD_3D* p3d = &w->pad[0].pad3d; // r2

    switch (w->lower_now) {
        case JMS_ST_L_GUARD:
            if (w->upper_now != JMS_ST_L_GUARD) {
                upper_st_set(JMS_ST_U_GUARD, w);
                upper_flg_set(JMS_ST_U_GUARD, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case JMS_ST_L_DAMAGE:
            if (w->upper_now != JMS_ST_L_DAMAGE) {
                upper_st_set(JMS_ST_U_DAMAGE, w);
                upper_flg_set(JMS_ST_U_DAMAGE, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case JMS_ST_L_FALL:
            if (w->upper_now != JMS_ST_L_FALL) {
                upper_st_set(JMS_ST_U_FALL, w);
                upper_flg_set(JMS_ST_U_FALL, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case JMS_ST_L_WALL_F:
            if (w->upper_now != JMS_ST_L_WALL_F) {
                upper_st_set(JMS_ST_U_WALL_F, w);
                upper_flg_set(JMS_ST_U_WALL_F, w);
            }
            return;
        case JMS_ST_L_EVENT:
            if (w->upper_now != JMS_ST_L_EVENT) {
                upper_st_set(JMS_ST_U_EVENT, w);
                upper_flg_set(JMS_ST_U_EVENT, w);
            }
            return;
        default:
            if ((w->weapon != 0) && (u_anime_flg_on(2) == 0)) {
                if (p->hold != 0) {
                    if (upper_flg_on(1 << JMS_ST_U_HOLD) != 0) {
                        if (w->upper_now != JMS_ST_L_HOLD) {
                            upper_st_set(JMS_ST_U_HOLD, w);
                            upper_flg_set(JMS_ST_U_HOLD, w);
                            actwithwep_flg_set(w->weapon, w);
                            if (sh2jms.upper_prev != 0x1C) {
                                if ((playing.battle_level != 1) && (playing.battle_level != 0)) {
                                    int unknown = 0;
                                } else {
                                    ItemWeaponReload(PlayerNowItemName(sh2jms.weapon), 1);
                                }
                            }
                            PlayerGetTarget();
                            PlayerCheckBothArmsAngle(this);
                        } else if (w->target != NULL) {
                            if (((p_pre->lstickX == 0) && (p->lstickX > 0)) || (shPadTrigger(0, key_config.right_turn) != 0)) {
                                PlayerChangeTarget(1);
                            }
                            if (((p_pre->lstickX == 0) && (p->lstickX < 0)) || (shPadTrigger(0, key_config.left_turn) != 0)) {
                                PlayerChangeTarget(-1);
                            }
                            PlayerCheckBothArmsAngle(this);
                        }
                        if ((w->weapon == 1) && (w->target == NULL) && (w->lock_on != 0)) {
                            player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                            if (w->lower_now == 0x1A) {
                                player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_U_LROUND);
                            }
                        }
                        if (w->target != NULL) {
                            w->lock_on = 1;
                        } else {
                            w->lock_on = 0;
                        }
                        return;
                    }
                } else if (upper_flg_on(1 << JMS_ST_U_RELEASE) != 0) {
                    if (w->upper_now != JMS_ST_L_RELEASE) {
                        upper_st_set(JMS_ST_U_RELEASE, w);
                        upper_flg_set(JMS_ST_U_RELEASE, w);
                        player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                        actwithwep_flg_set(0U, w);
                        sh2jms.target = NULL;
                    }
                    return;
                }
            }
            switch (w->lower_now) {
                case JMS_ST_L_STAND:
                    if (!upper_flg_on(1 << JMS_ST_U_STAND))
                        break;
                    if (!w->upper_now)
                        break;
                    upper_st_set(JMS_ST_U_STAND, w);
                    upper_flg_set(JMS_ST_U_STAND, w);
                    return;
                case JMS_ST_L_RELAX:
                    if ((upper_flg_on(1 << JMS_ST_U_RELAX) != 0) && (w->upper_now != JMS_ST_L_RELAX)) {
                        upper_st_set(JMS_ST_U_RELAX, w);
                        upper_flg_set(JMS_ST_U_RELAX, w);
                        return;
                    }
                    break;
                case JMS_ST_L_ALERT:
                    if ((upper_flg_on(1 << JMS_ST_U_ALERT) != 0) && (w->upper_now != JMS_ST_L_ALERT)) {
                        upper_st_set(JMS_ST_U_ALERT, w);
                        upper_flg_set(JMS_ST_U_ALERT, w);
                        return;
                    }
                    break;
                case JMS_ST_L_TIRED:
                    if ((upper_flg_on(1 << JMS_ST_U_TIRED) != 0) && (w->upper_now != JMS_ST_L_TIRED)) {
                        upper_st_set(JMS_ST_U_TIRED, w);
                        upper_flg_set(JMS_ST_U_TIRED, w);
                        return;
                    }
                    break;
                case JMS_ST_L_READY:
                    if ((w->u_anime_st_flg == 0) && (upper_flg_on(1 << JMS_ST_U_READY) != 0) && (w->upper_now != JMS_ST_L_READY)) {
                        upper_st_set(JMS_ST_U_READY, w);
                        upper_flg_set(JMS_ST_U_READY, w);
                        return;
                    }
                    break;
                case JMS_ST_L_READYOFF:
                    if ((upper_flg_on(1 << JMS_ST_U_READYOFF) != 0) && (w->upper_now != JMS_ST_L_READYOFF)) {
                        upper_st_set(JMS_ST_U_READYOFF, w);
                        upper_flg_set(JMS_ST_U_READYOFF, w);
                        player_flg_on(&w->u_anime_st_flg, 2);
                        player_flg_off(&w->upper_st_flg, 1 << JMS_ST_U_RUN3);
                        return;
                    }
                    break;
                case JMS_ST_L_LROUND:
                    if ((upper_flg_on(1 << JMS_ST_U_LROUND) != 0) && (w->upper_now != JMS_ST_L_LROUND)) {
                        upper_st_set(JMS_ST_U_LROUND, w);
                        upper_flg_set(JMS_ST_U_LROUND, w);
                        return;
                    }
                    break;
                case JMS_ST_L_RROUND:
                    if ((upper_flg_on(1 << JMS_ST_U_RROUND) != 0) && (w->upper_now != JMS_ST_L_RROUND)) {
                        upper_st_set(JMS_ST_U_RROUND, w);
                        upper_flg_set(JMS_ST_U_RROUND, w);
                        return;
                    }
                    break;
                case JMS_ST_L_BACK:
                    if ((upper_flg_on(1 << JMS_ST_U_BACK) != 0) && (w->upper_now != JMS_ST_L_BACK)) {
                        upper_st_set(JMS_ST_U_BACK, w);
                        upper_flg_set(JMS_ST_U_BACK, w);
                        if (sh2jms.act_with_wep & 1) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_WALK:
                    if ((upper_flg_on(1 << JMS_ST_U_WALK) != 0) && (w->upper_now != JMS_ST_L_WALK)) {
                        upper_st_set(JMS_ST_U_WALK, w);
                        upper_flg_set(JMS_ST_U_WALK, w);
                        if (sh2jms.act_with_wep & 1) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_LSWALK:
                    if ((upper_flg_on(1 << JMS_ST_U_LSWALK) != 0) && (w->upper_now != JMS_ST_L_LSWALK)) {
                        upper_st_set(JMS_ST_U_LSWALK, w);
                        upper_flg_set(JMS_ST_U_LSWALK, w);
                        if (sh2jms.act_with_wep & 1) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_RSWALK:
                    if ((upper_flg_on(1 << JMS_ST_U_RSWALK) != 0) && (w->upper_now != JMS_ST_L_RSWALK)) {
                        upper_st_set(JMS_ST_U_RSWALK, w);
                        upper_flg_set(JMS_ST_U_RSWALK, w);
                        if (sh2jms.act_with_wep & 1) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_RUN1:
                    if ((upper_flg_on(1 << JMS_ST_U_RUN1) != 0) && (w->upper_now != JMS_ST_L_RUN1)) {
                        upper_st_set(JMS_ST_U_RUN1, w);
                        upper_flg_set(JMS_ST_U_RUN1, w);
                        if (sh2jms.act_with_wep & 2) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_RUN2:
                    if ((upper_flg_on(1 << JMS_ST_U_RUN2) != 0) && (w->upper_now != JMS_ST_L_RUN2)) {
                        upper_st_set(JMS_ST_U_RUN2, w);
                        upper_flg_set(JMS_ST_U_RUN2, w);
                        if (sh2jms.act_with_wep & 2) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_RUN3:
                    if ((upper_flg_on(1 << JMS_ST_U_RUN3) != 0) && (w->upper_now != JMS_ST_L_RUN3)) {
                        upper_st_set(JMS_ST_U_RUN3, w);
                        upper_flg_set(JMS_ST_U_RUN3, w);
                        if (sh2jms.act_with_wep & 2) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_LSRUN:
                    if ((upper_flg_on(1 << JMS_ST_U_LSRUN) != 0) && (w->upper_now != JMS_ST_L_LSRUN)) {
                        upper_st_set(JMS_ST_U_LSRUN, w);
                        upper_flg_set(JMS_ST_U_LSRUN, w);
                        if (sh2jms.act_with_wep & 2) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_RSRUN:
                    if ((upper_flg_on(1 << JMS_ST_U_RSRUN) != 0) && (w->upper_now != JMS_ST_L_RSRUN)) {
                        upper_st_set(JMS_ST_U_RSRUN, w);
                        upper_flg_set(JMS_ST_U_RSRUN, w);
                        if (sh2jms.act_with_wep & 2) {
                            player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                            return;
                        }
                    }
                    break;
                case JMS_ST_L_LTURN:
                    if (w->upper_now != JMS_ST_L_LTURN) {
                        upper_st_set(JMS_ST_U_LTURN, w);
                        upper_flg_set(JMS_ST_U_LTURN, w);
                        player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                        return;
                    }
                    break;
                case JMS_ST_L_RTURN:
                    if (w->upper_now != JMS_ST_L_RTURN) {
                        upper_st_set(JMS_ST_U_RTURN, w);
                        upper_flg_set(JMS_ST_U_RTURN, w);
                        player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                        return;
                    }
                    break;
                case JMS_ST_L_JUMP:
                    if (w->upper_now != JMS_ST_L_JUMP) {
                        upper_st_set(JMS_ST_U_JUMP, w);
                        upper_flg_set(JMS_ST_U_JUMP, w);
                    }
                    break;
                case JMS_ST_L_GUARD:
                case JMS_ST_L_LSTEP:
                case JMS_ST_L_RSTEP:
                case JMS_ST_L_FALL:
                case JMS_ST_L_DAMAGE:
                case JMS_ST_L_HOLD:
                case JMS_ST_L_RELEASE:
                case JMS_ST_L_ATTACK:
                case JMS_ST_L_KICK:
                case JMS_ST_L_TO_STAND:
                    break;
            }
            break;
    }
} 

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_3d", PlayerUpdatePosition3D);

static void PlayerUpdateStatusLower2nd3D(SubCharacter* this) { // not line matched
    shPlayerWork* w = &sh2jms; // r16

    
    switch (w->upper_now) {
        case JMS_ST_U_HOLD:
            if (lower_flg_on(0x4000000)) {
                if (w->lower_now != JMS_ST_L_HOLD) {
                    lower_st_set(JMS_ST_L_HOLD, w);
                    lower_flg_set(JMS_ST_L_HOLD, w);
                }
            }
            break;
        case JMS_ST_U_RELEASE:
            if (lower_flg_on(0x8000000)) {
                if (w->lower_now != JMS_ST_L_RELEASE) {
                    lower_st_set(JMS_ST_L_RELEASE, w);
                    lower_flg_set(JMS_ST_L_RELEASE, w);
                    player_flg_on(&w->l_anime_st_flg, 0x40);
                }
            }
            break;
        case JMS_ST_U_ATTACK:
            if (lower_flg_on(0x10000000)) {
                if (w->lower_now != JMS_ST_L_ATTACK || w->lower_prev == JMS_ST_L_ATTACK) {
                    lower_st_set(JMS_ST_L_ATTACK, w);
                    lower_flg_set(JMS_ST_L_ATTACK, w);
                }
            } else {
                if (lower_flg_on(0x4000000)) {
                    if (w->lower_now != JMS_ST_L_HOLD) {
                        lower_st_set(JMS_ST_L_HOLD, w);
                        lower_flg_set(JMS_ST_L_HOLD, w);
                        player_flg_off(&w->lower_st_flg, 0x1000);
                        player_flg_off(&w->lower_st_flg, 0x2000);
                        player_flg_off(&w->lower_st_flg, 0x4000);
                        player_flg_off(&w->lower_st_flg, 0x10000);
                        player_flg_off(&w->lower_st_flg, 0x8000);
                        player_flg_off(&w->lower_st_flg, 0x100);
                        player_flg_off(&w->lower_st_flg, 0x200);
                        player_flg_off(&w->lower_st_flg, 0x800);
                        player_flg_off(&w->lower_st_flg, 0x400);
                    }
                }
            }
            break;        
        case JMS_ST_U_KICK:
            break;
    }
    
    switch (w->lower_now) {
        case JMS_ST_L_RUN1:
        case JMS_ST_L_RUN2:
        case JMS_ST_L_RUN3:
        case JMS_ST_L_RSRUN:
        case JMS_ST_L_LSRUN:
            w->running = 1;
            break;
        default:
            w->running = 0;
            break;
    }
}

static void PlayerCheckAttack3D(SubCharacter* this) {
    PlayerCheckAttack(this);
}

void PlayerCheckControl3D(SubCharacter* this) {
    PlayerUpdateStatus3D(this);
    PlayerUpdateStatusLower3D(this);
    PlayerUpdateStatusUpper3D(this);
    PlayerCheckAttack3D(this);
    PlayerUpdateStatusLower2nd3D(this);
}

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @2681);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @2682);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @2683);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play_3d", @2684);
