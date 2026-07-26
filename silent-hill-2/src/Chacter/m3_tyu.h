#ifndef M3_TYU_H
#define M3_TYU_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyTYULow(SubCharacter* scp);
int shCharacterEnemyTYUAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyTYUAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_TYU_H
