#ifndef M3_PLAY_EVENT_H
#define M3_PLAY_EVENT_H

#include "common.h"
#include "Chacter/character.h"

int PlayerNowDemoEventMode(void);
int PlayerEventButtonCheck(int button /* r2 */);
int PlayerEventDeadAnimeFinish(void);
int PlayerEventAnimeSuccessFrame(void);
int PlayerGetJamesWeapon(void);

#endif // M3_PLAY_EVENT_H
