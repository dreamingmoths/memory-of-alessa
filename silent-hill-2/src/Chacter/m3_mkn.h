#ifndef M3_MKN_H
#define M3_MKN_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyMKNLow(SubCharacter* scp);
int shCharacterEnemyMKNAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyMKNAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyMKNAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);
void shEnemyMKN_EffectFoot(SubCharacter* scp, int type);

#endif // M3_MKN_H
