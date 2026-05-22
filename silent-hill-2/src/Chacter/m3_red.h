#ifndef M3_RED_H
#define M3_RED_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetEnemyREDLow(SubCharacter* scp);
void shCharacterSetWeaponRED(SubCharacter* scp, int on_off);

int shCharacterEnemyREDAnimeSetP(SubCharacter* scp /* r17 */, int anime_id /* r18 */, int comp /* r16 */);

#endif // M3_RED_H
