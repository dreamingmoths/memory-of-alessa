#ifndef M3_BGOBJ_H
#define M3_BGOBJ_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define BACKGROUND_OBJECT_DRAMA_ANIME_ID_START  10000
#define BACKGROUND_OBJECT_DRAMA_ANIM(id) (id + BACKGROUND_OBJECT_DRAMA_ANIME_ID_START)

#define BACKGROUND_OBJECT_PLAY_ANIME_ID_START   10247
#define BACKGROUND_OBJECT_PLAY_ANIM(id) (id + BACKGROUND_OBJECT_PLAY_ANIME_ID_START)

void shCharacterSetObjectLow(SubCharacter* scp);
int shCharacterObjectAnimeSet(SubCharacter* scp, int anime_id);
int shCharacterObjectAnimeSetP(SubCharacter* scp, int anime_id);
void shCharacterSetRObjectLow(SubCharacter* scp);

#endif // M3_BGOBJ_H
