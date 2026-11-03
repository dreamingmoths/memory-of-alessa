#ifndef M3_RPJAMES_H
#define M3_RPJAMES_H

#include "sh2_common.h"
#include "Chacter/character.h"

void shCharacterSetHumanRPJMSLow(SubCharacter* scp);
void shGetJamesLightPos_Calc_Reverse(void);
void shGetJamesLightPosOriginal_Reverse(float* pos, float* vec);
void PlayerSetReverseMode(void);

#endif // M3_RPJAMES_H
