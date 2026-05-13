#ifndef M3_PLAY_H
#define M3_PLAY_H

#include "sh2_common.h"
#include "Chacter/character.h"

void PlayerCheckInit(struct SubCharacter* player); // I have no fucking idea
void actwithwep_flg_set(u_char status /* r2 */, struct shPlayerWork* w /* r16 */);
void player_flg_on(int* type /* r2 */, u_int status /* r2 */);
int l_anime_flg_on(u_int status /* r2 */);
int PlayerNowItemName(u_char wep /* r2 */);

#endif // M3_PLAY_H
