#ifndef M3_PLAY_EVENT_H
#define M3_PLAY_EVENT_H

#include "sh2_common.h"
#include "Chacter/character.h"

#define PJAMES_DRAMA_ANIME_ID_START 950

int PlayerNowDemoEventMode(void);
int PlayerEventButtonCheck(int button);
int PlayerEventDeadAnimeFinish(void);
int PlayerEventJamesDeadly(void);
int PlayerEventMariaDeadly(void);
int PlayerEventAnimeSuccessFrame(void);
void PlayerEventAnimeSet(int anime);
void PlayerEventAnimeSetDirect(int anime);
float PlayerEventMove(float* target);
int PlayerEventMoveIsEnd(void);
int PlayerEventMoveCancel(void);
int shCharacterHumanPJAMESAnimeSet(SubCharacter* scp, int anime_id);
void JamesWeaponSet(int wep);
int PlayerGetJamesWeapon(void);

#endif // M3_PLAY_EVENT_H
