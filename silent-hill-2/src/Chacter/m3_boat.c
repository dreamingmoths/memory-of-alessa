#include "sh2_common.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh_vu0.h"

#include "Chacter/character.h"
#include "Chacter/sh2_battle_list.h"

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

static int dt_0x01202578; // size: 0x4, address: 0x1202578
static float dtf_0x01202570; // size: 0x4, address: 0x1202570

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
    if (sh2jms.player->status & (1 << 17)) {
        this->center_y = -10000.0f;
        this->eye_y = -10000.0f;
        return;
    }
    this->center_y = -10000.0f;
    this->eye_y = -10000.0f;
}

static void (* func_list_main_0x00371B78[3])(SubCharacter *) = {boat_both, boat_right, boat_left}; // size: 0xC, address: 0x371B78
static int anime_change_check_1323 = -1;
static int dboat_anime_adr_list[4] = {0x0, 33180, 79732, 0x0}; // size: 0x10, address: 0x371B90

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckSetParameter);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", boat_both);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", boat_right);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", boat_left);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckStatus);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckControl);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckAnimeSpeed);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", boat_anim_set_all);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckAnime);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckOarStatus);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckEffect);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckSound);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckRollEnergy);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", BoatCheckSetFirst);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", HumanBOTFunction);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", shCharacterSetHumanBOTLow);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", shCharacterBoatWorkInit);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", shCharacterHumanBOTAnimeSet);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_boat", shUpdateBoatJamesPosAfterAnime);
