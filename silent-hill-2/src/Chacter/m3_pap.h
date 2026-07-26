#ifndef M3_PAP_H
#define M3_PAP_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyPAPLow(SubCharacter* scp);
int shCharacterEnemyPAPAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyPAPAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyPAPAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_PAP_H
