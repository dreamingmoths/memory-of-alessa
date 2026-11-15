#ifndef EF_STAGE_H
#define EF_STAGE_H

#include "common.h"
#include "Effect/ef_common.h"

int InitEffectObjectGunFire(EFCTObject* pObj, int nIndex, sceVu0FVECTOR Pos, sceVu0FVECTOR vec, int wep_kind, u_char light_status);

int InitEffectObjectGunSmoke(EFCTObject* pObj, int nIndex, sceVu0FVECTOR Pos, int wep_kind, u_char light_status);

void DrawBloodSpray(void* task);

void DrawBloodDrop(void* task);

void DrawBloodPool(void* task);

void DrawGunFire(void* task);

void DrawGunSmoke(void* task);

u_short GetStageEffectLayerNum(short EffectKind);

void InitBloodTexEnv(EFCTTexEnvInfo* pTexInfo);

void InitGunFireTexEnv(EFCTTexEnvInfo* pTexInfo);

void InitGunSmokeTexEnv(EFCTTexEnvInfo* pTexInfo);

#endif // EF_STAGE_H
