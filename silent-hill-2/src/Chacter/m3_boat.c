#include "sh2_common.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/sh2dt.h"

#include "sce/eeregs.h"
#include "vec.h"
#include "sdk.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/sh2_battle_list.h"
#include "Chacter/lake_wave.h"
#include "Chacter/m3_play.h"
#include "Chacter/m3_boat.h"
#include "Chacter/m3_sc.h"
#include "Chacter/player_result.h"

#include "Collision/cl_main.h"
#include "Multi_thr/pad/keydata.h"
#include "shPad/lib_sh_pad.h"

#define STICK_BUF_SIZE 20

static void close_to_value(short* now, short tgt, short mov);
static int HumanBOTInit(void);
static float BoatCheckKeyInputStickDir(float x, float y);
static float BoatCheckKeyInputStickPow(float x, float y, float dir);
static int check_value(float key, float* buf);
static void BoatCheckKeyInput(void);
static void BoatSetHeightDummy();
static void BoatSetHeight(SubCharacter* this);
static void BoatCheckSetParameter(SubCharacter* this);
static void boat_both(void);
static void boat_right(void);
static void boat_left(void);
static void BoatCheckStatus(SubCharacter* this);
static void BoatCheckControl(SubCharacter* this);
static void BoatCheckAnimeSpeed(SubCharacter* scp);
static void boat_anim_set_all(AnimeInfo* aip, int comp_type);
static void BoatCheckAnime(SubCharacter* scp);
static void BoatCheckOarStatus(SubCharacter* scp);
static void BoatCheckEffect(void);
static void BoatCheckSound(void);
static void BoatCheckRollEnergy(SubCharacter* scp);
static void BoatCheckSetFirst(SubCharacter* this);
static void HumanBOTFunction(SubCharacter* this);

