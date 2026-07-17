#include "sh2_common.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/pad.h"
#include "SH2_common/sh2dt.h"
#include "SH2_common/sh_vu0.h"

#include "Chacter/m3_play_3d.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_play_common.h"
#include "Chacter/sh_character_battle.h"

#include "Event/event.h"

static void PlayerCheckHuggedPos(float* l_pos, int dir, float mov);
static int PlayerCheckKeyLStickTrg(int dir);

static int dt;
static float dtf;

#ifdef NON_MATCHING
void PlayerCheckHuggedPos(float* l_pos, int dir, float mov) {
    float tgt_rot;      // r21
    float target_pos_x; // @note: not in dwarf
    float target_pos_y; // @note: not in dwarf
    float target_pos_z; // @note: not in dwarf

    int anim_counter; // r16

    sh2jms.player->spd     = 0.0f;
    sh2jms.player->spd_org = 0.0f;

    target_pos_x = l_pos[0] * shCosF(sh2jms.player->battle.target->rot.y) + (l_pos[2] * shSinF(sh2jms.player->battle.target->rot.y));

    target_pos_y = l_pos[1];
    target_pos_z = (-l_pos[0] * shSinF(sh2jms.player->battle.target->rot.y) + (l_pos[2] * shCosF(sh2jms.player->battle.target->rot.y)));

    target_pos_x = sh2jms.player->battle.target->pos.x + target_pos_x;
    target_pos_y = sh2jms.player->battle.target->pos.y + target_pos_y;
    target_pos_z = sh2jms.player->battle.target->pos.z + target_pos_z;

    if (dir != 0) {
        tgt_rot = shAngleRegulate(PI + sh2jms.player->battle.target->rot.y);
    } else {
        tgt_rot = sh2jms.player->battle.target->rot.y;
    }

    close_to_value(&sh2jms.player->pos.x, target_pos_x, mov);
    close_to_value(&sh2jms.player->pos.y, target_pos_y, mov);
    close_to_value(&sh2jms.player->pos.z, target_pos_z, mov);

    close_to_angle_target(&sh2jms.player->rot.y, tgt_rot, -PI, PI, TAU);

    if (sh2jms.hug_status == 2) {
        anim_counter = shCharacterAnimeCounterGet(sh2jms.player->battle.target);
        shCharacterAnimeCounterSet_(sh2jms.player, 1, anim_counter);
        shCharacterAnimeCounterSet_(sh2jms.player, 2, anim_counter);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play_common", PlayerCheckHuggedPos);
#endif

void PlayerSetDT(void) {
    dt  = shGetDF();
    dtf = shGetDT();
}

void PlayerUpdateStatus(SubCharacter* this) {

    if (!clPermitColumnExpansion()) {
        sh2jms.map_mode = 2;

    } else {

        switch (stage->glb_crd) {
            case 1:
            case 2:
            case 3:
            case 5:
                sh2jms.map_mode = 0;
                break;
            default:
                sh2jms.map_mode = 1;
                break;
        }
    }

    shCharacterAnimeSpeedAdd(this, 0);

    if (sh2jms.weapon == WEAPON_NATA_CHARA_KIND >> 8) {
        if (l_anime_flg_on(4) == 0) {
            shCharacterAnimeSpeedAddY_(this, 2, -256);
            shCharacterAnimeSpeedAddY_(this, 1, -256);
        }
        if ((sh2jms.hold_type == -1) && (sh2jms.lower_now >= 8) && (sh2jms.lower_now < 12)) {

            shCharacterAnimeSpeedAdd_(this, 2, -512);
            shCharacterAnimeSpeedAdd_(this, 1, -512);
        }
    }

    sh2jms.cannot_run = 0;
    sh2jms.se_on      = 0;

    if ((sh2jms.lower_now >= 12) && (sh2jms.lower_now < 17)) {
        sh2jms.running_time += dtf;
    } else {
        sh2jms.running_time = 0.0f;
    }

    if (sh2jms.muteki_time) {
        if ((sh2jms.muteki_time -= dtf) < 0.0f) {
            sh2jms.muteki_time = 0.0f;
        }
    }
}

static int PlayerCheckKeyLStickTrg(int dir) {
    switch (dir) { /* irregular */
        case 2:
            return sh2jms.pad[0].lstickY > 0 && sh2jms.pad[1].lstickY <= 0;

        case 4:
            return sh2jms.pad[0].lstickX < 0 && sh2jms.pad[1].lstickX >= 0;

        case 6:
            return sh2jms.pad[0].lstickX > 0 && sh2jms.pad[1].lstickX <= 0;

        case 8:
            return sh2jms.pad[0].lstickY < 0 && sh2jms.pad[1].lstickY >= 0;

        default:
            return 0;
    }
}

void PlayerCheckHuggingButton(void) {
    float pow   = 0.0f;      // r29+32
    float gauge = shGetDT(); // r20

    if (shPadTrigger(0, key_config.action))
        pow += gauge;
    if (shPadTrigger(0, key_config.dash))
        pow += gauge;
    if (shPadTrigger(0, key_config.front_move))
        pow += gauge;
    if (shPadTrigger(0, key_config.back_move))
        pow += gauge;
    if (shPadTrigger(0, key_config.right_turn))
        pow += gauge;
    if (shPadTrigger(0, key_config.left_turn))
        pow += gauge;
    if (shPadTrigger(0, key_config.front_move))
        pow += gauge;
    if (shPadTrigger(0, key_config.right_move))
        pow += gauge;
    if (shPadTrigger(0, key_config.left_move))
        pow += gauge;
    if (PlayerCheckKeyLStickTrg(2))
        pow += gauge;
    if (PlayerCheckKeyLStickTrg(4))
        pow += gauge;
    if (PlayerCheckKeyLStickTrg(6))
        pow += gauge;
    if (PlayerCheckKeyLStickTrg(8))
        pow += gauge;
    if (pow) {
        sh2jms.hugging_gauge -= pow;

        if (sh2jms.hugging_gauge < 0.0f)
            sh2jms.hugging_gauge = 0.0f;
    }
}

void PlayerSpeedDownToStand(SubCharacter* p) {

    switch (sh2jms.lower_prev) {
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:

            p->spd -= 20.0f * shGetDT();

            break;

        default:
            p->spd -= 10.0f * shGetDT();
    }

    p->spd_org = p->spd = p->spd > 0.0f ? p->spd : 0.0f;

    if (playing.control_type != 0)
        return;
    if (p->spd == 0.0f) {
        p->spd_roty = 0.0f;
    }
}

void PlayerSetAttackWithWalkIsOk(void) {

    if ((sh2jms.upper_now == ((1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) || (sh2jms.upper_now == ((1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY)))) {
        if (!l_anime_flg_on(2))
            if ((sh2jms.act_with_wep & (1 << 4)) && sh2jms.atk_type < 4) {

                sh2jms.attack_ok = 1;
                return;
            }
    }
    sh2jms.attack_ok = 0;
}

void PlayerSetAttackWithRunIsOk(void) {
    if ((sh2jms.upper_now == ((1 << JMS_ST_U_ALERT) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) || (sh2jms.upper_now == ((1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY)))) {
        if (!l_anime_flg_on(2)) {
            if ((sh2jms.act_with_wep & (1 << 5)) && sh2jms.atk_type < 4) {

                sh2jms.attack_ok = 1;
                return;
            }
        }
    }
    sh2jms.attack_ok = 0;
}

void PlayerCheckAimingToEnemy(SubCharacter* p, SubCharacter* target) {
    float to_target; // r20
    float roty_tmp;  // r21
    float mov_angle; // r29+64

    if (target != NULL) {

        to_target = shAtan2(target->pos.z - p->pos.z, target->pos.x - p->pos.x);

        roty_tmp  = shAngleRegulate(p->rot.y - to_target);
        mov_angle = (roty_tmp / 3.0915927410125734) * (shGetDT() * 15.0f);
        if (roty_tmp >= 0.0f) {
            if (roty_tmp - mov_angle <= 0.0f)
                p->rot.y = to_target;
            else
                p->rot.y -= mov_angle;
        } else if (roty_tmp - mov_angle >= 0.0f)
            p->rot.y = to_target;
        else
            p->rot.y -= mov_angle;

        p->rot.y = shAngleRegulate(p->rot.y);
    }
}

void PlayerCheckAttack(SubCharacter* this) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(this, 1); // r2
    shPlayerWork* w   = &sh2jms;                           // r16
    PAD_INFO* pad;                                         // r2
    int attack_no;                                         // @note not in dwarf

    if ((w->upper_now == ((1 << JMS_ST_U_RELAX) | (1 << JMS_ST_U_TIRED) | (1 << JMS_ST_U_READY))) && ((sh2jms.anime_pause & 2) || (a_info->loop != 0))) {
        PlayerRequestAttack(w, 0);
        sh2jms.atk_count = 0;
    }
    if ((w->enemy_liedown != NULL) && ((w->upper_now < 18) || (w->upper_now > 29))) {
        PlayerRequestAttackFinish(w);
        player_flg_on(&w->upper_st_flg, 1 << JMS_ST_U_KICK);
    } else {
        player_flg_off(&w->upper_st_flg, 1 << JMS_ST_U_KICK);
    }
    if (w->upper_st_flg & (1 << JMS_ST_U_KICK)) {
        if (w->atk_reserve[0] != 0) {
            w->atk_type = w->atk_reserve[0];
            if (w->atk_type == 7) {
                attack_no = w->motion_no + 30;
            } else {
                attack_no = w->motion_no + 25;
            }
            w->attack_no = attack_no;
            shBattleAttackHitCheckInit(this);
            if (w->upper_now != 29) {
                upper_st_set(29, w);
                upper_flg_set(29, w);
                player_flg_on(&w->u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                lower_st_set(29, w);
                lower_flg_set(29, w);
                player_flg_on(&w->l_anime_st_flg, 1 << JMS_ST_L_LROUND);
            }
            w->atk_reserve[0] = 0;
            w->hold_type      = -1;
            w->lock_on        = 0;
        }
    } else if ((w->upper_st_flg & (1 << JMS_ST_U_ATTACK)) && (w->atk_reserve[0] != 0)) {
        shBattleAttackHitCheckInit(this);
        switch (w->weapon) {
            case 1:
                if ((w->shoot_val == 0) && (w->reload_val != 0)) {
                    w->atk_type  = 0;
                    w->attack_no = 3;
                } else {
                    if ((w->hold_type == 1) || (u_anime_flg_on(64) != 0)) {
                        w->hold_type = 1;
                        w->atk_type  = 2;
                        w->attack_no = 2;
                    } else {
                        w->atk_type  = 1;
                        w->attack_no = 1;
                    }
                    PlayerGetTarget();
                    if (w->target != NULL) {
                        w->lock_on = 1;
                    }
                }
                switch (w->lower_now) {
                    case JMS_ST_L_BACK:
                    case JMS_ST_L_WALK:
                    case JMS_ST_L_RSWALK:
                    case JMS_ST_L_LSWALK:
                        break;
                    default:
                        player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_HOLD);
                        break;
                    case JMS_ST_L_HOLD:
                        player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_ATTACK);
                        break;
                }
                break;
            case 2:
                if ((w->shoot_val == 0) && (w->reload_val != 0)) {
                    w->attack_no = 5;
                } else {
                    w->atk_type  = 2;
                    w->attack_no = 4;
                }
                switch (w->lower_now) {
                    case JMS_ST_L_BACK:
                    case JMS_ST_L_WALK:
                    case JMS_ST_L_RSWALK:
                    case JMS_ST_L_LSWALK:
                        player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_BACK);
                        player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_WALK);
                        player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_RSWALK);
                        player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_LSWALK);
                        player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_HOLD);
                        break;

                    default:
                        break;
                }
                break;
            case 3:
                if ((w->shoot_val == 0) && (w->reload_val != 0)) {
                    w->attack_no = 7;
                } else {
                    w->atk_type  = 2;
                    w->attack_no = 6;
                }
                player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_ATTACK);
                break;
            case 4:
                w->atk_type = 2;
                if ((w->shoot_val == 0) && (w->reload_val != 0)) {
                    if (sh2jms.upper_prev == 28) {
                        w->attack_no = 11;
                    } else {
                        w->attack_no = 10;
                    }
                } else if (w->atk_count != 0) {
                    w->atk_count = 1;
                    w->attack_no = 9;
                } else {
                    w->attack_no = 8;
                }
                break;
            case 5:
                if (w->running != 0) {
                    w->atk_type = 3;
                    if (w->atk_count != 0) {
                        w->atk_count = 1;
                        w->attack_no = 13;
                    } else {
                        w->attack_no = 12;
                    }
                } else {
                    if (w->atk_reserve[0] == 3) {
                        w->atk_type = 3;
                        if (w->atk_count != 0) {
                            w->atk_count = 1;
                            w->attack_no = 13;
                        } else {
                            w->attack_no = 12;
                        }
                    }
                    if (w->atk_reserve[0] == 4) {
                        w->atk_type  = 4;
                        w->attack_no = 14;
                    }
                }
                switch (w->lower_now) {
                    case JMS_ST_L_RUN1:
                    case JMS_ST_L_RUN2:
                    case JMS_ST_L_RUN3:
                    case JMS_ST_L_LSRUN:
                    case JMS_ST_L_RSRUN:
                        break;
                    case JMS_ST_L_BACK:
                    case JMS_ST_L_WALK:
                    case JMS_ST_L_LSWALK:
                    case JMS_ST_L_RSWALK:
                        if (w->atk_type == 4) {
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_BACK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_WALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_RSWALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_LSWALK);
                            player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_HOLD);
                        }
                        break;
                }
                break;
            case 6:
                if (w->atk_reserve[0] == 5) {
                    w->atk_type  = 5;
                    w->attack_no = 18;
                }
                if (w->atk_reserve[0] == 4) {
                    w->atk_type  = 4;
                    w->attack_no = 17;
                }
                if (w->atk_reserve[0] == 3) {
                    w->atk_type = 3;
                    if (w->atk_count != 0) {
                        w->atk_count = 1;
                        w->attack_no = 16;
                    } else {
                        w->attack_no = 15;
                    }
                }

                switch (w->lower_now) {
                    case JMS_ST_L_BACK:
                    case JMS_ST_L_WALK:
                    case JMS_ST_L_RSWALK:
                    case JMS_ST_L_LSWALK:
                        if (w->atk_type != 3) {
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_BACK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_WALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_RSWALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_LSWALK);
                            player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_HOLD);
                        }
                        break;

                    default:
                        // player_flg_on(&w->lower_st_flg, (1 << JMS_ST_L_ATTACK));
                        break;
                }
                break;
            case 7:
                if (w->atk_reserve[0] == 3) {
                    w->atk_type  = 3;
                    w->attack_no = 23;
                }
                if (w->atk_reserve[0] == 5) {
                    w->atk_type  = 5;
                    w->attack_no = 24;
                }
                switch (w->lower_now) {
                    case JMS_ST_L_BACK:
                    case JMS_ST_L_WALK:
                    case JMS_ST_L_RSWALK:
                    case JMS_ST_L_LSWALK:
                        if (w->atk_type == 5) {
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_BACK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_WALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_RSWALK);
                            player_flg_off(&w->lower_st_flg, 1 << JMS_ST_L_LSWALK);
                            player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_HOLD);
                        }
                        break;

                    default:
                        player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_ATTACK);
                        break;
                }
                break;

            case 8:
                if (w->atk_reserve[0] == 3) {
                    w->atk_type = 3;
                    if (w->hold_type == 0) {
                        w->attack_no = 19;
                    } else {
                        w->attack_no = 20;
                    }
                }
                if (w->atk_reserve[0] == 4) {
                    w->atk_type = 4;
                    if (w->hold_type == 0) {
                        w->attack_no = 21;
                    } else {
                        w->attack_no = 22;
                    }
                }
                player_flg_on(&w->lower_st_flg, 1 << JMS_ST_L_ATTACK);
                break;
        }
        if ((w->upper_now != 28) || (w->upper_prev == 28)) {
            upper_st_set(28, w);
            upper_flg_set(28, w);
        }
        ASSERT_ON_LINE(w->attack_no != 0, 727);
        w->atk_reserve[0] = 0;
    }
}

