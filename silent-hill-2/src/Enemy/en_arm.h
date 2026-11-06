#ifndef EN_ARM_H
#define EN_ARM_H

#include "sh2_common.h"
#include "Enemy/en_common.h"

void enARMInitData(EnLOCAL_DATA* dp);
void enARMCtrlMain(struct EnLOCAL_DATA * dp /* r2 */);
void enARMCtrlAutomatic(EnLOCAL_DATA* dp);
void enARMCtrlSleep(EnLOCAL_DATA* dp /* r16 */);
void enARMCtrlGoPlayable(EnLOCAL_DATA* dp /* r2 */);
void enARMCtrlEvent(EnLOCAL_DATA* dp /* r2 */);
void enARMCtrlHand(EnLOCAL_DATA* dp);
void enARMCtrlWander(EnLOCAL_DATA* dp /* r17 */);
void enARMCtrlTurn(EnLOCAL_DATA* dp /* r16 */);
void enARMCtrlDamage(EnLOCAL_DATA* dp);
void enARMCtrlDead(EnLOCAL_DATA* dp);
void enARMCheckNearPlayer(EnLOCAL_DATA* dp);
int enARMGetDamageMotion(EnLOCAL_DATA* dp);
int enARMCanSeePlayer(EnLOCAL_DATA * dp /* r16 */);
int enARMCheckNearOther(struct EnLOCAL_DATA * dp /* r18 */);
void enARMAnimeSet(EnLOCAL_DATA * dp /* r17 */, int anim /* r16 */);
void enARMAnimeReset(EnLOCAL_DATA * dp /* r17 */, int anim /* r16 */);
void enARMAnimeExec(struct EnLOCAL_DATA * dp /* r16 */);
void enARMSetHandPos(EnLOCAL_DATA * dp /* r16 */, int d /* r2 */);
void enARMGetHandPos(float * vec /* r17 */, EnLOCAL_DATA * dp /* r16 */, int d /* r2 */);
int enARMCheckFloor(EnLOCAL_DATA * dp /* r2 */, int d /* r2 */);
float enARMGetMoveSpeed(EnLOCAL_DATA * dp /* r16 */);
void enARMSoundSigns(EnLOCAL_DATA * dp /* r16 */);

#endif // EN_ARM_H
