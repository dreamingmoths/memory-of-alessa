#include "Chacter/m3_play.h"
#include "Chacter/m3_sc.h"

#include "Event/event.h"

#include "Multi_thr/pad/keydata.h"

#include "SH2_common/pad.h"
#include "SH2_common/playing_info.h"
#include "SH2_common/sh_vu0.h"

#include "shPad/lib_sh_pad.h"

#include "sound/sh_sound.h"

#include "vec.h"

static s_char PlayerCheckKeyInputRoundWay(void);
static u_char PlayerCheckKeyInputL180(void);
static u_char PlayerCheckKeyInputR180(void);
static u_char PlayerCheckKeyInputPrsAttack(void);
static u_char PlayerCheckKeyInputTrgAttack(void);
static u_char PlayerCheckKeyInputTrgLight(void);
static float PlayerCheckKeyInputStickDir(void);
static float PlayerCheckKeyStickClamp(float stick_val, float min, float max);
static float PlayerCheckKeyInputStickPow(void);
static u_char PlayerCheckKeyInputHold(u_char hold_prev, u_char hold);
static u_char PlayerCheckKeyInputDash(u_char dash);
static void PlayerCheckKeyInput(void);
static u_short PlayerDamageMotionNo(SubCharacter* this);
static void PlayerCheckSideLine(SubCharacter* this);
static void PlayerCheckFootLine(SubCharacter* this);
static void PlayerSetColumn_SetTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z);
static void PlayerSetColumn_CloseToTarget(CL_HITPOLY_COLUMN* mov, CL_HITPOLY_COLUMN* atk, float* mov_z, float* atk_z);
static void PlayerSetHitColumn(SubCharacter* this);
static void PlayerSetSearchArea(SubCharacter* this);
static void PlayerCheckDamage(SubCharacter* this);
static void PlayerCheckNeckAngle(SubCharacter* this);
static void PlayerCheckBodyAngle(SubCharacter* this);
static void PlayerCheckSetParameterPhase1(SubCharacter* this);
static void PlayerCheckSetParameterPhase2(SubCharacter* this);
static void PlayerCheckModelParts(void);
static void james_anim_set_all(AnimeInfo* aip, int comp_type);
static void james_anim_set(AnimeInfo* aip, int body_type, int comp_type);
static AnimeInfo* PlayerGetStageAnime(int anime);
static void PlayerCheckAnimeUpper(void);
static void PlayerCheckAnimeLower(void);
static void PlayerCheckAnime(void);
static void PlayerFunction(SubCharacter* this);
static void shGetJamesLightPos_Calc_Chest(void);
static void shGetJamesLightPos_Calc_Hand(void);
static void shGetJamesFootPos(float* pos, float* vec, int kind);

extern /* static */ int anime_change_check_upper; // @ 0x002A8DD0
extern /* static */ int anime_change_check_lower; // @ 0x002A8DD8
extern /* static */ AnimeInfo pjames_anim[34]; // size: 0x198, address: 0x0
extern /* static */ AnimeInfo pjames_hg_anim[11]; // size: 0x84, address: 0x0
extern /* static */ AnimeInfo pjames_sg_anim[17]; // size: 0xCC, address: 0x0
extern /* static */ AnimeInfo pjames_rg_anim[5]; // size: 0x3C, address: 0x0
extern /* static */ AnimeInfo pjames_sp_anim[17]; // size: 0xCC, address: 0x0
extern /* static */ AnimeInfo pjames_ka_anim[33]; // size: 0x18C, address: 0x0
extern /* static */ AnimeInfo pjames_pi_anim[33]; // size: 0x18C, address: 0x0
extern /* static */ AnimeInfo pjames_na_anim[17]; // size: 0xCC, address: 0x0
extern /* static */ AnimeInfo pjames_cs_anim[24]; // size: 0x120, address: 0x0
extern /* static */ AnimeInfo pjames_demo_anim[30]; // size: 0x168, address: 0x0

const static u_int pjames_act_with_wep_flag[9] = {
    0xFF, 0x55, 0x05, 0x00, 
    0xFF, 0xFF, 0x55, 0x05, 
    0x00
}; // size: 0x24, address: 0x0

const static u_int pjames_upper_flag[32] = {
    (1 << JMS_ST_U_RELAX)    | (1 << JMS_ST_U_ALERT)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_READY)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_READY)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_READY)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_READY)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_RUN2)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN2)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN3)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN),
    (1 << JMS_ST_U_STAND)    | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_RSRUN),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (1 << JMS_ST_U_HOLD),
    (1 << JMS_ST_U_READY)    | (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_RUN2)     | (1 << JMS_ST_U_RUN3)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_RELEASE),
    (1 << JMS_ST_U_ATTACK),
    NULL,
    (1 << JMS_ST_U_LROUND)   | (1 << JMS_ST_U_RROUND)   | (1 << JMS_ST_U_BACK)     | (1 << JMS_ST_U_WALK)     | (1 << JMS_ST_U_LSWALK)   | (1 << JMS_ST_U_RSWALK)   | (1 << JMS_ST_U_RUN1)     | (1 << JMS_ST_U_LSRUN)    | (1 << JMS_ST_U_RSRUN)    | (1 << JMS_ST_U_LTURN)    | (1 << JMS_ST_U_RTURN)    | (1 << JMS_ST_U_JUMP)     | (1 << JMS_ST_U_HOLD),
}; // size: 0x80, address: 0x0

const static u_int pjames_lower_flag[32] = {
    (1 << JMS_ST_L_RELAX)    | (1 << JMS_ST_L_ALERT)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_READY)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_READY)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_READY)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_READY)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD)     | (1 << JMS_ST_L_RELEASE),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD)     | (1 << JMS_ST_L_RELEASE),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_RUN2)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN2)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN3)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN),
    (1 << JMS_ST_L_STAND)    | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_RSRUN),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_HOLD)     | (1 << JMS_ST_L_RELEASE),
    (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP),
    (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_ATTACK),
    NULL,
    (1 << JMS_ST_L_LROUND)   | (1 << JMS_ST_L_RROUND)   | (1 << JMS_ST_L_BACK)     | (1 << JMS_ST_L_WALK)     | (1 << JMS_ST_L_LSWALK)   | (1 << JMS_ST_L_RSWALK)   | (1 << JMS_ST_L_RUN1)     | (1 << JMS_ST_L_LSRUN)    | (1 << JMS_ST_L_RSRUN)    | (1 << JMS_ST_L_LTURN)    | (1 << JMS_ST_L_RTURN)    | (1 << JMS_ST_L_JUMP)     | (1 << JMS_ST_L_HOLD),
    (1 << JMS_ST_L_EVENT)
}; // size: 0x80, address: 0x0

void player_flg_on(u_int* type, u_int status) {
    *type |= status;
}

void player_flg_off(u_int* type, u_int status) {
    *type &= ~status;
}

int upper_flg_on(u_int status) {
    return sh2jms.upper_st_flg & status;
}

int lower_flg_on(u_int status) {
    return sh2jms.lower_st_flg & status;
}

int u_anime_flg_on(u_int status) {
    return sh2jms.u_anime_st_flg & status;
}

int l_anime_flg_on(u_int status) {
    return sh2jms.l_anime_st_flg & status;
}

int actwithwep_flg_on(u_int status) {
    return sh2jms.act_with_wep & status;
}

void lower_st_set(int status, shPlayerWork* w) {
    w->lower_prev = w->lower_now;
    w->lower_now = status;
    sh2jms.non_input = 0.0f;
}

void upper_st_set(int status, shPlayerWork* w) {
    w->upper_prev = w->upper_now;
    w->upper_now = status;
}

void lower_flg_set(int status, shPlayerWork* w) {
    w->lower_st_flg = pjames_lower_flag[status];
}

void upper_flg_set(int status, shPlayerWork* w) {
    w->upper_st_flg = pjames_upper_flag[status];
}

void actwithwep_flg_set(u_char status, shPlayerWork* w) {
    w->act_with_wep = pjames_act_with_wep_flag[status];

    
    
    
    
    if ((status == 4) || (status == 5)) {
        if (sh2jms.map_mode) {
            player_flg_off(&w->act_with_wep, 1 << JMS_ST_U_RELAX);
            player_flg_off(&w->act_with_wep, 1 << JMS_ST_U_TIRED);
            player_flg_off(&w->act_with_wep, 1 << JMS_ST_U_READYOFF);
            player_flg_off(&w->act_with_wep, 1 << JMS_ST_U_RROUND);
        }
    }
}

