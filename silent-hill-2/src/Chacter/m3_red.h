#ifndef M3_RED_H
#define M3_RED_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyREDLow(SubCharacter* scp);
void shCharacterSetWeaponRED(SubCharacter* scp, int on_off);
int shCharacterEnemyREDAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyREDAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);
void shGetEnemyREDAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_RED_H
