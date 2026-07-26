#ifndef M3_ONI_H
#define M3_ONI_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyONILow(SubCharacter* scp);
int shCharacterEnemyONIAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyONIAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyONIAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_ONI_H
