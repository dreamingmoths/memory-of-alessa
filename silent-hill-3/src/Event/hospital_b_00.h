#ifndef HOSPITAL_B_00_H
#define HOSPITAL_B_00_H

#include "common.h"
#include "Chacter/m3_bgobj.h"
#include "Chacter/m3_sc.h"

/**
 * @brief Deletes nurses from the birthday room based on drug & ammo points.
 */
void func_01F6E5B0_hospital_b_00(void);

void func_01F6DBF0_hospital_b_00(void);
void func_01F6E4E0_hospital_b_00(void);
void func_01F6DD80_hospital_b_00(void);                   
void func_01F6E360_hospital_b_00(void);                   
void func_01F6E980_hospital_b_00(void);

void fontClear(void);
int func_00168440(void);
int func_0016C190(void);
void func_0016C1A0(void);  
void func_0016C1B0(void);
int func_0016C1C0(int);
void func_0016C3C0(void);   
int func_0016BED0(int, int);
void func_00190A20(int);
int func_00190C00(void);
void func_001C2290(int, float);
void func_0016CA40(int);                                
void func_00189F00(u_short);                                
void func_00189FA0(int, int);                           
int func_00190050(void);                                
int func_00190950(void);                              
int func_0019B580(int);                             
void func_0019F820(void);                                 
void func_002FE380(void);  
int RoomName();
u_char GetActionLevel(void);
int GetItemCount(int);
void SeCall(float, float, int);
float shGetDT(void);
void clAddDynamicWall(int *);
void clAddDynamicFloor(int *);

extern int D_01F70528_hospital_b_00;
extern int D_01F70540_hospital_b_00;
extern int birthday_room_ammo_total;
extern int birthday_room_drug_total;

extern int D_01F70600_hospital_b_00;
extern float D_01F70608_hospital_b_00;
extern int D_01F70610_hospital_b_00;
extern int D_01F70618_hospital_b_00;
extern int D_01F70620_hospital_b_00;
extern int D_01F70628_hospital_b_00;
extern int D_01F70630_hospital_b_00;
extern int D_01F706C8_hospital_b_00;
extern int D_01F706D0_hospital_b_00;
extern int D_01F706D8_hospital_b_00;
extern int D_01F706E0_hospital_b_00;
extern int D_01F706E8_hospital_b_00;
extern int D_01F706F0_hospital_b_00;
extern int D_01F6FC20_hospital_b_00;
extern int D_01F6FCC0_hospital_b_00;
extern int D_01F6FEA0_hospital_b_00;
extern int D_01F70030_hospital_b_00;
extern int D_01F702B0_hospital_b_00;
extern int D_01F70350_hospital_b_00;

extern int birthday_ampoules;
extern int birthday_first_aid_kits;
extern int birthday_handgun_bullets;
extern int birthday_health_drinks;
extern int birthday_shotgun_shells;
extern int birthday_submachine_gun_bullets;

extern u_int D_01F706F8_hospital_b_00;
extern u_int D_1D31644[];
extern u_int D_1D31648[];
extern u_int D_1D31694[];
extern u_int D_1D31698[];
extern u_int D_1D316F4[];
extern u_int D_1D31728[];
extern u_int D_1D317C0[];
extern u_int D_1D3172C[];
                            
#endif