void PlayerCheckInit(SubCharacter* this) {
    
        
    SCAnimeTypeSwitch(this, 1);
    
    
    this->battle.status |= 0x400;
    
    this->work[0] = sh2jms.weapon;
    
    sh2jms.hold_type = -1;
    sh2jms.lock_on = 0;
    actwithwep_flg_set(0, &sh2jms);
    
    sh2jms.now_cam_no = 0;
    sh2jms.cam_chg_flg = 0;
    
    
    sh2jms.allbody_now = 0;
    sh2jms.upper_now = 0xFF; // ~JMS_ST_U_STAND; ?
    sh2jms.lower_now = 0xFF; // ~JMS_ST_L_STAND; ?
    sh2jms.allbody_prev = 0xFF;
    sh2jms.upper_prev = 0xFF; // ~JMS_ST_U_STAND; ?
    sh2jms.lower_prev = 0xFF; // ~JMS_ST_L_STAND; ?
    sh2jms.event_status_now = 0xFF;
    sh2jms.event_status_prev = 0xFF;
    
    sh2jms.lower_st_flg = 0;
    sh2jms.upper_st_flg = JMS_ST_L_STAND;
    
    player_flg_on(&sh2jms.lower_st_flg, 1 << JMS_ST_L_STAND);
    player_flg_on(&sh2jms.upper_st_flg, 1 << JMS_ST_U_STAND);
    
    
    shQzero(sh2jms.pad, sizeof(PAD_INFO));
}

static s_char PlayerCheckKeyInputRoundWay(void) {
    PAD_INFO* pad = sh2jms.pad; // r4
    
    if ((pad[0].lround != 0) || (pad[0].lstickX < 0)) 
        return -1;    
    if ((pad[0].rround != 0) || (pad[0].lstickX > 0)) 
        return 1;    
    return 0;
}

static u_char PlayerCheckKeyInputL180(void) {
    int i; // r3
    int tmp; // r2 is it really needed?
    PAD_INFO* pad = sh2jms.pad; // r4

    if (pad[0].pad3d.lslide != 0) {
        if (pad[1].pad3d.lslide == 0) {
            return 2;
        }
        for (i = 2; i < 2; i++) {
            if (pad[i].pad3d.lslide == 0) {
                return 2;
            }
        }
        return 1;
    }

    return 0;
}

static u_char PlayerCheckKeyInputR180(void) {
    int i; // r3
    int tmp; // r2 is it really needed?
    PAD_INFO* pad = sh2jms.pad; // r4
    
    if (pad[0].pad3d.rslide != 0) {
        if (pad[1].pad3d.rslide == 0) {
            return 2;
        }
        for (i = 2; i < 2; i++) {
            if (pad[i].pad3d.rslide == 0) {
                return 2;
            }
        }
        return 1;
    }
    
    return 0;
}

static u_char PlayerCheckKeyInputPrsAttack(void) {
    int i; // r3
    u_char result; // r2
    u_char value; // r4
    PAD_INFO* pad; // r5
    
    value = 0;
    pad = sh2jms.pad;


    
    
    
    
    
    for (i = 0; i < 10; i++) {
        if (pad[i].attack0 == 0) {
            return 0;
        }
        value += pad[i].attack0;
    
    }
    result = ((value * 2) + 10) / 20;

    
    
    return result;
}

static u_char PlayerCheckKeyInputTrgAttack(void) {
    PAD_INFO* pad = sh2jms.pad; // r3
    
    if (pad[0].attack1 != 0) {
        return 0;
    }
    if (pad[0].attack0 != 0) {        
        if (pad[1].attack0 == 0) {
            return pad[0].attack0;
        }
    }
    
    return 0;
}

static u_char PlayerCheckKeyInputTrgLight(void) {
    PAD_INFO* pad = sh2jms.pad; // r3

    if (pad[0].light_ && !pad[1].light_) {
        return pad[0].light_;
    }    
    return 0;
}

static float PlayerCheckKeyInputStickDir(void) {
    PAD_INFO* pad = sh2jms.pad; // r4
    float y; // r1
    float x; // r29+0x10
    
    if (sh2jms.ctrl_unit == 1) {
        y = pad[0].lstickY;
        x = pad[0].lstickX;
    } else {
        if (pad[0].forward != 0) y = -127.0f;        
        if (pad[0].backward != 0) y = 127.0f;        
        if (pad[0].lround != 0) x = -127.0f;        
        if (pad[0].rround != 0) x = 127.0f;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    return shAtan2(-y, x);
}

static float PlayerCheckKeyStickClamp(float stick_val, float min, float max) {
    stick_val = (stick_val < min) ? min : ((stick_val > max) ? max : stick_val);
    return (stick_val - min) / (max - min);

}

static float PlayerCheckKeyInputStickPow(void) {
    float x, y, p; 
    PAD_INFO* pad = sh2jms.pad; // r4
   
    switch (sh2jms.ctrl_unit) {
        
        case 1:
            x = sh2jms.lstick_x;
            y = sh2jms.lstick_y;            
            break;
        case 0:
            x = y = 0.0f;
            
            
            
            
            
            
            if (pad[0].forward != 0) y = -1.0f;            
            if (pad[0].backward != 0) y = 1.0f;
            if (pad[0].lround != 0) x = -1.0f;
            if (pad[0].rround != 0) x = 1.0f;
        
            x = x * shSinF(pad[0].pad2d.dir);
            y = -y * shCosF(pad[0].pad2d.dir);
            break;
        default:
            x = y = 0.0f;
            break;
    }
    p = SQRT(x * x + y * y);
    return (p < 0.0f) ? 0.0f : ((p > 1.0f) ? 1.0f : p);
    
       
}

static u_char PlayerCheckKeyInputHold(u_char hold_prev, u_char hold) {
    if (playing.weapon_control == 0) {
        return hold;
    }
    if (shPadTrigger(0, key_config.ready) != 0) {
        return !hold_prev;
    }

        
    return hold_prev;
}

static u_char PlayerCheckKeyInputDash(u_char dash) {
    if (playing.walk_run_control == 0) {
        return dash;  
    } else {
        return !dash;
    }            
}

void PlayerCheckKeyInput(void) {
    s_char pad_local_org[4]; // r29+0x4C
    u_char pad_local[32]; // r29+0x20
    s_char asobi_x; // r3
    s_char asobi_y; // r2
    int i; // r5
    PAD_INFO* pad = sh2jms.pad; // r16
    shGameKeyData key; // r29+0x40


    
    
    
    
    
    
    
    
    
    
    for (i = 9; i > 0; i--) {
        sh2jms.pad[i] = sh2jms.pad[i - 1];
    }

    
    libShPadRead(0, 0, pad_local);
    shSysKeyNormalize(pad_local);

    for (i = 0; i < 4; i++) {
        pad_local_org[i] = pad_local[i + 4] - 0x80;
    }
    shSysKeyAdjust(pad_local);
    shGameKeyConvert(&key, pad_local);

    
    
    
    pad[0].skip  = pad_local[22];
    pad[0].pause = pad_local[22];
    pad[0].action = shPadTrigger(0, key_config.action);
    pad[0].attack0 = key.f.ACTION;

    if (sh2jms.weapon == 8) {
        pad[0].dash = 0;
    } else {
        pad[0].dash = PlayerCheckKeyInputDash((key.f.DASH != 0) ? 1 : 0);
    }

    pad[0].hold = PlayerCheckKeyInputHold(sh2jms.pad[1].hold, key.f.READY);
    pad[0].menu = shPadTrigger(0, key_config.item);
    pad[0].search = key.f.VIEW;
    pad[0].map = shPadTrigger(0, key_config.map);
    pad[0].light_ = key.f.LIGHT;
    pad[0].light = PlayerCheckKeyInputTrgLight();
    
    
    pad[0].rstickY = pad_local_org[1];
    pad[0].rstickX = pad_local_org[0];
    pad[0].lstickY = pad_local_org[3];
    pad[0].lstickX = pad_local_org[2];

    
    
    if (int_abs(pad[0].lstickY) < 0x26) pad[0].lstickY = 0;
    if (int_abs(pad[0].lstickX) < 0x26) pad[0].lstickX = 0;
    if (int_abs(pad[0].rstickY) < 0x26) pad[0].rstickY = 0;
    if (int_abs(pad[0].rstickX) < 0x26) pad[0].rstickX = 0;

    if (playing.control_type == 0) {
        asobi_x = int_abs(pad[0].lstickY) / 2;
        asobi_x = (asobi_x < 0) ? 0 : (asobi_x > 0x40) ? 0x40 : asobi_x;        
        asobi_y = int_abs(pad[0].lstickX) / 2;
        asobi_y = (asobi_y < 0) ? 0 : (asobi_y > 0x40) ? 0x40 : asobi_y;
            
        if (int_abs(pad[0].lstickY) < asobi_y) pad[0].lstickY = 0;        
        if (int_abs(pad[0].lstickX) < asobi_x) pad[0].lstickX = 0;
    } else {
        asobi_x = asobi_y = 0;
    }

    if (pad[0].lstickX >= 0) {
        
        sh2jms.lstick_x = PlayerCheckKeyStickClamp(pad[0].lstickX,
                                                   (asobi_x < 0x13) ? 0.0f : asobi_x,
                                                   104.0f);
    
    
    
    } else {
        
        sh2jms.lstick_x = -PlayerCheckKeyStickClamp(-pad[0].lstickX,
                                                    (asobi_x < 0x13) ? 0.0f : asobi_x,
                                                    104.0f);
    }

    
    if (pad[0].lstickY >= 0) {
        sh2jms.lstick_y = PlayerCheckKeyStickClamp(pad[0].lstickY,
                                                   0.0f,
                                                   104.0f);
    } else {
        sh2jms.lstick_y = -PlayerCheckKeyStickClamp(-pad[0].lstickY,
                                                    0.0f,
                                                    104.0f);
    }
    if (pad[0].rstickX >= 0) {
        sh2jms.rstick_x = PlayerCheckKeyStickClamp(pad[0].rstickX, 38.0f, 104.0f);
    } else {
        sh2jms.rstick_x = -PlayerCheckKeyStickClamp(-pad[0].rstickX, 38.0f, 104.0f);
    }
    if (pad[0].rstickY >= 0) {
        sh2jms.rstick_y = PlayerCheckKeyStickClamp(pad[0].rstickY, 38.0f, 104.0f);
    } else {
        sh2jms.rstick_y = -PlayerCheckKeyStickClamp(-pad[0].rstickY, 38.0f, 104.0f);
    }


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    pad[0].forward = pad_local[10];
    pad[0].backward = pad_local[11];
    pad[0].lround = pad_local[9];
    pad[0].rround = pad_local[8];

    
    
    
    if ((pad[0].forward == 0) && (pad[0].backward == 0) && (pad[0].lround == 0) && (pad[0].rround == 0) && ((pad[0].lstickX != 0) || (pad[0].lstickY != 0)))  {
        
        sh2jms.ctrl_unit = 1;
    } else {
        sh2jms.ctrl_unit = 0;
    }

    
    pad[0].attack1 = PlayerCheckKeyInputPrsAttack();
    pad[0].attack2 = PlayerCheckKeyInputTrgAttack();

    
    switch (playing.control_type) {

        case 0:
            pad[0].pad3d.lslide = key.f.LSLIDE;
            pad[0].pad3d.rslide = key.f.RSLIDE;
            
            pad[0].pad3d.lturn180 = PlayerCheckKeyInputL180();
            pad[0].pad3d.rturn180 = PlayerCheckKeyInputR180();
            pad[0].pad3d.round_way = PlayerCheckKeyInputRoundWay();
            break;

        case 1:            
            pad[0].pad2d.dir = PlayerCheckKeyInputStickDir();
        
            sh2jms.lstick_p = PlayerCheckKeyInputStickPow();
            break;
    }


    
    
    
    
    
    
    
    
    if ((sh2jms.player->status & 0x4000) != 0) {

        shQzero(pad, sizeof(PAD_INFO));

        if (sh2jms.event_anime == 0) {
            if (shPadTrigger(0, key_config.front_move) ||
                shPadTrigger(0, key_config.back_move) ||
                shPadTrigger(0, key_config.right_move) ||
                shPadTrigger(0, key_config.left_move) ||
                shPadTrigger(0, key_config.right_turn) ||
                shPadTrigger(0, key_config.left_turn) ||
                shPadTrigger(0, key_config.ready) ||
                key.f.AY != 0 ||
                key.f.AX != 0)
            {
                
                sh2jms.event_anime = 0;
                EventCancel();
            }
        }
    }






















}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerDamageMotionNo);

