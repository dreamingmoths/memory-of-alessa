#ifndef M3_PLAY_EVENT_H
#define M3_PLAY_EVENT_H

#include "common.h"
#include "Chacter/character.h"

int PlayerNowDemoEventMode(void);
int PlayerEventButtonCheck(int button /* r2 */);
int PlayerEventDeadAnimeFinish(void);
int PlayerEventJamesDeadly(void);
int PlayerEventMariaDeadly(void);
int PlayerEventAnimeSuccessFrame(void);
void PlayerEventAnimeSet(int anime /* r16 */);
void PlayerEventAnimeSetDirect(int anime /* r16 */);
int PlayerEventMoveIsEnd(void);
int PlayerEventMoveCancel(void);
void JamesWeaponSet(int wep /* r2 */);
int PlayerGetJamesWeapon(void);

#endif // M3_PLAY_EVENT_H
