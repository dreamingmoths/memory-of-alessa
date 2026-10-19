#ifndef M3_BOAT_H
#define M3_BOAT_H

#include "Chacter/character.h"

void bot_flg_on(u_int* type, u_int status);

void bot_flg_off(u_int* type, u_int status);

int bot_anime_flg_on(u_int status);

void bot_st_set(int status, shBoatWork* w);

void shCharacterSetHumanBOTLow(SubCharacter* scp);

void shCharacterBoatWorkInit(void);

int shCharacterHumanBOTAnimeSet(SubCharacter* scp, int anime_id);

void shUpdateBoatJamesPosAfterAnime(void);

#endif // M3_BOAT_H