static void PlayerCheckSideLine(SubCharacter* this) {
    sceVu0FVECTOR sp; // r29+0x40
    sceVu0FVECTOR ep; // r29+0x50

    sp[0] = this->pos.x;
    sp[2] = this->pos.z;
    sp[1] = ep[1] = this->pos.y + -750.0; // mistake? 
    
    
    ep[0] = sp[0] + (600.0f * shSinF(QUARTER_TURN + this->rot.y));
    ep[2] = sp[2] + (600.0f * shCosF(QUARTER_TURN + this->rot.y));
    clCheckHitEyes(&sh2jms.r_side, (u32) this, sp, ep, 0);
    
    
    ep[0] = sp[0] + (600.0f * shSinF(this->rot.y - QUARTER_TURN));
    ep[2] = sp[2] + (600.0f * shCosF(this->rot.y - QUARTER_TURN));
    clCheckHitEyes(&sh2jms.l_side, (u32) this, sp, ep, 0);

}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckFootLine);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetHeightDummy);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetHeight);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetHeightConnectWait);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetColumn_SetTarget);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetColumn_CloseToTarget);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetHitColumn);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSetSearchArea);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckDamage);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckNeckAngle);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckBothArmsAngle);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @1248);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @1249);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckBodyAngle);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckSetParameterPhase1);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckSetParameterPhase2);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckModelParts);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", james_anim_set_all);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", james_anim_set);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerGetStageAnime);


const char rodata_2356_0x0038BEB0[] = "m3_play.c:3888> assert:(%s)\n";
const char rodata_assertion[] = "0";

