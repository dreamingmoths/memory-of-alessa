#ifndef M3_IKE_H
#define M3_IKE_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyIKELow(SubCharacter* scp);
int shCharacterEnemyIKEAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyIKEAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyIKEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk); // 4th arg not present in DWARF

#endif // M3_IKE_H