static inline int get_tired(int x, int y) {
    int w = y; // @ wtf?
    return (x / 3);
}

void lower_stand(SubCharacter* p) {
    actwithwep_flg_set(0, &sh2jms);
    sh2jms.tired -= dt;
    PlayerSpeedDownToStand(p);
    if (p->spd < 0.1f) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_READY);
    }
    if (get_tired(sh2jms.tired_max, sh2jms.tired) < sh2jms.tired) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_TIRED);
    }
}

void upper_stand(SubCharacter* p) {
    if (p->spd < 0.1f) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_READY);
    }
    if (get_tired(sh2jms.tired_max, sh2jms.tired) < sh2jms.tired) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_TIRED);
    }
}

void lower_relax(SubCharacter* p) {
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
    }
    if (sh2jms.weapon == 8) {
        shCharacterAnimeSpeedAdd_(p, 2, -192);
        shCharacterAnimeSpeedAdd_(p, 1, -192);
    }
}

void upper_relax(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
    }
}

void lower_alert(SubCharacter* p) {
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
    }
}

void upper_alert(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
    }
}

void lower_tired(SubCharacter* p) {
    AnimeInfo* temp_s0;

    sh2jms.tired -= dt;
    PlayerSpeedDownToStand(p);
    temp_s0 = shCharacterAnimeGetInfo_(p, 2);
    if (sh2jms.tired <= get_tired(sh2jms.tired_max, sh2jms.tired)) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
        player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_TIRED);
    }
    if (sh2jms.tired <= get_tired(sh2jms.tired_max * 2, sh2jms.tired) && temp_s0->name == 114) {
        player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
    }
}

