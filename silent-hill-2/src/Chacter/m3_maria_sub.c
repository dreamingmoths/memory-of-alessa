#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"
#include "vec.h"
#include "Collision/cl_main.h"
#include "Chacter/m3_maria_sub.h"
#include "Chacter/m3_sc.h"
#include "Chacter/m3_play.h"
#include "Chacter/sh_character_status.h"
#include "sound/sh_sound.h"

#define dtf dtf_0x011B6F30

// values confirmed
#define BTL_ID_8                8
#define BTL_ID_JAMES_KICK_START 25
#define BTL_ID_JAMES_KICK_END   35

// @todo find the real values for these
#define BTL_ID_ENEMY_TO_MARIA_END   16
#define BTL_ID_ENEMY_TO_MARIA_START   0

// ???
#define CLAMP_MAX(_val, _max) do { (_val) = (_val) > (_max) ? (_val) : (_max); } while (0);
#define CLAMP_MIN(_val, _min) do { (_val) = (_val) > (_min) ? (_min) : (_val); } while (0);

double dpdiv(double, double);
extern void printf(char*, ...);

// exter /* static */ shAttackInfo sh2_attack_list[66]; // size: 0x948, address: 0x0
// extern /* static */ u_char human_skelton[14]; // size: 0xE, address: 0x0
// extern /* static */ u_char enemy_skelton[14]; // size: 0xE, address: 0x0
// extern /* static */ u_char obj_outdoor_skelton[20]; // size: 0x14, address: 0x0
// extern /* static */ u_char obj_anime_skelton[69]; // size: 0x45, address: 0x0
// extern /* static */ u_char obj_stay_skelton[97]; // size: 0x61, address: 0x0
extern /* static */ AnimeInfo pmaria_anim[40];                    // size: 0x1E0, address: 0x397090
extern /* static */ AnimeInfo d_mar_anim[7];                      // size: 0x54, address: 0x0
extern /* static */ MariaAppearPoint maria_apeear_point_list[91]; // size: 0xB60, address: 0x397270
extern /* static */ u_int pmaria_sub_status_flag[9];              // size: 0x24, address: 0x397DD0
extern shMariaWork sh2mar;                                        // size: 0x310, address: 0x11B6B30
extern /* static */ void (*func_list_main[7])(SubCharacter*);     // size: 0x1C, address: 0x34C500
extern /* static */ void (*func_list_sub[9])(SubCharacter*);      // size: 0x24, address: 0x34C520

extern shPlayerWork sh2jms; // size: 0x540, address: 0x3C7EE0

extern float dtf;         // size: 0x4, address: 0x11B6F30
extern int dt;            // size: 0x4, address: 0x11B6F38
extern int dt_0x011B6F38; // size: 0x4, address: 0x11B6F38

extern /* static */ void (*func_list_main_0x0034C500[7])(SubCharacter*); // size: 0x1C, address: 0x34C500
extern /* static */ AnimeInfo pmaria_anim_0x00397090[40];                // size: 0x1E0, address: 0x397090
extern int anime_change_check_1840;
extern int test_1475;

static void MariaBodyAngleCloseToTarget(float target);
static void MariaSpeedDownToStand(SubCharacter* p);
static void MariaPushedAnyoneIsOn(SubCharacter* p);
static int shMariaSoundOn(SubCharacter* this, float vol, int se_name, int arg2);
static void MariaCheckSoundLower(void);
static void MariaCheckSoundUpper(void);
static void mar_sub_flg_check(int status);
static void mar_muteki_set(void);
static void mar_timer_set(int mode);
static void mar_main_stand(void);
static void mar_main_close_to(void);
static void mar_main_alert(void);
static void mar_main_discover(void);
static void mar_main_recover(void);
static void mar_main_boredom(void);
static void mar_main_damaged(void);
static void mar_sub_stand(SubCharacter* p);
static void mar_sub_relax(SubCharacter* p);
static void mar_sub_relax_off(SubCharacter* p);
static void mar_sub_afraid(SubCharacter* p);
static void mar_sub_tired(SubCharacter* p);
static void mar_sub_onestep(SubCharacter* p);
static void mar_sub_walk(SubCharacter* p);
static void mar_sub_run(SubCharacter* p);
static void mar_sub_damage(SubCharacter* p);
static int MariaCheckJamesLook(float* sp, float* ep);
static int JamesCheckMariaLook(float* sp, float* ep);
static int CheckJamesLook1(float* sp, float* ep);
static int CheckJamesLook2(float* sp, float* ep);
static int MariaCheckLook1(float* sp, float* ep);
static int MariaCheckLook2(float* sp, float* ep);
static void MariaSetStraightRoot(SubCharacter* this);
static u_short MariaDamageMotionNo(SubCharacter* this);
static int MariaTouchJamesCheck(void);
static void MariaCheckFootLine(SubCharacter* this);
static void MariaSetSearchArea(SubCharacter* this);
static void MariaSetColumn_SetTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z);
static void MariaSetColumn_CloseToTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z);
static void MariaSetHitColumn(SubCharacter* this);
static void MariaCheckNeckAngle(SubCharacter* this);
static void MariaUpdateStatusInitial(SubCharacter* this);
static void MariaUpdateStatusExecPhase1(void);
static void MariaUpdateStatusExecPhase2(SubCharacter* this);
static void MariaUpdateStatusExec(SubCharacter* this);
static void maria_anim_set_all(AnimeInfo* aip, int comp_type);

void mar_flg_on(u_int* type, u_int status) {
    *type |= status;
}

void mar_flg_off(u_int* type, u_int status) {
    *type &= ~status;
}

int mar_sub_flg_on(u_int status) {
    return sh2mar.sub_st_flg & status;
}

int mar_anime_flg_on(u_int status) {
    return sh2mar.anime_st_flg & status;
}

void mar_main_st_set(int status, shMariaWork* w) {
    w->main_status_prev = w->main_status_now;
    w->main_status_now  = status;
}

void mar_sub_st_set(int status, shMariaWork* w) {
    w->sub_status_prev = w->sub_status_now;
    w->sub_status_now  = status;
}

void mar_sub_flg_set(int status, shMariaWork* w) {
    w->sub_st_flg = pmaria_sub_status_flag[status];
}

static void MariaBodyAngleCloseToTarget(float target) {
    float roty_tmp;
    float mov_angle;

    roty_tmp  = shAngleRegulate(sh2mar.mar_p->rot.y - target);
    mov_angle = dtf * 15.0f * (roty_tmp / TO_RAD(177.1352174054566));
    if (roty_tmp >= 0.0f) {
        if ((roty_tmp - mov_angle) <= 0.0f)
            sh2mar.mar_p->rot.y = target;
        else
            sh2mar.mar_p->rot.y -= mov_angle;
    } else {
        if (roty_tmp - mov_angle >= 0.0f)
            sh2mar.mar_p->rot.y = target;
        else
            sh2mar.mar_p->rot.y -= mov_angle;
    }
    sh2mar.mar_p->rot.y = shAngleRegulate(sh2mar.mar_p->rot.y);
}

static void MariaSpeedDownToStand(SubCharacter* p) {
    float speed;

    switch (sh2mar.sub_status_prev) {
        case MAR_SUB_ST_RUN:
            p->spd -= 10.0f * dtf;

            break;
        default:
            p->spd -= 8.0f * dtf;
            break;
    }

    p->spd = p->spd > 0.0f ? p->spd : 0.0f;
}

