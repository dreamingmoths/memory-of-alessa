#ifndef M3_NSE_H
#define M3_NSE_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyNSELow(SubCharacter* scp);
int shCharacterEnemyNSEAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyNSEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec);

#endif // M3_NSE_H