/*
@todo: add lots of macros & clean this up!
*/
void PlayerCheckAnimeUpper(void) {
    SubCharacterDisp* scp_d = sh2jms.player; // r16
    AnimeInfo* aip;                          // r17

    if (!u_anime_flg_on(2) && (sh2jms.upper_now != anime_change_check_upper || u_anime_flg_on(0x40))) {
        switch (sh2jms.upper_now) {
            case JMS_ST_U_STAND: {
                aip = &pjames_anim[1];
                james_anim_set(aip, 1, 8);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            }
            
            case JMS_ST_U_LTURN:
                aip = &pjames_anim[10];
                james_anim_set(aip, 1, 2);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_RTURN:
                aip = &pjames_anim[9];
                james_anim_set(aip, 1, 2);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_LROUND:
                aip = &pjames_anim[3];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_RROUND:
                aip = &pjames_anim[2];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_WALK: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[4];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_LSWALK: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x19];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_RSWALK: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x18];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_BACK:
                aip = &pjames_anim[5];
                james_anim_set(aip, 1, 8);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_JUMP:
                aip = &pjames_anim[0x15];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_RUN1: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[6];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_RUN2: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[7];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_RUN3: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[8];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_LSRUN: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x1B];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_RSRUN: {
                int comp_type;
                if ((sh2jms.upper_prev >= 9) && (sh2jms.upper_prev < 0x11)) {
                    comp_type = 0xA;
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                } else {
                    comp_type = 8;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x1A];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            
            case JMS_ST_U_GUARD:
                aip = &pjames_anim[23];
                james_anim_set(aip, 1, 2);
                break;
            
            case JMS_ST_U_READY:
                aip = &pjames_anim[19];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_READYOFF:
                aip = &pjames_anim[20];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_ALERT: {
                int anime;
                if (sh2jms.weapon == 7) {
                    aip = &pjames_cs_anim[23];
                } else {
                    aip = &pjames_anim[18];
                }
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            }
            
            case JMS_ST_U_RELAX:
                aip = &pjames_anim[shCharacterAnimeGetInfo_(sh2jms.player, 2)->name - 0x64];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            
            case JMS_ST_U_HOLD: {
                int anime;
                int comp_type;
                int anime_on = 1;
                if (sh2jms.upper_prev == 0x1C) {
                    switch (sh2jms.weapon) {
                        case 1:
                            if ((sh2jms.lock_on == 0) && (sh2jms.reload == 0)) {
                                comp_type = 4;
                                sh2jms.hold_type = 0;
                                aip = &pjames_hg_anim[6];
                            } else {
                                if (sh2jms.reload == 0) {
                                    sh2jms.hold_type = 1;
                                } else {
                                    sh2jms.hold_type = 0;
                                    sh2jms.reload = 0;
                                }
                                anime_on = 0;
                            }
                            break;
                        case 2:
                            if ((sh2jms.hold_chg[0] != 0) && (sh2jms.shotgun_dir != sh2jms.shotgun_prev)) {
                                switch (sh2jms.shotgun_prev) {
                                    case 0:
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x10A;
                                        } else {
                                            anime = 0x108;
                                        }
                                        break;
                                    case 1:
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x105;
                                        } else {
                                            anime = 0x107;
                                        }
                                        break;
                                    case 2:
                                        if (sh2jms.shotgun_dir == 1) {
                                            anime = 0x106;
                                        } else {
                                            anime = 0x109;
                                        }
                                        break;
                                }
                                comp_type = 4;
                                sh2jms.shotgun_prev = sh2jms.shotgun_dir;
                                sh2jms.hold_type = 1;
                                aip = &pjames_sg_anim[anime - 0xFA];
                            } else {
                                anime_on = 0;
                            }
                            break;
                        case 3:
                            anime_on = 0;
                            break;
                        case 4:
                            shSdSeStop(0x2B27);
                            sh2jms.csaw_se_vol = 0.0f;
                            comp_type = 4;
                            aip = &pjames_sp_anim[(sh2jms.hold_loop[0] ? 0x1F9 : 0x1FB) - 0x1F4];
                            break;
                        case 5:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x169;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x16A;
                                    sh2jms.hold_type = 0;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x168;
                                } else {
                                    anime = 0x167;
                                }
                                comp_type = 4;
                            } else if (sh2jms.atk_type == 3) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x16F;
                                } else {
                                    anime = 0x175;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_ka_anim[anime - 0x15E];
                            break;
                        case 6:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x197;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x198;
                                    sh2jms.hold_type = 0;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x196;
                                } else {
                                    anime = 0x195;
                                }
                                comp_type = 4;
                            } else if (sh2jms.atk_type == 3) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x19D;
                                } else {
                                    anime = 0x1A3;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_pi_anim[anime - 0x190];
                            break;
                        case 8:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1C8;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x1C7;
                                    sh2jms.hold_type = 0;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1CA;
                                } else {
                                    anime = 0x1C9;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_na_anim[anime - 0x1C2];
                            break;
                        case 7:
                            shSdSeStop(0x2B25);
                            shSdSeStop(0x2B30);
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x233;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x234;
                                    sh2jms.hold_type = 0;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x230;
                                } else {
                                    anime = 0x22F;
                                }
                                comp_type = 2;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_cs_anim[anime - 0x226];
                            break;
                    }
                    if (anime_on != 0) {
                        james_anim_set(aip, 1, comp_type);
                        player_flg_on(&sh2jms.u_anime_st_flg, 2);
                    }
                } else {
                    if (sh2jms.upper_prev == 0x1B) {
                        comp_type = 6;
                    } else {
                        comp_type = 4;
                    }
                    switch (sh2jms.weapon) {
                        case 1:
                            if (u_anime_flg_on(0x40) != 0) {
                                anime = 0xCE;
                                sh2jms.hold_type = 0;
                            } else if (sh2jms.lock_on != 0) {
                                anime = 0xCB;
                                sh2jms.hold_type = 1;
                            } else {
                                anime = 0xC9;
                                sh2jms.hold_type = 0;
                            }
                            aip = &pjames_hg_anim[anime - 0xC8];
                            break;
                        case 2:
                            if ((sh2jms.hold_chg[0] != 0) && (sh2jms.shotgun_dir != sh2jms.shotgun_prev)) {
                                switch (sh2jms.shotgun_prev) {
                                    case 0:
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x10A;
                                        } else {
                                            anime = 0x108;
                                        }
                                        break;
                                    case 1:
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x105;
                                        } else {
                                            anime = 0x107;
                                        }
                                        break;
                                    case 2:
                                        if (sh2jms.shotgun_dir == 1) {
                                            anime = 0x106;
                                        } else {
                                            anime = 0x109;
                                        }
                                        break;
                                }
                            } else {
                                switch (sh2jms.shotgun_dir) {
                                    case 0:
                                        anime = 0x101;
                                        break;
                                    case 1:
                                        anime = 0xFB;
                                        break;
                                    case 2:
                                        anime = 0xFE;
                                        break;
                                }
                            }
                            sh2jms.shotgun_prev = sh2jms.shotgun_dir;
                            sh2jms.hold_type = 1;
                            aip = &pjames_sg_anim[anime - 0xFA];
                            break;
                        case 3:
                            sh2jms.hold_type = 1;
                            aip = &pjames_rg_anim[1];
                            break;
                        case 4:
                            if (sh2jms.hold_loop[0] != 0) {
                                anime = 0x1F9;
                            } else {
                                anime = 0x1F5;
                                sh2jms.hold_type = 1;
                            }
                            aip = &pjames_sp_anim[anime - 0x1F4];
                            break;
                        case 5:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x169;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x16A;
                                    sh2jms.hold_type = 0;
                                }
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x168;
                                } else {
                                    anime = 0x167;
                                }
                                comp_type = 4;
                            } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                anime = 0x15F;
                                sh2jms.hold_type = 1;
                            } else {
                                anime = 0x161;
                                sh2jms.hold_type = 0;
                            }
                            aip = &pjames_ka_anim[anime - 0x15E];
                            break;
                        case 6:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x197;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x198;
                                    sh2jms.hold_type = 0;
                                }
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x196;
                                } else {
                                    anime = 0x195;
                                }
                                comp_type = 4;
                            } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                anime = 0x191;
                                sh2jms.hold_type = 1;
                            } else {
                                anime = 0x193;
                                sh2jms.hold_type = 0;
                            }
                            aip = &pjames_pi_anim[anime - 0x190];
                            break;
                        case 8:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1C8;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x1C7;
                                    sh2jms.hold_type = 0;
                                }
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1CA;
                                } else {
                                    anime = 0x1C9;
                                }
                                comp_type = 4;
                            } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                anime = 0x1C3;
                                sh2jms.hold_type = 1;
                            } else {
                                anime = 0x1C5;
                                sh2jms.hold_type = 0;
                            }
                            aip = &pjames_na_anim[anime - 0x1C2];
                            break;
                        case 7:
                            if (sh2jms.hold_chg[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x233;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x234;
                                    sh2jms.hold_type = 0;
                                }
                            } else if (sh2jms.hold_loop[0] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x230;
                                } else {
                                    anime = 0x22F;
                                }
                                comp_type = 2;
                            } else {
                                sh2jms.csaw_se_vol = 0.7f;
                                SeCallPos(0x2B24, sh2jms.csaw_se_vol, &sh2jms.player->pos, 0);
                                if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                    anime = 0x227;
                                    sh2jms.hold_type = 1;
                                } else {
                                    anime = 0x22B;
                                    sh2jms.hold_type = 0;
                                }
                            }
                            aip = &pjames_cs_anim[anime - 0x226];
                            break;
                    }
                    james_anim_set(aip, 1, comp_type);
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                }
                sh2jms.atk_type = 0;
                break;
            }
            
            case JMS_ST_U_RELEASE: {
                int anim;
                int comp_type;

                switch (sh2jms.weapon) {
                    case 1:
                        if ((sh2jms.lock_on != 0) || ((sh2jms.upper_prev == 0x1C) && (sh2jms.reload == 0))) {
                            anim = 0xCC;
                            sh2jms.reload = 0;
                        } else {
                            anim = 0xCA;
                        }
                        aip = &pjames_hg_anim[anim - 0xC8];
                        break;
                    case 2:
                        switch (sh2jms.shotgun_dir) {
                            case 0:
                                anim = 0x102;
                                break;
                            case 1:
                                anim = 0xFC;
                                break;
                            case 2:
                                anim = 0xFF;
                                break;
                        }
                        aip = &pjames_sg_anim[anim - 0xFA];
                        break;
                    case 3:
                        anim = 0x12E;
                        aip = &pjames_rg_anim[2];
                        break;
                    case 4:
                        shSdSeStop(0x2B27);
                        sh2jms.csaw_se_vol = 0.0f;
                        anim = 0x1F6;
                        aip = &pjames_sp_anim[2];
                        break;
                    case 5:
                        if (sh2jms.hold_type == 0) {
                            anim = 0x162;
                        } else {
                            anim = 0x160;
                        }
                        aip = &pjames_ka_anim[anim - 0x15E];
                        break;
                    case 6:
                        if (sh2jms.hold_type == 0) {
                            anim = 0x194;
                        } else {
                            anim = 0x192;
                        }
                        aip = &pjames_pi_anim[anim - 0x190];
                        break;
                    case 8:
                        if (sh2jms.hold_type == 0) {
                            anim = 0x1C6;
                        } else {
                            anim = 0x1C4;
                        }
                        aip = &pjames_na_anim[anim - 0x1C2];
                        break;
                    case 7:
                        shSdSeStop(0x2B25);
                        shSdSeStop(0x2B30);
                        if (sh2jms.hold_type == 0) {
                            anim = 0x22E;
                        } else {
                            anim = 0x22A;
                        }
                        aip = &pjames_cs_anim[anim - 0x226];
                        break;
                }

                sh2jms.hold_type = -1;
                sh2jms.atk_type = 0;
                sh2jms.atk_reserve[1] = 0;

                if (sh2jms.weapon != 7) {
                    if (anim < scp_d->anime2.anim_a->name) {
                        comp_type = 4;
                    } else {
                        comp_type = 6;
                    }
                } else {
                    comp_type = 4;
                }
                james_anim_set(aip, 1, comp_type);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            }

            case JMS_ST_U_ATTACK: {
                int comp_type = 2;
                int anime;
                switch (sh2jms.weapon) {
                    case 1:
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            if (sh2jms.hold_type != 0) {
                                anime = 0xD2;
                            } else {
                                anime = 0xD1;
                            }
                            sh2jms.reload = 1;
                            sh2jms.hold_type = 0;
                        } else if ((sh2jms.hold_type == 1) || (u_anime_flg_on(0x40) != 0)) {
                            anime = 0xCF;
                        } else {
                            anime = 0xD0;
                        }
                        aip = &pjames_hg_anim[anime - 0xC8];
                        break;
                    case 2:
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            anime = 0x104;
                        } else {
                            switch (sh2jms.shotgun_dir) {
                                case 0:
                                    anime = 0x103;
                                    break;
                                case 1:
                                    anime = 0xFD;
                                    break;
                                case 2:
                                    anime = 0x100;
                                    break;
                            }
                        }
                        aip = &pjames_sg_anim[anime - 0xFA];
                        break;
                    case 3: {
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            anime = 0x130;
                        } else {
                            anime = 0x12F;
                        }
                        aip = &pjames_rg_anim[anime - 0x12C];
                        break;
                    }
                    case 4:
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            if (sh2jms.upper_prev == 0x1C) {
                                anime = 0x1FF;
                            } else {
                                anime = 0x1FE;
                            }
                        } else if (sh2jms.atk_count != 0) {
                            anime = 0x1FD;
                        } else {
                            anime = 0x1FC;
                        }
                        aip = &pjames_sp_anim[anime - 0x1F4];
                        break;
                    case 5:
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x16D;
                                    } else {
                                        anime = 0x16B;
                                    }
                                    break;
                                case 4:
                                    anime = 0x177;
                                    break;
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x173;
                                    } else {
                                        anime = 0x171;
                                    }
                                    break;
                                case 4:
                                    anime = 0x17B;
                                    break;
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if ((scp_d->anime2.anim_a->name != 0x171) && (scp_d->anime2.anim_a->name != 0x16B)) {
                                        int unknown = 0; // ?
                                    } else {
                                        scp_d->anime2.total_count = (scp_d->anime2.total_count - 0x4000);
                                    }
                                    if (sh2jms.hold_type != 0) {
                                        anime = 0x16E;
                                    } else {
                                        anime = 0x174;
                                    }
                                    break;
                                case 4:
                                    anime++;
                                    break;
                            }
                        }
                        aip = &pjames_ka_anim[anime - 0x15E];
                        break;
                    case 6:
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x19B;
                                    } else {
                                        anime = 0x199;
                                    }
                                    break;
                                case 4:
                                    anime = 0x1A5;
                                    break;
                                case 5:
                                    anime = 0x1AD;
                                    break;
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x1A1;
                                    } else {
                                        anime = 0x19F;
                                    }
                                    break;
                                case 4:
                                    anime = 0x1A9;
                                    break;
                                case 5:
                                    anime = 0x1AF;
                                    break;
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            switch (sh2jms.atk_type) {
                                case 3:
                                    anime = scp_d->anime2.anim_a->name;
                                    if ((anime != 0x19F) && (anime != 0x199)) {
                                        int unknown = 0;
                                    } else {
                                        scp_d->anime2.total_count = (scp_d->anime2.total_count - 0x6000);
                                    }
                                    if (sh2jms.hold_type != 0) {
                                        anime = 0x19C;
                                    } else {
                                        anime = 0x1A2;
                                    }
                                    break;
                                case 4:
                                case 5:
                                    anime++;
                                    break;
                            }
                        }
                        aip = &pjames_pi_anim[anime - 0x190];
                        break;
                    case 8:
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    anime = 0x1CB;
                                    break;
                                case 4:
                                    anime = 0x1CF;
                                    break;
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    anime = 0x1CD;
                                    break;
                                case 4:
                                    anime = 0x1D1;
                                    break;
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            anime++;
                        }
                        aip = &pjames_na_anim[anime - 0x1c2];
                        break;
                    case 7:
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    anime = 0x235;
                                    break;
                                case 5:
                                    anime = 0x239;
                                    break;
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3:
                                    anime = 0x237;
                                    break;
                                case 5:
                                    anime = 0x23B;
                                    break;
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            anime++;
                        } else {
                            SeCallPos(0x2B25, sh2jms.csaw_se_vol, &sh2jms.player->pos, 0);
                        }
                        aip = &pjames_cs_anim[anime - 0x226];
                        break;
                }
                sh2jms.strike_splash_flg = 0;
                james_anim_set(aip, 1, comp_type);
                break;
            }
            case JMS_ST_U_TIRED: {
                int comp_type;
                int anime;
                if (anime_change_check_upper == sh2jms.lower_now) {
                    comp_type = 0xA;
                    anime = 0x71;
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                } else {
                    comp_type = 4;
                    if (sh2jms.tired >= (((sh2jms.tired_max * 2) / 3))) {
                        anime = 0x72;
                    } else {
                        anime = 0x71;
                    }
                    player_flg_on(&sh2jms.u_anime_st_flg, 4);
                }
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 1, comp_type);
                break;
            }
            case JMS_ST_U_KICK: {
                int anime;
                int comp_type;
                if (sh2jms.atk_type == 7) {
                    anime = 0x85;
                } else {
                    anime = 0x84;
                }
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 1, 4);
                break;
                case JMS_ST_U_WALL_F:
                    switch (sh2jms.lower_prev) {
                        case 12:
                        case 13:
                        case 14:
                            anime = 0x80;

                            break;
                        case 16:
                            anime = 0x81;
                            break;
                        case 15:
                            anime = 0x82;
                            break;
                        default:
                            // @todo: un-comment when all rodata migrated
                            // mwcc won't deduplicate the strings here for some reason
                            if (!0) {
                                printf(rodata_2356_0x0038BEB0, rodata_assertion);
                                do { } while (1);
                            }
                            /* ASSERT_ON_LINE(0, 3888); */
                    }
                    player_flg_on(&sh2jms.u_anime_st_flg, 2);
                    aip = &pjames_anim[anime - 0x64];
                    james_anim_set(aip, 1, 4);
                    break;
            }
            case JMS_ST_U_FALL:
                aip = &pjames_anim[sh2jms.fall_type + 0xB];
                james_anim_set(aip, 1, 4);
                player_flg_on(&sh2jms.u_anime_st_flg, 2);
                break;
            case JMS_ST_U_DAMAGE: {
                int anime;
                switch (sh2jms.hug_status) {
                    case 0:
                    case 1:
                        anime = sh2jms.damage_no;
                        break;
                    case 2:
                        switch (sh2jms.player->battle.id) {
                            case 0x2F:
                            case 0x30:
                                anime = 0x4E3E;
                                break;
                            case 0x36:
                            case 0x37:
                                anime = 0x4E47;
                                break;
                            case 0x39:
                            case 0x3A:
                                if (sh2jms.hug_dir != 0) {
                                    anime = 0x4E4F;
                                } else {
                                    anime = 0x4E4B;
                                }
                                break;
                            case 0x3B:
                            case 0x3C:
                                anime = 0x4E56;
                                break;
                            case 0x3E:
                            case 0x3F:
                                anime = shCharacterAnimeGetInfo_(sh2jms.player, 2)->name;
                                break;
                        }
                        break;
                    case 3:
                    case 4:
                        switch (sh2jms.player->battle.id) {
                            case 0x30:
                            case 0x2F:
                                anime = (short)((sh2jms.dead != 0) ? 0x4E3F : 0x4E40);
                                break;
                            case 0x37:
                            case 0x36:
                                anime = (short)(sh2jms.dead != 0 ? 0x4E48 : 0x4E49);
                                break;
                            case 0x3A:
                            case 0x39:
                                if (sh2jms.dead != 0) {
                                    if (sh2jms.hug_dir != 0) {
                                        anime = 0x4E51;
                                    } else {
                                        anime = 0x4E4D;
                                    }
                                } else if (sh2jms.hug_dir != 0) {
                                    anime = 0x4E50;
                                } else {
                                    anime = 0x4E4C;
                                }
                                break;
                            case 0x3C:
                            case 0x3B:
                                anime = (short)(sh2jms.dead ? 0x4E57 : 0x4E59);
                                break;
                            case 0x3E:
                            case 0x3F:
                                anime = (short)(sh2jms.dead ? 0x4E27 : 0x4E53);
                                break;
                        }
                        break;
                }
                sh2jms.damage_no = anime;
                aip = PlayerGetStageAnime(anime);
                ASSERT_ON_LINE(aip, 3989);
                james_anim_set(aip, 1, 4);
                break;
            }
            case JMS_ST_U_EVENT: {
                int anime;
                int comp_type;
                if (sh2jms.event_move_mode != 0) {
                    switch (sh2jms.event_status_now) {
                        case 0:
                            anime = 0x65;
                            comp_type = 4;
                            break;
                        case 1:
                            anime = 0x68;
                            comp_type = (s_char)((sh2jms.event_status_prev == 2) ? 10 : 4);
                            break;
                        case 2:
                            anime = 0x6B;
                            comp_type = (s_char)((sh2jms.event_status_prev == 1) ? 10 : 4);
                            break;
                    }
                    if (comp_type == 4) {
                        player_flg_on(&sh2jms.u_anime_st_flg, 2);
                    } else {
                        player_flg_on(&sh2jms.u_anime_st_flg, 4);
                    }
                    aip = &pjames_anim[anime - 0x64];
                } else {
                    anime = (u_long)sh2jms.event_anime & 0x7FFFFFFF;

                    if (sh2jms.event_anime & 0x80000000) {
                        comp_type = 2;
                    } else {
                        player_flg_on(&sh2jms.u_anime_st_flg, 2);
                        comp_type = 4;
                    }
                    if (anime == 0x65) {
                        aip = &pjames_anim[anime - 0x64];
                    } else {
                        aip = PlayerGetStageAnime(anime);
                        ASSERT_ON_LINE(aip, 4038);
                    }
                }
                james_anim_set(aip, 1, comp_type);
                break;
            }
        }
        anime_change_check_upper = sh2jms.upper_now;
        player_flg_off(&sh2jms.u_anime_st_flg, 0x40);
    }
    if (scp_d->anime2.comp_type < 3 || 8 < scp_d->anime2.comp_type) {
        player_flg_off(&sh2jms.u_anime_st_flg, 2);
    }
    if (scp_d->anime2.comp_type < 9) {
        player_flg_off(&sh2jms.u_anime_st_flg, 4);
    }
    if (scp_d->anime2.comp_type == -1) {
        if (!(sh2jms.anime_pause & 8)) {
            sh2jms.anime_pause |= 2;
        }
    } else {
        sh2jms.anime_pause &= 5;
    }
    sh2jms.hold_chg[0] = 0;
    sh2jms.hold_loop[0] = 0;
}