static void MariaPushedAnyoneIsOn(SubCharacter* p) {
    float angle;

    if (sh2mar.sub_status_now != MAR_SUB_ST_ONESTEP) {

        if (p->spd) {

            sh2mar.pushed_dir = 0;
        } else {
            if ((p->pos.x == p->b_pos.x) && (p->pos.z == p->b_pos.z)) {
                sh2mar.pushed_dir = 0;
            } else {
                angle = shAtan2(p->pos.z - p->b_pos.z, p->pos.x - p->b_pos.x);
                angle = shAngleRegulate(p->rot.y - angle);
                if (float_abs(angle) < QUARTER_TURN) {
                    sh2mar.pushed_dir = 1;
                } else
                    sh2mar.pushed_dir = -1;
            }
        }
    }
}

static int shMariaSoundOn(SubCharacter* this, float vol /* r29+16 */, int se_name, int arg2) {
    SeCallPos(se_name, vol, &this->pos, 0);
    return 0;
}

static void MariaCheckSoundLower(void) {
    int i;
    u_int material;
    u_short se;
    u_short se_r;
    u_short se_l;
    short frame;
    int pitch;
    MariaSoundInfo se_info[4] = {
        0.0f, -1, -1,
        0.0f, -1, -1,
        0.0f, -1, -1,
        0.0f, -1, -1
    };
    AnimeInfo* a_info;

    s64 temp_a0;
    s8 temp_a0_2;
    s8 i1;
    u8* scp_d;
    void* temp_a2;

    a_info = shCharacterAnimeGetInfo(sh2mar.mar_p);
    frame  = shCharacterAnimeFrameGet(sh2mar.mar_p);
    for (i = 0; i < 2; i++) {
        if (i != 0) {
            if (sh2mar.l_foot.kind == 1) {
                material = sh2mar.l_foot.hobj.wall.pd->material;
            }
        } else if (sh2mar.r_foot.kind == 1) {
            material = sh2mar.r_foot.hobj.wall.pd->material;
        }
        switch (material) {
            case 12:
                se = 19031;
                break;
            case 0:
                se = 19031;
                break;
            case 1:
                se = 19035;
                break;
            case 2:
                se = 19032;
                break;
            case 3:
                se = 19035;
                break;
            case 4:
                se = 19035;
                break;
            case 5:
                se = 19038;
                break;
            case 6:
                se = 19037;
                break;
            case 7:
                se = 19036;
                break;
            case 8:
                se = 19033;
                break;
            case 9:
                se = 19038;
                break;
            case 10:
                se = 19034;
                break;
            case 11:
                se = 19038;
                break;
        }
        if (i != 0) {
            se_l = se;
        } else {
            se_r = se;
        }
    }
    switch ((u8) sh2mar.sub_status_now) {
        case MAR_SUB_ST_ONESTEP:
            if (a_info->name == 48) {
                se_info[0].frame = 6;
                se_info[1].frame = 12;
            } else {
                se_info[0].frame = 22;
                se_info[1].frame = 26;
            }
            se_info[0].vol = 0.3f;
            se_info[1].vol = 0.3f;
            break;
        case MAR_SUB_ST_RELAX:
            if (a_info->name == 16) {
                se_info[0].frame = 18;
                se_info[0].vol   = 0.3f;
            }
            break;
        case MAR_SUB_ST_AFRAID:
            se_info[0].frame = 10;
            se_info[1].frame = 16;
            se_info[2].frame = 22;
            se_info[3].frame = 26;
            se_info[0].vol   = 0.3f;
            se_info[1].vol   = 0.3f;
            se_info[2].vol   = 0.3f;
            se_info[3].vol   = 0.3f;
            break;
        case MAR_SUB_ST_WALK:
        case MAR_SUB_ST_RUN:
            se_info[0].frame = 5;
            se_info[1].frame = 17;
            se_info[0].vol   = 0.6f;
            se_info[1].vol   = 0.6f;
            break;
        case MAR_SUB_ST_DAMAGE:
            switch (a_info->name) {
                case 22:
                    se_info[0].frame = 2;
                    se_info[1].frame = 4;
                    se_info[2].frame = 9;
                    break;
                case 23:
                    se_info[0].frame = 4;
                    se_info[1].frame = 9;
                    se_info[2].frame = 13;
                    break;
                case 24:
                    se_info[0].frame = 3;
                    se_info[1].frame = 6;
                    break;
                case 25:
                    se_info[0].frame = 3;
                    se_info[1].frame = 5;
                    se_info[2].frame = 9;
                    break;
                case 26:
                    se_info[0].frame = 5;
                    se_info[1].frame = 8;
                    break;
                case 27:
                    se_info[0].frame = 4;
                    se_info[1].frame = 8;
                    break;
                case 28:
                    se_info[0].frame = 5;
                    se_info[1].frame = 8;
                    break;
                case 29:
                    se_info[0].frame = 5;
                    se_info[1].frame = 9;
                    break;
                case 20:
                    se_info[0].frame = 6;
                    se_info[1].frame = 10;
                    break;
                case 21:
                    se_info[0].frame = 4;
                    se_info[1].frame = 12;
                    break;
                case 30:
                    se_info[0].frame = 6;
                    se_info[1].frame = 12;
                    break;
                case 31:
                    se_info[0].frame = 4;
                    se_info[1].frame = 5;
                    se_info[2].frame = 13;
                    break;
                case 34:
                    se_info[0].frame = 2;
                    se_info[1].frame = 6;
                    break;
                case 35:
                    se_info[0].frame = 7;
                    se_info[1].frame = 13;
                    break;
                case 39:
                    se_info[0].frame = 3;
                    se_info[1].frame = 11;
                    break;
                case 40:
                    se_info[0].frame = 2;
                    se_info[1].frame = 11;
                    break;
                case 47:
                    se_info[0].frame = 10;
                    break;
            }
            se_info[0].vol = 0.6f;
            se_info[1].vol = 0.6f;
            se_info[2].vol = 0.6f;
            break;
    }
    switch ((u8) sh2mar.sub_status_now) {
        case MAR_SUB_ST_ONESTEP:
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            break;
        case MAR_SUB_ST_RELAX:
            if (a_info->name == 16) {
                se_info[0].domain = 2;
            }
            break;
        case MAR_SUB_ST_AFRAID:
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            se_info[2].domain = 1;
            se_info[3].domain = 2;
            break;
        case MAR_SUB_ST_WALK:
        case MAR_SUB_ST_RUN:
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            break;
        case MAR_SUB_ST_DAMAGE:
            se_info[0].domain = 1;
            se_info[1].domain = 2;
            se_info[2].domain = 1;
            break;
    }
    for (i = 0; i < 4; i++) {
        if (se_info[i].frame >= 0) {
            if (frame >= 0) {
                if (frame >= se_info[i].frame) {
                    if (sh2mar.se_foot[i] == 0) {
                        switch (se_info[i].domain) {
                            case 1:
                                shMariaSoundOn(sh2mar.mar_p, se_info[i].vol, se_r, 0);
                                break;
                            case 2:
                                shMariaSoundOn(sh2mar.mar_p, se_info[i].vol, se_l, 0);
                                break;
                        }
                    }
                    sh2mar.se_foot[i] = 1;
                } else {
                    sh2mar.se_foot[i] = 0;
                }
            }
        };
    }
}

