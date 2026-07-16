#ifndef M3_PLAY_H
#define M3_PLAY_H

#include "sh2_common.h"
#include "Chacter/character.h"

void player_flg_on(u_int* type, u_int status);

void player_flg_off(u_int* type, u_int status);

int upper_flg_on(u_int status);

int lower_flg_on(u_int status);

int u_anime_flg_on(u_int status);

int l_anime_flg_on(u_int status);

int actwithwep_flg_on(u_int status);

void lower_st_set(int status, shPlayerWork* w);

void upper_st_set(int status, shPlayerWork* w);

void lower_flg_set(int status, shPlayerWork* w);

void upper_flg_set(int status, shPlayerWork* w);

void actwithwep_flg_set(u_char status, shPlayerWork* w);

void PlayerCheckInit(SubCharacter* this);

void PlayerSetHeightDummy(void);

void PlayerSetHeight(SubCharacter* this);

void PlayerSetHeightConnectWait(void);

void PlayerCheckBothArmsAngle(SubCharacter* this);

void BoatPlayerCheckAnime(void);

void shGetJamesLightPos(float* pos, float* vec);

void shGetJamesLightPosOriginal(float* pos, float* vec);

void shGetJamesLightPos_Calc(void);

void GetPlayerPartsMatrixForCameraCtrl(float (*mat)[4], u_int parts_name);

void GetPlayerPartsWorldMatrix(float (*mat)[4], u_int parts_name);

void GetPlayerPartsLocalMatrix(sceVu0FMATRIX dest, int parts_name);

shCharaInfo* GetPlayerInfoForCameraCtrl(void);

void shCharacterPlayerWorkInitAtPowerOn(void);

void shCharacterPlayerWorkInitAtGameStart(void);

void shCharacterSetPlayerLow(SubCharacter* scp);

void PlayerGetTargetInfo(void);

void PlayerGetTarget(void);

void PlayerChangeTarget(int key);

void PlayerCheckHuggingAttack(void);

int PlayerChectGuardSuccess(void);

void PlayerRequestAttack(shPlayerWork* w, int num);

void PlayerRequestAttackFinish(shPlayerWork* w);

void PlayerCheckStraightLine(SubCharacter* this, float spd_roty);

void shGetJamesKickStartPos(float* pos, float* vec);

void shGetJamesTrampStartPos(float* pos, float* vec);

int PlayerNowItemName(u_char wep);

int PlayerSearchVIewButtonCheck(void);

float PlayerGetNeckAngleX(void);

float PlayerGetNeckAngleY(void);

void PlayerInitOnConnect(void);

void PlayerStatusClear(void);

void close_to_angle_target(float* now, float tgt, float min, float max, float spd);

void close_to_value(float* now, float tgt, float mov);

int PlayerReverseLightCalcIsOn(void);

int PlayerWaterRoadIsOn(void);

#endif // M3_PLAY_H
