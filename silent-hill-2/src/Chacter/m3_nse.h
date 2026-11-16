#ifndef M3_NSE_H
#define M3_NSE_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define NSE_PLAY_ANIME_ID_START 5500
#define NSE_PLAY_ANIM(id) (id + NSE_PLAY_ANIME_ID_START)

void shCharacterSetEnemyNSELow(SubCharacter* scp);
int shCharacterEnemyNSEAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyNSEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_NSE_H