void upper_tired(SubCharacter* p) {
    AnimeInfo* temp_s0;

    temp_s0 = shCharacterAnimeGetInfo_(p, 2);
    if (sh2jms.tired <= (get_tired(sh2jms.tired_max, sh2jms.tired))) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_TIRED);
    }
    if ((sh2jms.tired <= get_tired(sh2jms.tired_max * 2, sh2jms.tired)) && (temp_s0->name == 114)) {
        player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
    }
}

void lower_ready(SubCharacter* p) {
    PlayerSpeedDownToStand(p);
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_READYOFF);
        if (sh2jms.tired <= (get_tired(sh2jms.tired_max, sh2jms.tired))) {
            player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RUN3);
            return;
        }
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RUN2);
    }
}

void upper_ready(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_READYOFF);
        if (sh2jms.tired <= (get_tired(sh2jms.tired_max, sh2jms.tired))) {
            player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN3);
            return;
        }
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
    }
}

void lower_readyoff(SubCharacter* p) {
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
    }
}

void upper_readyoff(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
    }
}

void upper_run1(SubCharacter* p) {
    if (!(p->spd < 3.5f) && (sh2jms.u_anime_st_flg == 0)) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
        player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN1);
    }
}

void upper_run2(SubCharacter* p) {
    switch (sh2jms.ctrl_unit) { /* irregular */
        case 0:
            if ((p->spd == 4.0f) && (sh2jms.u_anime_st_flg == 0) && (sh2jms.tired < sh2jms.tired_max)) {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN3);
                player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
                break;
            }
            break;
        case 1:
            if ((p->spd <= 3.5f) && (sh2jms.u_anime_st_flg == 0)) {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN1);
                player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
            }
            if (!(p->spd < 4.0f) && (sh2jms.u_anime_st_flg == 0) && (sh2jms.tired < sh2jms.tired_max)) {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN3);
                player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
            }
            break;
    }
}

