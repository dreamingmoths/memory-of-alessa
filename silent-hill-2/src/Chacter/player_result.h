#ifndef PLAYER_RESULT_H
#define PLAYER_RESULT_H

#include "common.h"
#include "Chacter/character.h"

void GameTimerCountUp(void);
void GameMoveDistanceCountUp(struct SubCharacter* scp, int status);
void GameKillEnemyCountUp(u_short atk);
void GameBoatTimerCountUp(void);
void GameBoatMaxSpeedCheck(float spd);
void GameItemGetCountUp(void);
void GameJamesDamagedCountUp(float damage);
void GameMariaDamagedCountUp(u_short atk, float damage);
u_int GameCalcRankSaveCount(void);
u_int GameCalcRankEndingKind(void);
u_int GameCalcRankBattleLevel(void);
u_int GameCalcRankRiddleLevel(void);
u_int GameCalcRankItemGet(void);
u_int GameCalcRankHiddenItemGet(void);
u_int GameCalcRankKillByShot(void);
u_int GameCalcRankKillByFight(void);
u_int GameCalcRankClearTime(void);
u_int GameCalcRankBoatClearTime(void);
u_int GameCalcRankJamesDamage(void);
u_int GameCalcRankTotal(void);
void GameSavePreviousTotalRank(void);
void GameSaveSprayPower(void);

#endif // PLAYER_RESULT_H
