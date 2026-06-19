#ifndef M3_PLAY_COMMON_H
#define M3_PLAY_COMMON_H

#include "common.h"
#include "Chacter/character.h"

void PlayerSpeedDownToStand(SubCharacter* p /* r16 */);

void lower_stand(SubCharacter* p /* r16 */);
void upper_stand(SubCharacter* p /* r2 */);
void lower_relax(SubCharacter* p /* r16 */);
void upper_relax(SubCharacter* p); // arg not present in DWARF
void lower_alert(SubCharacter* p); // arg not present in DWARF
void upper_alert(SubCharacter* p); // arg not present in DWARF
void lower_tired(SubCharacter* p /* r16 */);
void upper_tired(SubCharacter* p /* r2 */);
void lower_ready(SubCharacter* p /* r2 */);
void upper_ready(SubCharacter* p); // arg not present in DWARF
void lower_readyoff(SubCharacter* p); // arg not present in DWARF
void upper_readyoff(SubCharacter* p); // arg not present in DWARF

void PlayerCheckAttack(SubCharacter* this);

#endif // M3_PLAY_COMMON_H