void upper_run3(SubCharacter* p) {
    switch (sh2jms.ctrl_unit) { /* irregular */
        case 0:
            if ((sh2jms.tired >= sh2jms.tired_max) && (sh2jms.u_anime_st_flg == 0)) {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
                player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN3);
                break;
            }
            break;
        case 1:
            if (((p->spd <= 4.0f) || (sh2jms.tired >= sh2jms.tired_max)) && (sh2jms.u_anime_st_flg == 0)) {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN2);
                player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RUN3);
            }
            break;
    }
}

void lower_hold(SubCharacter* p) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(p, 2);
    short frame       = shCharacterAnimeFrameGet_(p, 2);
    int check;

    PlayerSpeedDownToStand(p);
    switch (sh2jms.weapon) {
        case 3:
            if (!(sh2jms.anime_pause & 1) && (frame >= 4) && (frame < 15)) {
                if (playing.control_type == 0) {
                    p->spd_roty = 0.0f;
                }

                p->spd_org = p->spd = 25.0 * dtf;
            }
            break;
        case 5:
            if (((a_info->name == 351) || (a_info->name == 353)) && !(sh2jms.anime_pause & 1)) {
                if ((frame >= 2) && (frame < 9)) {
                    if (playing.control_type == 0) {
                        p->spd_roty = 0.0f;
                    }

                    p->spd_org = p->spd = 20.0 * dtf;
                }
            }
            break;
    }
    if ((sh2jms.anime_pause & 1) || ((a_info->loop != 0) && (a_info->name >= 200))) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RELEASE);
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_ATTACK);
        if (a_info->loop == 0) {
            switch (sh2jms.weapon) {
                case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                case WEAPON_ID(WEAPON_SP_CHARA_KIND):
                    sh2jms.hold_loop[1] = 1;
                    break;

                case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                    sh2jms.hold_loop[1] = 1;
                    break;
            }
        }
        if (sh2jms.hold_chg[1] == 0) {
            switch (sh2jms.weapon) {
                case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                    switch (sh2jms.hold_type) {
                        case 0:
                            if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                sh2jms.hold_chg[1] = 1;
                            }
                            break;
                        case 1:
                            if ((sh2jms.l_side.kind == 1) && (sh2jms.r_side.kind != 1)) {
                                sh2jms.hold_chg[1] = 1;
                            }
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        if ((sh2jms.upper_now != 28) || !(sh2jms.anime_pause & 8)) {
            if (sh2jms.hold_chg[1] != 0) {
                player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RELEASE);
                player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_ATTACK);
                player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                sh2jms.hold_loop[1] = 0;
            } else if (sh2jms.hold_loop[1] != 0) {
                player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
            }
        } else {
            sh2jms.hold_loop[1] = 0;
            sh2jms.hold_chg[1]  = 0;
        }
    }
    if ((sh2jms.weapon == 2) && (sh2jms.anime_pause & 1)) {
        check = 0;
        switch (a_info->name) {
            case 251:
            case 253:
            case 256:
            case 259:
            case 260:
            case 262:
            case 264:
                if (sh2jms.shotgun_dir != 1) {
                    check = 1;
                }
                break;
            case 254:
            case 261:
            case 266:
                if (sh2jms.shotgun_dir != 2) {
                    check = 1;
                }
                break;
            case 257:
            case 263:
            case 265:
                if (sh2jms.shotgun_dir != 0) {
                    check = 1;
                }
                break;
        }
        if (check != 0) {
            sh2jms.hold_chg[1] = 1;
            player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RELEASE);
            player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_ATTACK);
            player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
        }
    }
    sh2jms.attack_ok = 0;
}

