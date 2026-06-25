#include "common.h"
#include "Chacter/character.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh_vu0.h"

extern float angle;
extern float dtf_0x003C8450;
extern int dt_0x003C8458;

void PlayerChangeAngleToCameraY(SubCharacter* this) {
    f32 diff;
    f32 step;

    diff = shAngleRegulate(this->rot.y - this->spd_roty);
    step = (diff / 3.0915927410125734) * (20.0f * dtf_0x003C8450);

    if (diff >= 0.0f) {
        if ((diff - step) <= 0.0f) {
            this->rot.y = this->spd_roty;
        } else {
            this->rot.y -= step;
        }
    } else if ((diff - step) >= 0.0f) {
        this->rot.y = this->spd_roty;
    } else {
        this->rot.y -= step;
    }
    this->rot.y = shAngleRegulate(this->rot.y);
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_walk_2d_nata);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_stand_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_stand_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_relax_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_relax_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_alert_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_alert_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_tired_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_tired_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_ready_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_ready_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_readyoff_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_readyoff_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_walk_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_walk_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_back_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_lswalk_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_rswalk_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_run1_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_run1_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_run2_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_run2_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_run3_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_run3_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_lsrun_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_rsrun_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_jump_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_jump_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_guard_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_guard_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_lstep_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_lstep_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_rstep_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_rstep_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_hold_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_hold_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_release_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_release_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_attack_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_attack_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_kick_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_kick_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_fall_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_fall_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_damage_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_damage_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_to_stand_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_to_stand_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_wall_f_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_wall_f_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", lower_event_2d);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", upper_event_2d);

void PlayerUpdateStatus2D(SubCharacter* this) {
    dt_0x003C8458 = shGetDF();
    dtf_0x003C8450 = shGetDT();
    PlayerSetDT();
    PlayerUpdateStatus(this);
}

