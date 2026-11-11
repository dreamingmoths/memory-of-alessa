#ifndef M3_ARM_H
#define M3_ARM_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define ARM_PLAY_ANIME_ID_START 5250
#define ARM_PLAY_ANIM(id) (id + ARM_PLAY_ANIME_ID_START)

void shCharacterSetEnemyARMLow(SubCharacter* scp);
int shCharacterEnemyARMAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyARMAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_ARM_H
