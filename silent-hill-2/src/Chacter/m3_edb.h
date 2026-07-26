#ifndef M3_EDB_H
#define M3_EDB_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyEDBLow(SubCharacter* scp);
int shCharacterEnemyEDBAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyEDBAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyEDBAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_EDB_H