void PlayerCheckAnimeLower(void) {
    SubCharacterDisp* scp_d = sh2jms.player; // r16
    AnimeInfo* aip;                          // r17

    if ((l_anime_flg_on(2) == 0) && ((sh2jms.lower_now != anime_change_check_lower) || (l_anime_flg_on(0x40) != 0))) {
        switch (sh2jms.lower_now) {
            case JMS_ST_L_STAND: {
                aip = &pjames_anim[1];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_LTURN: {
                aip = &pjames_anim[10];
                james_anim_set(aip, 2, 2);
                break;
            }
            case JMS_ST_L_RTURN: {
                aip = &pjames_anim[9];
                james_anim_set(aip, 2, 2);
                break;
            }
            case JMS_ST_L_LROUND: {
                aip = &pjames_anim[3];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_RROUND: {
                aip = &pjames_anim[2];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_WALK: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[4];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_LSWALK: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x19];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_RSWALK: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x18];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_BACK: {
                aip = &pjames_anim[5];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_JUMP: {
                aip = &pjames_anim[0x15];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_RUN1: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[6];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_RUN2: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[7];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_RUN3: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[8];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_LSRUN: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x1B];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_RSRUN: {
                int comp_type;
                if ((sh2jms.lower_prev >= 9) && (sh2jms.lower_prev < 0x11)) {
                    comp_type = 10;
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                } else {
                    comp_type = 4;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                }
                aip = &pjames_anim[0x1A];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_GUARD: {
                aip = &pjames_anim[0x17];
                james_anim_set(aip, 2, 2);
                break;
            }
            case JMS_ST_L_READY: {
                aip = &pjames_anim[0x13];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_READYOFF: {
                aip = &pjames_anim[0x14];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_ALERT: {
                if (sh2jms.weapon == 7) {
                    aip = &pjames_cs_anim[0x17];
                } else {
                    aip = &pjames_anim[0x12];
                }
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_RELAX: {
                int anime = (shRandI() % 3) + 0x73;
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_HOLD: {
                int anime;
                int comp_type;
                int anime_on = 1;
                if (sh2jms.lower_prev == 0x1C) {
                    switch (sh2jms.weapon) {
                        case 1: {
                            if ((sh2jms.lock_on == 0) && (sh2jms.reload == 0)) {
                                comp_type = 4;
                                aip = &pjames_hg_anim[6];
                            } else {
                                anime_on = 0;
                            }
                            break;
                        }
                        case 2: {
                            if ((sh2jms.hold_chg[1] != 0) && (sh2jms.shotgun_dir != sh2jms.shotgun_prev)) {
                                switch (sh2jms.shotgun_prev) {
                                    case 0: {
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x10A;
                                        } else {
                                            anime = 0x108;
                                        }
                                        break;
                                    }
                                    case 1: {
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x105;
                                        } else {
                                            anime = 0x107;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (sh2jms.shotgun_dir == 1) {
                                            anime = 0x106;
                                        } else {
                                            anime = 0x109;
                                        }
                                        break;
                                    }
                                }
                                comp_type = 4;
                                sh2jms.hold_type = 1;
                                aip = &pjames_sg_anim[anime - 0xFA];
                            } else {
                                anime_on = 0;
                            }
                            break;
                        }
                        case 3: {
                            anime_on = 0;
                            break;
                        }
                        case 4: {
                            comp_type = 4;
                            if (sh2jms.hold_loop[1]) {
                                anime = 0x1F9;
                            } else {
                                anime = 0x1FB;
                            }
                            aip = &pjames_sp_anim[anime - 0x1F4];
                            break;
                        }
                        case 5: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x169;
                                } else {
                                    anime = 0x16A;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x168;
                                } else {
                                    anime = 0x167;
                                }
                                comp_type = 4;
                            } else if (sh2jms.atk_type == 3) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x16F;
                                } else {
                                    anime = 0x175;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_ka_anim[anime - 0x15E];
                            break;
                        }
                        case 6: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x197;
                                } else {
                                    anime = 0x198;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x196;
                                } else {
                                    anime = 0x195;
                                }
                                comp_type = 4;
                            } else if (sh2jms.atk_type == 3) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x19D;
                                } else {
                                    anime = 0x1A3;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_pi_anim[anime - 0x190];
                            break;
                        }
                        case 8: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1C8;
                                } else {
                                    anime = 0x1C7;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1CA;
                                } else {
                                    anime = 0x1C9;
                                }
                                comp_type = 4;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_na_anim[anime - 0x1C2];
                            break;
                        }
                        case 7: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x233;
                                } else {
                                    anime = 0x234;
                                }
                                comp_type = 4;
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x230;
                                } else {
                                    anime = 0x22F;
                                }
                                comp_type = 2;
                            } else {
                                anime = 0;
                                anime_on = 0;
                            }
                            aip = &pjames_cs_anim[anime - 0x226];
                            break;
                        }
                    }
                    if (anime_on != 0) {
                        james_anim_set(aip, 2, comp_type);
                        player_flg_on(&sh2jms.l_anime_st_flg, 2);
                    }
                    break;
                } else {
                    if (sh2jms.lower_prev == 0x1B) {
                        comp_type = 6;
                    } else {
                        comp_type = 4;
                    }
                    switch ((u_char)sh2jms.weapon) {
                        case 1:
                            if (l_anime_flg_on(0x40) != 0) {
                                anime = 0xCE;
                            } else if ((sh2jms.lock_on != 0) || (sh2jms.hold_type == 1)) {
                                anime = 0xCB;
                            } else {
                                anime = 0xC9;
                            }
                            aip = &pjames_hg_anim[anime - 0xC8];
                            break;

                        case 2:
                            if ((sh2jms.hold_chg[1] != 0) && (sh2jms.shotgun_dir != sh2jms.shotgun_prev)) {
                                switch (sh2jms.shotgun_prev) {
                                    case 0: {
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x10a;
                                        } else {
                                            anime = 0x108;
                                        }
                                        break;
                                    }
                                    case 1: {
                                        if (sh2jms.shotgun_dir == 2) {
                                            anime = 0x105;
                                        } else {
                                            anime = 0x107;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (sh2jms.shotgun_dir == 1) {
                                            anime = 0x106;
                                        } else {
                                            anime = 0x109;
                                        }
                                        break;
                                    }
                                }
                            } else {
                                switch (sh2jms.shotgun_dir) {
                                    case 0: {
                                        anime = 0x101;
                                        break;
                                    }
                                    case 1: {
                                        anime = 0xFB;
                                        break;
                                    }
                                    case 2: {
                                        anime = 0xFE;
                                        break;
                                    }
                                }
                            }
                            aip = &pjames_sg_anim[anime - 0xFA];
                            break;

                        case 3: {
                            aip = &pjames_rg_anim[1];
                            break;
                        }
                        case 4: {
                            if (sh2jms.hold_loop[1]) {
                                anime = 0x1F9;
                            } else {
                                anime = 0x1F5;
                            }
                            aip = &pjames_sp_anim[anime - 0x1F4];
                            break;
                        }
                        case 5: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x169;
                                } else {
                                    anime = 0x16A;
                                }
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x168;
                                } else {
                                    anime = 0x167;
                                }
                                comp_type = 4;
                            } else {
                                anime = shCharacterAnimeGetInfo_(sh2jms.player, 1)->name;
                                if ((anime == 0x161) || (anime == 0x168)) {
                                    anime = 0x161;
                                } else {
                                    if ((anime == 0x15F) || (anime == 0x167)) {
                                        anime = 0x15F;
                                    } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                        anime = 0x15F;
                                    } else {
                                        anime = 0x161;
                                    }
                                }
                            }
                            aip = &pjames_ka_anim[anime - 0x15E];
                            break;
                        }
                        case 6: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x197;
                                } else {
                                    anime = 0x198;
                                }
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x196;
                                } else {
                                    anime = 0x195;
                                }
                                comp_type = 2;
                            } else {
                                anime = shCharacterAnimeGetInfo_(sh2jms.player, 1)->name;
                                if ((anime == 0x193) || (anime == 0x196)) {
                                    anime = 0x193;
                                } else {
                                    if ((anime == 0x191) || (anime == 0x195)) {
                                        anime = 0x191;
                                    } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                        anime = 0x191;
                                    } else {
                                        anime = 0x193;
                                    }
                                }
                            }
                            aip = &pjames_pi_anim[anime - 0x190];
                            break;
                        }
                        case 8: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1C8;
                                } else {
                                    anime = 0x1C7;
                                }
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x1CA;
                                } else {
                                    anime = 0x1C9;
                                }
                                comp_type = 4;
                            } else {
                                anime = shCharacterAnimeGetInfo_(sh2jms.player, 1)->name;
                                if ((anime == 0x1C5) || (anime == 0x1CA)) {
                                    anime = 0x1C5;
                                } else {
                                    if ((anime == 0x1C3) || (anime == 0x1C9)) {
                                        anime = 0x1C3;
                                    } else if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                        anime = 0x1C3;
                                    } else {
                                        anime = 0x1C5;
                                    }
                                }
                            }
                            aip = &pjames_na_anim[anime - 0x1C2];
                            break;
                        }
                        case 7: {
                            if (sh2jms.hold_chg[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x233;
                                } else {
                                    anime = 0x234;
                                }
                            } else if (sh2jms.hold_loop[1] != 0) {
                                if (sh2jms.hold_type == 0) {
                                    anime = 0x230;
                                } else {
                                    anime = 0x22F;
                                }
                                comp_type = 2;
                            } else {
                                int name = shCharacterAnimeGetInfo_(sh2jms.player, 1)->name;
                                anime = 0x22b;
                                switch (name) {
                                    case 0x22b:
                                        if (sh2jms.hold_type == -1) {
                                            anime = 0x22B;
                                        } else {
                                            anime = 0x22D;
                                        }
                                        break;

                                    case 0x230: {
                                        anime = 0x22D;
                                        break;
                                    }
                                    case 0x227: {
                                        if (sh2jms.hold_type == -1) {
                                            anime = 0x227;
                                        } else {
                                            anime = 0x229;
                                        }
                                        break;
                                    }

                                    case 0x22F:
                                        anime = 0x229;
                                        break;

                                    default:

                                        if ((sh2jms.r_side.kind == 1) && (sh2jms.l_side.kind != 1)) {
                                            if (sh2jms.hold_type == -1) {
                                                anime = 0x227;
                                            } else {
                                                anime = 0x229;
                                            }
                                            break;
                                        } else if (sh2jms.hold_type == -1) {
                                            anime = 0x22B;

                                        } else {
                                            anime = 0x22d;
                                        }

                                        break;
                                }
                            }
                            aip = &pjames_cs_anim[anime - 0x226];
                            break;
                        }

                        break;
                    }

                    james_anim_set(aip, 2, comp_type);
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                    break;
                }
            }
            case JMS_ST_L_RELEASE: {
                int anime;
                int comp_type;
                switch (sh2jms.weapon) {
                    case 1: {
                        if ((sh2jms.lock_on != 0) || ((sh2jms.lower_prev == 0x1C) && (sh2jms.reload == 0))) {
                            anime = 0xCC;
                        } else {
                            anime = 0xCA;
                        }
                        aip = &pjames_hg_anim[anime - 0xC8];
                        break;
                    }
                    case 2: {
                        switch (sh2jms.shotgun_dir) {
                            case 0: {
                                anime = 0x102;
                                break;
                            }
                            case 1: {
                                anime = 0xFC;
                                break;
                            }
                            case 2: {
                                anime = 0xFF;
                                break;
                            }
                        }
                        aip = &pjames_sg_anim[anime - 0xFA];
                        break;
                    }
                    case 3: {
                        anime = 0x12E;
                        aip = &pjames_rg_anim[2];
                        break;
                    }
                    case 4: {
                        anime = 0x1F6;
                        aip = &pjames_sp_anim[2];
                        break;
                    }
                    case 5: {
                        if (sh2jms.hold_type == 0) {
                            anime = 0x162;
                        } else {
                            anime = 0x160;
                        }
                        aip = &pjames_ka_anim[anime - 0x15E];
                        break;
                    }
                    case 6: {
                        if (sh2jms.hold_type == 0) {
                            anime = 0x194;
                        } else {
                            anime = 0x192;
                        }
                        aip = &pjames_pi_anim[anime - 0x190];
                        break;
                    }
                    case 8: {
                        if (sh2jms.hold_type == 0) {
                            anime = 0x1C6;
                        } else {
                            anime = 0x1C4;
                        }
                        aip = &pjames_na_anim[anime - 0x1C2];
                        break;
                    }
                    case 7: {
                        if (sh2jms.hold_type == 0) {
                            anime = 0x22E;
                        } else {
                            anime = 0x22A;
                        }
                        aip = &pjames_cs_anim[anime - 0x226];
                        break;
                    }
                }
                if (sh2jms.weapon != 7) {
                    if (anime < scp_d->anime.anim_a->name) {
                        comp_type = 4;
                    } else {
                        comp_type = 6;
                    }
                } else {
                    comp_type = 4;
                }
                james_anim_set(aip, 2, comp_type);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_ATTACK: {
                int anime;
                int comp_type = 2;
                switch (sh2jms.weapon) {
                    case 1: {
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            if (sh2jms.hold_type != 0) {
                                anime = 0xD2;
                            } else {
                                anime = 0xD1;
                            }
                        } else if ((sh2jms.hold_type == 1) || (l_anime_flg_on(0x40) != 0)) {
                            anime = 0xCF;
                        } else {
                            anime = 0xD0;
                        }
                        aip = &pjames_hg_anim[anime - 0xC8];
                        break;
                    }
                    case 2: {
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            anime = 0x104;
                        } else {
                            switch (sh2jms.shotgun_dir) {
                                case 0: {
                                    anime = 0x103;
                                    break;
                                }
                                case 1: {
                                    anime = 0xFD;
                                    break;
                                }
                                case 2: {
                                    anime = 0x100;
                                    break;
                                }
                            }
                        }
                        aip = &pjames_sg_anim[anime - 0xFA];
                        break;
                    }
                    case 3: {
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            anime = 0x130;
                        } else {
                            anime = 0x12F;
                        }
                        aip = &pjames_rg_anim[anime - 0x12C];
                        break;
                    }
                    case 4: {
                        if ((sh2jms.shoot_val == 0) && (sh2jms.reload_val != 0)) {
                            if (sh2jms.lower_prev == 0x1C) {
                                anime = 0x1FF;
                            } else {
                                anime = 0x1FE;
                            }
                        } else if (sh2jms.atk_count != 0) {
                            anime = 0x1FD;
                        } else {
                            anime = 0x1FC;
                        }
                        aip = &pjames_sp_anim[anime - 0x1F4];
                        break;
                    }
                    case 5: {
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x16D;
                                    } else {
                                        anime = 0x16B;
                                    }
                                    break;
                                }
                                case 4: {
                                    anime = 0x177;
                                    break;
                                }
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x173;
                                    } else {
                                        anime = 0x171;
                                    }
                                    break;
                                }
                                case 4: {
                                    anime = 0x17B;
                                    break;
                                }
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if ((scp_d->anime.anim_a->name != 0x171) && (scp_d->anime.anim_a->name != 0x16B)) {
                                        int unknown = 0;
                                    } else {
                                        scp_d->anime.total_count -= 0x4000;
                                    }
                                    if (sh2jms.hold_type != 0) {
                                        anime = 0x16E;
                                    } else {
                                        anime = 0x174;
                                    }
                                    break;
                                }
                                case 4: {
                                    anime++;
                                    break;
                                }
                            }
                        }
                        aip = &pjames_ka_anim[anime - 0x15E];
                        break;
                    }
                    case 6: {
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x19B;
                                    } else {
                                        anime = 0x199;
                                    }
                                    break;
                                }
                                case 4: {
                                    anime = 0x1A5;
                                    break;
                                }
                                case 5: {
                                    anime = 0x1AD;
                                    break;
                                }
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if (sh2jms.atk_count != 0) {
                                        anime = 0x1A1;
                                    } else {
                                        anime = 0x19F;
                                    }
                                    break;
                                }
                                case 4: {
                                    anime = 0x1A9;
                                    break;
                                }
                                case 5: {
                                    anime = 0x1AF;
                                    break;
                                }
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    if ((scp_d->anime.anim_a->name != 0x19F) && (scp_d->anime.anim_a->name != 0x199)) {
                                        int unknown = 0;
                                    } else {
                                        scp_d->anime.total_count -= 0x6000;
                                    }
                                    if (sh2jms.hold_type != 0) {
                                        anime = 0x19C;
                                    } else {
                                        anime = 0x1A2;
                                    }
                                    break;
                                }
                                case 4: {
                                }
                                case 5: {
                                    anime++;
                                    break;
                                }
                            }
                        }
                        aip = &pjames_pi_anim[anime - 0x190];
                        break;
                    }
                    case 8: {
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    anime = 0x1CB;
                                    break;
                                }
                                case 4: {
                                    anime = 0x1CF;
                                    break;
                                }
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    anime = 0x1CD;
                                    break;
                                }
                                case 4: {
                                    anime = 0x1D1;
                                    break;
                                }
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            anime++;
                        }
                        aip = &pjames_na_anim[anime - 0x1C2];
                        break;
                    }
                    case 7: {
                        if (sh2jms.hold_type != 0) {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    anime = 0x235;
                                    break;
                                }
                                case 5: {
                                    anime = 0x239;
                                    break;
                                }
                            }
                        } else {
                            switch (sh2jms.atk_type) {
                                case 3: {
                                    anime = 0x237;
                                    break;
                                }
                                case 5: {
                                    anime = 0x23B;
                                    break;
                                }
                            }
                        }
                        if (sh2jms.player->battle.atk_result != 0) {
                            comp_type = 6;
                            anime++;
                        }
                        aip = &pjames_cs_anim[anime - 0x226];
                        break;
                    }
                }
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_TIRED: {
                int anime;
                int comp_type;
                if (anime_change_check_lower == sh2jms.lower_now) {
                    comp_type = 10;
                    anime = 0x71;
                    player_flg_on(&sh2jms.l_anime_st_flg, 2);
                } else {
                    comp_type = 4;
                    if (sh2jms.tired >= (((sh2jms.tired_max * 2) / 3))) {
                        anime = 0x72;
                    } else {
                        anime = 0x71;
                    }
                    player_flg_on(&sh2jms.l_anime_st_flg, 4);
                }
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 2, comp_type);
                break;
            }
            case JMS_ST_L_KICK: {
                int anime;
                if (sh2jms.atk_type == 7) {
                    anime = 0x85;
                } else {
                    anime = 0x84;
                }
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 2, 4);
                break;
            }
            case JMS_ST_L_WALL_F: {
                int anime;
                switch (sh2jms.lower_prev) {
                    case 12:
                    case 13:
                    case 14: {
                        anime = 0x80;
                        break;
                    }
                    case 16: {
                        anime = 0x81;
                        break;
                    }
                    case 15: {
                        anime = 0x82;
                        break;
                    default:
                        // @todo: un-comment when all rodata migrated
                        // mwcc won't deduplicate the strings here for some reason
                        if (!0) {
                            printf("m3_play.c:5241> assert:(%s)\n", rodata_assertion);
                            do { } while (1);
                        }
                        // ASSERT_ON_LINE(0, 5241);
                    }
                }
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                aip = &pjames_anim[anime - 0x64];
                james_anim_set(aip, 2, 4);
                break;
            }
            case JMS_ST_L_FALL: {
                aip = &pjames_anim[sh2jms.fall_type + 0xB];
                james_anim_set(aip, 2, 4);
                player_flg_on(&sh2jms.l_anime_st_flg, 2);
                break;
            }
            case JMS_ST_L_DAMAGE: {
                int anime;
                switch (sh2jms.hug_status) {
                    case 0:
                    case 1:
                        anime = sh2jms.damage_no;
                        break;
                    case 2:
                        switch (sh2jms.player->battle.id) {
                            case 0x2F:
                            case 0x30:
                                anime = 0x4E3E;
                                break;
                            case 0x36:
                            case 0x37:
                                anime = 0x4E47;
                                break;
                            case 0x39:
                            case 0x3A:
                                if (sh2jms.hug_dir != 0) {
                                    anime = 0x4E4F;
                                } else {
                                    anime = 0x4E4B;
                                }
                                break;
                            case 0x3B:
                            case 0x3C:
                                anime = 0x4E56;
                                break;
                            case 0x3E:
                            case 0x3F:
                                anime = ((short)((!(shRandI() & 1) ? 0x4E55 : 0x4E54)));
                                break;
                        }
                        break;
                    case 3:
                    case 4:
                        switch (sh2jms.player->battle.id) {
                            case 0x30:
                            case 0x2F:
                                anime = (short)((sh2jms.dead != 0) ? 0x4E3F : 0x4E40);
                                break;
                            case 0x37:
                            case 0x36:
                                anime = (short)(sh2jms.dead != 0 ? 0x4E48 : 0x4E49);
                                break;
                            case 0x3A:
                            case 0x39:
                                if (sh2jms.dead != 0) {
                                    if (sh2jms.hug_dir != 0) {
                                        anime = 0x4E51;
                                    } else {
                                        anime = 0x4E4D;
                                    }
                                } else if (sh2jms.hug_dir != 0) {
                                    anime = 0x4E50;
                                } else {
                                    anime = 0x4E4C;
                                }
                                break;
                            case 0x3C:
                            case 0x3B:
                                anime = (short)(sh2jms.dead ? 0x4E57 : 0x4E59);
                                ;
                                break;
                            case 0x3E:
                            case 0x3F:
                                anime = (short)(sh2jms.dead ? 0x4E27 : 0x4E53);
                                break;
                        }
                        break;
                }
                aip = PlayerGetStageAnime(anime);
                ASSERT_ON_LINE(aip, 5341);
                james_anim_set(aip, 2, 2);
                break;
            }
            case JMS_ST_L_EVENT: {
                int anime;
                int comp_type;
                if (sh2jms.event_move_mode != 0) {
                    switch (sh2jms.event_status_now) {
                        case 0: {
                            anime = 0x65;
                            comp_type = 4;
                            break;
                        }
                        case 1: {
                            anime = 0x68;
                            if (sh2jms.event_status_prev == 2) {
                                comp_type = 10;
                            } else {
                                comp_type = 4;
                            }
                            comp_type = (s_char)comp_type;
                            break;
                        }
                        case 2: {
                            anime = 0x6B;
                            if (sh2jms.event_status_prev == 1) {
                                comp_type = 10;
                            } else {
                                comp_type = 4;
                            }
                            comp_type = (s_char)comp_type;
                            break;
                        }
                    }
                    if (comp_type == 4) {
                        player_flg_on(&sh2jms.l_anime_st_flg, 2);
                    } else {
                        player_flg_on(&sh2jms.l_anime_st_flg, 4);
                    }
                    aip = &pjames_anim[anime - 0x64];
                    sh2jms.event_anime = anime;
                } else {
                    anime = (u_long)sh2jms.event_anime & 0x7FFFFFFF;

                    if (sh2jms.event_anime & 0x80000000) {
                        comp_type = 2;
                    } else {
                        comp_type = 4;
                        player_flg_on(&sh2jms.l_anime_st_flg, 2);
                    }
                    if (anime == 0x65) {
                        aip = &pjames_anim[anime - 0x64];
                    } else {
                        aip = PlayerGetStageAnime(anime);
                        ASSERT_ON_LINE(aip, 5390);
                    }
                }
                james_anim_set(aip, 2, comp_type);
                break;
            }
        }
        anime_change_check_lower = sh2jms.lower_now;
        player_flg_off(&sh2jms.l_anime_st_flg, 0x40);
    }
    if (scp_d->anime.comp_type < 3 || 6 < scp_d->anime.comp_type) {
        player_flg_off(&sh2jms.l_anime_st_flg, 2);
    }
    if (scp_d->anime.comp_type < 9) {
        player_flg_off(&sh2jms.l_anime_st_flg, 4);
    }
    if (scp_d->anime.comp_type == -1) {
        if (!(sh2jms.anime_pause & 4)) {
            sh2jms.anime_pause |= 1;
        }
    } else {
        sh2jms.anime_pause &= 10;
    }
    sh2jms.hold_chg[1] = 0;
    sh2jms.hold_loop[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckAnime);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", BoatPlayerCheckAnime);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerFunction);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesLightPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesLightPosOriginal);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesLightPos_Calc_Chest);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesLightPos_Calc_Hand);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesLightPos_Calc);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", GetPlayerPartsMatrixForCameraCtrl);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", GetPlayerPartsWorldMatrix);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", GetPlayerPartsLocalMatrix);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", GetPlayerInfoForCameraCtrl);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shCharacterPlayerWorkInitAtPowerOn);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shCharacterPlayerWorkInitAtGameStart);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shCharacterSetPlayerLow);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerGetTargetInfo);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerGetTarget);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerChangeTarget);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckHuggingAttack);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerChectGuardSuccess);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @3326);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @3350);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @3351);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @3495);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerRequestAttack);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerRequestAttackFinish);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerCheckStraightLine);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesFootPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesKickStartPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", shGetJamesTrampStartPos);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerNowItemName);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerSearchVIewButtonCheck);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerGetNeckAngleX);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerGetNeckAngleY);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerInitOnConnect);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerStatusClear);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", close_to_angle_target);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", close_to_value);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerReverseLightCalcIsOn);

INCLUDE_ASM("asm/nonmatchings/Chacter/m3_play", PlayerWaterRoadIsOn);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @905_0x0038C2D0);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @906_0x0038C2F0);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @2145);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @2146_0x0038C330);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @2147);

INCLUDE_RODATA("asm/nonmatchings/Chacter/m3_play", @2148);
