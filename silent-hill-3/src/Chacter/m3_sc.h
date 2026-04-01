#ifndef M3_SC_H
#define M3_SC_H

#include "Chacter/character.h"

int shCharacter_Manage_Delete(u_short kind, u_short id);

static void shCharacterDelete(SubCharacter* scp);

extern SubCharacter* D_003DAD54;
extern void* D_003DAD50;
extern int D_003DAD5C;

#define HEATHER_CHARA_ID 0x100
#define DOUGLAS_CHARA_ID 0x101
#define CLAUDIA_CHARA_ID 0x102
#define VINCENT_CHARA_ID 0x103
#define DOUGLAS_CC_CHARA_ID 0x104
#define DOUGLAS_DD_CHARA_ID 0x105
#define DOUBLE_HEAD_CHARA_ID 0x200
#define NUMB_BODY_CHARA_ID 0x201
#define CLOSER_CHARA_ID 0x202
#define NURSE_CHARA_ID 0x203
#define INSANE_CANCER_CHARA_ID 0x204
#define PENDULUM_CHARA_ID 0x205
#define SCRAPER_CHARA_ID 0x206
#define SEWER_MONSTER_CHARA_ID 0x207
#define EN_DED1_CHARA_ID 0x208
#define CAROUSEL_HORSE_CHARA_ID 0x209
#define SLURPER_E_CHARA_ID 0x20a
#define SLURPER_X_CHARA_ID 0x20b
#define SPLIT_WORM_CHARA_ID 0x210
#define MISSIONARY_CHARA_ID 0x211
#define VALTIEL_CHARA_ID 0x212
#define LEONARD_WOLF_CHARA_ID 0x213
#define GOD_CHARA_ID 0x214
#define MEMORY_OF_ALESSA_CHARA_ID 0x215

#endif