void PlayerUpdateStatusLower2D(SubCharacter* this) {
    shPlayerWork* w = &sh2jms; // r16
    PAD_INFO* p = &sh2jms.pad; // r17
    PAD_2D* p2d = &sh2jms.pad->pad2d; // r18
    Vector4 cam_pos; // r29+0x50
    Vector4 watch_pos; // r29+0x60
    float lower_motion_angle; // r29+0x70
    int cam; // not part of dwarf
    
    vcGetNowCamPos(&cam_pos);
    vcGetNowWatchPos(&watch_pos);
    if ((vcRetCamMvSmoothF() == 0) && (sh2jms.cam_chg_flg == 0)) {
        sh2jms.cam_chg_flg = 1;
        sh2jms.now_cam_no = !sh2jms.now_cam_no;
    }
    sh2jms.cam_rot_y[sh2jms.now_cam_no] = shAtan2(watch_pos.z - cam_pos.z, watch_pos.x - cam_pos.x);
    switch (sh2jms.upper_now) {
       case (1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY):
            angle = this->spd_roty;
            break;

        case (1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY): 
        case (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY):
        case (1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_READY):
            angle = this->spd_roty = this->rot.y;
            break;

        default: {
            float roty;
            if (sh2jms.lock_on) {
                if (sh2jms.lstick_p) {
                    if (sh2jms.cam_chg_flg) {
                        cam = 1 - sh2jms.now_cam_no;
                    } else {
                        cam = sh2jms.now_cam_no;
                    }
                    this->spd_roty = shAngleRegulate(sh2jms.cam_rot_y[cam] + p2d->dir);
                } else {
                    this->spd_roty = 0.0f;
                    sh2jms.cam_chg_flg = 0;
                }
                angle = this->rot.y;
                roty = shAngleRegulate(this->spd_roty - this->rot.y);
                if (roty >= 2.3561945f || (roty < -2.3561945f)) {
                    p2d->lower_motion = 2;
                } else if (roty >= 0.7853982f) {
                    p2d->lower_motion = 3;
                } else if (roty >= -0.7853982f) {
                    p2d->lower_motion = 1;
                } else {
                    p2d->lower_motion = 4;
                }
            } else {
                if (sh2jms.lstick_p) {
                    if (sh2jms.cam_chg_flg) {
                        cam = 1 - sh2jms.now_cam_no;
                    } else {
                        cam = sh2jms.now_cam_no;
                    }
                    angle = shAngleRegulate(sh2jms.cam_rot_y[cam] + p2d->dir);
                } else {
                    angle = this->rot.y;
                    sh2jms.cam_chg_flg = 0;
                }
                this->spd_roty = angle;
                p2d->lower_motion = 0;
            }
            break;
        }
    }
    if (lower_flg_on(1 << JMS_ST_L_FALL)) {
        if (w->lower_now != 0x18) {
            lower_st_set(JMS_ST_L_FALL, w);
            lower_flg_set(JMS_ST_L_FALL, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    if (lower_flg_on(1 << JMS_ST_L_GUARD)) {
        if (w->lower_now != 0x15) {
            lower_st_set(JMS_ST_L_GUARD, w);
            lower_flg_set(JMS_ST_L_GUARD, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    if (lower_flg_on(1 << JMS_ST_L_DAMAGE)) {
        if (w->lower_now != 0x19) {
            lower_st_set(JMS_ST_L_DAMAGE, w);
            lower_flg_set(JMS_ST_L_DAMAGE, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    if (lower_flg_on(1 << JMS_ST_L_EVENT)) {
        if (w->lower_now != 0x1F) {
            lower_st_set(JMS_ST_L_EVENT, w);
            lower_flg_set(JMS_ST_L_EVENT, w);
            player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
        return;
    }
    if (w->upper_now == 0x1C) {
        switch (w->lower_now) {
            case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_TIRED):
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if ((actwithwep_flg_on(0x40)) && (u_anime_flg_on(0x40) == 0)) {
                        return;
                    }
                    break;
                }
                if ((actwithwep_flg_on(0x40)) && (u_anime_flg_on(0x40) == 0)) {
                    return;
                }
                break;
            case (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            case (1 << JMS_ST_L_READY):
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if ((actwithwep_flg_on(0x80)) && (u_anime_flg_on(0x40) == 0)) {
                        return;
                    }
                    break;
                }
                if ((actwithwep_flg_on(0x80)) && (u_anime_flg_on(0x40) == 0)) {
                    return;
                }
                break;
            case (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
            case (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
                if ((sh2jms.weapon == 1) || (sh2jms.weapon == 4)) {
                    if (l_anime_flg_on(0x40) == 0) {
                        return;
                    }
                    break;
                }
                if (l_anime_flg_on(0x40)) {
                    break;
                }
                return;
            }
    }

    if ((this->eye.kind == 1) && (sh2jms.inner_to_wall <= -0.85f) && sh2jms.running_time >= 3.0f && (lower_flg_on(1 << JMS_ST_L_WALL_F))) {
        lower_st_set(JMS_ST_L_WALL_F, w);
        lower_flg_set(JMS_ST_L_WALL_F, w);
    }
    if ((sh2jms.lstick_p) && ((s32) p2d->lower_motion < 2)) {
        PlayerCheckStraightLine(this, this->spd_roty);
        if ((p->dash) && (sh2jms.cannot_run == 0)) {
            if ((lower_flg_on(1 << JMS_ST_L_RUN3)) && !sh2jms.map_mode && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xE)) {
                    lower_st_set(JMS_ST_L_RUN3, w);
                    lower_flg_set(JMS_ST_L_RUN3, w);
                    if (this->spd < 3.0f) {
                        this->spd = 3.0f;
                    }
                }
                return;
            }
            if ((lower_flg_on(1 << JMS_ST_L_RUN2)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xD)) {
                    lower_st_set(JMS_ST_L_RUN2, w);
                    lower_flg_set(JMS_ST_L_RUN2, w);
                    if (this->spd < 2.5f) {
                        this->spd = 2.5f;
                    }
                }
                return;
            }
            if ((lower_flg_on(1 << JMS_ST_L_RUN1)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
                if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xC)) {
                    lower_st_set(JMS_ST_L_RUN1, w);
                    lower_flg_set(JMS_ST_L_RUN1, w);
                    if (this->spd < 1.5f) {
                        this->spd = 1.5f;
                    }
                }
                return;
            }
        }
        if (((p->dash == 0) || (w->hold_type != -1) || sh2jms.cannot_run) && (lower_flg_on(1 << JMS_ST_L_WALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x40))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 9)) {
                lower_st_set(JMS_ST_L_WALK, w);
                lower_flg_set(JMS_ST_L_WALK, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if ((sh2jms.lstick_p) && (p2d->lower_motion == 2) && (lower_flg_on(1 << JMS_ST_L_BACK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x40))))) {
        if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 8)) {
            lower_st_set(JMS_ST_L_BACK, w);
            lower_flg_set(JMS_ST_L_BACK, w);
            this->spd = 0.6f;
        }
        return;
    }
    if ((sh2jms.lstick_p) && (p2d->lower_motion == 4)) {
        float roty;
        switch (w->lower_prev) {
            case 9:
            case 12:
            case 13:
            case 14:
                roty = this->spd_roty;
                break;
            default:
                roty = -QUARTER_TURN;
        }
        PlayerCheckStraightLine(this, roty);
        if ((p->dash) && (sh2jms.cannot_run == 0) && (lower_flg_on(1 << JMS_ST_L_LSRUN)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xF)) {
                lower_st_set(JMS_ST_L_LSRUN, w);
                lower_flg_set(JMS_ST_L_LSRUN, w);
                this->spd = 2.0f;
            }
            return;
        }
        if (((p->dash == 0) || (w->hold_type != -1) || sh2jms.cannot_run) && (lower_flg_on(1 << JMS_ST_L_LSWALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x40))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xA)) {
                lower_st_set(JMS_ST_L_LSWALK, w);
                lower_flg_set(JMS_ST_L_LSWALK, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if ((sh2jms.lstick_p) && (p2d->lower_motion == 3)) {
        float roty;
        switch (w->lower_prev) {
            case 9:
            case 12:
            case 13:
            case 14:
                roty = this->spd_roty;
                break;
            default:
                roty = QUARTER_TURN;
        }
        PlayerCheckStraightLine(this, roty);
        if ((p->dash) && (sh2jms.cannot_run == 0) && (lower_flg_on(1 << JMS_ST_L_RSRUN)) && ((w->hold_type == -1) || ((w->upper_now != 0x1C) && (actwithwep_flg_on(8))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x80))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0x10)) {
                lower_st_set(JMS_ST_L_RSRUN, w);
                lower_flg_set(JMS_ST_L_RSRUN, w);
                this->spd = 2.0f;
            }
            return;
        }
        if (((p->dash == 0) || (w->hold_type != -1) || sh2jms.cannot_run) && (lower_flg_on(1 << JMS_ST_L_RSWALK)) && (((w->upper_now != 0x1C) && (actwithwep_flg_on(4))) || ((w->upper_now == 0x1C) && (actwithwep_flg_on(0x40))))) {
            if (((sh2jms.l_anime_st_flg == 0) || (l_anime_flg_on(0x40))) && (w->lower_now != 0xB)) {
                lower_st_set(JMS_ST_L_RSWALK, w);
                lower_flg_set(JMS_ST_L_RSWALK, w);
                if (this->spd < 0.6f) {
                    this->spd = 0.6f;
                }
            }
            return;
        }
    }
    if ((w->l_anime_st_flg == 0) && (shPadPress(0, key_config.dash)) && (sh2jms.weapon != 8) && (lower_flg_on(1 << JMS_ST_L_READY)) && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->lower_now != 4) {
            lower_st_set(JMS_ST_L_READY, w);
            lower_flg_set(JMS_ST_L_READY, w);
        }
        return;
    }
    if ((lower_flg_on(1 << JMS_ST_L_READYOFF)) && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->lower_now != 5) {
            lower_st_set(JMS_ST_L_READYOFF, w);
            lower_flg_set(JMS_ST_L_READYOFF, w);
        }
        return;
    }
    if ((lower_flg_on(1 << JMS_ST_L_TIRED)) && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->lower_now != 3) {
            lower_st_set(JMS_ST_L_TIRED, w);
            lower_flg_set(JMS_ST_L_TIRED, w);
        }
        return;
    }
    if (lower_flg_on(1 << JMS_ST_L_STAND)) {
        if (w->lower_now) {
            lower_st_set(JMS_ST_L_STAND, w);
            lower_flg_set(JMS_ST_L_STAND, w);
            sh2jms.no_damage = 0;
            sh2jms.player->battle.id = 0;
            if (sh2jms.lower_prev == 0x19) {
                sh2jms.muteki_time = 2.0f;
            }
        }
        return;
    }
    if (shPadPress(0, key_config.ready) == 0) {
        w->non_input += dtf_0x003C8450;
    }
    if (w->non_input >= 10.0f && (PlayerSearchVIewButtonCheck() == 0)) {
        if (w->enemy_around) {
            if (lower_flg_on(1 << JMS_ST_L_ALERT)) {
                if (w->lower_now != 2) {
                    lower_st_set(JMS_ST_L_ALERT, w);
                    lower_flg_set(JMS_ST_L_ALERT, w);
                }
                return;
            }
        } else {
            if ((lower_flg_on(1 << JMS_ST_L_RELAX)) && (w->lower_now != 1)) {
                lower_st_set(JMS_ST_L_RELAX, w);
                lower_flg_set(JMS_ST_L_RELAX, w);
            }
        }
    
    }
    
}