static void MariaCheckSoundUpper(void) {
    AnimeInfo* anim_p = shCharacterAnimeGetInfo(sh2mar.mar_p);
    int i;
    u_short se;
    short frame;
    MariaSoundInfo se_info[4] = {
        0.0f, -1, -1,
        0.0f, -1, -1,
        0.0f, -1, -1,
        0.0f, -1, -1
    };

    frame = shCharacterAnimeFrameGet(sh2mar.mar_p);

    switch ((u8) sh2mar.sub_status_now) {
        case MAR_SUB_ST_TIRED:
            se = 19039;
            break;
        case MAR_SUB_ST_DAMAGE:
            if (sh2mar.dead != 0) {
                se = 19041;
            } else {
                se = 19040;
            }
            break;
    }
    switch ((u8) sh2mar.sub_status_now) {
        case MAR_SUB_ST_TIRED:
            se_info[0].frame = 1;
            se_info[0].vol   = 0.5f;
            break;
        case MAR_SUB_ST_DAMAGE:
            if (sh2mar.dead != 0) {
                se_info[0].frame = 1;
                se_info[0].vol   = 1.0f;
            } else {
                se_info[0].frame = 1;
                se_info[0].vol   = 0.7f;
            }
            break;
    }

    for (i = 0; i < 4; i++) {
        if (se_info[i].frame >= 0 && frame >= 0) {
            if (frame >= se_info[i].frame) {
                if (sh2mar.se_upper[i] == 0) {
                    shMariaSoundOn(sh2mar.mar_p, se_info[i].vol, se, 0);
                }
                sh2mar.se_upper[i] = 1;
            } else {
                sh2mar.se_upper[i] = 0;
            }
        }
    }
}

static void mar_sub_flg_check(int status) {
    if ((sh2mar.anime_st_flg == 0) && ((u8) sh2mar.sub_status_now != status)) {
        mar_sub_st_set(status, &sh2mar);
        mar_sub_flg_set(status, &sh2mar);
    }
}

static void mar_muteki_set(void) {
    if (sh2mar.sub_status_prev == 8) {
        sh2mar.muteki_time     = 2.0f;
        sh2mar.no_damage       = 0;
        sh2mar.sub_status_prev = -1;
    }
}

static void mar_timer_set(int mode) {
    switch (mode) {
        case 0:
            sh2mar.stand_time += dtf;
            sh2mar.move_time   = 0.0f;
            sh2mar.afraid_time = 0.0f;
            sh2mar.relax_time  = 0.0f;
            return;
        case 1:
            sh2mar.stand_time = 0.0f;
            sh2mar.move_time += dtf;
            sh2mar.afraid_time = 0.0f;
            sh2mar.relax_time  = 0.0f;
            return;
        case 2:
            sh2mar.stand_time += dtf;
            sh2mar.move_time = 0.0f;
            sh2mar.afraid_time += dtf;
            sh2mar.relax_time = 0.0f;
            return;
        case 3:
            sh2mar.stand_time += dtf;
            sh2mar.move_time   = 0.0f;
            sh2mar.afraid_time = 0.0f;
            sh2mar.relax_time += dtf;
            return;
    }
}

