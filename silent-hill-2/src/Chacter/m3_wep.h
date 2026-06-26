#ifndef M3_WEP_H
#define M3_WEP_H

#include "common.h"
#include "Chacter/character.h"

void shUpdateWeaponMatrixAfterAnime(SubCharacter* this, short kind /* r16 */); // I gave the name to the first arg

void shGetJamesWeaponStartPos(float* pos, float* vec);
void shGetJamesWeaponEndPos(float* pos /* r2 */, float* vec /* r2 */);
void shCharacterSetWeaponLow(SubCharacter* scp);

#endif // M3_WEP_H
