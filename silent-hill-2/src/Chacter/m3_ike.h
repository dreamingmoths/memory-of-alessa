#ifndef M3_IKE_H
#define M3_IKE_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define IKE_PLAY_ANIME_ID_START 5600
#define IKE_PLAY_ANIM(id) (id + IKE_PLAY_ANIME_ID_START)

#define IKE_DRAMA_ANIME_ID_START 6500
#define IKE_DRAMA_ANIM(id) (id + IKE_DRAMA_ANIME_ID_START)

void shCharacterSetEnemyIKELow(SubCharacter* scp);
int shCharacterEnemyIKEAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyIKEAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyIKEAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk); // @note: 4th arg not present in DWARF

#endif // M3_IKE_H
