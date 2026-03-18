#ifndef HOSPITAL_B_00_H
#define HOSPITAL_B_00_H

#include "common.h"
#include "Chacter/m3_bgobj.h"
#include "Chacter/m3_sc.h"

/**
 * @brief Deletes nurses from the birthday room based on drug & ammo points.
 */
void func_01F6E5B0_hospital_b_00(void);

u_char GetActionLevel(void);
int GetItemCount(int);

extern int D_01F70540_hospital_b_00;
extern int birthday_room_ammo_total;
extern int birthday_room_drug_total;

extern int D_01F706C8_hospital_b_00;
extern int D_01F706D0_hospital_b_00;
extern int D_01F706D8_hospital_b_00;
extern int D_01F706E0_hospital_b_00;
extern int D_01F706E8_hospital_b_00;
extern int D_01F706F0_hospital_b_00;
extern int birthday_ampoules;
extern int birthday_first_aid_kits;
extern int birthday_handgun_bullets;
extern int birthday_health_drinks;
extern int birthday_shotgun_shells;
extern int birthday_submachine_gun_bullets;

void fontClear(void);
int func_00168440(void);
int func_0016C1C0(int);
void func_00190A20(int);
int func_00190C00(void);
extern u_int D_01F706F8_hospital_b_00;
extern u_int D_1D31694[];

#endif
