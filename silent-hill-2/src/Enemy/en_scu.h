#ifndef EN_SCU_H
#define EN_SCU_H

void enFlagResetRotFloor(EnLOCAL_DATA* dp);
int enSetPath(EnLOCAL_DATA* dp, float* target, float* pos);
int enCheckSpray(EnLOCAL_DATA* dp);
float enReduceHP(EnLOCAL_DATA* dp);
int enCheckDamage(EnLOCAL_DATA* dp);
void enSetHitBack(EnLOCAL_DATA* dp);
void enInitPath(EnPATH_DATA* p, float angle);
void enSetNewSize(EnLOCAL_DATA* dp, float size, float tall, float center, float eye);
int enCheckInstantDeath(EnLOCAL_DATA* dp);
int enCheckFinishedByHuman(EnLOCAL_DATA* dp);
void enAnimePause(EnLOCAL_DATA* dp);
void enFlagSetLieDown(EnLOCAL_DATA* dp);
void enFlagSetRotFloor(EnLOCAL_DATA* dp);
void enKillCountUp(EnLOCAL_DATA* dp);
void enMoveAngle(EnPATH_DATA* p, float delta);
void enResetDamage(EnLOCAL_DATA* dp);
void enFlagSetNoDamage(EnLOCAL_DATA* dp);
int enGetMode(void);
void enSetTimer(EnLOCAL_DATA* dp, int t);
void enFlagResetNoDamage(EnLOCAL_DATA* dp);
int enReduceTimer(EnLOCAL_DATA* dp);
void enFlagResetLieDown(EnLOCAL_DATA* dp);
float enAddHP(EnLOCAL_DATA* dp, float n);

#endif // EN_SCU_H
