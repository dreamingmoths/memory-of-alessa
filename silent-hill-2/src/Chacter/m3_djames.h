#ifndef M3_DJAMES_H
#define M3_DJAMES_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define DJAMES_DRAMA_ANIME_ID_START 1000
#define DJAMES_DRAMA_ANIM(id) (id + DJAMES_DRAMA_ANIME_ID_START)

void DemoPlayerSetHeight(SubCharacter* this);
void shCharacterSetHumanDJMSLow(SubCharacter* scp);

#endif // M3_DJAMES_H
