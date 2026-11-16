#ifndef M3_MKN_H
#define M3_MKN_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define MANNEQUIN_PLAY_ANIME_ID_START 5100
#define MANNEQUIN_PLAY_ANIM(id) (id + MANNEQUIN_PLAY_ANIME_ID_START)

#define MANNEQUIN_DRAMA_ANIME_ID_START 6100
#define MANNEQUIN_DRAMA_ANIM(id) (id + MANNEQUIN_DRAMA_ANIME_ID_START)

void shCharacterSetEnemyMKNLow(SubCharacter* scp);
int shCharacterEnemyMKNAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyMKNAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyMKNAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);
void shEnemyMKN_EffectFoot(SubCharacter* scp, int type);

#endif // M3_MKN_H