const static AnimeInfo boat_anim[5] = {
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 51,
        /* .frame = */ 150,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 149,
        /* .loop = */ true,
        /* .pad = */ -1,
    },
    {
        /* .name = */ 52,
        /* .frame = */ 150,
        /* .speed = */ 0,
        /* .start = */ 150,
        /* .end = */ 299,
        /* .loop = */ true,
        /* .pad = */ -1,
    },
    {
        /* .name = */ 53,
        /* .frame = */ 150,
        /* .speed = */ 0,
        /* .start = */ 300,
        /* .end = */ 449,
        /* .loop = */ true,
        /* .pad = */ -1,
    },
    {
        /* .name = */ 54,
        /* .frame = */ 24,
        /* .speed = */ 32,
        /* .start = */ 450,
        /* .end = */ 473,
        /* .loop = */ true,
        /* .pad = */ 0,
    }
}; // size: 0x3C, address: 0x39A610
const static AnimeInfo d_boat_anim[4] = {
    {
        /* .name = */ 0,
        /* .frame = */ 0,
        /* .speed = */ 0,
        /* .start = */ 0,
        /* .end = */ 0,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 56,
        /* .frame = */ 3000,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 2999,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 57,
        /* .frame = */ 1078,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1077,
        /* .loop = */ false,
        /* .pad = */ 0,
    },
    {
        /* .name = */ 58,
        /* .frame = */ 1896,
        /* .speed = */ 2048,
        /* .start = */ 0,
        /* .end = */ 1895,
        /* .loop = */ false,
        /* .pad = */ 0,
    }
}; // size: 0x30, address: 0x39A650
extern /* static */ AnimeInfo b_james_anim[5]; // size: 0x3C, address: 0x0
static CL_HITPOLY_PLANE lake_active_wall_list[12] = {
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {40000.0f, 3490.0f, -40000.0f, 1.0f, 40000.0f, 3490.0f, -80000.0f, 1.0f, 40000.0f, 3690.0f, -80000.0f, 1.0f, 40000.0f, 3690.0f, -40000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {40000.0f, 3490.0f, -80000.0f, 1.0f, 30000.0f, 3490.0f, -100000.0f, 1.0f, 30000.0f, 3690.0f, -100000.0f, 1.0f, 40000.0f, 3690.0f, -80000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {30000.0f, 3490.0f, -100000.0f, 1.0f, -40000.0f, 3490.0f, -100000.0f, 1.0f, -40000.0f, 3690.0f, -100000.0f, 1.0f, 30000.0f, 3690.0f, -100000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-40000.0f, 3490.0f, -100000.0f, 1.0f, -50000.0f, 3490.0f, -80000.0f, 1.0f, -50000.0f, 3690.0f, -80000.0f, 1.0f, -40000.0f, 3690.0f, -100000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-45000.0f, 3490.0f, -100000.0f, 1.0f, -45000.0f, 3490.0f, -20000.0f, 1.0f, -45000.0f, 3690.0f, -20000.0f, 1.0f, -45000.0f, 3690.0f, -100000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-50000.0f, 3490.0f, -40000.0f, 1.0f, -40000.0f, 3490.0f, -20000.0f, 1.0f, -40000.0f, 3690.0f, -20000.0f, 1.0f, -50000.0f, 3690.0f, -40000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-40000.0f, 3490.0f, -21000.0f, 1.0f, 30000.0f, 3490.0f, -21000.0f, 1.0f, 30000.0f, 3690.0f, -21000.0f, 1.0f, -40000.0f, 3690.0f, -21000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {30000.0f, 3490.0f, -20000.0f, 1.0f, 40000.0f, 3490.0f, -40000.0f, 1.0f, 40000.0f, 3690.0f, -40000.0f, 1.0f, 30000.0f, 3690.0f, -20000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-40500.0f, 3490.0f, -61000.0f, 1.0f, -45000.0f, 3490.0f, -58000.0f, 1.0f, -45000.0f, 3690.0f, -58000.0f, 1.0f, -40500.0f, 3690.0f, -61000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-42000.0f, 3490.0f, -78000.0f, 1.0f, -40500.0f, 3490.0f, -61000.0f, 1.0f, -40500.0f, 3690.0f, -61000.0f, 1.0f, -42000.0f, 3690.0f, -78000.0f, 1.0f},
    },
    {
        /* .kind = */ 1,
        /* .shape = */ 1,
        /* .pad = */ 0,
        /* .weight = */ 4,
        /* .material = */ MATERIAL_TYPE_2,
        /* .flg = */ 0,
        /* .p = */ {-45000.0f, 3490.0f, -80000.0f, 1.0f, -42000.0f, 3490.0f, -78000.0f, 1.0f, -42000.0f, 3690.0f, -78000.0f, 1.0f, -45000.0f, 3690.0f, -80000.0f, 1.0f},
    },
    {
        /* .kind = */ 0,
        /* .shape = */ 0,
        /* .pad = */ 0,
        /* .weight = */ 0,
        /* .material = */ MATERIAL_TYPE_0,
        /* .flg = */ 0,
        /* .p = */ {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    }
};

static int dt; // size: 0x4, address: 0x1202578
static float dtf; // size: 0x4, address: 0x1202570

shBoatWork sh2bot; // size: 0x20, address: 0x1202550
Matrix4 boat_localworld_matrix; // size: 0x40, address: 0x1202510
Vector4 rot; // size: 0x10, address: 0x1202500
Vector4 pos; // size: 0x10, address: 0x12024F0
float pos_aspd; // size: 0x4, address: 0x12024E8
float rot_aspd; // size: 0x4, address: 0x12024E0
float lstick_buf[20]; // size: 0x50, address: 0x1202490
float rstick_buf[20]; // size: 0x50, address: 0x1202440
float lstick_power; // size: 0x4, address: 0x1202430
float rstick_power; // size: 0x4, address: 0x1202428
float round_power; // size: 0x4, address: 0x1202420
float straight_power; // size: 0x4, address: 0x1202418
float lstick_total_power; // size: 0x4, address: 0x1202410
float rstick_total_power; // size: 0x4, address: 0x1202408
u_short lstick_status; // size: 0x2, address: 0x1202400
u_short rstick_status; // size: 0x2, address: 0x12023F8
float key_lstick_power; // size: 0x4, address: 0x12023F0
float key_rstick_power; // size: 0x4, address: 0x12023E8
float key_lstick_dir; // size: 0x4, address: 0x12023E0
float key_rstick_dir; // size: 0x4, address: 0x12023D8
int oar_status_left[2]; // size: 0x8, address: 0x12023D0
int oar_status_right[2]; // size: 0x8, address: 0x12023C8
float wv_energy_x; // size: 0x4, address: 0x12023C0
float wv_energy_y; // size: 0x4, address: 0x12023B8
float wv_energy_z; // size: 0x4, address: 0x12023B0
float wv_timer_x; // size: 0x4, address: 0x12023A8
float wv_timer_y; // size: 0x4, address: 0x12023A0
float wv_timer_z; // size: 0x4, address: 0x1202398
float wv_shinpuku_x; // size: 0x4, address: 0x1202390
float wv_shinpuku_z; // size: 0x4, address: 0x1202388
float wv_height_x; // size: 0x4, address: 0x1202380
float wv_height_z; // size: 0x4, address: 0x1202378
float wv_height_y; // size: 0x4, address: 0x1202370
int wv_status_x; // size: 0x4, address: 0x1202368
int wv_status_z; // size: 0x4, address: 0x1202360
int wv_type_x; // size: 0x4, address: 0x1202358
int wv_type_z; // size: 0x4, address: 0x1202350
short anm_speed_left; // size: 0x2, address: 0x1202348
short anm_speed_right; // size: 0x2, address: 0x1202340
float oar_pos_left[4]; // size: 0x10, address: 0x1202330
float oar_pos_right[4]; // size: 0x10, address: 0x1202320
extern Matrix4 kt_unit_matrix; // size: 0x40, address: 0x2A7B90

void bot_flg_on(u_int* type /* r2 */, u_int status /* r2 */) {
    *type |= status;
}

void bot_flg_off(u_int* type /* r2 */, u_int status /* r2 */) {
    *type &= ~status;
}

int bot_anime_flg_on(u_int status /* r2 */) {
    return sh2bot.anime_st_flg & status;
}

void bot_st_set(int status /* r2 */, shBoatWork* w /* r2 */) {
    w->status_prev = w->status_now;
    w->status_now = status;
}

/*
 * Checks if the short at `now` is within `mov` of `tgt`.
 */
static void close_to_value(short* now /* r2 */, short tgt /* r2 */, short mov /* r2 */) {
    if (*now == tgt) return;
    if (tgt < *now) {
        *now = *now - mov;
        if (*now < tgt)
            *now = tgt;
    } else {
        *now = *now + mov;
        if (tgt < *now) {
            *now = tgt;
        }
    }
}

static int HumanBOTInit(void) {
    int i1; // r3
    
    lstick_status = 0;
    rstick_status = 0;
    round_power = 0.0f;
    straight_power = 0.0f;
    lstick_total_power = 0.0f;
    rstick_total_power = 0.0f;
    
    for (i1 = 0; i1 < 2; i1++) {
        oar_status_left[i1] = 0;
        oar_status_right[i1] = 0;
    }
    wv_energy_x = 0.0f;
    wv_energy_z = 0.0f;
    wv_timer_x = 0.0f;
    wv_timer_z = 0.0f;
    wv_shinpuku_x = 0.0f;
    wv_shinpuku_z = 0.0f;
    wv_height_x = 0.0f;
    wv_height_z = 0.0f;
    
    wv_height_y = 0.0f;
    
    wv_status_x = 0;
    wv_status_z = 0;
    wv_type_x = 0;
    wv_type_z = 0;
    
    anm_speed_left = 0;
    anm_speed_right = 0;
    
    for (i1 = 0; i1 < STICK_BUF_SIZE; i1++) {
        lstick_buf[i1] = 0.0f;
        rstick_buf[i1] = 0.0f;
    }
    
    mizTestLakeWaveInit();
    
    
    
    
    
    
    sh2bot.anim_change = 0;
    sh2bot.anime_change_now = 0;
    sh2bot.anime_change_prev = 0;
    
    return 0;
}

/**
 * Gets the angle of the stick in radians
 */
static float BoatCheckKeyInputStickDir(float x /* r29+0x10 */, float y /* r29+0x10 */) {
        return shAtan2(-y, x);
}

/**
 * Power is equal to how far the stick is moved in a certain direction
 */
static float BoatCheckKeyInputStickPow(float x /* r20 */, float y /* r22 */, float dir /* r21 */) {
    float pow_x, pow_y; // @note this is the correct dwarf order, assumes inverted stick
    float pow;
    pow_y = x * shSinF(dir); // r20
    pow_x = -y * shCosF(dir); // r29+0x20
    
    pow = SQRT(pow_y * pow_y + pow_x * pow_x); // r29+0x20
    pow = pow < 0.0f ? 0.0f : pow > 1.0f ? 1.0f : pow;
    
    return pow;
}

/**
 * Checks if any the last `STICK_BUF_SIZE` stick values were equal to `key`.
 */
static int check_value(float key /* r29 */, float* buf /* r2 */) {
    int i; // r3

    for (i = 0; i < STICK_BUF_SIZE; i++, buf++) {
        if (key != *buf) return false;
    }

    return true;
}

static void BoatCheckKeyInput(void) {
    static u_char pad_local[32]; // @ 0x01202300
    static int left, right; // @ 0x012022F8, @ 0x012022F0
    shGameKeyData key; // r29+0x88
    int i; // r4
    float rot_left, rot_right; // r20, r1
    float lstick_real_power, rstick_real_power; // r29+0x90
    int anime_type[3][3] = {
        { 0, 1, 1 },
        { 2, 0, 1 },
        { 2, 1, 0 },
    }; // r29+0x60
    int cy, cx, ay, ax;













    
    libShPadRead(0, 0, pad_local);
    shSysKeyNormalize(pad_local);
    shSysKeyAdjust(pad_local);
    shGameKeyConvert(&key, pad_local);
    
    cy = (s_char) key.f.CY;
    cx = (s_char) key.f.CX;
    ay = (s_char) key.f.AY;
    ax = (s_char) key.f.AX;
    
    key_lstick_dir = BoatCheckKeyInputStickDir(ax, ay);
    key_rstick_dir = BoatCheckKeyInputStickDir(cx, cy);
    key_lstick_power = BoatCheckKeyInputStickPow(ax, ay, key_lstick_dir);
    key_rstick_power = BoatCheckKeyInputStickPow(cx, cy, key_rstick_dir);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    If playing on easy, the stick buffer is not used at all. The direction
    is computed from the current stick position.
    
    
    
    */
    if (playing.battle_level == SH2_RIDDLE_LEVEL_EASY) {
        
        lstick_power = 0.5f * key_lstick_power * shCosF(key_lstick_dir) + (0.5f * (0.5f * key_lstick_power * shSinF(key_lstick_dir)));
        
        rstick_power = 0.5f * key_lstick_power * shCosF(key_lstick_dir) - (0.5f * (0.5f * key_lstick_power * shSinF(key_lstick_dir)));
        
        
        if (lstick_power < 0.0f && rstick_power >= 0.0f)
            left = 1, right = 2;
        else if (lstick_power < 0.0f && rstick_power >= 0.0f)
            left = 2, right = 1;
        else
            left = 1, right = 1;
    
    } else {
        // get the change in direction
        rot_left = shAngleRegulate(key_lstick_dir - *lstick_buf);
        rot_right = shAngleRegulate(key_rstick_dir - *rstick_buf);
        
        
        
        lstick_status = 0;
        
        lstick_status |= 1 << 0;
        
        if (check_value(key_lstick_dir, lstick_buf)) {
        
            lstick_power = 0.0f;
            lstick_status |= 1 << 1;
            left = 0;
        } else {
            lstick_power = -rot_left;
            if (rot_left > 0.0f) {
                
                lstick_status |= 1 << 2;
                left = 2;
            } else if (rot_left < 0.0f) {
                
                lstick_status |= 1 << 3;
                left = 1;
            } else {
                switch (left) {
                    case 0:
                        lstick_status |= 1 << 1;
                        break;
                    case 1:
                        lstick_status |= 1 << 3;
                        break;
                    case 2:
                        lstick_status |= 1 << 2;
                        break;
                }
            }
        }
        
        // move the sliding window
        for (i = STICK_BUF_SIZE - 1; i > 0; i--)
            lstick_buf[i] = lstick_buf[i - 1];

        *lstick_buf = key_lstick_dir;
        
        lstick_power = lstick_power < -0.5f ? -0.5f : lstick_power > 0.5f ? 0.5f : lstick_power;
        
        
        
        // copy & pasted logic for the right stick:
        
        
        rstick_status = 0;
        
        rstick_status |= 1 << 0;

        if (check_value(key_rstick_dir, rstick_buf)) {
            
            rstick_power = 0.0f;
            rstick_status |= 1 << 1;
            right = 0;
        } else {
            rstick_power = rot_right;
            if (rot_right > 0.0f) {
            
                rstick_status |= 1 << 2;
                right = 1;
            } else if (rot_right < 0.0f) {

                rstick_status |= 1 << 3;
                right = 2;
            } else {
                switch (right) {
                    case 0:
                        rstick_status |= 1 << 1;
                        break;
                    case 1:
                        rstick_status |= 1 << 2;
                        break;
                    case 2:
                        rstick_status |= 1 << 3;
                        break;
                }
            }
        }
        
        
        for (i = STICK_BUF_SIZE - 1; i > 0; i--)
            rstick_buf[i] = rstick_buf[i - 1];

        *rstick_buf = key_rstick_dir;
        
        rstick_power = rstick_power < -0.5f ? -0.5f : rstick_power > 0.5f ? 0.5f : rstick_power;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    
    
    {
        float lstick = lstick_power; // @note not in dwarf
        float rstick = rstick_power; // @note not in dwarf
        
        
        
        
        
        
        
        
        round_power = 2.0f * (lstick - rstick);
        
        
        
        straight_power = 0.5f * (lstick + rstick);
        
        
        
        
        if (sh2bot.anime_change_timer == 0.0f) {
        
            sh2bot.anime_change_prev = sh2bot.anime_change_now;
            sh2bot.anime_change_now = anime_type[left][right];
            
            if (sh2bot.boat_p->spd >= 2.0f) {
                sh2bot.anime_change_now = 0;
            }
            if (sh2bot.anime_change_prev != sh2bot.anime_change_now) {
                sh2bot.anime_change_timer = 1.5f;
            }
        }
    }























}

void BoatSetHeightDummy(void) {
    /* empty */
}

void BoatSetHeight(SubCharacter* this) {
    this->pos.y = 500.0f * (7.18f + wv_height_y);
    if (sh2jms.player->status & (1 << SCP_STATUS_BIT_17)) {
        this->center_y = -10000.0f;
        this->eye_y = -10000.0f;
        return;
    }
    this->center_y = -10000.0f;
    this->eye_y = -10000.0f;
}

static void (* func_list_main[3])(SubCharacter *) = {boat_both, boat_right, boat_left}; // size: 0xC, address: 0x371B78

static void BoatCheckSetParameter(SubCharacter* this) {
    CL_HITPOLY_COLUMN column; // r29+0x20

    
    GameBoatTimerCountUp();
    GameBoatMaxSpeedCheck(this->spd);
    
    
    sh2bot.anim_change = false;
    if (bot_anime_flg_on(1 << 2) == 0) {
        sh2bot.anime_change_timer -= dtf;
        if (sh2bot.anime_change_timer < 0.0f)
            sh2bot.anime_change_timer = 0.0f;
    }
    
    
    
    
    column.kind = 1;
    column.weight = 2;
    column.material = 6;
    column.shape = 3;
    
    column.p[0][3] = sh2jms.column_atk.p[0][3] = 1.0f;
    column.p[1][0] = sh2jms.column_atk.p[0][0] = 0.0f;
    column.p[1][2] = sh2jms.column_atk.p[0][2] = 0.0f;
    
    
    column.p[0][0] = sh2bot.boat_p->pos.x;
    column.p[0][1] = 50.0f + sh2bot.boat_p->pos.y;
    column.p[0][2] = sh2bot.boat_p->pos.z;
    column.p[1][1] = -50.0f + sh2bot.boat_p->pos.y;
    column.p[1][3] = 1650.0f;
    
    
    BoatSetHeight(this);
    
    clSetCharaHitColumn(&column, &column, this, BoatSetHeightDummy);
}



static void boat_both(void) {
    switch (sh2bot.anime_change_now) {
        case 0:
            break;
        case 1:
            bot_st_set(1, &sh2bot);
            break;
        case 2:
            bot_st_set(2, &sh2bot);
            break;
    }
}



static void boat_right(void) {
    switch (sh2bot.anime_change_now) {
        case 0:
            bot_st_set(0, &sh2bot);
            break;
        case 1:
            break;
        case 2:
            bot_st_set(2, &sh2bot);
            break;
    }
}



static void boat_left(void) {
    switch (sh2bot.anime_change_now) {
        case 0:
            bot_st_set(0, &sh2bot);
            break;
        case 1:
            bot_st_set(1, &sh2bot);
            break;
        case 2:
            break;
    }
}



static void BoatCheckStatus(SubCharacter* this) {
    void (*boat_main_func)(SubCharacter*) = func_list_main[sh2bot.status_now]; // r2
    func_list_main[sh2bot.status_now](this);
}


static void BoatCheckControl(SubCharacter* this) {
    f32 var_f12;
    s32 var_v0;
    s32 var_v1;

    this->spd -= 0.15f * this->spd * dtf;
    this->rot.w -= 0.2f * this->rot.w * dtf;

    if (ABS_WITHIN_TOLERANCE(this->spd, 0.05f) && !straight_power)
        this->spd = 0.0f;

    if (ABS_WITHIN_TOLERANCE(this->rot.w, 0.025f) && !round_power)
        this->rot.w = 0.0f;

    pos_aspd = 1.5f * straight_power;
    this->spd += (pos_aspd * dtf);
    this->spd = CLAMP(this->spd, -3.0f, 4.0f);

    rot_aspd = (0.25f * round_power) / (1.0f + fabsf(this->spd));
    this->rot.w += (rot_aspd * dtf);
    this->rot.w = CLAMP(this->rot.w, -1.5f, 1.5f);

    var_f12 = this->rot.y + this->spd_roty;
    var_f12 = GET_REFLEX_ANGLE(var_f12);
    this->pos_spd.x = this->spd * dtf * shSinF(var_f12);

    var_f12 = this->rot.y + this->spd_roty;
    var_f12 =  GET_REFLEX_ANGLE(var_f12);
    this->pos_spd.z = this->spd * dtf * shCosF(var_f12);
    this->pos_spd.y = this->spd_y * dtf;

    rot.y = this->rot.w * dtf;
    pos.x = this->pos_spd.x;
    pos.y = this->pos_spd.y;
    pos.z = this->pos_spd.z;
    pos.x = pos.x * 500.0f;
    pos.y = pos.y * 500.0f;
    pos.z = pos.z * 500.0f;

    if (wv_energy_y != 0.0f) {
        wv_timer_y += dtf;
        if ((wv_timer_y > 2.0f)) {
            wv_timer_y -= 2.0f;
        }
        wv_height_y = -wv_energy_y * sinf(PI * wv_timer_y);
        wv_energy_y -= (0.01f * wv_energy_y);
        var_v1 = wv_energy_y >= -0.0005f && wv_energy_y < 0.0005f ? 1 : 0;
        if (var_v1 != 0) {
            wv_energy_y = 0.0f;
            wv_timer_y = 0.0f;
            wv_height_y = 0.0f;
        }
    }

    if (wv_energy_x != 0.0f) {
        wv_timer_x += dtf;
        if (wv_timer_x > 2.0f)
            wv_timer_x -= 2.0f;

        if (wv_timer_x >= 0.5f && wv_timer_x < 1.5f) wv_status_x = -1;
        else wv_status_x = 1;

        wv_shinpuku_x = sqrtf(2.0f * wv_energy_x / 1480.4408f);
        wv_height_x = wv_shinpuku_x * sinf(PI * wv_timer_x);
        wv_energy_x -= (0.02f * wv_energy_x);
        
        if (ABS_WITHIN_TOLERANCE(wv_energy_x, 0.0005f)) {
            wv_energy_x = 0.0f;
            wv_timer_x = 0.0f;
            wv_height_x = 0.0f;
        }
        this->rot.z = atan2f(wv_height_x, 0.5f);
    }

    if (wv_energy_z != 0.0f) {
        wv_timer_z += dtf;
        if (wv_timer_z > 2.0f)
            wv_timer_z -= 2.0f;

        if (wv_timer_z >= 0.5f && wv_timer_z < 1.5f) wv_status_z = -1;
        else wv_status_z = 1;

        wv_shinpuku_z = sqrtf(2.0f * wv_energy_z / 1480.4408f);
        wv_height_z = wv_shinpuku_z * sinf(PI * wv_timer_z);
        wv_energy_z -= 0.02f * wv_energy_z;

        if (IS_IN_RANGE(wv_energy_z, -0.0005f, 0.0005f)) {
            wv_energy_z = 0.0f;
            wv_timer_z = 0.0f;
            wv_height_z = 0.0f;
        }
        
        this->rot.x = atan2f(wv_height_z, 2.0f);
    }
}



static void BoatCheckAnimeSpeed(SubCharacter* scp) {
    short purpose_speed_left; // r17
    short purpose_speed_right; // r8
    SubCharacter* boat_jms; // r2
    SubCharacterDisp* scp_d; // r2

    purpose_speed_left = (8.0f * (4096.0f * lstick_power));
    purpose_speed_right = (8.0f * (4096.0f * rstick_power));
    
    if (shAbs(purpose_speed_left) > shAbs(anm_speed_left)) {
        close_to_value(&anm_speed_left, purpose_speed_left, 0x40);
    } else {
        close_to_value(&anm_speed_left, purpose_speed_left, 0x10);
    }
    
    if (shAbs(purpose_speed_right) > shAbs(anm_speed_right)) {
        close_to_value(&anm_speed_right, purpose_speed_right, 0x40);
    } else {
        close_to_value(&anm_speed_right, purpose_speed_right, 0x10);
    }

    anm_speed_left = CLAMP(anm_speed_left, -0x800, 0x800);
    anm_speed_right = CLAMP(anm_speed_right, -0x800, 0x800);

    switch (sh2bot.anime_change_now) {
        case 0:
            shCharacterAnimeSpeedAdd(scp, sh2bot.anime_speed = (anm_speed_left + anm_speed_left) & ~1);
            return;
        case 1:
            shCharacterAnimeSpeedAdd(scp, sh2bot.anime_speed = anm_speed_right * 2);
            return;
        case 2:
            shCharacterAnimeSpeedAdd(scp, sh2bot.anime_speed = anm_speed_left * 2);
            return;
    }
}



static void boat_anim_set_all(AnimeInfo* aip, int comp_type) {
                                                            //probably incorrect
    shCharacterAnimeSet(sh2bot.boat_p, 0, comp_type, aip, (int)shCharacterGetAnimeAdrForPlay(sh2bot.boat_p));
}



static void BoatCheckAnime(SubCharacter* scp) {
    static int anime_change_check = -1; // @ 0x00371B88
    shBoatWork* w = &sh2bot; // r16
    SubCharacterDisp* scp_d; // r17
    AnimeInfo* aip; // r18

    scp_d = (SubCharacterDisp*) w->boat_p;
    w->anim_change = 0;
    if (!bot_anime_flg_on(4) && (w->status_now != anime_change_check || bot_anime_flg_on(8))) {
        switch (w->status_now) {
            case 0:
                aip = (AnimeInfo*) &boat_anim[1];
                break;
            case 1:
                aip = (AnimeInfo*) &boat_anim[2];
                break;
            case 2:
                aip = (AnimeInfo*) &boat_anim[3];
                break;
        }
        boat_anim_set_all(aip, 10);
        bot_flg_on(&w->anime_st_flg, 1 << 2);
        anime_change_check = w->status_now;
        mar_flg_off(&w->anime_st_flg, 1 << 3);
        sh2bot.anim_change = 1;
    }
    if (scp_d->anime.comp_type < 3) {
        bot_flg_off(&w->anime_st_flg, 1 << 1);
    }
    if (scp_d->anime.comp_type < 9) {
        bot_flg_off(&w->anime_st_flg, 1 << 2);
    } else {
        shCharacterAnimeSpeedAddY(scp, 1 << 6);
    }
    if (scp_d->anime.comp_type == -1) {
        bot_flg_on(&w->anime_pause, 1 << 0);
        return;
    }
    bot_flg_off(&w->anime_pause, 1 << 0);
}



static void BoatCheckOarStatus(SubCharacter* scp) {
    int i; // r3
    shSkelton* top; // r4

    top = scp->sk_top;
    for (i = 0; i < 3; i++)
        top = top->next;

    shVectorCopy(oar_pos_left, top->src_m.d[3]);
    top = top->next;
    shVectorCopy(oar_pos_right, top->src_m.d[3]);
    sceVu0ApplyMatrix(oar_pos_left, (sceVu0FVECTOR*) &boat_localworld_matrix, oar_pos_left);
    sceVu0ApplyMatrix(oar_pos_right, (sceVu0FVECTOR*) &boat_localworld_matrix, oar_pos_right);
    oar_status_left[1] = oar_status_left[0];
    oar_status_right[1] = oar_status_right[0];
    if (oar_pos_left[1] > 3500.0f) {
        oar_status_left[0] = 1;
    } else {
        oar_status_left[0] = 0;
    }
    if ((oar_pos_right[1] > 3500.0f)) {
        oar_status_right[0] = 1;
        return;
    }
    oar_status_right[0] = 0;
}



static void BoatCheckEffect(void) {
    int kind_l = -1; // r16
    int kind_r = -1; // r2

    if (oar_status_right[0] == 0  && oar_status_right[1] == 1) kind_r = 1;
    if (oar_status_right[0] == 1  && oar_status_right[1] == 0) kind_r = 0;
    if (oar_status_left[0]  == 0  && oar_status_left[1]  == 1) kind_l = 1;
    if (oar_status_left[0]  == 1  && oar_status_left[1]  == 0) kind_l = 0;

    if (kind_r != -1)
        HH_Effect_Object_WaterSplash_Impact_Post(oar_pos_right, kind_r);

    if (kind_l != -1)
        HH_Effect_Object_WaterSplash_Impact_Post(oar_pos_left, kind_l);
}



static void BoatCheckSound(void) {
   
}


static void BoatCheckRollEnergy(SubCharacter* scp) {
    int init_check_x; // r18
    int init_check_y; // r19
    int init_check_z; // r16
    float energy_x; // r20
    float energy_y; // r21
    float energy_z; // r22
    shLakeWaveInfo* wip; // r17
    float angle; // r29+0x70


    if ((wv_energy_x == 0.0f) && (round_power != 0.0f)) init_check_x = 1;
    else init_check_x = 0;
    
    if ((wv_energy_z == 0.0f) && (straight_power != 0.0f)) init_check_z = 1;
    else init_check_z = 0;

    init_check_y = 0;
    energy_x = 0.05f * round_power;
    energy_z = 0.05f * straight_power;
    energy_y = 0.0f;

    wip = mizTestLakeWaveMain(scp);
    if (wip != NULL) {
        angle = wip->distance[1] - scp->rot.y;
        REFLEX_ANGLE(angle, angle);
        energy_x += 2.0f * (dtf * (wip->energy * sinf(angle)));
        energy_z += 4.0f * (dtf * (wip->energy * cosf(angle)));
        energy_y += wip->energy * 0.05;
        if (wv_energy_x != 0.0f) {
            init_check_x = 0;
        } else {
            init_check_x = 1;
        }
        if (wv_energy_z != 0.0f) {
            init_check_z = 0;
        } else {
            init_check_z = 1;
        }
        if (wv_energy_y != 0.0f) {
            init_check_y = 0;
        } else {
            init_check_y = 1;
        }
    }

    if (init_check_y != 0) {
        wv_timer_y = 0.0f;
        wv_energy_y += energy_y;
    }

    if (init_check_x != 0) {
        if ((energy_x > 0.0f)) {
            wv_timer_x = 0.0f;
            wv_status_x = 1;
        } else {
            wv_timer_x = 1.0f;
            wv_status_x = -1;
        }
        switch (wv_status_x) {
            case 1:
                wv_type_x = (u_char) (wv_height_x >= 0.0f ? 0 : 1);
                break;
            case -1:
                wv_type_x = (u_char) (wv_height_x > 0.0f ? 2 : 3);
                break;
        }
    }

    if (init_check_z != 0) {
        if (energy_z > 0.0f) {
            wv_timer_z = 0.0f;
            wv_status_z = 1;
        } else {
            wv_timer_z = 1.0f;
            wv_status_z = -1;
        }
        switch (wv_status_z) {
            case 1:
                wv_type_z = (u_char) (wv_height_z >= 0.0f ? 0 : 1);
                break;
            case -1:
                wv_type_z = (u_char) (wv_height_z > 0.0f ? 2 : 3);
                break;
        }
    }

    switch (wv_type_x) {
        case 0:
            wv_energy_x += energy_x;
            if (wv_energy_x < 0.0f) {
                wv_energy_x = -wv_energy_x;
                wv_timer_x = 0.5f;
                wv_type_x = 2;
            }
            break;
        case 1:
            wv_energy_x += energy_x;
            if (wv_energy_x < 0.0f) {
                wv_energy_x = -wv_energy_x;
                wv_timer_x = 1.0f;
                wv_type_x = 3;
            }
            break;
        case 2:
            wv_energy_x -= energy_x;
            if (wv_energy_x < 0.0f) {
                wv_energy_x = -wv_energy_x;
                wv_timer_x = 0.0f;
                wv_type_x = 0;
            }
            break;
        case 3:
            wv_energy_x -= energy_x;
            if (wv_energy_x < 0.0f) {
                wv_energy_x = -wv_energy_x;
                wv_timer_x = 1.5f;
                wv_type_x = 1;
            }
            break;
    }
    switch (wv_type_z) {
        case 0:
            wv_energy_z += energy_z;
            if (wv_energy_z < 0.0f) {
                wv_energy_z = -wv_energy_z;
                wv_timer_z = 0.5f;
                wv_type_z = 2;
            }
            break;

        case 1:
            wv_energy_z += energy_z;
            if (wv_energy_z < 0.0f) {
                wv_energy_z = -wv_energy_z;
                wv_timer_z = 1.0f;
                wv_type_z = 3;
            }
            break;

        case 2:
            wv_energy_z -= energy_z;
            if (wv_energy_z < 0.0f) {
                wv_energy_z = -wv_energy_z;
                wv_timer_z = 0.0f;
                wv_type_z = 0;
            }
            break;

        case 3:
            wv_energy_z -= energy_z;
            if (wv_energy_z < 0.0f) {
                wv_energy_z = -wv_energy_z;
                wv_timer_z = 1.5f;
                wv_type_z = 1;
            }
            break;
    }
}

static void BoatCheckSetFirst(SubCharacter* this) {
    shCharacterAnimeFrameSet(this, 60);
}

static inline void setBoatLocalWorldMatrix(SubCharacter* this) {
    sceVu0FVECTOR vec;
    vec[0] = this->rot.x; vec[1] = 0.0f; vec[2] = this->rot.z; vec[3] = 1.0f;
    sceVu0RotMatrix(boat_localworld_matrix.d, kt_unit_matrix.d, vec);
    sceVu0RotMatrixY(boat_localworld_matrix.d, boat_localworld_matrix.d, this->rot.y);
}

static inline void setBoatLocalWorldPosition(SubCharacter* this) {
    boat_localworld_matrix.d[3][0] = this->pos.x;
    boat_localworld_matrix.d[3][1] = this->pos.y;
    boat_localworld_matrix.d[3][2] = this->pos.z;
    boat_localworld_matrix.d[3][3] = 1.0f;
}

static void HumanBOTFunction(SubCharacter* this) {
    AnimeInfo* aip; // r17
    
    
    
    int count = *T0_COUNT;
    
    pos.z = pos.y = pos.x = 0.0f;
    rot.z = rot.y = rot.x = 0.0f;
    pos_aspd = 0.0f;
    rot_aspd = 0.0f;

    switch (this->step) {
        case 0: {
            sceVu0FVECTOR pos; // r29+0x30
            sceVu0FVECTOR rot; // r29+0x40
            sceVu0FVECTOR sp50;
            
            shVectorCopy(pos, &this->pos);
            shVectorCopy(rot, &this->rot);
            
            HumanBOTInit();
            
            if (PlayerNowDemoEventMode() == 0) {
                SCAnimeTypeSwitch(this, 1);
            
                aip = (AnimeInfo*) &boat_anim[1];
                shCharacterAnimeSet(this, 0, 0, aip, (int) shCharacterGetAnimeAdrForPlay(this));

                
                sh2bot.status_now = sh2bot.status_prev = 0;
            }
            
            
            shVectorCopy(&this->pos, pos);
            shVectorCopy(&this->rot, rot);
            
            BoatSetHeight(this);
            shCharacterSetPosAfterDemo(this, &this->pos.x, this->rot.y);
            
            this->step++;
            
            return;
        }
            
            
            
            
            
            
            
            
            
            
        case 1: 
            if (!(sh2jms.player->status & (1 << SCP_STATUS_BIT_NOW_DEMO_EVENT))) {
                
                
                
                
                if (!(this->status & (1 << SCP_STATUS_BIT_ANIME_TYPE))) {
                    this->step = 0;
                    HumanBOTFunction(this);
                }
                
                
                
                
                dt = shGetDF();
                dtf = shGetDT();
                
                
                
                clAddDynamicWall(lake_active_wall_list);
                
                
                
                
                
                
                
                
                
                
                
                
                
                if (sh2jms.player->status & (1 << SCP_STATUS_BIT_17)) {
                    BoatCheckKeyInput();
                    BoatCheckSetParameter(this);
                    BoatCheckStatus(this);
                    BoatCheckAnime(this);
                    BoatCheckControl(this);
                    BoatCheckAnimeSpeed(this);
                } else {
                
                    BoatCheckSetFirst(this);
                }
                
                

                
                setBoatLocalWorldMatrix(this);
                setBoatLocalWorldPosition(this);
                
                
                
                
                
                
                BoatCheckOarStatus(this);
                
                
                BoatCheckEffect();
                BoatCheckSound();
                
                
                
                
                
                
                
                
                
                
                
                
                SCRotZYXSwitch(this, true);
                BoatCheckRollEnergy(this);
                SCAddPos(this, &pos);
                SCAddRot(this, &rot);
                this->rot.y = shAngleRegulate(this->rot.y);
                if (sh2jms.player->status & (1 << SCP_STATUS_BIT_17)) {
                    BoatPlayerCheckControl();
                }
            }
            return;
    }
}



void shCharacterSetHumanBOTLow(SubCharacter* scp) {
    shCharacterSetFunction(scp, HumanBOTFunction);
    shCharacterBoatWorkInit();
    sh2bot.boat_p = scp;
}



void shCharacterBoatWorkInit(void) {
    shQzero(&sh2bot, sizeof(sh2bot));
}

#define BOAT_ANIME_ID_START 55
static int dboat_anime_adr_list[4] = {0, 33180, 79732, 0}; // size: 0x10, address: 0x371B90

int shCharacterHumanBOTAnimeSet(SubCharacter* scp, int anime_id) {
    AnimeInfo* aip; // r2

    if (shCharacterGetModelID(scp) == BOAT_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = (AnimeInfo*) &d_boat_anim[anime_id - BOAT_ANIME_ID_START];
        shCharacterAnimeSet(scp,
                            0,
                            2,
                            aip,
                            dboat_anime_adr_list[anime_id - BOAT_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - BOAT_ANIME_ID_START));
        return 0;
    }
    return -1;
}



void shUpdateBoatJamesPosAfterAnime(void) {
    shCharaInfo* cip; // r2

    if (sh2jms.player->status & (1 << SCP_STATUS_BIT_17)) {
        cip          = GetPlayerInfoForCameraCtrl();
        cip->pos     = sh2bot.boat_p->pos;
        cip->rot     = sh2bot.boat_p->rot;
        cip->pos_spd = sh2bot.boat_p->pos_spd;
        cip->rot_spd = sh2bot.boat_p->rot_spd;
        cip->mat     = sh2bot.boat_p->mat;
    }
}
