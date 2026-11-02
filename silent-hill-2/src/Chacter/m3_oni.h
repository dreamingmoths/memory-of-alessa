#ifndef M3_ONI_H
#define M3_ONI_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define ONI_PLAY_ANIME_ID_START 5400
#define ONI_PLAY_ANIM(id) (id + ONI_PLAY_ANIME_ID_START)

#define ONI_DRAMA_ANIME_ID_START 6350
#define ONI_DRAMA_ANIM(id) (id + ONI_DRAMA_ANIME_ID_START)

void shCharacterSetEnemyONILow(SubCharacter* scp);
int shCharacterEnemyONIAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterEnemyONIAnimeSetP(SubCharacter* scp, int anime_id, int comp);
void shGetEnemyONIAttackPos(SubCharacter* scp, float* s_pos, float* s_vec, u_short atk);

#endif // M3_ONI_H