void upper_hold(SubCharacter* p) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(p, 1);
    int check;

    if (sh2jms.lock_on != 0) {
        PlayerCheckAimingToEnemy(p, sh2jms.target);
    }
    if ((sh2jms.anime_pause & 2) || ((a_info->loop != 0) && (a_info->name >= 200))) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_ATTACK);
        if (a_info->loop == 0) {

            switch (sh2jms.weapon) {
                case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                case WEAPON_ID(WEAPON_SP_CHARA_KIND):
                    sh2jms.hold_loop[0] = 1;
                    break;
                default:
                    break;
            }
        }
        if (sh2jms.hold_chg[0] == 0) {
            switch (sh2jms.weapon) {
                case WEAPON_ID(WEAPON_KAKUZAI_CHARA_KIND):
                case WEAPON_ID(WEAPON_PIPE_CHARA_KIND):
                case WEAPON_ID(WEAPON_NATA_CHARA_KIND):
                case WEAPON_ID(WEAPON_CSAW_CHARA_KIND):
                    switch (sh2jms.hold_type) {
                        case 0:
                            if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                sh2jms.hold_chg[0] = 1;
                            }
                            break;
                        case 1:
                            if ((sh2jms.l_side.kind == 1) && (sh2jms.r_side.kind != 1)) {
                                sh2jms.hold_chg[0] = 1;
                            }
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        if (sh2jms.hold_chg[0] != 0) {
            player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
            player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_ATTACK);
            player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            sh2jms.hold_loop[0] = 0;
        } else if (sh2jms.hold_loop[0] != 0) {
            player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
        }
    }
    if ((sh2jms.weapon == 2) && (sh2jms.anime_pause & 2)) {
        check = 0;
        switch (a_info->name) {
            case 251:
            case 253:
            case 256:
            case 259:
            case 260:
            case 262:
            case 264:
                if (sh2jms.shotgun_dir != 1) {
                    check = 1;
                }
                break;
            case 254:
            case 261:
            case 266:
                if (sh2jms.shotgun_dir != 2) {
                    check = 1;
                }
                break;
            case 257:
            case 263:
            case 265:
                if (sh2jms.shotgun_dir != 0) {
                    check = 1;
                }
                break;
        }
        if (check != 0) {
            sh2jms.hold_chg[0] = 1;
            player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
            player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_ATTACK);
            player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
        }
    }
}

void lower_release(SubCharacter* p) {
    float temp_f0;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f0_4;
    s64 temp_a2;
    s64 temp_a2_2;
    short frame;

    frame = shCharacterAnimeFrameGet_(p, 2);
    PlayerSpeedDownToStand(p);
    switch (sh2jms.weapon) { /* irregular */
        case 3:
            if (!(sh2jms.anime_pause & 1)) {
                if ((frame >= 4) && (frame < 15)) {
                    if (playing.control_type == 0) {
                        p->spd_roty = -PI;

                        p->spd_org = p->spd = 25.0 * dtf;
                    } else {
                        p->spd_org = p->spd = -25.0 * dtf;
                    }
                }
            }
            break;
        case 5:
            if (!(sh2jms.anime_pause & 1)) {
                if ((frame >= 2) && (frame < 9)) {
                    if (playing.control_type == 0) {
                        p->spd_roty = -PI;

                        p->spd_org = p->spd = 20.0 * dtf;
                    } else {

                        p->spd_org = p->spd = -20.0 * dtf;
                    }
                }
            }
            break;
    }
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
        player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RELEASE);
    }
}

