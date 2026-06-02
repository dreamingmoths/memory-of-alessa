#ifndef M3_SC_H
#define M3_SC_H

#include "common.h"
#include "Chacter/character.h"
#include "shared/Chacter_Draw/clani.h"

#define HHH_JMS_CHARA_ID 0x103 // highest detail james model
#define EN_RED_CHARA_ID 0x208 // pyramid head
#define LAU_CHARA_ID 0x104 // laura
#define AGL_CHARA_ID 0x107 // angela
#define EN_PAP_CHARA_ID 0x204 // abstract daddy

#define IS_PLAYER_KIND(_kind) ((_kind) >= 0x100 && (_kind) <= 0x103)
#define IS_ENEMY_KIND(_kind) ((_kind) >= 0x200 && (_kind) < 0x300)

// E:\work\sh2(CVS全取得)\src\Chacter\m3_sc.c
extern struct shCharacterAll sh2chara; // size: 0x6810, address: 0x3C84D0

void shCharacterSetPlayer(SubCharacter* scp);

short shCharacterAnimeFrameGet_(SubCharacter* scp /* r2 */, u_int type /* r2 */);
AnimeInfo* shCharacterAnimeGetInfo(SubCharacter* scp /* r2 */); 
AnimeInfo* shCharacterAnimeGetInfo_(SubCharacter* scp /* r2 */, int ctrl_type /* r2 */);
void shCharacterAnimeFrameSet(SubCharacter* scp /* r2 */, u_short frame /* r2 */);
void shCharacterAnimeRestart(SubCharacter* scp /* r2 */);

void shCharacterDelete(SubCharacter* scp);

short shCharacterGetModelID(SubCharacter* scp /* r2 */);
void SCAnimeTypeSwitch(SubCharacter* scp /* r2 */, int flag /* r2 */);
SubCharacter* shCharacterGetSubCharacter(u_short kind /* r2 */, short id /* r2 */);
void shCharacterSetFunction(SubCharacter* scp /* r2 */, void (* func)(SubCharacter *) /* r2 */); 
void* shCharacterGetAnimeAdrForPlay(SubCharacter * scp /* r2 */);
void shCharacterAnimeSet(SubCharacter* scp /* r19 */, int ctrl_type /* r2 */, int inter_type /* r18 */, AnimeInfo* anim_info /* r17 */, int anime /* r2 */);
void* shCharacterGetAnimeAdrForDrama(SubCharacter* scp /* r2 */);

void SCNowPlayableEventSwitch(SubCharacter* scp /* r2 */, int flag /* r2 */);

#endif
