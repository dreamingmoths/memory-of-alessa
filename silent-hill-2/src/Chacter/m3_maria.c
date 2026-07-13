#include "sh2_common.h"
#include "SH2_common/sh_vu0.h"
#include "SH2_common/playing_info.h"

#include "Chacter/character.h"
#include "Chacter/chara_list.h"
#include "Chacter/sh2_battle_list.h"
#include "Chacter/m3_sc.h"

#include "sound/sh_sound.h"

/* @note: values are for Letter From Silent Heaven, unconfirmed for Born From A Wish */

#define SH2_MARIA_LFSH_HP_MAX_EASY    160.0f
#define SH2_MARIA_LFSH_HP_MAX_NORMAL  80.0f
#define SH2_MARIA_LFSH_TIRED_MAX      600
#define MARIA_DRAMA_ANIME_ID_START    40

/* @todo: migrate data */
extern /* static */ AnimeInfo pmaria_anim_0x00396AB0[40]; // size: 0x1E0, address: 0x396AB0
extern /* static */ AnimeInfo pmaria_anim[40]; // size: 0x1E0, address: 0x396AB0
extern /* static */ AnimeInfo d_mar_anim[7]; // size: 0x54, address: 0x396C90
extern /* static */ int dmar_anime_adr_list[7]; // size: 0x1C, address: 0x34C260

static int HumanMARInit(SubCharacter* scp /* r16 */) {
    SCAnimeTypeSwitch(scp, 1);
    SCLightOnNowSwitch(scp, 1);

    scp->battle.status |= 1 << 10;
    sh2mar.active_type = 2;

    return 0;
}

static void HumanMARFunction(SubCharacter* this /* r16 */) {
    AnimeInfo* aip; // r17
    sceVu0FVECTOR pos; // r29+0x30
    sceVu0FVECTOR rot; // r29+0x40

    switch (this->step) {
        case 0:
            volatile_vec_copy(&pos, &this->pos);
            volatile_vec_copy(&rot, &this->rot);
            HumanMARInit(this);
            SCAnimeTypeSwitch(this, 1);

            aip = &pmaria_anim_0x00396AB0[1];
            shCharacterAnimeSet(this, 0, 0, aip, (int) shCharacterGetAnimeAdrForPlay(this));
            volatile_vec_copy(&this->pos, &pos);
            volatile_vec_copy(&this->rot, &rot);
            MariaCheckSetParameterPhase2(this);
            this->step++;
            return;

        case 1:
            // @todo: add status defines
            if ((this->status & (1 << 2)) && !(this->status & (1 << 13))) {
                MariaCheckDamage(this);
                MariaCheckSetParameterPhase1(this);
                MariaCheckControl(this);
                MariaCheckAnime(this);
                MariaUpdatePosition(this);
                MariaCheckSetParameterPhase2(this);
                MariaCheckSound();
            }
            return;
    }
}

void shCharacterSetHumanMARLow(SubCharacter* scp /* r16 */) {
    shCharacterSetFunction(scp, HumanMARFunction);
    sh2mar.mar_p = scp;
    sh2mar.mar_p->battle.hp = sh2mar.hp;
    sh2mar.mar_p->battle.hp_max = sh2mar.hp_max;
}

int shCharacterHumanMARAnimeSet(SubCharacter* scp /* r17 */, int anime_id /* r16 */) {
    AnimeInfo* aip; // r2

    if (shCharacterGetModelID(scp) == LLL_MAR_CHARA_KIND) {
        SCAnimeTypeSwitch(scp, 0);
        aip = &d_mar_anim[anime_id - MARIA_DRAMA_ANIME_ID_START];
        shCharacterAnimeSet(scp, 0, 2, aip, dmar_anime_adr_list[anime_id - MARIA_DRAMA_ANIME_ID_START] + (int) shCharacterGetAnimeAdrForDrama(scp, anime_id - MARIA_DRAMA_ANIME_ID_START));
        return 0;
    }

    return -1;
}

void shCharacterMariaWorkInit(void) {
    shQzero(&sh2mar, sizeof(sh2mar));
}

void shCharacterMariaWorkInitAtGameStart(void) {
    switch (playing.battle_level) {
        case SH2_BATTLE_LEVEL_BEGINNER:
        case SH2_BATTLE_LEVEL_EASY:
            sh2mar.hp = sh2mar.hp_max = SH2_MARIA_LFSH_HP_MAX_EASY;
            break;
        case SH2_BATTLE_LEVEL_NORMAL:
        case SH2_BATTLE_LEVEL_HARD:
            sh2mar.hp = sh2mar.hp_max = SH2_MARIA_LFSH_HP_MAX_NORMAL;
            break;
    }

    sh2mar.tired_max = SH2_MARIA_LFSH_TIRED_MAX;
    sh2mar.main_status_now = 0;
    sh2mar.main_status_prev = 0;
    sh2mar.sub_status_now = 0;
    sh2mar.sub_status_prev = 0;

    mar_flg_on(&sh2mar.sub_st_flg, 1 << MAR_SUB_ST_STAND);
    mar_sub_st_set(MAR_SUB_ST_STAND, &sh2mar);
    mar_sub_flg_set(MAR_SUB_ST_STAND, &sh2mar);

    // @todo: add defines for these?
    sh2mar.column_atk.kind = 1;
    sh2mar.column_mov.kind = 1;
    sh2mar.column_atk.weight = 2;
    sh2mar.column_mov.weight = 2;
    sh2mar.column_atk.material = 6;
    sh2mar.column_mov.material = 6;
    sh2mar.column_atk.shape = 3;
    sh2mar.column_mov.shape = 3;
    sh2mar.column_atk.p[1][3] = 150.0f;
    sh2mar.column_mov.p[1][3] = 150.0f;
}