void upper_release(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_TIRED);
        player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
        sh2jms.lock_on = 0;
    }
    sh2jms.lock_on = 0;
    if ((sh2jms.lower_now == ((1 << JMS_ST_L_RELAX) | (1 << JMS_ST_L_READY))) || (sh2jms.lower_now == 19) || (sh2jms.lower_now == 20) || (sh2jms.lower_now == 21) || (sh2jms.lower_now == 23) || (sh2jms.lower_now == 22)) {
        player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
        sh2jms.lock_on = 0;
    }
}

void lower_attack(SubCharacter* p) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(p, 2);
    short frame       = shCharacterAnimeFrameGet_(p, 2);

    PlayerSpeedDownToStand(p);
    if (playing.control_type == 0) {
        p->spd_roty = 0.0f;
    }
    switch (sh2jms.weapon) { /* irregular */
        case 5:
            if ((sh2jms.atk_type == 4) && (a_info->speed > 0)) {
                frame = frame;
                if ((frame >= 4) && (frame < 10)) {

                    p->spd_org = p->spd = 30.0 * dtf;
                }
                if ((frame >= 11) && (frame < 20)) {

                    p->spd_org = p->spd = -20.0 * dtf;
                }
            }
            break;
        case 6:
            if ((sh2jms.atk_type == 5) && (a_info->speed > 0)) {
                frame = frame;
                if ((frame >= 2) && (frame < 10)) {

                    p->spd_org = p->spd = 35.0 * dtf;
                }
                if ((frame >= 14) && (frame < 25)) {

                    p->spd_org = p->spd = -20.0 * dtf;
                }
            }
            break;
        case 8:
            if (sh2jms.atk_type == 4) {
                if (sh2jms.hold_type == 0) {
                    if (a_info->speed > 0) {
                        if ((frame >= 10) && (frame < 14)) {
                            p->spd_org = p->spd = 5.0 * dtf;
                        }
                        if ((frame >= 14) && (frame < 17)) {
                            p->spd_org = p->spd = 30.0 * dtf;
                        }
                        if ((frame >= 2) && (frame < 5)) {
                            p->spd_org = p->spd = 10.0 * dtf;
                        }
                        if ((frame >= 25) && (frame < 31)) {
                            p->spd_org = p->spd = -28.0 * dtf;
                        }
                    }
                } else if (a_info->speed > 0) {
                    frame = frame;
                    if ((frame >= 14) && (frame < 18)) {

                        p->spd_org = p->spd = 33.0 * dtf;
                    }
                    if ((frame > 0) && (frame < 4)) {

                        p->spd_org = p->spd = -3.0 * dtf;
                    }
                    if ((frame >= 25) && (frame < 31)) {

                        p->spd_org = p->spd = -24.0 * dtf;
                    }
                }
            }
            break;
        case 7:
            if ((a_info->speed > 0) && (sh2jms.atk_type == 5)) {
                if (sh2jms.hold_type == 0) {
                    frame = frame;
                    if ((frame > 0) && (frame < 7)) {

                        p->spd_org = p->spd = 30.0 * dtf;
                    }
                    if ((frame >= 13) && (frame < 19)) {

                        p->spd_org = p->spd = -25.0 * dtf;
                    }
                } else {
                    frame = frame;
                    if ((frame >= 2) && (frame < 7)) {

                        p->spd_org = p->spd = 30.0 * dtf;
                    }
                    if ((frame >= 12) && (frame < 18)) {

                        p->spd_org = p->spd = -25.0 * dtf;
                    }
                }
            }
            break;
    }
    sh2jms.attack_ok = 1;
    if (sh2jms.anime_pause & 1) {
        if (sh2jms.pad[0].hold != 0) {
            if ((sh2jms.atk_reserve[0] != 0) || (sh2jms.atk_reserve[1] != 0)) {
                sh2jms.lower_prev = 28;
                player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_ATTACK);
                player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                return;
            }
            player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_HOLD);
            return;
        }
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_RELEASE);
    }
}
void upper_attack(SubCharacter* p) {
    AnimeInfo* a_info; // r16
    int wep;           // r17
    u_short name1;     // r3
    u_short name2;     // r5
    u_short frame;     // r16

    float var_f0;

    a_info = shCharacterAnimeGetInfo_(p, 1);
    wep    = PlayerNowItemName(sh2jms.weapon);
    if (sh2jms.lock_on != 0) {
        PlayerCheckAimingToEnemy(p, sh2jms.target);
    }
    if (sh2jms.attack_ok != 0) {
        if (sh2jms.anime_pause & 8) {
            sh2jms.anime_pause -= 8;
        }
        shCharacterAnimeRestart_(p, 1);
    } else {
        shCharacterAnimePause_(p, 1);
        sh2jms.anime_pause |= 8;
    }
    if ((sh2jms.u_anime_st_flg == 0) && (sh2jms.atk_reserve[0] == 0) && (shBattleRequestNextAttackIsOk(sh2jms.attack_no, (u_short) shCharacterAnimeFrameGet_(p, 1)) != 0)) {
        PlayerRequestAttack(&sh2jms, 1);
    }
    if ((sh2jms.anime_pause & 10) == 2) {
        if (sh2jms.pad[0].hold != 0) {
            sh2jms.atk_reserve[0] = sh2jms.atk_reserve[1];
            sh2jms.atk_reserve[1] = 0;
            if (sh2jms.atk_reserve[0] != 0) {
                sh2jms.atk_count += 1;
                sh2jms.upper_prev = 28;
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_ATTACK);
                player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
            } else {
                shCharacterAnimePause_(p, 1);
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_HOLD);
                sh2jms.shotgun_prev = 1;
                sh2jms.shotgun_dir  = 1;
            }
        } else {
            shCharacterAnimePause_(p, 1);
            player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_RELEASE);
        }
        if ((sh2jms.atk_type == 3) && (a_info->speed > 0)) {
            if (sh2jms.hold_type == 0) {
                sh2jms.hold_type = 1;
            } else {
                sh2jms.hold_type = 0;
            }
        }
        sh2jms.player->battle.atk_result = 0;
        return;
    }
    if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
        AnimeInfo* a_info = shCharacterAnimeGetInfo_(p, 1); // r2
        switch (sh2jms.weapon) {                            /* irregular */
            case 1:
                name1 = 209;
                name2 = 210;
                frame = 21;

                break;
            case 2:
                name1 = 260;
                name2 = 260;
                frame = 12;
                break;
            case 3:
                name1 = 304;
                name2 = 304;
                frame = 17;
                break;
            case 4:
                name1 = 510;
                name2 = 511;
                frame = 7;
                break;
            default:
                return;
        }
        if (((a_info->name == (name1)) || (a_info->name == (name2))) && ((shCharacterAnimeFrameGet_(p, 1)) >= (frame))) {
            ItemWeaponReload(wep, 1);
            if (sh2jms.weapon == 4) {
                if (sh2jms.spray_set != 0) {
                    sh2jms.spray_set -= 1;
                }
                sh2jms.spray_time = (20.0f * sh2jms.spray_set) / 200.0f;
            }
            sh2jms.lock_on   = 0;
            sh2jms.hold_type = 0;
            return;
        }
    } else {
        if (!sh2jms.attack_no)
            ASSERT_ON_LINE(0, 1961);
        switch (sh2jms.weapon) {
            case 8:
            case 7:
            case 4:
                if (sh2jms.attack_ok != 0) {
                    shBattleAttackHitCheckToEnemy(p, sh2jms.weapon, sh2jms.attack_no);
                }
                break;
            default:
                if ((p->battle.atk_result == 0) && (sh2jms.attack_ok != 0)) {
                    shBattleAttackHitCheckToEnemy(p, sh2jms.weapon, sh2jms.attack_no);
                }
                break;
        }
    }
}

