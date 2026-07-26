#ifndef M3_SCU_H
#define M3_SCU_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemySCULow(SubCharacter* scp);
int shCharacterEnemySCUAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemySCUAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemySCUAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);
void shEnemySCU_EffectFoot(SubCharacter* scp, int type);

#endif // M3_SCU_H
