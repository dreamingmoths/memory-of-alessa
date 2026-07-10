#ifndef M3_INU_H
#define M3_INU_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetHumanINULow(SubCharacter* scp);
int shCharacterHumanINUAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterHumanINUAnimeSetP(SubCharacter* scp, int anime_id, int comp);

#endif // M3_INU_H