void lower_kick(SubCharacter* p) {
    PlayerSpeedDownToStand(p);
    if (sh2jms.enemy_liedown != NULL) {
        PlayerCheckAimingToEnemy(p, sh2jms.enemy_liedown);
    }
    sh2jms.attack_ok = 1;
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
        player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_KICK);
    }
}

void upper_kick(SubCharacter* p) {
    if (p->battle.atk_result != 1) {
        if (!sh2jms.attack_no)
            ASSERT_ON_LINE(0, 2000);
        shBattleAttackHitCheckToEnemy(p, sh2jms.weapon, sh2jms.attack_no);
    }
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_KICK);
    }
}

void lower_fall(SubCharacter* p) {
    float temp_f2;
    float var_f0;

    if ((u_short) shCharacterAnimeFrameGet_(p, 2) < 21) {
        if (p->spd > 0.9f) {
            PlayerSpeedDownToStand(p);
        } else {
            p->spd += (2.5f * dtf);
            p->spd_org = p->spd = p->spd > 0.9f ? 0.9f : p->spd;
        }
    } else {
        PlayerSpeedDownToStand(p);
    }
    if (sh2jms.anime_pause & 1) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
    }
}

void upper_fall(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        PlayerStatusClear();
    }
}

void lower_damage(SubCharacter* p) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo_(p, 2); // r2
    float damage_angle;                                 // r29+128
    u_short cur_frame;                                  // r16
    sceVu0FVECTOR hugging_pos[5] = {
        {52.133198, 1550.9032, 36.494709, 0.0},
        {43.538513, -93.47943, 353.91226, 0.0},
        {0.000018835068, 0.0, 328.05243, 0.0},
        {0.0, 0.0, 176.79146, 0.0},
        {0.0, 1496.4872, 0.000002, 0.0},
    };

    cur_frame   = shCharacterAnimeFrameGet_(p, 2);
    p->spd_roty = shAngleRegulate(shAtan2(p->battle.vec[2], p->battle.vec[0]) - p->rot.y);
    if (l_anime_flg_on(2) == 0) {
        switch (sh2jms.damage_no) {
            case 20008:
            case 20009:
                if ((cur_frame > 0) && (cur_frame < 8)) {
                    p->spd = 0.96000004f;
                } else {
                    p->spd = 0.0f;
                }
                break;
            case 20012:
            case 20013:

                if ((cur_frame > 0) && (cur_frame < 8)) {
                    p->spd = 0.3f;
                } else {
                    p->spd = 0.0f;
                }
                break;
            case 20016:

                if ((cur_frame > 0) && (cur_frame < 8)) {
                    p->spd = 1.2f;
                } else {
                    p->spd = 0.0f;
                }
                break;
            case 20017:

                if ((cur_frame > 0) && (cur_frame < 8)) {
                    p->spd = -1.2f;
                } else {
                    p->spd = 0.0f;
                }
                break;
            case 20021:
            case 20022:
                p->spd = 0.0f;
                break;
            case 20023:
            case 20024:
                p->spd = 0.0f;
                break;
            case 20025:
            case 20026:

                if ((cur_frame > 0) && (cur_frame < 4)) {
                    p->spd = -0.3f;
                } else {
                    p->spd = 0.0f;
                }
                break;
            case 20033:
            case 20034:
                if (4 < cur_frame) {
                    p->spd = 0.0f;
                } else {
                    p->spd = 0.6f;
                }
                break;
            case 20037:
                p->spd = 0.0f;
                break;
            case 20029:
            case 20030:
            case 20031:

                PlayerCheckHuggedPos(hugging_pos[1], 1, dtf * 500.0);
                break;
            case 20038:
            case 20039:
            case 20040:

                PlayerCheckHuggedPos(hugging_pos[0], 1, dtf * 500.0);
                break;
            case 20042:
            case 20043:
            case 20045:

                PlayerCheckHuggedPos(hugging_pos[2], 1, dtf * 500.0);
                break;
            case 20046:
            case 20047:
            case 20049:

                PlayerCheckHuggedPos(hugging_pos[3], 0, dtf * 500.0);
                break;
            case 20056:
            case 20054:
            case 20055:

                PlayerCheckHuggedPos(hugging_pos[4], 1, dtf * 500.0);
                break;
            default:
                p->spd = 0.0f;
                break;
        }
    }
    p->spd_org = p->spd;
    if ((sh2jms.hugging_gauge) || (sh2jms.hug_status == 3)) {
        switch (sh2jms.hug_status) {
            case 1:
                if (sh2jms.anime_pause & 1) {
                    player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                    player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                    sh2jms.hug_status = 2;
                    return;
                }
                break;
            case 2:
                if (sh2jms.dead == 0) {
                    PlayerCheckHuggingButton();
                    if (sh2jms.hugging_gauge == 0.0f) {
                        player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                        player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                        sh2jms.hug_status = 3;
                        return;
                    }
                    if (p->battle.hp <= 0.0f) {
                        sh2jms.dead = 1;
                        return;
                    }
                } else {
                    player_flg_on(&sh2jms.l_anime_st_flg, 1 << JMS_ST_L_LROUND);
                    player_flg_on(&sh2jms.u_anime_st_flg, 1 << JMS_ST_U_LROUND);
                    if (sh2jms.player->battle.target->kind != 515) {
                        sh2jms.hug_status = 3;
                        return;
                    }
                    sh2jms.hug_status = 4;
                    return;
                }
                break;
            case 4:
            case 3:
                if (sh2jms.anime_pause & 1) {
                    if (sh2jms.dead != 0) {
                        if (sh2jms.player->battle.target->kind == 515) {
                            sh2jms.dead = 3;
                        } else {
                            sh2jms.dead = 2;
                        }
                    }
                    if ((sh2jms.player->battle.target->kind != 515) || (sh2jms.hug_status == 3)) {
                        sh2jms.hug_status = 0;
                        return;
                    }
                }
                break;
        }
    } else if (sh2jms.anime_pause & 1) {
        PlayerStatusClear();
        if (sh2jms.dead != 0) {
            sh2jms.dead = 2;
        }
        if (sh2jms.dead == 0) {
            if (sh2jms.motion_no == 0) {
                player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
            } else {
                player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
                player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
            }
            player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_DAMAGE);
            player_flg_off(&sh2jms.upper_st_flg, 1 << JMS_ST_U_DAMAGE);
        }
    }
}

