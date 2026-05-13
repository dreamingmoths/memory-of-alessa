#ifndef M3_SC_H
#define M3_SC_H

#include "common.h"
#include "Chacter/character.h"
#include "shared/Chacter_Draw/clani.h"

// E:\work\sh2(CVS全取得)\src\Chacter\m3_sc.c
extern struct shCharacterAll sh2chara; // size: 0x6810, address: 0x3C84D0

void shCharacterSetPlayer(SubCharacter* scp);

short shCharacterAnimeFrameGet_(SubCharacter * scp /* r2 */, u_int type /* r2 */);
AnimeInfo* shCharacterAnimeGetInfo_(SubCharacter* scp /* r2 */, int ctrl_type /* r2 */);

void SCNowPlayableEventSwitch(SubCharacter * scp /* r2 */, int flag /* r2 */);

#endif
