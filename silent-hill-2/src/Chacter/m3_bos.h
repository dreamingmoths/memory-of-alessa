#ifndef M3_BOS_H
#define M3_BOS_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyBOSLow(SubCharacter* scp);
int shCharacterEnemyBOSAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyBOSAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyBOSAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_BOS_H