void upper_damage(SubCharacter* p) {
}

void lower_to_stand(SubCharacter* p) {
}

void upper_to_stand(SubCharacter* p) {
}

void upper_wall_f(SubCharacter* p) {
    if (sh2jms.anime_pause & 2) {
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        PlayerStatusClear();
    }
}

void lower_event(SubCharacter* p) {

    switch (sh2jms.event_anime) { /* irregular */
        case 104:
        case 107:
            break;
        case 20003: {
            float tgt_pos[4] = {
                -62093.0f,
                0.0f,
                60734.0f,
                0.0f,
            }; // r29+32
            float target; // r29+48
            p->spd     = 0.0f;
            p->spd_org = 0.0f;
            close_to_angle_target(&p->rot.y, shAtan2(tgt_pos[2] - p->pos.z, tgt_pos[0] - p->pos.x), -PI, PI, 8.0f);
            break;
        }
        default:
            p->spd     = 0.0f;
            p->spd_org = 0.0f;
            /* fallthrough */
    }
}

void upper_event(SubCharacter* p) {
    if (!(p->status & (1 << 14))) {
        player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
        player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
        player_flg_off(&sh2jms.lower_st_flg, 1 << JMS_ST_L_EVENT);
        PlayerStatusClear();
        sh2jms.event_anime = 0;
    }
}
