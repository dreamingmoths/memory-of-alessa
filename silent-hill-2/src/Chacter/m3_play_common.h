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

void upper_run1(SubCharacter* p /* r2 */);
void upper_run2(SubCharacter* p /* r16 */);
void upper_run3(SubCharacter* p /* r2 */);

void lower_hold(SubCharacter* p /* r18 */);
void upper_hold(SubCharacter* p /* r17 */);

void lower_release(SubCharacter* p /* r17 */);
void upper_release(SubCharacter* p); // arg not present in DWARF

void lower_attack(SubCharacter* p /* r18 */);
void upper_attack(SubCharacter* p /* r18 */);
void lower_kick(SubCharacter* p /* r16 */);
void upper_kick(SubCharacter* p /* r2 */);

void lower_damage(SubCharacter* p /* r17 */);
void upper_damage(SubCharacter* p); // arg not present in DWARF

void lower_fall(SubCharacter* p /* r16 */);
void upper_fall(SubCharacter* p); // arg not present in DWARF

void lower_event(SubCharacter* p /* r16 */);
void upper_event(SubCharacter* p /* r2 */);

void lower_to_stand(SubCharacter* p); // arg not present in DWARF
void upper_to_stand(SubCharacter* p); // arg not present in DWARF

void upper_wall_f(SubCharacter* p); // arg not present in DWARF

void PlayerSetDT(void);

void PlayerUpdateStatus(SubCharacter* this);
void PlayerCheckAttack(SubCharacter* this);

#endif // M3_PLAY_COMMON_H