void PlayerUpdateStatusUpper2D(SubCharacter* this) {
    shPlayerWork* w = &sh2jms; // r16
    PAD_INFO* p = &w->pad; // r17
    PAD_INFO* p_pre = &w->pad[1]; // r18
    PAD_2D* p2d = &w->pad->pad2d; // r18
    
    switch (w->lower_now) {
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_READY):
            if (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_READY))) {
                upper_st_set(JMS_ST_U_GUARD, w);
                upper_flg_set(JMS_ST_U_GUARD, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
            if (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) {
                upper_st_set(JMS_ST_U_DAMAGE, w);
                upper_flg_set(JMS_ST_U_DAMAGE, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
            if (w->upper_now != ((1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) {
                upper_st_set(JMS_ST_U_FALL, w);
                upper_flg_set(JMS_ST_U_FALL, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            }
            return;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_READY):
            if (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_READY))) {
                upper_st_set(JMS_ST_U_WALL_F, w);
                upper_flg_set(JMS_ST_U_WALL_F, w);
            }
            return;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
            if (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) {
                upper_st_set(JMS_ST_U_EVENT, w);
                upper_flg_set(JMS_ST_U_EVENT, w);
            }
            return;
    }

    if ((w->weapon != 0) && (u_anime_flg_on(2) == 0)) {
        if (p->hold != 0) {
            if (upper_flg_on(1 << JMS_ST_U_HOLD) != 0) {
                if (w->upper_now != ((1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) {
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
                    if (shPadTrigger(0, key_config.right_move) != 0) {
                        PlayerChangeTarget(1);
                    }
                    if (shPadTrigger(0, key_config.left_move) != 0) {
                        PlayerChangeTarget(-1);
                    }
                    PlayerCheckBothArmsAngle(this);
                }
                if ((w->weapon == 1) && (w->target == NULL) && (w->lock_on != 0)) {
                    player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                    if (w->lower_now == 0x1A) {
                        player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                    }
                }
                if (w->target != NULL) {
                    w->lock_on = 1;
                } else {
                    w->lock_on = 0;
                }
                return;
            }
        } 
        else 
            if (upper_flg_on(1 << JMS_ST_U_RELEASE) != 0) {
                if (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) {
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
        case JMS_ST_U_STAND:
            if ((upper_flg_on(1 << JMS_ST_U_STAND) != 0) && (w->upper_now != 0)) {
                upper_st_set(JMS_ST_U_STAND, w);
                upper_flg_set(JMS_ST_U_STAND, w);
                break;
            }
            break;
        case (1 << JMS_ST_L_STAND):
            if ((upper_flg_on(1 << JMS_ST_U_RELAX) != 0) && (w->upper_now != 1)) {
                upper_st_set(JMS_ST_U_RELAX, w);
                upper_flg_set(JMS_ST_U_RELAX, w);
                break;
            }
            break;
        case (1 << JMS_ST_L_RELAX):
            if ((upper_flg_on(1 << JMS_ST_U_ALERT) != 0) && (w->upper_now != 2)) {
                upper_st_set(JMS_ST_U_ALERT, w);
                upper_flg_set(JMS_ST_U_ALERT, w);
                break;
            }
            break;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_RELAX):
            if ((upper_flg_on(1 << JMS_ST_U_TIRED) != 0) && (w->upper_now != 3)) {
                upper_st_set(JMS_ST_U_TIRED, w);
                upper_flg_set(JMS_ST_U_TIRED, w);
                break;
            }
            break;
        case (1 << JMS_ST_L_ALERT):
            if ((w->u_anime_st_flg == 0) && (upper_flg_on(1 << JMS_ST_U_READY) != 0) && (w->upper_now != 4)) {
                upper_st_set(JMS_ST_U_READY, w);
                upper_flg_set(JMS_ST_U_READY, w);
                break;
            }
            break;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_ALERT):
            if ((upper_flg_on(1 << JMS_ST_U_READYOFF) != 0) && (w->upper_now != 5)) {
                upper_st_set(JMS_ST_U_READYOFF, w);
                upper_flg_set(JMS_ST_U_READYOFF, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_RELAX);
                player_flg_off(&w->upper_st_flg, 0x4000);
                break;
            }
            break;
        case (1 << JMS_ST_L_TIRED):
            if ((upper_flg_on(1 << JMS_ST_U_BACK) != 0) && (w->upper_now != 8)) {
                upper_st_set(JMS_ST_U_BACK, w);
                upper_flg_set(JMS_ST_U_BACK, w);
                if (sh2jms.act_with_wep & 1) {
                    player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                    break;
                }
            }
            break;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_TIRED):
            if ((upper_flg_on(1 << JMS_ST_U_WALK) != 0) && (w->upper_now != 9)) {
                upper_st_set(JMS_ST_U_WALK, w);
                upper_flg_set(JMS_ST_U_WALK, w);
                if (sh2jms.act_with_wep & 1) {
                    player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                    break;
                }
            }
            break;
        case (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            if ((upper_flg_on(1 << JMS_ST_U_RUN1) != 0) && (w->upper_now != ((1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED)))) {
                upper_st_set(JMS_ST_U_RUN1, w);
                upper_flg_set(JMS_ST_U_RUN1, w);
                if (sh2jms.act_with_wep & 2) {
                    player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                    break;
                }
            }
            break;
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            if ((upper_flg_on(1 << JMS_ST_U_RUN2) != 0) && (w->upper_now != ((1 << JMS_ST_U_STAND) | (1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED)))) {
                upper_st_set(JMS_ST_U_RUN2, w);
                upper_flg_set(JMS_ST_U_RUN2, w);
                if (sh2jms.act_with_wep & 2) {
                    player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                    break;
                }
            }
            break;
        case (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED):
            if ((upper_flg_on(1 << JMS_ST_U_RUN3) != 0) && (w->upper_now != ((1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED)))) {
                upper_st_set(JMS_ST_U_RUN3, w);
                upper_flg_set(JMS_ST_U_RUN3, w);
                if (sh2jms.act_with_wep & 2) {
                    player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_HOLD);
                }
            }
            break;
        case (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
        case (1 << JMS_ST_L_STAND) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
        case (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
        case (1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_ALERT) | (1 << JMS_ST_L_TIRED) | (1 << JMS_ST_L_READY):
            break;
    }
}

void PlayerUpdateStatusLower2nd2D(SubCharacter* this) {
    shPlayerWork* w = &sh2jms;

    switch (w->upper_now) {
        case JMS_ST_U_HOLD:
            if ((lower_flg_on(1 << JMS_ST_L_HOLD)) && (w->lower_now != JMS_ST_L_HOLD)) {
                lower_st_set(JMS_ST_L_HOLD, w);
                lower_flg_set(JMS_ST_L_HOLD, w);
            }
            break;
        case JMS_ST_U_RELEASE:
            if ((lower_flg_on(1 << JMS_ST_L_RELEASE) != 0) && (w->lower_now != JMS_ST_L_RELEASE)) {
                lower_st_set(JMS_ST_L_RELEASE, w);
                lower_flg_set(JMS_ST_L_RELEASE, w);
                player_flg_on(&w->l_anime_st_flg, 0x40);
            }
            break;
        case JMS_ST_U_ATTACK:
            if (lower_flg_on(1 << JMS_ST_L_ATTACK)) {
                if ((w->lower_now != JMS_ST_L_ATTACK) || (w->lower_prev == JMS_ST_L_ATTACK)) {
                    lower_st_set(JMS_ST_L_ATTACK, w);
                    lower_flg_set(JMS_ST_L_ATTACK, w);
                }
            } else if ((lower_flg_on(0x04000000) != 0) && (w->lower_now != JMS_ST_L_HOLD)) {
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

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_2d", PlayerUpdatePosition2D);

void PlayerCheckAttack2D(SubCharacter* this) {
    PlayerCheckAttack(this);
}

void PlayerCheckControl2D(SubCharacter* this) {
    PlayerUpdateStatus2D(this);
    PlayerUpdateStatusLower2D(this);
    PlayerUpdateStatusUpper2D(this);
    PlayerCheckAttack2D(this);
    PlayerUpdateStatusLower2nd2D(this);
}