static void mar_main_stand(void) {
    shMariaWork* w;
    if (mar_sub_flg_on(4U) != 0) {
        mar_sub_flg_check(2);
        return;
    }
    if (mar_sub_flg_on(32) != 0) {
        mar_sub_flg_check(5);
        return;
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_main_close_to(void) {
    shMariaWork* w = &sh2mar;
    if (mar_sub_flg_on(4U) != 0) {
        mar_sub_flg_check(2);
        return;
    }
    if ((mar_sub_flg_on(128) != 0) && !(w->dist_to_jms < 2000.0f)) {
        mar_sub_flg_check(7);
        return;
    }
    if ((mar_sub_flg_on(64) != 0) && (!(w->dist_to_jms < 1000.0f) || (sh2mar.look_jms == 0))) {
        mar_sub_flg_check(6);
        return;
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_main_alert(void) {
    shMariaWork* w;
    if (mar_sub_flg_on(8U) != 0) {
        mar_sub_flg_check(3);
        return;
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_main_discover(void) {
    shMariaWork* w;
}

static void mar_main_recover(void) {
    shMariaWork* w;
    if (mar_sub_flg_on(16) != 0) {
        mar_sub_flg_check(4);
        return;
    }
    if (mar_sub_flg_on(32) != 0) {
        mar_sub_flg_check(5);
        return;
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_main_boredom(void) {
    shMariaWork* w;
    if (mar_sub_flg_on(2U) != 0) {
        mar_sub_flg_check(1);
        return;
    }
    if (mar_sub_flg_on(32) != 0) {
        mar_sub_flg_check(5);
        return;
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_main_damaged(void) {
    shMariaWork* w;
    if (mar_sub_flg_on(256) != 0) {
        mar_sub_flg_check(8);
    }
    if (mar_sub_flg_on(1U) != 0) {
        mar_sub_flg_check(0);
        mar_muteki_set();
    }
}

static void mar_sub_stand(SubCharacter* p) {
    mar_timer_set(0);
    sh2mar.tired -= dt_0x011B6F38;
    MariaSpeedDownToStand(p);
    if (sh2mar.pushed_dir != 0) {
        mar_flg_on(&sh2mar.sub_st_flg, 32);
    }
}

static void mar_sub_relax(SubCharacter* p) {
    mar_timer_set(3);
    sh2mar.tired -= dt_0x011B6F38;
    MariaSpeedDownToStand(p);
    switch (sh2mar.relax_flag) {
        case 0:
            if (sh2mar.anime_pause & 1) {
                sh2mar.relax_flag = 1;
                mar_flg_on(&sh2mar.anime_st_flg, 64);
            }
            break;
        case 1:
            if (!(sh2mar.relax_time < 10.0f)) {
                sh2mar.relax_flag = 2;
                mar_flg_on(&sh2mar.anime_st_flg, 64);
            }
            break;
        case 2:
            if (sh2mar.anime_pause & 1) {
                sh2mar.relax_time = 0.0f;
                sh2mar.relax_flag = 1;
                mar_flg_on(&sh2mar.anime_st_flg, 64);
            }
            break;
    }
    if (sh2mar.main_status_now != 5) {
        sh2mar.relax_flag = 0;
        mar_flg_on(&sh2mar.sub_st_flg, 4U);
    }
    if (sh2mar.pushed_dir != 0) {
        mar_flg_on(&sh2mar.sub_st_flg, 32);
    }
}

static void mar_sub_relax_off(SubCharacter* p) {
    mar_timer_set(0);
    MariaSpeedDownToStand(p);
    if (sh2mar.anime_pause & 1) {
        mar_flg_off(&sh2mar.sub_st_flg, 4U);
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
    }
    if (sh2mar.pushed_dir != 0) {
        mar_flg_on(&sh2mar.sub_st_flg, 32);
    }
}

static void mar_sub_afraid(SubCharacter* p) {
    short frame = shCharacterAnimeFrameGet(p);
    mar_timer_set(2);
    sh2mar.tired -= dt_0x011B6F38;
    MariaSpeedDownToStand(p);
    if (sh2mar.anime_pause & 1) {
        mar_flg_off(&sh2mar.sub_st_flg, 8U);
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
        sh2mar.stand_time = 0.0f;
    }
}

static void mar_sub_tired(SubCharacter* p) {
    mar_timer_set(0);
    sh2mar.tired -= dt_0x011B6F38;
    MariaSpeedDownToStand(p);
    if (sh2mar.tired < ((s32) sh2mar.tired_max >> 1)) {
        mar_flg_off(&sh2mar.sub_st_flg, 16);
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
    }
    if (sh2mar.pushed_dir != 0) {
        mar_flg_on(&sh2mar.sub_st_flg, 32);
    }
}

static void mar_sub_onestep(SubCharacter* p) {
    mar_timer_set(1);
    sh2mar.tired -= dt_0x011B6F38;
    MariaSpeedDownToStand(p);
    if (sh2mar.anime_pause & 1) {
        mar_flg_off(&sh2mar.sub_st_flg, 32);
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
        sh2mar.stand_time = 0.0f;
    }
}

static void mar_sub_walk(SubCharacter* p) {

    mar_timer_set(1);

    if (p->spd > 1.4f) {

        p->spd -= 4.0f * dtf;
        CLAMP_MAX(p->spd, 1.4f);
    } else {

        p->spd += (2.0f * dtf);
        CLAMP_MIN(p->spd, 1.4f);
    }
    if (sh2mar.look_jms != 0) {
        sh2mar.to_target = shAtan2(sh2jms.player->pos.z - p->pos.z, sh2jms.player->pos.x - p->pos.x);
    } else {
        sh2mar.to_target = shAtan2(sh2mar.tgt_pos[0][2] - p->pos.z, sh2mar.tgt_pos[0][0] - p->pos.x);
    }
    MariaBodyAngleCloseToTarget(sh2mar.to_target);
    if (sh2mar.move_time >= 1.06f) {
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
    }
}

static void mar_sub_run(SubCharacter* p) {
    f32 var_f1;

    mar_timer_set(1);
    sh2mar.tired += dt_0x011B6F38;
    p->spd += (3.0f * dtf);
    p->spd = p->spd > 3.5f ? 3.5f : p->spd;
    if (sh2mar.look_jms != 0) {
        sh2mar.to_target = shAtan2(sh2jms.player->pos.z - p->pos.z, sh2jms.player->pos.x - p->pos.x);
    } else {
        sh2mar.to_target = shAtan2(sh2mar.tgt_pos[0][2] - p->pos.z, sh2mar.tgt_pos[0][0] - p->pos.x);
    }
    MariaBodyAngleCloseToTarget(sh2mar.to_target);
    if (!(sh2mar.move_time < 0.91f)) {
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
    }
}

static void mar_sub_damage(SubCharacter* p) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo(p);
    float damage_angle;
    short cur_frame;

    mar_timer_set(0);
    MariaSpeedDownToStand(p);
    cur_frame = shCharacterAnimeFrameGet(p);
    if (p->battle.id != 0) {
        p->spd_roty = shAngleRegulate(shAtan2(p->battle.vec.z, p->battle.vec.x) - p->rot.y);
    } else if (a_info->name == 20) {
        p->spd_roty = TO_RAD(180);
    } else {
        p->spd_roty = 0.0f;
    }
    if (mar_anime_flg_on(2U) == 0) {
        switch (a_info->name) {
            case 20:
            case 22:
            case 26:
            case 34:
                if (2 < cur_frame && (cur_frame < 7)) {
                    p->spd = 1.0f;
                } else {
                    p->spd = 0.2f;
                }
                break;
            case 21:
            case 23:
            case 27:
            case 35:
                if (cur_frame >= 6) {
                    p->spd = 0.3f;
                } else if (cur_frame >= 3) {
                    p->spd = 1.2f;
                }
                break;
            case 24:
            case 28:
            case 32:
            case 36:
            case 38:
            case 41:
            case 46:
                if (2 < cur_frame && (cur_frame < 15)) {
                    p->spd = 0.05f * (f32) cur_frame;
                }
                break;
            case 25:
            case 29:
            case 33:
            case 37:
            case 42:
            case 45:
                if (2 < cur_frame && (cur_frame < 15)) {
                    p->spd = 0.05f * (f32) cur_frame;
                }
                break;
        }
    }
    if (sh2mar.anime_pause & 1) {
        MariaStatusClear();
        if (sh2mar.dead != 0) {
            sh2jms.dead = 2;
            return;
        }
        mar_flg_off(&sh2mar.sub_st_flg, 256);
        mar_flg_on(&sh2mar.sub_st_flg, 1U);
    }
}

static int MariaCheckJamesLook(float* sp, float* ep) {
    CL_VHIT_RESULT result;
    clCheckHitEyes(&result, (u_int) sh2mar.mar_p, sp, ep, 0);
    if ((result.kind == 3) && (result.hobj.chara.sc == sh2jms.player)) {
        return true;
    }
    return false;
}

static int JamesCheckMariaLook(float* sp, float* ep) {
    CL_VHIT_RESULT result;
    clCheckHitEyes(&result, (u_int) sh2jms.player, sp, ep, 0);
    if ((result.kind == 3) && (result.hobj.chara.sc == sh2mar.mar_p)) {
        return true;
    }
    return false;
}

static int CheckJamesLook1(float* sp, float* ep) {
    CL_VHIT_RESULT result;
    clCheckHitEyes(&result, 0, sp, ep, 0);
    if ((result.kind == 3) && (result.hobj.chara.sc == sh2jms.player)) {
        return true;
    }
    return false;
}

static int CheckJamesLook2(float* sp, float* ep) {
    CL_VHIT_RESULT result;
    clCheckHitEyes(&result, (u_int) sh2jms.player, sp, ep, 0);
    return result.kind == 0;
}

#line 1225
static int MariaCheckLook1(float* sp, float* ep) {
    CL_VHIT_RESULT result;

    clCheckHitEyes(&result, (u_int) sh2mar.mar_p, sp, ep, 0);

    if (result.kind == 0 || (result.kind == 3 && result.hobj.chara.sc == sh2jms.player))

        return true;

    return false;
}
static int MariaCheckLook2(float* sp, float* ep) {
    CL_VHIT_RESULT result;
    clCheckHitEyes(&result, (u_int) sh2jms.player, sp, ep, 0);
    if ((result.kind == 3) && (result.hobj.chara.sc == sh2mar.mar_p)) {
        return true;
    }
    return false;
}

static void MariaSetStraightRoot(SubCharacter* this) {
    int i;
    int j;
    float sp0[4];
    float sp1[4];
    float ep0[4];
    float ep1[4];

    u8 var_s0;

    sp0[0] = sh2mar.mar_p->pos.x;
    sp0[2] = sh2mar.mar_p->pos.z;
    sp0[1] = sh2mar.mar_p->pos.y - 100.0f;
    ep0[0] = sh2jms.player->pos.x;
    ep0[2] = sh2jms.player->pos.z;
    ep0[1] = sh2jms.player->pos.y - 100.0f;
    if (sh2mar.tgt_pointer == 0) {
        if (!(sh2mar.look_jms = ((MariaCheckJamesLook(&sp0[0], &ep0[0]) != 0) && (JamesCheckMariaLook(&ep0[0], &sp0[0]) != 0)))) {
            sh2mar.tgt_pointer++;
        }
    } else {
        volatile_vec_copy(&sp1, sh2mar.tgt_pos[sh2mar.tgt_pointer - 1]);
        if ((CheckJamesLook1(&sp1[0], &ep0[0]) == 0) || (CheckJamesLook2(&ep0[0], &sp1[0]) == 0)) {
            sh2mar.tgt_pointer += 1;
        }
    }
    if (sh2mar.tgt_pointer == 5) {
        sh2mar.tgt_pointer -= 1;
        volatile_vec_copy(&sh2mar.mar_p->pos, &sh2mar.tgt_pos[0]);
    }
    volatile_vec_copy(sh2mar.tgt_pos[sh2mar.tgt_pointer], ep0);
    if (sh2mar.tgt_pointer > 0) {
        for (i = 0; i <= 0; i++) {
            volatile_vec_copy(ep1, sh2mar.tgt_pos[i + 1]);
            if ((MariaCheckLook1(&sp0[0], &ep1[0]) != 0) && (MariaCheckLook2(&ep1[0], &sp0[0]) != 0)) {
                for (j = 0; j < sh2mar.tgt_pointer; j++) {
                    volatile_vec_copy(sh2mar.tgt_pos[j], sh2mar.tgt_pos[j + 1]);
                }
                sh2mar.tgt_pointer--;
            }
        }
    }
    if (sh2mar.tgt_pointer < 0)
        ASSERT_ON_LINE(sh2mar.tgt_pointer >= 0, 1371);
}

// @note: our definition of NULL differs?
#undef NULL
#define NULL (0ULL)
#line 1466
static u_short MariaDamageMotionNo(SubCharacter* this) {
    static int test; // @ 18575144
    u_short damage_motion_james_body_index[2] = {20, 21};

    u_short damage_motion_james_weapon_index[24][2][2] = {
        28, 29, 28, 29,
        28, 29, 28, 29,
        0,  0,  0,  0,
        28, 29, 28, 29,
        0,  0,  0,  0,
        28, 29, 28, 29,
        0,  0,  0,  0,
        22, 23, 22, 23,
        22, 23, 22, 23,
        0,  0,  0,  0,
        0,  0,  0,  0,
        39, 40, 45, 45,
        39, 40, 45, 45,
        34, 35, 36, 37,
        39, 40, 45, 45,
        39, 40, 45, 45,
        34, 35, 36, 37,
        30, 31, 32, 33,
        38, 38, 38, 38,
        38, 38, 38, 38,
        38, 38, 38, 38,
        38, 38, 38, 38,
        39, 40, 45, 45,
        43, 44, 45, 46
    };

    u_short damage_motion_enemy_index[16][2][2] = {
        22, 23, 24, 25,
        22, 23, 24, 25,
        26, 27, 28, 29,
        26, 27, 28, 29,
        34, 35, 36, 37,
        30, 31, 32, 33,
        34, 35, 36, 37,
        30, 31, 32, 33,
        38, 38, 38, 38,
        38, 38, 38, 38,
        43, 44, 45, 46,
        0,  0,  0,  0,
        0,  0,  0,  0,
        39, 40, 41, 42,
        39, 40, 41, 42,
        47, 47, 24, 25
    };
    sceVu0FVECTOR direction;
    float roty;
    float roty2;
    u_short result;
    int kind;
    int dir;

    if (this->battle.id == 0) {
        roty2 = shAngleRegulate(sh2jms.player->rot.y + sh2jms.player->spd_roty);

    } else {
        vec_normalize(&this->battle.vec, direction);
        roty2 = shAtan2(direction[2], direction[0]);
    }

    roty = roty2 - this->rot.y;
    roty = roty > PI ? roty : (roty < -PI ? roty : roty);
    if (roty >= -QUARTER_TURN && roty < QUARTER_TURN)
        dir = 1;
    else
        dir = 0;

    if (this->battle.id == 0) {
        return damage_motion_james_body_index[dir];
    }
    if (this->battle.id < 35) {
        kind = this->battle.id - 1;

        ASSERT_ON_LINE(damage_motion_james_weapon_index[kind][sh2mar.dead][dir] != NULL, 1705);

        return damage_motion_james_weapon_index[kind][sh2mar.dead][dir];
    }
    kind = this->battle.id - 36;

    test_1475 = kind;
    ASSERT_ON_LINE(kind >= 0 && kind < BTL_ID_ENEMY_TO_MARIA_END - BTL_ID_ENEMY_TO_MARIA_START, 1714);
    ASSERT_ON_LINE(dir >= 0 && dir < 2, 1713);
    ASSERT_ON_LINE(damage_motion_enemy_index[kind][sh2mar.dead][dir] != NULL, 2263);
    return damage_motion_enemy_index[kind][sh2mar.dead][dir];
}

#undef NULL
#define NULL 0

static void MariaCheckFootLine(SubCharacter* this) {
    sceVu0FMATRIX mat;
    sceVu0FVECTOR sp;
    sceVu0FVECTOR ep;

    GetMariaPartsWorldMatrix(mat, 8U);
    volatile_vec_copy(sp, mat[3]);
    volatile_vec_copy(ep, sp);
    sp[1] -= 250.0f;
    ep[1] += 750.0f;
    clCheckHitEyesOnlyFloor(&sh2mar.r_foot, (int) this, &sp, &ep);
    if (sh2jms.r_foot.kind == 1) {
        vec_normalize(sh2mar.r_foot.hobj.chara.cp, sh2mar.r_foot.hobj.chara.cp);
    }
    GetMariaPartsWorldMatrix(mat, 7U);
    volatile_vec_copy(sp, mat[3]);
    volatile_vec_copy(ep, sp);
    sp[1] -= 250.0f;
    ep[1] += 750.0f;
    clCheckHitEyesOnlyFloor(&sh2mar.l_foot, (int) this, &sp, &ep);
    if (sh2mar.l_foot.kind == 1) {
        vec_normalize(sh2mar.l_foot.hobj.chara.cp, sh2mar.l_foot.hobj.chara.cp);
    }
}

static void MariaSetSearchArea(SubCharacter* this) {
    if (sh2gfw_Get_NightOrDay() == 0) {
        shBattleSetLookArea(this, 4.0f, 4.0f);
    } else {
        shBattleSetLookArea(this, 1.2f, 1.2f);
    }
    shBattleSetFeelArea(this, 0.2f, 2.0f);
}

static void MariaSetColumn_SetTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z) {
    AnimeInfo* a_info = shCharacterAnimeGetInfo(sh2mar.mar_p);

    atk->p[0][3] = 1.0f;
    mov->p[0][3] = 1.0f;
    atk->p[0][0] = 0.0f;
    mov->p[1][0] = 0.0f;
    atk->p[0][2] = 0.0f;
    mov->p[1][2] = 0.0f;

    mov->p[0][0] = atk->p[0][0] = sh2mar.mar_p->pos.x;

    mov->p[0][1] = atk->p[0][1] = -50.0f + sh2mar.mar_p->pos.y;

    mov->p[0][2] = atk->p[0][2] = sh2mar.mar_p->pos.z;

    mov->p[1][1] = atk->p[1][1] = -800.0f + sh2mar.mar_p->pos.y;
    *mov_z                      = 0.0f;
    *atk_z                      = 0.0f;
    switch ((u8) sh2mar.sub_status_now) {
        case MAR_SUB_ST_AFRAID:
            break;
        case MAR_SUB_ST_DAMAGE:
            if (a_info->name != 21) {
                int x = 0; // @hack
            } else {
                *mov_z = 100.0f;
            }
            break;
    }
    if (clPermitColumnExpansion() == 0) {
        atk->p[1][3] = 150.0f;
        mov->p[1][3] = 150.0f;
    }
}

static void MariaSetColumn_CloseToTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z) {
    sh2mar.column_mov.p[0][0] = sh2mar.column_atk.p[0][0] = sh2mar.mar_p->pos.x;

    sh2mar.column_mov.p[0][1] = sh2mar.column_atk.p[0][1] = -50.0f + sh2mar.mar_p->pos.y;

    sh2mar.column_mov.p[0][2] = sh2mar.column_atk.p[0][2] = sh2mar.mar_p->pos.z;

    sh2mar.column_mov.p[0][3] = sh2mar.column_atk.p[0][3] = 1.0f;

    sh2mar.column_mov.p[1][0] = sh2mar.column_atk.p[1][0] = 0.0f;

    sh2mar.column_mov.p[1][1] = sh2mar.column_atk.p[1][1] = -850.0f + sh2mar.mar_p->pos.y;

    sh2mar.column_atk.p[1][2] = 0.0f;
    sh2mar.column_mov.p[1][2] = 0.0f;
}

void MariaSetHeightDummy(void) {
    /* empty */
}

void MariaSetHeight(SubCharacter* this) {
    sceVu0FVECTOR sp;
    sceVu0FVECTOR ep;

    volatile_vec_copy(sp, &this->pos);
    volatile_vec_copy(ep, sp);
    sp[1] -= 250.0f;
    ep[1] += 1500.0f;
    clCheckHitEyesOnlyFloor(&sh2mar.ft_floor, (int) this, &sp, &ep);
    if (sh2jms.ft_floor.kind == 1) {
        this->grnd_height = sh2mar.ft_floor.hobj.wall.cp[1];
        this->grnd_normal = sh2mar.ft_floor.hobj.wall.nl;
    }
    sh2mar.dist_pos.y = this->grnd_height;
    if (sh2mar.dist_pos.y <= this->pos.y) {
        this->spd_y = 0.0f;
        this->pos.y = sh2mar.dist_pos.y;
        return;
    }

    this->spd_y += (9.8f * shGetDT()) * shGetDT();
    if (!(sh2jms.dist_pos.y <= (100.0f + this->pos.y))) {
        SCFreefallSwitch(this, 1);
    } else {
        this->spd_y = 0.0f;
        this->pos.y = sh2jms.dist_pos.y;
    }
    this->spd_y = 0.0f;
    this->pos.y = sh2mar.dist_pos.y;
}

static void MariaSetHitColumn(SubCharacter* this) {
    CL_HITPOLY_COLUMN col_mov;
    CL_HITPOLY_COLUMN col_atk;
    float mov_z;
    float atk_z;
    sceVu0FMATRIX mat;

    MariaSetHeight(this);
    MariaSetColumn_SetTarget(&col_mov, &col_atk, &mov_z, &atk_z);
    MariaSetColumn_CloseToTarget(&col_mov, &col_atk, &mov_z, &atk_z);
    if (sh2mar.l_foot.kind == 1) {
        clSetCharaHitColumn(&sh2mar.column_mov, &sh2mar.column_atk, this, MariaSetHeightDummy);
    } else {
        clSetCharaHitColumn(&sh2mar.column_mov, &sh2mar.column_atk, this, NULL);
    }
    this->center_y = 0.5f * (sh2mar.column_mov.p[0][1] + sh2mar.column_mov.p[1][1]);
    GetMariaPartsWorldMatrix(mat, 9U);
    this->eye_y = mat[3][1];
}

static void MariaCheckNeckAngle(SubCharacter* this) {
    SubCharacterDisp* this_d = (SubCharacterDisp*) this;
    float pos[4];
    float tmp[4];

    switch (sh2mar.sub_status_now) {
        case MAR_SUB_ST_TIRED:
        case MAR_SUB_ST_AFRAID:
        case MAR_SUB_ST_DAMAGE:

            sh2mar.tgt_neck_angle.y = 0.0f;
            sh2mar.tgt_neck_angle.x = 0.0f;
            break;

        default:
            if (sh2mar.look_tgt != NULL) {

                volatile_vec_copy(pos, &sh2mar.look_tgt->pos);
                pos[1] = sh2mar.look_tgt->eye_y;

                tmp[0] = pos[0] - this->pos.x;
                tmp[1] = pos[1] - this->eye_y;
                tmp[2] = pos[2] - this->pos.z;

                sh2mar.tgt_neck_angle.y = shAtan2(tmp[2], tmp[0]) - this->rot.y;
                sh2mar.tgt_neck_angle.x = -shAtan2(vec_length(tmp), tmp[1]);

                REFLEX_ANGLE(sh2mar.tgt_neck_angle.x, sh2mar.tgt_neck_angle.x);
                REFLEX_ANGLE(sh2mar.tgt_neck_angle.y, sh2mar.tgt_neck_angle.y);
            } else {
                sh2mar.tgt_neck_angle.y = 0.0f;
                sh2mar.tgt_neck_angle.x = 0.0f;
            }
            break;
    }

    close_to_angle_target(&this_d->anime.rot_neck.x, sh2mar.tgt_neck_angle.x, -0.4f, 0.5f, 10.0f);

    close_to_angle_target(&this_d->anime.rot_neck.y, sh2mar.tgt_neck_angle.y, -0.8f, 0.8f, 10.0f);
}

static void MariaUpdateStatusInitial(SubCharacter* this) {
    sh2mar.enemy_atk_area = shBattleCheckTargetChara(sh2mar.mar_p);
    sh2mar.enemy_around   = sh2jms.enemy_around;
    sh2mar.look_tgt       = (SubCharacter*) shBattleGetTargetChara(sh2mar.mar_p, 0);
    sh2mar.dist_to_jms    = vec3_dist(&sh2jms.player->pos, &this->pos);
    if ((u8) sh2mar.sub_status_now == 7) {
        sh2mar.tired += dt_0x011B6F38;
        sh2mar.tired = (sh2mar.tired < 0) ? 0 : ((sh2mar.tired_max < sh2mar.tired) ? sh2mar.tired_max : sh2mar.tired);
    }
    if (sh2mar.muteki_time) {
        sh2mar.muteki_time -= dtf;
        if (sh2mar.muteki_time < 0.0f) {
            sh2mar.muteki_time = 0.0f;
        }
    }
}

static void MariaUpdateStatusExecPhase1(void) {
    if ((sh2mar.no_damage == 0) && (sh2mar.random_status == 0)) {
        if ((s32) sh2mar.active_type >= 2) {
            if (!(sh2mar.dist_to_jms <= 1000.0f) || (sh2mar.look_jms == 0)) {
                mar_main_st_set(1, &sh2mar);
                return;
            }
            if (sh2mar.tired >= 400) {
                mar_main_st_set(4, &sh2mar);
                return;
            }
            if ((sh2mar.enemy_around != 0) && !(sh2mar.stand_time < 6.0f)) {
                mar_main_st_set(2, &sh2mar);
                return;
            }
            if (sh2mar.look_obj != NULL) {
                mar_main_st_set(3, &sh2mar);
                return;
            }
        }

        if (!(sh2mar.stand_time < 6.0f) || (sh2jms.lower_now == 1)) {
            mar_main_st_set(5, &sh2mar);
            return;
        }
        mar_main_st_set(0, &sh2mar);
    }
}

static void MariaUpdateStatusExecPhase2(SubCharacter* this) {
    void (*mar_main_func)(SubCharacter*) = func_list_main_0x0034C500[(u_char) sh2mar.main_status_now];
    mar_main_func(this);
}

static void MariaUpdateStatusExec(SubCharacter* this) {
    MariaUpdateStatusExecPhase1();
    MariaUpdateStatusExecPhase2(this);
}

void GetMariaPartsWorldMatrix(float (*mat)[4], u_int parts_name) {
    int i1;
    shSkelton* sk = sh2mar.mar_p->sk_top;

    for (i1 = 0; i1 < parts_name; i1++) {
        sk = sk->next;
    }
    sceVu0MulMatrix(mat, sh2mar.mar_p->mat, sk->src_m.d);
}

void MariaCheckDamage(SubCharacter* this) {
    MariaPushedAnyoneIsOn(this);
    volatile_vec_copy(&this->b_pos, &this->pos);
    volatile_vec_copy(&this->b_rot, &this->rot);
    shBattleGetResult(this);

    if (sh2mar.hp_recover) {
        this->battle.hp += sh2mar.hp_recover;
        sh2mar.hp_recover = 0.0f;
        this->battle.hp   = this->battle.hp < 0.0f ? 0.0f : this->battle.hp > this->battle.hp_max ? this->battle.hp_max
                                                                                                  : this->battle.hp;
    }
    if ((this->battle.damage || MariaTouchJamesCheck()) && !sh2mar.no_damage) {
        if ((this->battle.id >= BTL_ID_JAMES_KICK_START) && (this->battle.id <= BTL_ID_JAMES_KICK_END)) {
            this->battle.damage = 0.0f;
        } else {
            sh2mar.no_damage  = 1;
            sh2mar.relax_flag = 0;
            mar_main_st_set(6, &sh2mar);
            mar_flg_on(&sh2mar.sub_st_flg, 256);
            ASSERT_ON_LINE(this->battle.id < BTL_ID_JAMES_KICK_START || this->battle.id > BTL_ID_JAMES_KICK_END, 2263);

            if (this->battle.damage) {
                if ((this->battle.id >= BTL_ID_8) && (this->battle.id < BTL_ID_JAMES_KICK_START)) {
                    this->battle.damage *= 0.1f;
                }
                this->battle.hp -= this->battle.damage;
                GameMariaDamagedCountUp(this->battle.id, this->battle.damage); // @bug: they forgor to #include this

                switch (this->battle.id) {
                    case 1:
                    case 2:
                    case 4:
                    case 6:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 44:
                    case 45:
                        sh2mar.dead = 1;
                        break;
                    default:
                        break;
                }
                if (this->battle.hp <= 0.0f) {
                    sh2mar.dead = 1;
                }
            }
            sh2mar.damage_no    = MariaDamageMotionNo(this);
            this->battle.damage = 0.0f;
        }
    }

    if (this->battle.damage) {
        this->battle.hp -= this->battle.damage;
    }
    this->battle.hp += dtf;
    this->battle.hp = this->battle.hp < 0.0f ? 0.0f : this->battle.hp > this->battle.hp_max ? this->battle.hp_max
                                                                                            : this->battle.hp;

    this->battle.damage  = 0.0f;
    this->battle.shock   = 0.0f;
    this->battle.hp_rate = (100.0f * this->battle.hp) / this->battle.hp_max;
    sh2mar.tired         = sh2mar.tired < 0 ? 0 : (sh2mar.tired_max < sh2mar.tired) ? sh2mar.tired_max
                                                                                    : sh2mar.tired;
}

void MariaCheckSetParameterPhase1(SubCharacter* this) {
    dt_0x011B6F38 = shGetDF();
    dtf           = shGetDT();
    if (sh2mar.active_type >= 2) {
        MariaSetStraightRoot(this);
    }
    MariaSetSearchArea(this);
}

void MariaCheckSetParameterPhase2(SubCharacter* this) {
    MariaCheckFootLine(this);
    MariaSetHitColumn(this);
    MariaCheckNeckAngle(this);
}

void MariaCheckControl(SubCharacter* this) {
    MariaUpdateStatusInitial(this);
    MariaUpdateStatusExec(this);
}

static void maria_anim_set_all(AnimeInfo* aip, int comp_type) {
    shCharacterAnimeSet(sh2mar.mar_p, 0, comp_type, aip, (int) shCharacterGetAnimeAdrForPlay(sh2mar.mar_p));
}

void MariaCheckAnime(void) {
    int anime_change_check; // @ 18575136
    shMariaWork* w          = &sh2mar;
    SubCharacterDisp* scp_d = (SubCharacterDisp*) sh2mar.mar_p;
    AnimeInfo* aip;
    int anime;

    if ((mar_anime_flg_on(2U) == 0) && (((u8) w->sub_status_now != anime_change_check_1840) || (mar_anime_flg_on(64) != 0))) {
        switch ((u8) w->sub_status_now) {
            case MAR_SUB_ST_STAND:
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[1], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_RELAX:
                switch (sh2mar.relax_flag) {
                    case 0:
                        anime = 16;
                        break;
                    case 1:
                        anime = 18;
                        break;
                    case 2:
                        anime = 19;
                        break;
                }
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[anime - 10], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_RELAX_OFF:
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[7], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_AFRAID:
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[5], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_TIRED:
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[4], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_ONESTEP:
                switch (sh2mar.pushed_dir) {
                    case -1:
                        aip = &pmaria_anim_0x00397090[39];
                        break;
                    case 1:
                        aip = &pmaria_anim_0x00397090[38];
                        break;
                    case 0:
                        break;
                }
                maria_anim_set_all(aip, 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
            case MAR_SUB_ST_WALK: {
                int comp_type;
                switch ((u8) w->sub_status_prev) {
                    case MAR_SUB_ST_RUN:
                        comp_type = 10;
                        mar_flg_on(&w->anime_st_flg, 4U);
                        break;
                    case MAR_SUB_ST_RELAX_OFF:
                        comp_type = 2;
                        break;
                    default:
                        comp_type = 4;
                        mar_flg_on(&w->anime_st_flg, 2U);
                        break;
                }
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[2], comp_type);
                break;
            }
            case MAR_SUB_ST_RUN: {
                int comp_type;
                if ((u8) w->sub_status_prev == 6) {
                    comp_type = 10;
                    mar_flg_on(&w->anime_st_flg, 4U);
                } else {
                    comp_type = 4;
                    mar_flg_on(&w->anime_st_flg, 2U);
                }
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[3], comp_type);
                break;
            }
            case MAR_SUB_ST_DAMAGE:
                maria_anim_set_all(aip = &pmaria_anim_0x00397090[sh2mar.damage_no - 10], 4);
                mar_flg_on(&w->anime_st_flg, 2U);
                break;
        }
        anime_change_check_1840 = (s32) (u8) w->sub_status_now;
        mar_flg_off(&w->anime_st_flg, 64);
    }
    if (scp_d->anime.comp_type < 3) {
        mar_flg_off(&w->anime_st_flg, 2U);
    }
    if (scp_d->anime.comp_type < 9) {
        mar_flg_off(&w->anime_st_flg, 4U);
    }
    if (scp_d->anime.comp_type == -1) {
        mar_flg_on(&w->anime_pause, 1U);
        return;
    }
    mar_flg_off(&w->anime_pause, 1U);
}

void MariaUpdatePosition(SubCharacter* this) {
    void (*mar_sub_func)(SubCharacter*) = func_list_sub[(u8) sh2mar.sub_status_now];
    float cos_x;
    float cos_z;

    f32 var_f12;
    f32 var_f12_2;
    f32 var_f12_3;
    f32 var_f12_4;
    s32 i1;
    s32 i1_2;
    s32 i1_3;
    s32 i1_4;

    mar_sub_func(this);
    switch (sh2mar.sub_status_now) {
        case MAR_SUB_ST_DAMAGE:
            var_f12 = this->rot.y + this->spd_roty;
            if (var_f12 <= PI) {
                i1 = 0;
            } else
                i1 = 1;

            if (i1 != 0) {
                var_f12 -= TAU;
            } else if (var_f12 < -PI) {
                var_f12 += TAU;
            }
            this->pos_spd.x = this->spd * dtf * shSinF(var_f12);
            var_f12_2       = this->rot.y + this->spd_roty;
            i1_2            = 1;
            if (var_f12_2 <= PI) {
                i1_2 = 0;
            }
            if (i1_2 != 0) {
                var_f12_2 -= TAU;
            } else if (var_f12_2 < -PI) {
                var_f12_2 += TAU;
            }
            this->pos_spd.z = this->spd * dtf * shCosF(var_f12_2);
            break;
        default:
            var_f12_3 = sh2mar.to_target;
            i1_3      = 1;
            if (var_f12_3 <= PI) {
                i1_3 = 0;
            }
            if (i1_3 != 0) {
                var_f12_3 -= TAU;
            } else if (var_f12_3 < -PI) {
                var_f12_3 += TAU;
            }
            this->pos_spd.x = this->spd * dtf * shSinF(var_f12_3);
            var_f12_4       = sh2mar.to_target;
            i1_4            = 1;
            if (var_f12_4 <= PI) {
                i1_4 = 0;
            }
            if (i1_4 != 0) {
                var_f12_4 -= TAU;
            } else if (var_f12_4 < -PI) {
                var_f12_4 += TAU;
            }
            this->pos_spd.z = this->spd * dtf * shCosF(var_f12_4);
            this->spd_roty  = 0.0f;
    }
    this->pos_spd.y = this->spd_y;
    this->pos_spd.x = 1.0f * (this->pos_spd.x * 1.0f);
    this->pos_spd.z = 1.0f * (this->pos_spd.z * 1.0f);
    sh2mar.pos.x    = this->pos_spd.x;
    sh2mar.pos.y    = this->pos_spd.y;
    sh2mar.pos.z    = this->pos_spd.z;
    sh2mar.pos.x *= 500.0f;
    sh2mar.pos.y *= 500.0f;
    sh2mar.pos.z *= 500.0f;
    SCAddPos(this, &sh2mar.pos);
}

void MariaCheckSound(void) {
    MariaCheckSoundLower();
    MariaCheckSoundUpper();
}

void MariaInitOnConnect(void) {
    int i1 = -1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    s16 temp_a0;

    sh2mar.column_atk.kind    = 1;
    sh2mar.column_mov.kind    = 1;
    sh2mar.column_atk.kind    = 2;
    sh2mar.column_mov.kind    = 2;
    sh2mar.column_atk.kind    = 6;
    sh2mar.column_mov.kind    = 6;
    sh2mar.column_atk.kind    = 3;
    sh2mar.column_mov.kind    = 3;
    sh2mar.column_atk.p[0][3] = 1.0f;
    sh2mar.column_mov.p[0][3] = 1.0f;
    sh2mar.column_atk.p[0][0] = 0.0f;
    sh2mar.column_mov.p[1][0] = 0.0f;
    sh2mar.column_atk.p[0][2] = 0.0f;
    sh2mar.column_mov.p[1][2] = 0.0f;
    if (sh2jms.room_name_prev != 0) {
        for (i1 = 0; maria_apeear_point_list[i1].room_name_prev != 0; i1++) {
            if ((sh2jms.room_name_prev == maria_apeear_point_list[i1].room_name_prev) && (sh2jms.room_name_now == maria_apeear_point_list[i1].room_name_now)) {
                sh2mar.mar_p->pos.x = sh2mar.mar_p->b_pos.x = maria_apeear_point_list[i1].pos[0];
                sh2mar.mar_p->pos.y = sh2mar.mar_p->b_pos.y = maria_apeear_point_list[i1].pos[1];
                sh2mar.mar_p->pos.z = sh2mar.mar_p->b_pos.z = maria_apeear_point_list[i1].pos[2];
                sh2mar.mar_p->rot.y = sh2mar.mar_p->b_rot.y = maria_apeear_point_list[i1].pos[3];
                sh2mar.active_type                          = maria_apeear_point_list[i1].active_type;
                break;
            }
        }
    }
    if ((i1 == -1) || (maria_apeear_point_list[i1].room_name_prev == 0)) {
        sh2mar.mar_p->pos.x = sh2jms.player->pos.x + (500.0f * shSinF(sh2jms.player->rot.y));
        sh2mar.mar_p->pos.y = sh2jms.player->pos.y;
        sh2mar.mar_p->pos.z = sh2jms.player->pos.z + (500.0f * shCosF(sh2jms.player->rot.y));
        sh2mar.mar_p->rot.y = 3.1415927f + sh2jms.player->pos.y;
        sh2mar.active_type  = 2;
    }

    sh2mar.column_mov.p[0][0] = sh2mar.column_atk.p[0][0] = sh2mar.mar_p->pos.x;
    sh2mar.column_mov.p[0][1] = sh2mar.column_atk.p[0][1] = -50.0f + sh2mar.mar_p->pos.y;
    sh2mar.column_mov.p[0][2] = sh2mar.column_atk.p[0][2] = sh2mar.mar_p->pos.z;
    sh2mar.column_mov.p[1][1] = sh2mar.column_atk.p[1][1] = -850.0f + sh2mar.mar_p->pos.y;

    if (sh2mar.active_type == 1) {
        sh2mar.column_atk.p[1][3] = 50.0f;
        sh2mar.column_mov.p[1][3] = 50.0f;
    } else {
        sh2mar.column_atk.p[1][3] = 150.0f;
        sh2mar.column_mov.p[1][3] = 150.0f;
    }
    sh2mar.col_mov_z_hosei  = 0.0f;
    sh2mar.col_atk_z_hosei  = 0.0f;
    sh2mar.mar_p->spd_org   = 0.0f;
    sh2mar.mar_p->spd       = 0.0f;
    sh2mar.tgt_pointer      = 0;
    sh2mar.afraid_time      = 0.0f;
    sh2mar.relax_time       = 0.0f;
    sh2mar.muteki_time      = 0.0f;
    sh2mar.move_time        = 0.0f;
    sh2mar.stand_time       = 0.0f;
    sh2mar.dist_to_jms      = 0.0f;
    sh2mar.tired_max        = 0;
    sh2mar.tired            = 0;
    sh2mar.no_damage        = 0;
    sh2mar.main_status_now  = 0;
    sh2mar.main_status_prev = 0;
    sh2mar.sub_status_now   = 0;
    sh2mar.sub_status_prev  = 0;
    mar_flg_on(&sh2mar.sub_st_flg, 1U);
    mar_sub_st_set(0, &sh2mar);
    mar_sub_flg_set(0, &sh2mar);
    sh2mar.look_jms = 1;
}

void MariaSetHeightConnectWait(void) {
    MariaSetHeight(sh2mar.mar_p);
}

void MariaStatusClear(void) {
    sh2mar.mar_p->battle.id         = 0;
    sh2mar.mar_p->battle.atk_result = 0;
}
