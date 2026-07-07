#ifndef M3_MARIA_H
#define M3_MARIA_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetHumanMARLow(SubCharacter* scp);
int shCharacterHumanMARAnimeSet(SubCharacter* scp, int anime_id);
void shCharacterMariaWorkInit(void);
void shCharacterMariaWorkInitAtGameStart(void);

#endif // M3_MARIA_H
