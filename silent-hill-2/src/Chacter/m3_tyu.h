#ifndef M3_TYU_H
#define M3_TYU_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define TYU_PLAY_ANIME_ID_START 5200
#define TYU_PLAY_ANIM_5201      5201
#define TYU_PLAY_ANIM(id)       (id + TYU_PLAY_ANIME_ID_START)

void shCharacterSetEnemyTYULow(SubCharacter* scp);
int shCharacterEnemyTYUAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyTYUAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_TYU_H
