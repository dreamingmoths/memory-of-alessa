#ifndef ANIME_H
#define ANIME_H

#include "common.h"
#include "Chacter/character.h"
#include "Chacter/skelton.h"
#include "Chacter_Draw/clani.h"

typedef union /* @anon3 */ {
    int i; // offset 0x0, size 0x4
    float f; // offset 0x0, size 0x4
} FloatOrInt;

void shCharacterStayModelExecItem(shSkelton* stp, float* rot);

void shCharacterStayModelExecNthParts(shSkelton* stp, float* pos, float* rot);

void shCharacterAnimePartsControl(shAnime3d* ap, shSkelton* stp /* r16 */, Vector4* rot /* r2 */); // first arg not present in dwarf

void shCharacterAnimeSetSkelton(shAnime3d* ap, shSkelton* stp);

int shCharacterDramaAnimeExecMain(shAnime3d* ap);

int shCharacterPlayingAnimeExecMain(shAnime3d* ap, int type);

void shCharacterStayModelScale(shAnime3d* ap);

#endif // ANIME_H
